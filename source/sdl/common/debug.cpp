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

#include "debug.h"
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

	void verbose(const char* fmt, ...)
	{
		va_list ap;
		va_start(ap, fmt);
		SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, fmt, ap);
		va_end(ap);
	}

	void debug(const char* fmt, ...)
	{
		va_list ap;
		va_start(ap, fmt);
		SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, fmt, ap);
		va_end(ap);
	}

	void info(const char* fmt, ...)
	{
		va_list ap;
		va_start(ap, fmt);
		SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, fmt, ap);
		va_end(ap);
	}

	void warn(const char* fmt, ...)
	{
		va_list ap;
		va_start(ap, fmt);
		SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, fmt, ap);
		va_end(ap);
	}

	void error(const char* fmt, ...)
	{
		va_list ap;
		va_start(ap, fmt);
		SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, fmt, ap);
		va_end(ap);
	}

	void beginDebug()
	{
		SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
		SDL_LogSetOutputFunction(writeLog, NULL);
	}

	void endDebug()
	{
		writeLog(NULL, SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Bye.");
	}
}
