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
		Index _end, _capacity;

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

	public:

		Array() :
			_begin(NULL), _end(0), _capacity(0) {
		}

		~Array() {
			release();
		}

		void reserve(Index capacity) {
			release();
			_begin = (T*) ::common::allocateMemory(capacity, sizeof(T), MEMF_CLEAR);
			_capacity = capacity;
			_end = 0;
		}

		void release() {
			if (_begin) {
				::common::releaseMemory(_begin);
				_begin = NULL;
				_end = 0;
				_capacity = 0;
			}
		}

		void clear() {
			_end = 0;
		}

		T* ptr() {
			return _begin;
		}

		const T* ptr() const {
			return _begin;
		}

		Index size() const {
			return _end;
		}

		Index capacity() const {
			return _capacity;
		}

		void push(const T& value) {
			if (_end == _capacity) {
				grow();
			}

			_begin[_end] = value;
			++_end;
		}

		void pop() {
			if (_end == 0) {
				error(GS_THIS, "(%p, %d, %d, %d) Out of bounds erasure.", _begin, _end, _capacity);
			}

			--_end;
		}

		T popItem() {
			if (_end == 0) {
				error(GS_THIS, "(%p, %d, %d, %d) Out of bounds erasure.", _begin, _end, _capacity);
			}

			--_end;
			return _begin[_end];
		}

		void erase(Index index) {
			if (index >= _end) {
				error(GS_THIS, "(%p, %d, %d, %d) Out of bounds erasure.", _begin, _end, _capacity, index);
			}

			if (index == _end - 1) {
				--_end;
			}
			else {
				_begin[index] = _begin[_end - 1];
				--_end;
			}
		}

		inline T& operator[](Index idx) {
			if (idx >= _end) {
				error(GS_THIS, "(FIXED, %d, %d) Out of bounds access", _end, idx);
			}

			return _begin[idx];
		}

		inline const T& operator[](Index idx) const {
			if (idx >= _end) {
				error(GS_THIS, "(FIXED, %d, %d) Out of bounds access", _end, idx);
			}

			return _begin[idx];
		}

		inline T& get(Index idx) {
			if (idx >= _end) {
				error(GS_THIS, "(FIXED, %d, %d) Out of bounds access", _end, idx);
			}

			return _begin[idx];
		}

		inline const T& get(Index idx) const {
			if (idx >= _end) {
				error(GS_THIS, "(FIXED, %d, %d) Out of bounds access", _end, idx);
			}

			return _begin[idx];
		}

		inline T& get_unchecked(Index idx) {
			return _begin[idx];
		}

		inline const T& get_unchecked(Index idx) const {
			return _begin[idx];
		}

	};

}


#endif
