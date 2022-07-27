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

	uint32 decodeNutFrame44ToRLE2(byte* nutSrc, byte* rleDst, byte* tempGlyphBuffer, RLEImage2& rle) {

		int16 len, t, s;
		byte  *nextSrc, *x;
		byte  *originalRleDst = rleDst;
		byte  *originalTempGlyphBuffer = tempGlyphBuffer;
		int8* writeRle = (int8*) rleDst;

		// byte histogram[256] = { 0 };

		for(uint16 y=0;y < rle._height;y++) {

			t = READ_LE_UINT16(nutSrc);
			nutSrc += 2;
			nextSrc = nutSrc + t;

			if (t == 0)
				continue;

			len = rle._width;
			x = tempGlyphBuffer;

			do {

				// Offset
				t = READ_LE_INT16(nutSrc);
				nutSrc += 2;
				len -= t;

				if (len <= 0)
					break;

				x += t;

				// Matte
				t = READ_LE_INT16(nutSrc) + 1;
				nutSrc += 2;
				len -= t;

				if (len < 0) {
					t += len;
				}


				while(t--) {
					s = *nutSrc;
					s = 1 + ((s - 0xE0) & 1);	// Colours seen are 0, 1, 224, 225
												// So if you do:
												//				x - 224
												//				then & 1
												//				it will be limited to 0..1
												//
					// histogram[s & 0xFF] = 1;
					*x= s;
					x++;
					nutSrc++;
				}

			} while(len > 0);


			tempGlyphBuffer += rle._width;
			nutSrc = nextSrc;
		}

		for(uint8 i=0;i < 2;i++) {
			rle._offsets[i] = ((byte*)writeRle) - rleDst;

			uint8 colourIdx = i + 1;
			byte* img = originalTempGlyphBuffer;

			for(uint16 y=0;y < rle._height;y++) {

				uint8 count = 0;
				uint8 type = 0;
				uint8 bHasColourThisLine = 0;

				for(uint16 x=0;x < rle._width;x++) {
					uint8 thisType = (*img == colourIdx ? 1 : 0);
					img++;

					if (x == 0) {
						count = 1;
						type = thisType;
						continue;
					}

					if (thisType == type) {
						count++;
						continue;
					}


					if (type == 0) {
						*writeRle = -((int8) count);
						writeRle++;
					}
					else {
						*writeRle = (int8) count;
						writeRle++;
						bHasColourThisLine = 1;
					}

					count = 1;
					type = thisType;
				}

				if (bHasColourThisLine == 1) {
					if (count > 0) {
						if (type == 0) {
							*writeRle = -((int8) count);
							writeRle++;
						} else {
							*writeRle = (int8) count;
							writeRle++;
						}
					}
				}

				*writeRle = 0;
				writeRle++;
			}

			*writeRle = -128;
			writeRle++;
		}

#if 0
		// for(uint16 i=0;i < 256;i++) {
		// 	byte count = histogram[i];
		// 	if (count != 0) {
		// 		debug(GS_THIS, "[%i]", i);
		// 	}
		// }

		debug_write_char('\n');
		debug_write_int(rle._width);
		debug_write_char('x');
		debug_write_int(rle._height);

		debug_write_char('\n');


		byte* dd = originalTempGlyphBuffer;
		for(uint16 y=0;y < rle._height;y++) {
			for (uint16 x=0;x < rle._width;x++) {
				byte t = (*dd);
				if (t == 0) {
					debug_write_char('.');
				}
				else {
					debug_write_char('0' + t);
				}

				dd++;
			}
			debug_write_char('\n');
		}
		debug_write_char('\n');

		debug_write_char('\n');
		int8* tv = (int8*) originalRleDst;

		while(tv < writeRle) {
			debug_write_int(*tv);
			debug_write_char(' ');
			tv++;
		}

		debug_write_char('\n');
#endif

		return ((byte*) writeRle) - originalRleDst;
	}

}
