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

#ifndef __GS_DISTINCT_H
#define __GS_DISTINCT_H

#if !defined(__AMIGA__)
#error "Only Amiga supported!"
#endif

#include <exec/types.h>

namespace gs {

    template<typename T, ULONG Tag>
    struct Distinct final {
    private:
        const T value;
    public:

        typedef Distinct<T, Tag> ThisType;

        inline Distinct() : value {} {}

        inline explicit Distinct(T value_) : value{value_} {}


        inline ThisType operator+(const ThisType& rhs) {
            return Distinct(value + rhs.value);
        }

        inline ThisType operator-(const ThisType& rhs) {
            return Distinct(value - rhs.value);
        }

        inline operator bool() const {
            return value != 0;
        }

        inline const T getValue() const {
            return value;
        }

        inline T getValue() {
            return value;
        }
    };

}

#endif