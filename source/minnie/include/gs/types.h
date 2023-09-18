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

#ifndef __GS_TYPES_H
#define __GS_TYPES_H

#if defined(__AMIGA__)
#include <exec/types.h>
#else
#include <stdint.h>

typedef uint8_t  UBYTE;
typedef uint16_t UWORD;
typedef uint32_t ULONG;
typedef int8_t   BYTE;
typedef int16_t  WORD;
typedef int32_t  LONG;
typedef void*    APTR;
typedef int16_t  SHORT;
typedef uint16_t  USHORT;

#endif


namespace gs {

    enum class AllocationType;

    template<typename T, AllocationType AT>
    class Buffer;

}

#endif