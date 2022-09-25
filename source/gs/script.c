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

#define GS_FILE "script"

#include "shared/forward.h"
#include "shared/error.h"
#include "shared/game.h"
#include "shared/memory.h"
#include "shared/tag.h"
#include "shared/file.h"
#include "shared/string.h"


#include "script.h"

#define T gs_Script
#include "shared/list.h"

gs_Script_List sScripts = { NULL, NULL };

GS_IMPORT gs__SaveScript_8_Native(gs_File* file, gs_Script* script);

GS_IMPORT gs__SaveScript_8_Text(gs_File* file, gs_Script* script);

GS_PRIVATE int gs_ScriptProcessor_Null(struct gs_Script* script, struct gs_Coroutine* coroutine, void* stack, void* vars) {
	return 1;
}

GS_PRIVATE void gs_Script_Ctor(gs_Script* script) {
	script->next = NULL;
	script->prev = NULL;
	script->num = NULL;
	script->parent = 0;
	script->parentCObjectType = 0;
	script->scriptType = 0;
	script->scriptFormat = SSF_Null;
	script->p_gc = 0;
	script->p_processorFn = gs_ScriptProcessor_Null;
	script->dataLength_bytes = 0;
	script->data = NULL;

	gs_Script_List_PushBack(&sScripts, script);
}

GS_PRIVATE void gs_Script_Dtor(gs_Script* script) {
	/* TODO: Unload Loaded Data */

	gs_Script_List_Remove(&sScripts, script);
}



GS_EXPORT gs_Script* gs_NewScript() {
	gs_Script* script = gs_New(gs_Script, GS_COMMENT_FILE_LINE_NOTE("SCRIPT"));
	gs_Script_Ctor(script);
	return script;
}

GS_EXPORT void gs_DeleteScript(gs_Script* script) {
	gs_Script_Dtor(script);
	gs_Delete(script);
}

void gs_AllocateScriptData(gs_Script* script) {
	if (script->data != NULL) {
		return;
	}

	script->data = gs_Allocate(1, script->dataLength_bytes, MF_Clear, GS_COMMENT_FILE_LINE);
}

void gs_DeallocateScriptData(gs_Script* script) {
	if (script->data == NULL) {
		return;
	}

	gs_Deallocate(script->data);

	script->data = NULL;
	script->dataLength_bytes = 0;
}

GS_EXPORT gs_Script* gs_GetScript(uint16 scriptNum, uint16 parentNum_optional, uint8 parentCObjectType_optional) {
	gs_Script* script = sScripts.head;
	while (script) {
		if (script->num == scriptNum) {

			if (parentNum_optional != 0 && parentCObjectType_optional != 0) {
				if (script->parent == parentNum_optional && script->parentCObjectType == parentCObjectType_optional) {
					return script;
				}
				else {
					goto next;
				}
			}

			return script;
		}

		next:
		script = script->next;
	}
}

/**
 */
GS_EXPORT void gs_LoadScript(gs_Script* script, struct gs_File* file, gs_TagPair* tag) {
	/* TODO */
}

/**
 */
GS_EXPORT void gs_SaveScript(gs_Script* script, struct gs_File* dst, uint8 format) {
	gs_TagPair scriptTag;

	gs_SaveOpen(dst, &scriptTag, GS_TAG_GSC_SCRIPT);

	gs_SaveOpenKnown(dst, GS_TAG_GSD_INFO, 
		GS_FIELD_SIZEOF(gs_Script, num) +
		GS_FIELD_SIZEOF(gs_Script, parent) +
		GS_FIELD_SIZEOF(gs_Script, parentCObjectType) +
		GS_FIELD_SIZEOF(gs_Script, scriptType) +
		GS_FIELD_SIZEOF(gs_Script, scriptFormat)
	);

	gs_SaveValue(dst, script->num);
	gs_SaveValue(dst, script->parent);
	gs_SaveValue(dst, script->parentCObjectType);
	gs_SaveValue(dst, script->scriptType);
	gs_SaveValue(dst, script->scriptFormat);

	if (script->dataLength_bytes != 0) {
		gs_SaveOpenKnown(dst, GS_TAG_GSD_DATA, script->dataLength_bytes);
		gs_SaveBytes(dst, script->data, script->dataLength_bytes);
	}

	gs_SaveClose(dst, &scriptTag);
}

/**
 */
GS_EXPORT gs_Script* gs_LoadScriptFile(uint32 scriptNum) {
	/* TODO */
}

/**
 */
GS_EXPORT gs_bool gs_SaveScriptFile(gs_Script* script, uint8 format) {
	char path[sizeof(GS_PATH_GS_ROOM_FMT) + 4];
	gs_File dst;

	gs_format(path, sizeof(path), GS_PATH_GS_ROOM_FMT, script->num);
	if (gs_OpenFileWrite(&dst, path, GS_COMMENT_FILE_LINE) == FALSE) {
		return FALSE;
	}

	
	if (format == 0) {
		format = script->scriptFormat;
	}

	switch (format) {

		default: {
			gs_SaveBinaryFileHeader(&dst);
			gs_SaveScript(script, &dst, format);
		}
		break;
		case SSF_GS8: {
			gs_SaveBinaryFileHeader(&dst);
			gs__SaveScript_8_Native(&dst, script);
		}
		break;
		case SSF_Text: {
			gs__SaveScript_8_Text(&dst, script);
		}
		break;
	}
	

	gs_CloseFile(&dst);

	return TRUE;
}
