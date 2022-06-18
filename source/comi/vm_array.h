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

#ifndef COMI_VM_ARRAY_H
#define COMI_VM_ARRAY_H

#include "common/types.h"
#include "common/array.h"
#include "common/buffer.h"
#include "common/endian.h"

#include "constants.h"
#include "debug.h"

using namespace common;

namespace comi
{
	enum VmArrayKind {
		VAK_None = 0,
		VAK_String = 1,
		VAK_Integer = 4
	};

	class VmArrayAllocator;

	extern VmArrayAllocator* ARRAYS;

	struct VmArray {
		uint16 _num;
		uint16 _dim1, _dim2;
		uint8  _idx;
		uint8  _kind;
		uint8  _data[4];

		inline void write(int32 value, uint32 idx, uint32 base) {
			int32 offset = base + idx * (uint32)_kind;

			if (offset < 0 || offset > _dim1) {
				error(COMI_THIS, "Out of bounds array write (%ld, %ld, %ld, %ld)", _num, value, idx, base);
				return;
			}

			if (_kind == VAK_Integer) {
				writeInt32(offset, value);
			}
			else {
				writeByte(offset, (byte) value);
			}
		}

		inline void writeByte(uint32 offset, byte data) {
			_data[offset] = data;
		}

		inline void writeUInt16(uint32 offset, uint16 data) {
			WRITE_LE_UINT16(&_data[offset], data);
		}

		inline void writeUInt32(uint32 offset, uint32 data) {
			WRITE_LE_UINT32(&_data[offset], data);
		}
		
		inline void writeInt16(uint32 offset, int16 data) {
			WRITE_LE_INT16(&_data[offset], data);
		}

		inline void writeInt32(uint32 offset, int32 data) {
			WRITE_LE_INT32(&_data[offset], data);
		}

		inline void writeBytes(const byte* data, uint32 offset, uint32 length) {
			while (length--) {
				_data[offset++] = *data++;
			}
		}

		inline byte readByte(uint32 offset) {
			return _data[offset];
		}

		inline uint16 readUInt16(uint32 offset) {
			return READ_LE_UINT16(&_data[offset]);
		}
		
		inline uint32 readUInt32(uint32 offset) {
			return READ_LE_UINT32(&_data[offset]);
		}

		inline int16 readInt16(uint32 offset) {
			return READ_LE_UINT16(&_data[offset]);
		}
		
		inline int32 readInt32(uint32 offset) {
			return READ_LE_UINT32(&_data[offset]);
		}

	};

	class VmArrayAllocator {
	private:
		VmArray*          _slots[NUM_ARRAY];
		uint16            _nums[NUM_ARRAY];
		Array<byte, byte> _free;
		VmArray*          _lastUsed;

		uint8 _getFreeIndex();

	public:
		VmArrayAllocator();
		~VmArrayAllocator();

		void reset();

		VmArray* allocate(uint16 arrayNum, uint16 dim1, uint16 dim2, uint8 kind);
		void deallocateFromNum(uint16 arrayNum) {
			deallocateFromArray(findFromNum(arrayNum));
		}
		void deallocateFromArray(VmArray* array);

		VmArray* getFromIndex(uint8 index);
		VmArray* findFromNum(uint16 arrayNum);
	};

}

#endif
