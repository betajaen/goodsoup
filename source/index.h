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

#ifndef GS_INDEX_H
#define GS_INDEX_H

#include "types.h"
#include "buffer.h"
#include "file.h"

#include "resource.h"
#include "profile.h"
#include "string.h"

namespace gs
{
	class Index;

	extern Index* INDEX;

	template<int Kind, uint16 Capacity>
	class ResourceIndexTable {
	public:

		void reset() {
			clearMemoryNonAllocated(_diskOrRoomNum, sizeof(_diskOrRoomNum));
			clearMemoryNonAllocated(_offset, sizeof(_offset));
		}

		const char* _name;
		uint8  _diskOrRoomNum[Capacity];
		uint32 _offset[Capacity];
	};


	struct ObjectLocation
	{
		String  _name;
		byte   _state;
		byte   _roomNum;
		byte   _owner;
		byte   _padding;
		uint32 _class;
	};

	class Index
	{
	public:

		Index();
		~Index();

		bool readFromFile(const char* path);

		bool getRoom(uint16 roomNum, uint8& diskNum, uint32& offset) {

			if (roomNum >= NUM_ROOMS) {
				error(GS_THIS, "Attempted to load room out of bounds! %ld", (uint32)roomNum);
				return false;
			}

			diskNum = _roomsResources._diskOrRoomNum[roomNum];
			offset = _roomsResources._offset[roomNum];

			return true;
		}

		bool getScript(uint16 num, uint8& roomNum, uint32& offset) {

			if (num >= NUM_SCRIPTS) {
				error(GS_THIS, "Attempted to load script out of bounds! %ld", (uint32)num);
				return false;
			}

			roomNum = _scriptsResources._diskOrRoomNum[num];
			offset = _scriptsResources._offset[num];

			return true;
		}

		String getRoomName(uint8 idx) const {
			if (idx >= NUM_ROOMS) {
				return String();
			}
			else {
				return _roomNames[idx];
			}
		}

		bool getObject(uint16 objectNum, uint16& roomNum, uint8& diskNum) {
			
			if (objectNum >= NUM_OBJECT_GLOBALS) {
				error(GS_THIS, "Attempted to load object out of bounds! %ld", (uint32)objectNum);
				return false;
			}

			roomNum = _objects[objectNum]._roomNum;
			diskNum = _roomsResources._diskOrRoomNum[roomNum];

			return true;
		}

	private:

		String					    _roomNames[NUM_ROOMS + 1];
		ResourceIndexTable<RK_ROOM, NUM_ROOMS>		_roomsResources;
		ResourceIndexTable<RK_SCRIPT, NUM_ROOMS>		_roomsScriptsResources;
		ResourceIndexTable<RK_SCRIPT, NUM_SCRIPTS>	_scriptsResources;
		ResourceIndexTable<RK_SOUND, NUM_SOUNDS>	_soundsResources;
		ResourceIndexTable<RK_COSTUME, NUM_COSTUMES>	_costumesResources;
		ResourceIndexTable<RK_CHARSET, NUM_CHARSETS>	_charsetResources;
		ObjectLocation	_objects[NUM_OBJECT_GLOBALS];

	};
}

#endif