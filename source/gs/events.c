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

#define GS_FILE "events"

#include "shared/forward.h"
#include "shared/error.h"
#include "events.h"

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/intuition.h>

#include <exec/ports.h>
#include <proto/timer.h>
#include <inline/timer.h>
#include <clib/exec_protos.h>
#include <clib/alib_protos.h>

// --- Intution Events ---

extern struct Screen* gs_Screen;
extern struct ScreenBuffer* gs_ScreenBuffer;
extern struct Window* gs_Window;
extern struct RastPort gs_RastPort;

static void InitializeWindowEvents() {
	// @TODO
}

static void TeardownWindowEvents() {
	// @TODO
}

// --- Timer Events ---

struct Device* TimerBase;
struct MsgPort* sTimerMsgPort;
struct timerequest* sTimerRequest;
uint32 sTimerBit;

typedef struct TimerCallbackState {
	struct TimerCallbackState *prev, *next;
	uint32 time_usec;
	gs_TimerCallback callback;
} TimerCallbackState;

TimerCallbackState *sTimerFirst, *sTimerLast;


static gs_bool InitializeTimerEvents() {
		sTimerMsgPort = CreatePort(NULL, 0);
		if (sTimerMsgPort == NULL) {
			gs_error_str("Could not open timer message port.");
			return FALSE;
		}

		sTimerRequest = (struct timerequest*) CreateExtIO(sTimerMsgPort, sizeof(struct timerequest));

		if (sTimerRequest == NULL) {
			DeletePort(sTimerMsgPort);
			sTimerMsgPort = NULL;
			gs_error_str("Could not create timer request");
			return FALSE;
		}

		if (OpenDevice(TIMERNAME, UNIT_MICROHZ, (struct IORequest*)sTimerRequest, 0) != 0) {
			DeleteExtIO((struct IORequest*) sTimerRequest);
			sTimerRequest = NULL;
			DeletePort(sTimerMsgPort);
			sTimerMsgPort = NULL;
			gs_error_str("Could not open timer device.");
			return FALSE;
		}

		return TRUE;
}

static void TeardownTimerEvents() {
	if (sTimerRequest != NULL) {

		AbortIO((struct IORequest*) sTimerRequest);
		WaitIO((struct IORequest*) sTimerRequest);

		CloseDevice((struct IORequest*) sTimerRequest);
		DeleteExtIO((struct IORequest*) sTimerRequest);
		sTimerRequest = NULL;
	}

	if (sTimerMsgPort != NULL) {
		DeletePort(sTimerMsgPort);
		sTimerMsgPort = NULL;
	}
}


// --- General Signal/Wait Loop ---

void gs_Listen() {
	InitializeTimerEvents();

	gs_debug_str("Starting to listen.");

	Delay(100);
	TeardownTimerEvents();
}
