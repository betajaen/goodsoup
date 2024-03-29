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
#include "events/events.h"

typedef struct InputEventHandler {
	struct InputEventHandler *prev, *next;
	gs_InputEventHandler callback;
} InputEventHandler;

typedef struct InputEventHandlers {
	struct InputEventHandler *head, *tail;
} InputEventHandlers;

GS_PRIVATE InputEventHandlers sInputEventHandlerStack = { NULL, NULL };

GS_EXPORT void gs_HandleInputEvent(uint16 kind, int32 p0, int32 p1) {
	/* TODO */
}

GS_EXPORT void gs_PushInputEventHandler(gs_InputEventHandler handler) {
	/* TODO */
}

GS_EXPORT void gs_PopInputEventHandler() {
	/* TODO */
}

