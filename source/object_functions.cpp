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
#include "room.h"

namespace gs
{
	
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
