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
#include "vm_array.h"

namespace gs
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
		error(GS_THIS, "(%ld,%2x,%2x,%2x,%2x) Read a bad tagName. Read index is incorrect! ", pos, tagName[0], tagName[1], tagName[2], tagName[3]);
	}

	Index::Index() {
	}

	Index::~Index() {
	}

	bool Index::readFromFile(const char* path) {
		ReadFile file;
		file.open(path);

		if (file.isOpen() == false) {
			error(GS_THIS, "Could not open Index file %s for reading", path);
			abort_quit_stop();
			return false;
		}

		DiskReader reader(file);

		while(file.pos() < file.length()) {

			TagPair tag = reader.readTagPair();

			debug(GS_THIS, "+ INDEX %s", tag.tagStr());

			if (tag.isTag(GS_MAKE_ID('R', 'N', 'A', 'M'))) {
				// Skip RNAMEs as it seems to be a debug feature, and possible waste of memory.
				reader.skip(tag);
				continue;
			}

			if (tag.isTag(GS_MAKE_ID('M', 'A', 'X', 'S'))) {

				reader.skip(100); // Copyright header.

				uint32 value;

#define ENFORCE_MAXS1(CONSTANT) \
				value = reader.readUInt32LE();\
				if (value != CONSTANT) {\
					error(GS_THIS, "MAXS has an unexpected constant. Expect=%ld, Got=%ld, For=%s", CONSTANT, value, STRINGIFY_ARG(CONSTANT));\
					return false;\
				}

				ENFORCE_MAXS1(NUM_INT_GLOBALS);
				ENFORCE_MAXS1(NUM_BOOL_GLOBALS);
				reader.skip(sizeof(uint32));
				ENFORCE_MAXS1(NUM_SCRIPTS);
				ENFORCE_MAXS1(NUM_SOUNDS);
				ENFORCE_MAXS1(NUM_CHARSETS);
				ENFORCE_MAXS1(NUM_COSTUMES);
				ENFORCE_MAXS1(NUM_ROOMS);
				reader.skip(sizeof(uint32));
				ENFORCE_MAXS1(NUM_OBJECT_GLOBALS);
				reader.skip(sizeof(uint32));
				ENFORCE_MAXS1(NUM_OBJECT_LOCALS);
				ENFORCE_MAXS1(NUM_NEWNAMES);
				ENFORCE_MAXS1(NUM_FLOBJECTS);
				ENFORCE_MAXS1(NUM_INVENTORY);
				ENFORCE_MAXS1(NUM_ARRAY);
				ENFORCE_MAXS1(NUM_VERBS);
#undef ENFORCE_MAXS1

				continue;
			}

			if (tag.isTag(GS_MAKE_ID('D', 'R', 'O', 'O'))) {

				uint32 length = reader.readUInt32LE();

				if (length != NUM_ROOMS) {
					error(GS_THIS, "Number of rooms %ld is unexpected %ld", length, NUM_ROOMS);
					abort_quit_stop();
					return false;
				}

				for(uint8 i=0;i < NUM_ROOMS;i++) {
					_roomDisks[i] = reader.readByte();
				}

				reader.seekEndOf(tag);

				goto checkTag;
			}


			if (tag.isTag(GS_MAKE_ID('D', 'R', 'S', 'C'))) {

				uint32 length = reader.readUInt32LE();

				if (length != NUM_ROOMS) {
					error(GS_THIS, "Number of rooms %ld is unexpected %ld", length, NUM_ROOMS);
					abort_quit_stop();
					return false;
				}

				// We dont need to store these as they are implied by the array index.
				for(uint8 i=0;i < NUM_ROOMS;i++) {
					uint8 x = reader.readByte();
					if (x != i) {
						error(GS_THIS, "Order of DRSC is unexpected!", (uint32) i, (uint32) x);
						abort_quit_stop();
						return false;
					}
				}

				for(uint8 i=0;i < NUM_ROOMS;i++) {
					uint32 offset = reader.readUInt32LE();
					_roomScriptOffsets[i] = offset;
				}

				goto checkTag;
			}

			if (tag.isTag(GS_MAKE_ID('D', 'S', 'C', 'R'))) {

				uint32 length = reader.readUInt32LE();

				if (length != NUM_SCRIPTS) {
					error(GS_THIS, "Number of scripts %ld is unexpected %ld", length, NUM_SCRIPTS);
					abort_quit_stop();
					return false;
				}

				for(uint16 i=0;i < NUM_SCRIPTS;i++) {
					_scriptRoom[i] = reader.readByte();
				}

				for(uint32 i=0;i < NUM_SCRIPTS;i++) {
					_scriptOffset[i] = reader.readUInt32LE();
				}

				goto checkTag;
			}

			if (tag.isTag(GS_MAKE_ID('D', 'O', 'B', 'J'))) {

				uint32 length = reader.readUInt32LE();

				if (length != NUM_OBJECT_GLOBALS) {
					error(GS_THIS, "Number of objects %ld is unexpected %ld", length, NUM_SCRIPTS);
					abort_quit_stop();
					return false;
				}

				for(uint16 i=0;i < NUM_OBJECT_GLOBALS;i++) {
					_objectNameHash[i] = reader.readFixedStringAsHash(40);
					_objectState[i] = reader.readByte();
					_objectRoomNum[i] = reader.readByte();
					_objectClass[i] = reader.readUInt32LE();
					_objectOwner[i] = 0xFF;
				}

				goto checkTag;
			}

			if (tag.isTag(GS_MAKE_ID('A', 'A', 'R', 'Y'))) {

				uint16 count = 0, arrayNum = 0;
				uint16 a, b;

				while (reader.pos() < tag.end()) {

					if (count > NUM_AARY) {
						error(GS_THIS, "(AARY, %ld, %ld) Expected AARY count has been exceeded!");
						return false;
					}

					arrayNum = reader.readUInt32LE();

					if (arrayNum == 0)
						break;

					a = reader.readUInt32LE();
					b = reader.readUInt32LE();

					if (b != 0)
					{
						ARRAYS->allocate(arrayNum, a, b, VAK_Integer);
					}
					else
					{
						ARRAYS->allocate(arrayNum, b, a, VAK_Integer);
					}

					count++;

				}

				goto checkTag;
			}


			/* TODO DSOU */
			/* TODO DCOS */
			/* TODO DCHR */

			NO_FEATURE(GS_THIS, "Missing support for Index Tag %s", tag.tagStr());
			reader.skip(tag);
			continue;

			checkTag:

			if (reader.pos() > tag.end()) {

				error(GS_THIS, "Tag overread!! %s %ld %ld", tag.tagStr(), reader.pos(), tag.end());
				abort_quit_stop();
				return false;
			}

			continue;

		}


		debug(GS_THIS, "End");

		return true;
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
