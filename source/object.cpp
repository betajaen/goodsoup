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

	ObjectData* ObjectState::_readIntoObject(DiskReader &reader, const TagPair &parentTag, bool& out_isNew) {

		// This needs to handle OBCD tags and OBIM tags, in either order. And create or fetch the existing
		// object.

		int isCorrectTag = false;
		ObjectData* object = NULL;

		// OBCD - Object Code
		if (parentTag.isTag(GS_MAKE_ID('O', 'B', 'C', 'D'))) {

			reader.seek(parentTag);

			// CDHD header first
			while (reader.pos() < parentTag.end()) {
				TagPair tag = reader.readTagPair();

				if (tag.isTag(GS_MAKE_ID('C', 'D', 'H', 'D'))) {

					uint32 version = reader.readUInt32LE();
					uint16 objectNum = reader.readUInt16LE();

					object = _acquireByNum(objectNum, out_isNew);
					object->_parent = reader.readByte();
					object->_parentState = reader.readByte();
					object->_flags = OF_AllowMaskOr;
					break;
				}
			}

			// There was no CDHD header.
			if (object == NULL) {
				error(GS_THIS, "No CDHD tag found in OBCD!");
				abort_quit_stop();
				return NULL;
			}

			// Second pass
			reader.seek(parentTag);

			while (reader.pos() < parentTag.end()) {

				TagPair tag = reader.readTagPair();

				if (tag.isTag(GS_MAKE_ID('V', 'E', 'R', 'B'))) {

					if (SCRIPTS->readObjectVerbScript(object->_num, tag, reader) == false) {
						error(GS_THIS, "Could not read Object %ld Verb Script", (uint32) object->_num);
						abort_quit_stop();
						return NULL;
					}

					reader.seekEndOf(tag);
					continue;
				}
				else if (tag.isTag(GS_MAKE_ID('O', 'B', 'N', 'A'))) {
					reader.skip(tag);	// Current Ignored.
					continue;
				}

				reader.skip(tag);
			}

			return object;
		}
		// Object Image Header
		else if (parentTag.isTag(GS_MAKE_ID('I', 'M', 'H', 'D'))) {

			reader.seek(parentTag);

			uint32 hash = reader.readFixedStringAsHash(40);
			uint16 objectNum = INDEX->findObjectNumFromHash(hash);

			if (objectNum == 0) {
				reader.seek(parentTag);
				char name[41] = { 0 };
				reader.readBytes(&name[0], 41);
				error(GS_THIS, "Could not find object in Index with hash for %s!", name);
				return NULL;
			}

			object = _acquireByNum(objectNum, out_isNew);
			reader.readUInt32LE(); // Version
			reader.readInt32LE(); // Num Images?
			object->_x = reader.readInt32LE();
			object->_y = reader.readInt32LE();
			object->_width = reader.readInt32LE();
			object->_height = reader.readInt32LE();



			return object;

		}

		error(GS_THIS, "Unknown Object Tag %s", parentTag.tagStr());
		abort_quit_stop();
		return NULL;
	}

	ObjectData* ObjectState::_acquireByNum(uint16 num, bool& out_isNew) {
		if (num != 0) {
			for(uint8 i=0;i < _objects.getSize();i++) {
				ObjectData* object = _objects.get_unchecked(i);
				if (object->_num == num) {
					out_isNew = false;
					return object;
				}
			}
		}

		ObjectData* object = _objects.acquire();
		object->_num = num;
		out_isNew = true;
		return object;
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

		bool isNew;
		object = _readIntoObject(reader, tag, isNew);

		if (object) {
			object->setFloating(true);
		}

		return object;
	}

	ObjectData* ObjectState::loadFromRoomLoad(DiskReader& reader, const TagPair& tag, bool& out_isNew) {
		return _readIntoObject(reader, tag, out_isNew);
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
		NO_FEATURE(GS_THIS, "Not implemented ObjectState::findObjectNumFromXY (%ld, %ld)", x, y);

		for(uint8 i=0;i < _objects.getSize();i++) {
			ObjectData* object = _objects.get_unchecked(i);
			/*TODO*/

			//debug(GS_THIS, "Object num=%ld x=%ld y=%ld w=%ld h=%ld", (uint32) object->_num, object->_x, object->_y, object->_width, object->_height);
		}

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
