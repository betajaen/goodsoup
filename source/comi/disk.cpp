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

#define GS_FILE_NAME "disk"

#include "resource.h"
#include "index.h"
#include "resource_object.h"
#include "room.h"
#include "script.h"

#include "debug.h"
#include "constants.h"

using namespace common;

namespace comi
{

	Disk::Disk() {
	}

	Disk::~Disk() {
		close();
	}

	bool Disk::open(uint8 num) {
		
		verbose(COMI_THIS, "Building path for Disk %ld", num);
		String path;
		String::format(path, "%sCOMI.LA%ld", GS_GAME_PATH, num);
		verbose(COMI_THIS, "Opening Disk %ld at %s", num, path.string());
		_file.open(path.string());

		if (_file.isOpen() == false)
			return false;
	
		info(COMI_THIS, "Opened Disk %ld at %s", num, path.string());
	
		// Read Room Offsets and other bits

		/* TODO */

		return true;
	}

	void Disk::close() {
		_file.close();
		_roomOffsets.release();
	}

}
