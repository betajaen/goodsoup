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

#define GS_FILE_NAME "resource"

#include "resource.h"
#include "index.h"
#include "disk.h"
#include "resource_data.h"
#include "room.h"
#include "script.h"
#include "disk.h"

#include "debug.h"
#include "profile.h"

namespace gs
{

	Resources* RESOURCES = NULL;

	Resources::Resources() {
	}

	Resources::~Resources() {
		close();
	}

	void Resources::close() {
		uint16 i, j;

		for (i = 0; i < NUM_DISKS; i++) {
			_disk[i].close();
		}

		_rooms.reset();
	}

	bool Resources::open() {
		uint16 i;

		for (i = 0; i < NUM_DISKS; i++) {
			uint32 diskNum = 1 + i;

			Disk& disk = _disk[i];
			if (disk.open(1 + i) == false)
				return false;
		}

		return true;
	}


	Disk& Resources::_getDisk(uint8 num) {

		if (num >= NUM_DISKS) {
			error(GS_THIS, "Unknown disk %ld", num);
			return _disk[0];
		}

		return _disk[num - 1];
	}

	RoomData* Resources::loadRoomData(uint16 num)
	{
		/* TODO */
		uint8 room_diskNum;
		uint32 room_resOffset;

		
		if (INDEX->getRoom(num, room_diskNum, room_resOffset) == false) {
			return NULL;
		}

		Disk& disk = _getDisk(room_diskNum);
		disk.getRoomOffset(num, room_resOffset);

		RoomData* room = _rooms.create(num, room_diskNum);
		DiskReader reader = disk.readSection(room_resOffset);

		if (room->readFromDisk(reader) == false) {
			_rooms.destroy(room);
			abort_quit_stop();
			return NULL;
		}

		return room;
	}

	RoomData* Resources::getRoomData(uint16 num) {
		RoomData* room = _rooms.find(num);

		if (room == NULL) {
			room = loadRoomData(num);
		}

		return room;
	}


}
