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

#define GS_FILE_NAME "object"

#include "object.h"
#include "memory.h"

namespace gs
{
	ObjectState* OBJECTS = NULL;
	Array<ObjectData*, uint16> DRAWING_OBJECTS;

	ObjectState::ObjectState() {
		for (uint16 i = 0; i < MAX_OBJECTS; i++) {
			_objects[i]._idx = i;
		}
	}

	ObjectState::~ObjectState() {
	}

	uint16 ObjectState::newObject(uint16 num) {
		for (uint16 i = 1; i < MAX_OBJECTS; i++) {
			ObjectData& object = _objects[i];

			if (object._bUsed == false) {
				object._num = num;
				object._bUsed = true;
				return i;
			}
		}

		return 0;
	}
	
	uint16 ObjectState::releaseObjectByIdx(uint16 idx) {
		if (idx > 0 && idx < MAX_OBJECTS) {
			ObjectData& object = _objects[idx];
			object.clear();
		}
	}

	uint16 ObjectState::releaseObjectByNum(uint16 objectNum) {
		uint16 idx = findObjectIdxByNum(objectNum);

		if (idx != 0) {
			releaseObjectByIdx(idx);
		}
	}

	uint16 ObjectState::findObjectIdxByNum(uint16 objectNum) {
		for (uint16 i = 1; i < MAX_OBJECTS; i++) {
			ObjectData& object = _objects[i];
			if (object._num == objectNum) {
				return i;
			}
		}

		return 0;
	}
	
	void ObjectState::clearObjects() {
		for (uint16 i = 1;i < MAX_OBJECTS; i++) {
			ObjectData& object = _objects[i];
			object.clear();
		}
	}
	
	void ObjectState::clearRoomObjects() {
		for (uint16 i = 1; i < MAX_OBJECTS; i++) {
			ObjectData& object = _objects[i];

			if ((object._bIsFloating == false) || (object._bIsLocked == false)) {
				object.clear();
			}
		}
	}

	void ObjectData::clear() {
		_num = 0;
		_roomNum = 0;
		_bUsed = false;
		_bIsFloating = false;
		_bIsLocked = false;
	}


}
