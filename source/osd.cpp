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

#define GS_FILE_NAME "osd"

#include "resource.h"
#include "room.h"
#include "vm/vm.h"
#include "string.h"
#include "screen.h"
#include "globals.h"
#include "index.h"
#include "object.h"

namespace gs
{

	void runOSD() {

		if (PAUSED) {
			drawSystemText(1, 10, 10, "Paused");
		}

		drawSystemTextF(1, 10, 20, "Frame: %ld", FRAME_NUM);

		drawSystemTextF(1, 10, 30, "Mouse: %ld %ld %ld %ld", MOUSE_X, MOUSE_Y, MOUSE_LMB_STATE, MOUSE_RMB_STATE);

		RoomData* room = getRoom();

		if (room == NULL) {
			drawSystemText(1, 10, 40, "Room: <NONE>");
		}
		else {

			String roomName = INDEX->getRoomName(room->getNum());

			drawSystemTextF(1, 10, 40, "Room: %ld %s", (uint32) room->getNum(), roomName.string());
		}

		drawSystemTextF(1, 10, 50, "Objects: %ld", (uint32) OBJECTS->getCount());

	}

}
