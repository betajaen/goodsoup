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

namespace gs
{
	static uint8 line[640];

	static uint8 rnd = 23;

	void drawStripComplex(SequentialReadSpanReader<byte, uint32> reader, uint32 width, uint32 height) {
		clearScreen(108); // TEMP

		const uint32 origin = reader.getPos();

		uint8 colour = reader.readInt8_unchecked();
		uint8 bits = reader.readInt8_unchecked();
		uint8 cl = 8;
		uint8* dst = &line[0];

		for (uint16 y=0;y < GS_SCREEN_HEIGHT;y++) {

			for(uint16 i=0;i < GS_SCREEN_WIDTH;i++) {
				line[i] = rnd++;
			}

			blitLine(y, &line[0]);
			

		}


	}

	void drawStrip(SequentialReadSpanReader<byte, uint32> reader, uint32 stripNum, uint32 width, uint32 height) {
		
		reader.skip_unchecked(stripNum * 4);
		const uint32 stripBegin = reader.readUint32LE_unchecked() - 8;

		reader.setPos_unchecked(stripBegin);

		uint8 code = reader.readUint8_unchecked();

		debug(GS_THIS, "Draw strip code %ld", (uint32) code);

		switch (code) {
			default:
				warn(GS_THIS, "Unsupported drawStrip#%ld functionality!", (uint32) code);
			return;
			case 108:
				drawStripComplex(reader, width, height);
			return;
		}

	}

	void drawRoomBackgroundSimple(ReadSpan<byte, uint32>& data, uint32 width, uint32 height) {

		if (data.getSize() == 0) {
			clearScreen(0);
			return;
		}

		drawStrip(SequentialReadSpanReader<byte, uint32>(data), 0, GS_SCREEN_WIDTH, GS_SCREEN_HEIGHT);
	}

}
