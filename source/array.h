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

#ifndef GS_ARRAY_H
#define GS_ARRAY_H

#include "types.h"
#include "memory.h"
#include "debug.h"
#include "ext.h"

namespace gs
{

	template<typename T, uint32 N, typename Index = uint16>
	class FixedArray {
		private:
			T _array[N];
		public:

			void clearAndCallCtors() {
				clearZero();
				for(Index i=0;i < N;i++) {
					T* item = &_array[i];
					new (item)(T);
				}
			}

			void callDtorsAndClear() {
				for (Index i = 0; i < N; i++) {
					T* item = &_array[i];
					item->~T();
				}
				clearZero();
			}

			T size() const {
				return N;
			}

			uint32 byteSize() const {
				return sizeof(T) * N;
			}

			void clearZero() {
				clearMemoryNonAllocated(&_array[0], byteSize());
			}

			void clearDefaultValue() {
				for(Index i=0;i < N;i++) {
					_array[i] = defaultValue<T>();
				}
			}

			inline T& operator[](Index idx) {
#if GS_CHECKED == 1
				if (idx >= N) {
					error(GS_THIS, "(FIXED, %d, %d) Out of bounds access", N, idx);
				}
#endif

				return _array[idx];
			}

			inline const T& operator[](Index idx) const {
#if GS_CHECKED == 1
				if (idx >= N) {
					error(GS_THIS, "(FIXED, %d, %d) Out of bounds access", N, idx);
				}
#endif

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
				_begin = (T*) allocateMemory(_capacity, sizeof(T), MF_Clear, GS_COMMENT_FILE_LINE);
			}
			else {
				_capacity *= 2;
				_begin = (T*) reallocateMemory(_begin, _capacity, sizeof(T));
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
			_begin = (T*) allocateMemory(capacity, sizeof(T), MF_Clear, GS_COMMENT_FILE_LINE);
			_capacity = capacity;
			_end = 0;
		}

		void release() {
			if (_begin) {
				releaseMemory(_begin);
				_begin = NULL;
				_end = 0;
				_capacity = 0;
			}
		}

		void clear() {
			_end = 0;
		}

		T* getPtr() {
			return _begin;
		}

		const T* getPtr() const {
			return _begin;
		}

		Index getSize() const {
			return _end;
		}

		Index getCapacity() const {
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
#if GS_CHECKED == 1
			if (_end == 0) {
				error(GS_THIS, "(%p, %d, %d, %d) Out of bounds erasure.", _begin, _end, _capacity);
			}
#endif
			--_end;
		}

		T popItem() {
#if GS_CHECKED == 1
			if (_end == 0) {
				error(GS_THIS, "(%p, %d, %d, %d) Out of bounds erasure.", _begin, _end, _capacity);
			}
#endif

			--_end;
			return _begin[_end];
		}

		void erase(Index index) {
#if GS_CHECKED == 1
			if (index >= _end) {
				error(GS_THIS, "(%p, %d, %d, %d) Out of bounds erasure.", _begin, _end, _capacity, index);
			}
#endif

			if (index == _end - 1) {
				--_end;
			}
			else {
				_begin[index] = _begin[_end - 1];
				--_end;
			}
		}

		inline T& operator[](Index idx) {
#if GS_CHECKED == 1
			if (idx >= _end) {
				error(GS_THIS, "(FIXED, %d, %d) Out of bounds access", _end, idx);
			}
#endif

			return _begin[idx];
		}

		inline const T& operator[](Index idx) const {
#if GS_CHECKED == 1
			if (idx >= _end) {
				error(GS_THIS, "(FIXED, %d, %d) Out of bounds access", _end, idx);
			}
#endif

			return _begin[idx];
		}

		inline T& get(Index idx) {
#if GS_CHECKED == 1
			if (idx >= _end) {
				error(GS_THIS, "(FIXED, %d, %d) Out of bounds access", _end, idx);
			}
#endif

			return _begin[idx];
		}

		inline const T& get(Index idx) const {
#if GS_CHECKED == 1
			if (idx >= _end) {
				error(GS_THIS, "(FIXED, %d, %d) Out of bounds access", _end, idx);
			}
#endif

			return _begin[idx];
		}

		inline T& get_unchecked(Index idx) {
			return _begin[idx];
		}

		inline const T& get_unchecked(Index idx) const {
			return _begin[idx];
		}

	};


	template<typename T, typename Index, Index Capacity>
	class InlineArray {
		T _items[Capacity];
		Index _end;

	public:

		inline InlineArray() 
			: _end(0) {
			clearMemoryNonAllocated(_items, sizeof(T) * Capacity);
		}

		inline ~InlineArray() {
		}

		inline void clear() {
			_end = 0;
		}

		inline T* ptr() {
			return &_items[0];
		}

		inline const T* ptr() const {
			return &_items[0];
		}

		inline Index size() const {
			return _end;
		}

		inline Index capacity() const {
			return Capacity;
		}

		inline bool isFull() const {
			return _end == Capacity;
		}

		inline bool isEmpty() const {
			return _end == 0;
		}

		inline bool hasAny() const {
			return _end != 0;
		}

		inline bool indexOf(const T& value, Index& out_index) const {
			for(Index i=0;i < _end;i++) {
				if (_items[i] == value) {
					out_index = i;
					return true;
				}
			}

			return false;
		}

		inline bool contains(const T& value) const {
			for(Index i=0;i < _end;i++) {
				if (_items[i] == value)
					return true;
			}

			return false;
		}

		inline Index count(const T& value) const {
			Index amount = 0;
			for(Index i=0;i < _end;i++) {
				if (_items[i] == value) {
					amount++;
				}
			}
			return amount;
		}
		
		inline T& get_unchecked(Index idx) {
			return _items[idx];
		}
		
		inline const T& get_unchecked(Index idx) const {
			return _items[idx];
		}

		inline T& get(Index idx) {
#if GS_CHECKED == 1
			if (idx >= _end) {
				error(GS_THIS, "(FIXED, %d, %d) Out of bounds access", _end, idx);
			}
#endif

			return _items[idx];
		}
		
		inline const T& get(Index idx) const {
#if GS_CHECKED == 1
			if (idx >= _end) {
				error(GS_THIS, "(FIXED, %d, %d) Out of bounds access", _end, idx);
			}
#endif

			return _items[idx];
		}

		inline T& operator[](Index idx) {
			return _get(idx);
		}
		
		inline const T& operator[](Index idx) const {
			return _get(idx);
		}

		inline void erase(Index index) {

			CHECK_IF(index >= _end, "Out of bounds erasure");

			if (index == _end - 1) {
				--_end;
			}
			else {
				_items[index] = _items[_end - 1];
				--_end;
			}
		}

		inline bool tryPush(const T& item) {
			if (isFull() == false) {
				_items[_end++] = item;
				return true;
			}
			else {
				return false;
			}
		}
		
		inline void push_unchecked(const T& item) {
			_items[_end++] = item;
		}

		inline void push(const T& item) {
#if GS_CHECKED == 1
			if (isFull()) {
				error(GS_THIS, "Out of bounds access");
			}
#endif
			_items[_end++] = item;
		}

		inline bool tryPop(T& item) const {
			if (hasAny()) {
				_end--;
				item = _items[_end];
				return true;
			}
			else {
				return false;
			}
		}

		inline T& pop() const {
#if GS_CHECKED == 1
			if (_end == 0) {
				error(GS_THIS, "Out of bounds access");
			}
#endif

			_end--;
			return _items[_end];
		}

		inline T& pop_unchecked() const {
			_end--;
			return _items[_end];
		}

		inline void popDiscard() {
			if (hasAny()) {
				--_end;
			}
		}

		inline void popDiscard_unchecked() {
			--_end;
		}


	};

	template<typename T, typename Index, Index PO2_Capacity>
	struct RingArray {


		T _items[PO2_Capacity];
		Index _read, _write;

		inline RingArray() 
			: _read(0), _write(0) {
			clearMemoryNonAllocated(_items, sizeof(T) * PO2_Capacity);
		}

		inline ~RingArray() {
		}

		inline Index capacity() const {
			return PO2_Capacity;
		}

		bool write(const T& value) {
			Index next = (_write + 1) & (PO2_Capacity - 1);
			if (next == _read)
				return false;

			_items[next] = value;
		}

		void overwrite(const T& value) {
			_write = (_write + 1) & (PO2_Capacity - 1);
			_items[_write] = value;
		}

		bool read(T& out_value) {
			if (_read == _write)
				return false;

			out_value = _items[_read];
			_read = (_read + 1) & (PO2_Capacity - 1);
			return true;
		}
		
		bool peek(T& out_value) {
			if (_read == _write)
				return false;

			out_value = _items[_read];
			return true;
		}

	};
	
	template<typename T>
	struct RingLog {
		T _items[256];
		uint8 _write;

		inline RingLog() 
			: _write(0) {
			clearMemoryNonAllocated(_items, sizeof(T) * 256);
		}

		void write(const T& value) {
			_items[++_write] = value;
		}

		void read(uint8 index, T& out_value) {
			uint8 offset = _write - index;
			out_value = _items[offset];
		}

	};

	template<typename T, typename Index, Index Capacity>
	class Stack {
	private:
		T    	_items[Capacity];
		Index   _head;

	public:

		Stack() {
			clearMemoryNonAllocated(&_items[0], sizeof(_items));
		}

		T* items() {
			return &_items[0];
		}

		void clear() {
			_head = 0;
		}

		uint16 getSize() const {
			return _head;
		}

		void push(const T& item) {
			if (_head == Capacity) {
				error(GS_THIS, "Stack overflow!");
				abort_quit_stop();
				return;
			}

			_items[_head] = item;
			_head++;
		}

		bool pop(T& item) {
			if (_head == 0) {
				error(GS_THIS, "Stack underflow!");
				abort_quit_stop();
				return false;
			}
			_head--;
			item = _items[_head];
			return true;
		}

		bool peek(T& item) {
			if (_head == 0) {
				return false;
			}
			item = _items[_head - 1];
			return true;
		}

	};

}


#endif
