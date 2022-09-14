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

#ifndef GS_COROUTINE_H
#define GS_COROUTINE_H

#include "shared/forward.h"
#include "shared/game.h"

typedef struct gs_Coroutine {
	gs_Coroutine *prev, *next;
	uint16 num;
	uint16 pc;
	uint8 state;
	uint8 flags;
	uint8 verb;
	uint8 freezeCount;
	uint8 bFreezeResistant;
	uint8 recursive;
	uint8 bIsExecuted;
	uint8 cutSceneOverride;
	uint8 hasScript;
	int32 locals[GS_NUM_LOCAL_INTS];
	void* scriptDataRef;
	// TODO...
} gs_Coroutine;

extern gs_Coroutine* gs_CoroutineStack[1 + GS_COROUTINE_STACK_SIZE];

#endif
