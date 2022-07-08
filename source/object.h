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

#ifndef GS_OBJECT_H
#define GS_OBJECT_H

#include "types.h"
#include "pool.h"
#include "resource_data.h"
#include "span.h"
#include "disk.h"
#include "profile.h"
#include "debug.h"
#include "point.h"
#include "script.h"

namespace gs
{
	struct ActorObjectData;
	struct FLObjectData;
	struct InventoryObjectData;
	
	struct RoomObjectData;

	enum RoomObjectFlags {
		OF_None = 0,
		OF_AllowMaskOr = 1,
		OF_DrawMaskOnAll = 2,
		OF_ObjectMode = 8
	};

	enum ObjectKind {
		OK_NeverClip = 20,
		OK_AlwaysClip = 21,
		OK_IgnoreBoxes = 22,
		OK_YFlip = 29,
		OK_XFlip = 30,
		OK_Player = 31,
		OK_Untouchable = 32
	};

	struct ObjectData {
		uint16 _num;
		uint8 _parent;
		uint8 _parentState;
		uint8 _state;
		uint8 _flags;
		uint32 _class;
		int16 _x, _y;
		uint16 _width, _height;
		uint8 _bIsFloating;
		uint8 _bIsLocked;

		ScriptDataReference _script;

		bool isKind(uint8 objectKind) const;

		bool inBounds(int16 x, int16 y) const {
			return (_x <= x) && (_y <= y) && ( (_x + _width) >= x ) && ( (_y + _height) >= y );
		}

		bool isLocked() const {
			return _bIsLocked;
		}

		void setLocked(bool isLocked) {
			_bIsLocked = isLocked;
		}

		bool isFloating() const {
			return _bIsFloating;
		}

		void setFloating(bool isFloating) {
			_bIsFloating = isFloating;
		}

		void clear();
	};

	class ObjectState {
		AllocatedPool<ObjectData, uint16> _pool;

		DiskReader _seekToObject(uint16 objectNum, TagPair& out_tag);
		ObjectData* _readIntoObject(DiskReader& reader, const TagPair& parentTag, bool& out_isNew);

		ObjectData* _acquireByNum(uint16 num, bool& out_isNew);

	public:

		ObjectState();
		~ObjectState();


		Array<ObjectData*, uint16> _globalObjects;
		Array<ObjectData*, uint16> _roomObjects;

		uint16 getCount() const {
			return _globalObjects.size() + _roomObjects.size();
		}

		void dumpObjects() const;
		void clearAll();
		void moveRoomObjectsToGlobals();
		void clearRoomObjectsForNewRoom();

		bool loadFromFloatingObject(uint16 objectNum);
		bool loadFromRoomLoad(DiskReader& reader, const TagPair& tag);
		bool unload(uint16 objectNum);


		bool hasGlobalObject(uint16 objectNum) const;
		bool hasRoomObject(uint16 objectNum) const;

		inline bool hasObject(uint16 objectNum) {

			if (objectNum == 0) {
				return false;
			}

			if (hasRoomObject(objectNum)) {
				return true;
			}

			if (hasGlobalObject(objectNum)) {
				return true;
			}

			return false;
		}

		ObjectData* findGlobalObject(uint16 objectNum);
		ObjectData* findRoomObject(uint16 objectNum);

		ObjectData* findObject(uint16 objectNum) {

			if (objectNum == 0) {
				return NULL;
			}

			ObjectData* objectData = findRoomObject(objectNum);

			if (objectData != NULL) {
				return objectData;
			}

			objectData = findGlobalObject(objectNum);

			if (objectData != NULL) {
				return objectData;
			}

			return NULL;
		}

		void putClass(uint16 objectNum, uint32 classKind, bool isEnabled);

		byte getState(uint16 objectNum);

		void setState(uint16 objectNum, byte newState);

		uint16 findRoomObjectNumFromXY(int16 x, int16 y);

	};

	extern ObjectState* OBJECTS;
	extern Array<ObjectData*, uint8> DRAWING_OBJECTS;


}

#endif