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
#include "../screen.h"
#include "../room.h"  // For RoomPaletteData

namespace gs
{
	VideoContext* VIDEO = NULL;

	void tempAnimation(uint32 frame) {

		int y = frame;
		y %= GS_SCREEN_HEIGHT;
		drawBox(0, 0, y, GS_SCREEN_WIDTH, 1);
		y++;
		y %= GS_SCREEN_HEIGHT;
		drawBox(frame, 0, y, GS_SCREEN_WIDTH, 8);

	}

	VideoContext::VideoContext() {
	}

	VideoContext::~VideoContext() {
	}

	void VideoContext::loadVideo(uint8 id) {
		/* Temporary Code to imitate Video Playing */

		_videoStateKind = VSK_Loaded;
	}

	void VideoContext::unloadVideo() {
		/* Temporary Code to imitate Video Playing */

		_videoStateKind = VSK_NotLoaded;
	}

	void VideoContext::playVideoFrame() {

		/* Temporary Code to imitate Video Playing */

		if (_videoStateKind == VSK_Loaded) {
			_videoStateKind = VSK_Playing;
			_videoFrameCounter = 0;

			RoomPaletteData pal;

			int16 j=0;
			for(uint16 i=0,j=0;i < 256;i++) {
				pal.palette[j++] = i & 0xFF;
				pal.palette[j++] = i*4 & 0xFF;
				pal.palette[j++] = i*8 & 0xFF;
			}

			setRoomPalette(&pal);
			clearScreen(0);
			return;
		}


		if (_videoStateKind == VSK_Playing) {
			_videoFrameCounter++;
			tempAnimation(_videoFrameCounter);

			debug(GS_THIS, "Video Frame %ld", _videoFrameCounter);

			if (_videoFrameCounter >= 25 * 30) {
				_videoStateKind = VSK_Stopped;
			}

			return;
		}

	}

}
