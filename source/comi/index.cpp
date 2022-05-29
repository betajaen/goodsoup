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

#include "common/hash.h"
#include "index.h"
#include "debug.h"

#include "utils.h"
#include "constants.h"

using namespace common;

namespace comi
{
	static inline void enforceMAXSConstant(const char* name, uint32 constantValue, ReadFile& file) {
		uint32 value = file.readUInt32LE();

		if (value != constantValue) {
			comi_error("MAXS has an unexpected constant. Expect=%d, Got=%d, For=%s", constantValue, value, name);
		}

	}

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
		comi_error("(%d,%2x,%2x,%2x,%2x) Read a bad tagName. Read index is incorrect! ", pos, tagName[0], tagName[1], tagName[2], tagName[3]);
	}

	Index::Index() {
		comi_debug(".");
	}

	Index::~Index() {
		comi_debug(".");
	}

	template<uint16 Length>
	static void readResourceList(ResourceList<Length>& resources, ReadFile& file, const char* name) {
		uint16 testLength = (uint16) file.readUInt32LE();
		if (testLength != Length) {
			error("ResourceList length does not match expected length! Expected=%d,Given=%d,Type=%s", Length, testLength, name);
		}

		for (uint32 i = 0; i < Length; i++) {
			Resource& resource = resources._resources[i];
			resource._roomNum = file.readByte();
		}

		for (uint32 i = 0; i < Length; i++) {
			Resource& resource = resources._resources[i];
			resource._offset = file.readUInt32LE();
		}

		for (uint32 i = 0; i < Length; i++) {
			Resource& resource = resources._resources[i];
			comi_verbose("(%d, %d,%d)", i, resource._roomNum, resource._offset);
		}
	}

	bool Index::readFromFile(const char* path) {

		ReadFile _file;

		char tagName[5] = { 0 };
		uint32 tagLength;
		byte b;
		int32 i;

		_file.open(path);

		if (_file.isOpen() == false) {
			return false;
		}


		while (_file.isEof() == false) {
			_file.readTag(tagName);
			
			checkTag(tagName, _file.pos());
			tagLength = _file.readUInt32BE();

			comi_verbose("(%s, %d, %d, %d)", tagName, tagLength, _file.pos(), _file.length());


			// RNAM
			if (tagEqual(tagName, 'R', 'N', 'A', 'M')) {

				comi_verbose("(RNAM, Read)");

				clearMemoryNonAllocated(_roomNames, sizeof(_roomNames));

				while (true) {

					byte roomNum = _file.readByte();
					if (roomNum == 0)
						break;

					if (roomNum >= NUM_ROOMS) {
						error("(RNAM, %d) Room number exceeded!", roomNum);
					}

					char* roomStr = &_roomNames[roomNum][0];
					_file.readBytes(roomStr, 9);

					for (i = 0; i < 10; i++) {
						roomStr[i] ^= 0xFF;
					}

					comi_verbose("(RNAM, %d, %s)", roomNum, &_roomNames[roomNum][0]);
				}

				comi_verbose("(%s, %d) Ok.", tagName, tagLength);
				continue;
			}

			// MAXS
			if (tagEqual(tagName, 'M', 'A', 'X', 'S')) {
				_file.skip(100); // Skip copyright and version info string.


#define ENFORCE_MAXS(CONSTANT) \
	enforceMAXSConstant(STRINGIFY_ARG(CONSTANT), CONSTANT, _file)

				ENFORCE_MAXS(NUM_INT_GLOBALS);
				ENFORCE_MAXS(NUM_BOOL_GLOBALS);
				_file.skip(sizeof(uint32));
				ENFORCE_MAXS(NUM_SCRIPTS);
				ENFORCE_MAXS(NUM_SOUNDS);
				ENFORCE_MAXS(NUM_CHARSETS);
				ENFORCE_MAXS(NUM_COSTUMES);
				ENFORCE_MAXS(NUM_ROOMS);
				_file.skip(sizeof(uint32));
				ENFORCE_MAXS(NUM_OBJECT_GLOBALS);
				_file.skip(sizeof(uint32));
				ENFORCE_MAXS(NUM_OBJECT_LOCALS);
				ENFORCE_MAXS(NUM_NEWNAMES);
				ENFORCE_MAXS(NUM_FLOBJECTS);
				ENFORCE_MAXS(NUM_INVENTORY);
				ENFORCE_MAXS(NUM_ARRAY);
				ENFORCE_MAXS(NUM_VERBS);
#undef ENFORCE_MAXS
				comi_verbose("(%s, %d) Ok.", tagName, tagLength);
				continue;
			}

			// DROO
			if (tagEqual(tagName, 'D', 'R', 'O', 'O')) {
				readResourceList(_roomsResources, _file, "DROO (Rooms)");
				comi_verbose("(%s, %d) Ok.", tagName, tagLength);
				continue;
			}

			// DRSC
			if (tagEqual(tagName, 'D', 'R', 'S', 'C')) {
				readResourceList(_roomsScriptsResources, _file, "DRSC (Rooms Scripts)");
				comi_verbose("(%s, %d) Ok.", tagName, tagLength);
				continue;
			}

			// DSCR
			if (tagEqual(tagName, 'D', 'S', 'C', 'R')) {
				readResourceList(_scriptsResources, _file, "DSCR (Scripts)");
				comi_verbose("(%s, %d) Ok.", tagName, tagLength);
				continue;
			}

			// DSOU
			if (tagEqual(tagName, 'D', 'S', 'O', 'U')) {
				readResourceList(_soundsResources, _file, "DSOU (Sounds)");
				comi_verbose("(%s, %d) Ok.", tagName, tagLength);
				continue;
			}

			// DCOS
			if (tagEqual(tagName, 'D', 'C', 'O', 'S')) {
				readResourceList(_costumesResources, _file, "DCOS (Sounds)");
				comi_verbose("(%s, %d) Ok.", tagName, tagLength);
				continue;
			}

			// DCHR
			if (tagEqual(tagName, 'D', 'C', 'H', 'R')) {
				readResourceList(_charsetResources, _file, "DCHR (Charset)");
				comi_verbose("(%s, %d) Ok.", tagName, tagLength);
				continue;
			}

			// DOBJ
			if (tagEqual(tagName, 'D', 'O', 'B', 'J')) {

				uint32 num = _file.readUInt32LE();

				if (num != NUM_OBJECT_GLOBALS) {
					error("(%d, %d) Unexpected Object Globals Count (DOBJ)", num, NUM_OBJECT_GLOBALS);
				}

				_objectTable.reset();

				for (uint32 i = 0; i < NUM_OBJECT_GLOBALS; i++) {
					ObjectEntry& entry = _objectTable._objects[i];
					_file.readBytes(&entry._name[0], 40);
					entry._hash = djb2Hash(&entry._name[0]);
					entry._state = _file.readByte();
					entry._room = _file.readByte();
					entry._class = _file.readUInt32LE();
					entry._owner = 0xFF;

					comi_verbose("(DOBJ, %i, %s, 0x%04x, 0x%2x, 0x%08x, %d)", i, entry._name, entry._hash, entry._room, entry._class, entry._owner);
				}

				//  check collisions
				for (uint32 i = 0; i < NUM_OBJECT_GLOBALS; i++) {
				
					ObjectEntry& first = _objectTable._objects[i];
				
					if (first._name[0] == 0)
						continue;
				
					for (uint32 j = 0; j < NUM_OBJECT_GLOBALS; j++) {
					
						if (i == j)
							continue;
				
						ObjectEntry& second = _objectTable._objects[j];
				
						if (second._name[0] == 0)
							continue;
				
						if (first._hash == second._hash) {
							comi_error("(%s, %s, %d, %d, %d, %d) quickHash Collision!", &first._name[0], &second._name[0], first._hash, second._hash, i, j);
						}
					}
				}

				comi_verbose("(%s, %d) Ok.", tagName, tagLength);
				continue;
			}

			// AARY
			if (tagEqual(tagName, 'A', 'A', 'R', 'Y')) {
				uint32 num, a, b;
				while (_file.isEof() == false) {
					num = _file.readUInt32LE();

					if (num == 0)
						break;

					a = _file.readUInt32LE();
					b = _file.readUInt32LE();

					/* TODO */

					comi_verbose("(AARY, %d, %d, %d, %d)", _file.pos(), _file.length(), num, a, b);
					
				}
				continue;
			}


			comi_warn("(%s, %d, %d) Unhandled Tag!", tagName, tagLength, _file.pos());

			_file.skip(tagLength - 8);
		}

		return true;
	}

}
