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

namespace common
{
    static const char kNullString = { 0 };

    uint16 stringLength(const char* str) {
        uint16 length = 0;

        if (str) {
            while(*str++) {
                length++;
            }
        }

        verbose(GS_THIS, "(%s, %d)", str, length);
        return length;
    }

    const char* stringDuplicate(const char* str, uint16& length) {
        char* dup, *it;

        if (str == NULL) {
            return NULL;
        }

        length = stringLength(str);

        it = dup = (char*) ::common::allocateMemory(1, length + 1, MEMF_HINT_STRING);
        
        if (length) {
            for(;*str;it++, str++) {
                *it = *str;
            }
        }

        *it = '\0';

        verbose(GS_THIS, "(%d)", length);

        return dup;
    }

    String::String() {
        _data = &kNullString;
        _length = 0;
    }

    String::String(const char* str) {
        if (str == NULL) {
            _data = &kNullString;
            _length = 0;
        } else {
            _data = stringDuplicate(str, _length);
            verbose(GS_THIS, "(%s, %d)", _data, _length);
        }
    }

    String::String(String& str, bool move) {
        if (move) {
            _data = str._data;
            _length = str._length;
            str._data = kNullString;
            str._length = 0;
        }
        else {
            if (str._length == 0) {
                str._data = kNullString;
                str._length = 0;
            }
            else {
                str._data = stringDuplicate(str._data, _length);
            }
        }
    }

    String::String(const String& str) {
        _data = stringDuplicate(str._data, _length);
    }

    String::~String() {
        release();
    }

    void String::release() {
        if (_length && _data) {
            ::common::releaseMemory((void*) _data);
            _data = NULL;
            _length = 0;
        }
    }

    void test_string_1()
    {
        String s1;
    }

    void test_string_2()
    {
        String s2("Hello World");
    }

    void test_string()
    {
        test_string_1();
        test_string_2();
    }
}
