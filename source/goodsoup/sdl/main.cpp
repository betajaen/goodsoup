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

#include "forward.h"
#include <SDL2/SDL.h>

namespace gs
{
	int main(int param);
	void checkMem();
	uint32 stringToUInt32(const char* str);

    int32 getMSec() {
        return SDL_GetTicks();
    }

}

int main(int argc, char** argv)
{
	gs::uint32 param = 0;

	if (argc > 1) {
		param = gs::stringToUInt32(argv[1]);
	}

	SDL_Init(SDL_INIT_EVERYTHING); //EVENTS | SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
	int rc = gs::main(param);
	gs::checkMem();
	SDL_Quit();
	return rc;
}

