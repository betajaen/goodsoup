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

#ifndef GS_KEYARRAY_H
#define GS_KEYARRAY_H

#include "types.h"
#include "memory.h"
#include "debug.h"
#include "hash.h"

namespace gs
{

	template<typename K, typename V>
	class KeyArray {
	private:

		struct Node
		{
			uint32 _hash;
			V      _value;

			Node(uint32 hash, const V& value) :
			_hash(hash), _value(value) {
			}
		};

		Node* _begin;
		uint32 _size, _capacity;
		HashFunction<K>     _hashFunction;

		void grow() {
			verbose(GS_THIS, "/1(%p,%d,%d)", _begin, _size, _capacity);
			if (_capacity == 0) {
				_capacity = 8;
				_begin = (Node*) allocateMemory(_capacity, sizeof(Node), MF_Clear, GS_COMMENT_FILE_LINE);
			}
			else {
				_capacity *= 2;
				_begin = (Node*) reallocateMemory(_begin, _capacity, sizeof(Node));
			}
			verbose(GS_THIS, "/2(%p,%d,%d)", _begin, _size, _capacity);
		}
		void release() {
			if (_begin) {
				releaseMemory(_begin);
				_begin = NULL;
				_size = 0;
				_capacity = 0;
			}
		}

		void push(uint32 hash, const V& value) {
			if (_size == _capacity) {
				grow();
			}

			_begin[_size] =  Node(hash, value);
			++_size;
		}

		void erase(uint32 index) {
			if (index >= _size) {
				error(GS_THIS, "(%p, %d, %d, %d) Out of bounds erasure.", _begin, _size, _capacity, index);
			}

			if (index == _size - 1) {
				_begin[index].~Node();
				--_size;
			}
			else {
				_begin[index].~Node();
				_begin[index] = _begin[_size - 1];
				_begin[_size - 1].~Node();
				--_size;
			}
		}

		uint32 indexOf(uint32 hash) {
			for (uint32 i = 0; i < _size; i++) {
				Node& node = _begin[i];
				if (node._hash == hash) {
					return i;
				}
			}
			return _size;
		}

	public:

		KeyArray() :
			_begin(NULL), _size(0), _capacity(0) {
		}

		~KeyArray() {
			release();
		}


		uint32 size() const {
			return _size;
		}

		uint32 capacity() const {
			return _capacity;
		}

		uint32 hashFor(const K& key) {
			return _hashFunction.hash(key);
		}

		bool exists(const K& key) {
			uint32 hash = hashFor(key);
			for (uint32 i = 0; i < _size; i++) {
				Node& node = _begin[i];
				if (node._hash == hash) {
					return true;
				}
			}
			return false;
		}

		bool existsWithHash(uint32 hash) {
			for (uint32 i = 0; i < _size; i++) {
				Node& node = _begin[i];
				if (node._hash == hash) {
					return true;
				}
			}
			return false;
		}

		void add(const K& key, const V& value) {
			uint32 hash = hashFor(key);
			push(hash, value);
		}

		void addOnce(const K& key, const V& value) {
			uint32 hash = hashFor(key);
			if (existsWithHash(hash) == false) {
				push(hash, value);
			}
		}

		void addWithHash(uint32 hash, const V& value) {
			push(hash, value);
		}

		void addOnceWithHash(uint32 hash, const V& value) {
			if (existsWithHash(hash) == false) {
				push(hash, value);
			}
		}

		void remove(const K& key) {
			uint32 hash = hashFor(key);
			uint32 index = indexOf(hash);
			if (index < _size) {
				erase(index);
			}
		}

		void removeWithHash(uint32 hash) {
			uint32 index = indexOf(hash);
			if (index < size) {
				erase(index);
			}
		}

		V& get(const K& key) {
			uint32 hash = hashFor(key);
			uint32 index = indexOf(hash);
			return _begin[index]._value;
		}

		const V& get(const K& key) const {
			uint32 hash = hashFor(key);
			uint32 index = indexOf(hash);
			return _begin[index]._value;
		}

		V& getWithHash(uint32 hash) {
			uint32 index = indexOf(hash);
			return _begin[index]._value;
		}

		const V& getWithHash(uint32 hash) const {
			uint32 index = indexOf(hash);
			return _begin[index]._value;
		}

	};

}


#endif
