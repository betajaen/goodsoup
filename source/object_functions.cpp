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
		return OBJECTS->loadFromFloatingObject(objectNum);
	}

	int16 getObjectX(uint16 objectNum) {
		const ObjectData* object = OBJECTS->findObject(objectNum);
		
		if (object != NULL) {
			return object->_x;
		}
		else {
			warn(GS_THIS, "Missing Object %ld", (uint32) objectNum);
		}

		return 0;
	}

	int16 getObjectY(uint16 objectNum) {
		const ObjectData* object = OBJECTS->findObject(objectNum);
		
		if (object != NULL) {
			return object->_y;
		}
		else {
			warn(GS_THIS, "Missing Object %ld", (uint32) objectNum);
		}

		return 0;

	}

	Point getObjectXY(uint16 objectNum) {
		
		const ObjectData* object = OBJECTS->findObject(objectNum);
		
		if (object != NULL) {
			return Point(object->_x, object->_y);
		}
		else {
			warn(GS_THIS, "Missing Object %ld", (uint32) objectNum);
		}

		return Point();
	}

	void setObjectXY(uint16 objectNum, const Point& xy) {
		
		ObjectData* object = OBJECTS->findObject(objectNum);
		
		if (object != NULL) {
			object->_x = xy.x;
			object->_y = xy.y;
		}
		else {
			warn(GS_THIS, "Missing Object %ld", (uint32) objectNum);
		}

	}

	void setObjectX(uint16 objectNum, int16 x) {
		
		ObjectData* object = OBJECTS->findObject(objectNum);
		
		if (object != NULL) {
			object->_x = x;
		}
		else {
			warn(GS_THIS, "Missing Object %ld", (uint32) objectNum);
		}
	}

	void setObjectY(uint16 objectNum, int16 y) {

		ObjectData* object = OBJECTS->findObject(objectNum);
		
		if (object != NULL) {
			object->_y = y;
		}
		else {
			warn(GS_THIS, "Missing Object %ld", (uint32) objectNum);
		}
	}

}
