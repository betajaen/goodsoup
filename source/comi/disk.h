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

using namespace common;

namespace comi
{

	class DiskReader {
	private:
		ReadFile& _file;
	public:

		DiskReader(ReadFile& file);
		~DiskReader();

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

		bool readAndExpectTag(char a, char b, char c, char d);

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