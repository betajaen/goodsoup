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

#ifndef GS_DRAW_H
#define GS_DRAW_H

#include "types.h"

namespace gs
{
	class RoomData;

	enum DrawFlags {
		DF_NoChanges = 0,
		DF_TotalChange = (1 << 0),
		DF_BackgroundChanged = (1 << 1),
		DF_CameraMoved = (1 << 2),
		DF_ActorChanged = (1 << 3),
		DF_PaletteChanged = (1 << 4)
	};

	extern uint8 DRAW_FLAGS;

	void drawRoomBackground(RoomData* roomData, uint8 backgroundNum);
	void drawSetPalette(RoomData* roomData, uint8 paletteNum);
	void drawScalePalette(uint8 from, uint8 to, uint8 redScale, uint8 greenScale, uint8 blueScale);

}

#endif