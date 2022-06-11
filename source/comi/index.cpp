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
	Index* INDEX = NULL;

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

	Index::Index() {
		debug(COMI_THIS, ".");
	}

	Index::~Index() {
		debug(COMI_THIS, ".");
	}

	template<int kind, uint16 length>
	static bool readResourceIndexTable(ResourceIndexTable<kind, length>& table, ReadFile& file, const char* name) {
		uint16 testLength = (uint16) file.readUInt32LE();
		if (testLength != length) {
			error(GS_THIS, "ResourceList length does not match expected length! Expected=%ld,Given=%ld,Type=%s", length, testLength, name);
			return false;
		}

		table.reset();
		table._name = name;

		file.readBytes(table._roomNum, length);

		uint32* offset = &table._offset[0];
		for (uint32 i = 0; i < length; i++) {
			*offset = file.readUInt32LE();
			offset++;
		}

		verbose(COMI_THIS, "(%ld, %s)", testLength, name);
		return true;
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

			verbose(COMI_THIS, "(%ld, %ld, %ld)", _file.isEof(), _file.pos(), _file.length());

			_file.readTag(tagName);
			
			checkTag(tagName, _file.pos());
			tagLength = _file.readUInt32BE();

			verbose(COMI_THIS, "(%s, %ld, %ld, %ld)", tagName, tagLength, _file.pos(), _file.length());

			// RNAM
			if (tagEqual(tagName, 'R', 'N', 'A', 'M')) {

				verbose(COMI_THIS, "(RNAM, Read, 0x%lx)", &_roomNames[0]);

				clearMemoryNonAllocated(&_roomNames[0], sizeof(_roomNames));

				char roomNameTempStr[11] = { 0 };

				while (true) {

					byte roomNum = _file.readByte();
					if (roomNum == 0)
						break;

					if (roomNum >= NUM_ROOMS) {
						error(GS_THIS, "(RNAM, %ld) Room number exceeded!", roomNum);
					}

					char* roomStr = &roomNameTempStr[0];
					_file.readBytes(roomStr, 9);

					for (i = 0; i < 10; i++) {
						roomStr[i] ^= 0xFF;
					}

					String& roomName = _roomNames[roomNum];
					roomName.copyFrom(roomStr);

					verbose(COMI_THIS, "(RNAM, %ld, %s)", roomNum, _roomNames[roomNum].string());
				}

				verbose(COMI_THIS, "(%s, %ld) Ok.", tagName, tagLength);
				continue;
			}

			// MAXS
			if (tagEqual(tagName, 'M', 'A', 'X', 'S')) {
				_file.skip(100); // Skip copyright and version info string.

				uint32 value;

#define ENFORCE_MAXS(CONSTANT) \
				value = _file.readUInt32LE();\
				if (value != CONSTANT) {\
					error(COMI_THIS, "MAXS has an unexpected constant. Expect=%ld, Got=%ld, For=%s", CONSTANT, value, STRINGIFY_ARG(CONSTANT));\
					return false;\
				}

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
				verbose(COMI_THIS, "(%s, %ld) Ok.", tagName, tagLength);
				continue;
			}

			// DROO
			if (tagEqual(tagName, 'D', 'R', 'O', 'O')) {
				if (readResourceIndexTable(_roomsResources, _file, "DROO (Rooms)") == false)
					return false;
				verbose(COMI_THIS, "(%s, %ld) Ok.", tagName, tagLength);
				continue;
			}

			// DRSC
			if (tagEqual(tagName, 'D', 'R', 'S', 'C')) {
				if (readResourceIndexTable(_roomsScriptsResources, _file, "DRSC (Rooms Scripts)") == false)
					return false;
				verbose(COMI_THIS, "(%s, %ld) Ok.", tagName, tagLength);
				continue;
			}

			// DSCR
			if (tagEqual(tagName, 'D', 'S', 'C', 'R')) {
				if (readResourceIndexTable(_scriptsResources, _file, "DSCR (Scripts)") == false)
					return false;
				verbose(COMI_THIS, "(%s, %ld) Ok.", tagName, tagLength);
				continue;
			}

			// DSOU
			if (tagEqual(tagName, 'D', 'S', 'O', 'U')) {
				if (readResourceIndexTable(_soundsResources, _file, "DSOU (Sounds)") == false)
					return false;
				verbose(COMI_THIS, "(%s, %ld) Ok.", tagName, tagLength);
				continue;
			}

			// DCOS
			if (tagEqual(tagName, 'D', 'C', 'O', 'S')) {
				if (readResourceIndexTable(_costumesResources, _file, "DCOS (Sounds)") == false)
					return false;
				verbose(COMI_THIS, "(%s, %ld) Ok.", tagName, tagLength);
				continue;
			}

			// DCHR
			if (tagEqual(tagName, 'D', 'C', 'H', 'R')) {
				if (readResourceIndexTable(_charsetResources, _file, "DCHR (Charset)") == false)
					return false;
				verbose(COMI_THIS, "(%s, %ld) Ok.", tagName, tagLength);
				continue;
			}

			// DOBJ
			if (tagEqual(tagName, 'D', 'O', 'B', 'J')) {

				uint32 num = _file.readUInt32LE();

				if (num != NUM_OBJECT_GLOBALS) {
					error(GS_THIS, "(%ld, %ld) Unexpected Object Globals Count (DOBJ)", num, NUM_OBJECT_GLOBALS);
					return false;
				}

				_objectTable.reset();

				char objectNameTemp[42] = { 0 };

				for (uint32 i = 0; i < NUM_OBJECT_GLOBALS; i++) {
					ObjectLocation& entry = _objectTable._objects[i];
					_file.readBytes(&objectNameTemp, 40);
					entry._name.copyFrom(&objectNameTemp[0]);
					entry._state = _file.readByte();
					entry._room = _file.readByte();
					entry._class = _file.readUInt32LE();
					entry._owner = 0xFF;

					verbose(COMI_THIS, "(DOBJ, %ld, %s, 0x%2x, 0x%08x, %ld)", i, entry._name.string(), entry._room, entry._class, entry._owner);
				}

#if GS_TEST == 2
				//  check collisions
				for (uint32 i = 0; i < NUM_OBJECT_GLOBALS; i++) {
				
					ObjectEntry& first = _objectTable._objects[i];
				
					if (first._name.length() == 0)
						continue;
				
					for (uint32 j = 0; j < NUM_OBJECT_GLOBALS; j++) {
					
						if (i == j)
							continue;
				
						ObjectEntry& second = _objectTable._objects[j];
				
						if (second._name.length() == 0)
							continue;
				
						if (first._name == second._name) {
							error(COMI_THIS, "(%s, %s, %ld, %ld) quickHash Collision!", &first._name, &second._name, i, j);
							return false;
						}
					}
				}
#endif

				verbose(COMI_THIS, "(%s, %ld) Ok.", tagName, tagLength);
				continue;
			}

			// AARY
			if (tagEqual(tagName, 'A', 'A', 'R', 'Y')) {
				uint16 count = 0, num = 0;
				while (_file.isEof() == false) {

					if (count > NUM_AARY) {
						error(COMI_THIS, "(AARY, %ld, %ld) Expected AARY count has been exceeded!");
						return false;
					}

					num = _file.readUInt32LE();

					if (num == 0)
						break;

					ArraySpec& spec = _arraySpec[count];
					spec.num = num;

					spec.a = _file.readUInt32LE();
					spec.b = _file.readUInt32LE();

					verbose(COMI_THIS, "(AARY, %ld, %ld, %ld, %ld)", count, spec.num, spec.a, spec.b);
					count++;
					
				}
				continue;
			}


			warn(COMI_THIS, "(%s, %ld, %ld) Unhandled Tag!", tagName, tagLength, _file.pos());

			_file.skip(tagLength - 8);
		}

		info(COMI_THIS, "Read Index File at %s", path);
		return true;
	}

	void ObjectLocationTable::reset() {
		clearMemoryNonAllocated(_objects, sizeof(_objects));
	}

}
