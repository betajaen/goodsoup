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

	enum ObjectKind {
		OK_None = 0,
		OK_RoomObject = 1,
		OK_Actor = 2,
		OK_Inventory = 3
	};
	
	enum RoomObjectFlags {
		OF_None = 0,
		OF_AllowMaskOr = 1,
		OF_DrawMaskOnAll = 2,
		OF_ObjectMode = 8
	};

	enum ObjectVariantFlags {
		OVF_None = 0,
		OVF_Locked = 1,
		OVF_Floating = 2
	};

	struct ObjectData {
		uint16 _num;
		uint8 _parent;
		uint8 _parentState;
		uint8 _state;
		uint8 _flags;
		uint8 _class;
		int16 _x, _y;
		uint16 _width, _height;
		ScriptDataReference _script;

		bool isLocked() const {
			return (_flags & OVF_Locked) == 0;
		}

		void setLocked(bool isLocked) {
			if (isLocked) {
				_flags |= OVF_Locked;
			}
			else {
				_flags &= ~OVF_Locked;
			}
		}

		bool isFloating() const {
			return (_flags & OVF_Floating) == 0;
		}

		void setFloating(bool isFloating) {
			if (isFloating) {
				_flags |= OVF_Floating;
			}
			else {
				_flags &= ~OVF_Floating;
			}
		}

		void clear();
	};

	class ObjectState {
		ArrayPool<ObjectData, uint8> _objects;

		DiskReader _seekToObject(uint16 objectNum, TagPair& out_tag);
		bool _readIntoObject(ObjectData* data, DiskReader& reader, const TagPair& obcdTag);

	public:

		ObjectState();
		~ObjectState();

		uint16 getCount() const {
			return _objects.getSize();
		}
		void dumpObjects();
		void clearAll();
		void clearForNewRoom();

		ObjectData* loadFromFloatingObject(uint16 objectNum);
		ObjectData* loadFromRoomLoad(DiskReader& reader, const TagPair& obcdTag);
		bool unload(uint16 objectNum);

		bool hasObject(uint16 objectNum) const;
		ObjectData* findObject(uint16 objectNum);

	};

	extern ObjectState* OBJECTS;
	extern Array<ObjectData*, uint8> DRAWING_OBJECTS;


}

#endif