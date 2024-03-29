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

#define GS_FILE "script_gs8"

#include "shared/forward.h"
#include "shared/error.h"
#include "shared/game.h"
#include "shared/file.h"

#include "script.h"

GS_PRIVATE void convertLA8ToGS8(gs_File* file, gs_Script* script) {
	/* TODO */
}

GS_EXPORT void gs__SaveScriptData_GS8(gs_File* file, gs_Script* script) {

	if (script->scriptFormat == SSF_GS8) {
		gs_WriteBytes(file, script->data, script->dataLength_bytes);
		return;
	}
	else if (script->scriptFormat == SSF_LA8) {
		convertLA8ToGS8(file, script);
	}
	else {
		gs_error_str("Unsupported source script format to GS8");
	}
}