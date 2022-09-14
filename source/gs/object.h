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

// This is a reinterpretation of the Object section of LA0 files 
// which have been converted to a GSO file.
// These hold:-
//		- Names (represented as hashes)
//		- Default States
//		- Room Numbers
//		- Owners
//		- Classes & Flags
//
//	Data is stored in Structure of Arrays format.
typedef struct gs_ObjectIndex {
	uint32 hash[GS_NUM_GLOBAL_OBJECTS];
	byte state[GS_NUM_GLOBAL_OBJECTS];
	byte roomNum[GS_NUM_GLOBAL_OBJECTS];
	byte owner[GS_NUM_GLOBAL_OBJECTS];
	uint32 classFlag[GS_NUM_GLOBAL_OBJECTS];
} gs_ObjectIndex;


typedef struct gs_Object {
	gs_Object *next, *prev;
	uint16 num;
	uint16 containerNum;
	byte   state;
	uint32 classFlag;
	// TODO...
} gs_Object;

#endif
