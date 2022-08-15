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

#define GS_FILE_NAME "video"
#define TEMP_USE_VIDEO_CODEC 0
#include "video.h"
#include "video/video_api.h"
#include "video/video_frame.h"
#include "san/codec.h"
#include "screen.h"
#include "room.h"  // For RoomPaletteData
#include "disk.h"
#include "audio.h"

extern gs::VideoDecoder SMUSH_DECODER;

namespace gs
{

	VideoContext* VIDEO = NULL;

	void getSANApi(VideoApi* api);

	VideoContext::VideoContext() {

		_videoCodec = NULL;

		_api.initialize = NULL;
		_api.teardown = NULL;
		_api.processFrame = NULL;

#if TEMP_USE_VIDEO_CODEC
		initializeVideoFrameData();

		_audioStream = createAudioStream();
		pushAudioStream(_audioStream);
		_frameBuffer = (byte*) allocateMemory(1, GS_BITMAP_SIZE, MF_Clear, GS_COMMENT_FILE_LINE_NOTE("FrameBuffer"));
#endif

	}

	VideoContext::~VideoContext() {
#if TEMP_USE_VIDEO_CODEC

		releaseMemoryChecked(_frameBuffer);

		VideoFrame* frame = _frames.pullFront();
		while(frame != NULL) {
			disposeVideoFrame(frame);
			frame = _frames.pullFront();
		}
		_frames.clear();

		if (_videoCodec != NULL) {
			_videoCodec->teardown();
		}

		deleteObject(_videoFile);


		popAudioStream();
		releaseAudioStream(_audioStream);
		_audioStream = NULL;

		debug(GS_THIS, "Video End");

		disposeVideoFrameData();
#else
		if (_api.teardown != NULL) {
			_api.teardown();
		}
		_file.close();
#endif
	}

	void VideoContext::loadVideo(uint8 id) {
#if TEMP_USE_VIDEO_CODEC
		_videoStateKind = VSK_Loaded;
		_videoFile = newObject<TagReadFile>(GS_COMMENT_FILE_LINE);
		CHECK_IF(_videoFile == NULL, "Could not allocate Video File!");

		_videoFile->open(GS_GAME_PATH "RESOURCE/OPENING.SAN");

		if (_videoFile->isOpen() == false) {
			error(GS_THIS, "Could not open Video File!");
			abort_quit_stop();
			deleteObject(_videoFile);
			return;
		}

		_videoCodec = &SMUSH_DECODER;

		if (_videoCodec->initialize(_videoFile) == false) {
			error(GS_THIS, "Could not read Video File!");
			abort_quit_stop();
			deleteObject(_videoFile);
			_videoCodec = NULL;
			return;
		}

#else
		/* Temporary Code to imitate Video Playing */
		_videoStateKind = VSK_Loaded;

		// Temp. Ignore ID and just open OPENING.SAN for now.
		_file.open(GS_GAME_PATH "RESOURCE/OPENING.SAN");

		if (_file.isOpen() == false) {
			error(GS_THIS, "Could not open Video File!");
			abort_quit_stop();
			return;
		}

		// Temp. Figure out codec from extension name and call the appropriate API.
		getSANApi(&_api);

		_api.initialize(DiskReader(_file));
#endif
	}

	void VideoContext::unloadVideo() {
		/* Temporary Code to imitate Video Playing */

		_videoStateKind = VSK_NotLoaded;
	}

	bool VideoContext::_acquireNextFrame() {

#if TEMP_USE_VIDEO_CODEC
		VideoFrame* frame = acquireVideoFrame();
		_nextFrameAction = _videoCodec->processFrame(frame);

		if (_nextFrameAction == 0) {
			// An Error has happened
			disposeVideoFrame(frame);
			return false;
		}
		else if (_nextFrameAction == 1) {
			// Received a frame
			_frames.pushBack(frame);
			_framesInQueue++;
			return true;
		}
		else if (_nextFrameAction == 2) {
			// Received last frame
			_frames.pushBack(frame);
			_framesInQueue++;
			return false;
		}

		// Fallback
		return false;

#endif

	}

	void VideoContext::playVideoFrame() {
#if TEMP_USE_VIDEO_CODEC

		while(_framesInQueue < 4) {
			if (_acquireNextFrame() == false)
				break;
		}


		// TODO: Timing

		VideoFrame* oldest = _frames.pullFront();

		if (oldest) {
			_framesInQueue--;
			oldest->apply(_frameBuffer, _audioStream);
			screenBlitCopy(_frameBuffer);
			if (oldest->_timing.action == VFNA_Stop) {
				_videoStateKind = VSK_Stopped;
			}

			disposeVideoFrame(oldest);
		}
		else {
			debug(GS_THIS, "No more frames. Stopping");
			_videoStateKind = VSK_Stopped;
		}

#else
		int32 frames = -1;

		/* Temporary Code to imitate Video Playing */

		if (_videoStateKind == VSK_Loaded) {
			_videoStateKind = VSK_Playing;
			_videoFrameCounter = 0;

			CHECK_IF(_api.processFrame == NULL, "Initialize API function is NULL");

			frames = _api.processFrame();

			if (frames <0) {
				_videoStateKind = VSK_Stopped;
				CHECK_IF(_api.teardown != NULL, "ProcessFrame API function is NULL");
				_api.processFrame();
				_file.close();
			}
			else {
				_waitFrames = _waitFrames;
			}

			return;
		}


		if (_videoStateKind == VSK_Playing) {
			_videoFrameCounter++;
			_waitFrames--;

			if (_waitFrames <= 0) {

				CHECK_IF(_api.processFrame == NULL, "ProcessFrame API function is NULL");
				frames = _api.processFrame();

				if (frames < 0) {
					_videoStateKind = VSK_Stopped;
					CHECK_IF(_api.teardown != NULL, "Teardown API function is NULL");
					_api.teardown();
					_file.close();
				}
				else {
					_waitFrames = frames;
				}
			}

			return;
		}
#endif

	}

}
