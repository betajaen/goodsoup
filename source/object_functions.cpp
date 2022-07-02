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

#define GS_FILE_NAME "object"

#include "object.h"
#include "index.h"
#include "room.h"

namespace gs
{
	
	bool loadFloatingObject(uint16 objectNum) {

		uint16 roomNum;
		uint8 diskNum;

		if (INDEX->getObject(objectNum, roomNum, diskNum) == false) {
			error(GS_THIS, "Could not read Floating Object %ld as it does not exist", (uint32) objectNum);
			abort_quit_stop();
			return false;
		}

		Disk& disk = RESOURCES->_getDisk(diskNum);
		DiskReader reader = disk.openRoomForReading(roomNum);
		if (reader.pos() == 0) {
			error(GS_THIS, "Could not read Floating Object %ld as the container room %ld does not exist", (uint32) objectNum, (uint32) roomNum);
			abort_quit_stop();
			return false;
		}

		TagPair lflf = reader.readTagPair();
		
		if (lflf.isTag(GS_MAKE_ID('L','F','L','F')) == false) {
			error(GS_THIS, "Could not read RoomData as its not a Room!", (uint32) roomNum);
			return false;
		}

		if (lflf.length == 0) {
			error(GS_THIS, "Room length %ld is 0 bytes!", (uint32) roomNum);
			return false;
		}

		debug(GS_THIS, "Find Object %ld", (uint32) objectNum);

		while (reader.pos() < lflf.end()) {
			TagPair roomPair = reader.readTagPair();

			if (roomPair.isTag(GS_MAKE_ID('R', 'M', 'S', 'C'))) {	// RMSC

				while (reader.pos() < roomPair.end()) {
					TagPair rmscPair = reader.readTagPair();

					if (rmscPair.isTag(GS_MAKE_ID('O', 'B', 'C', 'D'))) {	// OBCD?
						
						while (reader.pos() < rmscPair.end()) {
							TagPair innerObjectTag = reader.readTagPair();
			
							if (innerObjectTag.isTag(GS_MAKE_ID('C', 'D', 'H', 'D'))) {	// CDHD?
							
								uint32 readVersion = reader.readUInt32LE();
								uint16 readObjectNum = reader.readUInt16LE();

								if (readObjectNum != objectNum) { // Not this one. Skip OBCD completely.
									reader.seek(rmscPair);
									break;
								}


								reader.seek(rmscPair); // Skip back to outer tag, so it can be read in full.
								return OBJECTS->newObject(objectNum, OK_RoomObject, reader, rmscPair, OVF_Floating);
							}
							reader.skip(innerObjectTag);
						}
						
					}

					reader.skip(rmscPair);
				}

				break;
			}

			reader.skip(roomPair);
		}


		NO_FEATURE(GS_THIS, "Not implemented loadFloatingObject %ld", (uint32) objectNum);
		return NULL;
	}

	int16 getObjectX(uint16 num) {
		const ObjectVariant* object = OBJECTS->findObjectByNum(num);
		
		if (object != NULL) {
			if (object->_kind == OK_RoomObject) {
				const RoomObjectData* data = object->_data._room;
				return data->_x;
			}
		}
		else {
			warn(GS_THIS, "Missing Object %ld", (uint32) num);
		}

		return 0;
	}

	int16 getObjectY(uint16 num) {
		const ObjectVariant* object = OBJECTS->findObjectByNum(num);
		
		if (object != NULL) {
			if (object->_kind == OK_RoomObject) {
				const RoomObjectData* data = object->_data._room;
				return data->_x;
			}
		}
		else {
			warn(GS_THIS, "Missing Object %ld", (uint32) num);
		}

		return 0;

	}

	Point getObjectXY(uint16 num) {
		
		const ObjectVariant* object = OBJECTS->findObjectByNum(num);
		
		if (object != NULL) {
			if (object->_kind == OK_RoomObject) {
				const RoomObjectData* data = object->_data._room;
				return Point(data->_x, data->_y);
			}
		}
		else {
			warn(GS_THIS, "Missing Object %ld", (uint32) num);
		}

		return Point();
	}

	void setObjectXY(uint16 num, const Point& xy) {
		
		ObjectVariant* object = OBJECTS->findObjectByNum(num);
		
		if (object != NULL) {
			if (object->_kind == OK_RoomObject) {
				RoomObjectData* data = object->_data._room;
				data->_x = xy.x;
				data->_y = xy.y;
			}
		}
		else {
			warn(GS_THIS, "Missing Object %ld", (uint32) num);
		}

	}

	void setObjectX(uint16 num, int16 x) {
		
		ObjectVariant* object = OBJECTS->findObjectByNum(num);
		
		if (object != NULL) {
			if (object->_kind == OK_RoomObject) {
				RoomObjectData* data = object->_data._room;
				data->_x = x;
			}
		}
		else {
			warn(GS_THIS, "Missing Object %ld", (uint32) num);
		}
	}

	void setObjectY(uint16 num, int16 y) {
		
		ObjectVariant* object = OBJECTS->findObjectByNum(num);
		
		if (object != NULL) {
			if (object->_kind == OK_RoomObject) {
				RoomObjectData* data = object->_data._room;
				data->_y = y;
			}
		}
		else {
			warn(GS_THIS, "Missing Object %ld", (uint32) num);
		}
	}

}
