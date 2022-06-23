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

#ifndef COMI_DISK_H
#define COMI_DISK_H

#include "common/types.h"
#include "common/buffer.h"
#include "common/string.h"
#include "common/file.h"
#include "common/endian.h"

using namespace common;

namespace comi
{
	struct TagPair {
		uint32 tag;
		uint32 length;
		uint32 dataPos;

		const char* tagStr() const {
			static char str[5] = {0};
			*((uint32*) &str[0]) = tag;
			return &str[0];
		}

		bool isTag(uint32 name) const {
			return tag == name;
		}
		
		bool isTag(uint32 name1, uint32 name2) const {
			return tag == name1 || tag == name2;
		}
		
		bool isTag(uint32 name1, uint32 name2, uint32 name3) const {
			return tag == name1 || tag == name2 || tag == name3;
		}
		
		bool isTag(uint32 name1, uint32 name2, uint32 name3, uint32 name4) const {
			return tag == name1 || tag == name2 || tag == name3 || tag == name4;
		}

		uint32 end() const {
			return dataPos + length;
		}

	};

	class DiskReader {
	private:
		ReadFile& _file;
	public:

		DiskReader(ReadFile& file);
		~DiskReader();

		inline void readBytes(Buffer<byte>& buffer, uint16 length) {
			buffer.setSize(length, 0);
			_file.readBytes(buffer.ptr(0), length);
		}

		inline void readBytes(void* data, uint32 length) {
			_file.readBytes(data, length);
		}

		inline byte readByte() {
			return _file.readByte();
		}

		inline uint16 readUInt16BE() {
			return _file.readUInt16BE();
		}

		inline uint32 readUInt32BE() {
			return _file.readUInt32BE();
		}

		inline uint16 readUInt16LE() {
			return _file.readUInt16LE();
		}

		inline uint32 readUInt32LE() {
			return _file.readUInt32LE();
		}

		inline void seek(uint32 pos) {
			_file.seek(pos);
		}

		inline uint32 pos() {
			return _file.pos();
		}

		inline void skip(uint32 length) {
			_file.skip(length);
		}

		inline TagPair readTagPair() {
			TagPair pair;
			byte* tag = (byte*) &pair.tag;
			_file.readBytes(tag, 4);
			pair.length = _file.readUInt32BE() - 8;
			pair.dataPos = _file.pos();
			return pair;
		}

		inline void seek(const TagPair& tagPair) {
			_file.seek(tagPair.dataPos);
		}

		inline void skip(const TagPair& tagPair) {
			_file.skip(tagPair.length);
		}

		void readTagAndLength(char tag[5], uint32& length);

		bool readAndExpectTag(char a, char b, char c, char d);
		bool readAndExpectTag(const char* test);

		uint32 sumBytesWithin(uint32 rangeBytes, uint32 numTags, const char** tags, uint32& out_count);

	};

	class Disk {
	private:

		struct RoomOffset {
			uint8 _room;
			uint32 _offset;
		};

		uint8 _num;
		uint8 _minRoomOffset, _maxRoomOffset;
		Buffer<RoomOffset, uint8> _roomOffsets;
		ReadFile _file;

		bool _readSections();
		bool _readRoomOffsets();

	public:

		Disk();
		~Disk();

		bool open(uint8 num);
		void close();

		bool getRoomOffset(uint8 num, uint32& offset) const;

		DiskReader readSection(uint32 offset);

	};

}

#endif