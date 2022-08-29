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

#define GS_FILE_NAME "draw"

#include "draw.h"
#include "room.h"
#include "screen.h"

namespace gs
{
	uint8 DRAW_FLAGS = 0;

	void drawRoomBackground(RoomData* roomData, uint8 backgroundNum) {
		DRAW_FLAGS &= DF_BackgroundChanged;

		ReadSpan<byte, uint32> backgroundData = roomData->getBackground(0);
		if (backgroundData.getSize() > 0) {
			screenBlitRoomBackground(backgroundData, 640, 480); // TEMP.
		}
	}

	void drawSetPalette(RoomData* roomData, uint8 paletteNum) {
		DRAW_FLAGS &= DF_PaletteChanged;

		RoomPaletteData* palette = roomData->getPalette(paletteNum);

		if (palette) {
			screenSetPalette(palette);
		}
	}

	void drawScalePalette(uint8 from, uint8 to, uint8 redScale, uint8 greenScale, uint8 blueScale) {

		DRAW_FLAGS &= DF_PaletteChanged;

		screenScalePalette(from, to, redScale, greenScale, blueScale);

	}


}
