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

#ifndef COMMON_ARRAY_H
#define COMMON_ARRAY_H

#include "common/types.h"
#include "common/memory.h"
#include "common/debug.h"
#include "common/ext.h"

namespace common
{

	template<typename T, uint32 N, typename Index = uint16>
	class FixedArray {
		private:
			T _array[N];
		public:

			T size() const {
				return N;
			}

			uint32 byteSize() const {
				return sizeof(T) * N;
			}

			void clearZero() {
				clearMemoryNonAllocated(_array[0], byteSize);
			}

			void clearDefaultValue() {
				for(Index i=0;i < N;i++) {
					_array[i] = defaultValue<T>();
				}
			}

			inline T& operator[](Index idx) {
				if (idx >= N) {
					error(GS_THIS, "(FIXED, %d, %d) Out of bounds access", N, idx);
				}

				return _array[idx];
			}

			inline const T& operator[](Index idx) const {
				if (idx >= N) {
					error(GS_THIS, "(FIXED, %d, %d) Out of bounds access", N, idx);
				}

				return _array[idx];
			}
	};


	template<typename T, typename Index = uint16>
	class Array {
	private:

		T* _begin;
		Index _size, _capacity;

		void grow() {
			if (_capacity == 0) {
				_capacity = 8;
				_begin = (T*) ::common::allocateMemory(_capacity, sizeof(T), MEMF_CLEAR);
			}
			else {
				_capacity *= 2;
				_begin = (T*) ::common::reallocateMemory(_begin, _capacity, sizeof(T));
			}
		}
		void release() {
			if (_begin) {
				::common::releaseMemory(_begin);
				_begin = NULL;
				_size = 0;
				_capacity = 0;
			}
		}

	public:

		Array() :
			_begin(NULL), _size(0), _capacity(0) {
		}

		~Array() {
			release();
		}


		Index size() const {
			return _size;
		}

		Index capacity() const {
			return _capacity;
		}

		void push(const T& value) {
			if (_size == _capacity) {
				grow();
			}

			_begin[_size] = value;
			++_size;
		}

		void pop() {
			if (_size == 0) {
				error(GS_THIS, "(%p, %d, %d, %d) Out of bounds erasure.", _begin, _size, _capacity);
			}

			--_size;
		}

		void erase(Index index) {
			if (index >= _size) {
				error(GS_THIS, "(%p, %d, %d, %d) Out of bounds erasure.", _begin, _size, _capacity, index);
			}

			if (index == _size - 1) {
				--_size;
			}
			else {
				_begin[index] = _begin[_size - 1];
				--_size;
			}
		}

	};

}


#endif
