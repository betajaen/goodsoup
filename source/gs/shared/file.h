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

#ifndef GS_FILE_H
#define GS_FILE_H

#include "shared/forward.h"

typedef struct gs_File {
	gs_absptr handle;
	uint32 pos;
	uint32 length;
	uint32 comment;
} gs_File;

typedef struct gs_TagPair gs_TagPair;

GS_IMPORT gs_File* gs_NewFile();
GS_IMPORT void gs_DeleteFile(gs_File* file);
GS_IMPORT gs_bool gs_OpenFileRead(gs_File* file, const char* path, uint32 comment);
GS_IMPORT gs_bool gs_OpenFileWrite(gs_File* file, const char* path, uint32 comment);
GS_IMPORT void gs_CloseFile(gs_File* file);


GS_IMPORT gs_bool gs_Eof(gs_File* file);
GS_IMPORT uint32 gs_FileLength(gs_File* file);
GS_IMPORT uint32 gs_FilePosition(gs_File* file);
GS_IMPORT void gs_SetFilePosition(gs_File* file, uint32 absPos);
GS_IMPORT void gs_Skip(gs_File* file, int32 relPos);

GS_IMPORT uint32 gs_ReadBytes(gs_File* file, void* data, uint32 length);

GS_IMPORT byte gs_ReadByte(gs_File* file);

GS_IMPORT int8 gs_ReadInt8(gs_File* file);
GS_IMPORT uint8 gs_ReadUInt8(gs_File* file);

GS_IMPORT int16 gs_ReadInt16_BE(gs_File* file);
GS_IMPORT uint16 gs_ReadUInt16_BE(gs_File* file);
GS_IMPORT int16 gs_ReadInt16_LE(gs_File* file);
GS_IMPORT uint16 gs_ReadUInt16_LE(gs_File* file);

#if defined(GS_BIG)
#define gs_ReadInt16_Native gs_ReadInt16_BE
#define gs_ReadUInt16_Native gs_ReadUInt16_BE
#else
#define gs_ReadInt16_Native gs_ReadInt16_LE
#define gs_ReadUInt16_Native gs_ReadUInt16_LE
#endif

GS_IMPORT int32 gs_ReadInt32_BE(gs_File* file);
GS_IMPORT uint32 gs_ReadUInt32_BE(gs_File* file);
GS_IMPORT int32 gs_ReadInt32_LE(gs_File* file);
GS_IMPORT uint32 gs_ReadUInt32_LE(gs_File* file);

#if defined(GS_BIG)
#define gs_ReadInt32_Native gs_ReadInt32_BE
#define gs_ReadUInt32_Native gs_ReadUInt32_BE
#else
#define gs_ReadInt32_Native gs_ReadInt32_LE
#define gs_ReadUInt32_Native gs_ReadUInt32_LE
#endif

GS_IMPORT void gs_ReadTag(gs_File* file, char* tagStr);

GS_IMPORT void gs_ReadTagPairBE(gs_File* file, gs_TagPair* tagPair);
GS_IMPORT void gs_SkipTagPair(gs_File* file, gs_TagPair* tagPair);

GS_IMPORT void gs_WriteBytes(gs_File* file, void* data, uint32 length);

GS_IMPORT void gs_WriteByte(gs_File* file, byte);

GS_IMPORT void gs_WriteInt8(gs_File* file, int8 value);
GS_IMPORT void gs_WriteUInt8(gs_File* file, uint16 value);

GS_IMPORT void gs_WriteInt16_BE(gs_File* file, int16 value);
GS_IMPORT void gs_WriteUInt16_BE(gs_File* file, uint16 value);
GS_IMPORT void gs_WriteInt16_LE(gs_File* file, int16 value);
GS_IMPORT void gs_WriteUInt16_LE(gs_File* file, uint16 value);

#if defined(GS_BIG)
#define gs_WriteInt16_Native gs_WriteInt16_BE
#define gs_WriteUInt16_Native gs_WriteUInt16_BE
#else
#define gs_WriteInt16_Native gs_WriteInt16_LE
#define gs_WriteUInt16_Native gs_WriteUInt16_LE
#endif

GS_IMPORT void gs_WriteInt32_BE(gs_File* file, int32 value);
GS_IMPORT void gs_WriteUInt32_BE(gs_File* file, uint32 value);
GS_IMPORT void gs_WriteInt32_LE(gs_File* file, int32 value);
GS_IMPORT void gs_WriteUInt32_LE(gs_File* file, uint32 value);

#if defined(GS_BIG)
#define gs_WriteInt32_Native gs_WriteInt32_BE
#define gs_WriteUInt32_Native gs_WriteUInt32_BE
#else
#define gs_WriteInt32_Native gs_WriteInt32_LE
#define gs_WriteUInt32_Native gs_WriteUInt32LBE
#endif

GS_IMPORT void gs_WriteTag(gs_File* file, char* tagStr);

GS_IMPORT gs_bool gs_FindTag(gs_File* file, gs_tag tag, gs_TagPair* out_tag);
GS_IMPORT gs_bool gs_RewindAndFindTag(gs_File* file, uint32 rewindPos, gs_tag tag, gs_TagPair* out_tag);


#endif
