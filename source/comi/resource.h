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

#ifndef COMI_RESOURCE_H
#define COMI_RESOURCE_H

#include "common/types.h"
#include "common/buffer.h"
#include "common/string.h"
#include "common/memory.h"
#include "common/file.h"
#include "common/array.h"

#include "disk.h"
#include "constants.h"
#include "debug.h"

using namespace common;

namespace comi
{
	class Resources;
	class ResourceObject;
	class Disk;
	class DiskParser;

	class RoomData;
	class Script;

	extern Resources* RESOURCES;

	struct Resource {
		void*  _object;
		uint8  _kind;
		uint8  _users;
	};

	class Resources {
	private:

		Disk _disk[NUM_DISKS];

		Array<ResourceObject*> _resources;

		Disk& _getDisk(uint8 num);

		ResourceObject* _findResource(uint16 num, uint8 kind);

	public:

		Resources();
		~Resources();

		bool open();
		void close();

		Script* loadGlobalScript(uint16 num);
		RoomData* loadRoom(uint16 num);

		Script* getGlobalScript(uint16 num);

	};

}

#endif