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

GS_IMPORT gs_bool gs_FindTag(gs_File* file, gs_tag match, gs_TagPair* out_tag) {
	gs_TagPair tag;

	gs_verbose_fmt("Find tag %s", gs_Tag2Str(match));

	while (gs_EndOfFile(file) == FALSE) {
		gs_ReadTagPair(file, &tag);

		if (tag.tag == match) {
			gs_verbose_fmt("YES for %s", gs_Tag2Str(tag.tag));
			if (out_tag != NULL) {
				*out_tag = tag;
			}
			return TRUE;
		}
		gs_verbose_fmt("NO for %s %ld", gs_Tag2Str(tag.tag), tag.end);
		gs_SeekTagPairEnd(file, &tag);
	}

	return FALSE;
}

GS_IMPORT gs_bool gs_SeekToAndFindTag(gs_File* file, uint32 absPos, gs_tag match, gs_TagPair* out_tag) {
	gs_Seek(file, absPos);
	return gs_FindTag(file, match, out_tag);
}

GS_IMPORT void gs_FileCopy(gs_File* dst, gs_File* src, uint32 length) {

	byte buffer[1024];

	while (length > 0) {

		uint32 copySize = sizeof(buffer);

		if (copySize > length) {
			copySize = length;
		}

		gs_ReadBytes(src, buffer, copySize);
		gs_WriteBytes(dst, buffer, copySize);

		length -= copySize;
	}

}