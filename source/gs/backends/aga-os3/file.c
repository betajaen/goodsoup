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

#ifndef GS_OS3_ARCH
#error "GS_OS3_ARCH must be defined to compile this file."
#endif

#include "shared/memory.h"
#include "shared/endian.h"
#include "shared/file.h"
#include "shared/tag.h"
#include "shared/error.h"

#include <proto/dos.h>

#define FHANDLE ((BPTR) (file->handle))

GS_EXPORT gs_File* gs_NewFile() {
	gs_File* file = gs_New(gs_File, GS_COMMENT_FILE_LINE);
	file->handle = 0;
	file->position = 0;
	file->length = 0;
	return file;
}

GS_EXPORT void gs_DeleteFile(gs_File* file) {
	if (file != NULL) {
		if (file->handle != 0) {
			gs_CloseFile(file);
		}
		gs_Deallocate(file);
	}
}

GS_EXPORT gs_bool gs_OpenFileRead(gs_File* file, const char* path, uint32 comment) {
	
	gs_debug_fmt("Opening file %s for reading.", path);

	BPTR handle = Open(path, MODE_OLDFILE);

	if (handle == 0) {
		LONG err = IoErr();
		gs_error_fmt("Could not open file %s for reading!", path);
		
		PrintFault(err, "Reason:");

		return FALSE;
	}

	file->comment = comment;
	file->handle = (gs_absptr) handle;
	file->position = 0;
	Seek(handle, 0, OFFSET_END);
	file->length = Seek(handle, 0, OFFSET_BEGINNING);
	
	gs_verbose_fmt("Opened file %s.", gs_Comment2Str(file->comment));

	return TRUE;
}

GS_EXPORT gs_bool gs_OpenFileWrite(gs_File* file, const char* path, uint32 comment) {

	gs_debug_fmt("Opening file %s for writing.", path);

	BPTR handle = Open(path, MODE_NEWFILE);

	if (handle == 0) {
		LONG err = IoErr();
		gs_error_fmt("Could not open file %s for writing!", path);
		PrintFault(err, "Reason:");
		return FALSE;
	}
	
	file->comment = comment;
	file->handle = (gs_absptr) handle;
	file->position = 0;
	Seek(handle, 0, OFFSET_END);
	file->length = Seek(handle, 0, OFFSET_BEGINNING);
	
	gs_verbose_fmt("Opened file %s.", gs_Comment2Str(file->comment));

	return TRUE;
}

GS_EXPORT void gs_CloseFile(gs_File* file) {
	if (file->handle != 0) {

		Close(FHANDLE);
		file->handle = 0;
		file->position = 0;
		file->length = 0;
		
		gs_verbose_fmt("Closed file %s.", gs_Comment2Str(file->comment));
	}
}

GS_EXPORT void gs_Seek(gs_File* file, uint32 absPos) {
	Seek(FHANDLE, absPos, OFFSET_BEGINNING);
	file->position = Seek(FHANDLE, 0, OFFSET_CURRENT);
}

GS_EXPORT void gs_Skip(gs_File* file, int32 relPos) {
	Seek(FHANDLE, relPos, OFFSET_CURRENT);
	file->position = Seek(FHANDLE, 0, OFFSET_CURRENT);
}

GS_EXPORT uint32 gs_ReadBytes(gs_File* file, void* data, uint32 length) {
	uint32 bytesRead = Read(FHANDLE, data, length);
	file->position += bytesRead;
	return bytesRead;
}

GS_EXPORT byte gs_ReadByte(gs_File* file) {
	byte val;
	file->position += Read(FHANDLE, &val, sizeof(val));
	return val;
}

GS_EXPORT int8 gs_ReadInt8(gs_File* file) {
	int8 val;
	file->position += Read(FHANDLE, &val, sizeof(val));
	return val;
}
GS_EXPORT uint8 gs_ReadUInt8(gs_File* file) {
	uint8 val;
	file->position += Read(FHANDLE, &val, sizeof(val));
	return val;
}

GS_EXPORT int16 gs_ReadInt16_BE(gs_File* file) {
	int16 val;
	file->position += Read(FHANDLE, &val, sizeof(val));
	val = gs_from_be16(val);
	return val;
}

GS_EXPORT uint16 gs_ReadUInt16_BE(gs_File* file) {
	uint16 val;
	file->position += Read(FHANDLE, &val, sizeof(val));
	val = gs_from_be16(val);
	return val;
}

GS_EXPORT int16 gs_ReadInt16_LE(gs_File* file) {
	int16 val;
	file->position += Read(FHANDLE, &val, sizeof(val));
	val = gs_from_le16(val);
	return val;
}

GS_EXPORT uint16 gs_ReadUInt16_LE(gs_File* file) {
	uint16 val;
	file->position += Read(FHANDLE, &val, sizeof(val));
	val = gs_from_le16(val);
	return val;
}

GS_EXPORT int32 gs_ReadInt32_BE(gs_File* file) {
	int32 val;
	file->position += Read(FHANDLE, &val, sizeof(val));
	val = gs_from_be32(val);
	return val;
}

GS_EXPORT uint32 gs_ReadUInt32_BE(gs_File* file) {
	uint32 val;
	file->position += Read(FHANDLE, &val, sizeof(val));
	val = gs_from_be32(val);
	return val;
}

GS_EXPORT int32 gs_ReadInt32_LE(gs_File* file) {
	int32 val;
	file->position += Read(FHANDLE, &val, sizeof(val));
	val = gs_from_le32(val);
	return val;
}

GS_EXPORT uint32 gs_ReadUInt32_LE(gs_File* file) {
	uint32 val;
	file->position += Read(FHANDLE, &val, sizeof(val));
	val = gs_from_le32(val);
	return val;
}

GS_EXPORT void gs_WriteBytes(gs_File* file, void* data, uint32 length) {
	file->position += Write(FHANDLE, data, length);	
}

GS_EXPORT void gs_WriteByte(gs_File* file, byte value) {
	file->position += Write(FHANDLE, &value, sizeof(value));
}

GS_EXPORT void gs_WriteInt8(gs_File* file, int8 value) {
	file->position += Write(FHANDLE, &value, sizeof(value));
}

GS_EXPORT void gs_WriteUInt8(gs_File* file, uint16 value) {
	file->position += Write(FHANDLE, &value, sizeof(value));
}

GS_EXPORT void gs_WriteInt16_BE(gs_File* file, int16 value) {
	file->position += Write(FHANDLE, &value, sizeof(value));
}
GS_EXPORT void gs_WriteUInt16_BE(gs_File* file, uint16 value) {
	file->position += Write(FHANDLE, &value, sizeof(value));
}

GS_EXPORT void gs_WriteInt16_LE(gs_File* file, int16 value) {
	value = gs_to_le16(value);
	file->position += Write(FHANDLE, &value, sizeof(value));
}

GS_EXPORT void gs_WriteUInt16_LE(gs_File* file, uint16 value) {
	value = gs_to_le16(value);
	file->position += Write(FHANDLE, &value, sizeof(value));
}

GS_EXPORT void gs_WriteInt32_BE(gs_File* file, int32 value) {
	file->position += Write(FHANDLE, &value, sizeof(value));
}

GS_EXPORT void gs_WriteUInt32_BE(gs_File* file, uint32 value) {
	file->position += Write(FHANDLE, &value, sizeof(value));
}

GS_EXPORT void gs_WriteInt32_LE(gs_File* file, int32 value) {
	value = gs_to_le32(value);
	file->position += Write(FHANDLE, &value, sizeof(value));
}

GS_EXPORT void gs_WriteUInt32_LE(gs_File* file, uint32 value) {
	value = gs_to_le32(value);
	file->position += Write(FHANDLE, &value, sizeof(value));
}

GS_EXPORT void gs_WriteTagStr(gs_File* file, char* tagStr) {
	file->position += Write(FHANDLE, tagStr, 4);
}