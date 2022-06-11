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

#define GS_FILE_NAME "disk"

#include "resource.h"
#include "index.h"
#include "resource_object.h"
#include "room.h"
#include "script.h"

#include "utils.h"
#include "debug.h"
#include "constants.h"

using namespace common;

namespace comi
{

	static inline void checkTag(char tagName[5], uint32 pos)
	{
		if (tagName[0] < 'A')
			goto _error;
		if (tagName[0] > 'Z')
			goto _error;
		if (tagName[1] < 'A')
			goto _error;
		if (tagName[1] > 'Z')
			goto _error;
		if (tagName[2] < 'A')
			goto _error;
		if (tagName[2] > 'Z')
			goto _error;
		if (tagName[3] < 'A')
			goto _error;
		if (tagName[3] > 'Z')
			goto _error;
		return;

	_error:
		error(COMI_THIS, "(%ld,%2x,%2x,%2x,%2x) Read a bad tagName. Read index is incorrect! ", pos, tagName[0], tagName[1], tagName[2], tagName[3]);
	}

	Disk::Disk() {
	}

	Disk::~Disk() {
		close();
	}

	bool Disk::open(uint8 num) {
		_num = num;
		verbose(COMI_THIS, "Building path for Disk %ld", num);
		String path;
		String::format(path, "%sCOMI.LA%ld", GS_GAME_PATH, num);
		verbose(COMI_THIS, "Opening Disk %ld at %s", num, path.string());
		_file.open(path.string());

		if (_file.isOpen() == false)
			return false;
	
		info(COMI_THIS, "Opened Disk %ld at %s", num, path.string());
	
		return _readSections();
	}

	void Disk::close() {
		_file.close();
		_roomOffsets.release();
	}

	bool Disk::_readSections() {
		uint32 tagLength;
		char tagName[5] = { 0 };


		_file.readTag(tagName);
		tagLength = _file.readUInt32BE();

		// File header
		if (tagEqual(tagName, 'L', 'E', 'C', 'F') == false) {
			error(COMI_THIS, "Disk %ld is not a COMI.LA%ld file!", _num, _num);
			return false;
		}

		// Reasonable tag length;
		if (tagLength < 10000) {
			error(COMI_THIS, "Disk %ld is probably not a COMI.LA%ld file!", _num, _num);
			return false;
		}

		
		while (_file.isEof() == false) {
			_file.readTag(tagName);

			checkTag(tagName, _file.pos());
			tagLength = _file.readUInt32BE();

			debug(COMI_THIS, "(%s, %ld, %ld, %ld)", tagName, tagLength, _file.pos(), _file.length());

			warn(COMI_THIS, "(%s, %ld, %ld) Unhandled Tag!", tagName, tagLength, _file.pos());

			_file.skip(tagLength - 8);
		}

		return true;
	}

}
