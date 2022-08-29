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

#define GS_FILE_NAME "string"

#include "../memory.h"
#include "../string.h"

#include <SDL2/SDL.h>

namespace gs
{
	String String::format(const char* fmt, ...) {
		int32 length = 0;
		va_list arg;
		va_start(arg, fmt);

		length = SDL_vsnprintf(NULL, 0, fmt, arg);

		if (length <= 0) {
			warn(GS_THIS, "Empty string created from String::format");
			return String();
		}

		if (length >= 65535) {
			error(GS_THIS, "String is to large %ld to fit into String", length);
			return String();
		}

		String str;
		str._reserve((uint16)length);
		char* strData = str._stringWritable();

		SDL_vsnprintf(strData, length +1 , fmt, arg);

		va_end(arg);
		return str;
	}

	void String::format(String& str, const char* fmt, ...) {
		int32 length = 0;
		va_list arg;
		va_start(arg, fmt);

		length = SDL_vsnprintf(NULL, 0, fmt, arg);

		verbose(GS_THIS, "%s -> %ld", fmt, length);

		if (length <= 0) {
			warn(GS_THIS, "Empty string created from String::format");
			str.release();
			return;
		}

		if (length >= 65535) {
			error(GS_THIS, "String is to large %ld to fit into String", length);
			str.release();
			return;
		}

		str._reserve((uint16)length);
		char* strData = str._stringWritable();

		SDL_vsnprintf(strData, length + 1, fmt, arg);

		va_end(arg);
	}

}