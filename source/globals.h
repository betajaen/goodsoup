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

#ifndef GS_GLOBALS_H
#define GS_GLOBALS_H

#include "types.h"

namespace gs
{
	class VirtualMachine;
	class Index;
	class VmArrayAllocator;
	class Resources;
	struct VmIntVars;
	struct VmBoolVars;

	extern VirtualMachine* VM;
	extern Index* INDEX;
	extern VmArrayAllocator* ARRAYS;
	extern Resources* RESOURCES;
	extern VmIntVars* INTS;
	extern VmBoolVars* BOOLS;
	extern uint8 CURRENT_CONTEXT;

	extern bool PAUSED;
	extern int32 SENTENCE_NUM;
	extern bool SHOW_OSD;
	extern uint32 FRAME_NUM;
	extern int32 MOUSE_X;
	extern int32 MOUSE_Y;
	extern int32 MOUSE_LMB_EVENT;
	extern int32 MOUSE_RMB_EVENT;
	extern int32 MOUSE_LMB_STATE;
	extern int32 MOUSE_RMB_STATE;
	extern uint32 OVERRIDE_FRAME_WAIT_USEC;

	extern uint8 CURRENT_ACTOR;

	extern bool DEBUG_STOP_AFTER_FRAMES;
	extern int32 DEBUG_STOP_AFTER_FRAMES_COUNT;
	extern bool FAST_MODE;
}

#endif