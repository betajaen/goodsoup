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

#define GS_FILE_NAME "disk"

#include "resource.h"
#include "index.h"
#include "resource_data.h"
#include "room.h"
#include "script.h"

#include "utils.h"
#include "debug.h"
#include "profile.h"
#include "hash.h"

namespace gs
{

	static inline void checkTag(char tagName[5], uint32 pos)
	{
#if GS_CHECKED == 1
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
#endif
	}

	Disk::Disk() {
	}

	Disk::~Disk() {
		close();
	}

	bool Disk::open(uint8 num) {
		_num = num;
		verbose(GS_THIS, "Building path for Disk %ld", num);
		String path;
		String::format(path, "%s" GS_DISK_FILENAME_PATTERN, GS_GAME_PATH, num);
		verbose(GS_THIS, "Opening Disk %ld at %s", num, path.string());
		_file.open(path.string());

		if (_file.isOpen() == false)
			return false;
	
		info(GS_THIS, "Opened Disk %ld at %s", num, path.string());
	
		return _readSections();
	}

	void Disk::close() {
		_file.close();
		_roomOffsets.release();
	}

	bool Disk::_readSections() {
		uint32 tagLength;
		char tagName[5] = { 0 };


		_file.readTag(tagName);
		tagLength = _file.readUInt32BE();

#if GS_CHECKED==1
		// File header
		if (tagEqual(tagName, 'L', 'E', 'C', 'F') == false) {
			error(GS_THIS, "Disk %ld is not a COMI.LA%ld file!", _num, _num);
			return false;
		}
#endif

#if GS_CHECKED==1
		// Reasonable tag length;
		if (tagLength < 10000) {
			error(GS_THIS, "Disk %ld is probably not a COMI.LA%ld file!", _num, _num);
			return false;
		}
#endif

		
		while (_file.isEof() == false) {
			_file.readTag(tagName);

			checkTag(tagName, _file.pos());
			tagLength = _file.readUInt32BE();

			if (tagEqual(tagName, 'L', 'O', 'F', 'F') == true) {
				_readRoomOffsets();
				continue;
			}

			if (tagEqual(tagName, 'L', 'F', 'L', 'F') == true) {
				// Purposely unhandled.
				_file.skip(tagLength - 8);
				continue;
			}

			warn(GS_THIS, "(%s, %ld, %ld) Unhandled Tag!", tagName, tagLength, _file.pos());

			_file.skip(tagLength - 8);
		}

		info(GS_THIS, "Read Disk File at %sCOMI.LA%ld", GS_GAME_PATH, (uint32)_num);

		return true;
	}

	bool Disk::_readRoomOffsets() {
		uint8 _numRooms = _file.readByte();
		_roomOffsets.setSize(_numRooms);
		_minRoomOffset = 255;
		_maxRoomOffset = 0;

		for (uint8 i = 0; i < _numRooms;i++) {
			RoomOffset& offset = _roomOffsets.get_unchecked(i);
			offset._room = _file.readByte();
			offset._offset = _file.readUInt32LE();

			if (offset._room < _minRoomOffset) {
				_minRoomOffset = offset._room;
			}

			if (offset._room > _maxRoomOffset) {
				_maxRoomOffset = offset._room;
			}
		}

		return true;
	}

	bool Disk::getRoomOffset(uint8 num, uint32& offset) const {
		if (num < _minRoomOffset) {
			return false;
		}

		if (num > _maxRoomOffset) {
			return false;
		}

		const uint8 size = _roomOffsets.getSize();

		for (uint8 i = 0; i < size; i++) {
			const RoomOffset& roomOffset = _roomOffsets.get_unchecked(i);

			if (roomOffset._room == num) {
				offset = roomOffset._offset;
				return true;
			}
		}

		return false;
	}

	DiskReader Disk::readSection(uint32 offset) {
		_file.seek(offset);

		return DiskReader(_file);
	}


	DiskReader::DiskReader(ReadFile& file)
		: _file(file) {
	}
	
	DiskReader::DiskReader(ReadFile& file, uint32 offset)
		: _file(file) {
		_file.seek(offset);
	}

	DiskReader::~DiskReader() {
	}

	bool DiskReader::isNull() const {
		return _file.isOpen() == false;
	}

	DiskReader DiskReader::Null() {
		return DiskReader(ReadFile::NullFile, 0UL);
	}

	bool DiskReader::readAndExpectTag(char a, char b, char c, char d) {

		char tagName[5] = { 0 };
		_file.readTag(tagName);

		return tagEqual(tagName, a, b, c, d);
	}
	
	bool DiskReader::readAndExpectTag(const char* test) {
		char tagName[5] = { 0 };
		_file.readTag(tagName);

		return tagEqual(test, tagName);
	}

	void DiskReader::readTagAndLength(char tag[5], uint32& length) {
		_file.readTag(tag);
		length = _file.readUInt32BE();
	}

	uint32 DiskReader::readFixedStringAsHash(uint8 fixedLength) {
		HashBuilder hash;
		uint32 end = _file.pos() + fixedLength;

		for(uint8 i=0;i < fixedLength;i++) {
			char ch = _file.readByte();

			if (ch == 0)
				break;

			hash.feed(ch);
		}

		_file.seek(end);

		return hash.hash;
	}

	uint32 DiskReader::sumBytesWithin(uint32 rangeBytes, uint32 numTags, const char** tags, uint32& out_count) {
		uint32 origin = _file.pos();
		uint32 end = rangeBytes;
		uint32 numBytes = 0;
		out_count = 0;

		char tagName[5] = { 0 };
		uint32 tagLength = 0;

		while (_file.pos() < end) {
			_file.readTag(tagName);
			tagLength = _file.readUInt32BE();

			for (uint32 i = 0; i < numTags; i++) {
				const char* testTag = tags[i];

				if (tagEqual(testTag, tagName)) {
					numBytes += tagLength - 8;
					out_count++;
					break;
				}
			}

			_file.skip(tagLength - 8);
		}

		_file.seek(origin);

		return numBytes;

	}
}
