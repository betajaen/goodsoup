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

#define GS_FILE "string"

#include "shared/forward.h"
#include "shared/error.h"


#if defined(GS_OS3_ARCH)

#include <proto/exec.h>
#include "shared/sdi/SDI_stdarg.h"

typedef VOID(*PUTCHARPROC)();

GS_PRIVATE const uint32 PutChar = 0x16c04e75;
GS_PRIVATE const uint32 LenChar = 0x52934e75;

#endif


#if defined(GS_CSTD_ARCH)
#include <stdio.h>
#endif

// shared/error.c
GS_IMPORT int gs_StartedFromCli;


GS_EXPORT uint32 gs_format(char* buf, uint32 bufLength, const char* fmt, ...) {

	if (buf == NULL || bufLength == 0 || fmt == NULL) {
		return 0;
	}

#if defined(GS_OS3_ARCH)
	uint32 length = 0;
	GS_VARARG_LIST(args);
	GS_VARARG_BEGIN(args, fmt);
	RawDoFmt((CONST_STRPTR)fmt, GS_VARARG_ARG(args, void*), (PUTCHARPROC)&LenChar, &length);
	if (length >= bufLength) {
		return 0;
	}

	RawDoFmt((CONST_STRPTR)fmt, GS_VARARG_ARG(args, void*), (PUTCHARPROC)&PutChar, buf);
	buf[length] = 0;

	GS_VARARG_END(args);

	return length;
#endif

#if defined(GS_CSTD_ARCH)
	uint32 length;
	GS_VARARG_LIST(args);
	GS_VARARG_BEGIN(args, fmt);
	length  = vsnprintf(buf,bufLength, fmt, GS_VARARG_ARG(args, va_list));
	GS_VARARG_END(args);
	return length;
#endif

}

GS_EXPORT uint32 gs_format_vargs(char* buf, uint32 bufLength, const char* fmt, void* args) {

	if (buf == NULL || bufLength == 0 || fmt == NULL || args == NULL) {
		return 0;
	}

#if defined(GS_OS3_ARCH)
	uint32 length = 0;
	RawDoFmt((CONST_STRPTR)fmt, (APTR)args, (PUTCHARPROC)&LenChar, &length);

	if (length >= bufLength) {
		return 0;
	}

	RawDoFmt((CONST_STRPTR)fmt, (APTR)args, (PUTCHARPROC)&PutChar, buf);
	buf[length] = 0;

	return length;
#endif
	
#if defined(GS_CSTD_ARCH)
	return vsnprintf(buf,bufLength, fmt, GS_VARARG_ARG(args, va_list));
#endif

}

GS_EXPORT uint32 gs_format_length(const char* fmt, ...) {

	if (fmt == NULL) {
		return 0;
	}

#if defined(GS_OS3_ARCH)
	uint32 length = 0;
	VA_LIST args;
	VA_START(args, fmt);
	RawDoFmt((CONST_STRPTR)fmt, VA_ARG(args, void*), (PUTCHARPROC)&LenChar, &length);
	VA_END(args);
	return length;
#endif
	
#if defined(GS_CSTD_ARCH)
	uint32 length;
	GS_VARARG_LIST(args);
	GS_VARARG_BEGIN(args, fmt);
	length  = vsnprintf(NULL, 0, fmt, GS_VARARG_ARG(args, va_list));
	GS_VARARG_END(args);
	return length;
#endif
}

GS_EXPORT uint32 gs_format_length_vargs(const char* fmt, void* args) {

	if (fmt == NULL) {
		return 0;
	}

#if defined(GS_OS3_ARCH)
	uint32 length = 0;
	RawDoFmt((CONST_STRPTR)fmt, (APTR)args, (PUTCHARPROC)&LenChar, &length);
	return length;
#endif
	
#if defined(GS_CSTD_ARCH)
	uint32 length;
	length  = vsnprintf(NULL, 0, fmt, GS_VARARG_ARG(args, va_list));
	return length;
#endif
}

GS_EXPORT uint32 gs_hash_str(const char* str) {

	// DJB2 hash
	// Quick and good enough for names
	
	if (str == NULL)
		return 0;

	uint32 h = 5381;

	while (*str) {
		h = ((h << 5) + h) + *str++;
	}

	return h;
}

GS_EXPORT uint32 gs_str_length(const char* str) {

	if (str == NULL)
		return 0;

	const char* s = str;
	while (*s) {
		s++;
	}

	return s - str;
}