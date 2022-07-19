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

#ifndef GS_FONT_H
#define GS_FONT_H

#include "types.h"
#include "buffer.h"
#include "disk.h"

namespace gs
{

	struct FontChar
	{
		uint16  _width, _height;
		uint8  _bTransparent;
		uint8  _reserved;
		uint32 _offset;
	};

	class Font
	{
		uint16               _numChars;
		Buffer<byte, uint32> _data;
		FontChar 	 		 _chars[256];

		void _readNutFont(DiskReader reader);

	public:

		Font(uint8 id);
		~Font();

		void drawText(uint32 x, uint32 y, const char* text);
	};

	extern Font* FONT0;

}

#endif