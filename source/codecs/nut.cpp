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

#define GS_FILE_NAME "nut"

#include "../types.h"
#include "../debug.h"
#include "../endian.h"
#include "rle.h"

namespace gs
{
	uint32 decodeNutFrame44ToBitmap(byte* src, byte* dst, uint16 width, uint16 height) {

		int16 len, t;
		byte  *nextSrc, *x;
		byte  *originalDst = dst;

		for(uint16 y=0;y < height;y++) {

			t = READ_LE_UINT16(src);
			src += 2;
			nextSrc = src + t;

			if (t == 0)
				continue;

			len = width;
			x = dst;

			do {

				// Offset
				t = READ_LE_INT16(src);
				src += 2;
				len -= t;

				if (len <= 0)
					break;

				x += t;

				// Matte
				t = READ_LE_INT16(src) + 1;
				src += 2;
				len -= t;

				if (len < 0) {
					t += len;
				}

				while(t--) {
					*x= *src;
					x++;
					src++;
				}

			} while(len > 0);

			dst += width;
			src = nextSrc;
		}

		return dst - originalDst;
	}

	uint32 decodeNutFrame44ToRLE2(byte* src, byte* dst, RLEImage2& rle) {

		int16 len, t;
		byte  *nextSrc, *x;
		byte  *originalDst = dst;

		uint32 histogram[256] = { 0 };

		for(uint16 y=0;y < rle._height;y++) {

			t = READ_LE_UINT16(src);
			src += 2;
			nextSrc = src + t;

			if (t == 0)
				continue;

			len = rle._width;
			x = dst;

			do {

				// Offset
				t = READ_LE_INT16(src);
				src += 2;
				len -= t;

				if (len <= 0)
					break;

				x += t;

				// Matte
				t = READ_LE_INT16(src) + 1;
				src += 2;
				len -= t;

				if (len < 0) {
					t += len;
				}


				while(t--) {
					*x= *src;
					histogram[(*src) & 0xFF]++;
					x++;
					src++;
				}

			} while(len > 0);

			dst += rle._width;
			src = nextSrc;
		}

		for(uint16 i=0;i < 256;i++) {
			uint16 count = histogram[i];

			if (count > 0) {
				debug(GS_THIS, "Histogram [%ld] => %ld", i, count);
			}
		}

		return dst - originalDst;
	}

}