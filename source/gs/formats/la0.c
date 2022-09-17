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

#define GS_FILE "la0"

#include "shared/forward.h"
#include "shared/file.h"
#include "shared/game.h"
#include "shared/error.h"
#include "shared/tag.h"


#define ENFORCE_MAXS1(CONSTANT) \
		value = gs_ReadUInt32_LE(src);\
		if (value != CONSTANT) {\
			gs_error_fmt("Unknown Game version! Difference for \"%s\" %ld vs %ld.", GS_STR(CONSTANT), CONSTANT, value);\
			return 1;\
		}


GS_PRIVATE int checkMAXS(gs_File* src) {
	uint32 value;
	gs_Skip(src, 100); // Skip Copyright Header
	
	
	ENFORCE_MAXS1(GS_NUM_INT_GLOBALS);
	ENFORCE_MAXS1(GS_NUM_BOOL_GLOBALS);
	gs_Skip(src, sizeof(uint32));
	ENFORCE_MAXS1(GS_NUM_GLOBAL_SCRIPTS);
	ENFORCE_MAXS1(GS_NUM_SOUNDS);
	ENFORCE_MAXS1(GS_NUM_CHARSETS);
	ENFORCE_MAXS1(GS_NUM_COSTUMES);
	ENFORCE_MAXS1(GS_NUM_ROOMS);
	gs_Skip(src, sizeof(uint32));
	ENFORCE_MAXS1(GS_NUM_GLOBAL_OBJECTS);
	gs_Skip(src, sizeof(uint32));
	ENFORCE_MAXS1(GS_NUM_LOCAL_OBJECTS);
	ENFORCE_MAXS1(GS_NUM_NEWNAMES);
	ENFORCE_MAXS1(GS_NUM_FLOBJECTS);
	ENFORCE_MAXS1(GS_NUM_INVENTORY);
	ENFORCE_MAXS1(GS_NUM_ARRAY);
	ENFORCE_MAXS1(GS_NUM_VERBS);

	gs_verbose_str("MAXS Check Passed.");
	return 0;
}

GS_PRIVATE int convertDROO(gs_File* src) {

}

GS_PRIVATE int convertDRSC(gs_File* src) {

}

GS_PRIVATE int convertDSOU(gs_File* src) {

}

GS_PRIVATE int convertDCHR(gs_File* src) {

}

GS_PRIVATE int convertDOBJ(gs_File* src) {

}

GS_PRIVATE int convertAARY(gs_File* src) {

}

GS_EXPORT int gs_LA0_ConvertToOptimized() {
	gs_File file;

	if (gs_OpenFileRead(&file, GS_PATH_LA0) == FALSE) {
		gs_error_str("Could not open file " GS_PATH_LA0);
		return 1;
	}

	gs_debug_str("File Okay " GS_PATH_LA0);

	gs_TagPair tag;
	while (gs_Eof(&file) == FALSE) {
		gs_ReadTagPairBE(&file, &tag);

		gs_debug_fmt("Tag %s %ld", gs_TagPair2Str(&tag), tag.length);

		if (gs_IsTagPair(&tag, 'M', 'A', 'X', 'S')) {
			gs_debug_str("CHECK MAXS");
			checkMAXS(&file);
		}


		gs_SkipTagPair(&file, &tag);
	}

	gs_CloseFile(&file);


	return 0;
}