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

#define GS_FILE_NAME "screen"

#include "types_sdl.h"
#include "../debug.h"
#include "../profile.h"
#include "../screen.h"
#include "../globals.h"
#include "../functions.h"

#include <SDL2/SDL.h>

namespace gs
{
	SDL_Window* sWindow = NULL;
	SDL_Surface* sWindowSurface = NULL;
	SDL_Surface* sSurface = NULL;
	bool sSurfaceDirty = false;
	bool sPaletteDirty = false;
	SDL_Color sPalette[256];

	bool closeScreen();

	bool openScreen() {

		if (sWindow) {
			closeScreen();
		}


		for (uint16 i = 0; i < 256; i++) {
			SDL_Color& colour = sPalette[i];
			colour.r = 0;
			colour.g = 255;
			colour.b = 0;
			colour.a = 255;
		}

		sPalette[0].g = 0;
		sPaletteDirty = true;

		sWindow = SDL_CreateWindow(GS_GAME_NAME, 
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			GS_SCREEN_WIDTH,
			GS_SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
		);

		if (sWindow == NULL) {
			error(GS_THIS, "Could not open SDL Window");
			return false;
		}


		sWindowSurface = SDL_GetWindowSurface(sWindow);


		sSurface = SDL_CreateRGBSurface(0, GS_SCREEN_WIDTH, GS_SCREEN_HEIGHT, 8, 0,0,0,0);

		if (sSurface == NULL) {
			error(GS_THIS, "Could not open SDL Surface");
			return false;
		}

		return true;
	}

	bool closeScreen() {

		if (sSurface) {
			SDL_FreeSurface(sSurface);
			sSurface = NULL;
		}

		if (sWindow != NULL) {
			SDL_DestroyWindow(sWindow);
			sWindow = NULL;
		}

		return true;
	}
	
	void screenLoop() {
		SDL_Event event;

		while (QUIT_NOW == false) {
			
			bool step = false;

			while (SDL_PollEvent(&event)) {
				switch(event.type) {
					case SDL_QUIT: {
						QUIT_NOW = true;
					}
					break;
					case SDL_KEYUP: {
						if (event.key.keysym.sym == SDLK_SPACE) {
							togglePause();
						}
						else if (PAUSED && event.key.keysym.sym == SDLK_s) {
							step = true;
						}
					}
					break;
				}
			}

			if (PAUSED == false) {
				runFrame();
			}
			else {
				if (step) {
					debug(GS_THIS, "Step");
					runFrame();
					step = false;
				}
			}
			
			if (sPaletteDirty) {
				sPaletteDirty  = false;
				SDL_LockSurface(sSurface);
				SDL_SetPaletteColors(sSurface->format->palette, sPalette, 0, 255);
				SDL_UnlockSurface(sSurface);
			}

			if (sSurfaceDirty) {
				sSurfaceDirty = false;
				SDL_BlitSurface(sSurface, NULL, sWindowSurface, NULL);
			}

			SDL_UpdateWindowSurface(sWindow);
		}
	}
	
	void setScreenPalette(uint8* palette, uint8 from, uint8 to) {
		for (uint8 i = from; i <= to; i++) {
			SDL_Color& colour = sPalette[i];
			colour.r = *palette;
			colour.g = *palette;
			colour.a = *palette;
		}
		sPaletteDirty = true;
	}

	void clearScreen(uint8 colour) {
		SDL_FillRect(sSurface, NULL, colour);
	}

	void drawBox(uint8 colour, uint16 x, uint16 y, uint16 w, uint16 h) {
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;

		SDL_FillRect(sSurface, &rect, colour);
		sSurfaceDirty = true;
	}
	
	void drawSystemText(uint8 colour, uint16 x, uint16 y, const char* text) {
		printf("SYSTEX: %s\n", text);
	}

	void drawSystemTextF(uint8 colour, uint16 x, uint16 y, const char* fmt, ...) {

		static char sTemp[256] = { 0 };

		va_list arg;
		va_start(arg, fmt);

		SDL_vsnprintf(sTemp, 256, fmt, arg);
		printf("SYSTEX: %s\n", &sTemp[0]);
	}

	void togglePause() {

		if (PAUSED == true) {
			SDL_SetWindowTitle(sWindow, GS_GAME_NAME);
		}
		else {
			SDL_SetWindowTitle(sWindow, "Paused");
		}

		PAUSED = !PAUSED;
	}

}