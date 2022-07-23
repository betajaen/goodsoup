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
#include "../hash.h"
#include "../string.h"

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

	byte* readFileIntoMemory(const char* path, uint32& length) {
		SDL_RWops* file = SDL_RWFromFile(path, "rb");
		if (file == NULL)
		{
			SDL_RWclose(file);
			return false;
		}

		byte* data = NULL;
		length = SDL_RWsize(file);

		data = (byte*) allocateMemory(1, length, 0);
		SDL_RWread(file, data, length, 1);

		SDL_RWclose(file);
		return data;
	}

    StringAppendFile::StringAppendFile()
        : _file(NULL) {
    }

    StringAppendFile::~StringAppendFile() {
        close();
    }

    void StringAppendFile::open(const char* path) {
        if (isOpen()) {
            close();
        }

        _file = SDL_RWFromFile(path, "wb");
    }

    void StringAppendFile::close() {
        if (_file) {
            SDL_RWclose(_file);
            _file = NULL;
        }
    }

    bool StringAppendFile::isOpen() const {
        return _file != NULL;
    }

    void StringAppendFile::writeChar(char ch) {
        writeBytes(&ch, 1);
    }

    void StringAppendFile::writeString(const char* str) {
        uint16 length = stringLength(str);
        writeBytes(str, length);
    }

    void StringAppendFile::writeFormat(const char* fmt, ...) {
        static char buffer[512];

        uint16 length = 0;
        va_list arg;
        va_start(arg, fmt);

        length = SDL_vsnprintf(NULL, 0, fmt, arg);

        if (length >= sizeof(buffer)) {
            error(GS_THIS, "String is to large %ld to fit into temporary buffer", length);
            return;
        }

        SDL_vsnprintf(buffer, length + 1 , fmt, arg);

        writeBytes(&buffer[0], length);

        va_end(arg);
    }

    void StringAppendFile::writeBytes(const void* buffer, uint16 length) {
        SDL_RWwrite(_file, buffer, length, 1);
    }



}