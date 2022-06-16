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

#include "vm_array.h"

#include "common/memory.h"

using namespace common;

namespace comi
{
	const uint16 NO_ARRAY = 0;

	VmArrayAllocator::VmArrayAllocator() {
		for (uint8 i = 0; i < NUM_ARRAY; i++) {
			_slots[i] = NULL;
		}
	}

	VmArrayAllocator::~VmArrayAllocator() {
		for (uint8 i = 0; i < NUM_ARRAY; i++) {
			VmArray* array = _slots[i];
			if (array) {
				releaseMemory(array);
				_slots[i] = NULL;
			}
		}
	}
	

	void VmArrayAllocator::reset() {
		
		if (_free.capacity() != NUM_ARRAY) {
			_free.reserve(NUM_ARRAY);
		}
		else {
			_free.clear();
		}
		
		uint8 num = NUM_ARRAY-1;
		for (uint8 i = 0; i < NUM_ARRAY; i++) {
			_free.push(num--);
		}

		for (uint8 i = 0; i < NUM_ARRAY; i++) {
			VmArray* array = _slots[i];
			if (array) {
				releaseMemory(array);
				_slots[i] = NULL;
			}
		}

		for (uint8 i = 0; i < NUM_ARRAY; i++) {
			_nums[i] = NO_ARRAY;
		}
		
	}
	
	uint8 VmArrayAllocator::_getFreeIndex() {
		if (_free.size()) {
			return _free.popItem();
		}
		return NUM_ARRAY;
	}

	VmArray* VmArrayAllocator::allocate(uint16 arrayNum, uint16 dim1, uint16 dim2, uint8 kind) {

		uint8 arrayIdx = _getFreeIndex();

		if (arrayIdx == NUM_ARRAY) {
			error(COMI_THIS, "Out of array slots!");
			return NULL;
		}

		uint32 allocSize = 4;

		VmArray* array = findFromNum(arrayNum);
		if (array != NULL) {
			deallocateFromArray(array);
		}

		if (kind != VAK_Integer) {
			allocSize = 1;
		}

		allocSize *= dim2 + 1;
		allocSize *= dim1 + 1;

		// sizeof ArrayHeader
		allocSize += sizeof(VmArray);

		array = (VmArray*) allocateMemory(1, allocSize, MEMF_CLEAR);
		array->_kind = kind;
		array->_dim1 = dim1 + 1;
		array->_dim2 = dim2 + 1;
		array->_num = arrayNum;
		array->_idx = arrayIdx;

		_nums[arrayIdx] = arrayNum;
		
		return array;
	}
	
	void VmArrayAllocator::deallocateFromArray(VmArray* array) {
		
		if (array == NULL) {
			error(COMI_THIS, "Tried to free a null VmArray!");
			return;
		}

		uint8 index = array->_idx;

		_slots[index] = NULL;
		_free.push(index);
		_nums[index] = NO_ARRAY;

		releaseMemory(array);
	}

	VmArray*  VmArrayAllocator::getFromIndex(uint8 index) {
		if (index >= NUM_ARRAY) {
			error(COMI_THIS, "VmArray index %ld out of bounds!", (uint32) index);
			return NULL;
		}

		return _slots[index];
	}

	VmArray* VmArrayAllocator::findFromNum(uint16 num) {

		for (uint8 i = 0; i < NUM_ARRAY; i++) {
			if (_nums[i] == num) {
				return _slots[i];
			}
		}
		return NULL;
	}
	
}
