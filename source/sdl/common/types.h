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

typedef char __GS_ASSERT_32BIT_ARCH_ONLY__[(!!(sizeof(void*) == 4))*2-1];

#include <SDL2/SDL.h>
#include <new>

typedef Uint8   byte;
typedef Uint8   uint8;
typedef Uint16  uint16;
typedef Uint32  uint32;
typedef Sint8   int8;
typedef Sint16  int16;
typedef Sint32  int32;

#define STRINGIFY_ARG(arg)  #arg

#endif
