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
#include "../room.h"
#include "../input.h"

#include <SDL2/SDL.h>

namespace gs
{
	SDL_Window* sWindow = NULL;
	SDL_Surface* sWindowSurface = NULL;
	SDL_Surface* sSurface = NULL;
	bool sSurfaceDirty = false;
	bool sPaletteDirty = false;
	SDL_Color sPalette[256];
	SDL_Color sOriginalPalette[256];
    bool quitNextFrame;

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
        quitNextFrame = false;

		while (QUIT_NOW == false) {
			
			bool step = false;

			while (SDL_PollEvent(&event)) {
				switch(event.type) {
					case SDL_QUIT: {
                        if (!PAUSED) {
                            quitNextFrame = true;
                        }
                        else {
                            QUIT_NOW = true;
                        }
					}
					break;
					case SDL_KEYUP: {
						if (event.key.keysym.sym == SDLK_SPACE) {
							togglePause();
						}
						else if (PAUSED && event.key.keysym.sym == SDLK_s) {
							step = true;
						}

						if (event.key.keysym.sym == SDLK_m) {
							MOUSE_LMB_STATE = 1;
						}

						if (event.key.keysym.sym == SDLK_p) {
							KEY_EVENT = KE_DebugDumpStack;
						}

						if (event.key.keysym.sym == SDLK_o) {
							KEY_EVENT = KE_DebugDumpVerbs;
						}
					}
					break;
					case SDL_MOUSEMOTION: {
						MOUSE_X = event.motion.x;
						MOUSE_Y = event.motion.y;
					}
					break;
					case SDL_MOUSEBUTTONUP: {
						MOUSE_X = event.button.x;
						MOUSE_Y = event.button.y;

						if (event.button.button == SDL_BUTTON_LEFT ) {
							MOUSE_LMB_EVENT = -1;
						}
						else if (event.button.button == SDL_BUTTON_RIGHT) {
							MOUSE_RMB_EVENT = -1;
						}
					}
					break;
					case SDL_MOUSEBUTTONDOWN: {
						MOUSE_X = event.button.x;
						MOUSE_Y = event.button.y;

						if (event.button.button == SDL_BUTTON_LEFT ) {
							MOUSE_LMB_EVENT = 1;
						}
						else if (event.button.button == SDL_BUTTON_RIGHT) {
							MOUSE_RMB_EVENT = -1;
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

            if (quitNextFrame) {
                QUIT_NOW = true;
            }
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
		//printf("SYSTEX: %s\n", text);
	}

	void drawSystemTextF(uint8 colour, uint16 x, uint16 y, const char* fmt, ...) {

		static char sTemp[256] = { 0 };

		va_list arg;
		va_start(arg, fmt);

		SDL_vsnprintf(sTemp, 256, fmt, arg);
		//printf("SYSTEX: %s\n", &sTemp[0]);
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
	
	void setRoomPalette(RoomPaletteData* palette) {
		uint8* rgb = &palette->palette[0];
		for (uint16 i = 0; i < 256; i++) {
			SDL_Color& dst = sOriginalPalette[i];
			dst.r = *rgb++;
			dst.g = *rgb++;
			dst.b = *rgb++;
			SDL_Color& copy = sPalette[i];
			copy.r = dst.r;
			copy.g = dst.g;
			copy.b = dst.b;
		}
		sPaletteDirty = true;
	}

	void resetScreenPalette() {
		for (uint16 i = 0; i < 256; i++) {
			SDL_Color& dst = sPalette[i];
			SDL_Color& src = sOriginalPalette[i];
			dst.r = src.r;
			dst.g = src.g;
			dst.b = src.b;
		}
		sPaletteDirty = true;
	}

	void scaleScreenPalette(uint8 from, uint8 to, uint8 redScale, uint8 greenScale, uint8 blueScale) {
		for (uint16 i = from; i < to; i++) {
			SDL_Color& original = sOriginalPalette[i];
			SDL_Color& dest = sPalette[i];

			dest.r = (original.r * redScale) / 255;
			dest.g = (original.g * greenScale) / 255;
			dest.b = (original.b * blueScale) / 255;
		}
		sPaletteDirty = true;
	}

	void blitBitmap(uint32 x, uint32 y, uint32 w, uint32 h, uint32 len, byte*) {

	}
	
	void blitLine(uint16 y, byte* lineData) {
		
		SDL_LockSurface(sSurface);
		uint8* dst = (uint8*) sSurface->pixels;
		dst += y * sSurface->pitch;

		SDL_memcpy(dst, lineData, GS_SCREEN_WIDTH);
	
		SDL_UnlockSurface(sSurface);

		sSurfaceDirty = true;
	}
	
	void blitCopyBitmap(byte* bitmap) {
		
		SDL_LockSurface(sSurface);
		uint8* dst = (uint8*) sSurface->pixels;
		
		SDL_memcpy(dst, bitmap, GS_SCREEN_WIDTH * GS_SCREEN_HEIGHT);
	
		SDL_UnlockSurface(sSurface);

		sSurfaceDirty = true;
	}
}