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

#include "types_amiga.h"
#include "../debug.h"
#include "../profile.h"
#include "../globals.h"
#include "../functions.h"

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/intuition.h>
#include <proto/cybergraphics.h>
#include <proto/graphics.h>
#include <proto/datatypes.h>

#include <intuition/intuition.h>
#include <intuition/screens.h>
#include <cybergraphx/cybergraphics.h>

#include <datatypes/datatypes.h>
#include <datatypes/datatypesclass.h>
#include <datatypes/pictureclass.h>
#include <graphics/gfx.h>
#include <graphics/scale.h>
#include <graphics/displayinfo.h>
#include <intuition/intuition.h>
#include <intuition/intuitionbase.h>


namespace gs
{
	struct Screen* sScreen;
	struct Window* sWindow;
	struct ScreenBuffer* sScreenBuffer;
	struct RastPort sRastPort;

	bool openScreen() {

		uint32 modeId = BestCModeIDTags(
			CYBRBIDTG_NominalWidth, GS_SCREEN_WIDTH,
			CYBRBIDTG_NominalHeight, GS_SCREEN_HEIGHT,
			CYBRBIDTG_Depth, GS_SCREEN_DEPTH,
			TAG_DONE
		);

		if (modeId == INVALID_ID) {
			error(GS_THIS, "Could not find suitable screen mode for %ldx%ldx%ld!", GS_SCREEN_WIDTH, GS_SCREEN_HEIGHT, GS_SCREEN_DEPTH);
			return false;
		}

		sScreen = OpenScreenTags(NULL,
			SA_DisplayID, modeId,
			SA_Left, 0,
			SA_Top, 0,
			SA_Width, GS_SCREEN_WIDTH,
			SA_Height, GS_SCREEN_HEIGHT,
			SA_Depth, GS_SCREEN_DEPTH,
			SA_Title, (ULONG) GS_GAME_NAME,
			SA_Type, CUSTOMSCREEN,
			SA_SysFont, 1,
			TAG_DONE
		);

		if (sScreen == NULL) {
			error(GS_THIS, "Could open Screen for %ldx%ldx%ld!", GS_SCREEN_WIDTH, GS_SCREEN_HEIGHT, GS_SCREEN_DEPTH);
			return false;
		}
		
		sScreenBuffer = AllocScreenBuffer(
			sScreen,
			NULL,
			SB_SCREEN_BITMAP
		);

		if (sScreenBuffer == NULL)
		{
			error(GS_THIS, "Could open ScreenBuffer for %ldx%ldx%ld!", GS_SCREEN_WIDTH, GS_SCREEN_HEIGHT, GS_SCREEN_DEPTH);
			return false;
		}

		InitRastPort(&sRastPort);
		sRastPort.BitMap = sScreenBuffer->sb_BitMap;

		sWindow = OpenWindowTags(NULL,
			WA_Left, 0,
			WA_Top, 0,
			WA_Width, GS_SCREEN_WIDTH,
			WA_Height, GS_SCREEN_HEIGHT,
			WA_CustomScreen, (ULONG)sScreen,
			WA_Backdrop, TRUE,
			WA_Borderless, TRUE,
			WA_DragBar, FALSE,
			WA_Activate, TRUE,
			WA_SimpleRefresh, TRUE,
			WA_CloseGadget, FALSE,
			WA_DepthGadget, FALSE,
			WA_IDCMP, IDCMP_CLOSEWINDOW | IDCMP_VANILLAKEY |IDCMP_IDCMPUPDATE | IDCMP_INTUITICKS,
			TAG_END
		);
		
		if (sScreenBuffer == NULL)
		{
			error(GS_THIS, "Could open Window for %ldx%ldx%ld!", GS_SCREEN_WIDTH, GS_SCREEN_HEIGHT, GS_SCREEN_DEPTH);
			return false;
		}

		return true;
	}

	bool closeScreen() {
		
		if (sScreenBuffer && sScreen)
		{
			FreeScreenBuffer(sScreen, sScreenBuffer);
			sScreenBuffer = NULL;
		}

		if (sWindow)
		{
			CloseWindow(sWindow);
			sWindow = NULL;
		}

		if (sScreen)
		{
			CloseScreen(sScreen);
			sScreen = NULL;
		}

		return true;
	}

	void screenLoop() {

		while (QUIT_NOW == false) {

			ULONG signal = Wait((1 << sWindow->UserPort->mp_SigBit) | SIGBREAKF_CTRL_C);

			if (signal & SIGBREAKF_CTRL_C)
			{
				QUIT_NOW = true;
			}

			struct IntuiMessage* msg;

			while (true)
			{
				msg = (struct IntuiMessage*)GetMsg(sWindow->UserPort);

				if (msg == NULL)
					break;

				struct TagItem* tstate, * tag, * tags;
				ULONG tiData;

				switch (msg->Class)
				{
					case IDCMP_CLOSEWINDOW: {
						QUIT_NOW = true;
					}
					break;
					case IDCMP_VANILLAKEY: {
						if (msg->Code == 27) {
							QUIT_NOW = true;
						}
					}
					break;
					case IDCMP_INTUITICKS: {
					
						/*
							TODO: This is placeholder code with the IDCMP_INTUITICKS flag.

							This will tick the runFrame function approx 10 times a second.

							Eventually this will be replaced by a proper OS friendly timer callback.

						*/
						runFrame();

					}
					break;
				}
				ReplyMsg((struct Message*)msg);
			}

		}

	}
}