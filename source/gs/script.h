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

#ifndef GS_SCRIPT_H
#define GS_SCRIPT_H

#include "shared/forward.h"

typedef int(*gs_ScriptProcessorFn)(struct gs_Script* script, struct gs_Coroutine* coroutine, void* stack, void* vars);

typedef enum gs_ScriptType {
	ST_Global,
	ST_Room,
	ST_Object,
	ST_Enter,
	ST_Exit
} gs_ScriptType;

typedef enum gs_ScriptSaveFormat {
	SSF_Null,
	SSF_8,
	SSF_8_Native,
	SSF_8_Text
} gs_ScriptSaveFormat;

typedef struct gs_Script {
	struct gs_Script *next, *prev;
	uint16 num;
	uint16 parent;
	byte   parentCObjectType;
	byte   scriptType;
	byte   scriptFormat;
	uint8  p_gc;
	gs_ScriptProcessorFn p_processorFn;
	uint32 dataLength;
	byte*  data;
} gs_Script;


/**
 *	Create a Script onto the Heap  
 */
GS_IMPORT gs_Script* gs_NewScript();

/**
 *	Delete Script onto the Heap  
 */
GS_IMPORT void gs_DeleteScript(gs_Script* script);

/**
 * Allocate Script data onto the heap 
 */
GS_IMPORT void gs_AllocateScriptData(gs_Script* script);

/**
 * Allocate Script data onto the heap 
 */
GS_IMPORT void gs_DeallocateScriptData(gs_Script* script);

/**
 */
GS_IMPORT gs_Script* gs_GetScript(uint16 scriptNum, uint16 parentNum_optional, uint8 parentCObjectType_optional);

/**
 */
GS_IMPORT void gs_LoadScript(gs_Script* script, struct gs_File* file, gs_TagPair* tag);

/**
 */
GS_IMPORT void gs_SaveScript(gs_Script* script, struct gs_File* file, uint8 format);

/**
 */
GS_IMPORT gs_Script* gs_LoadScriptFile(uint32 scriptNum);

/**
 */
GS_IMPORT gs_bool gs_SaveScriptFile(gs_Script* scriptNum, uint8 format);

/**
 */
GS_IMPORT int gs_ScriptProcessor_8(struct gs_Script* script, struct gs_Coroutine* coroutine, void* stack, void* vars);

/**
 */
GS_IMPORT int gs_ScriptProcessor_8_Native(struct gs_Script* script, struct gs_Coroutine* coroutine, void* stack, void* vars);

#endif
