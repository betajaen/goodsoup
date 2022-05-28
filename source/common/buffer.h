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

#ifndef BUFFER_H
#define BUFFER_H

#include "common/types.h"
#include "common/memory.h"
#include "common/debug.h"

namespace common
{

	template<typename T>
	struct Buffer
	{
	private:
		T* _data;
		uint32 _size;
	public:

		Buffer() {
			_size = 0;
			_data = NULL;
		}

		~Buffer() {
			release();
		}

		void setSize(uint32 size, int flags = MEMF_CLEAR) {
			if (_size && _data) {
				releaseMemory(_data);;
			}
			_data = (T*)allocateMemory(size, sizeof(T), flags);
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

		void set_unchecked(uint32 idx, const T& newValue) {
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

		const T& get(uint32 idx) const {
			if (idx >= _size)
				error("array(Out of bounds, const, %d)", idx);

			return _data[idx];
		}

		T& get_unchecked(uint32 idx) {
			return _data[idx];
		}

		const T& get_unchecked(uint32 idx) const {
			return _data[idx];
		}
	};


}

#endif
