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

#ifndef GS_SCHEMA_ITERATOR_H
#define GS_SCHEMA_ITERATOR_H

#include "shared/forward.h"

typedef struct gs_Script gs_Script;

typedef enum gs_ScriptArgType {
	SAT_None = 0,
	SAT_Long = 1,
	SAT_Word = 2,
	SAT_Byte = 3,
	SAT_Text = 4,
	SAT_StackLong = 5,
	SAT_StackWord = 6,
	SAT_StackByte = 7
} gs_ScriptArgType;

typedef struct gs_ScriptIteratorArg {
	union {
		byte  bValue;
		int32 lValue;
		char* sValue;
	};
	uint16 type;
} gs_ScriptIteratorArg;

typedef struct gs_ScriptIterator {
	byte* data;
	byte op1;
	byte op2;
	struct gs_Script* script;
	uint32 pc;
	uint8 iteratorState;
	uint8 numArgs;
	gs_ScriptIteratorArg args[8];

} gs_ScriptIterator;

void gs_ScriptIteratorInitialize(gs_Script* script, gs_ScriptIterator* iterator);

gs_bool gs_ScriptIteratorNext(gs_ScriptIterator* script);

#endif
