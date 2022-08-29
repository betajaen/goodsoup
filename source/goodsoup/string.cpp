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

#define GS_FILE_NAME "string"

#include "string.h"
#include "test.h"

#define STRING_LEN_BYTE (STRING_SMALL_SIZE-1)
#define STRING_SMALL_MAX_SIZE (STRING_SMALL_SIZE-2)
#define STRING_BIG_STRING_MARKER ((char) 255)

namespace gs
{
	uint16 stringLength(const char* str) {
		uint16 length = 0;

		if (str) {
			while(*str++) {
				length++;
			}
		}

		return length;
	}

	uint32 stringToUInt32(const char* str) {
		uint32 num = 0;
		while(*str != 0) {
			if (*str < '0' || *str > '9')
				break;

			num *= 10;
			num += *str - '0';

			str++;
		}

		return num;
	}

	String::String() {
		clear();
	}

	String::String(char ch) {
		clear();
		_copyFrom(ch);
	}

	String::String(const char* str) {
		clear();
		_copyFrom(str);
	}

	String::String(String& str, bool move) {
		clear();
		if (move) {
			_moveFrom(str);
		}
		else {
			_copyFrom(str);
		}
	}

	String::String(const String& str) {        
		clear();
		_copyFrom(str);
	}

	String::~String() {
		release();
	}

	void String::clear() {                      
		for(uint16 i=0;i < (STRING_SMALL_SIZE / 4);i++){
			_data._longs[i] = 0;
		}
	}

	void String::release() {
		
		if (isSmallString() == false) {
			LongStringData* longData = _data._long._str;

			longData->_users--;

			if (longData->_users == 0) {
				releaseMemory(longData);
			}

			_data._long._str = NULL;
		}

		clear();
	}

	void String::_reserve(uint16 length) {
		uint16 i;

		release();

		if (length < STRING_SMALL_MAX_SIZE) {
			_data._small[STRING_LEN_BYTE - 1] = 0;
			_data._small[STRING_LEN_BYTE] = length;
		}
		else {

			LongStringData* longData = (LongStringData*)
				allocateMemory(
					1,
					sizeof(uint16) +
					sizeof(uint16) +
					length + 1,
					MF_Any,
					GS_COMMENT_FILE_LINE
				);

			longData->_length = length;
			longData->_users = 1;

			char* dst = &longData->_str[0];
			*dst = '\0';

			_data._long._str = longData;
			_data._long._hash = 0;
			_data._small[STRING_LEN_BYTE] = STRING_BIG_STRING_MARKER;
		}
	}

	void String::_refreshHash() {
		if (isSmallString() == false) {
			LongStringData* longData = _data._long._str;

			char* str = &longData->_str[0];
			char ch;

			uint32 hash = 5381;

			while (*str) {
				ch = *str;
				hash = ((hash << 5) + hash) + ch;
				str++;
			}

			_data._long._hash = hash;
		}
	}

	char* String::_stringWritable() {
		if (isSmallString()) {
			return &_data._small[0];
		}
		else {
			return &_data._long._str->_str[0];
		}
	}

	bool String::isSmallString() const {
		return !(_data._small[STRING_LEN_BYTE] == STRING_BIG_STRING_MARKER);
	}
	
	uint16 String::length() const {
		if (isSmallString()) {
			uint32 x = _data._small[STRING_LEN_BYTE];
			return _data._small[STRING_LEN_BYTE];
		}
		else {
			uint32 x = _data._long._str->_length;
			return _data._long._str->_length;
		}
	}

	const char* String::string() const {
		if (isSmallString()) {
			return &_data._small[0];
		}
		else {
			return &_data._long._str->_str[0];
		}
	}

	void String::_copyFrom(char ch) {
		_data._small[0] = ch;
		_data._small[1] = 0;
		_data._small[STRING_LEN_BYTE] = 1;
	}

	void String::_copyFrom(const char* str) {
		uint16 length = stringLength(str);
		uint16 i;
		uint32 hash;
		char ch;

		if (length < STRING_SMALL_MAX_SIZE) {

			for(uint16 i=0;i < length;i++) {
				_data._small[i] = str[i];
			}

			_data._small[STRING_LEN_BYTE-1] = 0;
			_data._small[STRING_LEN_BYTE] = length;
		}
		else {

			LongStringData* longData = (LongStringData*)
				allocateMemory(
					1,
					sizeof(uint16) +
					sizeof(uint16) +
					length + 1,
					MF_Any,
					GS_COMMENT_FILE_LINE
			);

			longData->_length = length;
			longData->_users = 1;

			hash = 5381;
			char* dst = &longData->_str[0];
			while(*str) {
				ch = *str;
				hash = ((hash << 5) + hash) + ch;
				*dst = ch;
				dst++;
				str++;
			}
			*dst = '\0';

			_data._long._str = longData;
			_data._long._hash = hash;
			_data._small[STRING_LEN_BYTE] = STRING_BIG_STRING_MARKER;
		}
	}

	void String::_copyFrom(const String& other) {
		for(uint16 i=0;i < (STRING_SMALL_SIZE / 4);i++) {
			_data._longs[i] = other._data._longs[i];
		}

		if (_data._small[STRING_LEN_BYTE] == STRING_BIG_STRING_MARKER) {
			_data._long._str->_users++;
		}
	}

	void String::_moveFrom(String& other) {
		for(uint16 i=0;i < (STRING_SMALL_SIZE / 4);i++) {
			_data._longs[i] = other._data._longs[i];
			other._data._longs[i] = 0;
		}
	}

	uint32 String::_heapSize() const
	{
		if (isSmallString()) {
			return 0;
		}

		LongStringData* data = _data._long._str;
		return sizeof(uint16) + sizeof(uint16) + data->_length + 1;
	}


	bool String::equals(const char* str) const {
		const char* this_str = string();
		while(true) {
			if (*this_str != *str)
				return false;
			
			if (*this_str == '\0')
				return true;

			str++;
			this_str++;
		}
	}

	bool String::equals(const String& other) const {
		const bool sm0 = isSmallString();
		const bool sm1 = other.isSmallString();

		if (sm0 && sm1) {
			for(uint16 i=0; i < (STRING_SMALL_SIZE) / 4;i++) {
				if (_data._longs[i] != other._data._longs[i])
					return false;
			} 
			return true;
		}
		else if (!sm0 && !sm1) {
			return _data._long._hash == other._data._long._hash;
		}

		return false;
	}

	uint32 String::hash() const {
		if (isSmallString()) {
			uint32 hash = 5381;
			const char* str = &_data._small[0];
			while(*str) {
				hash = ((hash << 5) + hash) + *str;
				str++;
			}
			return hash;
		}
		else {
			return _data._long._hash;
		}
	}

	TEST_CASE(string_1)
	{
		String s1;


		TEST_EQUAL((uint16) 0, s1.length());
		TEST_EQUAL(true, s1.isSmallString());
		TEST_EQUAL('\0', s1.string()[0]);
	}

	TEST_CASE(string_2)
	{
		String s2('a');
		TEST_EQUAL((uint16) 1, s2.length());
		TEST_EQUAL(true, s2.isSmallString());
		TEST_EQUAL('a', s2.string()[0]);
		TEST_EQUAL('\0', s2.string()[1]);
	}

	TEST_CASE(string_3)
	{
		String s3("Hello");
		TEST_EQUAL((uint16) 5, s3.length());
		TEST_EQUAL(true, s3.isSmallString());
		TEST_EQUAL('H', s3.string()[0]);
		TEST_EQUAL('e', s3.string()[1]);
		TEST_EQUAL('l', s3.string()[2]);
		TEST_EQUAL('l', s3.string()[3]);
		TEST_EQUAL('o', s3.string()[4]);        
		TEST_EQUAL('\0', s3.string()[5]);
	}

	void string_4_impl() {
		TEST_MEMORY_MEASURE(m1);
		String s4("Hello World");
		TEST_EQUAL((uint16) 11, s4.length());
		TEST_EQUAL(false, s4.isSmallString());
		TEST_EQUAL((2u + 2u + 11u + 1u), s4._heapSize());
		TEST_MEMORY(m1, (2u + 2u + 11u + 1u));
	}

	TEST_CASE(string_4)
	{
		TEST_MEMORY_MEASURE(m1);
		TEST_MEMORY(m1, 0u);
		string_4_impl();
		TEST_MEMORY(m1, 0u);
	}

	TEST_CASE(string_5)
	{
		TEST_MEMORY_MEASURE(m1);
		TEST_MEMORY(m1, 0UL);
		String s5("Hello World2");
		TEST_EQUAL((uint16) 12, s5.length());
		TEST_EQUAL((12u + 1u + 2u + 2u), s5._heapSize());
		TEST_MEMORY(m1, (12u + 1u + 2u + 2u));

		String s6(s5);
		TEST_EQUAL((uint16) 12u, s6.length());
		TEST_EQUAL((12u + 1u + 2u + 2u), s6._heapSize());

		// s5 and s6 should use the same memory since
		// the string is the same.
		TEST_MEMORY(m1, (12u + 1u + 2u + 2u));
	}

	TEST_CASE(string_6)
	{
		TEST_MEMORY_MEASURE(m1);
		TEST_MEMORY(m1, 0);
		String s5("Hello World2");
		TEST_EQUAL((uint16) 12, s5.length());
		TEST_EQUAL((12u + 1u + 2u + 2u), s5._heapSize());
		String s6(s5, true);
		TEST_EQUAL((uint16) 12, s6.length());
		TEST_EQUAL((12u + 1u + 2u + 2u), s6._heapSize());

		TEST_MEMORY(m1, (12u + 1u + 2u + 2u));

		TEST_EQUAL((uint16) 0, s5.length());
		TEST_EQUAL(true, s5.isSmallString());
	}

	TEST_SUITE(string)
	{
		TEST_RUN_CASE(string_1);
		TEST_RUN_CASE(string_2);
		TEST_RUN_CASE(string_3);
		TEST_RUN_CASE(string_4);
		TEST_RUN_CASE(string_5);
		TEST_RUN_CASE(string_6);
	}
}
