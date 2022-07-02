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
#include "room.h"

namespace gs
{
	ObjectState* OBJECTS = NULL;
	Array<ObjectVariant*, uint16> DRAWING_OBJECTS;

	ObjectState::ObjectState() {
	}

	ObjectState::~ObjectState() {
		release();
	}

	
	void ObjectState::release() {
		_objects.clear();
		_roomObjectDatas.clear();
	}


	ObjectVariant* ObjectState::newObject(uint16 num, uint8 kind) {
		ObjectVariant* object = _objects.acquire();
		object->_num = num;
		object->_kind = kind;

		switch (kind) {
			case OK_RoomObject: {
				object->_data._room = _roomObjectDatas.acquire();
			}
			break;
		}

		return object;
	}
	
	void ObjectState::releaseObject(ObjectVariant* object) {
		if (object == NULL ) {
			warn(GS_THIS, "Tried to release a NULL ObjectVariant!");
			return;
		}

		if (object->_kind == OK_None) {
			warn(GS_THIS, "Tried to release a None ObjectVariant!");
			return;
		}

		object->release();
		_objects.release_unchecked(object);
	}

	void ObjectState::releaseObjectByNum(uint16 objectNum) {
		releaseObject(findObjectByNum(objectNum));
	}

	void ObjectState::clearRoomObjects() {

		static Array<ObjectVariant*> objectsToClear;

		for(uint16 i=0;i < _objects.getSize(); i++) {

			ObjectVariant* object = _objects.get_unchecked(i);

			if (object->_kind == OK_RoomObject) {
				object->release();
				objectsToClear.push(object);
			}
			else if (object->_kind == OK_FLObject && object->isLocked() == false) {
				object->release();
				objectsToClear.push(object);
			}
		}

		if (objectsToClear.size()) {
			for (uint16 i = 0; i < objectsToClear.size(); i++) {
				ObjectVariant* object = objectsToClear.get_unchecked(i);
				_objects.release_unchecked(object);
			}

			objectsToClear.release();
		}

	}

	void ObjectVariant::release() {

		switch (_kind) {
			case OK_RoomObject: {
				_data._room->release();
				OBJECTS->_roomObjectDatas.release(_data._room);
				_data._room = NULL;
			}
			break;
			case OK_FLObject: {
				NO_FEATURE(GS_THIS, "Not handled for clear for OK_FLObject");
			}
			break;
			case OK_Actor: {
				NO_FEATURE(GS_THIS, "Not handled for clear for OK_Actor");
			}
			break;
			case OK_Inventory: {
				NO_FEATURE(GS_THIS, "Not handled for clear for OK_Inventory");
			}
			break;
		}

		_num = 0;
		_kind = OK_None;
		_flags = OVF_None;
		_data._room = NULL;
	}


}
