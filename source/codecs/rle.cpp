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

#define GS_FILE_NAME "rle"

#include "../types.h"
#include "../debug.h"
#include "../endian.h"
#include "rle.h"

namespace gs
{

	static byte* drawRLEimpl(byte* dst, uint32 dstPitch, byte* src, uint8 colour) {

		byte* d = dst;
		byte* nextLine = d + dstPitch;

		while(true) {
			int8 s = *src;
			src++;

			if (s == -128) {
				break;
			}

			else if (s == 0) {
				dst = nextLine;
				nextLine = dst + dstPitch;
			}

			else if (s < 0) {
				dst += -s;
			}

			else {
				while(s) {
					*dst = colour;
					dst++;
					s--;
				}
			}
		}

		return src;
	}

	void drawRLEImage1(uint16 x, uint16 y, const RLEImage1& info, byte* srcData, byte* dstData, uint16 dstPitch, uint8 colour) {

		uint8* d = dstData + x + (y * (uint32) dstPitch);

		drawRLEimpl(d, dstPitch, srcData + info._offset, colour);
	}

	void drawRLEImage2(uint16 x, uint16 y, const RLEImage2& info, byte* srcData, byte* dstData, uint16 dstPitch, uint8 colours[2]) {

		uint8* d = dstData + x + (y * (uint32) dstPitch);

		drawRLEimpl(d, dstPitch, srcData + info._offsets[0], colours[0]);
		drawRLEimpl(d, dstPitch, srcData + info._offsets[1], colours[1]);
	}

	void drawRLEImage3(uint16 x, uint16 y, const RLEImage3& info, byte* srcData, byte* dstData, uint16 dstPitch, uint8 colours[3]) {

		uint8* d = dstData + x + (y * (uint32) dstPitch);

		drawRLEimpl(d, dstPitch, srcData + info._offsets[0], colours[0]);
		drawRLEimpl(d, dstPitch, srcData + info._offsets[1], colours[1]);
		drawRLEimpl(d, dstPitch, srcData + info._offsets[2], colours[2]);
	}

	void drawRLEImage4(uint16 x, uint16 y, const RLEImage4& info, byte* srcData, byte* dstData, uint16 dstPitch, uint8 colours[4]) {

		uint8* d = dstData + x + (y * (uint32) dstPitch);

		drawRLEimpl(d, dstPitch, srcData + info._offsets[0], colours[0]);
		drawRLEimpl(d, dstPitch, srcData + info._offsets[1], colours[1]);
		drawRLEimpl(d, dstPitch, srcData + info._offsets[2], colours[2]);
		drawRLEimpl(d, dstPitch, srcData + info._offsets[3], colours[3]);
	}


	// Codes
	//  11 111111	- Stop
	//	00 00000N	- For N: Set Pixel(X,Y) to C, X++
	//  01 00000N   - X = 0,  Y = 0, C = N
	//  10 00000N   - X+=N, Y = Y
	//  11 00000N   - X= 0, Y += N

	void drawRLEImage64(uint16 x, uint16 y, const RLEImage64& img, byte* srcBegin, byte* dstData, uint16 dstPitch, uint8* colour) {

		uint8* origin = dstData + x + (y * (uint32) dstPitch);
		byte* src = srcBegin + (uint32) img._offset;
		byte* nextLine = origin + dstPitch;
		byte* dst = origin;
		byte code, op, value;
		uint8 col = colour[0];

		while(true) {
			code = *src;
			src++;

			if (code == 0xFF) {
				break;
			}

			op = code & 0xC0;
			value = code & 0x3F;

			switch(op) {
				case 0x00: { // 00
					while(value--) {
						*dst = col;
						dst++;
					}
				}
				continue;
				case 0x40: { // 01
					col = colour[value];
					dst = origin;
					nextLine = origin + dstPitch;
				}
				continue;
				case 0x80: { // 10
					dst += value;
				}
				continue;
				case 0xC0: { // 11
					while(value--) {
						dst = nextLine;
						nextLine = dst + dstPitch;
					}
				}
				continue;
			}
		}

	}

}
