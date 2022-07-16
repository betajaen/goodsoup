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

#define GS_FILE_NAME "vm_array"

#include "vm/array.h"

#include "memory.h"
#include "vm/vars.h"

namespace gs
{
	const uint16 NO_ARRAY = 0;
	VmArrayAllocator* ARRAYS = NULL;

	VmArrayAllocator::VmArrayAllocator() 
		: _lastUsed(NULL)
	{
		for (uint8 i = 0; i < NUM_ARRAY; i++) {
			_slots[i] = NULL;
		}
	}

	VmArrayAllocator::~VmArrayAllocator() {
		reset();
	}

	void VmArrayAllocator::reset() {

		for (uint8 i = 0; i < NUM_ARRAY; i++) {
			VmArray* array = _slots[i];
			if (array) {
				INTS->set(array->_num, 0);
				releaseMemory(array);
				_slots[i] = NULL;
			}
		}

		_lastUsed = NULL;
		
	}
	
	uint8 VmArrayAllocator::_getFreeIndex() {
		for (uint8 i = 1; i < NUM_ARRAY; i++) {
			if (_slots[i] == NULL) {
				return i;
			}
		}
		return NUM_ARRAY;
	}

	VmArray* VmArrayAllocator::allocate(uint16 arrayNum, uint16 xSize, uint16 ySize, uint8 kind) {

		VmArray* array = findFromNum(arrayNum);

		if (array != NULL) {
			deallocateFromArray(array);
		}

		uint8 arrayIdx = _getFreeIndex();

#if 0
		if (arrayIdx == NUM_ARRAY) {
			error(GS_THIS, "Out of array slots!");
			return NULL;
		}
#endif

		uint32 allocSize = 4;

		if (kind != VAK_Integer) {
			allocSize = 1;
		}

		xSize++;
		ySize++;

		allocSize *= ySize;
		allocSize *= xSize;

		// sizeof ArrayHeader
		allocSize += sizeof(VmArray);

		array = (VmArray*) allocateMemory(1, allocSize, MF_Clear);
		array->_kind = kind;
		array->_xSize = xSize;
		array->_ySize = ySize;
		array->_size = ySize * xSize;
		array->_num = arrayNum;
		array->_idx = arrayIdx;

		INTS->set(arrayNum, arrayIdx);
		_slots[arrayIdx] = array;

		_lastUsed = array;
		
		return array;
	}
	
	void VmArrayAllocator::deallocateFromArray(VmArray* array) {

#if GS_CHECKED == 1
		if (array == NULL) {
			error(GS_THIS, "Tried to free a null VmArray!");
			return;
		}
#endif

		uint8 index = array->_idx;

		_slots[index] = NULL;
		INTS->set(array->_num, 0);

		if (_lastUsed == array) {
			_lastUsed = NULL;
		}

		releaseMemory(array);
	}

	VmArray* VmArrayAllocator::findFromNum(uint16 arrayNum) {

		if (_lastUsed != NULL && _lastUsed->_num == arrayNum) {
			return _lastUsed;
		}

		uint16 idx = INTS->get(arrayNum);

		if (idx > 0 && idx < NUM_ARRAY) {
			_lastUsed = _slots[idx];
			return _lastUsed;
		}

		return NULL;
	}

}
