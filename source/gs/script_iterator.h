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

typedef struct gs_ScriptIterator {
	byte* data;
	uint32 pc;
	byte op1;
	byte op2;
	struct gs_Script* script;
	uint32 opcodeLength;
	uint8 iteratorState;
	uint8 argsLength;
	uint8 args[16];
} gs_ScriptIterator;

void gs_ScriptIteratorInitialize(gs_Script* script, gs_ScriptIterator* iterator);

gs_bool gs_ScriptIteratorNext(gs_ScriptIterator* script);

#endif
