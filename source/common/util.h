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

#ifndef COMMON_UTIL_H
#define COMMON_UTIL_H

#include "common/types.h"

namespace common
{
	inline const char* tag2str(uint32 tag, char* str)
	{
		str[0] = (char)(tag >> 24);
		str[1] = (char)(tag >> 16);
		str[2] = (char)(tag >> 8);
		str[3] = (char)tag;
		str[4] = '\0';
		return str;
	}

	inline uint32 SWAP_BYTES_32(uint32 a) {
		return ((a >> 24) & 0x000000FF) |
			((a >> 8) & 0x0000FF00) |
			((a << 8) & 0x00FF0000) |
			((a << 24) & 0xFF000000);
	}

	/**
	 * Swap the bytes in a 16 bit word in order to convert LE encoded data to BE
	 * and vice versa.
	 */
	inline uint16 SWAP_BYTES_16(uint16 a) {
		return ((a >> 8) & 0x00FF) + ((a << 8) & 0xFF00);
	}
}


#if defined(GS_LITTLE)

#define READ_UINT16(a) READ_LE_UINT16(a)
#define READ_UINT32(a) READ_LE_UINT32(a)

#define WRITE_UINT16(a, v) WRITE_LE_UINT16(a, v)
#define WRITE_UINT32(a, v) WRITE_LE_UINT32(a, v)

#define FROM_LE_32(a) ((uint32)(a))
#define FROM_LE_16(a) ((uint16)(a))

#define TO_LE_32(a) ((uint32)(a))
#define TO_LE_16(a) ((uint16)(a))

#define TO_BE_32(a) SWAP_BYTES_32(a)
#define TO_BE_16(a) SWAP_BYTES_16(a)

#elif defined(GS_BIG)

#define MKID(a) ((uint32)(a))
#define MKID_BE(a) ((uint32)(a))

#define READ_UINT16(a) READ_BE_UINT16(a)
#define READ_UINT32(a) READ_BE_UINT32(a)

#define WRITE_UINT16(a, v) WRITE_BE_UINT16(a, v)
#define WRITE_UINT32(a, v) WRITE_BE_UINT32(a, v)

#define FROM_LE_32(a) SWAP_BYTES_32(a)
#define FROM_LE_16(a) SWAP_BYTES_16(a)

#define TO_LE_32(a) SWAP_BYTES_32(a)
#define TO_LE_16(a) SWAP_BYTES_16(a)

#define TO_BE_32(a) ((uint32)(a))
#define TO_BE_16(a) ((uint16)(a))

#else

#error No endianness defined


#endif

#endif
