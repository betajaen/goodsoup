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
	int16* sDeltaPalette;
	byte* sFrames[3];
	byte  sCurrentFrameBuffer;
	byte  sDeltaFrameBuffers[2];
	char* sSubtitleText;
	byte* sCompressedAudioSample;
	uint16 sFrameCount;
	uint16 sFrameNum;
	uint32 sFrameRate;
	uint32 sAudioRate;

	// Declared in Font.h
	bool parseFormattedDialogue2(const char* text, char* out_text, uint32 &out_translationHash, uint8 &out_fontNum, uint8 &out_Colour, uint8& out_Kind);
	void printDialogue(const char* text, uint32 id, uint8 kind);

	static byte* getFrameBuffer(uint8 buffer) {
		CHECK_IF_RETURN(buffer > 2, sFrames[0], "Out of bounds for FrameBuffer.");
		return sFrames[buffer];
	}

	static void readPalette();

	static bool readDeltaPalette(bool isApply);

	static inline void readTiming() {
		sFile->skip(10);
		sFrameNum = sFile->readUInt16LE();
	}

	static void readAudio(TagPair iact, VideoFrame* frame);

	static void readVideo(TagPair fobj, VideoFrame* frame);

	static bool readSubtitles(TagPair text, SubtitleFrame* subtitleFrame);

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
		sSubtitleText = (char*) allocateMemory(480, sizeof(char), MF_Clear, GS_COMMENT_FILE_LINE);
		sCompressedAudioSample = (byte*) allocateMemory(4096 + 2, sizeof(byte), MF_Clear, GS_COMMENT_FILE_LINE);
		sDeltaPalette = (int16*) allocateMemory(256, 3 * sizeof(int16), MF_Clear, GS_COMMENT_FILE_LINE);
		sCurrentFrameBuffer = 2;
		sDeltaFrameBuffers[0] = 0;
		sDeltaFrameBuffers[1] = 1;

		return true;
	}

	static void smush_teardown() {
		releaseMemoryChecked(sDeltaPalette);
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
					if (readDeltaPalette(tag.length == 6)) {
						PaletteFrame* pal = frame->addPalette();
						copyMemQuick((uint32*) &pal->_palette[0], (uint32*) sPalette, 3 * 256);
					}
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

					// debug(GS_THIS, "Frame %ld of %ld", sFrameNum, sFrameCount);

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
					SubtitleFrame* subtitleFrame = frame->addSubtitle();
					if (readSubtitles(tag, subtitleFrame) == false) {
						frame->removeSubtitle(subtitleFrame);
					}
					printDialogue(subtitleFrame->string(), subtitleFrame->hash, subtitleFrame->kind);
				}
				continue;

				case GS_MAKE_ID('S','T','O','R'): {
					// N/A - I think
					sFile->seekEndOf(tag);
				}
				continue;

				case GS_MAKE_ID('F','T','C','H'): {
					ImageFrame* imageFrame = frame->addImage();
					copyMemQuick( (uint32*) imageFrame->_video, (uint32*)  getFrameBuffer(sCurrentFrameBuffer), GS_BITMAP_SIZE);
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
	// Palette
	//
	//

	static void readPalette() {
		sFile->readBytes(sPalette, 768);
	}

	static bool readDeltaPalette(bool isApply) {

		if (isApply) {
			sFile->skip(6);

			for(uint16 i=0;i < 768;i++) {
				uint16 s = (uint16) sPalette[i];
				int16 d = sDeltaPalette[i];

				int16 c = ((s * 129 + d) / 128);
				if (c > 255)
					c = 255;
				else if (c < 0)
					c = 0;

				sPalette[i] = (uint8) c;
			}

			return true;
		}
		else {

			sFile->skip(4);
			sFile->readBytes((void*) sDeltaPalette, 768 * sizeof(int16));
			sFile->readBytes((void*) sPalette, 768 * sizeof(byte));

			// Swap LE to System Endian on sDeltaPalette
#if GS_BIG
			for(uint16 i=0;i < 768;i++) {
				sDeltaPalette[i] = FROM_LE_16(sDeltaPalette[i]);
			}
#endif

			return false;
		}
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

	static bool readSubtitles(TagPair text, SubtitleFrame* subtitleFrame) {
		uint16 subtitleLength = text.length - 16;

		CHECK_IF_RETURN_1(subtitleLength > 479, false, "Subtitle has too many %ld characters to draw.", subtitleLength);

		subtitleFrame->x = sFile->readInt16LE();
		subtitleFrame->y = sFile->readInt16LE();
		uint32 flags = sFile->readInt16LE();
		uint8 sfFlags = 0;

		if (flags == 13 || flags == 9 || flags == 1)
			sfFlags |= SF_Center;
		if (flags == 13)
			sfFlags |= SF_Wrap;

		subtitleFrame->flags = sfFlags;

		sFile->skip((sizeof(uint16) * 3) + 4);
		sFile->readBytes(sSubtitleText, subtitleLength);

		char* out_text = subtitleFrame->string();
		bool wasParsed = parseFormattedDialogue2(sSubtitleText, out_text, subtitleFrame->hash, subtitleFrame->font, subtitleFrame->colour, subtitleFrame->kind);

		return wasParsed;
	}


}

gs::VideoCodec SMUSH_VIDEO_CODEC = {
		&gs::smush_initialize,
		&gs::smush_teardown,
		&gs::smush_processFrame
};