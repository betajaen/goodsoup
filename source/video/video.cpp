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
#include "san/codec.h"
#include "../screen.h"
#include "../room.h"  // For RoomPaletteData
#include "../disk.h"

namespace gs
{

	VideoContext* VIDEO = NULL;

	void getSANApi(VideoApi* api);

	VideoContext::VideoContext() {
		_api.initialize = NULL;
		_api.teardown = NULL;
		_api.processFrame = NULL;
	}

	VideoContext::~VideoContext() {

		if (_api.teardown != NULL) {
			_api.teardown();
		}
		_file.close();
	}

	void VideoContext::loadVideo(uint8 id) {
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
	}

	void VideoContext::unloadVideo() {
		/* Temporary Code to imitate Video Playing */

		_videoStateKind = VSK_NotLoaded;
	}

	void VideoContext::playVideoFrame() {

		int32 frames = -1;

		/* Temporary Code to imitate Video Playing */

		if (_videoStateKind == VSK_Loaded) {
			_videoStateKind = VSK_Playing;
			_videoFrameCounter = 0;

			CHECK_IF(_api.processFrame == NULL, "Initialize API function is NULL");

			frames = _api.processFrame();

			if (frames < 0) {
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

	}

}
