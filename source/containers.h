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

#ifndef GS_CONTAINERS_H
#define GS_CONTAINERS_H

#include "forward.h"
#include "debug.h"
#include "memory.h"
#include "ext.h"
#include "endian.h"

namespace gs {

	template<typename T, typename Index>
	struct Buffer
	{
	private:
		T* _data;
		Index _size;
	public:

		Buffer() {
			_size = 0;
			_data = NULL;
		}

		~Buffer() {
			release();
		}

		template<typename SpanIndex>
		ReadSpan<T, SpanIndex> getReadSpan() const {
			return ReadSpan<T, SpanIndex>(&_data[0], _size);
		}

		template<typename SpanIndex>
		ReadSpan<T, SpanIndex> getReadSpan(Index from, SpanIndex size) const {

			if (size == 0) {
				size = _size;
			}

			Index srcEnd = from + size;

			if (from > _size) {
				error(GS_THIS, "Offset from %ld does not fit into _size %ld", from, _size);
				return ReadSpan<T, SpanIndex>(NULL, 0);
			}

			if (srcEnd > _size) {
				error(GS_THIS, "Offset size %ld does not fit into _size %ld", srcEnd, _size);
				return ReadSpan<T, SpanIndex>(NULL, 0);
			}

			return ReadSpan<T, SpanIndex>(&_data[from],  size);
		}

		template<typename SpanIndex>
		ReadWriteSpan<T, SpanIndex> getReadWriteSpan() const {
			return ReadWriteSpan<T, SpanIndex>(&_data[0], _size);
		}

		template<typename SpanIndex>
		ReadWriteSpan<T, SpanIndex> getReadWriteSpan(Index from, SpanIndex size) const {

			if (size == 0) {
				size = _size;
			}

			Index srcEnd = from + size;

			if (from > _size) {
				error(GS_THIS, "Offset from %ld does not fit into _size %ld", from, _size);
				return ReadWriteSpan<T, SpanIndex>(NULL, 0);
			}

			if (srcEnd > _size) {
				error(GS_THIS, "Offset size %ld does not fit into _size %ld", srcEnd, _size);
				return ReadWriteSpan<T, SpanIndex>(NULL, 0);
			}

			return ReadWriteSpan<T, SpanIndex>(&_data[from],  size);
		}

		void setSize(Index size, int flags = MF_Clear) {
			if (_size && _data) {
				releaseMemory(_data);;
			}
			_data = (T*)allocateMemory(size, sizeof(T), flags, GS_COMMENT_FILE_LINE);
			_size = size;
		}

		void release() {
			if (_size && _data) {
				releaseMemory(_data);
				_size = 0;
				_data = NULL;
			}
		}

		void zeroMem() {
			if (_size && _data) {
				clearMemory(_data, _size * sizeof(T));
			}
		}

		bool hasMem() const {
			return (_size && _data);
		}

		void callCtors() {
			if (_size && _data) {
				for (Index i = 0; i < _size; i++) {
					T* obj = ptr(i);
					new (obj)T();
				}
			}
		}

		void callDtors() {
			if (_size && _data) {
				for (Index i = 0; i < _size; i++) {
					_data[i].~T();
				}
			}
		}

		Index getSize() const {
			return _size;
		}

		void set(Index idx, const T& newValue) {
			if (idx >= _size)
				error(GS_THIS, "array(Out of bounds, replace, %d)", idx);

			_data[idx] = newValue;
		}

		void set_unchecked(Index idx, const T& newValue) {
			_data[idx] = newValue;
		}

		T* ptr(Index idx) {

			if (idx >= _size)
				error(GS_THIS, "array(Out of bounds, ptr, %d)", idx);

			return &_data[idx];
		}

		const T* ptr(Index idx) const {

			if (idx >= _size)
				error(GS_THIS, "array(Out of bounds, const ptr, %d)", idx);

			return &_data[idx];
		}


		T& get(Index idx) {
			if (idx >= _size)
				error(GS_THIS, "array(Out of bounds, mut, %d)", idx);

			return _data[idx];
		}

		const T& get(Index idx) const {
			if (idx >= _size)
				error(GS_THIS, "array(Out of bounds, const, %d)", idx);

			return _data[idx];
		}

		T& get_unchecked(Index idx) {
			return _data[idx];
		}

		const T& get_unchecked(Index idx) const {
			return _data[idx];
		}
	};

	template<typename T, uint32 N, typename Index>
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


	template<typename T, typename Index>
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

	template<typename T>
	class Queue
	{
	private:
		T* head, *tail;
	public:

		Queue() {
			head = NULL;
			tail = NULL;
		}

		~Queue() {
			head = NULL;
			tail = NULL;
		}

		void clear() {
			head = NULL;
			tail = NULL;
		}

		bool isEmpty() const {
			return head == NULL;
		}

		bool hasAny() const {
			return head != NULL;
		}

		bool hasOne() const {
			return head == tail && head != NULL;
		}

		uint16 count() const {
			uint16 count = 0;
			T* h = head;
			while(h) {
				count++;
				h = h->next;
			}
			return count;
		}

		T* peekFront() {
			return head;
		}

		T* pullFront() {
			T* h = head;

			if (h != NULL) {
				head = h->next;
				h->next = NULL;

				if (head == NULL) {
					tail = NULL;
				}

			}

			return h;
		}

		T* pullBack() {
			T* t = tail;

			if (t != NULL) {
				T* n = head;
				while(n != NULL) {

					if (n->next == t) {
						tail = n;
						tail->next = NULL;
						break;
					}

					n = n->next;
				}
			}

			return t;
		}

		void pushBack(T* newTail) {
			if (tail == NULL) {
				head = tail = newTail;
			}
			else {
				tail->next = newTail;
				tail = newTail;
			}
		}

		void pushFront(T* newHead) {
			if (head == NULL) {
				head = tail = newHead;
			}
			else {
				newHead->next = head;
				head = newHead;
			}
		}

		void pull(T* item) {

			if (item == head) {
				pullFront();
			}
			else {
				T* n = head;
				while(n != NULL) {
					if (n->next == item) {
						n->next = item->next;
						break;
					}
					n = n->next;
				}
			}
		}

	};

	template<typename T>
	class List {

		T* head, *tail;

	public:

		List() {
			head = NULL;
			tail = NULL;
		}

		T* peekFront() {
			return head;
		}

		T* pullFront() {
			T* h = head;

			if (h != NULL) {
				head = h->next;
				h->next = NULL;

				if (head == NULL) {
					tail = NULL;
				}
				else {
					head->prev = NULL;
				}
			}

			return h;
		}

		T* peekBack() {
			return tail;
		}

		T* pullBack() {
			T* t = tail;

			if (t != NULL) {
				tail = t->prev;

				if (tail != NULL) {
					tail->next = NULL;
				}
			}

			return t;
		}


		void pushFront(T* newHead) {
			if (head == NULL) {
				head = tail = newHead;
			}
			else {
				head->prev = newHead;
				newHead->next = head;
				head = newHead;
			}
		}

		void pushBack(T* newTail) {
			if (tail == NULL) {
				head = tail = newTail;
			}
			else {
				newTail->prev = tail;
				tail->next = newTail;
				tail = newTail;
			}
		}

		void pull(T* item) {

			if (item == head) {
				pullFront();
			}
			else if (item == tail) {
				pullBack();
			}
			else {
				T* before = item->prev;
				T* after = item->next;
				before->next = after;
				after->prev = before;
			}
		}

	};



	template<typename T, typename Index>
	struct ArrayPool {
	private:
		Array<T*, Index> _items;
		Array<T*, Index> _pool;
	public:

		ArrayPool() {
		}

		~ArrayPool() {
			clear();
		}

		void clear() {
			for (Index i = 0; i < _items.getSize(); i++) {
				T* item = _items.get_unchecked(i);
				deleteObject_unchecked(item);
			}
			_items.release();
			for (Index i = 0; i < _pool.getSize(); i++) {
				T* item = _pool.get_unchecked(i);
				deleteObject_unchecked(item);
			}
			_pool.release();
		}

		T* acquire(uint32 comment = 0) {
			if (_pool.getSize()) {
				T* item = _pool.popItem();
				_items.push(item);
				return item;
			}

			T* item = newObject<T>(comment);
			_items.push(item);
			return item;
		}

		bool release(T* item) {
			for (uint16 i = 0; i < _items.getSize(); i++) {
				T* test = _items.get_unchecked(i);
				if (test == item) {
					_items.erase(i);
					_pool.push(item);
					return true;
				}
			}

			return false;
		}

		void release_unchecked(T* item) {
			for (uint16 i = 0; i < _items.getSize(); i++) {
				T* test = _items.get_unchecked(i);
				if (test == item) {
					_items.erase(i);
					_pool.push(item);
					return;
				}
			}
		}

		uint16 getSize() const {
			return _items.getSize();
		}

		T* get(Index idx) {
			return _items.get(idx);
		}

		T* get_unchecked(Index idx) {
			return _items.get_unchecked(idx);
		}

		const T* get_unchecked(Index idx) const {
			return _items.get_unchecked(idx);
		}

		const T* get(Index idx) const {
			return _items.get(idx);
		}

	};

	template<typename T, typename Index>
	class AllocatedPool {
		Array<T*, Index> _free;
	public:

		AllocatedPool() {
		}

		~AllocatedPool() {
			clear();
		}

		void clear() {
			for(Index i=0;i < _free.getSize(); i++) {
				deleteObject_unchecked(_free.get_unchecked(i));
			}
			_free.clear();
		}

		T* acquire(uint32 comment = 0) {
			if (_free.getSize()) {
				T* item = _free.popItem();
				return item;
			}


			void* mem = allocateMemory(1, sizeof(T), MF_Clear, comment);
			return new(mem) T();
		}

		void release(T* item) {
			for (uint16 i = 0; i < _free.getSize(); i++) {
				T* test = _free.get_unchecked(i);
				if (test == item) {
					return;
				}
			}

			_free.push(item);
		}

		void release_unchecked(T* item) {
			_free.push(item);
		}

	};

	template<typename T>
	class LinkedListPool {
		T *head;
	public:

		LinkedListPool() {
			head = NULL;
		}

		~LinkedListPool() {
			clear();
		}

		void clear() {

			while(head != NULL) {
				T* nextHead = head->next;
				deleteObject_unchecked(head);
				head = nextHead;
			}
		}

		T* acquire(uint32 comment = 0) {
			if (head) {
				T* item = head;
				head = item->next;
				item->next = NULL;
				return item;
			}

			void* mem = allocateMemory(1, sizeof(T), MF_Clear, comment);
			return new(mem) T();
		}

		void release(T* item) {
			if (item != NULL) {
				item->next = head;
				head = item;
			}
		}

		void release_unchecked(T* item) {
			item->next = head;
			head = item;
		}

	};



	template<typename T, typename Index>
	struct ReadSpan {
	private:
		const T* _data;
		Index _size;
	public:

		ReadSpan()
				: _data(NULL), _size(0) {
		}

		ReadSpan(const T* data, Index size)
				: _data(data), _size(size)
		{
		}

		ReadSpan(const ReadSpan<byte, Index>& other)
				: _data(other._data), _size(other._size)
		{
		}

		ReadSpan& operator=(const ReadSpan<byte, Index>& other) {
			_data = other._data;
			_size = other._size;
			return *this;
		}

		bool isNull() const {
			return (_size && _data) == false;
		}

		Index getSize() const {
			return _size;
		}

		const T* ptr(Index idx) const {

			if (idx >= _size)
				error(GS_THIS, "ReadSpan(Out of bounds, const ptr, %d)", idx);

			return &_data[idx];
		}

		const T* ptr_unchecked(Index idx) const {
			return &_data[idx];
		}

		const T& get(Index idx) const {
			if (idx >= _size)
				error(GS_THIS, "ReadSpan(Out of bounds, const, %d)", idx);

			return _data[idx];
		}

		const T& get_unchecked(Index idx) const {
			return _data[idx];
		}

	};

	template<typename T, typename Index>
	struct SequentialReadSpanReader {
	private:
		ReadSpan<T, Index> _span;
		Index _pos;
	public:

		SequentialReadSpanReader(const ReadSpan<T, Index>& span)
				: _span(span), _pos(0) {
		}

		void skip_unchecked(Index amount) {
			_pos += amount;
		}

		void setPos_unchecked(Index index) {
			_pos = index;
		}

		Index getPos() const {
			return _pos;
		}

		byte peek() const {
			return _span.get_unchecked(_pos);
		}

		int8 readInt8_unchecked() {
			int8 value = (int8) _span.get_unchecked(_pos);
			_pos++;
			return value;
		}

		uint8 readUint8_unchecked() {
			uint8 value = _span.get_unchecked(_pos);
			_pos++;
			return value;
		}

		uint16 readUint16LE_unchecked() {
			uint16 value = READ_LE_UINT16(_span.ptr(_pos));
			_pos += 2;
			return value;
		}

		uint16 readUint16BE_unchecked() {
			uint16 value = READ_BE_UINT16(_span.ptr(_pos));
			_pos += 2;
			return value;
		}

		int16 readInt16LE_unchecked() {
			int16 value = READ_LE_INT16(_span.ptr(_pos));
			_pos += 2;
			return value;
		}

		int16 readInt16BE_unchecked() {
			int16 value = READ_BE_INT16(_span.ptr(_pos));
			_pos += 2;
			return value;
		}

		uint32 readUint32LE_unchecked() {
			uint32 value = READ_LE_UINT32(_span.ptr(_pos));
			_pos += 4;
			return value;
		}

		uint32 readUint32BE_unchecked() {
			uint32 value = READ_BE_UINT32(_span.ptr(_pos));
			_pos += 4;
			return value;
		}

		int32 readInt32LE_unchecked() {
			int32 value = READ_LE_INT32(_span.ptr(_pos));
			_pos += 4;
			return value;
		}

		int32 readInt32BE_unchecked() {
			int32 value = READ_BE_INT32(_span.ptr(_pos));
			_pos += 4;
			return value;
		}
	};

	template<typename T, typename Index>
	struct ReadWriteSpan {
	private:
		T* _data;
		Index _size;
	public:

		ReadWriteSpan()
				: _data(NULL), _size(0) {
		}

		ReadWriteSpan(T* data, Index size)
				: _data(data), _size(size)
		{
		}

		ReadWriteSpan(const ReadWriteSpan<byte, Index>& other)
				: _data(other._data), _size(other._size)
		{
		}

		ReadWriteSpan& operator=(const ReadWriteSpan<byte, Index>& other) {
			_data = other._data;
			_size = other._size;
			return *this;
		}

		bool isNull() const {
			return (_size && _data) == false;
		}

		Index getSize() const {
			return _size;
		}

		T* ptr(Index idx) {

			if (idx >= _size)
				error(GS_THIS, "ReadWriteSpan(Out of bounds, const ptr, %d)", idx);

			return &_data[idx];
		}

		T& get(Index idx) {
			if (idx >= _size)
				error(GS_THIS, "ReadWriteSpan(Out of bounds, const, %d)", idx);

			return _data[idx];
		}

		T& get_unchecked(Index idx) {
			return _data[idx];
		}

		const T* ptr(Index idx) const {

			if (idx >= _size)
				error(GS_THIS, "ReadWriteSpan(Out of bounds, const ptr, %d)", idx);

			return &_data[idx];
		}

		const T& get(Index idx) const {
			if (idx >= _size)
				error(GS_THIS, "ReadSpan(Out of bounds, const, %d)", idx);

			return _data[idx];
		}

		const T& get_unchecked(Index idx) const {
			return _data[idx];
		}

	};

}

#endif