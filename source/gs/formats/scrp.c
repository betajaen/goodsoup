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

#define GS_FILE "SCRP"

#include "shared/forward.h"
#include "shared/file.h"
#include "shared/game.h"
#include "shared/error.h"
#include "shared/tag.h"
#include "shared/memory.h"
#include "shared/string.h"
#include "shared/fs.h"

#include "script.h"

gs_Script* sCurrentScript = NULL;

GS_EXPORT int gs_SCRP_ExtractGlobalScript(gs_File* diskFile, uint16 scriptNum, uint8 roomNum, uint8 diskNum, uint32 offset) {

	gs_TagPair scrp;
	int r = 0;
	
	sCurrentScript = gs_NewScript();
	sCurrentScript->num = scriptNum;
	sCurrentScript->parent = roomNum;
	sCurrentScript->scriptType = ST_Global;
	sCurrentScript->scriptFormat = SSF_LA8;
	
	gs_Seek(diskFile, offset);
	gs_ReadTagPair(diskFile, &scrp);

	sCurrentScript->dataLength_bytes = gs_TagPairDataLength(&scrp) + 1;
	gs_AllocateScriptData(sCurrentScript);

	gs_ReadBytes(diskFile, sCurrentScript->data, gs_TagPairDataLength(&scrp));

	if (gs_SaveScriptFile(sCurrentScript, SSF_GS8) == FALSE) {
		r = 1;
	}
	else {
		gs_debug_fmt("Wrote Script %ld", scriptNum);
	}

	gs_DeleteScript(sCurrentScript);
	

	return r;
}