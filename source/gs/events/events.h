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

#ifndef GS_EVENTS_H
#define GS_EVENTS_H

#include "shared/forward.h"

typedef enum gs_InputEventKind {
	IEK_MouseMove,
	IEK_MouseLeftButton,
	IEK_MouseRightButton,
	IEK_KeyPress,
	IEK_KeyUp,
	IEK_Quit,
	IEK_Load,
	IEK_Save,
	IEK_Pause,
} gs_InputEventKind;

typedef void(*gs_InputEventHandler)(uint16 kind, int32 p0, int32 p1);

void gs_HandleInputEvent(uint16 kind, int32 p0, int32 p1);
void gs_PushInputEventHandler(gs_InputEventHandler handler);
void gs_PopInputEventHandler();

#endif
