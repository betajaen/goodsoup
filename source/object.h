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
#include "array.h"
#include "buffer.h"
#include "resource_data.h"
#include "span.h"
#include "disk.h"
#include "profile.h"
#include "debug.h"

namespace gs
{

#define MAX_OBJECTS 200

	enum ObjectFlags {
		OF_None = 0,
		OF_AllowMaskOr = 1,
		OF_DrawMaskOnAll = 2,
		OF_ObjectMode = 8,
	};

	struct ObjectData {
		uint16 _num, _idx, _roomNum;
		uint8  _bIsFloating;
		uint8  _bUsed;
		uint8  _bIsLocked;
		uint8  _parent;
		uint8  _parentState;
		uint8  _flags;

		ReadSpan<byte, uint16> _scriptData;

		void clear();
	};

	class ObjectState {

		ObjectData _objects[MAX_OBJECTS];
	public:

		ObjectState();
		~ObjectState();


		uint16 newObject(uint16 num);
		uint16 releaseObjectByIdx(uint16 idx);
		uint16 releaseObjectByNum(uint16 idx);
		uint16 findObjectIdxByNum(uint16 objectNum);
		
		void clearObjects();
		void clearRoomObjects();

		ObjectData* getObjectPtr_unchecked(uint16 idx) {
			return &_objects[idx];
		}

		ObjectData& getObjectByIdx_unchecked(uint16 idx) {
			return _objects[idx];
		}

		ObjectData& getObjectByIdx(uint16 idx) {
			if (idx > 0 && idx < MAX_OBJECTS) {
				return _objects[idx];
			}
		
			error(GS_THIS, "Object %ld out of range!", idx);
			return _objects[0];
		}
		
		const ObjectData& getObjectByIdx_unchecked(uint16 idx) const {
			return _objects[idx];
		}

		const ObjectData& getObjectByIdx(uint16 idx) const {
			if (idx > 0 && idx < MAX_OBJECTS) {
				return _objects[idx];
			}
		
			error(GS_THIS, "Object %ld out of range!", idx);
			return _objects[0];
		}

	};


	extern ObjectState* OBJECTS;
	extern Array<ObjectData*> DRAWING_OBJECTS;


}

#endif