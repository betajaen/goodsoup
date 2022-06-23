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

#define GS_FILE_NAME "room"

#include "room.h"
#include "resource.h"

#include "vm.h"
#include "debug.h"
#include "constants.h"
#include "globals.h"
#include "vm_vars.h"
#include "disk.h"
#include "utils.h"

using namespace common;

namespace comi
{
	RoomData::RoomData(uint16 num, uint8 disk, uint8 flags) {
		_num = num;
		_users = 1;
		_kind = RK_ROOM;
		_flags = 0;
		_disk = disk;
		
		scriptData = NULL;
		width = 0;
		height = 0;
		numObjects = 0;
		numZBuffers = 0;
	}


	RoomData::~RoomData() {
		close();
	}

	void RoomData::close(bool properties, bool scripts, bool graphics) {
		if (scripts) {
			deleteObject(scriptData);
		}

		if (properties) {
			width = 0;
			height = 0;
			numObjects = 0;
			numZBuffers = 0;
		}

		if (graphics) {
			deleteObject(graphicsData);
		}
	}
	
	bool RoomData::_readLFLF(DiskReader& reader, TagPair& lflf) {
		lflf = reader.readTagPair();

		if (lflf.isTag(GS_MAKE_ID('L','F','L','F')) == false) {
			error(COMI_THIS, "Could not read RoomData as its not a Room!", getNum());
			return false;
		}

		if (lflf.length == 0) {
			error(COMI_THIS, "Room length %ld is 0 bytes!", _num);
			return false;
		}

		return true;
	}
	
	bool RoomData::_readRoomData(DiskReader& reader, const TagPair& lflf, bool readProperties, bool readScripts, bool readGraphics) {
		
		if (readGraphics) {
			readProperties = true;
		}


		if (readProperties) {
			if (_readProperties(reader, lflf) == false)
				return false;
		}
		
		if (readScripts) {
			if (scriptData == NULL) {
				scriptData = newObject<RoomScriptData>();
			}
			else {
				scriptData->close();
			}

			if (scriptData->readFromDisk(reader, lflf, getNum()) == false)
				return false;
		}

		if (readGraphics) {
			if (graphicsData == NULL) {
				graphicsData = newObject<RoomGraphicsData>();
			}
			else {
				graphicsData->close();
			}
			graphicsData->open(width, height);

			if (graphicsData->readFromDisk(reader, lflf, getNum()) == false)
				return false;
		}

		return true;
	}

	bool RoomData::readFromDisk(DiskReader& reader, bool readProperties, bool readScripts, bool readGraphics) {

		TagPair lflf;
		if (_readLFLF(reader, lflf) == false)
			return false;

		close(true, true);

		return _readRoomData(reader, lflf, readProperties, readScripts, readGraphics);
	}

	bool RoomData::mergeFromDisk(DiskReader& reader, bool readProperties, bool readScripts, bool readGraphics) {

		TagPair lflf;
		if (_readLFLF(reader, lflf) == false)
			return false;

		return _readRoomData(reader, lflf, readProperties, readScripts, readGraphics);
	}

	bool RoomData::_readProperties(DiskReader& reader, const TagPair& lflf) {
		reader.seek(lflf);

		while (reader.pos() < lflf.end()) {
			TagPair roomPair = reader.readTagPair();

			if (roomPair.isTag(GS_MAKE_ID('R', 'O', 'O', 'M'))) {

				while (reader.pos() < roomPair.end()) {
					TagPair rmhdPair = reader.readTagPair();

					if (rmhdPair.isTag(GS_MAKE_ID('R', 'M', 'H', 'D'))) {
						reader.skip(sizeof(uint32));	// version
						width = reader.readUInt32LE();
						height = reader.readUInt32LE();
						numObjects = reader.readUInt32LE();
						reader.skip(sizeof(uint32));	// unknown
						numZBuffers = reader.readUInt32LE();

						debug(COMI_THIS, "(%ld, %ld, %ld, %ld)", (uint32) width, (uint32) height, (uint32) numObjects, (uint32) numZBuffers);

						return true;
					}

					reader.skip(rmhdPair);
				}

				break;
			}

			reader.skip(roomPair);
		}

		return false;
	}


	void startScene(uint16 roomNum) {

		RoomData* roomData;

		/* TODO: Stop Dialogue */

		VM->exitRoom();

		/* TODO: Hide All Actors */
		/* TODO: Stop Palette Cycling */
		/* TODO: Shadow Palette Handling */
		/* TODO: Graphics cleaning flags */

		INTS->room = roomNum;

		if (roomNum != 0) {
			roomData = RESOURCES->loadRoomData(roomNum);
		}

	}


}
