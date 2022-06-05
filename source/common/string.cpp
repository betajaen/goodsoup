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
#include "common/test.h"

#define STRING_LEN_BYTE (STRING_SMALL_SIZE-1)
#define STRING_SMALL_MAX_SIZE (STRING_SMALL_SIZE-2)
#define STRING_BIG_STRING_MARKER ((char) 255)

namespace common
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

    bool String::isSmallString() const {
        return !(_data._small[STRING_LEN_BYTE] == STRING_BIG_STRING_MARKER);
    }
    
    uint16 String::length() const {
        if (isSmallString()) {
            uint32 x = _data._small[STRING_LEN_BYTE];
            verbose(GS_THIS, "small %u", x);
            return _data._small[STRING_LEN_BYTE];
        }
        else {
            uint32 x = _data._long._str->_length;
            verbose(GS_THIS, "large %u", x);
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
                    MEMF_ANY
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

    TEST_CASE(string_1)
    {
        String s1;


        TEST_EQUAL(0, s1.length());
        TEST_EQUAL(true, s1.isSmallString());
        TEST_EQUAL('\0', s1.string()[0]);
    }

    TEST_CASE(string_2)
    {
        String s2('a');
        TEST_EQUAL(1, s2.length());
        TEST_EQUAL(true, s2.isSmallString());
        TEST_EQUAL('a', s2.string()[0]);
        TEST_EQUAL('\0', s2.string()[1]);
    }

    TEST_CASE(string_3)
    {
        String s3("Hello");
        TEST_EQUAL(5, s3.length());
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
        TEST_EQUAL(11, s4.length());
        TEST_EQUAL(false, s4.isSmallString());
        TEST_EQUAL((2 + 2 + 11 + 1), s4._heapSize());
        TEST_MEMORY(m1, (2 + 2 + 11 + 1));
    }

    TEST_CASE(string_4)
    {
        TEST_MEMORY_MEASURE(m1);
        TEST_MEMORY(m1, 0);
        string_4_impl();
        TEST_MEMORY(m1, 0);
    }

    TEST_CASE(string_5)
    {
        TEST_MEMORY_MEASURE(m1);
        TEST_MEMORY(m1, 0);
        String s5("Hello World2");
        TEST_EQUAL(12, s5.length());
        TEST_EQUAL((12 + 1 + 2 + 2), s5._heapSize());
        TEST_MEMORY(m1, (12 + 1 + 2 + 2));

        String s6(s5);
        TEST_EQUAL(12, s6.length());
        TEST_EQUAL((12 + 1 + 2 + 2), s6._heapSize());

        // s5 and s6 should use the same memory since
        // the string is the same.
        TEST_MEMORY(m1, (12 + 1 + 2 + 2));
    }

    TEST_CASE(string_6)
    {
        TEST_MEMORY_MEASURE(m1);
        TEST_MEMORY(m1, 0);
        String s5("Hello World2");
        TEST_EQUAL(12, s5.length());
        TEST_EQUAL((12 + 1 + 2 + 2), s5._heapSize());
        String s6(s5, true);
        TEST_EQUAL(12, s6.length());
        TEST_EQUAL((12 + 1 + 2 + 2), s6._heapSize());

        TEST_MEMORY(m1, (12 + 1 + 2 + 2));

        TEST_EQUAL(0, s5.length());
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
