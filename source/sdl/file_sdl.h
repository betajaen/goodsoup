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

#include <SDL2/SDL.h>

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

			int32 skip(uint32 bytes);
			void seek(uint32 offset);

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
			SDL_RWops* _file;
			uint32     _length, _pos;
	};

	bool fileExists(const char* path);

	byte* readFileIntoMemory(const char* path, uint32& length);

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
}
