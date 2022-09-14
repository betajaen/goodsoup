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

#ifndef GS_INDEX_H
#define GS_INDEX_H

#include "shared/forward.h"
#include "shared/game.h"

// This is a reinterpretation of the LA0 files which have been converted to GSI files.
// These hold:-
//		- Room Files (ideally sequential)
//		- Global Script Offsets (from the GSS file)
//
// Object data is held in the GSO file.
//
typedef struct gs_Index {
	// Which Room corresponds to a GSR file.
	uint8	roomFiles[GS_NUM_ROOMS];
	// The offset to a global script in the GSS file.
	uint16  globalScriptOffsets[GS_NUM_GLOBAL_SCRIPTS];
} gs_Index;

#endif
