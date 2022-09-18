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

#include "shared/forward.h"
#include "shared/file.h"
#include "shared/memory.h"
#include "shared/endian.h"
#include "shared/tag.h"
#include "shared/error.h"

#include <stdio.h>

#define FHANDLE ((FILE*) (file->handle))

GS_IMPORT gs_File* gs_NewFile() {
	gs_File* file = gs_new(gs_File, GS_COMMENT_FILE_LINE);
	file->handle = 0;
	file->position = 0;
	file->length = 0;
	return file;
}

GS_IMPORT void gs_DeleteFile(gs_File* file) {
	if (file != NULL) {
		if (file->handle != 0) {
			gs_CloseFile(file);
		}
		gs_Deallocate(file);
	}
}

GS_IMPORT gs_bool gs_OpenFileRead(gs_File* file, const char* path, uint32 comment) {
	FILE* handle = fopen(path, "rb");

	if (handle == NULL) {
		return FALSE;
	}
	
	file->comment = comment;
	file->handle = (gs_absptr) handle;
	file->position = 0;
	fseek(handle, 0, SEEK_END);
	file->length = ftell(handle);
	fseek(handle, 0, SEEK_SET);
	
	gs_verbose_fmt("Opened file %s.", gs_Comment2Str(file->comment));

	return TRUE;
}

GS_IMPORT gs_bool gs_OpenFileWrite(gs_File* file, const char* path, uint32 comment) {
	FILE* handle = fopen(path, "wb");

	if (handle == NULL) {
		return FALSE;
	}
	
	file->comment = comment;
	file->handle = (gs_absptr) handle;
	file->position = 0;
	fseek(handle, 0, SEEK_END);
	file->length = ftell(handle);
	fseek(handle, 0, SEEK_SET);
	
	gs_verbose_fmt("Opened file %s.", gs_Comment2Str(file->comment));

	return TRUE;
}

GS_IMPORT void gs_CloseFile(gs_File* file) {
	if (file->handle != 0) {
		fclose(FHANDLE);
		file->handle = 0;
		file->position = 0;
		file->length = 0;
		
		gs_verbose_fmt("Closed file %s.", gs_Comment2Str(file->comment));
	}
}

GS_EXPORT void gs_Seek(gs_File* file, uint32 absPos) {
	fseek(FHANDLE, absPos, SEEK_SET);
	file->position = ftell(FHANDLE);
}

GS_EXPORT void gs_Skip(gs_File* file, int32 relPos) {
	fseek(FHANDLE, relPos, SEEK_CUR);
	file->position = ftell(FHANDLE);
}

GS_EXPORT uint32 gs_ReadBytes(gs_File* file, void* data, uint32 length) {
	uint32 bytesRead = fread(data, length, 1, FHANDLE);
	file->position += bytesRead;
	return bytesRead;
}

GS_EXPORT byte gs_ReadByte(gs_File* file) {
	byte val;
	file->position += fread( &val, sizeof(val), 1, FHANDLE);
	return val;
}

GS_EXPORT int8 gs_ReadInt8(gs_File* file) {
	int8 val;
	file->position += fread( &val, sizeof(val), 1, FHANDLE);
	return val;
}
GS_EXPORT uint8 gs_ReadUInt8(gs_File* file) {
	uint8 val;
	file->position += fread( &val, sizeof(val), 1, FHANDLE);
	return val;
}

GS_EXPORT int16 gs_ReadInt16_BE(gs_File* file) {
	int16 val;
	file->position += fread( &val, sizeof(val), 1, FHANDLE);
	val = gs_from_be16(val);
	return val;
}

GS_EXPORT uint16 gs_ReadUInt16_BE(gs_File* file) {
	uint16 val;
	file->position += fread( &val, sizeof(val), 1, FHANDLE);
	val = gs_from_be16(val);
	return val;
}

GS_EXPORT int16 gs_ReadInt16_LE(gs_File* file) {
	int16 val;
	file->position += fread( &val, sizeof(val), 1, FHANDLE);
	val = gs_from_le16(val);
	return val;
}

GS_EXPORT uint16 gs_ReadUInt16_LE(gs_File* file) {
	uint16 val;
	file->position += fread( &val, sizeof(val), 1, FHANDLE);
	val = gs_from_le16(val);
	return val;
}

GS_EXPORT int32 gs_ReadInt32_BE(gs_File* file) {
	int32 val;
	file->position += fread( &val, sizeof(val), 1, FHANDLE);
	val = gs_from_be32(val);
	return val;
}

GS_EXPORT uint32 gs_ReadUInt32_BE(gs_File* file) {
	uint32 val;
	file->position += fread( &val, sizeof(val), 1, FHANDLE);
	val = gs_from_be32(val);
	return val;
}

GS_EXPORT int32 gs_ReadInt32_LE(gs_File* file) {
	int32 val;
	file->position += fread( &val, sizeof(val), 1, FHANDLE);
	val = gs_from_le32(val);
	return val;
}

GS_EXPORT uint32 gs_ReadUInt32_LE(gs_File* file) {
	uint32 val;
	file->position += fread( &val, sizeof(val), 1, FHANDLE);
	val = gs_from_le32(val);
	return val;
}

GS_EXPORT void gs_ReadTagPair(gs_File* file, gs_TagPair* tagPair) {
	file->position += fread(&tagPair->tag, 1, 4, FHANDLE);
	file->position += fread(&tagPair->end, 1, 4, FHANDLE);
	tagPair->start = file->position;
	tagPair->end = tagPair->start + gs_from_be32(tagPair->end) - 8;
}

GS_EXPORT void gs_WriteBytes(gs_File* file, void* data, uint32 length) {
	file->position += fwrite(data, length, 1, FHANDLE);	
}

GS_EXPORT void gs_WriteByte(gs_File* file, byte value) {
	file->position += fwrite(&value, sizeof(value), 1, FHANDLE);
}

GS_EXPORT void gs_WriteInt8(gs_File* file, int8 value) {
	file->position += fwrite(&value, sizeof(value), 1, FHANDLE);
}

GS_EXPORT void gs_WriteUInt8(gs_File* file, uint16 value) {
	file->position += fwrite(&value, sizeof(value), 1, FHANDLE);
}

GS_EXPORT void gs_WriteInt16_BE(gs_File* file, int16 value) {
	value = gs_to_be16(value);
	file->position += fwrite(&value, sizeof(value), 1, FHANDLE);
}
GS_EXPORT void gs_WriteUInt16_BE(gs_File* file, uint16 value) {
	value = gs_to_be16(value);
	file->position += fwrite(&value, sizeof(value), 1, FHANDLE);
}

GS_EXPORT void gs_WriteInt16_LE(gs_File* file, int16 value) {
	file->position += fwrite(&value, sizeof(value), 1, FHANDLE);
}

GS_EXPORT void gs_WriteUInt16_LE(gs_File* file, uint16 value) {
	file->position += fwrite(&value, sizeof(value), 1, FHANDLE);
}

GS_EXPORT void gs_WriteInt32_BE(gs_File* file, int32 value) {
	value = gs_to_be32(value);
	file->position += fwrite(&value, sizeof(value), 1, FHANDLE);
}

GS_EXPORT void gs_WriteUInt32_BE(gs_File* file, uint32 value) {
	value = gs_to_be32(value);
	file->position += fwrite(&value, sizeof(value), 1, FHANDLE);
}

GS_EXPORT void gs_WriteInt32_LE(gs_File* file, int32 value) {
	file->position += fwrite(&value, sizeof(value), 1, FHANDLE);
}

GS_EXPORT void gs_WriteUInt32_LE(gs_File* file, uint32 value) {
	file->position += fwrite(&value, sizeof(value), 1, FHANDLE);
}

GS_EXPORT void gs_WriteTagStr(gs_File* file, char* tagStr) {
	file->position += fwrite(tagStr, 4, 1, FHANDLE);
}