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
#if defined(GS_AMIGA)
#include <proto/dos.h>
#include "shared/sdi/SDI_stdarg.h"
#endif

// shared/error.h
void gs_message_str(const char* str);

// shared/error.c
extern int gs_StartedFromCli;

static const char* kCategoryCodes[] = { "E", "W", "I", "D", "V" };
static char tempFmtBuffer[1024];
static const char* kPadding = "\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\40\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";

static void WriteHeader(const char* source, uint32 line, const char* function, uint16 category) {
	uint32 l = gs_format(tempFmtBuffer, sizeof(tempFmtBuffer), "%s %.8s/%-.18s:%ld", kCategoryCodes[category], source, function, line);
	PutStr((CONST_STRPTR) tempFmtBuffer);
	int32 padding = 32 - l;
	if (padding > 0) {
		PutStr(&kPadding[l]);
	}
}

void gs__error_fmt(const char* source, uint32 line, const char* function, uint16 category, const char* fmt, ...) {


	if (category == 0 && gs_StartedFromCli == FALSE) {
#if defined(GS_AMIGA)
		VA_LIST args;
		VA_START(args, fmt);
		gs_format_vargs(tempFmtBuffer, sizeof(tempFmtBuffer), fmt, VA_ARG(args, void *));
		gs_message_str(&tempFmtBuffer[0]);
		VA_END(args);
#endif
		return;
	}

	if (category > 4) {
		category == 4;
	}

#if defined(GS_AMIGA)
	VA_LIST args;
	VA_START(args, fmt);
	WriteHeader(source, line, function, category);
	gs_format_vargs(tempFmtBuffer, sizeof(tempFmtBuffer), fmt, VA_ARG(args, void *));
	PutStr((CONST_STRPTR) &tempFmtBuffer[0]);
	PutStr("\n");


	VA_END(args);
#endif

}

void gs__error_str(const char* source, uint32 line, const char* function, uint16 category, const char* str) {

	if (category == 0 && gs_StartedFromCli == FALSE) {
		gs_message_str(str);
		return;
	}

	if (category > 4) {
		category == 4;
	}

#if defined(GS_AMIGA)
	WriteHeader(source, line, function, category);
	PutStr((CONST_STRPTR) str);
	PutStr("\n");
#endif

}

void gs_print_fmt(const char* fmt, ...) {
#if defined(GS_AMIGA)
	VA_LIST args;
	VA_START(args, fmt);
	gs_format_vargs(&tempFmtBuffer[0], sizeof(tempFmtBuffer), fmt, VA_ARG(args, void *));
	VA_END(args);

	PutStr((CONST_STRPTR) &tempFmtBuffer[0]);
#endif
}

void gs_print_str(const char* str) {
#if defined(GS_AMIGA)
	PutStr(str);
#endif
}

void gs_message_fmt(const char* fmt, ...) {
	VA_LIST args;
	VA_START(args, fmt);
	// @TODO
	VA_END(args);
}

void gs_message_str(const char* str) {

}
