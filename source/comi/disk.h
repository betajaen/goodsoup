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

#ifndef COMI_DISK_H
#define COMI_DISK_H

#include "common/types.h"
#include "common/buffer.h"
#include "common/string.h"
#include "common/file.h"

using namespace common;

namespace comi
{

	class Disk {
	private:

		struct RoomOffset {
			uint8 _room;
			uint32 _offset;
		};

		uint8 _num;
		Buffer<RoomOffset> _roomOffsets;
		ReadFile _file;

		bool _readSections();

	public:

		Disk();
		~Disk();

		bool open(uint8 num);
		void close();

	};

}

#endif