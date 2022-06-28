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

#define GS_FILE_NAME "file"

#include "cursor_amiga.h"

#include <proto/intuition.h>
#include <proto/graphics.h>
#include <graphics/sprite.h>

namespace gs {

	struct AmigaCursor
	{
		int16  _offsetX, _offsetY;
		uint16 _height;
		uint16 _data[2 * 24];
	};

}

__chip struct gs::AmigaCursor GS_AMIGA_CURSOR[] = {
  {
	-7,-7,15,
	{
		0x0000,0x0000,
		0x380 ,0x0   ,
		0x280 ,0x100 ,
		0x280 ,0x100 ,
		0x280 ,0x100 ,
		0x380 ,0x0   ,
		0x0   ,0x0   ,
		0xf83e,0x0   ,
		0x8822,0x701c,
		0xf83e,0x0   ,
		0x0   ,0x0   ,
		0x380 ,0x0   ,
		0x280 ,0x100 ,
		0x280 ,0x100 ,
		0x280 ,0x100 ,
		0x380 ,0x0   ,
		0x0000,0x0000
	}
  },
  {
	-7, -7, 15,
	{
	  0x0000,0x0000,
	  0xfff0,0x0   ,
	  0x9058,0x6fa0,
	  0x9148,0x6eb0,
	  0x9148,0x6eb0,
	  0x9048,0x6fb0,
	  0x9fc8,0x6030,
	  0x8008,0x7ff0,
	  0x9fc8,0x6030,
	  0xa028,0x5fd0,
	  0xafa8,0x5050,
	  0xa028,0x5fd0,
	  0xa028,0x5fd0,
	  0xfff8,0x0   ,
	  0x0000,0x0000
	}
  }
};

namespace gs
{

	struct SimpleSprite sCursorSprite;
	uint16 sCursorSpriteNum;
	struct Window* sCursorWindow;
	
	void setCursor(uint8 kind) {
		
		SetPointer(sCursorWindow, 
			&GS_AMIGA_CURSOR[kind]._data[0], 
			16, GS_AMIGA_CURSOR[kind]._height, 
			GS_AMIGA_CURSOR[kind]._offsetX, 
			GS_AMIGA_CURSOR[kind]._offsetY);
	}

	void openAmigaCursor(struct Window* window) {
		sCursorWindow = window;
		setCursor(0);
	}

	void closeAmigaCursor() {

	}

}
