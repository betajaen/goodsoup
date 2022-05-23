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

#include "goodsoup.h"
#include <stdio.h>
#include <stdarg.h>

int main(int argc, char** argv)
{
	return common::start();
}

void SDLCALL writeLog(void* userdata, int category, SDL_LogPriority priority, const char* message)
{
	switch (priority)
	{
		default:
		case SDL_LOG_PRIORITY_VERBOSE: fputs("V ", stdout); break;
		case SDL_LOG_PRIORITY_DEBUG: fputs("D ", stdout); break;
		case SDL_LOG_PRIORITY_INFO: fputs("I ", stdout); break;
		case SDL_LOG_PRIORITY_WARN: fputs("W ", stdout); break;
		case SDL_LOG_PRIORITY_ERROR: fputs("!! ERROR !!\n\n", stdout); break;
		case SDL_LOG_PRIORITY_CRITICAL: fputs("** CRITICAL **\n\n", stdout); break;
	}
	fputs(message, stdout);
	fputc('\n', stdout);

	if (priority > SDL_LOG_PRIORITY_WARN)
	{
		fputc('\n', stdout);
	}

}

namespace common
{
	bool openGraphics();
	bool closeGraphics();

	bool preinit()
	{
		SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
		SDL_LogSetOutputFunction(writeLog, NULL);
		return true;
	}

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

	bool init()
	{
		if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0)
			return false;

		if (openGraphics() == false)
			return false;

		return true;
	}

	bool teardown()
	{
		closeGraphics();

		writeLog(NULL, SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Bye.");
		SDL_Quit();
		return true;
	}

	void wait(uint32 ms)
	{
		SDL_Delay(ms);
	}

	const char* tag2str(uint32 tag, char* str)
	{
		str[0] = (char)(tag >> 24);
		str[1] = (char)(tag >> 16);
		str[2] = (char)(tag >> 8);
		str[3] = (char)tag;
		str[4] = '\0';
		return str;
	}

}