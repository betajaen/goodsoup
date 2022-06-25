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

#define GS_FILE_NAME "script"

#include "script.h"
#include "resource.h"

#include "disk.h"
#include "debug.h"
#include "constants.h"

using namespace common;

namespace comi
{
	ScriptData::ScriptData(uint16 num, uint8 disk, uint8 flags) {
		_num = num;
		_users = 1;
		_kind = RK_SCRIPT;
		_flags = 0;
		_disk = disk;
	}

	ScriptData::~ScriptData() {
		_data.release();
	}
	
	bool ScriptData::readFromDisk(DiskReader& reader) {
		if (reader.readAndExpectTag('S', 'C', 'R', 'P') == false)
			return false;

		uint32 length = reader.readUInt32BE();

		if (length == 0) {
			error(COMI_THIS, "Script length %ld is 0 bytes!", _num);
			return false;
		}

		if (length >= 16384) {
			error(COMI_THIS, "Very large script detected for %ld of %ld bytes!", _num, length);
			return false;
		}

		length -= 8;

		_data.setSize(length, 0);
		reader.readBytes((void*) _data.ptr(0), length);

		return true;
	}


}
