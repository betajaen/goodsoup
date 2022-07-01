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

#ifndef GS_OBJECT_H
#define GS_OBJECT_H

#include "types.h"
#include "array.h"
#include "buffer.h"
#include "resource_data.h"
#include "span.h"
#include "disk.h"
#include "profile.h"
#include "debug.h"

namespace gs
{

#define MAX_OBJECTS 200

	struct ObjectData
	{
		uint16 _num;

		void clear();
	};

	extern ObjectData* OBJECTS;

	void openObjects();
	void closeObjects();
	void clearObjects();

	inline ObjectData* getObject(uint16 idx) {
		if (idx < MAX_OBJECTS) {
			return &OBJECTS[idx];
		}

		error(GS_THIS, "Object %ld out of range!", idx);
		return NULL;
	}

}

#endif