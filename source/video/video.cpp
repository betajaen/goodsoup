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
#include "san_codec.h"
#include "../screen.h"
#include "../room.h"  // For RoomPaletteData
#include "../disk.h"

namespace gs
{
	VideoContext* VIDEO = NULL;

	void tempAnimation(uint32 frame) {

		int y = frame;
		y %= GS_SCREEN_HEIGHT;
		screenDrawBox(0, 0, y, GS_SCREEN_WIDTH, 1);
		y++;
		y %= GS_SCREEN_HEIGHT;
		screenDrawBox(frame, 0, y, GS_SCREEN_WIDTH, 8);

	}

	VideoContext::VideoContext()
		: _codec(NULL) {
	}

	VideoContext::~VideoContext() {

		if (_codec != NULL) {
			deleteObject(_codec);
			_file.close();
		}
	}

	void VideoContext::loadVideo(uint8 id) {

		if (_codec) {
			deleteObject(_codec);
			_file.close();
		}

		/* Temporary Code to imitate Video Playing */
		_videoStateKind = VSK_Loaded;

		// Temp. Ignore ID and just open OPENING.SAN for now.
		_file.open(GS_GAME_PATH "RESOURCE/OPENING.SAN");

		if (_file.isOpen() == false) {
			error(GS_THIS, "Could not open Video File!");
			abort_quit_stop();
			return;
		}

		_codec = newObject<SanCodec>(DiskReader(_file), GS_COMMENT_FILE_LINE);
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

			int32 frames = _codec->presentFrame();

			if (frames < 0) {
				_videoStateKind = VSK_Stopped;
				deleteObject(_codec);
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
				int32 frames = _codec->presentFrame();
				if (frames < 0) {
					_videoStateKind = VSK_Stopped;
					deleteObject(_codec);
					_file.close();
				}
				else {
					_waitFrames = frames;
				}
			}

			return;
		}

	}

}
