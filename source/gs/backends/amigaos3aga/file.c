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
#include "shared/memory.h"
#include "shared/endian.h"

#include <proto/dos.h>

typedef struct gs_File {
	BPTR handle;
	uint32 pos;
	uint32 length;
} gs_File;

GS_EXPORT gs_File* gs_OpenRead(const char* path) {
	BPTR handle = Open(path, MODE_OLDFILE);

	if (handle == 0) {
		return NULL;
	}

	gs_File* file = gs_new(gs_File, GS_COMMENT_FILE_LINE);
	file->handle = handle;
	file->pos = 0;
	Seek(handle, 0, OFFSET_END);
	file->length = Seek(handle, 0, OFFSET_BEGINNING);

	return file;
}

GS_EXPORT gs_File* gs_OpenWrite(const char* path) {

	BPTR handle = Open(path, MODE_NEWFILE);

	if (handle == 0) {
		return NULL;
	}

	gs_File* file = gs_new(gs_File, GS_COMMENT_FILE_LINE);
	file->handle = handle;
	file->pos = 0;
	Seek(handle, 0, OFFSET_END);
	file->length = Seek(handle, 0, OFFSET_BEGINNING);

	return file;
}

GS_EXPORT void gs_Close(gs_File* file) {
	if (file != NULL) {
		Close(file->handle);
		file->handle = 0;
		file->pos = 0;
		file->length = 0;
		gs_Deallocate(file);
	}
}

GS_EXPORT uint32 gs_ReadBytes(gs_File* file, void* data, uint32 length) {
	uint32 bytesRead = Read(file->handle, data, length);
	file->pos += bytesRead;
	return bytesRead;
}

GS_EXPORT byte gs_ReadByte(gs_File* file) {
	byte val;
	file->pos += Read(file->handle, &val, sizeof(val));
	return val;
}

GS_EXPORT int8 gs_ReadInt8(gs_File* file) {
	int8 val;
	file->pos += Read(file->handle, &val, sizeof(val));
	return val;
}
GS_EXPORT uint8 gs_ReadUInt8(gs_File* file) {
	uint8 val;
	file->pos += Read(file->handle, &val, sizeof(val));
	return val;
}

GS_EXPORT int16 gs_ReadInt16_BE(gs_File* file) {
	int16 val;
	file->pos += Read(file->handle, &val, sizeof(val));
	return val;
}

GS_EXPORT uint16 gs_ReadUInt16_BE(gs_File* file) {
	uint16 val;
	file->pos += Read(file->handle, &val, sizeof(val));
	return val;
}

GS_EXPORT int16 gs_ReadInt16_LE(gs_File* file) {
	int16 val;
	file->pos += Read(file->handle, &val, sizeof(val));
	val = gs_from_le16(val);
	return val;
}

GS_EXPORT uint16 gs_ReadUInt16_LE(gs_File* file) {
	uint16 val;
	file->pos += Read(file->handle, &val, sizeof(val));
	val = gs_from_le16(val);
	return val;
}

GS_EXPORT int32 gs_ReadInt32_BE(gs_File* file) {
	int32 val;
	file->pos += Read(file->handle, &val, sizeof(val));
	return val;
}

GS_EXPORT uint32 gs_ReadUInt32_BE(gs_File* file) {
	uint32 val;
	file->pos += Read(file->handle, &val, sizeof(val));
	return val;
}

GS_EXPORT int32 gs_ReadInt32_LE(gs_File* file) {
	int32 val;
	file->pos += Read(file->handle, &val, sizeof(val));
	val = gs_from_le32(val);
	return val;
}

GS_EXPORT uint32 gs_ReadUInt32_LE(gs_File* file) {
	uint32 val;
	file->pos += Read(file->handle, &val, sizeof(val));
	val = gs_from_le32(val);
	return val;
}

GS_EXPORT void gs_WriteBytes(gs_File* file, void* data, uint32 length) {
	file->pos += Write(file->handle, data, length);	
}

GS_EXPORT void gs_WriteByte(gs_File* file, byte value) {
	file->pos += Write(file->handle, &value, sizeof(value));
}

GS_EXPORT void gs_WriteInt8(gs_File* file, int8 value) {
	file->pos += Write(file->handle, &value, sizeof(value));
}

GS_EXPORT void gs_WriteUInt8(gs_File* file, uint16 value) {
	file->pos += Write(file->handle, &value, sizeof(value));
}

GS_EXPORT void gs_WriteInt16_BE(gs_File* file, int16 value) {
	file->pos += Write(file->handle, &value, sizeof(value));
}
GS_EXPORT void gs_WriteUInt16_BE(gs_File* file, uint16 value) {
	file->pos += Write(file->handle, &value, sizeof(value));
}

GS_EXPORT void gs_WriteInt16_LE(gs_File* file, int16 value) {
	value = gs_to_le16(value);
	file->pos += Write(file->handle, &value, sizeof(value));
}

GS_EXPORT void gs_WriteUInt16_LE(gs_File* file, uint16 value) {
	value = gs_to_le16(value);
	file->pos += Write(file->handle, &value, sizeof(value));
}

GS_EXPORT void gs_WriteInt32_BE(gs_File* file, int32 value) {
	file->pos += Write(file->handle, &value, sizeof(value));
}

GS_EXPORT void gs_WriteUInt32_BE(gs_File* file, uint32 value) {
	file->pos += Write(file->handle, &value, sizeof(value));
}

GS_EXPORT void gs_WriteInt32_LE(gs_File* file, int32 value) {
	value = gs_to_le32(value);
	file->pos += Write(file->handle, &value, sizeof(value));
}

GS_EXPORT void gs_WriteUInt32_LE(gs_File* file, uint32 value) {
	value = gs_to_le32(value);
	file->pos += Write(file->handle, &value, sizeof(value));
}
