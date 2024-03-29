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

#ifndef GS_INPUT_H
#define GS_INPUT_H

#include "types.h"

namespace gs
{

	extern uint8 KEY_EVENT;

	enum KeyEvent {
		KE_None = 0,
		KE_DebugDumpStack = 1,
		KE_DebugDumpVerbs = 2,
		KE_DebugShowPalette = 3,
		KE_SkipCutscene = 4,
		KE_StepForward = 5,
		KE_StepBackward = 6,
		KE_StepAhead = 7
	};

}

#endif