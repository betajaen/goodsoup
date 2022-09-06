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

const char* gs_VersionString = "$VER: goodsoup 0.6 (" __AMIGADATE__ ")";

// graphics/rtg.c
extern gs_bool gs_OpenScreen();

// graphics/rtg.c
extern gs_bool gs_CloseScreen();

// events.c
extern void gs_Listen();

int32 gs_Main(int32 param) {

	gs_debug_fmt("%s",&gs_VersionString[6]);

	if (gs_OpenScreen() == GS_FALSE)
		return 0;

	gs_Listen();

	gs_CloseScreen();
	return 0;
}