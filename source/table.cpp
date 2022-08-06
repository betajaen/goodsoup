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

#define GS_FILE_NAME "table"

#include "memory.h"
#include "file.h"
#include "debug.h"

namespace gs
{

	byte* TABLE_DARKEN_PALETTE = NULL;

	bool readTable(const char* path, uint32 size, byte*& table) {
		table = (byte*) allocateMemory(1, size, 0, GS_COMMENT_FILE_LINE);

		ReadFile file;
		file.open(path);

#if GS_CHECKED == 1
		if (file.isOpen() == false) {
			error(GS_THIS, "Could not open table %s", path);
			return false;
		}
#endif

		file.readBytes(table, size);
		file.close();

		return true;
	}


	bool openTables() {
		if (readTable(GS_GAME_PATH "DPL.GST", 65536, TABLE_DARKEN_PALETTE) == false)
			return false;

		return true;
	}

	void closeTables() {
		releaseMemoryChecked(TABLE_DARKEN_PALETTE);
	}

}
