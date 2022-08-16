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

#ifndef GS_VIDEO_H
#define GS_VIDEO_H

#include "forward.h"
#include "containers.h"
#include "file.h"
#include "video/video_api.h"

namespace gs
{

	class VideoFrame;
	class AudioStream_S16MSB;
	class VideoDecoder;
	class VideoEncoder;

	enum VideoStateKind {
		VSK_NotLoaded = 0,
		VSK_Loaded = 1,
		VSK_Playing = 2,
		VSK_Stopped = 3
	};

	class VideoContext {

		uint8 _videoStateKind;
		uint32 _videoFrameCounter;
		int32 _waitFrames;

		ReadFile _file;
		VideoApi _api;
		VideoDecoder* _videoDecoder;
		VideoEncoder* _videoEncoder;
		TagReadFile* _srcFile;
		WriteFile* _dstFile;

		byte* _frameBuffer;

		Queue<VideoFrame> _frames;
		uint16 _framesInQueue;
		uint8 _nextFrameAction;
		AudioStream_S16MSB* _audioStream;

		bool _acquireNextFrame();

	public:

		VideoContext();
		~VideoContext();

		void loadVideo(uint8 id);
		void unloadVideo();
		void playVideoFrame();

		inline uint8 getVideoStateKind() const {
			return _videoStateKind;
		}

	};


	extern VideoContext* VIDEO;

}

#endif