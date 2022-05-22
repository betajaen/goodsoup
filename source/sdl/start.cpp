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
		case SDL_LOG_PRIORITY_ERROR: fputs("!! ERROR !!", stdout); break;
		case SDL_LOG_PRIORITY_CRITICAL: fputs("** CRITICAL **", stdout); break;
	}
	fputs(message, stdout);
	fputc('\n', stdout);
}

namespace platform
{
	bool openGraphics();
	bool closeGraphics();

	bool preinit()
	{
		SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
		SDL_LogSetOutputFunction(writeLog, NULL);
		return true;
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
	}
}