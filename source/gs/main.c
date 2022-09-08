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

#define VERSION_NUM "0.6"

const char* gs_VersionString = "$VER: goodsoup " VERSION_NUM " " GS_ARCH_NAME " (" __AMIGADATE__ ")";

// graphics/rtg.c
extern gs_bool gs_OpenScreen();

// graphics/rtg.c
extern gs_bool gs_CloseScreen();

// events/timer.c
extern gs_bool gs_InitializeTimer();

// events/timer.c
extern void gs_TeardownTimer();

int32 gs_Main(int32 param) {

	gs_debug_str(&gs_VersionString[6]);

	if (gs_OpenScreen() == GS_FALSE) {
		goto exit;
	}

	if (gs_InitializeTimer() == GS_FALSE) {
		goto exit;
	}



	exit:
	gs_TeardownTimer();
	gs_CloseScreen();
	return 0;
}