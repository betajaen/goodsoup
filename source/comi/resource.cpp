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

#define GS_FILE_NAME "resource"

#include "resource.h"
#include "index.h"

#include "debug.h"
#include "constants.h"

using namespace common;

namespace comi
{

	Resources* RESOURCES = NULL;

	Resources::Resources() {
	}

	Resources::~Resources() {
		close();
	}

	void Resources::close() {
		uint16 i;

		for (i = 0; i < NUM_DISKS; i++) {
			_disk[i].close();
		}
	}

	bool Resources::open() {
		uint16 i;

		for (i = 0; i < NUM_DISKS; i++) {
			uint32 diskNum = 1 + i;

			verbose(COMI_THIS, "Building path for Disk %ld", diskNum);
			String path;
			String::format(path, "%sCOMI.LA%ld", GS_GAME_PATH, diskNum);
			verbose(COMI_THIS, "Opening Disk %ld at %s", diskNum, path.string());
			_disk[i].open(path.string());

			if (_disk[i].isOpen() == false)
				return false;
			info(COMI_THIS, "Opened Disk %ld at %s", diskNum, path.string());
		}

		return true;
	}

}
