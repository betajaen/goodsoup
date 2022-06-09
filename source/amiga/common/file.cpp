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

#include "file.h"

#include <proto/dos.h>

#include "common/debug.h"
#include "common/endian.h"

namespace common
{

	ReadFile::ReadFile()
		: _file(NULL) {

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
			info(GS_THIS, "(%x, %s, %d) Opened.", this, path, _length);
		}
		else {
			error(GS_THIS, "(%x, %s) Did not open file.", this, path);
		}
	}

	void ReadFile::close() {
		if (_file) {
			Close(_file);
			_file = NULL;
			_pos = 0;
			_length = 0;
			info(GS_THIS, "(%x) Closed");
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
		_pos = Seek(_file, bytes, OFFSET_CURRENT);
		return _pos;
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

}