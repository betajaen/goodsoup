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

#ifndef ARRAY_H
#define ARRAY_H

#include "goodsoup.h"
#include <new>

namespace common
{

	template<typename T>
	struct Array
	{
	private:
		T* _data;
		uint32 _size;
	public:

		Array() {
			_size = 0;
			_data = 0;
		}

		~Array() {
			releaseMem();
		}

		void setSize(uint32 size) {
			if (_size && _data) {
				freeMem(_data);;
			}
			_data = (T*) allocMem(size, sizeof(T), MEMF_CLEAR);
			_size = size;
		}

		void releaseMem() {
			if (_size && _data) {
				freeMem(_data);
				_size = 0;
				_data = NULL;
			}
		}

		void zeroMem() {
			if (_size && _data) {
				clearMem(_data, _size * sizeof(T));
			}
		}

		bool hasMem() {
			return (_size && _data);
		}

		void callCtors() {
			if (_size && _data) {
				for (uint32 i = 0; i < _size; i++) {
					T* obj = ptr(i);
					new (obj)T();
				}
			}
		}

		void callDtors() {
			if (_size && _data) {
				for (uint32 i = 0; i < _size; i++) {
					_data[i].~T();
				}
			}
		}

		uint32 getSize() const {
			return _size;
		}

		void set(uint32 idx, const T& newValue) {
			if (idx >= _size)
				error("array(Out of bounds, replace, %d)", idx);

			_data[idx] = newValue;
		}

		T* ptr(uint32 idx) {

			if (idx >= _size)
				error("array(Out of bounds, ptr, %d)", idx);

			return &_data[idx];
		}

		const T* ptr(uint32 idx) const {

			if (idx >= _size)
				error("array(Out of bounds, const ptr, %d)", idx);

			return &_data[idx];
		}


		T& get(uint32 idx) {
			if (idx >= _size)
				error("array(Out of bounds, mut, %d)", idx);

			return _data[idx];
		}

		const T& get(uint32 idx) const
		{
			if (idx >= _size)
				error("array(Out of bounds, const, %d)", idx);

			return _data[idx];
		}
	};


}

#endif
