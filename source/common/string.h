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

#ifndef STRING_H
#define STRING_H

#include "common/types.h"
#include "common/string.h"
#include "common/debug.h"
#include "common/memory.h"

namespace common
{

    uint16 stringLength(const char* str);
    const char* stringDuplicate(const char* str);

    struct String {
        private:
            const char* _data;
            uint16 _length;

            void release();

        public:

            String();
            String(const char* str);
            String(String& str, bool move);
            String(const String& str);
            
            ~String();

            uint16 length() const {
                return _length; 
            }

            char operator[](uint16 idx) const {
                if (idx >= _length) {
                    error(GS_THIS, "(%s, %d, %d) Out of string bounds.", _data, _length, idx);
                }

                return _data[idx];
            }

            const char* string() const {
                return _data;
            }

    };

}

#endif
