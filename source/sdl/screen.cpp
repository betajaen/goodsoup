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
	SDL_Renderer* sRenderer = NULL;
	SDL_Surface* sSurface = NULL;
	SDL_Texture* sTexture = NULL;

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
		}

		sPalette[0].g = 0;

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

		sRenderer = SDL_CreateRenderer(sWindow, -1, SDL_RENDERER_SOFTWARE);

		if (sRenderer == NULL) {
			error(GS_THIS, "Could not open SDL Renderer");
			return false;
		}

		sSurface = SDL_CreateRGBSurface(0, GS_SCREEN_WIDTH, GS_SCREEN_HEIGHT, 8, 0,0,0,0);

		if (sSurface == NULL) {
			error(GS_THIS, "Could not open SDL Surface");
			return false;
		}

		SDL_SetPaletteColors(sSurface->format->palette, sPalette, 0, 255);

		sTexture = SDL_CreateTextureFromSurface(sRenderer, sSurface);

		return true;
	}

	bool closeScreen() {

		if (sSurface) {
			SDL_FreeSurface(sSurface);
			sSurface = NULL;
		}

		if (sTexture) {
			SDL_DestroyTexture(sTexture);
			sTexture = NULL;
		}

		if (sRenderer != NULL) {
			SDL_DestroyRenderer(sRenderer);
			sRenderer = NULL;
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
			
			while (SDL_PollEvent(&event)) {
				switch(event.type) {
					case SDL_QUIT: {
						QUIT_NOW = true;
					}
					break;
				}
			}

			runFrame();
			
			SDL_RenderClear(sRenderer);
			SDL_UpdateTexture(sTexture, NULL, sSurface->pixels, sSurface->pitch);
			SDL_RenderCopy(sRenderer, sTexture, NULL, NULL);
			SDL_RenderPresent(sRenderer);
		}
	}


}