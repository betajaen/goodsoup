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

#define GS_FILE_NAME "codec47_opt_ulong"

#include "forward.h"
#include "endian.h"

#define PITCH_32 160 /* (640 / sizeof(uint32)) */
#define PITCH_16 320 /* (640 / sizeof(uint16)) */

namespace gs
{

	// Declared in video/smush/smush_tables.cpp
	extern int16 smush_motion_vectors[256];
	extern byte* smush_table_big;
	extern byte* smush_table_small;


#define COPY_8x1(D, S) \
	*D = *S;\
	*(D+1) = *(S+1);\
	D += PITCH_32;\
	S += PITCH_32;

#define FILL_8x1(D, C) \
	*D = C;\
	*(D+1) = C;\
	D += PITCH_32;

	inline static void FillLine2x1(byte* dst, byte src) {
		uint16 t = src << 8 | src;
		*((uint16*) dst) = t;
	}

	inline static void FillLine4x1(byte* dst, byte src) {
		uint32 t = src << 24 | src << 16 | src << 8 | src;
		uint32* d = (uint32*) dst;
		*d = t;
	}

	inline static void FillLine8x1(byte* dst, byte src) {
		uint32 t = src << 24 | src << 16 | src << 8 | src;
		uint32* d = (uint32*) dst;
		*d++ = t;
		*d = t;
	}

	inline static void CopyLine2x1(uint16* dst, uint16* src) {
		*((uint16*) dst) = *((uint16*) src);
	}

	inline static void CopyLine4x1(byte* dst, byte* src) {
		*((uint32*) dst) = *((uint32*) src);
	}

	inline static void CopyLine8x1(uint32* d, uint32* s) {
		*d++ = *s++;
		*d = *s;
	}

	static void decode_2x(uint16* dst, byte*& src, uint16* offset1, uint16* offset2, byte* params) {
		uint8 code = *src++;

		if (code < 0xF8) {
			// Note: Non-Aligned read! (tOff1)
			int32 t = smush_motion_vectors[code];
			uint16* tOff1 = (uint16*) (( (byte*) offset1) + t);

			*dst = *tOff1; // 1.
			dst += 320;
			tOff1 += 320;
			*dst = *tOff1; // 2.
		}
		else if (code == 0xFF) {
			*dst = * ((uint16*) src);
			src += 2;
			dst += 320;
			*dst = * ((uint16*) src);
			src += 2;
		}
		else if (code == 0xFE) {
			uint8 t = *src++;
			uint16 c = t << 8 | t;
			*dst = c;
			dst += 320;
			*dst = c;
		}
		else if (code == 0xFC) {
			*dst = *offset2;
			dst += 320;
			offset2 += 320;
			*dst = *offset2;
		}
		else {
			byte t = params[code - 0xF8];
			uint16 c = t << 8 | t;

			*dst = c;
			dst += 320;
			*dst = c;
		}
	}

	static void decode_4x(uint32* dst, byte*& src, uint32* offset1, uint32* offset2, byte* params) {
		uint8 code = *src++;

		if (code < 0xF8) {

			// Note: Non-Aligned read! (tOff1)
			int32 t = smush_motion_vectors[code];
			uint32* tOff1 = (uint32*) (( (byte*) offset1) + t);

			*dst = *tOff1;
			dst += 160;
			tOff1 += 160;
			*dst = *tOff1;
			dst += 160;
			tOff1 += 160;
			*dst = *tOff1;
			dst += 160;
			tOff1 += 160;
			*dst = *tOff1;
			dst += 160;
			tOff1 += 160;

		}
		else if (code == 0xFF) {

			uint16* dst_16 = (uint16*) dst;
			uint16* offset1_16 = (uint16*) offset1;
			uint16* offset2_16 = (uint16*) offset2;

			decode_2x(dst_16, src, offset1_16, offset2_16, params);
			dst_16++;
			offset1_16++;
			offset2_16++;
			decode_2x(dst_16, src, offset1_16, offset2_16, params);
			dst_16 += 639;		// P*2-1
			offset1_16 += 639;
			offset2_16 += 639;
			decode_2x(dst_16, src, offset1_16, offset2_16, params);
			dst_16++;
			offset1_16++;
			offset2_16++;
			decode_2x(dst_16, src, offset1_16, offset2_16, params);
		}
		else if (code == 0xFE) {
			uint8 t = *src++;
			uint32 c = t << 24 | t << 16 | t << 8 | t;

			*dst = c;
			dst += 160;
			*dst = c;
			dst += 160;
			*dst = c;
			dst += 160;
			*dst = c;

		}
		else if (code == 0xFD) {
			byte* bDst = (byte*) dst;
			int32 tmp = *src++;
			int32 tmpPtr = tmp * 128;
			byte len = smush_table_small[tmpPtr + 96];
			byte val = *src++;
			int32 tmpPtr2 = tmpPtr;

			while(len--) {
				uint16 m = READ_LE_UINT16(smush_table_small + tmpPtr2);
				if (m >= 32768) m -= 32768;
				*(bDst + m) = val;
				tmpPtr2 += 2;
			}

			len = smush_table_small[tmpPtr + 97];
			val = *src++;
			tmpPtr2 = tmpPtr + 32;
			while(len--) {
				uint16 m = READ_LE_UINT16(smush_table_small + tmpPtr2);
				if (m >= 32768) m -= 32768;
				*(bDst + m) = val;
				tmpPtr2 += 2;
			}

		}
		else if (code == 0xFC) {
			*dst = *offset2;
			dst += 160;
			offset2 += 160;
			*dst = *offset2;
			dst += 160;
			offset2 += 160;
			*dst = *offset2;
			dst += 160;
			offset2 += 160;
			*dst = *offset2;
		}
		else {
			byte t = params[code - 0xF8];
			uint32 c = t << 24 | t << 16 | t << 8 | t;

			*dst = c;
			dst += 160;
			*dst = c;
			dst += 160;
			*dst = c;
			dst += 160;
			*dst = c;
			dst += 160;
		}
	}

	static void decode_8x(uint32* dst, byte*& src, uint32* offset1, uint32* offset2, byte* params) {

		uint8 code = *src++;

		if (code < 0xF8) {
			int32 t = smush_motion_vectors[code];
			byte* tOff = ((byte*) offset1) + t;
			uint32* tOff32 = (uint32*) tOff;

			COPY_8x1(dst, tOff32); // 1.
			COPY_8x1(dst, tOff32); // 2.
			COPY_8x1(dst, tOff32); // 3.
			COPY_8x1(dst, tOff32); // 4.
			COPY_8x1(dst, tOff32); // 5.
			COPY_8x1(dst, tOff32); // 6.
			COPY_8x1(dst, tOff32); // 7.
			COPY_8x1(dst, tOff32); // 8.

		}
		else if (code == 0xFF) {
			decode_4x(dst, src, offset1, offset2, params);
			++dst;
			++offset1;
			++offset2;
			decode_4x(dst, src, offset1, offset2, params);
			dst += 639;		// P*4 - 1
			offset1 += 639;
			offset2 += 639;
			decode_4x(dst, src, offset1, offset2, params);
			++dst;
			++offset1;
			++offset2;
			decode_4x(dst, src, offset1, offset2, params);
		}
		else if (code == 0xFE) {
			uint8 t = *src++;
			uint32 c = t << 24 | t << 16 | t << 8 | t;

			FILL_8x1(dst, c); // 1.
			FILL_8x1(dst, c); // 2.
			FILL_8x1(dst, c); // 3.
			FILL_8x1(dst, c); // 4.
			FILL_8x1(dst, c); // 5.
			FILL_8x1(dst, c); // 6.
			FILL_8x1(dst, c); // 7.
			FILL_8x1(dst, c); // 8.

		}
		else if (code == 0xFD) {
			byte* bDst = (byte*) dst;
			byte tmp = *src++;
			int32 tmpPtr = ((int32) tmp) * 388;
			byte l = smush_table_big[tmpPtr + 384];
			byte val = *src++;
			int32 tmpPtr2 = tmpPtr;

			while(l--) {
				uint16 m = READ_LE_UINT16(smush_table_big + tmpPtr2);
				if (m >= 32768) m -= 32768;
				*(bDst + m) = val;
				tmpPtr2 += 2;
			}

			l = smush_table_big[tmpPtr + 385];
			val = *src++;
			tmpPtr2 = tmpPtr + 128;
			while(l--) {
				uint16 m = READ_LE_UINT16(smush_table_big + tmpPtr2);
				if (m >= 32768) m -= 32768;
				*(bDst + m) = val;
				tmpPtr2 += 2;
			}

		}
		else if (code == 0xFC) {
			COPY_8x1(dst, offset2); // 1.
			COPY_8x1(dst, offset2); // 2.
			COPY_8x1(dst, offset2); // 3.
			COPY_8x1(dst, offset2); // 4.
			COPY_8x1(dst, offset2); // 5.
			COPY_8x1(dst, offset2); // 6.
			COPY_8x1(dst, offset2); // 7.
			COPY_8x1(dst, offset2); // 8.
		}
		else {
			byte t = params[code - 0xF8];
			uint32 c = t << 24 | t << 16 | t << 8 | t;

			FILL_8x1(dst, c); // 1.
			FILL_8x1(dst, c); // 2.
			FILL_8x1(dst, c); // 3.
			FILL_8x1(dst, c); // 4.
			FILL_8x1(dst, c); // 5.
			FILL_8x1(dst, c); // 6.
			FILL_8x1(dst, c); // 7.
			FILL_8x1(dst, c); // 8.
		}

	}

	void smush_codec47_opt_ulong(uint32* dst, uint8* src, uint32* src1, uint32* src2, uint8* params) {
		uint8 bw = 80;
		uint8 bh = 60;
		const uint32 nextLine = PITCH_32 * 7;

		do
		{
			uint8 tmp_bw = bw;
			do
			{
				decode_8x(dst, src, src1, src2, params);
				dst += 2;
				src1 += 2;
				src2 += 2;
			} while ((--tmp_bw) != 0);

			dst += nextLine;
			src1 += nextLine;
			src2 += nextLine;

		} while ((--bh) != 0);

	}

}
