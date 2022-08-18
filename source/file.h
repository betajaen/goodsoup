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

#ifndef GS_FILE_H
#define GS_FILE_H

#include "forward.h"

#if defined(GS_AMIGA)
#define GS_FILE_HANDLE gs::int32
#else
typedef struct SDL_RWops SDL_RWops;
#define GS_FILE_HANDLE SDL_RWops*
#endif

namespace gs
{

	class ReadFile
	{
	public:

		static ReadFile NullFile;

		ReadFile();
		~ReadFile();

		void open(const char* path, bool throwErrorIsNotOpen = true);
		void close();

		bool isOpen() const;
		bool isEof() const;

		uint32 pos() const;
		uint32 length() const;

		void seek(uint32 position);
		uint32 skip(int32 offset);

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
		GS_FILE_HANDLE	_file;
		uint32			_length, _pos;
	};

	class WriteFile
	{
	public:

		WriteFile();
		~WriteFile();

		void open(const char* path);
		void close();

		bool isOpen();

		void writeByte(byte byte);
		void writeBytes(const void* data, uint32 length);

		void writeUInt16LE(uint16 value);
		void writeUInt16BE(uint16 value);
		void writeUInt32LE(uint32 value);
		void writeUInt32BE(uint32 value);

		void writeInt16LE(int16 value);
		void writeInt16BE(int16 value);
		void writeInt32LE(int32 value);
		void writeInt32BE(int32 value);

		void writeTag(const char* tagName);

	protected:
		GS_FILE_HANDLE	_file;
	};

#if !defined(GS_AMIGA)
	class StringAppendFile {

    public:

        StringAppendFile();
        ~StringAppendFile();

        void open(const char* path);
        void close();

        bool isOpen() const;
        bool isEof() const;

        void writeChar(char ch);
        void writeString(const char* str);
        void writeFormat(const char* fmt, ...);
        void writeBytes(const void* dst, uint16 length);

    protected:
        SDL_RWops* _file;
    };
#endif

	bool fileExists(const char* path);

	byte* readFileIntoMemory(const char* path, uint32& length, uint32 comment);

	bool writeFileFromMemory(const char* path, uint32 length, const void* data);

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

	class TagReadFile {

		ReadFile _file;

	public:

		inline TagReadFile()
			: _file() {
		}

		inline ~TagReadFile() {
			close();
		}

		inline void open(const char* path, bool throwErrorIsNotOpen = true) {
			_file.open(path, throwErrorIsNotOpen);
		}

		inline void close() {
			_file.close();
		}

		inline bool isOpen() const {
			return _file.isOpen();
		}

		template<typename Index>
		inline void readBytes(ReadWriteSpan<byte, Index>& span) {
			_file.readBytes(span.ptr(0), span.getSize());
		}

		void readBytes(Buffer<byte>& buffer, uint16 length);

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

		inline uint32 pos() const {
			return _file.pos();
		}

		inline uint32 length() const {
			return _file.length();
		}

		inline void skip(int32 offset) {
			_file.skip(offset);
		}

		inline TagPair readTag() {

			TagPair pair;
			byte* tag = (byte*) &pair.tag;
			_file.readBytes(tag, 4);
			pair.length = 0;
			pair.dataPos = _file.pos();

			return pair;
		}

		inline TagPair readTagPair() {
			TagPair pair;
			byte* tag = (byte*) &pair.tag;
			_file.readBytes(tag, 4);
			pair.length = _file.readUInt32BE() - 8;
			pair.dataPos = _file.pos();

			return pair;
		}

		inline TagPair readSanTagPair(bool roundUp) {
			TagPair pair;
			byte* tag = (byte*) &pair.tag;
			_file.readBytes(tag, 4);
			pair.length = _file.readUInt32BE();
			pair.dataPos = _file.pos();

			if (roundUp) {
				// Round up to nearest even number.
				if (pair.length & 1) {
					pair.length++;
				}
			}

			return pair;
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

	};

}


#endif
