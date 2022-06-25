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

#ifndef GS_HASH_H
#define GS_HASH_H

#include "types.h"
#include "string.h"

namespace gs
{
	uint32 djb2Hash(const char* str);

	template<typename T>
	struct HashFunction {
		uint32 hash(const T& value); /* Not implemented on purpose. */
	};

	template<>
	struct HashFunction<const char*> {
		uint32 hash(const char* value) {
			return djb2Hash(value);
		}
	};

	template<>
	struct HashFunction<uint16> {
		uint32 hash(uint16 value) {
			return (uint32) value;
		}
	};

	template<>
	struct HashFunction<uint32> {
		uint32 hash(uint32 value) {
			return (uint32)value;
		}
	};

	template<>
	struct HashFunction<int16> {
		uint32 hash(int16 value) {
			return (int32)value;
		}
	};

	template<>
	struct HashFunction<int32> {
		uint32 hash(int32 value) {
			return (int32)value;
		}
	};

	template<>
	struct HashFunction<String> {
		uint32 hash(const String& value) {
			return value.hash();
		}
	};
	
}


#endif
