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

#ifndef GS_VM_STACK_H
#define GS_VM_STACK_H

#include "../types.h"
#include "../debug.h"

#define DEBUG_STACK 0

namespace gs
{

	template<uint16 Capacity, uint16 CapacityOfTempItems = Capacity / 2>
	class VmStack {
	private:
		int32    _items[Capacity];
		uint16   _size;
		int32    _tempItems[CapacityOfTempItems];

		int32 _pop_unchecked() {
			_size--;
			return _items[_size];
		}

	public:

		VmStack() {
			clearMemoryNonAllocated(&_items[0], sizeof(_items));
			clearMemoryNonAllocated(&_tempItems[0], sizeof(_tempItems));
		}

        int32* items() {
            return &_items[0];
        }

		void reset() {
			_size = 0;
		}

		uint16 getSize() const {
			return _size;
		}

		int32& get_unchecked(uint16 index) {
			return _items[index];
		}

		void push(int32 item) {
			if (_size == Capacity) {
				error(GS_THIS, "VM stack overflow!");
				abort_quit_stop();
				return;
			}

#if DEBUG_STACK == 1
			debug(GS_THIS, "STACK PUSH %ld %ld", _size, item);
#endif

			_items[_size] = item;
			_size++;
		}
		
		int32 pop() {
			if (_size == 0) {
				error(GS_THIS, "VM tried to pop on an empty stack!");
				abort_quit_stop();
				return 0;
			}
#if DEBUG_STACK == 1
			debug(GS_THIS, "STACK POP %ld %ld", _size - 1, _items[_size]);
#endif
			_size--;
			return _items[_size];
		}

		uint16 readList(uint16 capacity) {

			uint16 i, size, sizePopped;

			for (i = 0; i < capacity; i++) {
				_tempItems[i] = 0;
			}

			size = pop();

			if (size > capacity || size > CapacityOfTempItems) {
				error(GS_THIS, "Amount (%ld) of pop from stack is higher than capacity (%ld)", (uint32) size, (uint32) capacity);
				abort_quit_stop();
				return 0;
			}

			i = size;
			sizePopped = 0;
			while(i-- != 0) {
				
				if (_size == 0)
					break;

				_tempItems[i] = _pop_unchecked();
				sizePopped++;
			}

			if (size != sizePopped) {
				error(GS_THIS, "Stack num %ld is not the same as amount popped %ld", (uint32) size, (uint32) sizePopped);
				abort_quit_stop();
				return 0;
			}

			verbose(GS_THIS, "%ld of %ld", (uint32) size, (uint32) capacity);

			return size;
		}


		inline int32& getListItem(uint16 index) {

			if (index >= CapacityOfTempItems) {
				error(GS_THIS, "Out of bounds read (%ld)", (uint32) index, (uint32) CapacityOfTempItems);
				abort_quit_stop();
				return _tempItems[0];
			}

			return _tempItems[index];
		}

		inline int32* getList() {
			return &_tempItems[0];
		}


	};

}

#endif
