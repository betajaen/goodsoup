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

	enum RoomObjectFlags {
		OF_None = 0,
		OF_AllowMaskOr = 1,
		OF_DrawMaskOnAll = 2,
		OF_ObjectMode = 8
	};

	enum ObjectClassFlags {
		OCF_NeverClip = 20,
		OCF_AlwaysClip = 21,
		OCF_IgnoreBoxes = 22,
		OCF_YFlip = 29,
		OCF_XFlip = 30,
		OCF_Player = 31,
		OCF_Untouchable = 32
	};

	enum ObjectContainerId {
		// Objects "being loaded" or unloaded.
		OCI_None = 0xFFFF,
		// Objects in the global objects
		OCI_Global = 0xFFFE,
		// Objects in inventory
		OCI_Inventory = 0xFFFD
	};

	struct ObjectData {
		uint16 _num;
		uint16 _containerNum;
		uint8 _parent;
		uint8 _parentState;
		uint8 _state;
		uint8 _flags;
		uint32 _class;
		uint8 _owner;
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

		void setOwner(uint8 owner);

		void setClass(uint32 objectClass);

		void setClassFlags(uint8 objectClassFlags, bool enabled);

		void setState(byte state);

		bool getClassFlags(uint32 flags);
	};

	class ObjectState {
		AllocatedPool<ObjectData, uint16> _pool;

		DiskReader _seekToObject(uint16 objectNum, TagPair& out_tag);
		ObjectData* _readIntoObject(DiskReader& reader, const TagPair& parentTag, bool& out_isNew);

		ObjectData* _acquireByNum(uint16 num, bool& out_isNew);

		bool _moveObject(ObjectData* object, uint16 targetNum);

	public:

		ObjectState();
		~ObjectState();


		Array<ObjectData*, uint16> _globalObjects;
		Array<ObjectData*, uint16> _roomObjects;
		Array<ObjectData*, uint16> _inventoryObjects;

		uint16 getCount() const {
			return _globalObjects.getSize() + _roomObjects.getSize();
		}

		void dumpObjects() const;
		void clearAll();
		void moveRoomObjectsToGlobals();
		void clearRoomObjectsForNewRoom();

		bool loadAndMoveInto(uint16 objectNum, uint16 targetContainerNum, ObjectData*& out_object, bool failIfAlreadyLoaded = false);

		bool loadFloatingObject(uint16 objectNum, ObjectData*& out_object) {


			debug(GS_THIS, "Load Floating Object %ld", objectNum);

			bool result = loadAndMoveInto(objectNum, OCI_Global, out_object);

			if (result) {
				out_object->setFloating(true);
			}

			return result;
		}

		bool loadInventoryObject(uint16 objectNum, ObjectData*& out_object) {

			bool didLoad =  loadAndMoveInto(objectNum, OCI_Inventory, out_object);

			if (didLoad == false) {
				warn(GS_THIS, "Inventory Object %ld was not loaded!", objectNum);
			}
			else {
				debug(GS_THIS, "Loaded Inventory Object %ld", objectNum);
			}

			return didLoad;
		}

		bool loadRoomObject(uint16 roomNum, DiskReader& reader, const TagPair& tag);

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
		ObjectData* findInventoryObject(uint16 objectNum);

		ObjectData* findObject(uint16 objectNum);

		byte getOwner(uint16 objectNum);

		void putClass(uint16 objectNum, uint32 classKind, bool isEnabled);

		byte getState(uint16 objectNum);

		void setState(uint16 objectNum, byte newState);

		uint16 findRoomObjectNumFromXY(int16 x, int16 y);

		uint16 findNthInventoryItem(uint16 owner, uint8 idx);

		uint8 calculateInventoryCountForOwner(uint8 owner);
	};

	extern ObjectState* OBJECTS;
	extern Array<ObjectData*, uint8> DRAWING_OBJECTS;


}

#endif