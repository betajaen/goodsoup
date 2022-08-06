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
#include "debug.h"
#include "hash.h"
#include "endian.h"

#if defined(GS_AMIGA)
#include <proto/dos.h>
#else
#include <SDL2/SDL_rwops.h>
#endif

namespace gs
{
	ReadFile ReadFile::NullFile;

	ReadFile::ReadFile() {
		_file = 0;
		_length = 0;
		_pos = 0;
	}

	ReadFile::~ReadFile() {
		close();
	}

	void ReadFile::open(const char* path, bool throwErrorIsNotOpen) {

		if (isOpen()) {
			close();
		}

#if defined(GS_AMIGA)
		_file = Open(path, MODE_OLDFILE);
#else
		_file = SDL_RWFromFile(path, "rb");
#endif
		_pos = 0;
		_length = 0;

		if (_file != 0) {

#if defined(GS_AMIGA)
			Seek(_file, 0, OFFSET_END);
			_length = Seek(_file, 0, OFFSET_BEGINNING);
#else
			_length = SDL_RWsize(_file);
#endif

			debug(GS_THIS, "(0x%lx, %s, %ld) Opened.", this, path, _length);
		}
		else {
			if (throwErrorIsNotOpen) {
				error(GS_THIS, "(0x%lx, %s) Did not open file.", this, path);
			}
		}
	}

	void ReadFile::close() {
		if (_file != 0) {
#if defined(GS_AMIGA)
			Close(_file);
#else
			SDL_RWclose(_file);
#endif
			_file = 0;
			_pos = 0;
			_length = 0;
		}
	}

	bool ReadFile::isOpen() const {
		return (_file != 0);
	}

	bool ReadFile::isEof() const {
		return _pos >= _length;
	}

	uint32 ReadFile::pos() const {
		return _pos;
	}

	uint32 ReadFile::length() const {
		return _length;
	}

	void ReadFile::seek(uint32 position) {
#if defined(GS_AMIGA)
		Seek(_file, position, OFFSET_BEGINNING);
		_pos = Seek(_file, 0, OFFSET_CURRENT);
#else
		_pos = SDL_RWseek(_file, position, RW_SEEK_SET);
#endif
	}

	uint32 ReadFile::skip(int32 offset) {
#if defined(GS_AMIGA)
		Seek(_file, offset, OFFSET_CURRENT);
		_pos = Seek(_file, 0, OFFSET_CURRENT);
		return _pos;
#else
		_pos = SDL_RWseek(_file, offset, RW_SEEK_CUR);
		return _pos;
#endif
	}

	uint32 ReadFile::readFixedStringAsHash(uint8 fixedLength) {
		HashBuilder hash;
		uint32 end = _pos + fixedLength;

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
#if defined(GS_AMIGA)
		byte val;
		_pos += (uint32)Read(_file, &val, sizeof(val));
		return val;
#else
		byte val;
		_pos += (uint32) SDL_RWread(_file, &val, sizeof(val), 1) * sizeof(val);
		return val;
#endif
	}

	uint32 ReadFile::readBytes(void* dst, uint32 length) {
#if defined(GS_AMIGA)
		uint32 bytesRead = 0;
		bytesRead = (uint32)Read(_file, dst, length);
		_pos += bytesRead;
		return bytesRead;
#else
		uint32 bytesRead = 0;
		bytesRead = (uint32)SDL_RWread(_file, dst, length, 1) * length;
		_pos += bytesRead;
		return bytesRead;
#endif
	}

	uint16 ReadFile::readUInt16LE() {
		uint16 val;
#if defined(GS_AMIGA)
		_pos += (uint32)Read(_file, &val, sizeof(val));
		val = (uint16) SWAP_BYTES_16(val);
#else
		_pos += (uint32)SDL_RWread(_file, &val, sizeof(val), 1) * sizeof(val);
#endif
		return val;
	}

	uint16 ReadFile::readUInt16BE() {
		uint16 val;
#if defined(GS_AMIGA)
		_pos += (uint32)Read(_file, &val, sizeof(val));
#else
		_pos += (uint32)SDL_RWread(_file, &val, sizeof(val), 1) * sizeof(val);
		val = (uint16) SWAP_BYTES_16(val);
#endif
		return val;
	}

	uint32 ReadFile::readUInt32LE() {
		uint32 val;
#if defined(GS_AMIGA)
		_pos += (uint32)Read(_file, &val, sizeof(val));
		val = (uint32) SWAP_BYTES_32(val);
#else
		_pos += (uint32)SDL_RWread(_file, &val, sizeof(val), 1) * sizeof(val);
#endif
		return val;
	}

	uint32 ReadFile::readUInt32BE() {
		uint32 val;
#if defined(GS_AMIGA)
		_pos += (uint32)Read(_file, &val, sizeof(val));
#else
		_pos += (uint32)SDL_RWread(_file, &val, sizeof(val), 1) * sizeof(val);
		val = (uint32) SWAP_BYTES_32(val);
#endif
		return val;
	}

	int16 ReadFile::readInt16LE() {
		int16 val;
#if defined(GS_AMIGA)
		_pos += (uint32)Read(_file, &val, sizeof(val));
		val = (int16) SWAP_BYTES_16(val);
#else
		_pos += (uint32)SDL_RWread(_file, &val, sizeof(val), 1) * sizeof(val);
#endif
		return val;
	}

	int16 ReadFile::readInt16BE() {
		int16 val;
#if defined(GS_AMIGA)
		_pos += (uint32)Read(_file, &val, sizeof(val));
#else
		_pos += (uint32)SDL_RWread(_file, &val, sizeof(val), 1) * sizeof(val);
		val = (int16) SWAP_BYTES_16(val);
#endif
		return val;
	}

	int32 ReadFile::readInt32LE() {
		int32 val;
#if defined(GS_AMIGA)
		_pos += (uint32)Read(_file, &val, sizeof(val));
		val = (int32) SWAP_BYTES_32(val);
#else
		_pos += (uint32)SDL_RWread(_file, &val, sizeof(val), 1) * sizeof(val);
#endif
		return val;
	}

	int32 ReadFile::readInt32BE() {
		int32 val;
#if defined(GS_AMIGA)
		_pos += (uint32)Read(_file, &val, sizeof(val));
#else
		_pos += (uint32)SDL_RWread(_file, &val, sizeof(val), 1) * sizeof(val);
		val = (int32) SWAP_BYTES_32(val);
#endif
		return val;
	}

	void ReadFile::readTag(char* tag) {
#if defined(GS_AMIGA)
		_pos += (uint32)Read(_file, tag, 4);
#else
		_pos += (uint32)SDL_RWread(_file, tag, 4, 1) * 4;
#endif
	}


	WriteFile::WriteFile() {
		_file = 0;
	}

	WriteFile::~WriteFile() {
		close();
	}

	void WriteFile::open(const char* path) {
		if (isOpen()) {
			close();
		}

#if defined(GS_AMIGA)
		_file = Open(path, MODE_NEWFILE);
#else
		_file = SDL_RWFromFile(path, "wb");
#endif
	}

	void WriteFile::close() {
		if (_file != 0) {
#if defined(GS_AMIGA)
			Close(_file);
#else
			SDL_RWclose(_file);
#endif
			_file = 0;
		}
	}

	bool WriteFile::isOpen() {
		return _file != 0;
	}

	void WriteFile::writeByte(byte byte) {
#if defined(GS_AMIGA)
		Write(_file, &byte, 1);
#else
		SDL_RWwrite(_file, &byte, 1, 1);
#endif
	}

	void WriteFile::writeBytes(const void* data, uint32 length) {
#if defined(GS_AMIGA)
		Write(_file, (APTR) data, length);
#else
		SDL_RWwrite(_file, data, length, 1);
#endif
	}

	void WriteFile::writeUInt16LE(uint16 value) {
#if defined(GS_AMIGA)
		value = (uint16) SWAP_BYTES_16(value);
		Write(_file, (APTR) &value, sizeof(value));
#else
		SDL_RWwrite(_file, &value, sizeof(value), 1);
#endif
	}

	void WriteFile::writeUInt16BE(uint16 value) {
#if defined(GS_AMIGA)
		Write(_file, (APTR) &value, sizeof(value));
#else
		value = (uint16) SWAP_BYTES_16(value);
		SDL_RWwrite(_file, &value, sizeof(value), 1);
#endif
	}

	void WriteFile::writeUInt32LE(uint32 value) {
#if defined(GS_AMIGA)
		value = (uint32) SWAP_BYTES_32(value);
		Write(_file, (APTR) &value, sizeof(value));
#else
		SDL_RWwrite(_file, &value, sizeof(value), 1);
#endif
	}

	void WriteFile::writeUInt32BE(uint32 value) {
#if defined(GS_AMIGA)
		Write(_file, (APTR) &value, sizeof(value));
#else
		value = (uint32) SWAP_BYTES_32(value);
		SDL_RWwrite(_file, &value, sizeof(value), 1);
#endif
	}

	void WriteFile::writeInt16LE(int16 value) {
#if defined(GS_AMIGA)
		value = (int16) SWAP_BYTES_16(value);
		Write(_file, (APTR) &value, sizeof(value));
#else
		SDL_RWwrite(_file, &value, sizeof(value), 1);
#endif
	}

	void WriteFile::writeInt16BE(int16 value) {
#if defined(GS_AMIGA)
		Write(_file, (APTR) &value, sizeof(value));
#else
		value = (int16) SWAP_BYTES_16(value);
		SDL_RWwrite(_file, &value, sizeof(value), 1);
#endif
	}

	void WriteFile::writeInt32LE(int32 value) {
#if defined(GS_AMIGA)
		value = (int32) SWAP_BYTES_32(value);
		Write(_file, (APTR) &value, sizeof(value));
#else
		SDL_RWwrite(_file, &value, sizeof(value), 1);
#endif
	}

	void WriteFile::writeInt32BE(int32 value) {
#if defined(GS_AMIGA)
		Write(_file, (APTR) &value, sizeof(value));
#else
		value = (int32) SWAP_BYTES_32(value);
		SDL_RWwrite(_file, &value, sizeof(value), 1);
#endif
	}

#if !defined(GS_AMIGA)

	StringAppendFile::StringAppendFile()
			: _file(0) {
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
#endif


	bool fileExists(const char* path) {
#if defined(GS_AMIGA)
		BPTR file = Open(path, MODE_OLDFILE);

		if (file)
		{
			Close(file);
			return true;
		}

		return false;

#else
		SDL_RWops* fp = SDL_RWFromFile(path, "rb");

		if (fp)
		{
			SDL_RWclose(fp);
			return true;
		}

		return false;
#endif
	}

	byte* readFileIntoMemory(const char* path, uint32& length) {
#if defined(GS_AMIGA)
		BPTR file = Open(path, MODE_OLDFILE);
		if (file == NULL)
		{
			return NULL;
		}

		byte* data = NULL;
		Seek(file, 0, OFFSET_END);
		length = Seek(file, 0, OFFSET_BEGINNING);

		data = (byte*) allocateMemory(1, length, 0, GS_COMMENT_FILE_LINE);
		Read(file, data, length);

		Close(file);
		return data;
#else
		SDL_RWops* file = SDL_RWFromFile(path, "rb");
		if (file == NULL)
		{
			SDL_RWclose(file);
			return NULL;
		}

		byte* data = NULL;
		length = SDL_RWsize(file);

		data = (byte*) allocateMemory(1, length, 0, GS_COMMENT_FILE_LINE);
		SDL_RWread(file, data, length, 1);

		SDL_RWclose(file);
		return data;
#endif
	}

	bool writeFileFromMemory(const char* path, uint32 length, const void* data) {
#if defined(GS_AMIGA)
		BPTR file = Open(path, MODE_NEWFILE);

		if (file == NULL) {
			return false;
		}

		Write(file, (APTR) data, length);
		Close(file);

		return true;
#else
		SDL_RWops* file = SDL_RWFromFile(path, "wb");
		if (file == NULL)
		{
			return false;
		}

		SDL_RWwrite(file, data, length, 1);
		SDL_RWclose(file);
		return true;
#endif
	}

}
