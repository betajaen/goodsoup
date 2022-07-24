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

#define GS_FILE_NAME "file"

#include "file_amiga.h"
#include "../debug.h"
#include "../endian.h"
#include "../memory.h"
#include "hash.h"

#include <proto/dos.h>


namespace gs
{

	ReadFile ReadFile::NullFile;

	ReadFile::ReadFile()
		: _file(NULL), _pos(0), _length(0) {

	}

	ReadFile::~ReadFile() {
		close();
	}

	void ReadFile::open(const char* path) {
		if (_file) {
			Close(_file);
		}

		_file = Open(path, MODE_OLDFILE);
		_pos = 0;
		_length = 0;

		if (_file) {
			Seek(_file, 0, OFFSET_END);
			_length = Seek(_file, 0, OFFSET_BEGINNING);
			debug(GS_THIS, "(0x%lx, %s, %ld) Opened.", this, path, _length);
		}
		else {
			error(GS_THIS, "(0x%lx, %s) Did not open file.", this, path);
		}
	}

	void ReadFile::close() {
		if (_file) {
			Close(_file);
			_file = NULL;
			_pos = 0;
			_length = 0;
			debug(GS_THIS, "(0x%lx) Closed", this);
		}
	}

	bool ReadFile::isOpen() const {
		return _file;
	}

	bool ReadFile::isEof() const {
		return !(_pos < _length);
	}

	uint32 ReadFile::pos() const {
		return _pos;
	}

	uint32 ReadFile::length() const {
		return _length;
	}

	int32 ReadFile::skip(uint32 bytes) {
		Seek(_file, bytes, OFFSET_CURRENT);
		_pos = Seek(_file, 0, OFFSET_CURRENT);
		return _pos;
	}

	void ReadFile::seek(uint32 position) {
		Seek(_file, position, OFFSET_BEGINNING);
		_pos = Seek(_file, 0, OFFSET_CURRENT);
	}

	byte ReadFile::readByte() {
		byte val;
		_pos += (uint32)Read(_file, &val, sizeof(val));
		return val;
	}

	uint32 ReadFile::readBytes(void* dst, uint32 length) {
		uint32 bytesRead = 0;
		bytesRead = (uint32)Read(_file, dst, length);
		_pos += bytesRead;
		return bytesRead;
	}

	uint32 ReadFile::readFixedStringAsHash(uint8 fixedLength) {
		HashBuilder hash;
		uint32 end = pos() + fixedLength;

		for(uint8 i=0;i < fixedLength;i++) {
			char ch = readByte();

			if (ch == 0)
				break;

			hash.feed(ch);
		}

		seek(end);

		return hash.hash;
	}

	int16 ReadFile::readInt16LE() {
		int16 val;
		_pos += (uint32)Read(_file, &val, sizeof(val));
		val = TO_LE_16(val);
		return val;
	}

	int16 ReadFile::readInt16BE() {
		int16 val;
		_pos += (uint32)Read(_file, &val, sizeof(val));
		val = TO_BE_16(val);
		return val;
	}

	int32 ReadFile::readInt32LE() {
		int32 val;
		_pos += (uint32)Read(_file, &val, sizeof(val));
		val = TO_LE_32(val);
		return val;
	}

	int32 ReadFile::readInt32BE() {
		int32 val;
		_pos += (uint32)Read(_file, &val, sizeof(val));
		val = TO_BE_32(val);
		return val;
	}

	uint16 ReadFile::readUInt16LE() {
		uint16 val;
		_pos += (uint32)Read(_file, &val, sizeof(val));
		val = TO_LE_16(val);
		return val;
	}

	uint16 ReadFile::readUInt16BE() {
		uint16 val;
		_pos += (uint32)Read(_file, &val, sizeof(val));
		val = TO_BE_16(val);
		return val;
	}

	uint32 ReadFile::readUInt32LE() {
		uint32 val;
		_pos += (uint32)Read(_file, &val, sizeof(val));
		val = TO_LE_32(val);
		return val;
	}

	uint32 ReadFile::readUInt32BE() {
		uint32 val;
		_pos += (uint32)Read(_file, &val, sizeof(val));
		val = TO_BE_32(val);
		return val;
	}

	void ReadFile::readTag(char* tag) {
		_pos += (uint32)Read(_file, tag, 4);
	}

	bool fileExists(const char* path)
	{
		BPTR file = Open(path, MODE_OLDFILE);

		if (file)
		{
			Close(file);
			return true;
		}

		return false;
	}

	byte* readFileIntoMemory(const char* path, uint32& length) {
		BPTR file = Open(path, MODE_OLDFILE);
		if (file == NULL)
		{
			Close(file);
			return NULL;
		}

		byte* data = NULL;
		Seek(file, 0, OFFSET_END);
		length = Seek(file, 0, OFFSET_BEGINNING);

		data = (byte*) allocateMemory(1, length, 0);
		Read(file, data, length);

		Close(file);
		return data;
	}

}
