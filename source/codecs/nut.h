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

#ifndef GS_NUT_H
#define GS_NUT_H

#include "../types.h"

namespace gs
{
	// Decode NUT Font Frame, Codec 44
	// src should point to the 14th byte in the FRME data section.
	// Return is number of bytes written to dst.
	uint32 decodeNutFrame44ToBitmap(byte* src, byte* dst, uint16 width, uint16 height);
}


#endif
