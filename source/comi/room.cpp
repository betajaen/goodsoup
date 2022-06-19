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
	}


	RoomData::~RoomData() {

	}
	
	bool RoomData::readFromDisk(DiskReader& reader) {
		return _readLFLF(reader);
	}

	bool RoomData::_readLFLF(DiskReader& reader) {

		char tagName[5] = { 0 };
		uint32 tagLength = 0;

		reader.readTagAndLength(tagName, tagLength);

		if (tagEqual(tagName, 'L', 'F', 'L', 'F') == false) {
			
			error(COMI_THIS, "Could not read RoomData as its not a Room!", getNum());
			return false;
		}

		if (tagLength == 0) {
			error(COMI_THIS, "Script length %ld is 0 bytes!", _num);
			return false;
		}

		uint32 end = reader.pos() + tagLength - 8;

		while (reader.pos() < end) {
			reader.readTagAndLength(tagName, tagLength);
			
			debug(COMI_THIS, "%s %ld", tagName, tagLength);

			if (tagEqual(tagName, 'R', 'O', 'O', 'M')) {
				if (_readRoom(reader, tagLength) == false) {
					return false;
				}

				continue;
			}
			
			NO_FEATURE(COMI_THIS, "Unhandled LFLF tag %s", tagName);
			reader.skip(tagLength - 8);
		}

		return true;
	}
	
	bool RoomData::_readRoom(DiskReader& reader, uint32 totalLength) {
		
		char tagName[5] = { 0 };
		uint32 tagLength = 0;

		uint32 end = reader.pos() + totalLength - 8;
		
		while (reader.pos() < end) {
			
			reader.readTagAndLength(tagName, tagLength);

			debug(COMI_THIS, "+ %s %ld", tagName, tagLength);

			if (tagEqual(tagName, 'R', 'M', 'H', 'D')) {
				_readRMHD(reader, tagLength);
				continue;
			}
			
			if (tagEqual(tagName, 'C', 'Y', 'C', 'L')) {
				_readCYCL(reader, tagLength);
				continue;
			}

			NO_FEATURE(COMI_THIS, "Unhandled ROOM tag %s", tagName);
			reader.skip(tagLength - 8);
		}

		return true;
	}

	void RoomData::_readRMHD(DiskReader& reader, uint32 tagLength) {
		reader.readUInt32BE();	// Version
		width = reader.readUInt32LE();
		height = reader.readUInt32LE();
		numObjects = reader.readUInt32LE();
		reader.readUInt32BE();	// Unknown
		numZBuffers = reader.readUInt32LE();

		debug(COMI_THIS, "width=%ld height=%ld numObjects=%ld numZBuffers=%ld", (uint32) width, (uint32) height, (uint32) numObjects, (uint32) numZBuffers);
	}
	
	void RoomData::_readCYCL(DiskReader& reader, uint32 tagLength) {

		while (true) {
			uint8 idx = reader.readByte();
			if (idx == 0)
				break;

			ColourCycle cycle;
			cycle.counter = 0;
			cycle.delay = 16384 / reader.readUInt16BE();
			cycle.flags = reader.readUInt16BE();
			cycle.start = reader.readByte();
			cycle.end = reader.readByte();

			colourCycle[idx - 1] = cycle;
		}

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
