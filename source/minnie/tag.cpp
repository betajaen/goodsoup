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

#include <exec/types.h>

namespace gs {

    inline CONST_STRPTR tag2str(ULONG tag) {
        static char str[8] = { 0 };

        *((ULONG*) str) = tag;
        
        return str;
    }

    inline CONST_STRPTR tag2str_2(ULONG tag) {
        static char str[8] = { 0 };

        *((ULONG*) str) = tag;
        
        return str;
    }
}

