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

#ifndef GS_SCRIPT_H
#define GS_SCRIPT_H

#include "types.h"
#include "buffer.h"

#include "resource_data.h"

namespace gs
{
	class DiskReader;

	class ScriptData : public ResourceData
	{
	private:
		Buffer<byte, uint16> _data;
	public:

		ScriptData(uint16 num, uint8 disk, uint8 flags);
		~ScriptData();

		bool readFromDisk(DiskReader& reader);

		ReadSpan<byte, uint16> getDataPtr() {
			return _data.getReadSpan<uint16>();
		}

	};

}

#endif