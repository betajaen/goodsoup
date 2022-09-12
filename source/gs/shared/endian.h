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

#ifndef GS_ENDIAN_H
#define GS_ENDIAN_H

#include "shared/forward.h"

static inline uint32 gs_endian_swap_uint32(uint32 a) {
	return ((a >> 24) & 0x000000FF) |
		((a >> 8) & 0x0000FF00) |
		((a << 8) & 0x00FF0000) |
		((a << 24) & 0xFF000000);
}

static inline uint16 gs_endian_swap_uint16(uint16 a) {
	return ((a >> 8) & 0x00FF) + ((a << 8) & 0xFF00);
}


#if defined(GS_BIG)

#define gs_to_le32(a) gs_endian_swap_uint32(a)
#define gs_to_le16(a) gs_endian_swap_uint16(a)
#define gs_to_be32(a) ((uint32)(a))
#define gs_to_be16(a) ((uint16)(a))

#define gs_from_le32(a) gs_endian_swap_uint32(a)
#define gs_from_le16(a) gs_endian_swap_uint16(a)
#define gs_from_be32(a) ((uint32)(a))
#define gs_from_be16(a) ((uint16)(a))

#else

#define gs_to_le32(a) ((uint32)(a))
#define gs_to_le16(a) ((uint16)(a))
#define gs_to_be32(a) gs_endian_swap_uint32(a)
#define gs_to_be16(a) gs_endian_swap_uint16(a)

#define gs_from_le32(a) ((uint32)(a))
#define gs_from_le16(a) ((uint16)(a))
#define gs_from_be32(a) gs_endian_swap_uint32(a)
#define gs_from_be16(a) gs_endian_swap_uint16(a)

#endif

#endif
