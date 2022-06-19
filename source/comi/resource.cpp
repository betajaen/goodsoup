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
#include "constants.h"

using namespace common;

namespace comi
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

		_scripts.reset();
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
			error(COMI_THIS, "Unknown disk %ld", num);
			return _disk[0];
		}

		return _disk[num - 1];
	}

	ScriptData* Resources::loadScriptData(uint16 num)
	{
		uint8 script_roomNum;
		uint32 script_offset;

		if (INDEX->getScript(num, script_roomNum, script_offset) == false) {
			return NULL;
		}

		uint8 room_diskNum;
		uint32 room_resOffset;

		if (INDEX->getRoom(script_roomNum, room_diskNum, room_resOffset) == false) {
			return NULL;
		}

		uint32 room_offset;
		Disk& disk = _getDisk(room_diskNum);
		disk.getRoomOffset(script_roomNum, room_offset);

		ScriptData* script = _scripts.create(num, room_diskNum);
		debug(COMI_THIS, "%ld", room_offset + script_offset);
		DiskReader reader = disk.readSection(room_offset + script_offset);

		if (script->readFromDisk(reader) == false) {
			_scripts.destroy(script);
			return NULL;
		}

		return script;
	}

	RoomData* Resources::loadRoom(uint16 num)
	{
		/* TODO */
		return NULL;
	}


	ScriptData* Resources::getScriptData(uint16 num) {
		ScriptData* script = _scripts.find(num);

		if (script == NULL) {
			script = loadScriptData(num);
		}

		return script;
	}

}
