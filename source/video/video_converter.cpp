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

#define GS_FILE_NAME "video_converter"

#include "video_converter.h"
#include "video_api.h"
#include "video_frame.h"
#include "memory.h"
#include "profile.h"
#include "file.h"
#include "audio.h"
#include "string.h"

extern gs::VideoDecoder SMUSH_DECODER;
extern gs::VideoEncoder GSV_ENCODER;
extern gs::VideoDecoder GSV_DECODER;

namespace gs
{
	// Declared in video/smush/smush_tables.cpp
	void smush_tables_initialize();
	void smush_tables_teardown();

	VideoConverter::VideoConverter() {
		_srcFile = NULL;
		_dstFile = NULL;
		_frameBuffer = NULL;
		initializeVideoFrameData();
		smush_tables_initialize();
	}

	VideoConverter::~VideoConverter() {
		disposeVideoFrameData();
		deleteObject(_dstFile);
		deleteObject(_srcFile);
		releaseMemory(_frameBuffer);
		smush_tables_teardown();
	}

	bool VideoConverter::initialize(uint8 videoNum, bool halfFrameSize) {

		deleteObject(_dstFile);
		deleteObject(_srcFile);
		releaseMemory(_frameBuffer);

		_videoNum = videoNum;
		_halfFrameSize = halfFrameSize;
		_frameBuffer = (byte*) allocateMemory(1, GS_BITMAP_SIZE, MF_Clear, GS_COMMENT_FILE_LINE);

		_srcFile = newObject<TagReadFile>(GS_COMMENT_FILE_LINE);
		CHECK_IF_RETURN(_srcFile == NULL, false, "Could not allocate src Video File!");

		String srcPath;

		if (tryGetVideoPath(srcPath, "SAN", videoNum) == false) {
			error(GS_THIS, "Could not find Video File!");
			abort_quit_stop();
			deleteObject(_srcFile);
			return false;
		}

		_srcFile->open(srcPath.string());

		if (_srcFile->isOpen() == false) {
			error(GS_THIS, "Could not open Video File!");
			abort_quit_stop();
			deleteObject(_srcFile);
			return false;
		}

		_videoDecoder = &SMUSH_DECODER;

		if (_videoDecoder->initialize(_srcFile) == false) {
			error(GS_THIS, "Could not read Video File!");
			abort_quit_stop();
			deleteObject(_srcFile);
			_videoDecoder = NULL;
			return false;
		}

		_dstFile = newObject<WriteFile>(GS_COMMENT_FILE_LINE);
		CHECK_IF_RETURN(_dstFile == NULL, false, "Could not allocate Video dst File!");

		String dstPath;
		CHECK_IF_RETURN(tryGetVideoPath(dstPath, "GSV", videoNum) == false, false, "Could not create Destination Video Path");

		_dstFile->open(dstPath.string());

		if (_dstFile->isOpen() == false) {
			error(GS_THIS, "Could not open destination Video File!");
			abort_quit_stop();
			deleteObject(_dstFile);
			return false;
		}

		_videoEncoder = &GSV_ENCODER;

		VideoEncoderParams encoderParams;
		encoderParams.left_px = _halfFrameSize ? GS_BITMAP_HALF_LEFT : GS_BITMAP_LEFT;
		encoderParams.top_px = _halfFrameSize ? GS_BITMAP_HALF_TOP : GS_BITMAP_TOP;
		encoderParams.width_px = _halfFrameSize ? GS_BITMAP_HALF_PITCH : GS_BITMAP_PITCH;
		encoderParams.height_px = _halfFrameSize ? GS_BITMAP_HALF_ROWS : GS_BITMAP_ROWS;
		encoderParams.audioFormat = AF_S16MSB;
		encoderParams.audioFrequency_hz = 22050;
		encoderParams.audioSampleRate_bytes = (1024 * 2 * sizeof(int16));

		if (_videoEncoder->initialize(_dstFile, encoderParams) == false) {
			error(GS_THIS, "Could not open destination Video File!");
			abort_quit_stop();
			deleteObject(_srcFile);
			_videoEncoder = NULL;
			return false;
		}


		debug_write_str("Converting ");
		debug_write_str(srcPath.string());
		debug_write_str(" to ");
		debug_write_str(dstPath.string());
		debug_write_char('\n');

		return true;
	}

	void VideoConverter::run() {

		VideoFrame* frame = acquireVideoFrame();

		debug_write_str("Processing Frames\n");
		uint16 counter = 0;
		uint8 tens = 0;

		uint32 lastDialogue = 0;

		while(true) {
			frame->recycle();
			_videoDecoder->processFrame(frame);

			bool shouldHalfSize = false;

			frame->_timing.clearFlags = 0;


			/* Half size */
			if (_halfFrameSize && frame->_image != NULL ) {
				shouldHalfSize = true;

				// OPENING.SAN/GSV  Credits
				if (_videoNum == 9 && frame->_timing.num >= 1722 && frame->_timing.num <= 3057) {
					shouldHalfSize = false;

					if (frame->_timing.num >= 3038) { // A few frames off.
						frame->_timing.clearFlags = 1;
					}
				}

			}

			/* Clear background for dialogue, if it has changed and half size */
			if (shouldHalfSize) {
				if (frame->_subtitles.hasAny()) {
					SubtitleFrame *subtitleFrame = frame->_subtitles.peekFront();

					if (subtitleFrame->hash != lastDialogue) {
						frame->_timing.clearFlags = 1;
					}

					lastDialogue = subtitleFrame->hash;
				} else {
					/* Clear background if there was dialogue */
					if (lastDialogue != 0) {
						frame->_timing.clearFlags = 1;
						lastDialogue = 0xFFFFffff;
					}
				}

			}

			if (shouldHalfSize) {
				reduceFrameSizeToHalf(frame);
			}

			_videoEncoder->processFrame(frame);

			if (frame->_timing.action == VFNA_Stop) {
				break;
			}

			counter++;
			tens++;

			if (tens == 10) {
				tens = 0;
				debug_write_int(counter);
				debug_write_char('\n');
			}
		}

		disposeVideoFrame(frame);

		debug_write_str("Completed.\n");
		_videoEncoder->teardown();
		_videoDecoder->teardown();
	}

	void VideoConverter::reduceFrameSizeToHalf(VideoFrame* frame) {
		ImageFrame* image = frame->_image;

		uint8* dst = image->getData();
		uint8* src = image->getData();

		uint16 y = GS_BITMAP_HALF_ROWS;
		while(y--) {
			uint16 x = GS_BITMAP_HALF_PITCH;

			while(x--) {
				*dst++ = *src++;
				src++;
			}

			src += GS_BITMAP_PITCH;
		}

		image->width = GS_BITMAP_HALF_PITCH;
		image->height = GS_BITMAP_HALF_ROWS;
		image->left = GS_BITMAP_LEFT;
		image->top = GS_BITMAP_TOP;
		image->size = GS_BITMAP_HALF_SIZE;
		image->format = IFF_HalfFrameRaw;

	}

	int convertVideo(uint8 videoNum, bool halfSize) {
		VideoConverter* converter = newObject<VideoConverter>(GS_COMMENT_FILE_LINE);
		if (converter->initialize(videoNum, halfSize) == false) {
			deleteObject(converter);
			return 1;
		}

		converter->run();
		deleteObject(converter);
		return 0;
	}

}
