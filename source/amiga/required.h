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

#ifndef GS_AMIGA_REQUIRED_H
#define GS_AMIGA_REQUIRED_H

#include <exec/types.h>

namespace gs
{
	typedef UBYTE  byte;
	typedef UBYTE  uint8;
	typedef UWORD  uint16;
	typedef ULONG  uint32;
	typedef BYTE   int8;
	typedef WORD   int16;
	typedef LONG   int32;

	void debug(const char* fmt, ...);
	void warn(const char* fmt, ...);
	void error(const char* fmt, ...);

	void __assert_impl(const char* file, int line);

#define assert(X) do { if (!(X)) { __assert_impl(__FILE__, __LINE__); } } while(0)
}

#endif
