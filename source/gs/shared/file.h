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
	uint32 position;
	uint32 length;
	uint32 comment;
} gs_File;

typedef struct gs_TagPair gs_TagPair;


/**
 * Allocates a gs_File
 * 
 * @return The File
 */
GS_IMPORT gs_File* gs_NewFile();


/**
 * Deallocates a gs_File. If the file is open, then it is closed.
 * 
 * @return The File
 */
GS_IMPORT void gs_DeleteFile(gs_File* file);


/**
 * Opens a file for reading only.
 * 
 * Arch:
 * - For OS3 the file is opened as MODE_OLDFILE
 * - For CSTD the file is opened as rb
 * 
 * @param file The file
 * @path Path to the file
 * @comment Resource tracking comment
 * @return If the file was opened or not.
 */
GS_IMPORT gs_bool gs_OpenFileRead(gs_File* file, const char* path, uint32 comment);


/**
 * Opens a file for write only.
 * 
 * Arch:
 * - For OS3 the file is opened as MODE_NEWFILE
 * - For CSTD the file is opened as wb
 * 
 * @param file The file
 * @path Path to the file
 * @comment Resource tracking comment
 * @return If the file was opened or not.
 */
GS_IMPORT gs_bool gs_OpenFileWrite(gs_File* file, const char* path, uint32 comment);


/**
 * Closes a file.
 * 
 * @param file The file
 */
GS_IMPORT void gs_CloseFile(gs_File* file);

/**
 * Is the position of an opened file at the end of the file?
 *
 * @param file The file
 * @return Is file pos >= file length
 */
#define gs_EndOfFile(FILE_PTR) (((FILE_PTR)->position) >= ((FILE_PTR)->length))



/**
 * Is the position of an opened file at the end of a TagPair?
 *
 * @param file The file
 * @param tag  The tag pair
 * @return Is file pos >= file length
 */
#define gs_EndOfTagPair(FILE_PTR, TAG_PTR) (((FILE_PTR)->position) > ((TAG_PTR)->end))


/**
 * Get the length in bytes of an opened file
 *
 * @param file The file
 * @return file length
 */
#define gs_FileLength(FILE_PTR) ((FILE_PTR)->length)


/**
 * Get the position in bytes of an opened file
 *
 * @param file The file
 * @return file pos
 */
#define gs_FilePosition(FILE_PTR) ((FILE_PTR)->position)


/**
 * Set the position in bytes of an opened file
 * 
 * Arch Notes:
 *  - For OS3 this is implemented as Seek with OFFSET_BEGINNING
 *  - For CSTD this is implemented as fseek with SEEK_SET
 *
 * @param file The file
 * @return file Absolute position
 */
GS_IMPORT void gs_Seek(gs_File* file, uint32 absPos);


/**
 * Seek to the start of the data inside a tag pair given in an 
 * opened read file.
 * 
 * File position will move to the start of the data section as
 * start + 8.
 * 
 * @note No assumptions are made about EOF or null file.
 * 
 * @param file The file
 * @param The tag pair
 */
#define gs_SeekTagPairStart(FILE_PTR, TAG_PTR) gs_Seek(FILE_PTR, (TAG_PTR)->start + 8)

/**
 * Seek to the end of the tag pair given in an opened read file.
 * 
 * File position will move to the end of the tag pair
 * 
 * @note No assumptions are made about EOF or null file.
 * 
 * @param file The file
 * @param The tag pair
 */
#define gs_SeekTagPairEnd(FILE_PTR, TAG_PTR) gs_Seek(FILE_PTR, (TAG_PTR)->end)

 /**
  * Seeks to an absolute position and finds a tag per the gs_FindTag
  * function.
  * 
  * @param file    File to search from
  * @param absPos  Absolute position to seek to before searching
  * @param tag     Tag to search for
  * @param out_tag Copy of the tag found (Optional: NULL)
  * @return If the tag was found
  * @arch all
  */
GS_IMPORT gs_bool gs_SeekToAndFindTag(gs_File* file, uint32 absPos, gs_tag match, gs_TagPair* out_tag);


/**
 * Set the position in bytes of an opened file relative to the
 * current position.
 * 
 * The relative position can be a positive or negative number.
 * 
 * Arch Notes:
 *  - For OS3 this is implemented as Seek with OFFSET_CURRENT
 *  - For CSTD this is implemented as fseek with SEEK_CUR
 *
 * @param file The file
 * @return file Relative Position
 */
GS_IMPORT void gs_Skip(gs_File* file, int32 relPos);


/**
 * Read bytes from a opened read file into memory upto a given length.
 * 
 * File position will advance by the number of bytes read.
 * 
 * @param file The file
 * @param data Memory that is at least length in size
 * @param length Number of bytes to read
 * @return Number of bytes **actually** read.
 */
GS_IMPORT uint32 gs_ReadBytes(gs_File* file, void* data, uint32 length);


/**
 * Read one byte from an opened read file.
 * 
 * File position will advance by 1.
 * 
 * @note No assumptions are made about EOF or null file.
 * 
 * @param file The file
 * @return The value
 */
GS_IMPORT byte gs_ReadByte(gs_File* file);


/**
 * Read one int8 from an opened read file.
 * 
 * File position will advance by 1.
 * 
 * @note No assumptions are made about EOF or null file.
 * 
 * @param file The file
 * @return The value
 */
GS_IMPORT int8 gs_ReadInt8(gs_File* file);


/**
 * Read one uint8 from an opened read file.
 * 
 * File position will advance by 1.
 * 
 * @note No assumptions are made about EOF or null file.
 * 
 * @param file The file
 * @return The value
 */
GS_IMPORT uint8 gs_ReadUInt8(gs_File* file);


/**
 * Read one big-endian encoded int16 from an opened read file.
 * 
 * File position will advance by 2.
 * 
 * @note No assumptions are made about EOF or null file.
 * @arch Value will be converted into native endian after read.
 * 
 * @param file The file
 * @return The value
 */
GS_IMPORT int16 gs_ReadInt16_BE(gs_File* file);


/**
 * Read one big-endian encoded uint16 from an opened read file.
 * 
 * File position will advance by 2.
 * 
 * @note No assumptions are made about EOF or null file.
 * @arch Value will be converted into native endian after read.
 * 
 * @param file The file
 * @return The value
 */
GS_IMPORT uint16 gs_ReadUInt16_BE(gs_File* file);


/**
 * Read one little-endian encoded int16 from an opened read file.
 * 
 * File position will advance by 2.
 * 
 * @note No assumptions are made about EOF or null file.
 * @arch Value will be converted into native endian after read.
 * 
 * @param file The file
 * @return The value
 */
GS_IMPORT int16 gs_ReadInt16_LE(gs_File* file);


/**
 * Read one little-endian encoded int16 from an opened read file.
 * 
 * File position will advance by 2.
 * 
 * @note No assumptions are made about EOF or null file.
 * @arch Value will be converted into native endian after read.
 * 
 * @param file The file
 * @return The value
 */
GS_IMPORT uint16 gs_ReadUInt16_LE(gs_File* file);

#if defined(GS_BIG)
#define gs_ReadInt16_Native gs_ReadInt16_BE
#define gs_ReadUInt16_Native gs_ReadUInt16_BE
#else
#define gs_ReadInt16_Native gs_ReadInt16_LE
#define gs_ReadUInt16_Native gs_ReadUInt16_LE
#endif

/**
 * Read one big-endian encoded int32 from an opened read file.
 * 
 * File position will advance by 4.
 * 
 * @note No assumptions are made about EOF or null file.
 * @arch Value will be converted into native endian after read.
 * 
 * @param file The file
 * @return The value
 */
GS_IMPORT int32 gs_ReadInt32_BE(gs_File* file);


/**
 * Read one big-endian encoded uint32 from an opened read file.
 * 
 * File position will advance by 4.
 * 
 * @note No assumptions are made about EOF or null file.
 * @arch Value will be converted into native endian after read.
 * 
 * @param file The file
 * @return The value
 */
GS_IMPORT uint32 gs_ReadUInt32_BE(gs_File* file);


/**
 * Read one little-endian encoded int32 from an opened read file.
 * 
 * File position will advance by 4.
 * 
 * @note No assumptions are made about EOF or null file.
 * @arch Value will be converted into native endian after read.
 * 
 * @param file The file
 * @return The value
 */
GS_IMPORT int32 gs_ReadInt32_LE(gs_File* file);


/**
 * Read one little-endian encoded uint32 from an opened read file.
 * 
 * File position will advance by 4.
 * 
 * @note No assumptions are made about EOF or null file.
 * @arch Value will be converted into native endian after read.
 * 
 * @param file The file
 * @return The value
 */
GS_IMPORT uint32 gs_ReadUInt32_LE(gs_File* file);


/**
 * Read one native encoded int32 from an opened read file.
 * 
 * File position will advance by 4.
 * 
 * @note No assumptions are made about EOF or null file.
 * 
 * @param file The file
 * @return The value
 */
#if defined(GS_BIG)
#define gs_ReadInt32_Native gs_ReadInt32_BE
#else
#define gs_ReadInt32_Native gs_ReadInt32_LE
#endif


/**
 * Read one native encoded uint32 from an opened read file.
 * 
 * File position will advance by 4.
 * 
 * @note No assumptions are made about EOF or null file.
 * 
 * @param file The file
 * @return The value
 */
#if defined(GS_BIG)
#define gs_ReadUInt32_Native gs_ReadUInt32_BE
#else
#define gs_ReadUInt32_Native gs_ReadUInt32_LE
#endif


/**
 * Read a GS or LA style TagPair from a read file.
 * 
 * File position will advance by 8.
 * 
 * @note No assumptions are made about EOF or null file.
 * 
 * @param file The file
 * @return The value
 */
GS_IMPORT void gs_ReadTagPair(gs_File* file, gs_TagPair* tagPair);


/**
 * Write memory to opened write file to the current position.
 * 
 * File position will advance by length
 * 
 * @note No assumptions are made about EOF or null file and data.
 * 
 * @param file The file
 * @param data Data to write
 * @param length Amount of data to write in bytes
 * 
 */
GS_IMPORT void gs_WriteBytes(gs_File* file, void* data, uint32 length);


/**
 * Write a byte to an opened write file to the current position.
 * 
 * File position will advance by 1
 * 
 * @param file The file
 * @param value Value to write
 * 
 */
GS_IMPORT void gs_WriteByte(gs_File* file, byte value);


/**
 * Write a int8 to an opened write file to the current position.
 * 
 * File position will advance by 1
 * 
 * @param file The file
 * @param value Value to write
 * 
 */
GS_IMPORT void gs_WriteInt8(gs_File* file, int8 value);


/**
 * Write a uint8 to an opened write file to the current position.
 * 
 * File position will advance by 1
 * 
 * @param file The file
 * @param value Value to write
 * 
 */
GS_IMPORT void gs_WriteUInt8(gs_File* file, uint16 value);


/**
 * Write a int16 as big-endian to an opened write file 
 * to the current position.
 * 
 * File position will advance by 2
 * 
 * @param file The file
 * @param value Value to write
 * 
 */
GS_IMPORT void gs_WriteInt16_BE(gs_File* file, int16 value);


/**
 * Write a uint16 as big-endian to an opened write file 
 * to the current position.
 * 
 * File position will advance by 2
 * 
 * @param file The file
 * @param value Value to write
 * 
 */
GS_IMPORT void gs_WriteUInt16_BE(gs_File* file, uint16 value);


/**
 * Write a int16 as little-endian to an opened write file 
 * to the current position.
 * 
 * File position will advance by 2
 * 
 * @param file The file
 * @param value Value to write
 * 
 */
GS_IMPORT void gs_WriteInt16_LE(gs_File* file, int16 value);


/**
 * Write a uint16 as little-endian to an opened write file 
 * to the current position.
 * 
 * File position will advance by 2
 * 
 * @param file The file
 * @param value Value to write
 * 
 */
GS_IMPORT void gs_WriteUInt16_LE(gs_File* file, uint16 value);


/**
 * Write a int16 in native-endian to an opened write file 
 * to the current position.
 * 
 * File position will advance by 2
 * 
 * @param file The file
 * @param value Value to write
 * 
 */
#if defined(GS_BIG)
#define gs_WriteInt16_Native gs_WriteInt16_BE
#else
#define gs_WriteInt16_Native gs_WriteInt16_BE
#endif


/**
 * Write a uint16 in native-endian to an opened write file 
 * to the current position.
 * 
 * File position will advance by 2
 * 
 * @param file The file
 * @param value Value to write
 * 
 */
#if defined(GS_BIG)
#define gs_WriteUInt16_Native gs_WriteUInt16_BE
#else
#define gs_WriteUInt16_Native gs_WriteUInt16_LE
#endif


/**
 * Write a int32 as big-endian to an opened write file 
 * to the current position.
 * 
 * File position will advance by 4
 * 
 * @param file The file
 * @param value Value to write
 * 
 */
GS_IMPORT void gs_WriteInt32_BE(gs_File* file, int32 value);


/**
 * Write a uint32 as big-endian to an opened write file 
 * to the current position.
 * 
 * File position will advance by 4
 * 
 * @param file The file
 * @param value Value to write
 * 
 */
GS_IMPORT void gs_WriteUInt32_BE(gs_File* file, uint32 value);


/**
 * Write a int32 as little-endian to an opened write file 
 * to the current position.
 * 
 * File position will advance by 4
 * 
 * @param file The file
 * @param value Value to write
 * 
 */
GS_IMPORT void gs_WriteInt32_LE(gs_File* file, int32 value);


/**
 * Write a uint32 as little-endian to an opened write file 
 * to the current position.
 * 
 * File position will advance by 4
 * 
 * @param file The file
 * @param value Value to write
 * 
 */
GS_IMPORT void gs_WriteUInt32_LE(gs_File* file, uint32 value);


/**
 * Write a int32 in native-endian to an opened write file 
 * to the current position.
 * 
 * File position will advance by 4
 * 
 * @param file The file
 * @param value Value to write
 * 
 */
#if defined(GS_BIG)
#define gs_WriteInt32_Native gs_WriteInt32_BE
#else
#define gs_WriteInt32_Native gs_WriteInt32_LE
#endif


/**
 * Write a uint32 in native-endian to an opened write file 
 * to the current position.
 * 
 * File position will advance by 4
 * 
 * @param file The file
 * @param value Value to write
 * 
 */
#if defined(GS_BIG)
#define gs_WriteUInt32_Native gs_WriteUInt32_BE
#else
#define gs_WriteUInt32_Native gs_WriteUInt32LBE
#endif

/**
 * Writes a string representation as a tag as four characters 
 * in left-to-right order to a write file.
 * 
 * @param file File to write to
 * @param tagStr Tag string to write to
 * 
 */
GS_IMPORT void gs_WriteTagStr(gs_File* file, char* tagStr);


/**
 * Writes the beginning of a TagPair to a opened write file
 * 
 * Used with gs_WriteTagPairEnd
 * 
 * @param file File to write to
 * @param out_tagPair TagPair to use
 * @param tag Tag Name
 * 
 */
GS_IMPORT void gs_WriteTagPairStart(gs_File* file, gs_TagPair* out_tagPair, uint32 tag);


/**
 * Writes the beginning of a TagPair to a opened write file
 * 
 * Used with gs_WriteTagPairEnd
 * 
 * @param file File to write to
 * @param out_tagPair TagPair to use
 * @param tag Tag Name
 * 
 */
GS_IMPORT void gs_WriteTagPairKnownSize(gs_File* file, uint32 tag, uint32 size);

/**
 * Writes the end of a TagPair in an opened file
 * 
 * Used with gs_WriteTagPairStart
 * 
 * @param file File to write to
 * @param tagStr TagPair value to write
 * 
 */
GS_IMPORT void gs_WriteTagPairEnd(gs_File* file, gs_TagPair* tagPair);

/**
 * Seeks forward from the current position in a file to the first tag
 * pair (TAGN<Length>) in a file that matches TAGN.
 * 
 * After finding the tag, the file position will be at the first byte
 * in the data section
 * 
 * @param file    File to search from
 * @param tag     Tag to search for
 * @param out_tag Copy of the tag found (Optional: NULL)
 * @return If the tag was found.
 * @arch all
 */
GS_IMPORT gs_bool gs_FindTag(gs_File* file, gs_tag tag, gs_TagPair* out_tag);


GS_IMPORT void gs_FileCopy(gs_File* dst, gs_File* src, uint32 length);

#endif
