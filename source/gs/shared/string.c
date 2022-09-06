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

#include "shared/error.h"
// shared/error.c
extern int gs_StartedFromCli;

#if defined(GS_AMIGA)

#include <proto/exec.h>
#include "shared/sdi/SDI_stdarg.h"

typedef VOID(*PUTCHARPROC)();

static const uint32 PutChar = 0x16c04e75;
static const uint32 LenChar = 0x52934e75;

#endif

uint32 gs_format(char* buf, uint32 bufLength, const char* fmt, ...) {

	if (buf == NULL || bufLength == 0 || fmt == NULL) {
		return 0;
	}

#if defined(GS_AMIGA)
	uint32 length = 0;
	const char* args = (const char*)(&fmt + 1);
	RawDoFmt((CONST_STRPTR)fmt, (APTR)args, (PUTCHARPROC)&LenChar, &length);
	if (length >= bufLength) {
		return 0;
	}

	RawDoFmt((CONST_STRPTR)fmt, (APTR)args, (PUTCHARPROC)&PutChar, buf);

	return length;
#endif

}

uint32 gs_format_vargs(char* buf, uint32 bufLength, const char* fmt, void* args) {

	if (buf == NULL || bufLength == 0 || fmt == NULL || args == NULL) {
		return 0;
	}

#if defined(GS_AMIGA)
	uint32 length = 0;
	RawDoFmt((CONST_STRPTR)fmt, (APTR)args, (PUTCHARPROC)&LenChar, &length);
	if (length >= bufLength) {
		return 0;
	}

	RawDoFmt((CONST_STRPTR)fmt, (APTR)args, (PUTCHARPROC)&PutChar, buf);

	return length;
#endif

}

uint32 gs_format_length(const char* fmt, ...) {

	if (fmt == NULL) {
		return 0;
	}

#if defined(GS_AMIGA)
	uint32 length = 0;
	const char* args = (const char*)(&fmt + 1);
	RawDoFmt((CONST_STRPTR)fmt, (APTR)args, (PUTCHARPROC)&LenChar, &length);
	return length;
#endif

}

uint32 gs_format_length_vargs(const char* fmt, void* args) {

	if (fmt == NULL) {
		return 0;
	}

#if defined(GS_AMIGA)
	uint32 length = 0;
	RawDoFmt((CONST_STRPTR)fmt, (APTR)args, (PUTCHARPROC)&LenChar, &length);
	return length;
#endif

}
