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

#ifndef SPAN_H
#define SPAN_H

#include "common/types.h"
#include "common/debug.h"

namespace common
{
	
	template<typename T, typename Index = uint16>
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

		const T& get(Index idx) const {
			if (idx >= _size)
				error(GS_THIS, "ReadSpan(Out of bounds, const, %d)", idx);

			return _data[idx];
		}

		const T& get_unchecked(Index idx) const {
			return _data[idx];
		}

	};
	
	template<typename T, typename Index = uint16>
	struct ReadWriteSpan {
	private:
		T* _data;
		Index _size;
	public:

		ReadWriteSpan() 
			: _data(NULL), _size(0) {
		}

		ReadWriteSpan(const T* data, Index size) 
			: _data(data), _size(size)
		{
		}

		ReadWriteSpan(const ReadSpan<byte, Index>& other) 
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
