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

#define GS_FILE_NAME "screen"

#include "screen.h"
#include "room.h"
#include "profile.h"


namespace gs
{
	static uint8 screen[640*480];

	static uint8 rnd = 23;

#define READ_BIT (cl--, bit = bits & 1, bits >>= 1, bit)
#define FILL_BITS do {              \
		if (cl <= 8) {              \
			bits |= (reader.readUint8_unchecked() << cl); \
			cl += 8;                \
		}                           \
	} while (0)
#define FETCH_BYTE reader.readUint8_unchecked()

	static uint8 transparentColour = 5;	// TODO
	static bool transparentCheck = false;

	void drawStripBasicV(SequentialReadSpanReader<byte, uint32> reader, uint8* dst, uint32 height, uint8 decompMask, uint8 decompShift) {
		
		uint8 colour = FETCH_BYTE;
		uint32 bits = FETCH_BYTE;
		uint8 cl = 8;
		uint8 bit;
		int8 inc = -1;
		
		int16 x = 8;
		do {
			int16 h = height;
			do {

				FILL_BITS;

				if (!transparentCheck || colour != transparentColour) {					
					*dst = colour; // Temp.
				}
				dst += GS_BITMAP_PITCH;

				if (!READ_BIT) {
				}
				else if (!READ_BIT) {
					FILL_BITS;
					colour = (bits & decompMask);
					bits >>= decompShift;
					cl -= decompShift;
					inc = -1;
				}
				else if (!READ_BIT) {
					colour += inc;
				}
				else {
					inc = -inc;
					colour += inc;
				}

			} while((--h) != 0);
			dst -= (GS_BITMAP_ROWS * GS_BITMAP_PITCH) - 1;
		} while((--x) != 0);

	}

	void drawStripComplex(SequentialReadSpanReader<byte, uint32> reader, uint8* dst, uint32 height, uint8 decompMask, uint8 decompShift) {
		
		uint8 colour = FETCH_BYTE;
		uint32 bits = FETCH_BYTE;
		uint8 cl = 8;
		uint8 bit;
		uint8 incm, reps;

		debug(GS_THIS, "colour = %ld, bits = %ld", (uint32) colour, (uint32) bits);

		do {
			
			int16 x = 8;

			do {

				FILL_BITS;
				if (!transparentCheck || colour != transparentColour)
					*dst = colour;
				dst++;

			againPos:

				if (!READ_BIT) {
				}
				else if (!READ_BIT) {
					FILL_BITS;
					colour = bits  & decompMask;
					bits >>= decompShift;
					cl -= decompShift;
				}
				else {
					incm = (bits & 7) - 4;
					cl -= 3;
					bits >>= 3;

					if (incm != 0) {
						colour += incm;
					}
					else {
						FILL_BITS;
						reps = (bits & 0xFF);

						do {

							if (!(--x)) {

								x = 8;
								dst += GS_BITMAP_PITCH - 8;
								if (!(--height)) {
									return;
								}
							}
							
							if (!transparentCheck || colour != transparentColour)
								*dst = colour; // Temp.

							dst++;
						} while ((--reps) != 0);
						bits >>= 8;
						bits |= FETCH_BYTE << (cl - 8);
						goto againPos;
					}
				}
			} while((--x) != 0);

			dst += GS_BITMAP_PITCH - 8;

		} while((--height) != 0);
		
	}

	void drawStrip(SequentialReadSpanReader<byte, uint32> reader, uint8* dst, uint32 stripNum, uint32 height) {
		
		reader.skip_unchecked(stripNum * 4);
		const uint32 stripBegin = reader.readUint32LE_unchecked() - 8;

		reader.setPos_unchecked(stripBegin);

		uint8 code = reader.readUint8_unchecked();

		switch (code) {
			default:
				warn(GS_THIS, "Unsupported drawStrip#%ld functionality!", (uint32) code);
			return;
			case 18:
				transparentCheck = false;
				drawStripBasicV(reader, dst, height, 255, 8);
			return;
			case 108:
				transparentCheck = true;
				drawStripComplex(reader, dst, height, 255, 8);
			return;
		}

	}

	void drawRoomBackgroundSimple(ReadSpan<byte, uint32>& imageData, uint32 width, uint32 height) {
		
		clearScreen(0);
		
		if (imageData.getSize() == 0) {
			return;
		}

		uint16 x = 0;
		const uint16 numStrips = GS_SCREEN_WIDTH / 8;
		uint8* dst = &screen[0];

		/* TODO: calculate actual number of strips*/
		/* TODO: calculate strip origin */
		
		SequentialReadSpanReader<byte, uint32> reader(imageData);
		for (uint16 stripNum = 0; stripNum < numStrips; stripNum++, x++) {
			
			dst = &screen[x * 8];
			reader.setPos_unchecked(x * 8);
			transparentCheck = true;
			drawStrip(imageData, dst, stripNum, GS_BITMAP_ROWS);

		}
		
		blitCopyBitmap(&screen[0]);
	}

}
