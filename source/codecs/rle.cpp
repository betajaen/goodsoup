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

	void drawRLEImage1(uint32 x, uint32 y, const RLEImage1& info, byte* srcData, byte* dstData, uint32 dstPitch, uint8 colour) {

		uint8* d = dstData + x + (y * dstPitch);

		drawRLEimpl(d, dstPitch, srcData + info._offset, colour);
	}

	void drawRLEImage2(uint32 x, uint32 y, const RLEImage2& info, byte* srcData, byte* dstData, uint32 dstPitch, uint8 colours[2]) {

		uint8* d = dstData + x + (y * dstPitch);

		drawRLEimpl(d, dstPitch, srcData + info._offsets[0], colours[0]);
		drawRLEimpl(d, dstPitch, srcData + info._offsets[1], colours[1]);
	}

	void drawRLEImage3(uint32 x, uint32 y, const RLEImage3& info, byte* srcData, byte* dstData, uint32 dstPitch, uint8 colours[3]) {

		uint8* d = dstData + x + (y * dstPitch);

		drawRLEimpl(d, dstPitch, srcData + info._offsets[0], colours[0]);
		drawRLEimpl(d, dstPitch, srcData + info._offsets[1], colours[1]);
		drawRLEimpl(d, dstPitch, srcData + info._offsets[2], colours[2]);
	}

	void drawRLEImage4(uint32 x, uint32 y, const RLEImage4& info, byte* srcData, byte* dstData, uint32 dstPitch, uint8 colours[4]) {

		uint8* d = dstData + x + (y * dstPitch);

		drawRLEimpl(d, dstPitch, srcData + info._offsets[0], colours[0]);
		drawRLEimpl(d, dstPitch, srcData + info._offsets[1], colours[1]);
		drawRLEimpl(d, dstPitch, srcData + info._offsets[2], colours[2]);
		drawRLEimpl(d, dstPitch, srcData + info._offsets[3], colours[3]);
	}

}
