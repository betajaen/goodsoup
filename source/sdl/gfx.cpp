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

#include "../goodsoup.h"


extern const char GOODSOUP_VERSION_STR[];

namespace common
{
	SDL_Window* sWindow;

	bool openGraphics()
	{
		sWindow = SDL_CreateWindow(
			&GOODSOUP_VERSION_STR[6],
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
		);

		return true;
	}

	bool closeGraphics()
	{
		if (sWindow)
		{
			SDL_DestroyWindow(sWindow);
		}

		return false;
	}

}