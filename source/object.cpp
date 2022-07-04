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

#define GS_FILE_NAME "object"

#include "object.h"
#include "memory.h"
#include "room.h"
#include "index.h"
#include "resource.h"

namespace gs
{
	ObjectState* OBJECTS = NULL;
	Array<ObjectData*, uint8> DRAWING_OBJECTS;

	ObjectState::ObjectState() {
	}

	ObjectState::~ObjectState() {
		clearAll();
	}

	DiskReader ObjectState::_seekToObject(uint16 objectNum, TagPair& out_tag) {

		uint16 roomNum;
		uint8 diskNum;

		if (INDEX->getObject(objectNum, roomNum, diskNum) == false) {
			error(GS_THIS, "Could not read Floating Object %ld as it does not exist", (uint32) objectNum);
			abort_quit_stop();
			return DiskReader::Null();
		}

		Disk& disk = RESOURCES->_getDisk(diskNum);
		DiskReader reader = disk.openRoomForReading(roomNum);
		if (reader.pos() == 0) {
			error(GS_THIS, "Could not read Floating Object %ld as the container room %ld does not exist", (uint32) objectNum, (uint32) roomNum);
			abort_quit_stop();
			return DiskReader::Null();
		}

		TagPair lflf = reader.readTagPair();

		if (lflf.isTag(GS_MAKE_ID('L','F','L','F')) == false) {
			error(GS_THIS, "Could not read RoomData as its not a Room!", (uint32) roomNum);
			return DiskReader::Null();
		}

		if (lflf.length == 0) {
			error(GS_THIS, "Room length %ld is 0 bytes!", (uint32) roomNum);
			return DiskReader::Null();
		}

		while (reader.pos() < lflf.end()) {
			TagPair roomPair = reader.readTagPair();

			if (roomPair.isTag(GS_MAKE_ID('R', 'M', 'S', 'C'))) {	// RMSC

				while (reader.pos() < roomPair.end()) {
					TagPair rmscPair = reader.readTagPair();

					if (rmscPair.isTag(GS_MAKE_ID('O', 'B', 'C', 'D'))) {	// OBCD?

						while (reader.pos() < rmscPair.end()) {
							TagPair innerObjectTag = reader.readTagPair();

							if (innerObjectTag.isTag(GS_MAKE_ID('C', 'D', 'H', 'D'))) {	// CDHD?

								uint32 readVersion = reader.readUInt32LE();
								uint16 readObjectNum = reader.readUInt16LE();

								if (readObjectNum != objectNum) { // Not this one. Skip OBCD completely.
									reader.seek(rmscPair);
									break;
								}

								reader.seek(rmscPair);

								out_tag = rmscPair;

								return reader;
							}
							reader.skip(innerObjectTag);
						}

					}

					reader.skip(rmscPair);
				}

				break;
			}

			reader.skip(roomPair);
		}

		return DiskReader::Null();

	}

	bool ObjectState::_readIntoObject(ObjectData* object, DiskReader &reader, const TagPair &obcdTag) {

		if (obcdTag.isTag(GS_MAKE_ID('O', 'B', 'C', 'D')) == false) {
			error(GS_THIS, "Unexpected tag %s, expected OBCD", obcdTag.tagStr());
			abort_quit_stop();
			return false;
		}

		reader.seek(obcdTag);

		while (reader.pos() < obcdTag.end()) {
			TagPair tag = reader.readTagPair();

			if (tag.isTag(GS_MAKE_ID('C', 'D', 'H', 'D'))) {

				uint32 version = reader.readUInt32LE();

				object->_num = reader.readUInt16LE();
				object->_parent = reader.readByte();
				object->_parentState = reader.readByte();
				object->_flags = OF_AllowMaskOr;

				continue;
			}
			else if (tag.isTag(GS_MAKE_ID('V', 'E', 'R', 'B'))) {

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

		return true;
	}

	void ObjectState::clearAll() {
		for(uint8 i=0;i < _objects.getSize();i++) {
			ObjectData* object = _objects.get_unchecked(i);
			object->clear();
		}

		_objects.clear();
	}

	void ObjectState::clearForNewRoom() {

		static Array<ObjectData*> objectsToClear;

		for(uint8 i=0;i < _objects.getSize(); i++) {

			ObjectData* object = _objects.get_unchecked(i);

			if (object->isFloating() == false) {
				object->clear();
				objectsToClear.push(object);
				continue;
			}

			if (object->isFloating() == true && object->isLocked() == false) {
				object->clear();
				objectsToClear.push(object);
				continue;
			}
		}

		if (objectsToClear.size()) {
			for (uint16 i = 0; i < objectsToClear.size(); i++) {
				ObjectData* object = objectsToClear.get_unchecked(i);
				_objects.release_unchecked(object);
			}

			objectsToClear.release();
		}

	}

	ObjectData* ObjectState::loadFromFloatingObject(uint16 objectNum) {

		ObjectData* object;

		object = findObject(objectNum);

		if (object != NULL) {

			if (object->isFloating() == false) {
				warn(GS_THIS, "A floating object %ld was requested which is already loaded, but it is not floating?", objectNum);
			}

			return object;
		}


		TagPair tag;
		DiskReader reader = _seekToObject(objectNum, tag);
		if (reader.isNull()) {
			error(GS_THIS, "Could not find (Floating) Object %ld", (uint32) objectNum);
			abort_quit_stop();
			return NULL;
		}

		object = _objects.acquire();

		if (_readIntoObject(object, reader, tag) == false) {
			error(GS_THIS, "Could not read (Floating) Object %ld", (uint32) objectNum);
			_objects.release_unchecked(object);
			abort_quit_stop();
			return NULL;
		}

		object->setFloating(true);

		return object;
	}

	ObjectData* ObjectState::loadFromRoomLoad(DiskReader& reader, const TagPair& tag) {

		ObjectData* object = _objects.acquire();

		if (_readIntoObject(object, reader, tag) == false) {
			error(GS_THIS, "Did not read Object from room");
			_objects.release_unchecked(object);
			abort_quit_stop();
			return NULL;
		}

		return object;
	}

	bool ObjectState::unload(uint16 objectNum) {

		ObjectData* object = findObject(objectNum);

		if (object != NULL) {
			object->clear();
			_objects.release_unchecked(object);

			return true;
		}

		return false;
	}

	bool ObjectState::hasObject(uint16 num) const {
		for(uint8 i=0;i < _objects.getSize();i++) {
			const ObjectData* object = _objects.get_unchecked(i);
			if (object->_num == num) {
				return true;
			}
		}
		return false;
	}

	ObjectData* ObjectState::findObject(uint16 num)  {
		for(uint8 i=0;i < _objects.getSize();i++) {
			ObjectData* object = _objects.get_unchecked(i);
			if (object->_num == num) {
				return object;
			}
		}
		return NULL;
	}

	void ObjectState::dumpObjects() {
		for(uint8 i=0;i < _objects.getSize();i++) {
			ObjectData* object = _objects.get_unchecked(i);
			debug(GS_THIS, "Object Idx=%ld Num=%ld Flags=%ld", (uint32) i, (uint32) object->_num, (uint32) object->_flags );
		}
	}

	uint16 ObjectState::findObjectNumFromXY(int16 x, int16 y) {
		NO_FEATURE(GS_THIS, "Not implemented ObjectState::findObjectNumFromXY");
		return 0;
	}

	void ObjectData::clear() {
		_num = 0;
		_state = 0;
		_parent = 0;
		_parentState = 0;
		_flags = 0;
		_class = 0;
		_x = 0;
		_y = 0;
		_width = 0;
		_height = 0;
		_script.gcForget();
	}

}
