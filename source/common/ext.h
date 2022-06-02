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

#ifndef COMMON_EXT_H
#define COMMON_EXT_H

#include "common/types.h"

namespace common
{
	template<typename T>
	inline void swap(T& l, T& r) {
        T t = l;
        l = r;
        r = t;
    }

    template<typename T>
    struct defaultValue {
        static T value();
    };

#define DEFAULT_VALUE(T, V) \
    template<> struct defaultValue<T> { static inline T value() { return V; }};

    DEFAULT_VALUE(bool, false);
    DEFAULT_VALUE(int8, 0);
    DEFAULT_VALUE(int16, 0);
    DEFAULT_VALUE(int32, 0);
    DEFAULT_VALUE(uint8, 0);
    DEFAULT_VALUE(uint16, 0);
    DEFAULT_VALUE(uint32, 0);

#undef DEFAULT_VALUE

    template<typename T>
    struct defaultValue<T*> {
        static inline T* value() {
            return NULL;
        } 
    };

    template<typename T>
    struct defaultValue<T**> {
        static inline T* value() {
            return NULL;
        } 
    };

}

#endif