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

 // The hash map (associative array) implementation in this file is
 // based on code by Andrew Y. Ng, 1996:

 /*
  * Copyright (c) 1998-2003 Massachusetts Institute of Technology.
  * This code was developed as part of the Haystack research project
  * (http://haystack.lcs.mit.edu/). Permission is hereby granted,
  * free of charge, to any person obtaining a copy of this software
  * and associated documentation files (the "Software"), to deal in
  * the Software without restriction, including without limitation
  * the rights to use, copy, modify, merge, publish, distribute,
  * sublicense, and/or sell copies of the Software, and to permit
  * persons to whom the Software is furnished to do so, subject to
  * the following conditions:
  *
  * The above copyright notice and this permission notice shall be
  * included in all copies or substantial portions of the Software.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
  * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
  * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
  * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
  * OTHER DEALINGS IN THE SOFTWARE.
  */

#ifndef COMMON_HASHMAP_H
#define COMMON_HASHMAP_H

#include "common/types.h"

namespace common
{
	uint32 hashString(const char* str);
	uint32 hashStringLower(const char* str);
	char* cloneString(const char* str);
	void freeCloneString(const char* str);
	uint32 nextTableSize(uint32 size);

	template<typename T>
	struct HashLessThan {
		bool operator()(const T& first, const T& second) {
			return first < second;
		}
	};

	template<typename T>
	struct HashEqualsTo {
		bool operator()(const T& first, const T& second) {
			return first == second;
		}
	};

	template<typename T>
	struct HashFunction {
		uint32 operator()(const T& value);
	};

	template<> struct HashFunction<byte>  { uint32 operator()(const byte& value)   { return (uint32) value; }};
	template<> struct HashFunction<int16> { uint32 operator()(const int16& value)  { return (uint32) value; }};
	template<> struct HashFunction<int32> { uint32 operator()(const int32& value)  { return (uint32) value; }};
	template<> struct HashFunction<uint16>{ uint32 operator()(const uint16& value) { return (uint32) value; }};
	template<> struct HashFunction<uint32>{ uint32 operator()(const uint32& value) { return (uint32) value; }};

	template<> struct HashFunction<const char*> {
		uint32 operator()(const char* value) {
			return hashString(value);
		}
	};

	template<typename K, typename V>
	struct HashMapNode {
		K _key;
		V _value;

		HashMapNode() {
		}

		HashMapNode(const K& key, const V& value)
			: _key(key), _value(value) {
		}

		~HashMapNode() {
		}
	};

	template<typename V>
	struct HashMapNode<const char*, V> {
		char* _key;
		V _value;

		HashMapNode();
		HashMapNode(const char* key, const V& value) {
			_key = cloneString(key);
			_value = value;
		}

		~HashMapNode() {
			freeCloneString(_key);
		}

	};

	template<typename K, typename V>
	class HashMap {
	public:

		HashMap()
		{
		}

		~HashMap()
		{
		}

	private:
	};

}


#endif
