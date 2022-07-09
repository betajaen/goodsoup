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

#ifndef GS_STRING_H
#define GS_STRING_H

#include "types.h"
#include "string.h"
#include "debug.h"
#include "memory.h"
#include "ext.h"

#define STRING_SMALL_SIZE 12

namespace gs
{

	#pragma pack(push, 4)
	struct LongStringData {
		uint16 _users;   
		uint16 _length;     
		char   _str[4];
	};
	#pragma pack(pop)


	#pragma pack(push, 4)
	union StringData {
		char _small[STRING_SMALL_SIZE];
		struct LongData {
			LongStringData* _str;
			uint32 _hash;
			char _padding[
				STRING_SMALL_SIZE -
				sizeof(LongStringData*) -
				sizeof(uint32)
			];
		} _long;
		uint32 _longs[STRING_SMALL_SIZE >> 2];
	};
	#pragma pack(pop)

	GS_STATIC_ASSERT(sizeof(StringData) == STRING_SMALL_SIZE, StringData_length_must_be_STRING_SMALL_SIZE);

	#pragma pack(push, 4)
	struct String {
		private:
			StringData _data;

			void clear();            
			void _copyFrom(char ch);
			void _copyFrom(const char* str);
			void _copyFrom(const String& other);
			void _moveFrom(String& other);
			void _reserve(uint16 length);
			void _refreshHash();
			char* _stringWritable();

		public:
			String();
			String(char ch);
			String(const char* str);
			String(String& str, bool move);
			String(const String& str);
			~String();

			void release();

			bool isSmallString() const;

			void copyFrom(char ch) {
				release();
				_copyFrom(ch);
			}

			void copyFrom(const char* str) {
				release();
				_copyFrom(str);
			}

			void copyFrom(const String& other) {
				release();
				_copyFrom(other);
			}

			void copyTo(String& other) const {
				other.copyFrom(*this);
			}

			void moveFrom(String& other) {
				release();
				_moveFrom(other);
			}

			void moveTo(String& other) {
				other.moveFrom(*this);
			}

			String& operator=(const String& other) {
				copyFrom(other);
				return *this;
			}

			bool equals(const char* str) const;
			bool equals(const String& other) const;

			inline bool notEquals(const String& other) const {
				return !equals(other);
			}

			inline bool operator==(const String& other) const {
				return equals(other);
			}

			bool operator!=(const String& other) const {
				return notEquals(other);
			}
			
			uint32 hash() const;
			uint16 length() const;
			const char* string() const;

			uint32 _heapSize() const;

			static void format(String& str, const char* fmt, ...);
			static String format(const char* fmt, ...);


	};
	#pragma pack(pop)

	GS_STATIC_ASSERT(sizeof(String) == STRING_SMALL_SIZE, String_must_be_STRING_SMALL_SIZE);

    uint16 stringLength(const char* str);
    uint16 stringFormatInto(char* dst, uint16 length, const char* fmt, ...);
}

#endif
