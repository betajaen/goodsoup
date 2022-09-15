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

#define GS_FILE "screenaga"

#include "shared/forward.h"

#ifndef GS_OS3_ARCH
#error "GS_OS3_ARCH must be defined to compile this file."
#endif

#include "shared/game.h"
#include "shared/error.h"

#include <proto/exec.h>
#include <proto/intuition.h>

GS_IMPORT void gs_InitializeMenu();
GS_IMPORT void gs_TeardownMenu();
GS_IMPORT void gs_HandleMenuEvent(uint32 menuCode);
GS_IMPORT void gs_EnterScreenLoop();
GS_IMPORT void gs_ExitScreenLoop();
GS_IMPORT struct Window* gs_Window;
GS_PRIVATE gs_bool sQuitLoopAlive = TRUE;

GS_EXPORT void gs_EnterScreenLoop() {

	uint32 timerBit = 0; /* TODO: Get from Timer, via a private extern function */
	uint32 windowBit = (1 << gs_Window->UserPort->mp_SigBit);
	uint32 signalBits = windowBit | timerBit | SIGBREAKF_CTRL_C;
	struct IntuiMessage* intMsg;

	sQuitLoopAlive = TRUE;

	gs_InitializeMenu();

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
					gs_HandleMenuEvent(intMsg->Code);
				}


				ReplyMsg((struct Message*) intMsg);
			}

		}

		if (signal & timerBit) {
			/* TODO: Timer */
		}

	}

	gs_TeardownMenu();

	sQuitLoopAlive = FALSE;
}

GS_EXPORT void gs_ExitScreenLoop() {
	sQuitLoopAlive = FALSE;
}
