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

#define GS_FILE_NAME "codec47_opt_none"

#include "forward.h"
#include "endian.h"

#define GS_BITMAP_PITCH 640

namespace gs
{

	// Declared in video/smush/smush_tables.cpp
	extern int16 smush_motion_vectors[256];
	extern byte* smush_table_big;
	extern byte* smush_table_small;

	inline static void FillLine2x1(byte *dst, byte src) {
		uint16 t = src << 8 | src;
		*((uint16 *) dst) = t;
	}

	inline static void FillLine4x1(byte *dst, byte src) {
		uint32 t = src << 24 | src << 16 | src << 8 | src;
		uint32 *d = (uint32 *) dst;
		*d = t;
	}

	inline static void FillLine8x1(byte *dst, byte src) {
		uint32 t = src << 24 | src << 16 | src << 8 | src;
		uint32 *d = (uint32 *) dst;
		*d++ = t;
		*d = t;
	}

	inline static void CopyLine2x1(byte *dst, byte *src) {
		*((uint16 *) dst) = *((uint16 *) src);
	}

	inline static void CopyLine4x1(byte *dst, byte *src) {
		*((uint32 *) dst) = *((uint32 *) src);
	}

	inline static void CopyLine8x1(byte *dst, byte *src) {
		uint32 *d = (uint32 *) dst;
		uint32 *s = (uint32 *) src;
		*d++ = *s++;
		*d = *s;
	}

	static void decode_2x(byte *dst, uint32 offset, byte *&src, byte *offset1, byte *offset2, byte* params) {
		uint8 code = *src++;

		if (code < 0xF8) {
			int16 t = smush_motion_vectors[code];
			// 1.
			CopyLine2x1(dst + offset, offset1 + offset + t);
			// 2.
			CopyLine2x1(dst + offset + GS_BITMAP_PITCH, offset1 + offset + GS_BITMAP_PITCH + t);
		} else if (code == 0xFF) {
			// 1.
			CopyLine2x1(dst + offset, src);
			// 2.
			CopyLine2x1(dst + offset + GS_BITMAP_PITCH, src + 2);
			src += 4;
		} else if (code == 0xFE) {
			uint8 t = *src++;
			// 1.
			FillLine2x1(dst + offset, t);
			// 2.
			FillLine2x1(dst + offset + GS_BITMAP_PITCH, t);
		} else if (code == 0xFC) {
			// 1.
			CopyLine2x1(dst + offset, offset2 + offset);
			// 2.
			CopyLine2x1(dst + offset + GS_BITMAP_PITCH, offset2 + offset + GS_BITMAP_PITCH);
		} else {
			byte t = params[code - 0xF8];
			// 1.
			FillLine2x1(dst + offset, t);
			// 2.
			FillLine2x1(dst + offset + GS_BITMAP_PITCH, t);
		}
	}

	static void decode_4x(byte *dst, uint32 offset, byte *&src, byte *offset1, byte *offset2, byte* params) {
		uint8 code = *src++;

		if (code < 0xF8) {
			int16 t = smush_motion_vectors[code];
			// 1.
			CopyLine4x1(dst + offset, offset1 + offset + t);
			offset += GS_BITMAP_PITCH;
			// 2.
			CopyLine4x1(dst + offset, offset1 + offset + t);
			offset += GS_BITMAP_PITCH;
			// 3.
			CopyLine4x1(dst + offset, offset1 + offset + t);
			offset += GS_BITMAP_PITCH;
			// 4.
			CopyLine4x1(dst + offset, offset1 + offset + t);
		} else if (code == 0xFF) {
			decode_2x(dst, offset, src, offset1, offset2, params);
			offset += 2;
			decode_2x(dst, offset, src, offset1, offset2, params);
			offset += (GS_BITMAP_PITCH * 2) - 2;
			decode_2x(dst, offset, src, offset1, offset2, params);
			offset += 2;
			decode_2x(dst, offset, src, offset1, offset2, params);
		} else if (code == 0xFE) {
			const uint8 t = *src++;
			// 1.
			FillLine4x1(dst + offset, t);
			offset += GS_BITMAP_PITCH;
			// 2.
			FillLine4x1(dst + offset, t);
			offset += GS_BITMAP_PITCH;
			// 3.
			FillLine4x1(dst + offset, t);
			offset += GS_BITMAP_PITCH;
			// 4.
			FillLine4x1(dst + offset, t);
		} else if (code == 0xFD) {

			int32 tmp = *src++;
			int32 tmpPtr = tmp * 128;
			byte len = smush_table_small[tmpPtr + 96];
			byte val = *src++;
			int32 tmpPtr2 = tmpPtr;

			while (len--) {
				int16 m = READ_LE_INT16(smush_table_small + tmpPtr2);
				*(dst + offset + m) = val;
				tmpPtr2 += 2;
			}

			len = smush_table_small[tmpPtr + 97];
			val = *src++;
			tmpPtr2 = tmpPtr + 32;
			while (len--) {
				int16 m = READ_LE_INT16(smush_table_small + tmpPtr2);
				*(dst + offset + m) = val;
				tmpPtr2 += 2;
			}

		} else if (code == 0xFC) {
			// 1.
			CopyLine4x1(dst + offset, offset2 + offset);
			offset += GS_BITMAP_PITCH;
			// 2.
			CopyLine4x1(dst + offset, offset2 + offset);
			offset += GS_BITMAP_PITCH;
			// 3.
			CopyLine4x1(dst + offset, offset2 + offset);
			offset += GS_BITMAP_PITCH;
			// 4.
			CopyLine4x1(dst + offset, offset2 + offset);
		} else {
			byte t = params[code - 0xF8];
			// 1.
			FillLine4x1(dst + offset, t);
			offset += GS_BITMAP_PITCH;
			// 2.
			FillLine4x1(dst + offset, t);
			offset += GS_BITMAP_PITCH;
			// 3.
			FillLine4x1(dst + offset, t);
			offset += GS_BITMAP_PITCH;
			// 4.
			FillLine4x1(dst + offset, t);
		}
	}

	static void decode_8x(byte *dst, uint32 offset, byte *&src, byte *offset1, byte *offset2, byte* params) {

		uint8 code = *src++;

		if (code < 0xF8) {
			int32 t = smush_motion_vectors[code];
			// 1.
			CopyLine8x1(dst + offset, offset1 + offset + t);
			offset += GS_BITMAP_PITCH;
			// 2.
			CopyLine8x1(dst + offset, offset1 + offset + t);
			offset += GS_BITMAP_PITCH;
			// 3.
			CopyLine8x1(dst + offset, offset1 + offset + t);
			offset += GS_BITMAP_PITCH;
			// 4.
			CopyLine8x1(dst + offset, offset1 + offset + t);
			offset += GS_BITMAP_PITCH;
			// 5.
			CopyLine8x1(dst + offset, offset1 + offset + t);
			offset += GS_BITMAP_PITCH;
			// 6.
			CopyLine8x1(dst + offset, offset1 + offset + t);
			offset += GS_BITMAP_PITCH;
			// 7.
			CopyLine8x1(dst + offset, offset1 + offset + t);
			offset += GS_BITMAP_PITCH;
			// 8.
			CopyLine8x1(dst + offset, offset1 + offset + t);
		} else if (code == 0xFF) {
			decode_4x(dst, offset, src, offset1, offset2, params);
			offset += 4;
			decode_4x(dst, offset, src, offset1, offset2, params);
			offset += (GS_BITMAP_PITCH * 4) - 4;
			decode_4x(dst, offset, src, offset1, offset2, params);
			offset += 4;
			decode_4x(dst, offset, src, offset1, offset2, params);
		} else if (code == 0xFE) {
			uint8 t = *src++;
			// 1.
			FillLine8x1(dst + offset, t);
			offset += GS_BITMAP_PITCH;
			// 2.
			FillLine8x1(dst + offset, t);
			offset += GS_BITMAP_PITCH;
			// 3.
			FillLine8x1(dst + offset, t);
			offset += GS_BITMAP_PITCH;
			// 4.
			FillLine8x1(dst + offset, t);
			offset += GS_BITMAP_PITCH;
			// 5.
			FillLine8x1(dst + offset, t);
			offset += GS_BITMAP_PITCH;
			// 6.
			FillLine8x1(dst + offset, t);
			offset += GS_BITMAP_PITCH;
			// 7.
			FillLine8x1(dst + offset, t);
			offset += GS_BITMAP_PITCH;
			// 8.
			FillLine8x1(dst + offset, t);
		} else if (code == 0xFD) {

			byte tmp = *src++;
			int32 tmpPtr = ((int32) tmp) * 388;
			byte l = smush_table_big[tmpPtr + 384];
			byte val = *src++;
			int32 tmpPtr2 = tmpPtr;

			while (l--) {
				int16 m = READ_LE_INT16(smush_table_big + tmpPtr2);
				*(dst + offset + m) = val;
				tmpPtr2 += 2;
			}

			l = smush_table_big[tmpPtr + 385];
			val = *src++;
			tmpPtr2 = tmpPtr + 128;
			while (l--) {
				int16 m = READ_LE_INT16(smush_table_big + tmpPtr2);
				*(dst + offset + m) = val;
				tmpPtr2 += 2;
			}

		} else if (code == 0xFC) {
			// 1.
			CopyLine8x1(dst + offset, offset2 + offset);
			offset += GS_BITMAP_PITCH;
			// 2.
			CopyLine8x1(dst + offset, offset2 + offset);
			offset += GS_BITMAP_PITCH;
			// 3.
			CopyLine8x1(dst + offset, offset2 + offset);
			offset += GS_BITMAP_PITCH;
			// 4.
			CopyLine8x1(dst + offset, offset2 + offset);
			offset += GS_BITMAP_PITCH;
			// 5.
			CopyLine8x1(dst + offset, offset2 + offset);
			offset += GS_BITMAP_PITCH;
			// 6.
			CopyLine8x1(dst + offset, offset2 + offset);
			offset += GS_BITMAP_PITCH;
			// 7.
			CopyLine8x1(dst + offset, offset2 + offset);
			offset += GS_BITMAP_PITCH;
			// 8.
			CopyLine8x1(dst + offset, offset2 + offset);
		} else {
			byte t = params[code - 0xF8];
			// 1.
			FillLine8x1(dst + offset, t);
			offset += GS_BITMAP_PITCH;
			// 2.
			FillLine8x1(dst + offset, t);
			offset += GS_BITMAP_PITCH;
			// 3.
			FillLine8x1(dst + offset, t);
			offset += GS_BITMAP_PITCH;
			// 4.
			FillLine8x1(dst + offset, t);
			offset += GS_BITMAP_PITCH;
			// 5.
			FillLine8x1(dst + offset, t);
			offset += GS_BITMAP_PITCH;
			// 6.
			FillLine8x1(dst + offset, t);
			offset += GS_BITMAP_PITCH;
			// 7.
			FillLine8x1(dst + offset, t);
			offset += GS_BITMAP_PITCH;
			// 8.
			FillLine8x1(dst + offset, t);
		}
	}

	void smush_codec47_opt_none(byte* dst, byte* src, byte* src1, byte* src2, uint8* params) {
		uint8 bw = 80;
		uint8 bh = 60;
		const uint32 nextLine = GS_BITMAP_PITCH * 7;
		uint32 offset =0;
		do
		{
			uint8 tmp_bw = bw;
			do
			{
				decode_8x(dst, offset, src, src1, src2, params);
				offset += 8;
			} while ((--tmp_bw) != 0);
			offset += nextLine;
		} while ((--bh) != 0);
	}

}
