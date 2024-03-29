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

#define GS_FILE "timer"

#include "shared/forward.h"

#ifndef GS_OS3_ARCH
#error "GS_OS3_ARCH must be defined to compile this file."
#endif

#include "shared/error.h"

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/intuition.h>

#include <exec/ports.h>
#include <proto/timer.h>
#include <inline/timer.h>
#include <clib/exec_protos.h>
#include <clib/alib_protos.h>

// Required by timer.device
struct Device* TimerBase;

typedef struct TimerCallbackState {
	struct TimerCallbackState *prev, *next;
	uint32 time_usec;
	gs_callback callback;
} TimerCallbackState;


GS_PRIVATE struct MsgPort* sTimerMsgPort = NULL;
GS_PRIVATE struct timerequest* sTimerRequest = NULL;
GS_PRIVATE uint32 sTimerBit = 0;
GS_PRIVATE TimerCallbackState *sTimerFirst = NULL;
GS_PRIVATE TimerCallbackState *sTimerLast = NULL;

GS_EXPORT gs_bool gs_InitializeTimer() {

	gs_debug_str("Initializing Timer.");

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

	gs_debug_str("Initialized Timer.");

	return TRUE;
}

GS_EXPORT void gs_TeardownTimer() {

	gs_debug_str("Tearing down Timer.");

	if (sTimerRequest != NULL && sTimerBit != 0) {

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

	gs_debug_str("Teared down Timer.");
}

GS_EXPORT void gs_QueueTimer_usec(uint32 time_usec) {
	/* TODO */
}

GS_EXPORT void gs_QueueTimer_msec(uint32 time_msec) {
	gs_QueueTimer_usec(time_msec * 1000);
}