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

#define GS_FILE_NAME "index"

#include "hash.h"
#include "index.h"
#include "debug.h"

#include "utils.h"
#include "profile.h"
#include "vm/array.h"

#include "codecs/la0.h"
#include "codecs/gsi.h"

namespace gs
{
	Index* INDEX = NULL;

	static inline void checkTag(char tagName[5], uint32 pos)
	{
#if GS_CHECKED == 1
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
		error(GS_THIS, "(%ld,%2x,%2x,%2x,%2x) Read a bad tagName. Read index is incorrect! ", pos, tagName[0], tagName[1], tagName[2], tagName[3]);
#endif
	}

	Index::Index() {
	}

	Index::~Index() {
	}

	bool Index::saveGSI(const char* path, int8 endian) {
		WriteFile file;
		file.open(path);

		if (endian == -1) {
#if defined(GS_AMIGA)
			endian = 1;
#endif
#if defined(GS_SDL)
			endian = 0;
#endif
		}
		
		return ::gs::writeGSI(&file, this, endian == 1);
	}

	bool Index::readGSI(const char* path) {
		TagReadFile file;
		file.open(path);

		return ::gs::readGSI(&file, this);
	}

	bool Index::readLA0(const char* path) {
		TagReadFile file;
		file.open(path);

		return ::gs::readLA0(&file, this);
	}

	uint16 Index::findObjectNumFromHash(uint32 hash) {

		for(uint16 i=OBJECT_MIN; i < NUM_OBJECT_GLOBALS;i++) {
			if (_objectNameHash[i] == hash) {
				return i;
			}
		}

		return 0;
	}


}
