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

	bool VideoConverter::initialize(uint8 videoNum) {

		deleteObject(_dstFile);
		deleteObject(_srcFile);
		releaseMemory(_frameBuffer);

		_frameBuffer = (byte*) allocateMemory(1, GS_BITMAP_SIZE, MF_Clear, GS_COMMENT_FILE_LINE);

		_srcFile = newObject<TagReadFile>(GS_COMMENT_FILE_LINE);
		CHECK_IF_RETURN(_srcFile == NULL, false, "Could not allocate src Video File!");

		_srcFile->open(GS_GAME_PATH "RESOURCE/OPENING.SAN");

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

		_dstFile->open(GS_GAME_PATH "RESOURCE/OPENING.GSV");

		if (_dstFile->isOpen() == false) {
			error(GS_THIS, "Could not open destination Video File!");
			abort_quit_stop();
			deleteObject(_dstFile);
			return false;
		}

		_videoEncoder = &GSV_ENCODER;

		VideoEncoderParams encoderParams;
		encoderParams.left_px = 0;
		encoderParams.top_px = 0;
		encoderParams.width_px = GS_BITMAP_PITCH;
		encoderParams.height_px = GS_BITMAP_ROWS;
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

		return true;
	}

	void VideoConverter::run() {

		VideoFrame* frame = acquireVideoFrame();


		while(true) {
			frame->recycle();
			_videoDecoder->processFrame(frame);
			_videoEncoder->processFrame(frame);

			if (frame->_timing.action == VFNA_Stop) {
				break;
			}
		}

		disposeVideoFrame(frame);

		_videoEncoder->teardown();
		_videoDecoder->teardown();
	}

	int convertVideo(uint8 videoNum) {
		VideoConverter* converter = newObject<VideoConverter>(GS_COMMENT_FILE_LINE);
		if (converter->initialize(videoNum) == false) {
			deleteObject(converter);
			return 1;
		}

		converter->run();
		deleteObject(converter);
		return 0;
	}

}
