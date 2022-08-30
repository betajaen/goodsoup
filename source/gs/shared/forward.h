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

#ifndef GS_FORWARD_H
#define GS_FORWARD_H

typedef char __32BIT_ARCH_ONLY__[(!!(sizeof(void*) == 4))*2-1];

#if defined(GS_AMIGA)

#include <exec/types.h>

typedef UBYTE	uint8;
typedef BYTE	int8;
typedef UBYTE	byte;
typedef UWORD	uint16;
typedef WORD	int16;
typedef ULONG	uint32;
typedef LONG	int32;
typedef uint16	gs_bool;

#endif

#if defined(GS_SDL)

#include <stdint.h>

typedef uint8_t		uint8;
typedef int8_t		int8;
typedef uint8_t		byte;
typedef uint16_t	uint16;
typedef int16_t		int16;
typedef uint32_t	uint32;
typedef int32_t		int32;
typedef uint16	gs_bool;

#endif

#define GS_FALSE (0)
#define GS_TRUE  (1)

#define GS__CONCAT(a, b) a##b
#define GS_CONCAT(a, b) GS__CONCAT(a, b)
#define GS_CONCAT2(a, b) GS_CONCAT(a, GS_CONCAT(_, b))

#endif
