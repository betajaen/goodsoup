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

#ifndef GS_SPAN_H
#define GS_SPAN_H

#include "forward.h"
#include "debug.h"
#include "endian.h"

namespace gs
{
	
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
