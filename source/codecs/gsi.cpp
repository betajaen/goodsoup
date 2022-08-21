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

#define GS_FILE_NAME "gsi"

#include "forward.h"
#include "file.h"
#include "index.h"
#include "profile.h"

namespace gs
{

	#define HEADER_BIG "GSIb"
	#define HEADER_LITTLE "GSIl"

	bool readGSI(TagReadFile* file, Index* index) {
		return false;
	}


	template<bool isBigEndian>
	static void writeRoomDisks_endian(EndianWriteFile<isBigEndian>& file, Index* index) {

		file.writeTag("ROOM");
		file.writeUInt32(NUM_ROOMS + NUM_ROOMS * sizeof(uint32));
		file.writeBytes(index->_roomDisks, NUM_ROOMS);
		uint8 count = NUM_ROOMS;
		uint32* offset = &index->_roomOffsets[0];
		while(count--) {
			file.writeUInt32(*offset++);
		}
	}

	template<bool isBigEndian>
	static bool writeGSI_endian(EndianWriteFile<isBigEndian>& file, Index* index) {

		uint16 count;
		uint32* offset;

		if (isBigEndian) {
			file.writeBytes(HEADER_BIG, 4);
		}
		else {
			file.writeBytes(HEADER_LITTLE, 4);
		}

		file.writeBytes(GS_GAME_FOURCC, 4);
		file.writeUInt32(0);	// Future. Game Revision, Type, or Language code.

		// LFLF - Implements DROO and DRSC
		// These are the Disk number, and the Offset to the LFLF in LA0, and LA1 files
		file.writeTag("LFLF");
		file.writeUInt16(NUM_ROOMS);
		file.writeBytes(index->_roomDisks, NUM_ROOMS);
		count = NUM_ROOMS;
		offset = &index->_roomScriptOffsets[0];
		while(count--) {
			file.writeUInt32(*offset++);
		}

		// SCRP - Pointers to SCRP tags which are inside ROOM tags of a Disk.
		// These are the Room number, and offset to the SCRP tags in inside LFLF which are in LA0 and LA1 files
		// A room may have multiple SCRP tags, hence NUM_SCRIPTS != NUM_ROOMS
		file.writeTag("SCRP");
		file.writeUInt16(NUM_SCRIPTS);

		// This is different to LA0. We store the DISK Number, where as the LA0 stores the ROOM Number. LA0
		// calculates these after the load to save an additional memory lookup, we cache it here to prevent the
		// calculation.
		file.writeBytes(index->_scriptDisk, NUM_SCRIPTS);
		// This is also different to LA0. LA0 stores an offset relative to the LFLF offset, which requires
		// a calculation each time. The LA0 will now pre-calculate these on load, and here we cache it to prevent
		// a calculation on load.
		file.writeBytes(index->_scriptDiskOffset, sizeof(uint32) * NUM_SCRIPTS);

		return true;
	}



	bool writeGSI(WriteFile* file, Index* index, bool isBigEndian) {

		if (isBigEndian) {
			EndianWriteFile<true> ef(file);
			return writeGSI_endian<true>(ef, index);
		}
		else {
			EndianWriteFile<false> ef(file);
			return writeGSI_endian<false>(ef, index);
		}

	}

}
