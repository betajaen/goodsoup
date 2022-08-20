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

#include "video.h"
#include "video/video_api.h"
#include "video/video_frame.h"
#include "video/video_converter.h"
#include "san/codec.h"
#include "screen.h"
#include "room.h"  // For RoomPaletteData
#include "disk.h"
#include "audio.h"
#include "image.h"
#include "globals.h"
#include "input.h"

extern gs::VideoDecoder SMUSH_DECODER;
extern gs::VideoEncoder GSV_ENCODER;
extern gs::VideoDecoder GSV_DECODER;

namespace gs
{
	// amiga/timer.cpp
	// sdl/main.cpp
	int32 getMSec();

	// source/video/video.cpp
	static void audioStreamCallback(void* videoPtr, void* audioFrame, uint16 frameNum);

	VideoContext* VIDEO = NULL;

	void getSANApi(VideoApi* api);

	VideoContext::VideoContext() {

		initializeVideoFrameData();

		_videoDecoder = NULL;

		_srcFile = NULL;

		_audioStream = NULL;
		_frameBuffer = (byte*) allocateMemory(1, GS_BITMAP_SIZE, MF_Clear, GS_COMMENT_FILE_LINE_NOTE("FrameBuffer"));

	}

	VideoContext::~VideoContext() {

		releaseMemoryChecked(_frameBuffer);

		disposeExtractedSubtitles(_keptSubtitlesHead, _keptSubtitlesTail);
		_keptSubtitlesHead = NULL;
		_keptSubtitlesTail = NULL;

		VideoFrame* frame = _frames.pullFront();

		while(frame != NULL) {
			disposeVideoFrame(frame);
			frame = _frames.pullFront();
		}
		_frames.clear();


		if (_videoDecoder != NULL) {
			_videoDecoder->teardown();
		}

		deleteObject(_srcFile);

		if (_audioStream != NULL) {
			popAudioStream();
			releaseAudioStream(_audioStream);
			_audioStream = NULL;
		}

		debug(GS_THIS, "Video End");

		disposeVideoFrameData();

	}

	void VideoContext::loadVideo(uint8 id) {

		_videoStateKind = VSK_Loaded;
		_srcFile = newObject<TagReadFile>(GS_COMMENT_FILE_LINE);
		CHECK_IF(_srcFile == NULL, "Could not allocate src Video File!");

		String srcPath;

		if (tryGetVideoPath(srcPath, "GSV", id) == false) {
			error(GS_THIS, "Could not find Video File!");
			abort_quit_stop();
			deleteObject(_srcFile);
			return;
		}

		_srcFile->open(srcPath.string(), false);

		if (_srcFile->isOpen() == true) {
			_videoDecoder = &GSV_DECODER;
		}
		else {
			CHECK_IF(tryGetVideoPath(srcPath, "SAN", id) == false, "Could not create Source Video Path");

			_srcFile->open(srcPath.string());

			if (_srcFile->isOpen() == false) {
				error(GS_THIS, "Could not open Video File!");
				abort_quit_stop();
				deleteObject(_srcFile);
				return;
			}

			_videoDecoder = &SMUSH_DECODER;
		}


		if (_videoDecoder->initialize(_srcFile) == false) {
			error(GS_THIS, "Could not read Video File!");
			abort_quit_stop();
			deleteObject(_srcFile);
			_videoDecoder = NULL;
			return;
		}

		_audioStream = createAudioStream();
		_audioStream->userData = this;
		_audioStream->callback = &audioStreamCallback;

		pushAudioStream(_audioStream);

		nextFrame = 0;
		showNextFrame = false;

		while(_framesInQueue < 4) {
			debug(GS_THIS, "QUEUE FRAME");
			if (_acquireNextFrame() == false)
				break;
		}


		startTime = getMSec();
		nextTime = startTime;

	}

	void VideoContext::unloadVideo() {
		/* Temporary Code to imitate Video Playing */

		_videoStateKind = VSK_NotLoaded;
	}

	bool VideoContext::_acquireNextFrame() {

		VideoFrame* frame = acquireVideoFrame();
		_nextFrameAction = _videoDecoder->processFrame(frame);

		if (_nextFrameAction == 0) {
			// An Error has happened
			disposeVideoFrame(frame);
			return false;
		}
		else if (_nextFrameAction == 1) {
			// Received a frame
			_frames.pushBack(frame);
			_framesInQueue++;
			frame->queueAudio(_audioStream);
			return true;
		}
		else if (_nextFrameAction == 2) {
			// Received last frame
			_frames.pushBack(frame);
			_framesInQueue++;
			frame->queueAudio(_audioStream);
			return false;
		}

		// Fallback
		return false;
	}

	void VideoContext::playVideoFrame() {

		if (PAUSED) {
			if (KEY_EVENT != KE_StepForward) {
				return;
			}
		}

		uint32 now = getMSec();
		if (now < nextTime)
			return;
		uint32 diff = now - nextTime;


		//mutex.lock();
		while(_framesInQueue < 4) {
			if (_acquireNextFrame() == false)
				break;
		}
		//mutex.unlock();

		// TODO: Thread/Interrupt safety.
		// mutex.lock();
		// if (showNextFrame == false) {
		// 	mutex.unlock();
		// 	return;
		// }
		// showNextFrame = false;
		// mutex.unlock();

		VideoFrame* oldest = _frames.pullFront();

		if (oldest) {

			_framesInQueue--;

			if (oldest->keepSubtitles() && oldest->hasSubtitles() == false) {
				oldest->injectSubtitles(_keptSubtitlesHead, _keptSubtitlesTail);
				_keptSubtitlesHead = NULL;
				_keptSubtitlesTail = NULL;
			}
			else {
				if (_keptSubtitlesTail != NULL && _keptSubtitlesHead != NULL) {
					disposeExtractedSubtitles(_keptSubtitlesHead, _keptSubtitlesTail);
					_keptSubtitlesHead = NULL;
					_keptSubtitlesTail = NULL;
				}
			}

			oldest->apply(_frameBuffer);

			screenBlitCopy(_frameBuffer);

			if (oldest->keepSubtitles() && oldest->hasSubtitles()) {
				oldest->extractSubtitles(_keptSubtitlesHead, _keptSubtitlesTail);
			}

			if (KEY_EVENT == KE_StepForward) {
				debug(GS_THIS, "Frame %ld", oldest->_timing.num);
			}

			if (oldest->_timing.action == VFNA_Stop) {
				_videoStateKind = VSK_Stopped;
			}


			nextTime = startTime - diff + ((oldest->getNum() * 1000) / 12);

			// debug(GS_THIS, "Frame %ld", oldest->_timing.num);
			disposeVideoFrame(oldest);



		}
		else {
			debug(GS_THIS, "No more frames. Stopping");
			_videoStateKind = VSK_Stopped;
		}

	}

	void VideoContext::streamCallback(AudioSampleFrame_S16MSB* audioSampleFrame, uint16 frameNum) {
		mutex.lock();
		if (frameNum == nextFrame) {
			nextFrame++;
			showNextFrame = true;
		}
		disposeAudioSampleFrame_S16MSB(audioSampleFrame);
		mutex.unlock();
	}

	static void audioStreamCallback(void* videoPtr, void* audioFrame, uint16 frameNum) {
		((VideoContext*) videoPtr)->streamCallback((AudioSampleFrame_S16MSB*) audioFrame, frameNum);

	}

}
