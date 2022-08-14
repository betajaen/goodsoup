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
#include "endian.h"
#include "video/video_frame.h"
#include "video/video_api.h"
#include "globals.h"

namespace gs
{
	static TagReadFile* sFile;
	static byte* sPalette;
	static int16* sDeltaPalette;
	static byte* sFrames[3];
	static byte* sTempBuffer;
	static byte* sStoredFrame;
	static byte  sCurrentFrameBuffer;
	static byte  sDeltaFrameBuffers[2];
	static char* sSubtitleText;
	static byte* sCompressedAudioSample;
	static uint16 sFrameCount;
	static uint16 sFrameNum;
	static uint32 sFrameRate;
	static uint32 sAudioRate;
	static int16 sPreviousSequenceNum;
	static uint8 sNextRotationOp;
	static bool sFrameStore;
	static uint16 sFrameVersion;
	static uint16 sFrameStoreVersion;
	static uint16 sFrameFetchVersion;
	static TagPair sLastFrmeTag;

	// Declared in Font.h
	bool parseFormattedDialogue2(const char* text, char* out_text, uint32 &out_translationHash, uint8 &out_fontNum, uint8 &out_Colour, uint8& out_Kind);

	// Declared in Font.h
	void printDialogue(const char* text, uint32 id, uint8 kind);

	// Declared in codecs/bomp.h
	void decodeBomp(byte* dst, byte* src, uint32 length);

#if GS_SAN_CODEC47 == 1
	// Declared in codec47_opt_none.cpp
	void smush_codec47_opt_none(byte* dst, byte* src, byte* src1, byte* src2, byte* params);
#endif

#if GS_SAN_CODEC47 == 2
	// Declared in codec47_opt_ulong.cpp
	void smush_codec47_opt_ulong(uint32* dst, uint32* src, uint32* src1, uint32* src2, byte* params);
#endif

	// Declared in smush.cpp
	void smush_tables_initialize();

	// Declared in smush.cpp
	void smush_tables_teardown();

	// Return a frame buffer 0,1 or 2 or otherwise abort
	static inline byte* getFrameBuffer(uint8 buffer) {
		CHECK_IF_RETURN(buffer > 2, sFrames[0], "Out of bounds for FrameBuffer.");
		return sFrames[buffer];
	}

	// Clear a frame buffer 0,1,2 with a given palette index
	static void clearFrameBuffer(uint8 buffer, uint8 colour) {
		uint32 col = colour << 24 | colour << 16 | colour << 8 | colour;
		uint32* dst = (uint32*) getFrameBuffer(buffer);
		uint32 length = GS_BITMAP_SIZE / 4;
		while(length--) {
			*dst++ = col;
		}
	}

	// Copy framebuffer src into framebuffer dst
	static void copyFrameBuffer(uint8 dst, uint8 src) {
		uint32* dstBuffer = (uint32*) getFrameBuffer(dst);
		uint32* srcBuffer = (uint32*) getFrameBuffer(src);
		copyMemQuick(dstBuffer, srcBuffer, GS_BITMAP_SIZE);
	}

	// Read a 256 colour RGB palette into sPalette.
	static void readPalette();

	// Read or apply a 16-bit delta multipliers to the current palette.
	static bool readDeltaPalette(bool isApply);

	// Read the IACT timing tag component
	static inline void readTiming() {
		sFile->skip(10);
		sFrameNum = sFile->readUInt16LE();
	}

	// Read the IACT audio tag component, and add audio samples to the given frame
	static void readAudio(TagPair iact, VideoFrame* frame);

	// Read the FOBJ video tag component, and add the video frame data to the frame
	static void readVideo(TagPair fobj, VideoFrame* frame);

	// Read one dialogue subtitle into the given subtitleFrame
	static bool readSubtitles(TagPair text, SubtitleFrame* subtitleFrame);

	// Read and validate the SMUSH file header
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

		sPreviousSequenceNum = -1;
		sFrameStore = false;
		sNextRotationOp = 0;

		return true;
	}

	// Initializer for the SMUSH codec. Should be called via the VideoCodec API before any
	// video decoding is performed!
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
		sTempBuffer = (byte*) allocateMemory(1, GS_BITMAP_SIZE, MF_Clear, GS_COMMENT_FILE_LINE);
		sStoredFrame = (byte*) allocateMemory(1, GS_BITMAP_SIZE, MF_Clear, GS_COMMENT_FILE_LINE);
		sCurrentFrameBuffer = 2;
		sDeltaFrameBuffers[0] = 0;
		sDeltaFrameBuffers[1] = 1;

		sFrameVersion = 0;
		sFrameStoreVersion = 0;
		sFrameFetchVersion = 0;

		smush_tables_initialize();

		return true;
	}

	// Teardown for the SMUSH codec. Should be called via the VideoCodec API after any
	// video decoding is performed.
	// All allocated memory is released.
	static void smush_teardown() {

		smush_tables_teardown();

		releaseMemoryChecked(sStoredFrame);
		releaseMemoryChecked(sTempBuffer);
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

		if (sFile->pos() >= sFile->length()) {
			frame->_timing.action = VFNA_Stop;
			return 2;
		}

		TagPair frme, tag;
		frme = sFile->readSanTagPair(true);
		bool increaseFrameNum = true;

		CHECK_IF_RETURN_2(frme.isTag(GS_MAKE_ID('F','R','M','E')) == false, 2, "Unexpected tag \"%s\" when trying to read a FRME at pos %ld", frme.tagStr(), (sFile->pos() - 8));

		bool probablySameCredits = false;

		if (sFrameStoreVersion > 0 && frme.length == sLastFrmeTag.length) {
			// Experimental:
			//  If we have a frame store, and the last frame length is the same length as this one, then the content
			//  is probably likely to be the same; such as the Credit sequences. For that we can skip over background redraws,
			//  and subtitles when they are the same.
			probablySameCredits = true;
		}

		// debug(GS_THIS, "%ld Last Size %ld New Size %ld Store %ld Fetch %ld", probablySameCredits, sLastFrmeTag.length, frme.length, sFrameStoreVersion, sFrameFetchVersion);

		while(sFile->pos() < frme.end() && sFile->pos() < sFile->length()) {
			tag = sFile->readSanTagPair(true);

			switch(tag.tag) {

				case GS_MAKE_ID('N','P','A','L'): {
					probablySameCredits = false;
					readPalette();
					PaletteFrame* pal = frame->addPalette();
					copyMemQuick((uint32*) &pal->palette[0], (uint32*) sPalette, 3 * 256);
				}
				continue;

				case GS_MAKE_ID('X','P','A','L'): {
					probablySameCredits = false;
					if (readDeltaPalette(tag.length == 6)) {
						PaletteFrame* pal = frame->addPalette();
						copyMemQuick((uint32*) &pal->palette[0], (uint32*) sPalette, 3 * 256);
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
					frame->_timing.action = VFNA_Next;

					// debug(GS_THIS, "Frame %ld of %ld", sFrameNum, sFrameCount);

#if GS_MUTE_AUDIO == 0
					readAudio(iact, frame);
#endif

					sFile->seekEndOf(tag);
				}
				continue;

				case GS_MAKE_ID('F','O','B','J'): {
					sFrameVersion++;
					sFrameStoreVersion = 0;
					probablySameCredits = false;
					readVideo(tag, frame);
					sFile->seekEndOf(tag);
				}
				continue;

				case GS_MAKE_ID('T','E','X','T'): {
					if (probablySameCredits == false) {
						SubtitleFrame *subtitleFrame = frame->addSubtitle();
						if (readSubtitles(tag, subtitleFrame) == false) {
							frame->removeSubtitle(subtitleFrame);
						}
					}
					else {
						sFile->seekEndOf(tag);
					}
				}
				continue;

				case GS_MAKE_ID('S','T','O','R'): {
					sFrameStore = true;
					sFile->seekEndOf(tag);
				}
				continue;

				case GS_MAKE_ID('F','T','C','H'): {
					if (probablySameCredits == false) {
						sFrameFetchVersion = sFrameStoreVersion;
						ImageFrame *imageFrame = frame->addImage();
						copyMemQuick((uint32 * ) & imageFrame->frame[0], (uint32 *) sStoredFrame, GS_BITMAP_SIZE);
					}
					sFile->seekEndOf(tag);
				}
				continue;

			}

			warn(GS_THIS, "Unsupported SMUSH FRME tag %s", tag.tagStr());
			sFile->seekEndOf(tag);
		}


		if (sFrameStore) {
			copyMemQuick((uint32*)  sStoredFrame, (uint32*)  getFrameBuffer(sCurrentFrameBuffer), GS_BITMAP_SIZE);
			sFrameStore = false;
			sFrameStoreVersion = sFrameVersion;
			// PAUSED = true;
		}

		if (sNextRotationOp != 0) {
			if (sNextRotationOp == 2) {
				GS_SWAP(byte, sDeltaFrameBuffers[0], sDeltaFrameBuffers[1]);
			}

			GS_SWAP(byte, sCurrentFrameBuffer, sDeltaFrameBuffers[1]);
			sNextRotationOp = 0;
		}

		if (sFile->pos() >= sFile->length()) {
			frame->_timing.action = VFNA_Stop;
			return 2;
		}

		if (increaseFrameNum) {
			sFrameNum++;
		}

		sLastFrmeTag = frme;

		if (sFrameNum >= sFrameCount) {
			frame->_timing.action = VFNA_Stop;
			return 2;
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
		bool hasFrame = false;
		byte header[40];
		sFile->readBytes(&header[0], sizeof(header));

		int16 sequenceNum = READ_LE_INT16(&header[14]);
		byte op = header[16];
		byte flags = header[18];

		if (flags & 1) {
			sFile->skip(0x8080);
		}

		uint8 offset1 = sDeltaFrameBuffers[1];
		uint8 offset2 = sDeltaFrameBuffers[0];

		if (sequenceNum == 0) {
			sPreviousSequenceNum = -1;

			clearFrameBuffer(sDeltaFrameBuffers[0], header[26]);
			clearFrameBuffer(sDeltaFrameBuffers[1], header[27]);
		}

		switch(op) {

			case 0:
				sFile->readBytes(getFrameBuffer(sCurrentFrameBuffer), GS_BITMAP_SIZE);
				hasFrame = true;
			break;

			case 1:
				break;

			case 2: {

				if (sequenceNum == sPreviousSequenceNum + 1) {
					uint32 length = fobj.end() - sFile->pos();
					CHECK_IF(length > GS_BITMAP_SIZE, "FOBJ Case 2 data is to large to read.");

					sFile->readBytes(sTempBuffer, length);

					uint8* dst = getFrameBuffer(sCurrentFrameBuffer);
					uint8* src = sTempBuffer;
					uint8* src1 = getFrameBuffer(sDeltaFrameBuffers[1]);
					uint8* src2 = getFrameBuffer(sDeltaFrameBuffers[0]);
					uint8* params = &header[22];

					smush_codec47_opt_none(dst, src, src1, src2, params);

					hasFrame = true;
				}

			}
			break;

			case 3:
				copyFrameBuffer(sCurrentFrameBuffer, sDeltaFrameBuffers[1]);
			break;

			case 4:
				copyFrameBuffer(sCurrentFrameBuffer, sDeltaFrameBuffers[0]);
			break;

			case 5: {
				uint32 length = READ_LE_UINT32(&header[28]);
				CHECK_IF(length > GS_BITMAP_SIZE, "BOMP Frame Length is to big.");

				byte* buffer = getFrameBuffer(sCurrentFrameBuffer);
				sFile->readBytes(sTempBuffer, length);
				decodeBomp(buffer, sTempBuffer, length);
				hasFrame = true;
			}
			break;

		}

		if (hasFrame) {
			ImageFrame* image = frame->addImage();
			copyMemQuick((uint32*) &image->frame[0], (uint32*) getFrameBuffer(sCurrentFrameBuffer), GS_BITMAP_SIZE);
		}

		if (sequenceNum == sPreviousSequenceNum + 1) {
			uint8 rotationOp = header[17];

			if (rotationOp != 0) {
				CHECK_IF_1(rotationOp > 2, "Unknown rotation op %ld.", rotationOp);

				sNextRotationOp = rotationOp;
			}
		}

		sPreviousSequenceNum = sequenceNum;
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