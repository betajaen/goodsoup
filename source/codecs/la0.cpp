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

#define GS_FILE_NAME "la0"

#include "forward.h"
#include "file.h"
#include "index.h"
#include "vm/array.h"

namespace gs
{

	bool readLA0(TagReadFile* file, Index* index) {

		if (file->isOpen() == false)  {
			error(GS_THIS, "Could not open LA0 Index file for reading");
			abort_quit_stop();
			return false;
		}

		while(file->pos() < file->length()) {
			TagPair tag = file->readTagPair();

			if (tag.isTag(GS_MAKE_ID('R', 'N', 'A', 'M'))) {
				// Dont read Room Names.
				file->skip(tag);
				continue;
			}

			if (tag.isTag(GS_MAKE_ID('M', 'A', 'X', 'S'))) {


#if GS_CHECKED == 1
				file->skip(100); // Copyright header.

				uint32 value;

#define ENFORCE_MAXS1(CONSTANT) \
				value = file->readUInt32LE();\
				if (value != CONSTANT) {\
					error(GS_THIS, "Unknown Game version! Difference for \"%s\" %ld vs %ld.", STRINGIFY_ARG(CONSTANT), CONSTANT, value);\
					return false;\
				}

				ENFORCE_MAXS1(NUM_INT_GLOBALS);
				ENFORCE_MAXS1(NUM_BOOL_GLOBALS);
				file->skip(sizeof(uint32));
				ENFORCE_MAXS1(NUM_SCRIPTS);
				ENFORCE_MAXS1(NUM_SOUNDS);
				ENFORCE_MAXS1(NUM_CHARSETS);
				ENFORCE_MAXS1(NUM_COSTUMES);
				ENFORCE_MAXS1(NUM_ROOMS);
				file->skip(sizeof(uint32));
				ENFORCE_MAXS1(NUM_OBJECT_GLOBALS);
				file->skip(sizeof(uint32));
				ENFORCE_MAXS1(NUM_OBJECT_LOCALS);
				ENFORCE_MAXS1(NUM_NEWNAMES);
				ENFORCE_MAXS1(NUM_FLOBJECTS);
				ENFORCE_MAXS1(NUM_INVENTORY);
				ENFORCE_MAXS1(NUM_ARRAY);
				ENFORCE_MAXS1(NUM_VERBS);
#undef ENFORCE_MAXS1
#else
				file->skip(tag);
#endif

				continue;
			}


			if (tag.isTag(GS_MAKE_ID('D', 'R', 'O', 'O'))) {

				uint32 length = file->readUInt32LE();

#if GS_CHECKED == 1
				if (length != NUM_ROOMS) {
					error(GS_THIS, "Unknown Game version! Differences for \"Room Count\" %ld vs %ld", NUM_ROOMS, length);
					abort_quit_stop();
					return false;
				}
#endif

				for(uint8 i=0;i < NUM_ROOMS;i++) {
					index->_roomDisks[i] = file->readByte();
				}

				file->seekEndOf(tag);

				goto checkTag;
			}


			if (tag.isTag(GS_MAKE_ID('D', 'R', 'S', 'C'))) {

				uint32 length = file->readUInt32LE();

#if GS_CHECKED == 1
				if (length != NUM_ROOMS) {
					error(GS_THIS, "Number of rooms %ld is unexpected %ld", length, NUM_ROOMS);
					abort_quit_stop();
					return false;
				}
#endif

				// We dont need to store these as they are implied by the array index.
				for(uint8 i=0;i < NUM_ROOMS;i++) {
					uint8 x = file->readByte();
					if (x != i) {
						error(GS_THIS, "Order of DRSC is unexpected!", (uint32) i, (uint32) x);
						abort_quit_stop();
						return false;
					}
				}

				for(uint8 i=0;i < NUM_ROOMS;i++) {
					uint32 offset = file->readUInt32LE();
					index->_roomScriptOffsets[i] = offset;
				}

				goto checkTag;
			}

			if (tag.isTag(GS_MAKE_ID('D', 'S', 'C', 'R'))) {

				uint32 length = file->readUInt32LE();

#if GS_CHECKED == 1

				if (length != NUM_SCRIPTS) {
					error(GS_THIS, "Number of scripts %ld is unexpected %ld", length, NUM_SCRIPTS);
					abort_quit_stop();
					return false;
				}
#endif

				for(uint16 i=0;i < NUM_SCRIPTS;i++) {
					index->_scriptRoom[i] = file->readByte();
				}

				for(uint32 i=0;i < NUM_SCRIPTS;i++) {
					index->_scriptOffset[i] = file->readUInt32LE();
				}

				goto checkTag;
			}

			if (tag.isTag(GS_MAKE_ID('D', 'O', 'B', 'J'))) {

				uint32 length = file->readUInt32LE();

#if GS_CHECKED == 1
				if (length != NUM_OBJECT_GLOBALS) {
					error(GS_THIS, "Number of objects %ld is unexpected %ld", length, NUM_SCRIPTS);
					abort_quit_stop();
					return false;
				}
#endif

				for(uint16 i=0;i < NUM_OBJECT_GLOBALS;i++) {
					index->_objectNameHash[i] = file->readFixedStringAsHash(40);
					index->_objectPrototypeState[i] = file->readByte();
					index->_objectPrototypeRoomNum[i] = file->readByte();
					index->_objectPrototypeClass[i] = file->readUInt32LE();
					index->_objectPrototypeOwner[i] = 0xFF;
				}

				goto checkTag;
			}

			if (tag.isTag(GS_MAKE_ID('D', 'C', 'O', 'S'))) {

				uint32 length = file->readUInt32LE();

#if GS_CHECKED == 1
				if (length != NUM_COSTUMES) {
					error(GS_THIS, "Number of scripts %ld is unexpected %ld", length, NUM_COSTUMES);
					abort_quit_stop();
					return false;
				}
#endif

				for(uint16 i=0;i < NUM_COSTUMES;i++) {
					index->_costumeRoom[i] = file->readByte();
				}

				for(uint32 i=0;i < NUM_COSTUMES;i++) {
					index->_costumeOffset[i] = file->readUInt32LE();
				}

				goto checkTag;
			}

			if (tag.isTag(GS_MAKE_ID('A', 'A', 'R', 'Y'))) {

				uint16 count = 0, arrayNum = 0;
				uint16 a, b;

				while (file->pos() < tag.end()) {

#if GS_CHECKED == 1
					if (count > NUM_AARY) {
						error(GS_THIS, "(AARY, %ld, %ld) Expected AARY count has been exceeded!");
						return false;
					}
#endif

					arrayNum = file->readUInt32LE();

					if (arrayNum == 0)
						break;

					a = file->readUInt32LE();
					b = file->readUInt32LE();

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
			/* TODO DCHR */

			NO_FEATURE(GS_THIS, "Missing support for Index Tag %s", tag.tagStr());
			file->skip(tag);
			continue;

			checkTag:

#if GS_CHECKED == 1
			if (file->pos() > tag.end()) {
				error(GS_THIS, "Tag overread!! %s %ld %ld", tag.tagStr(), file->pos(), tag.end());
				abort_quit_stop();
				return false;
			}
#endif

		}

		return true;
	}

}
