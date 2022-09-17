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

#define GS_FILE "filec"

#include "shared/forward.h"
#include "shared/file.h"
#include "shared/tag.h"
#include "shared/error.h"

GS_IMPORT gs_bool gs_FindTag(gs_File* file, gs_tag tag, gs_TagPair* out_tag) {
	gs_TagPair test;

	gs_verbose_fmt("Find tag %s", gs_Tag2Str(tag));

	while (gs_Eof(file) == FALSE) {
		gs_ReadTagPairBE(file, &test);

		if (test.tag == tag) {
			gs_verbose_fmt("YES for %s", gs_Tag2Str(test.tag));
			*out_tag = test;
			return TRUE;
		}
		gs_verbose_fmt("NO for %s", gs_Tag2Str(test.tag));
		gs_SkipTagPair(file, &test);
	}

	return FALSE;
}

GS_IMPORT gs_bool gs_RewindAndFindTag(gs_File* file, uint32 rewindPos, gs_tag tag, gs_TagPair* out_tag) {
	gs_SetFilePosition(file, rewindPos);
	return gs_FindTag(file, tag, out_tag);
}