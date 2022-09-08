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
#include <proto/cybergraphics.h>
#include <proto/graphics.h>
#include <cybergraphx/cybergraphics.h>

struct GfxBase* GfxBase = NULL;
struct Library* CyberGfxBase = NULL;

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
uint32 gs_PaletteMem[2 + (256 * 3)] = { 0 };

static gs_bool InitializeScreenAndWindow() {

	gs_bool rc = TRUE;

	uint32 modeId = BestCModeIDTags(
			CYBRBIDTG_NominalWidth, GS_WIDTH,
			CYBRBIDTG_NominalHeight, GS_HEIGHT,
			CYBRBIDTG_Depth,  GS_DEPTH,
			TAG_DONE
	);

	if (modeId == INVALID_ID) {
		gs_error_fmt("Could not find CyberGfx mode for a %ldx%ldx%ld resolution.", GS_WIDTH, GS_HEIGHT, GS_DEPTH);
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

	LoadRGB32(&gs_Screen->ViewPort, &gs_PaletteMem[0]);

	InitRastPort(&gs_RastPort);
	gs_RastPort.BitMap = gs_ScreenBuffer->sb_BitMap;

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
		rc = GS_FALSE;
		goto exit_function;
	}

	if ((CyberGfxBase  = (struct Library*)OpenLibrary("cybergraphics.library", 41)) == NULL) {
		rc = GS_FALSE;
		goto exit_function;
	}

	if (InitializeScreenAndWindow() == GS_FALSE) {
		rc = GS_FALSE;
		goto exit_function;
	}

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

extern gs_bool gs_CloseScreen() {

	TeardownScreenAndWindow();

	if (CyberGfxBase != NULL) {
		CloseLibrary((struct Library *) CyberGfxBase);
	}

	if (GfxBase != NULL) {
		CloseLibrary((struct Library *) GfxBase);
	}


	return GS_TRUE;
}

