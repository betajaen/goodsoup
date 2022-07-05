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

#define GS_FILE_NAME "room_object"

#include "room.h"
#include "disk.h"
#include "debug.h"
#include "object.h"

namespace gs
{


	bool RoomData::_readObjects(DiskReader& reader, const TagPair& lflf) {

		objects.clear();

		reader.seek(lflf);

		while (reader.pos() < lflf.end()) {
			TagPair roomPair = reader.readTagPair();

			if (roomPair.isTag(GS_MAKE_ID('R', 'M', 'S', 'C'))) {

				while (reader.pos() < roomPair.end()) {
					TagPair rmscPair = reader.readTagPair();

					if (rmscPair.isTag(GS_MAKE_ID('O', 'B', 'C', 'D'))) {

						bool isNew = false;
						ObjectData* object = OBJECTS->loadFromRoomLoad(reader, rmscPair, isNew);

						if (isNew) {
							objects.push(object);
						}

						reader.seekEndOf(rmscPair);
						continue;
					}

					reader.skip(rmscPair);
					continue;
				}

				continue;
			}

			if (roomPair.isTag(GS_MAKE_ID('R', 'O', 'O', 'M'))) {

				while(reader.pos() < roomPair.end()) {
					TagPair room = reader.readTagPair();

					if (room.isTag(GS_MAKE_ID('O', 'B', 'I', 'M'))) {
						TagPair obim = reader.readTagPair();

						bool isNew = false;
						ObjectData* object = OBJECTS->loadFromRoomLoad(reader, obim, isNew);

						if (isNew) {
							objects.push(object);
						}

						reader.seekEndOf(obim);
						continue;
					}

					reader.seekEndOf(room);
					continue;
				}

				continue;
			}

			reader.skip(roomPair);
		}


		return true;
	}
}
