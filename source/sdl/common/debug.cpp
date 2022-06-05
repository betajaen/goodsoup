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

#define GS_FILE_NAME "debug"

#include "common/debug.h"
#include <stdio.h>

void SDLCALL writeLog(void* userdata, int category, SDL_LogPriority priority, const char* message)
{
	switch (priority)
	{
	default:
	case SDL_LOG_PRIORITY_VERBOSE: fputs("V ", stdout); break;
	case SDL_LOG_PRIORITY_DEBUG: fputs("D ", stdout); break;
	case SDL_LOG_PRIORITY_INFO: fputs("I ", stdout); break;
	case SDL_LOG_PRIORITY_WARN: fputs("W ", stdout); break;
	case SDL_LOG_PRIORITY_ERROR: fputs("\n!! ERROR !!\n\nE ", stdout); break;
	case SDL_LOG_PRIORITY_CRITICAL: fputs("\n** CRITICAL **\n\nC ", stdout); break;
	}
	fputs(message, stdout);
	fputc('\n', stdout);

	if (priority > SDL_LOG_PRIORITY_WARN)
	{
		fputc('\n', stdout);
		exit(0);
	}

}


namespace common
{

	void debug_write(DebugCategory category, const char* module, const char* file, const char* function, uint32 line, const char* message) {	
		switch (category) {
			default:
			case DC_Test: fputs("T ", stdout); break;
			case DC_Verbose: fputs("V ", stdout); break;
			case DC_Debug: fputs("D ", stdout); break;
			case DC_Informational: fputs("I ", stdout); break;
			case DC_Warning: fputs("W ", stdout); break;
			case DC_Error: fputs("\n!! ERROR !!\n\nE ", stdout); break;
		}

		fputs(module, stdout);
		fprintf(stdout, "\t%-10s\t%-10s\t%d\t", file, function, line);

		fputs(message, stdout);

		fputc('\n', stdout);

		if (category == DC_Error) {
			fputc('\n', stdout);
			exit(0);
		}
	}

	void debug_writef(DebugCategory category, const char* module, const char* file, const char* function, uint32 line, const char* format, ...) {

		va_list ap;
		switch (category) {
			default:
			case DC_Test: fputs("T ", stdout); break;
			case DC_Verbose: fputs("V ", stdout); break;
			case DC_Debug: fputs("D ", stdout); break;
			case DC_Informational: fputs("I ", stdout); break;
			case DC_Warning: fputs("W ", stdout); break;
			case DC_Error: fputs("\n!! ERROR !!\n\nE ", stdout); break;
		}

		fputs(module, stdout);
		fprintf(stdout, "\t%-10s\t%s\t%d\t", file, function, line);

		va_start(ap, format);
		vfprintf(stdout, format, ap);
		va_end(ap);

		fputc('\n', stdout);

		if (category == DC_Error) {
			fputc('\n', stdout);
			exit(0);
		}

	}

	void debug_stop(const char* file, uint32 line, const char* message) {
		fprintf(stdout, "%s:%u\n", file, line);
		if (message) {
			fputs(message, stdout);
		}
		exit(0);
	}

	void debug_write_test_fail_location(const char* file, uint32 line, const char* test_name) {    
		fprintf(stdout, "%s failed\n:\n\t%s:%u\n", test_name, file, line);
	}

    void debug_write_str(const char* str_value) {
		fputs(str_value, stdout);
	}

    void debug_write_char(byte byte_value) {
		fprintf(stdout, "%2x", (uint32) byte_value);
	}

    void debug_write_char(char char_value) {
		fputc(char_value, stdout);
	}

    void debug_write_unsigned_int(uint32 uint32_value) {
		fprintf(stdout, "%u", uint32_value);
	}

    void debug_write_int(int32 int32_value) {
		fprintf(stdout, "%d", int32_value);
	}

    void debug_write_bool(bool bool_value) {
		if (bool_value)
			fprintf(stdout, "true");
		else
			fprintf(stdout, "false");
	}

	void debug_write_pointer(const void* ptr) {
		fprintf(stdout, "%p", ptr);
	}

}
