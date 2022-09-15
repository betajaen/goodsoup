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

#define GS_FILE "error"

#include "shared/string.h"

#if defined(GS_OS3_ARCH)
#include <proto/dos.h>
#include "shared/sdi/SDI_stdarg.h"

#define GS_PUT_CSTRING PutStr
#define GS_VAR_ARG(X) VA_LIST X
#endif

#if defined(GS_CSTD_ARCH)
#include <stdio.h>

#define GS_PUT_CSTRING puts
#endif

// shared/error.h
GS_IMPORT void gs_message_str(const char* str);

// shared/error.c
GS_IMPORT int gs_StartedFromCli;

GS_PRIVATE const char* kCategoryCodes[] = { "E", "W", "I", "D", "V" };
GS_PRIVATE char tempFmtBuffer[1024];
GS_PRIVATE const char* kPadding = "\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";

GS_PRIVATE void WriteHeader(const char* source, uint32 line, const char* function, uint16 category) {
	uint32 l = gs_format(tempFmtBuffer, sizeof(tempFmtBuffer), "%s %.8s/%-.18s:%ld", kCategoryCodes[category], source, function, line);
	GS_PUT_CSTRING((const char*) tempFmtBuffer);
	int32 padding = 32 - l;
	if (padding > 0) {
		GS_PUT_CSTRING(&kPadding[l]);
	}
}

GS_EXPORT void gs__error_fmt(const char* source, uint32 line, const char* function, uint16 category, const char* fmt, ...) {


	if (category == 0 && gs_StartedFromCli == FALSE) {
		GS_VARARG_LIST(args);
		GS_VARARG_BEGIN(args, fmt);
		gs_format_vargs(tempFmtBuffer, sizeof(tempFmtBuffer), fmt, GS_VARARG_ARG(args, void*));
		gs_message_str(&tempFmtBuffer[0]);
		GS_VARARG_END(args);
		return;
	}

	if (category > 4) {
		category == 4;
	}
	
	GS_VARARG_LIST(args);
	GS_VARARG_BEGIN(args, fmt);
	WriteHeader(source, line, function, category);
	gs_format_vargs(tempFmtBuffer, sizeof(tempFmtBuffer), fmt, GS_VARARG_ARG(args, void *));
	GS_PUT_CSTRING(&tempFmtBuffer[0]);
	GS_PUT_CSTRING("\n");
	GS_VARARG_END(args);

}

GS_EXPORT void gs__error_str(const char* source, uint32 line, const char* function, uint16 category, const char* str) {

	if (category == 0 && gs_StartedFromCli == FALSE) {
		gs_message_str(str);
		return;
	}

	if (category > 4) {
		category == 4;
	}

	WriteHeader(source, line, function, category);
	GS_PUT_CSTRING(str);
	GS_PUT_CSTRING("\n");

}

GS_EXPORT void gs_print_fmt(const char* fmt, ...) {
	GS_VARARG_LIST(args);
	GS_VARARG_BEGIN(args, fmt);
	gs_format_vargs(&tempFmtBuffer[0], sizeof(tempFmtBuffer), fmt, GS_VARARG_ARG(args, void *));
	GS_VARARG_END(args);

	GS_PUT_CSTRING(&tempFmtBuffer[0]);
}

GS_EXPORT void gs_print_str(const char* str) {
	GS_PUT_CSTRING(str);
}

GS_EXPORT void gs_message_fmt(const char* fmt, ...) {
	GS_VARARG_LIST(args);
	GS_VARARG_BEGIN(args, fmt);
	// @TODO
	GS_VARARG_END(args);
}

GS_EXPORT void gs_message_str(const char* str) {
	// @TODO
}
