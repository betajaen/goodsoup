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

#ifndef GS_RESOURCE_H
#define GS_RESOURCE_H

#include "types.h"
#include "string.h"
#include "memory.h"
#include "file.h"
#include "containers.h"

#include "disk.h"
#include "profile.h"
#include "debug.h"
#include "resource_data.h"

namespace gs
{
	class Resources;
	class ResourceData;
	class Disk;
	class DiskParser;

	class RoomData;
	class ScriptData;

	extern Resources* RESOURCES;

	template<typename T, uint16 Kind>
	class ResourceCollection {
	private:
		Array<T*> _items;
	public:
		
		ResourceCollection() {
		}

		~ResourceCollection() {
			reset();
		}

		void reset() {
			
			const uint16 size = _items.getSize();

			if (size) {
				for (uint16 i = 0; i < size; i++) {
					T* item = _items.get_unchecked(i);
					deleteObject_unchecked(item);
				}
			}
			
			_items.release();
		}

		T* create(uint16 num, uint8 disk) {
			T* resource = newObject<T>(num, disk, Kind, GS_COMMENT_FILE_LINE);
			_items.push(resource);
			return resource;
		}

		void destroy(T* item) {

			if (item == NULL) {
				error(GS_THIS, "Tried to destroy a NULL resource %ld", (uint32) Kind);
				return;
			}
			
			const uint16 size = _items.getSize();

			for (uint16 i = 0; i < size; i++) {
				T* other = _items.get_unchecked(i);
				if (other == item) {
					_items.erase(i);
					deleteObject_unchecked(item);
					return;
				}
			}

			warn(GS_THIS, "Tried to delete a resource that was not accounded for! %ld %ld", (uint32) item->getNum(), (uint32) item->getResourceKind());
		}

		void destroy(uint16 num) {

			if (num == 0) {
				error(GS_THIS, "Tried to destroy a 0 Id resource %ld", Kind);
				return;
			}

			const uint16 size = _items.getSize();

			for (uint16 i = 0; i < size; i++) {
				T* item = _items.get_unchecked(i);
				if (item->getNum() == num) {
					_items.erase(i);
					deleteObject_unchecked(item);
					return;
				}
			}

			warn(GS_THIS, "Tried to delete a resource that did not exist! %ld %ld", (uint32) num, (uint32) Kind);

		}

		T* find(uint16 num) const {
			
			const uint16 size = _items.getSize();

			for (uint16 i = 0; i < size; i++) {
				T* other = _items.get_unchecked(i);
				if (other->getNum() == num) {
					return other;
				}
			}

			return NULL;
		}

		bool exists(uint16 num) const {

			const uint16 size = _items.getSize();

			for (uint16 i = 0; i < size; i++) {
				T* item = _items.get_unchecked(i);
				if (item->getId() == num)
					return true;
			}

			return false;
		}

	};

	class Resources {
	private:

		Disk _disk[NUM_DISKS];
		ResourceCollection<RoomData, RK_ROOM> _rooms;


	public:

		Resources();
		~Resources();

		bool open();
		void close();
		
		Disk& _getDisk(uint8 num);
		RoomData* loadRoomData(uint16 num);

		RoomData* getRoomData(uint16 num);
	};

}

#endif