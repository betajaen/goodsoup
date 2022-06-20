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

#ifndef COMI_ROOM_H
#define COMI_ROOM_H

#include "common/types.h"
#include "common/array.h"
#include "common/buffer.h"
#include "resource_data.h"

using namespace common;

namespace comi
{
#define MAX_ROOM_PALETTES 8

	class DiskReader;

	struct ColourCycle
	{
		uint16 delay;
		uint16 counter;
		uint16 flags;
		uint8  start;
		uint8 end;
	};

	struct RoomPalette {
		uint8 palette[3 * 256];
	};

	class RoomData : public ResourceData
	{
		bool _readLFLF(DiskReader& reader);
		bool _readRoom(DiskReader& reader, uint32 totalLength);
		void _readRMHD(DiskReader& reader, uint32 tagLength);
		void _readCYCL(DiskReader& reader, uint32 tagLength);
		bool _readPALS(DiskReader& reader, uint32 tagLength);
		void _readAPAL(DiskReader& reader, RoomPalette& pal);

	public:

		RoomData(uint16 num, uint8 disk, uint8 flags);
		~RoomData();

		uint16 width, height, numObjects, numZBuffers;
		Buffer<byte> entryScript;
		Buffer<byte> exitScript;
		Buffer<byte> localScript;
		FixedArray<ColourCycle, 16> colourCycle;
		uint16 numPalOffs;
		FixedArray<uint32, MAX_ROOM_PALETTES> palOffs;
		FixedArray<RoomPalette, MAX_ROOM_PALETTES> palettes;

		bool readFromDisk(DiskReader& reader);
		
	};

}

#endif