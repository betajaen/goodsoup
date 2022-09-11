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

#define GS_FILE "screenrtg"

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
#include <proto/cybergraphics.h>
#include <cybergraphx/cybergraphics.h>

// Required by cybergraphics.library
struct Library* CyberGfxBase = NULL;

// Required by graphics.library
struct GfxBase* GfxBase = NULL;

GS_IMPORT void gs_ClearPalette();
GS_IMPORT void gs_ApplyPalette();
GS_IMPORT void gs_SetPaletteColour(uint8 index, uint8 r, uint8 g, uint8 b);
GS_PRIVATE uint32 GetAmigaScreenModeId();

/// --- SCREENS  ---

GS_EXPORT struct Screen* gs_Screen = NULL;
GS_EXPORT struct ScreenBuffer* gs_ScreenBuffer = NULL;
GS_EXPORT struct Window* gs_Window = NULL;
GS_EXPORT struct RastPort gs_RastPort;
GS_PRIVATE struct TextAttr sDefaultFont = {
		(STRPTR) "topaz.font", 		/* Name */
		8, 				/* YSize */
		FS_NORMAL,			/* Style */
		FPF_ROMFONT | FPF_DESIGNED,	/* Flags */
};


GS_EXPORT gs_bool InitializeScreenAndWindow() {

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

GS_EXPORT void TeardownScreenAndWindow() {

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

GS_EXPORT gs_bool gs_OpenScreen() {

	gs_bool rc = TRUE;

	if ((GfxBase = (struct GfxBase*)OpenLibrary("graphics.library", 33)) == NULL) {
		rc = FALSE;
		goto exit_function;
	}

	gs_debug_str("Opened graphics.library");

	if ((CyberGfxBase  = (struct Library*)OpenLibrary("cybergraphics.library", 41)) == NULL) {
		rc = FALSE;
		goto exit_function;
	}

	gs_debug_str("Opened cybergraphics.library");


	if (InitializeScreenAndWindow() == FALSE) {
		rc = FALSE;
		goto exit_function;
	}

	gs_verbose_str("Opened Screen and Window");

	return rc;

	exit_function:

	if (CyberGfxBase != NULL) {
		CloseLibrary((struct Library *) CyberGfxBase);
	}


	if (GfxBase != NULL) {
		CloseLibrary((struct Library *) GfxBase);
	}

	return rc;
}

GS_EXPORT gs_bool gs_CloseScreen() {

	TeardownScreenAndWindow();

	if (CyberGfxBase != NULL) {
		CloseLibrary((struct Library *) CyberGfxBase);
	}

	if (GfxBase != NULL) {
		CloseLibrary((struct Library *) GfxBase);
	}


	return TRUE;
}

GS_PRIVATE uint32 GetAmigaScreenModeId() {
	return BestCModeIDTags(
			CYBRBIDTG_NominalWidth, GS_WIDTH,
			CYBRBIDTG_NominalHeight, GS_HEIGHT,
			CYBRBIDTG_Depth,  GS_DEPTH,
			TAG_DONE
	);
}

/// --- PALETTE ---

GS_PRIVATE uint32 sPaletteMem[2 + (256 * 3)] = { 0 };
GS_PRIVATE uint16 sPaletteSize = 256;
GS_PRIVATE uint16 sPaletteDepth = 8;

GS_EXPORT void gs_ClearPalette() {
	const uint16 limit = sPaletteSize * 3;

	ULONG* dst = &sPaletteMem[0];

	*dst++ = sPaletteSize << 16 | 0;

	for (uint16 i = 0; i < limit; i++) {
		*dst++ = 0 | 0xFFFFFF;
	}

	*dst = 0;
}

GS_EXPORT void gs_ApplyPalette() {
	LoadRGB32(&gs_Screen->ViewPort, &sPaletteMem[0]);
}

GS_EXPORT void gs_SetPaletteColour(uint8 index, uint8 r, uint8 g, uint8 b) {
	const uint16 offset = (((uint16)index) * 3) + 1;
	sPaletteMem[offset] = r << 24 | 0xFFFFFF;
	sPaletteMem[offset+1] = g << 24 | 0xFFFFFF;
	sPaletteMem[offset+2] = b << 24 | 0xFFFFFF;
}
