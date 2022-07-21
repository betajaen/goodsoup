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

#ifndef GS_RLE_H
#define GS_RLE_H

#include "../types.h"

namespace gs
{

	struct RLEImage1 {
		uint8  _width, _height;
		uint32 _offset;
	};

	struct RLEImage2 {
		uint8  _width, _height;
		uint32 _offsets[2];
	};

	struct RLEImage3 {
		uint8  _width, _height;
		uint32 _offsets[3];
	};

	struct RLEImage4 {
		uint8  _width, _height;
		uint32 _offsets[4];
	};

	void drawRLEImage1(uint32 x, uint32 y, const RLEImage1& info, byte* srcData, byte* dstData, uint32 dstPitch, uint8 colour);
	void drawRLEImage2(uint32 x, uint32 y, const RLEImage2& info, byte* srcData, byte* dstData, uint32 dstPitch, uint8 colour[2]);
	void drawRLEImage3(uint32 x, uint32 y, const RLEImage3& info, byte* srcData, byte* dstData, uint32 dstPitch, uint8 colour[3]);
	void drawRLEImage4(uint32 x, uint32 y, const RLEImage4& info, byte* srcData, byte* dstData, uint32 dstPitch, uint8 colour[4]);
}


#endif
