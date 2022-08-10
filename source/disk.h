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

#ifndef GS_DISK_H
#define GS_DISK_H

#include "forward.h"
#include "containers.h"
#include "string.h"
#include "file.h"
#include "endian.h"

namespace gs
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
		DiskReader(ReadFile& file, uint32 offset);
		~DiskReader();

		static DiskReader Null();

		bool isNull() const;

		template<typename Index>
		inline void readBytes(ReadWriteSpan<byte, Index>& span) {
			_file.readBytes(span.ptr(0), span.getSize());
		}

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
		
		inline int16 readInt16BE() {
			return _file.readInt16BE();
		}

		inline int32 readInt32BE() {
			return _file.readInt32BE();
		}

		inline int16 readInt16LE() {
			return _file.readInt16LE();
		}

		inline int32 readInt32LE() {
			return _file.readInt32LE();
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

		uint32 readFixedStringAsHash(uint8 fixedLength);

		inline uint32 pos() {
			return _file.pos();
		}

		inline void skip(int32 offset) {
			_file.skip(offset);
		}

		inline TagPair readTagPair() {
			TagPair pair;
			byte* tag = (byte*) &pair.tag;
			_file.readBytes(tag, 4);
			pair.length = _file.readUInt32BE() - 8;
			pair.dataPos = _file.pos();
			return pair;
		}

		inline TagPair readSanTagPair() {
			TagPair pair;
			byte* tag = (byte*) &pair.tag;
			_file.readBytes(tag, 4);
			pair.length = _file.readUInt32BE();

			// Round up to nearest even number.
			if (pair.length & 1) {
				pair.length++;
			}

			pair.dataPos = _file.pos();
			return pair;
		}

		inline bool readAndCompareTag(uint32 test, TagPair& tag) {
			tag = readTagPair();
			return tag.tag == test;
		}

		inline void seek(const TagPair& tagPair) {
			_file.seek(tagPair.dataPos);
		}

		inline void skip(const TagPair& tagPair) {
			_file.skip(tagPair.length);
		}

        inline void seekEndOf(const TagPair& tagPair) {
            _file.seek(tagPair.dataPos + tagPair.length);
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

		DiskReader openRoomForReading(uint16 roomNum) {
			uint32 offset = 0;
			
			if (getRoomOffset(roomNum, offset) == false) {
				error(GS_THIS, "Could not open room! %ld", (uint32) roomNum);
				abort_quit_stop();
			}

			return DiskReader(_file, offset);
		}

	};

}

#endif