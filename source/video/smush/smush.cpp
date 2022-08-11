/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#define GS_FILE_NAME "smush"

#include "forward.h"
#include "file.h"
#include "containers.h"
#include "video/video_frame.h"
#include "video/video_api.h"

namespace gs
{
	TagReadFile* sFile;
	byte* sPalette;
	byte* sFrames[3];
	byte  sCurrentFrameBuffer;
	byte  sDeltaFrameBuffers[2];
	char* sSubtitleText;
	byte* sCompressedAudioSample;
	uint16 sFrameCount;
	uint16 sFrameNum;
	uint32 sFrameRate;
	uint32 sAudioRate;

	static inline void readPalette() {
		sFile->readBytes(sPalette, 3 * 256);
	}

	static bool readDeltaPalette() {
		/* TODO */
		return false; // Palette should not be applied.
	}

	static inline void readTiming() {
		sFile->skip(10);
		sFrameNum = sFile->readUInt16LE();
	}

	static void readAudio(TagPair iact, VideoFrame* frame);

	static void readVideo(TagPair fobj, VideoFrame* frame);

	static void readSubtitles(TagPair text, VideoFrame* frame);

	static bool readSmushFileHeader() {
		uint16 version;
		TagPair tag;


		sFile->seek(0);

		tag = sFile->readSanTagPair(true);

		if (tag.isTag(GS_MAKE_ID('A','N','I','M')) == false) {
			error(GS_THIS, "This is not an ANIM SAN file! Missing ANIM tag got %s", tag.tagStr());
			abort_quit_stop();
			return false;
		}

		tag = sFile->readSanTagPair(true);

		if (tag.isTag(GS_MAKE_ID('A','H','D','R')) == false) {
			error(GS_THIS, "This is not an ANIM SAN file! Missing ANHD tag got %s!", tag.tagStr());
			abort_quit_stop();
			return false;
		}

		// Check version
		version = sFile->readUInt16LE();
		if (version != 2) {
			error(GS_THIS, "This SMUSH version %ld is not supported!", (uint32) version);
			abort_quit_stop();
			return false;
		}

		// Read AHDR

		sFrameNum = 0;
		sFrameCount = sFile->readUInt16LE();
		sFile->skip(sizeof(uint16));

		sPalette = (byte*) allocateMemory(256, 3 * sizeof(byte), MF_Clear, GS_COMMENT_FILE_LINE);
		readPalette();
		sFrameRate = sFile->readUInt32LE();
		sFile->skip(sizeof(uint32));
		sAudioRate = sFile->readUInt32LE();

		sFile->seekEndOf(tag);

		return true;
	}

	static bool smush_initialize(TagReadFile* file) {
		sFile = file;

		if (readSmushFileHeader() == false) {
			return false;
		}

		// Setup memory (palette is created in isSmush)
		byte* videoFrames = (byte*) allocateMemory(3, GS_BITMAP_SIZE, MF_Clear, GS_COMMENT_FILE_LINE);
		sFrames[0] = videoFrames;
		sFrames[1] = videoFrames + GS_BITMAP_SIZE;
		sFrames[2] = videoFrames + GS_BITMAP_SIZE + GS_BITMAP_SIZE;
		sSubtitleText = (char*) allocateMemory(256, sizeof(char), MF_Clear, GS_COMMENT_FILE_LINE);
		sCompressedAudioSample = (byte*) allocateMemory(4096 + 2, sizeof(byte), MF_Clear, GS_COMMENT_FILE_LINE);

		sCurrentFrameBuffer = 3;
		sDeltaFrameBuffers[0] = 0;
		sDeltaFrameBuffers[1] = 1;

		return true;
	}

	static void smush_teardown() {
		releaseMemoryChecked(sCompressedAudioSample);
		releaseMemoryChecked(sSubtitleText);
		releaseMemoryChecked(sFrames[0]);
		sFrames[1] = NULL;
		sFrames[2] = NULL;
		releaseMemoryChecked(sPalette);
		sFile = NULL;
	}

	static uint8 smush_processFrame(VideoFrame* frame) {

		CHECK_IF_RETURN(frame == NULL, 2, "NULL VideoFrame given!");

		TagPair frme, tag;
		frme = sFile->readSanTagPair(true);
		bool increaseFrameNum = true;

		CHECK_IF_RETURN_2(frme.isTag(GS_MAKE_ID('F','R','M','E')) == false, 2, "Unexpected tag \"%s\" when trying to read a FRME at pos %ld", frme.tagStr(), (sFile->pos() - 8));

		while(sFile->pos() < frme.end()) {
			tag = sFile->readSanTagPair(true);

			switch(tag.tag) {

				case GS_MAKE_ID('N','P','A','L'): {
					readPalette();
					PaletteFrame* pal = frame->addPalette();
					copyMemQuick((uint32*) &pal->_palette[0], (uint32*) sPalette, 3 * 256);
				}
				continue;

				case GS_MAKE_ID('X','P','A','L'): {
					if (readDeltaPalette()) {
						PaletteFrame* pal = frame->addPalette();
						copyMemQuick((uint32*) &pal->_palette[0], (uint32*) sPalette, 3 * 256);
					}
					sFile->seekEndOf(tag);
				}
				continue;

				case GS_MAKE_ID('I','A','C','T'): {
					// IACT Tag is different to other SAN tags.
					TagPair iact;
					iact.dataPos = tag.dataPos;
					sFile->skip(-4);
					iact.length = sFile->readUInt32BE();

					readTiming();
					increaseFrameNum = false;
					frame->_timing.num = sFrameNum;
					frame->_timing.length_msec = 83; // Default

					debug(GS_THIS, "Frame %ld of %ld", sFrameNum, sFrameCount);

#if GS_MUTE_AUDIO == 0
					readAudio(iact, frame);
#endif

					sFile->seekEndOf(tag);
				}
				continue;

				case GS_MAKE_ID('F','O','B','J'): {
					readVideo(tag, frame);
					sFile->seekEndOf(tag);
				}
				continue;

				case GS_MAKE_ID('T','E','X','T'): {
					readSubtitles(tag, frame);
					sFile->seekEndOf(tag);
				}
				continue;

			}

			warn(GS_THIS, "Unsupported SMUSH FRME tag %s", tag.tagStr());
			sFile->seekEndOf(tag);
		}

		if (increaseFrameNum) {
			sFrameNum++;
		}

		return 1;
	}


	//
	// Audio
	//

	static void readAudio(TagPair iact, VideoFrame* frame) {

		/* TODO */
	}

	//
	// Video
	//

	static void readVideo(TagPair fobj, VideoFrame* frame) {

		/* TODO */
	}

	//
	// Subtitles
	//

	static void readSubtitles(TagPair text, VideoFrame* frame) {

		/* TODO */
	}


}

gs::VideoCodec SMUSH_VIDEO_CODEC = {
		&gs::smush_initialize,
		&gs::smush_teardown,
		&gs::smush_processFrame
};