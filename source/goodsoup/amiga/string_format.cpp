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

#include <proto/exec.h>

namespace gs
{
	typedef VOID(*PUTCHARPROC)();

	static const uint32 PutChar = 0x16c04e75;
	static const uint32 LenChar = 0x52934e75;
	
	String String::format(const char* fmt, ...) {
		uint32 length = 0;
		const char* arg = (const char*)(&fmt + 1);

		verbose(GS_THIS, "Len 1 %s", fmt);

		RawDoFmt((CONST_STRPTR)fmt, (APTR)arg, (PUTCHARPROC)&LenChar, &length);

		verbose(GS_THIS, "Len 2 %s %ld", fmt, length);

		if (length == 0) {
			return String();
		}

		if (length >= 65535) {
			error(GS_THIS, "String is to large %ld to fit into String", length);
			return String();
		}

		String str;
		str._reserve((uint16) length);
		char* strData = str._stringWritable();

		RawDoFmt((CONST_STRPTR)fmt, (APTR)arg, (PUTCHARPROC)&PutChar, strData);

		str._refreshHash();

		return str;
	}

	void String::format(String& str, const char* fmt, ...) {
		uint32 length = 0;
		const char* arg = (const char*)(&fmt + 1);

		verbose(GS_THIS, "Len 1 %s", fmt);

		RawDoFmt((CONST_STRPTR)fmt, (APTR)arg, (PUTCHARPROC)&LenChar, &length);

		verbose(GS_THIS, "Len 2 %s %ld", fmt, length);
		
		if (length == 0) {
			str.release();
			return;
		}

		if (length >= 65535) {
			error(GS_THIS, "String is to large %ld to fit into String", length);
			str.release();
			return;
		}

		str.release();
		str._reserve((uint16)length);
		char* strData = str._stringWritable();

		verbose(GS_THIS, "Len 2 %s %ld", fmt, length);

		RawDoFmt((CONST_STRPTR)fmt, (APTR)arg, (PUTCHARPROC)&PutChar, strData);

		verbose(GS_THIS, "Len 3 %s", strData);

		str._refreshHash();
	}

}