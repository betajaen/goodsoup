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
#include "disk.h"
#include "resource_object.h"
#include "room.h"
#include "script.h"
#include "disk.h"

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

		for (i = 0; i < _resources.size(); i++) {
			ResourceObject* resource = _resources[i];

			switch (resource->getResourceKind()) {
				case RK_ROOM: {
					deleteObject_unchecked<Room>((Room*)resource);
					continue;
				}
				case RK_SCRIPT: {
					deleteObject_unchecked<Script>((Script*)resource);
					continue;
				}
			}
		}

		_resources.release();

	}

	bool Resources::open() {
		uint16 i;

		for (i = 0; i < NUM_DISKS; i++) {
			uint32 diskNum = 1 + i;

			Disk& disk = _disk[i];
			if (disk.open(1 + i) == false)
				return false;
		}

		return true;
	}

	Script* Resources::loadScript(uint16 num)
	{
		/* TODO */
		return NULL;
	}

	Room* Resources::loadRoom(uint16 num)
	{
		/* TODO */
		return NULL;
	}


}
