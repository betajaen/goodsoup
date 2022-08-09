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

#ifndef GS_POOL_H
#define GS_POOL_H

#include "types.h"
#include "array.h"
#include "memory.h"

namespace gs
{
	template<typename T, typename Index = uint16>
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

	template<typename T, typename Index = uint16>
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

}

#endif