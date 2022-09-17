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

#define GS_FILE "main"

#include "shared/forward.h"
#include "shared/error.h"
#include "shared/game.h"

#define VERSION_NUM "0.6"

const char* gs_VersionString = "$VER: goodsoup " VERSION_NUM " " GS_ARCH_NAME " (" __AMIGADATE__ ")";

// graphics/screen.amiga.c
GS_IMPORT gs_bool gs_OpenScreen();

// graphics/screen.amiga.c
GS_IMPORT gs_bool gs_CloseScreen();

// graphics/screen.amiga.c
GS_IMPORT gs_bool gs_EnterScreenLoop();

// events/timer.amiga.c
GS_IMPORT gs_bool gs_InitializeTimer();

// events/timer.amiga.c
GS_IMPORT void gs_TeardownTimer();

// formats/la0.c
GS_IMPORT int gs_LA0_ConvertToOptimized();

int32 gs_Main(int32 param) {

	gs_debug_str(&gs_VersionString[6]);



	if (param == 0)
	{
		
		if (gs_OpenScreen() == FALSE) {
			goto exit;
		}

		if (gs_InitializeTimer() == FALSE) {
			goto exit;
		}

		gs_EnterScreenLoop();
	
	exit:

		gs_TeardownTimer();
		gs_CloseScreen();

		return 0;
	}
	else
	{
		switch (param)
		{
			case GS_PARAM_CONVERT_SCRIPTS:
				return gs_LA0_ConvertToOptimized();
		}
	}



	return 1;
}