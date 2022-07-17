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

#ifndef GS_CODEC_H
#define GS_CODEC_H

#include "../types.h"
#include "../file.h"
#include "../disk.h"
#include "../room.h"	// For RoomPaletteData

namespace gs
{

	class Codec
	{
		DiskReader _diskReader;

		uint16 _frameCount;
		uint16 _frameNum;

		RoomPaletteData _palette;

		void _readAndApplyPalette();

	public:

		Codec(DiskReader reader);
		~Codec();

		int32 presentFrame();

	};

}

#endif