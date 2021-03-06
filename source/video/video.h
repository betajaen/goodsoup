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

#include "../types.h"
#include "../file.h"

namespace gs
{

	class SanCodec;

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

		SanCodec* _codec;
		ReadFile _file;

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