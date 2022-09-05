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

static struct Screen* sScreen = NULL;
static struct ScreenBuffer* sScreenBuffer = NULL;
static struct Window* sWindow = NULL;
static struct RastPort sRastPort;
static struct TextAttr sDefaultFont =
{
		(STRPTR) "topaz.font", 		/* Name */
		8, 				/* YSize */
		FS_NORMAL,			/* Style */
		FPF_ROMFONT | FPF_DESIGNED,	/* Flags */
};
static ULONG sPalette[2 + (256 * 3)] = { 0 };

static gs_bool InitializeScreenAndWindow() {

	gs_bool rc = TRUE;

	uint32 modeId = BestCModeIDTags(
			CYBRBIDTG_NominalWidth, GS_WIDTH,
			CYBRBIDTG_NominalHeight, GS_HEIGHT,
			CYBRBIDTG_Depth, GS_DEPTH,
			TAG_DONE
	);

	if (modeId == INVALID_ID) {
		gs_error_fmt("Could not find CyberGfx mode for a %ldx%ldx%ld resolution.", GS_WIDTH, GS_HEIGHT, GS_DEPTH);
		rc = FALSE;
		goto exit_function;
	}

	sScreen = OpenScreenTags(NULL,
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

	if (sScreen == NULL) {
		gs_error_str("Could not open the screen.");
		rc = FALSE;
		goto exit_function;
	}

	sScreenBuffer = AllocScreenBuffer(
			sScreen,
			NULL,
			SB_SCREEN_BITMAP
	);

	if (sScreenBuffer == NULL) {
		gs_error_str("Could not allocate a screen buffer.");
		// TODO: Log Error Message
		rc = FALSE;
		goto exit_function;
	}

	LoadRGB32(&sScreen->ViewPort, &sPalette[0]);

	InitRastPort(&sRastPort);
	sRastPort.BitMap = sScreenBuffer->sb_BitMap;

	sWindow = OpenWindowTags(NULL,
							 WA_Left, 0,
							 WA_Top, 0,
							 WA_Width, GS_WIDTH,
							 WA_Height, GS_HEIGHT,
							 WA_CustomScreen, (ULONG)sScreen,
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

	if (sWindow == NULL) {
		gs_error_str("Could not open a window.");
		rc = FALSE;
		goto exit_function;
	}

	gs_verbose_str("Screen opened.");

	exit_function:

	if (sWindow)
	{
		CloseWindow(sWindow);
		sWindow = NULL;
	}

	if (sScreenBuffer && sScreen)
	{
		FreeScreenBuffer(sScreen, sScreenBuffer);
		sScreenBuffer = NULL;
	}

	if (sScreen)
	{
		CloseScreen(sScreen);
		sScreen = NULL;
	}

	return rc;
}

static void TeardownScreenAndWindow() {

	if (sScreen)
	{
		CloseScreen(sScreen);
		sScreen = NULL;
	}
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

