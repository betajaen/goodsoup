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

#define GS_FILE "rtg"

#ifndef GS_AMIGA
#error "GS_AMIGA must be defined to compile this file."
#endif

#include "shared/forward.h"
#include "shared/game.h"
#include "shared/error.h"

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/intuition.h>
#include <proto/graphics.h>


extern void gs_ClearPalette();
extern void gs_ApplyPalette();
extern void gs_SetPaletteColour(uint8 index, uint8 r, uint8 g, uint8 b);
static void InitializeMenu();
static void TeardownMenu();
static void HandleMenuEvent(uint32 menuCode);

#if defined(GS_RTG)

#include <proto/cybergraphics.h>
#include <cybergraphx/cybergraphics.h>

struct Library* CyberGfxBase = NULL;

static uint32 GetAmigaScreenModeId() {
	return BestCModeIDTags(
			CYBRBIDTG_NominalWidth, GS_WIDTH,
			CYBRBIDTG_NominalHeight, GS_HEIGHT,
			CYBRBIDTG_Depth,  GS_DEPTH,
			TAG_DONE
	);
}

#endif


#if defined(GS_AGA)

static uint32 GetAmigaScreenModeId() {
	return BestModeID(BIDTAG_NominalWidth, GS_WIDTH,
				BIDTAG_NominalHeight, GS_HEIGHT,
				BIDTAG_DesiredWidth, GS_WIDTH,
				BIDTAG_DesiredHeight, GS_HEIGHT,
				BIDTAG_Depth, GS_DEPTH,
				BIDTAG_MonitorID, PAL_MONITOR_ID,
				TAG_END);
}

#endif



/// --- SCREENS  ---

struct Screen* gs_Screen = NULL;
struct ScreenBuffer* gs_ScreenBuffer = NULL;
struct Window* gs_Window = NULL;
struct RastPort gs_RastPort;
static struct TextAttr sDefaultFont =
{
		(STRPTR) "topaz.font", 		/* Name */
		8, 				/* YSize */
		FS_NORMAL,			/* Style */
		FPF_ROMFONT | FPF_DESIGNED,	/* Flags */
};

struct GfxBase* GfxBase = NULL;
static gs_bool sQuitLoopAlive = FALSE;


static gs_bool InitializeScreenAndWindow() {

	gs_verbose_str("Opening Window");

	gs_bool rc = TRUE;

	uint32 modeId = GetAmigaScreenModeId();

	gs_verbose_fmt("Mode ID is %lx", modeId);

	if (modeId == INVALID_ID) {
		gs_error_fmt("Could not find graphics mode for a %ldx%ldx%ld resolution.", GS_WIDTH, GS_HEIGHT, GS_DEPTH);
		return FALSE;
	}

	gs_Screen = OpenScreenTags(NULL,
							 SA_DisplayID, modeId,
							 SA_Left, 0,
							 SA_Top, 0,
							 SA_Width, GS_WIDTH,
							 SA_Height, GS_HEIGHT,
							 SA_Depth, GS_DEPTH,
							 SA_Title, (ULONG) GS_GAME_TITLE,
							 SA_ShowTitle, FALSE,
							 SA_Type, CUSTOMSCREEN,
							 SA_FullPalette, TRUE,
							 SA_Colors32, TRUE,
							 SA_Exclusive, TRUE,
							 SA_AutoScroll, FALSE,
							 SA_Font, (ULONG) &sDefaultFont,
							 TAG_DONE
	);

	if (gs_Screen == NULL) {
		gs_error_str("Could not open the screen.");
		return FALSE;
	}

	gs_ScreenBuffer = AllocScreenBuffer(
			gs_Screen,
			NULL,
			SB_SCREEN_BITMAP
	);

	if (gs_ScreenBuffer == NULL) {
		gs_error_str("Could not allocate a screen buffer.");
		return FALSE;
	}

	gs_verbose_str("Clearing Palette");
	gs_ClearPalette();
	gs_SetPaletteColour(1, 0xFF, 0xFF, 0xFF);
	gs_SetPaletteColour(2, 0xFF, 0, 0);
	gs_SetPaletteColour(3, 0, 0xFF, 0);
	gs_SetPaletteColour(17, 0xFF, 0xFF, 0xFF);
	gs_verbose_str("Applying Palette");
	gs_ApplyPalette();

	InitRastPort(&gs_RastPort);
	gs_RastPort.BitMap = gs_ScreenBuffer->sb_BitMap;

	gs_debug_str("Opening Window");
	gs_Window = OpenWindowTags(NULL,
							 WA_Left, 0,
							 WA_Top, 0,
							 WA_Width, GS_WIDTH,
							 WA_Height, GS_HEIGHT,
							 WA_CustomScreen, (ULONG)gs_Screen,
							 WA_Backdrop, TRUE,
							 WA_Borderless, TRUE,
							 WA_DragBar, FALSE,
							 WA_Activate, TRUE,
							 WA_SimpleRefresh, TRUE,
							 WA_CloseGadget, FALSE,
							 WA_DepthGadget, FALSE,
							 WA_IDCMP, IDCMP_CLOSEWINDOW | IDCMP_VANILLAKEY | IDCMP_IDCMPUPDATE | IDCMP_MOUSEBUTTONS,
							 TAG_END
	);

	if (gs_Window == NULL) {
		gs_error_str("Could not open a window.");
		return FALSE;
	}

	gs_verbose_str("Screen opened.");

	return TRUE;

}

static void TeardownScreenAndWindow() {

	if (gs_Window)
	{
		CloseWindow(gs_Window);
		gs_Window = NULL;
	}

	if (gs_ScreenBuffer && gs_Screen)
	{
		FreeScreenBuffer(gs_Screen, gs_ScreenBuffer);
		gs_ScreenBuffer = NULL;
	}

	if (gs_Screen)
	{
		CloseScreen(gs_Screen);
		gs_Screen = NULL;
	}

	gs_verbose_str("Screen closed.");
}

extern gs_bool gs_OpenScreen() {

	gs_bool rc = TRUE;

	if ((GfxBase = (struct GfxBase*)OpenLibrary("graphics.library", 33)) == NULL) {
		rc = FALSE;
		goto exit_function;
	}

	gs_debug_str("Opened graphics.library");

#if defined(GS_RTG)
	if ((CyberGfxBase  = (struct Library*)OpenLibrary("cybergraphics.library", 41)) == NULL) {
		rc = FALSE;
		goto exit_function;
	}

	gs_debug_str("Opened cybergraphics.library");

#endif

	if (InitializeScreenAndWindow() == FALSE) {
		rc = FALSE;
		goto exit_function;
	}

	gs_verbose_str("Opened Screen and Window");

	return rc;

	exit_function:

#if defined(GS_RTG)
	if (CyberGfxBase != NULL) {
		CloseLibrary((struct Library *) CyberGfxBase);
	}
#endif

	if (GfxBase != NULL) {
		CloseLibrary((struct Library *) GfxBase);
	}

	return rc;
}

extern gs_bool gs_CloseScreen() {

	TeardownScreenAndWindow();

#if defined(GS_RTG)
	if (CyberGfxBase != NULL) {
		CloseLibrary((struct Library *) CyberGfxBase);
	}
#endif

	if (GfxBase != NULL) {
		CloseLibrary((struct Library *) GfxBase);
	}


	return TRUE;
}

extern void gs_EnterScreenLoop() {

	uint32 timerBit = 0; /* TODO: Get from Timer, via a private extern function */
	uint32 windowBit = (1 << gs_Window->UserPort->mp_SigBit);
	uint32 signalBits = windowBit | timerBit | SIGBREAKF_CTRL_C;
	struct IntuiMessage* intMsg;

	sQuitLoopAlive = TRUE;

	InitializeMenu();

	while(sQuitLoopAlive) {
		ULONG signal = Wait(signalBits);

		if (signal & SIGBREAKF_CTRL_C) {
			break;
		}

		if (signal & windowBit) {

			while ((intMsg = (struct IntuiMessage *) GetMsg(gs_Window->UserPort))) {

				if (intMsg == NULL)
					break;

				if (intMsg->Class == IDCMP_CLOSEWINDOW) {
					sQuitLoopAlive = FALSE;
				}
				else if (intMsg->Class == IDCMP_MENUPICK) {
					HandleMenuEvent(intMsg->Code);
				}


				ReplyMsg((struct Message*) intMsg);
			}

		}

		if (signal & timerBit) {
			/* TODO: Timer */
		}

	}

	TeardownMenu();

	sQuitLoopAlive = FALSE;
}

extern void gs_LeaveScreenLoop() {
	sQuitLoopAlive = FALSE;
}

/// --- PALETTE ---

uint32 gs_PaletteMem[2 + (256 * 3)] = { 0 };
uint16 gs_PaletteSize = 256;
uint16 gs_PaletteDepth = 8;

extern void gs_ClearPalette() {
	const uint16 limit = gs_PaletteSize * 3;

	ULONG* dst = &gs_PaletteMem[0];

	*dst++ = gs_PaletteSize << 16 | 0;

	for (uint16 i = 0; i < limit; i++) {
		*dst++ = 0 | 0xFFFFFF;
	}

	*dst = 0;
}

extern void gs_ApplyPalette() {
	LoadRGB32(&gs_Screen->ViewPort, &gs_PaletteMem[0]);
}

extern void gs_SetPaletteColour(uint8 index, uint8 r, uint8 g, uint8 b) {
	const uint16 offset = (((uint16)index) * 3) + 1;
	gs_PaletteMem[offset] = r << 24 | 0xFFFFFF;
	gs_PaletteMem[offset+1] = r << 24 | 0xFFFFFF;
	gs_PaletteMem[offset+2] = r << 24 | 0xFFFFFF;
}

/// --- MENUS ---

#define GS_AMIGA_TEXT(NAME, STR)\
	static struct IntuiText NAME = { 0, 1, JAM2, 4, 2, NULL, (UBYTE*) STR, NULL }
#define GS_AMIGA_MENU_ITEM(NAME, TEXT, PREV, Y)\
	static struct MenuItem NAME = { PREV, 0, Y, 48, 12, ITEMTEXT|ITEMENABLED|HIGHCOMP, 0, (APTR) TEXT, (APTR) TEXT, NULL, NULL, 0 }
#define GS_AMIGA_MENU(NAME, TEXT, FIRST_CHILD)\
	static struct Menu NAME = { NULL, 0, 0, 48, 12, MENUENABLED, (BYTE*) TEXT, FIRST_CHILD, 0, 0, 0, 0 }

GS_AMIGA_TEXT(TEXT_Unpause, "Resume");
GS_AMIGA_TEXT(TEXT_Quit, "Quit");
GS_AMIGA_MENU_ITEM(MENUITEM_Unpause, &TEXT_Unpause, NULL, 0);
GS_AMIGA_MENU_ITEM(MENUITEM_Quit, &TEXT_Quit, &MENUITEM_Unpause, 12);
GS_AMIGA_MENU(MENU_Game, GS_GAME_NAME, &MENUITEM_Quit);

static gs_bool sMenuActive = FALSE;

static void InitializeMenu() {
	if (sMenuActive == TRUE) {
		return;
	}

	sMenuActive = TRUE;
	SetMenuStrip (gs_Window, &MENU_Game);
	ModifyIDCMP(gs_Window, IDCMP_IDCMPUPDATE | IDCMP_VANILLAKEY | IDCMP_MENUPICK);
}

static void TeardownMenu() {
	if (sMenuActive == TRUE) {
		return;
	}

	sMenuActive = FALSE;
	ClearMenuStrip(gs_Window);
	ModifyIDCMP(gs_Window, IDCMP_CLOSEWINDOW | IDCMP_VANILLAKEY | IDCMP_IDCMPUPDATE | IDCMP_MOUSEBUTTONS);
}

static void HandleMenuEvent(uint32 menuCode) {

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
					gs_LeaveScreenLoop();
				}
				break;
			}
		}
		break;

	}

}