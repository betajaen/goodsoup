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

GS_PRIVATE int convertRNAM(gs_File* src) {

}

GS_PRIVATE int checkMAXS(gs_File* src) {

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



		gs_SkipTagPair(&file, &tag);
	}

	gs_CloseFile(&file);


	return 0;
}