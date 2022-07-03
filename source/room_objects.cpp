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

#define GS_FILE_NAME "room_object"

#include "room.h"
#include "disk.h"
#include "debug.h"
#include "object.h"

namespace gs
{


	void RoomObjectData::release() {
		_num = 0;
		_parent = 0;
		_parentState = 0;
		_flags = 0;
		_scriptData = ReadSpan<byte, uint16>();
	}


	bool RoomObjectData::readFromDisk(DiskReader& reader, const TagPair& obcdTag) {

		reader.seek(obcdTag);

		ObjectVariant* object = NULL;
		
		while (reader.pos() < obcdTag.end()) {
			TagPair tag = reader.readTagPair();
			
			if (tag.isTag(GS_MAKE_ID('C', 'D', 'H', 'D'))) {

				uint32 version = reader.readUInt32LE();
				uint16 objectNum = reader.readUInt16LE();

				object = OBJECTS->newObject(objectNum, OK_RoomObject);
				
				RoomObjectData* data = object->_data._room;
				
				data->_num = objectNum;
				data->_parent = reader.readByte();
				data->_parentState = reader.readByte();
				data->_flags = OF_AllowMaskOr;
				
				continue;
			}
			else if (tag.isTag(GS_MAKE_ID('V', 'E', 'R', 'B'))) {
				NO_FEATURE(GS_THIS, "Reading Object Verb");

				if (SCRIPTS->readObjectVerbScript(object->_num, tag, reader) == false) {
					error(GS_THIS, "Could not read Object %ld Verb Script", (uint32) object->_num);
					abort_quit_stop();
					return false;
				}

				reader.seekEndOf(tag);
				continue;
			}
			else if (tag.isTag(GS_MAKE_ID('O', 'B', 'N', 'A'))) {
				reader.skip(tag);

				// Currently Disabled, as it is unknown if this is actually required in functionality, and where
				// the data should be put, and if it should what *visible* objects should have this functionality.
#if 0
				if (object == NULL) {
					error(GS_THIS, "Name was read before header!");
					return false;
				}

                char nameTemp[255] = { 0 };
                uint16 nameLength = 0;

                while(true) {
                    char ch = reader.readByte();
                    nameTemp[nameLength++] = ch;
                    if (ch == 0)
                        break;
                }

                debug(GS_THIS, "+Object Name = \"%s\", %ld, %ld", &nameTemp[0], (uint32) nameLength, (uint32) tag.length);

				reader.seekEndOf(tag);
#endif
				continue;
			}
			
			debug(GS_THIS, "Unknown tag after OBCD %s %ld", tag.tagStr(), tag.length);

			reader.skip(tag);
		}

		if (object != NULL) {
			debug(GS_THIS, "Read Object %ld", (uint32) object->_num);
		}

		return object != NULL;
	}
	
	bool RoomData::_readObjects(DiskReader& reader, const TagPair& lflf) {
		reader.seek(lflf);

		while (reader.pos() < lflf.end()) {
			TagPair roomPair = reader.readTagPair();

			if (roomPair.isTag(GS_MAKE_ID('R', 'M', 'S', 'C'))) {

				while (reader.pos() < roomPair.end()) {
					TagPair rmscPair = reader.readTagPair();

					if (rmscPair.isTag(GS_MAKE_ID('O', 'B', 'C', 'D'))) {

						ObjectVariant* object = OBJECTS->newObject(0xFFFF, OK_RoomObject, reader, rmscPair, 0);
						objects.push(object->_data._room);

						reader.seek(rmscPair);
						reader.skip(rmscPair);
						continue;
					}

					reader.skip(rmscPair);
				}

				break;
			}

			reader.skip(roomPair);
		}

		return true;
	}
}