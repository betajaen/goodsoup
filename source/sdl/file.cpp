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

#include "file_sdl.h"

#include "../debug.h"
#include "../endian.h"

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
			SDL_RWclose(_file);
		}

		_file = SDL_RWFromFile(path, "rb");
		_pos = 0;
		_length = 0;

		if (_file) {
			_length = SDL_RWsize(_file);
			debug(GS_THIS, "(%x, %s, %d) Opened.", this, path, _length);
		}
		else {
			error(GS_THIS, "(%x, %s) Did not open file.", this, path);
		}
	}

	void ReadFile::close() {
		if (_file) {
			SDL_RWclose(_file);
			_file = NULL;
			_pos = 0;
			_length = 0;
			debug(GS_THIS, "(%x) Closed", this);
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
		_pos = SDL_RWseek(_file, bytes, RW_SEEK_CUR);
		return _pos;
	}

	void ReadFile::seek(uint32 offset) {
		_pos = SDL_RWseek(_file, offset, RW_SEEK_SET);
	}

	byte ReadFile::readByte() {
		byte val;
		_pos += (uint32) SDL_RWread(_file, &val, sizeof(val), 1) * sizeof(val);
		return val;
	}

	uint32 ReadFile::readBytes(void* dst, uint32 length) {
		uint32 bytesRead = 0;
		bytesRead = (uint32)SDL_RWread(_file, dst, length, 1) * length;
		_pos += bytesRead;
		return bytesRead;
	}

	int16 ReadFile::readInt16LE() {
		int16 val;
		_pos += (uint32)SDL_RWread(_file, &val, sizeof(val), 1) * sizeof(val);
		val = TO_LE_16(val);
		return val;
	}

	int16 ReadFile::readInt16BE() {
		int16 val;
		_pos += (uint32)SDL_RWread(_file, &val, sizeof(val), 1) * sizeof(val);
		val = TO_BE_16(val);
		return val;
	}

	int32 ReadFile::readInt32LE() {
		int32 val;
		_pos += (uint32)SDL_RWread(_file, &val, sizeof(val), 1) * sizeof(val);
		val = TO_LE_32(val);
		return val;
	}

	int32 ReadFile::readInt32BE() {
		int32 val;
		_pos += (uint32)SDL_RWread(_file, &val, sizeof(val), 1) * sizeof(val);
		val = TO_BE_32(val);
		return val;
	}

	uint16 ReadFile::readUInt16LE() {
		uint16 val;
		_pos += (uint32)SDL_RWread(_file, &val, sizeof(val), 1) * sizeof(val);
		val = TO_LE_16(val);
		return val;
	}

	uint16 ReadFile::readUInt16BE() {
		uint16 val;
		_pos += (uint32)SDL_RWread(_file, &val, sizeof(val), 1) * sizeof(val);
		val = TO_BE_16(val);
		return val;
	}

	uint32 ReadFile::readUInt32LE() {
		uint32 val;
		_pos += (uint32)SDL_RWread(_file, &val, sizeof(val), 1) * sizeof(val);
		val = TO_LE_32(val);
		return val;
	}
	
	uint32 ReadFile::readUInt32BE() {
		uint32 val;
		_pos += (uint32)SDL_RWread(_file, &val, sizeof(val), 1) * sizeof(val);
		val = TO_BE_32(val);
		return val;
	}

	void ReadFile::readTag(char* tag) {
		_pos += (uint32)SDL_RWread(_file, tag, 4, 1) * 4;
	}

	bool fileExists(const char* path)
	{
		SDL_RWops* fp = SDL_RWFromFile(path, "rb");

		if (fp)
		{
			SDL_RWclose(fp);
			return true;
		}

		return false;
	}

}