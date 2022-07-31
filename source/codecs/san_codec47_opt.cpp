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
#if GS_SAN_CODEC47 == 2

#define GS_FILE_NAME "san_codec44_opt"

#include "../types.h"
#include "../endian.h"

#define PITCH_32 160 /* (640 / sizeof(uint32)) */
#define PITCH_16 320 /* (640 / sizeof(uint16)) */

namespace gs
{

	extern int16 SAN47_MOTION_VECTORS[256];
	extern byte* SAN_TABLE_BIG;
	extern byte* SAN_TABLE_SMALL;

#define COPY_2x1(D, S) \
	*D = *S;\
	D += PITCH_16;\
	S += PITCH_16;

#define FILL_2x1(D, C) \
	*D = C;\
	D += PITCH_16;

#define COPY_4x1(D, S) \
	*D = *S;\
	D += PITCH_32;\
	S += PITCH_32;

#define FILL_4x1(D, C) \
	*D = C;\
	D += PITCH_32;

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
#if 0
			int32 t = SAN47_MOTION_VECTORS[code];
			uint16* motionSrc = (uint16*)(((byte*) offset1) + t);

			COPY_2x1(dst, motionSrc); // 1.
			COPY_2x1(dst, motionSrc); // 2.
#else
			int16 t = SAN47_MOTION_VECTORS[code];
			// 1.
			CopyLine2x1(dst, (uint16*) ((byte*)offset1) + t);
			dst += PITCH_16;
			offset1 += PITCH_16;
			// 2.
			CopyLine2x1(dst, (uint16*) ((byte*)offset1) + t);
#endif
		}
		else if (code == 0xFF) {
#if 1

			*dst = * ((uint16*) src);
			src += 2;
			dst += PITCH_16;
			*dst = * ((uint16*) src);
			src += 2;
#else
			CopyLine2x1(dst, (uint16*) src);
			dst++;
			CopyLine2x1(dst, (uint16*) (src + 2));
			src += 4;
#endif
		}
		else if (code == 0xFE) {
			uint8 t = *src++;
			uint16 c = t;
			c <<= 8;
			c |= t;

			FILL_2x1(dst, c); // 1.
			FILL_2x1(dst, c); // 2.
		}
		else if (code == 0xFC) {
			*dst = *offset2;
			dst += PITCH_16;
			offset2 += PITCH_16;
			*dst = *offset2;
		}
		else {
			byte t = params[code - 0xF8];
			uint16 c = t << 8 | t;

			FILL_2x1(dst, c); // 1.
			FILL_2x1(dst, c); // 2.
		}
	}

	static void decode_4x(uint32* dst, byte*& src, uint32* offset1, uint32* offset2, byte* params) {
		uint8 code = *src++;

		if (code < 0xF8) {
			int32 t = SAN47_MOTION_VECTORS[code];
			uint32* motionSrc = (uint32*)(((byte*) offset1) + t);

			COPY_4x1(dst, motionSrc); // 1.
			COPY_4x1(dst, motionSrc); // 2.
			COPY_4x1(dst, motionSrc); // 3.
			COPY_4x1(dst, motionSrc); // 4.
		}
		else if (code == 0xFF) {
			
			uint16* dst_16 = (uint16*) dst;
			uint16* offset1_16 = (uint16*) offset1;
			uint16* offset2_16 = (uint16*) offset2;
			
			decode_2x(dst_16, src, offset1_16, offset2_16, params);
			dst_16++;
			offset1_16++;
			offset2_16++;
			decode_2x((uint16*) dst, src, (uint16*) offset1, (uint16*) offset2, params);
			dst_16 += 639;
			offset1_16 += 639;
			offset2_16 += 639;
			decode_2x((uint16*) dst, src, (uint16*) offset1, (uint16*) offset2, params);
			dst_16++;
			offset1_16++;
			offset2_16++;
			decode_2x((uint16*) dst, src, (uint16*) offset1, (uint16*) offset2, params);
		}
		else if (code == 0xFE) {
			uint8 t = *src++;
			uint32 c = t << 24 | t << 16 | t << 8 | t;

			FILL_4x1(dst, c); // 1.
			FILL_4x1(dst, c); // 2.
			FILL_4x1(dst, c); // 3.
			FILL_4x1(dst, c); // 4.
		}
		else if (code == 0xFD) {
			byte* bDst = (byte*) dst;
			int32 tmp = *src++;
			int32 tmpPtr = tmp * 128;
			byte len = SAN_TABLE_SMALL[tmpPtr + 96];
			byte val = *src++;
			int32 tmpPtr2 = tmpPtr;

			while(len--) {
				int16 m = READ_LE_INT16(SAN_TABLE_SMALL + tmpPtr2);
				*(bDst + m) = val;
				tmpPtr2 += 2;
			}

			len = SAN_TABLE_SMALL[tmpPtr + 97];
			val = *src++;
			tmpPtr2 = tmpPtr + 32;
			while(len--) {
				int16 m = READ_LE_INT16(SAN_TABLE_SMALL + tmpPtr2);
				*(bDst + m) = val;
				tmpPtr2 += 2;
			}

		}
		else if (code == 0xFC) {
			COPY_4x1(dst, offset2); // 1.
			COPY_4x1(dst, offset2); // 2.
			COPY_4x1(dst, offset2); // 3.
			COPY_4x1(dst, offset2); // 4.
		}
		else {
			byte t = params[code - 0xF8];
			uint32 c = t << 24 | t << 16 | t << 8 | t;

			FILL_4x1(dst, c); // 1.
			FILL_4x1(dst, c); // 2.
			FILL_4x1(dst, c); // 3.
			FILL_4x1(dst, c); // 4.
		}
	}

	static void decode_8x(uint32* dst, byte*& src, uint32* offset1, uint32* offset2, byte* params) {

		uint8 code = *src++;

		if (code < 0xF8) {

			int32 t = SAN47_MOTION_VECTORS[code];

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
			dst += 639;
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
			uint32 c = t;
			c <<= 8;
			c |= t;
			c <<= 8;
			c |= t;
			c <<= 8;
			c |= t;

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
			byte l = SAN_TABLE_BIG[tmpPtr + 384];
			byte val = *src++;
			int32 tmpPtr2 = tmpPtr;

			while(l--) {
				int16 m = READ_LE_INT16(SAN_TABLE_BIG + tmpPtr2);
				*(bDst + m) = val;
				tmpPtr2 += 2;
			}

			l = SAN_TABLE_BIG[tmpPtr + 385];
			val = *src++;
			tmpPtr2 = tmpPtr + 128;
			while(l--) {
				int16 m = READ_LE_INT16(SAN_TABLE_BIG + tmpPtr2);
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
			uint32 c = t;
			c <<= 8;
			c |= t;
			c <<= 8;
			c |= t;
			c <<= 8;
			c |= t;

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

	void san_codec47_decode_opt(byte* dst, byte* src, byte* offset1, byte* offset2, byte* params) {

		uint8 bw = 80;
		uint8 bh = 60;
		const uint32 nextLine = PITCH_32 * 7;

		uint32* current = (uint32*) dst;
		uint32* off1 = (uint32*) offset1;
		uint32* off2 = (uint32*) offset2;
		do
		{
			uint8 tmp_bw = bw;
			do
			{
				decode_8x(current, src, off1, off2, params);
				current += 2;
				off1 += 2;
				off2 += 2;
			} while ((--tmp_bw) != 0);

			current += nextLine;
			off1 += nextLine;
			off2 += nextLine;

		} while ((--bh) != 0);

	}

}
#endif
