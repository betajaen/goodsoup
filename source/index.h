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

			diskNum = _roomDisks[roomNum];
			offset = _roomOffsets[roomNum];

			return true;
		}

		bool getScript(uint16 scriptNum, uint8& roomNum, uint32& offset) {

			if (scriptNum >= NUM_SCRIPTS) {
				error(GS_THIS, "Attempted to load script out of bounds! %ld", (uint32) scriptNum);
				return false;
			}

			roomNum = _scriptRoom[scriptNum];
			offset = _scriptOffset[scriptNum];

			return true;
		}

		String getRoomName(uint8 idx) const {
			return String();
		}

		uint16 findObjectNumFromHash(uint32 hash);

		bool getObject(uint16 objectNum, uint16& roomNum, uint8& diskNum) {

			if (objectNum >= NUM_OBJECT_GLOBALS) {
				error(GS_THIS, "Attempted to load object out of bounds! %ld", (uint32)objectNum);
				return false;
			}

			roomNum = _objectRoomNum[objectNum];
			diskNum = _roomDisks[roomNum];

			return true;
		}

		uint32 getObjectClass(uint16 objectNum) const {
			if (objectNum >= NUM_OBJECT_GLOBALS) {
				error(GS_THIS, "Attempted to load object out of bounds! %ld", (uint32)objectNum);
				return false;
			}

			return _objectClass[objectNum];
		}

		uint32 getObjectClass_unchecked(uint16 objectNum) const {
			return _objectClass[objectNum];
		}

	private:

		uint8 _roomDisks[NUM_ROOMS];
		uint32 _roomOffsets[NUM_ROOMS];
		uint32 _roomScriptOffsets[NUM_ROOMS];
		uint8  _scriptRoom[NUM_SCRIPTS];
		uint32 _scriptOffset[NUM_SCRIPTS];
		uint32 _objectNameHash[NUM_OBJECT_GLOBALS];
		byte _objectState[NUM_OBJECT_GLOBALS];
		byte _objectRoomNum[NUM_OBJECT_GLOBALS];
		byte _objectOwner[NUM_OBJECT_GLOBALS];
		uint32 _objectClass[NUM_OBJECT_GLOBALS];


	};
}

#endif