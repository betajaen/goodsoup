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

namespace gs
{
	struct ActorObjectData;
	struct FLObjectData;
	struct InventoryObjectData;
	
	struct RoomObjectData;

	enum ObjectKind {
		OK_None = 0,
		OK_RoomObject = 1,
		OK_FLObject = 2,
		OK_Actor = 3,
		OK_Inventory = 4,
	};
	
	enum RoomObjectFlags {
		OF_None = 0,
		OF_AllowMaskOr = 1,
		OF_DrawMaskOnAll = 2,
		OF_ObjectMode = 8,
	};

	enum ObjectVariantFlags {
		OVF_None = 0,
		OVF_Locked = 1
	};

	struct ObjectVariant {
		
		union ObjectVariantData {
			RoomObjectData* _room;
			ActorObjectData* _actor;
			FLObjectData* _fl;
			InventoryObjectData* _inventory;
		};

		uint16 _num;
		uint8  _kind;
		uint8  _flags;
		ObjectVariantData _data;

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

		void release();
	};

	class ObjectState {

		ArrayPool<ObjectVariant, uint16> _objects;

	public:
		
		ArrayPool<RoomObjectData, uint16> _roomObjectDatas;

		ObjectState();
		~ObjectState();

		void release();


		ObjectVariant* newObject(uint16 num, uint8 kind);

		void releaseObject(ObjectVariant* variant);

		void releaseObjectByNum(uint16 objectNum);

		bool findObjectIdxByNum(uint16 objectNum, uint16& out_Idx) const {
			for(uint16 i=0; i < _objects.getSize();i++) {
				const ObjectVariant* object = _objects.get_unchecked(i);
				if (object->_num == objectNum) {
					out_Idx = i;
					return true;
				}
			}
			return false;
		}
		
		ObjectVariant* findObjectByNum(uint16 objectNum) {

			if (objectNum == 0)
				return NULL;

			for(uint16 i=0; i < _objects.getSize();i++) {
				ObjectVariant* object = _objects.get_unchecked(i);
				if (object->_num == objectNum) {
					return object;
				}
			}
			return NULL;
		}

		const ObjectVariant* findObjectByNum(uint16 objectNum) const {
			for(uint16 i=0; i < _objects.getSize();i++) {
				const ObjectVariant* object = _objects.get_unchecked(i);
				if (object->_num == objectNum) {
					return object;
				}
			}
			return NULL;
		}
		
		void clearObjects();
		void clearRoomObjects();

		ObjectVariant* getObjectByIdx_unchecked(uint16 idx) {
			return _objects.get_unchecked(idx);
		}
		
		ObjectVariant* getObjectByIdx(uint16 idx) {
			return _objects.get(idx);
		}

		inline uint16 getCount() const {
			return _objects.getSize();
		}
		
	};


	extern ObjectState* OBJECTS;
	extern Array<ObjectVariant*> DRAWING_OBJECTS;


}

#endif