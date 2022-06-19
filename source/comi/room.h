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

#ifndef COMI_ROOM_H
#define COMI_ROOM_H

#include "common/types.h"
#include "resource_object.h"

namespace comi
{
	class ResourceParser;

	class RoomData : public ResourceObject
	{
	public:

		RoomData(uint16 num, uint8 kind, uint8 disk, uint8 flags);
		~RoomData();

		void readFromParser(ResourceParser& parser);
		
	};

}

#endif