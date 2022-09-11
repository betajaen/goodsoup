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

#define GS_FILE "menu"

#ifndef GS_AMIGA
#error "GS_AMIGA must be defined to compile this file."
#endif

#include "shared/forward.h"
#include "shared/game.h"
#include "shared/error.h"
#include "graphics/screen.h"

#include <proto/intuition.h>

#define GS_AMIGA_TEXT(NAME, STR)\
	struct IntuiText NAME = { 0, 1, JAM2, 4, 2, NULL, (UBYTE*) STR, NULL }
#define GS_AMIGA_MENU_ITEM(NAME, TEXT, PREV, Y)\
	struct MenuItem NAME = { PREV, 0, Y, 48, 12, ITEMTEXT|ITEMENABLED|HIGHCOMP, 0, (APTR) TEXT, (APTR) TEXT, NULL, NULL, 0 }
#define GS_AMIGA_MENU(NAME, TEXT, FIRST_CHILD)\
	struct Menu NAME = { NULL, 0, 0, 48, 12, MENUENABLED, (BYTE*) TEXT, FIRST_CHILD, 0, 0, 0, 0 }

GS_IMPORT struct Window* gs_Window;
GS_PRIVATE GS_AMIGA_TEXT(TEXT_Unpause, "Resume");
GS_PRIVATE GS_AMIGA_TEXT(TEXT_Quit, "Quit");
GS_PRIVATE GS_AMIGA_MENU_ITEM(MENUITEM_Unpause, &TEXT_Unpause, NULL, 0);
GS_PRIVATE GS_AMIGA_MENU_ITEM(MENUITEM_Quit, &TEXT_Quit, &MENUITEM_Unpause, 12);
GS_PRIVATE GS_AMIGA_MENU(MENU_Game, GS_GAME_NAME, &MENUITEM_Quit);
GS_PRIVATE gs_bool sMenuActive = FALSE;

GS_EXPORT void gs_InitializeMenu() {
	if (sMenuActive == TRUE) {
		return;
	}

	sMenuActive = TRUE;
	SetMenuStrip (gs_Window, &MENU_Game);
	ModifyIDCMP(gs_Window, IDCMP_IDCMPUPDATE | IDCMP_VANILLAKEY | IDCMP_MENUPICK);
}

GS_EXPORT void gs_TeardownMenu() {
	if (sMenuActive == TRUE) {
		return;
	}

	sMenuActive = FALSE;
	ClearMenuStrip(gs_Window);
	ModifyIDCMP(gs_Window, IDCMP_CLOSEWINDOW | IDCMP_VANILLAKEY | IDCMP_IDCMPUPDATE | IDCMP_MOUSEBUTTONS);
}

GS_EXPORT void gs_HandleMenuEvent(uint32 menuCode) {

	if (sMenuActive == FALSE) {
		return;
	}

	uint16 menuNum = MENUNUM(menuCode);
	uint16 itemNum = ITEMNUM(menuCode);

	switch(menuNum){

		case 0:
		{
			switch(itemNum) {
				// Pause
				case 1: {
					/* TODO */
				}
					break;
					// Quit
				case 0: {
					gs_verbose_str("Requesting Quit from Menu");
					gs_ExitScreenLoop();
				}
					break;
			}
		}
			break;

	}

}