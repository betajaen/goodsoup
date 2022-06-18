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

#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

typedef char __GS_ASSERT_32BIT_ARCH_ONLY__[(!!(sizeof(void*) == 4)) * 2 - 1];

#include <exec/types.h>
#include <new>

typedef char __GS_ASSERT_UBYTE_IS_1_BYTE__[(!!(sizeof(UBYTE) == 1)) * 2 - 1];
typedef char __GS_ASSERT_UWORD_IS_2_BYTE__[(!!(sizeof(UWORD) == 2)) * 2 - 1];
typedef char __GS_ASSERT_ULONG_IS_4_BYTE__[(!!(sizeof(ULONG) == 4)) * 2 - 1];
typedef char __GS_ASSERT_BYTE_IS_1_BYTE__[(!!(sizeof(BYTE) == 1)) * 2 - 1];
typedef char __GS_ASSERT_WORD_IS_2_BYTE__[(!!(sizeof(WORD) == 2)) * 2 - 1];
typedef char __GS_ASSERT_LONG_IS_4_BYTE__[(!!(sizeof(LONG) == 4)) * 2 - 1];
typedef char __GS_ASSERT_CHAR_IS_1_BYTE__[(!!(sizeof(char) == 1)) * 2 - 1];
typedef char __GS_ASSERT_INT_IS_1_BYTE__[(!!(sizeof(int) == 4)) * 2 - 1];
typedef char __GS_ASSERT_SHORT_IS_2_BYTE__[(!!(sizeof(short) == 2)) * 2 - 1];

typedef unsigned char byte;
typedef unsigned char uint8; 
typedef unsigned short uint16;
typedef unsigned int   uint32;
typedef char    int8;
typedef short    int16;
typedef int    int32;

#define STRINGIFY_ARG(arg)  #arg

namespace common
{
	void abort();
}

#endif
