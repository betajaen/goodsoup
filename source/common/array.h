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

#ifndef COMMON_ARRAY_H
#define COMMON_ARRAY_H

#include "common/types.h"
#include "common/memory.h"
#include "common/debug.h"

namespace common
{

	template<typename T, typename Index = uint16>
	class Array {
	private:

		T* _begin;
		Index _size, _capacity;

		void grow() {
			gs_verbose("/1(%p,%d,%d)", _begin, _size, _capacity);
			if (_capacity == 0) {
				_capacity = 8;
				_begin = (T*) ::common::allocateMemory(_capacity, sizeof(T), MEMF_CLEAR);
			}
			else {
				_capacity *= 2;
				_begin = (T*) ::common::reallocateMemory(_begin, _capacity, sizeof(T));
			}
			gs_verbose("/2(%p,%d,%d)", _begin, _size, _capacity);
		}

	public:

		Array() :
			_begin(NULL), _size(0), _capacity(0) {
		}

		~Array() {
			release();
		}

		void release() {
			if (_begin) {
				::common::releaseMemory(_begin);
				_begin = NULL;
				_size = 0;
				_capacity = 0;
			}
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
				gs_error("(%p, %d, %d, %d) Out of bounds erasure.", _begin, _size, _capacity);
			}

			--_size;
		}

		void erase(Index index) {
			if (index >= _size) {
				gs_error("(%p, %d, %d, %d) Out of bounds erasure.", _begin, _size, _capacity, index);
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
