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
#include "constants.h"

using namespace common;

namespace comi
{
	struct Resource
	{
		uint16 _roomNum;
		uint32 _offset;		// Word aligned.
	};


	template<uint16 length>
	class ResourceList
	{
	public:
		Resource _resources[length];
	};

	struct ObjectEntry
	{
		char   _name[42];
		uint32 _hash; /* TODO replace with a smaller 16-bit hash. */
		byte   _state;
		byte   _room;
		byte   _owner;
		byte   _padding;
		uint32 _class;
	};

	class ObjectTable
	{
	public:
		void reset();

		ObjectEntry     _objects[NUM_OBJECT_GLOBALS];

	};
}

#endif