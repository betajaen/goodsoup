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

#include "shared/string.h"
#if defined(GS_AMIGA)
#include <proto/dos.h>
#endif

// shared/error.h
void gs_message_str(const char* str);

// shared/error.c
extern int gs_StartedFromCli;

static const char kCategoryCodes[] = { 'E', 'W', 'I', 'D', 'V' };
static char tempFmtBuffer[1024];

void gs__error_fmt(const char* source, uint32 line, const char* function, uint16 category, const char* fmt, ...) {

	void* args = (void*) ((const char*) fmt + 1);

	if (category == 0 && gs_StartedFromCli == FALSE) {
		gs_format_vargs(tempFmtBuffer, sizeof(tempFmtBuffer), fmt, args);
		gs_message_str(&tempFmtBuffer[0]);
		return;
	}

	if (category > 4) {
		category == 4;
	}

	gs_format(tempFmtBuffer, sizeof(tempFmtBuffer), "%c\t%-10s\t%-10s\t%ld\t", kCategoryCodes[category], source, line, function);

#if defined(GS_AMIGA)
	PutStr((CONST_STRPTR) &tempFmtBuffer[0]);
#endif

	gs_format_vargs(tempFmtBuffer, sizeof(tempFmtBuffer), fmt, args);

#if defined(GS_AMIGA)
	PutStr((CONST_STRPTR) &tempFmtBuffer[0]);
	PutStr("\n");
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

	gs_format(tempFmtBuffer, sizeof(tempFmtBuffer), "%c\t%-10s\t%-10s\t%ld\t", kCategoryCodes[category], source, line, function);

#if defined(GS_AMIGA)
	PutStr((CONST_STRPTR) &tempFmtBuffer[0]);
#endif

#if defined(GS_AMIGA)
	PutStr((CONST_STRPTR) str);
	PutStr("\n");
#endif

}

void gs_print_fmt(const char* fmt, ...) {
	void* args = (void*) ((const char*) fmt + 1);
	gs_format_vargs(tempFmtBuffer, sizeof(tempFmtBuffer), fmt, args);
#if defined(GS_AMIGA)
	PutStr((CONST_STRPTR) &tempFmtBuffer[0]);
#endif
}

void gs_print_str(const char* str) {
#if defined(GS_AMIGA)
	PutStr(str);
#endif
}

void gs_message_fmt(const char* fmt, ...) {

}

void gs_message_str(const char* str) {

}
