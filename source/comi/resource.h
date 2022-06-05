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

#include "constants.h"

using namespace common;

namespace comi
{
	enum ResourceKind
	{
		RK_SCRIPT
	};

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
		String  _name;
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

	typedef Buffer<byte> ResourceBytes;

	class ResourceDictionary
	{
		struct ResourceData
		{
			uint16         _num;
			uint16         _reserved;
			uint32         _flags;
			ResourceBytes*  _data;
		};

	public:

		ResourceDictionary();
		~ResourceDictionary();

		void clear();
		ResourceBytes* get(uint16 num);
		ResourceBytes* set(uint16 num);
		void remove(uint16 num);


	};

}

#endif