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

#include "../types.h"

namespace gs
{
	class ReadFile
	{
	public:

		static ReadFile NullFile;

		ReadFile();
		~ReadFile();

		void open(const char* path);
		void close();

		bool isOpen() const;
		bool isEof() const;

		uint32 pos() const;
		uint32 length() const;

		void seek(uint32 position);
		int32 skip(uint32 bytes);

		uint32 readFixedStringAsHash(uint8 fixedLength);
		byte readByte();
		uint32 readBytes(void* dst, uint32 length);
		uint16 readUInt16LE();
		uint16 readUInt16BE();
		uint32 readUInt32LE();
		uint32 readUInt32BE();

		int16 readInt16LE();
		int16 readInt16BE();
		int32 readInt32LE();
		int32 readInt32BE();

		void readTag(char* tag);

	protected:
		ULONG      _file;
		uint32     _length, _pos;
	};

	bool fileExists(const char* path);

	byte* readFileIntoMemory(const char* path, uint32& length);

}
