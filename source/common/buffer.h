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
#include "common/span.h"

namespace common
{

	template<typename T, typename Index = uint16>
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

		void setSize(Index size, int flags = MEMF_CLEAR) {
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



}

#endif
