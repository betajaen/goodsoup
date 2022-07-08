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
#include "vm_vars.h"

namespace gs
{
	ObjectState* OBJECTS = NULL;
	Array<ObjectData*, uint8> DRAWING_OBJECTS;

	ObjectState::ObjectState() {
		_roomObjects.reserve(50);
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

					debug(GS_THIS, "+Object %ld, Parent = %ld, ParentState = %ld",
						  (uint32) object->_num,
						  (uint32) object->_parent,
						  (uint32) object->_parentState
						  );

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

			for(uint16 i=0; i < _roomObjects.size(); i++) {
				ObjectData* object = _roomObjects.get_unchecked(i);
				if (object->_num == num) {
					out_isNew = false;
					return object;
				}
			}

			for(uint16 i=0;i < _globalObjects.size();i++) {
				ObjectData* object= _globalObjects.get_unchecked(i);
				if (object->_num == num) {
					out_isNew = false;
					return object;
				}
			}

		}

		ObjectData* object = _pool.acquire();
		object->_num = num;
		object->_class = INDEX->getObjectClass(num);
		out_isNew = true;
		return object;
	}

	void ObjectState::clearAll() {
		for(uint16 i=0; i < _roomObjects.size(); i++) {
			ObjectData* object = _roomObjects.get_unchecked(i);
			object->clear();
			_pool.release_unchecked(object);
		}

		for (uint16 i=0;i < _globalObjects.size();i++) {
			ObjectData* object = _globalObjects.get_unchecked(i);
			object->clear();
			_pool.release_unchecked(object);
		}

		_pool.clear();
	}

	void ObjectState::moveRoomObjectsToGlobals() {

		// Delete old room/not-floating objects
		while(true) {
			bool didDelete = false;

			for(uint16 i=0;i < _globalObjects.size();i++) {
				ObjectData* object = _globalObjects.get_unchecked(i);

				if (object->isFloating() == false) {
					object->clear();
					_globalObjects.erase(i);
					didDelete = true;
					break;
				}
			}

			if (!didDelete)
				break;
		}

		// Merge in new ones.
		for(uint16 i=0; i < _roomObjects.size();i++) {
			ObjectData* object = _roomObjects.get_unchecked(i);
			_globalObjects.push(object);
		}

		_roomObjects.clear();

	}

	void ObjectState::clearRoomObjectsForNewRoom() {

		static Array< Pair<uint16, ObjectData*> > objectsToClear;

		for(uint16 i=0; i < _globalObjects.size(); i++) {

			ObjectData* object = _globalObjects.get_unchecked(i);

			if (object->isFloating() == false) {
				object->clear();
				objectsToClear.push(Pair<uint16, ObjectData*>(i, object));
				continue;
			}
			else {
				if (object->isLocked() == false) {
					object->clear();
					objectsToClear.push(Pair<uint16, ObjectData *>(i, object));
					continue;
				}
			}
		}

		if (objectsToClear.size()) {
			for (uint16 i = 0; i < objectsToClear.size(); i++) {
				Pair<uint16, ObjectData*> idxObject = objectsToClear.get_unchecked(i);
				_pool.release_unchecked(idxObject._second);
				_globalObjects.erase(idxObject._first);
			}

			objectsToClear.release();
		}

	}

	bool ObjectState::loadFromFloatingObject(uint16 objectNum) {

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
			_globalObjects.push(object);	// Is this correct?
		}

		return object;
	}

	bool ObjectState::loadFromRoomLoad(DiskReader& reader, const TagPair& tag) {
		bool isNew = false;
		ObjectData* object = _readIntoObject(reader, tag, isNew);
		if (object == NULL)
			return false;

		if (isNew) {
			_roomObjects.push(object);
		}

		return true;
	}

	bool ObjectState::unload(uint16 objectNum) {

		if (objectNum == 0) {
			return false;
		}

		for(uint16 i=0;i < _roomObjects.size();i++) {
			ObjectData* data = _roomObjects.get_unchecked(i);
			if (data->_num == objectNum) {
				_roomObjects.erase(i);
				_pool.release_unchecked(data);
				return true;
			}
		}

		for (uint16 i=0;i < _globalObjects.size();i++) {
			ObjectData* data = _globalObjects.get_unchecked(i);
			if (data->_num == objectNum) {
				_globalObjects.erase(i);
				_pool.release_unchecked(data);
				return true;
			}
		}

		return false;
	}

	ObjectData* ObjectState::findGlobalObject(uint16 objectNum)  {
		for(uint16 i=0; i < _globalObjects.size(); i++) {
			const ObjectData* object = _globalObjects.get_unchecked(i);
			if (object->_num == objectNum) {
				return (ObjectData*) object;
			}
		}
		return NULL;
	}

	ObjectData* ObjectState::findRoomObject(uint16 objectNum)  {
		for(uint16 i=0; i < _roomObjects.size(); i++) {
			const ObjectData* object = _roomObjects.get_unchecked(i);
			if (object->_num == objectNum) {
				return (ObjectData*) object;
			}
		}
		return NULL;
	}

	void ObjectState::dumpObjects() const {
		for(uint16 i=0; i < _roomObjects.size(); i++) {
			const ObjectData* object = _roomObjects.get_unchecked(i);
			debug(GS_THIS, "R Idx=%ld Num=%ld Flags=%ld Parent=%ld ParentState=%ld",
				  (uint32) i,
				  (uint32) object->_num,
				  (uint32) object->_flags,
				  (uint32) object->_parent,
				  (uint32) object->_parentState
				  );
		}
		for(uint16 i=0; i < _globalObjects.size(); i++) {
			const ObjectData* object = _globalObjects.get_unchecked(i);
			debug(GS_THIS, "G Idx=%ld Num=%ld Flags=%ld Parent=%ld ParentState=%ld",
				  (uint32) i,
				  (uint32) object->_num,
				  (uint32) object->_flags,
				  (uint32) object->_parent,
				  (uint32) object->_parentState
			);
		}
	}

	uint16 ObjectState::findRoomObjectNumFromXY(int16 x, int16 y)  {

		bool inBounds;
		uint8 otherState, thisState;
		uint16 otherNum;

		for(uint8 i=0;i < _globalObjects.size();i++) {

			const ObjectData* object = _globalObjects.get_unchecked(i);

			if (object->isKind(OK_Untouchable))
				continue;

			bool inBounds = object->inBounds(x, y);

			if (inBounds == false)
				continue;

			thisState = object->_parentState;
			otherNum = object->_num;

			/* TODO: Parents */

			if (INTS->leftbtnDown) {
				debug(GS_THIS, "Under object %ld x %ld %ld", (uint32) object->_num, (int32) x, (int32) y);
			}

			return object->_num;
		}

		return 0;
	}

	byte ObjectState::getState(uint16 objectNum) {
		ObjectData* object = findObject(objectNum);
		if (object) {
			return object->_state;
		}
		else {
			warn(GS_THIS, "getState %ld returned a null object", (uint32) objectNum);
			return 0;
		}
	}

	void ObjectState::setState(uint16 objectNum, byte newState) {
		ObjectData* object = findObject(objectNum);
		if (object) {
			object->_state = newState;
		}
		else {
			warn(GS_THIS, "setState %ld returned a null object", (uint32) objectNum);
		}
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
		_bIsLocked = false;
		_bIsFloating = false;
	}

	bool ObjectData::isKind(uint8 objectKind) const {
		const uint32 shift = 1 << ((uint32) (objectKind - 1));
		return (_class & shift) != 0;
	}


}
