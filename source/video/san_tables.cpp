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

#define GS_FILE_NAME "codec"

#include "san_codec.h"
#include "../screen.h"
#include "../codecs/bomp.h"
#include "../font.h"
#include "../memory.h"

namespace gs
{

	static const int8 CODEC47_TABLE[] =
			{
					0,   0,  -1, -43,   6, -43,  -9, -42,  13, -41,
					-16, -40,  19, -39, -23, -36,  26, -34,  -2, -33,
					4, -33, -29, -32,  -9, -32,  11, -31, -16, -29,
					32, -29,  18, -28, -34, -26, -22, -25,  -1, -25,
					3, -25,  -7, -24,   8, -24,  24, -23,  36, -23,
					-12, -22,  13, -21, -38, -20,   0, -20, -27, -19,
					-4, -19,   4, -19, -17, -18,  -8, -17,   8, -17,
					18, -17,  28, -17,  39, -17, -12, -15,  12, -15,
					-21, -14,  -1, -14,   1, -14, -41, -13,  -5, -13,
					5, -13,  21, -13, -31, -12, -15, -11,  -8, -11,
					8, -11,  15, -11,  -2, -10,   1, -10,  31, -10,
					-23,  -9, -11,  -9,  -5,  -9,   4,  -9,  11,  -9,
					42,  -9,   6,  -8,  24,  -8, -18,  -7,  -7,  -7,
					-3,  -7,  -1,  -7,   2,  -7,  18,  -7, -43,  -6,
					-13,  -6,  -4,  -6,   4,  -6,   8,  -6, -33,  -5,
					-9,  -5,  -2,  -5,   0,  -5,   2,  -5,   5,  -5,
					13,  -5, -25,  -4,  -6,  -4,  -3,  -4,   3,  -4,
					9,  -4, -19,  -3,  -7,  -3,  -4,  -3,  -2,  -3,
					-1,  -3,   0,  -3,   1,  -3,   2,  -3,   4,  -3,
					6,  -3,  33,  -3, -14,  -2, -10,  -2,  -5,  -2,
					-3,  -2,  -2,  -2,  -1,  -2,   0,  -2,   1,  -2,
					2,  -2,   3,  -2,   5,  -2,   7,  -2,  14,  -2,
					19,  -2,  25,  -2,  43,  -2,  -7,  -1,  -3,  -1,
					-2,  -1,  -1,  -1,   0,  -1,   1,  -1,   2,  -1,
					3,  -1,  10,  -1,  -5,   0,  -3,   0,  -2,   0,
					-1,   0,   1,   0,   2,   0,   3,   0,   5,   0,
					7,   0, -10,   1,  -7,   1,  -3,   1,  -2,   1,
					-1,   1,   0,   1,   1,   1,   2,   1,   3,   1,
					-43,   2, -25,   2, -19,   2, -14,   2,  -5,   2,
					-3,   2,  -2,   2,  -1,   2,   0,   2,   1,   2,
					2,   2,   3,   2,   5,   2,   7,   2,  10,   2,
					14,   2, -33,   3,  -6,   3,  -4,   3,  -2,   3,
					-1,   3,   0,   3,   1,   3,   2,   3,   4,   3,
					19,   3,  -9,   4,  -3,   4,   3,   4,   7,   4,
					25,   4, -13,   5,  -5,   5,  -2,   5,   0,   5,
					2,   5,   5,   5,   9,   5,  33,   5,  -8,   6,
					-4,   6,   4,   6,  13,   6,  43,   6, -18,   7,
					-2,   7,   0,   7,   2,   7,   7,   7,  18,   7,
					-24,   8,  -6,   8, -42,   9, -11,   9,  -4,   9,
					5,   9,  11,   9,  23,   9, -31,  10,  -1,  10,
					2,  10, -15,  11,  -8,  11,   8,  11,  15,  11,
					31,  12, -21,  13,  -5,  13,   5,  13,  41,  13,
					-1,  14,   1,  14,  21,  14, -12,  15,  12,  15,
					-39,  17, -28,  17, -18,  17,  -8,  17,   8,  17,
					17,  18,  -4,  19,   0,  19,   4,  19,  27,  19,
					38,  20, -13,  21,  12,  22, -36,  23, -24,  23,
					-8,  24,   7,  24,  -3,  25,   1,  25,  22,  25,
					34,  26, -18,  28, -32,  29,  16,  29, -11,  31,
					9,  32,  29,  32,  -4,  33,   2,  33, -26,  34,
					23,  36, -19,  39,  16,  40, -13,  41,   9,  42,
					-6,  43,   1,  43,   0,   0,   0,   0,   0,   0
			};

	int16 TABLE[256] = { 0 };
	byte TABLE_BIG[256 * 388] = { 0 };
	byte TABLE_SMALL[256 * 128] = { 0 };
	static bool hasInitTable = false;


	void initTable() {

		if (hasInitTable)
			return;

		for (uint16 j =0; j < 510; j += 2) {
			TABLE[j / 2] = (int16)(CODEC47_TABLE[j + 1] * GS_SCREEN_WIDTH + CODEC47_TABLE[j]);
		}
	}



}
