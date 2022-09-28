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
#include "shared/string.h"

GS_EXPORT gs_bool gs_FindTag(gs_File* file, gs_tag match, gs_TagPair* out_tag) {
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

GS_EXPORT gs_bool gs_SeekToAndFindTag(gs_File* file, uint32 absPos, gs_tag match, gs_TagPair* out_tag) {
	gs_Seek(file, absPos);
	return gs_FindTag(file, match, out_tag);
}

GS_EXPORT void gs_FileCopy(gs_File* dst, gs_File* src, uint32 length) {

	byte buffer[4096];

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

GS_EXPORT void gs_ReadTagPair(gs_File* file, gs_TagPair* tagPair) {
	tagPair->start = file->position;
	gs_ReadBytes(file, &tagPair->tag, 4);
	uint32 length = gs_ReadUInt32_BE(file);
	tagPair->end = tagPair->start + length;
}

GS_EXPORT void gs_WriteTagPairStart(gs_File* file, gs_TagPair* tagPair, uint32 tag) {

	tagPair->tag = tag;
	tagPair->start = gs_FilePosition(file);
	gs_WriteBytes(file, &tag, 4);
	gs_WriteUInt32_BE(file, 0);

	//gs_WriteUInt32_BE(file, gs_TagPairDataLength(tagPair));
}

GS_EXPORT void gs_WriteTagPairEnd(gs_File* file, gs_TagPair* tagPair) {
	uint32 end = gs_FilePosition(file);
	uint32 length = end - tagPair->start;
	tagPair->end = end;

	gs_Seek(file, tagPair->start + 4);
	gs_WriteUInt32_BE(file, length);
	gs_Seek(file, end);

}

GS_EXPORT void gs_WriteTagPairKnownSize(gs_File* file, uint32 tag, uint32 size) {
	gs_WriteBytes(file, &tag, 4);
	gs_WriteUInt32_BE(file, size);
}

GS_EXPORT void gs_WriteStr(gs_File* file, const char* str) {
	if (str == NULL)
		return;

	uint32 length = gs_str_length(str);
	gs_WriteBytes(file, str, length);
}

GS_EXPORT void gs_WriteFmt(gs_File* file, const char* fmt, ...) {
	static char buffer[1024];

	GS_VARARG_LIST(args);
	GS_VARARG_BEGIN(args, fmt);
	uint32 length = gs_format_vargs(buffer, sizeof(buffer), fmt, GS_VARARG_ARG(args, void*));
	GS_VARARG_END(args);

	gs_WriteBytes(file, &buffer[0], length);
}
