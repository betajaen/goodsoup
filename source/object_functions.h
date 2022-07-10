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

#ifndef GS_OBJECT_FUNCTIONS_H
#define GS_OBJECT_FUNCTIONS_H

#include "types.h"
#include "point.h"

namespace gs
{
	class ObjectData;

	int16 getObjectX(uint16 objectNum);
	int16 getObjectY(uint16 objectNum);
	Point getObjectXY(uint16 objectNum);
	void setObjectXY(uint16 objectNum, const Point& xy);
	void setObjectX(uint16 objectNum, int16 x);
	void setObjectY(uint16 objectNum, int16 y);
}

#endif