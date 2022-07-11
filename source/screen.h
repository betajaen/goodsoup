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

#ifndef GS_SCREEN_H
#define GS_SCREEN_H

#include "types.h"
#include "buffer.h"

namespace gs
{
	class RoomData;
	struct RoomPaletteData;

	bool openScreen();
	bool closeScreen();
	void screenLoop();
	void setScreenPalette(uint8* palette, uint8 from = 0, uint8 to = 255);
	void scaleScreenPalette(uint8 from, uint8 to, uint8 redScale, uint8 greenScale, uint8 blueScale);
	void resetScreenPalette();

	void drawSystemText(uint8 colour, uint16 x, uint16 y, const char* text);
	void drawSystemTextF(uint8 colour, uint16 x, uint16 y, const char* fmt, ...);
	void clearScreen(uint8 colour);
	void drawBox(uint8 colour, uint16 x, uint16 y, uint16 w, uint16 h);
	void setRoomPalette(RoomPaletteData* palette);
	void blitBitmap(uint32 x, uint32 y, uint32 w, uint32 h, uint32 len, byte*);
	void blitLine(uint16 y, byte* lineData);
	void blitCopyBitmap(byte* bitmap);
	void drawRoomBackgroundSimple(ReadSpan<byte, uint32>& data, uint32 width, uint32 height);
}

#endif