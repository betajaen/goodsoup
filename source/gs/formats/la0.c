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
#include "shared/memory.h"
#include "shared/string.h"
#include "shared/fs.h"


#define ENFORCE_MAXS1(CONSTANT) \
	value = gs_ReadUInt32_LE(src);\
	if (value != CONSTANT) {\
		gs_error_fmt("Unknown Game version! Difference for \"%s\" %ld vs %ld.", GS_STR(CONSTANT), CONSTANT, value);\
		return 1;\
	}

#define CREATE_RES_DRAWER(PATH, NAME) \
	if (gs_CreateDrawer(PATH) == FALSE) {\
		gs_error_str("Could not create " NAME " drawer.");\
		return 1;\
	}

GS_PRIVATE int checkMAXS(gs_File* src) {

	gs_TagPair maxs;
	if (gs_SeekToAndFindTag(src, 0, gs_MakeTag('M', 'A', 'X', 'S'), &maxs) == FALSE) {
		gs_error_str("Could not find MAXS tag in LA0 file.");
		return 1;
	}


	uint32 value;
	gs_Skip(src, 100); // Skip Copyright Header
	
	
	ENFORCE_MAXS1(GS_NUM_INT_GLOBALS);
	ENFORCE_MAXS1(GS_NUM_BOOL_GLOBALS);
	gs_Skip(src, sizeof(uint32));
	ENFORCE_MAXS1(GS_NUM_GLOBAL_SCRIPTS);
	ENFORCE_MAXS1(GS_NUM_SOUNDS);
	ENFORCE_MAXS1(GS_NUM_CHARSETS);
	ENFORCE_MAXS1(GS_NUM_COSTUMES);
	ENFORCE_MAXS1(GS_NUM_ROOMS);
	gs_Skip(src, sizeof(uint32));
	ENFORCE_MAXS1(GS_NUM_GLOBAL_OBJECTS);
	gs_Skip(src, sizeof(uint32));
	ENFORCE_MAXS1(GS_NUM_LOCAL_OBJECTS);
	ENFORCE_MAXS1(GS_NUM_NEWNAMES);
	ENFORCE_MAXS1(GS_NUM_FLOBJECTS);
	ENFORCE_MAXS1(GS_NUM_INVENTORY);
	ENFORCE_MAXS1(GS_NUM_ARRAY);
	ENFORCE_MAXS1(GS_NUM_VERBS);

	gs_verbose_str("MAXS Check Passed.");
	return 0;
}

GS_PRIVATE int createDrawers() {
	
	CREATE_RES_DRAWER(GS_PATH_GS_DATA_DIR, "data");
	CREATE_RES_DRAWER(GS_PATH_GS_TABLE_DIR, "table");
	CREATE_RES_DRAWER(GS_PATH_GS_ROOM_DIR, "room");
	CREATE_RES_DRAWER(GS_PATH_GS_SCRIPTS_DIR, "scripts");

	return 0;
}

GS_PRIVATE int extractRoom(gs_File* diskFile, uint8 roomNum, uint8 diskNum, uint32 offset) {

	char path[sizeof(GS_PATH_GS_ROOM_FMT) + 4];
	gs_TagPair lflf;
	gs_File dst;

	gs_format(path, sizeof(path), GS_PATH_GS_ROOM_FMT, roomNum);

	gs_OpenFileWrite(&dst, path, GS_COMMENT_FILE_LINE);

	gs_Seek(diskFile, offset);
	gs_ReadTagPair(diskFile, &lflf);
	uint32 length = 8;
	gs_WriteTagStr(&dst, "LFLF");
	gs_WriteUInt32_BE(&dst, 0);

	gs_debug_fmt("%lu:%lu LFLF pos = %ld length = %ld", diskNum, roomNum, lflf.start, gs_TagPairDataLength(&lflf));

	while (gs_EndOfFile(diskFile) == FALSE && gs_EndOfTagPair(diskFile, &lflf) == FALSE) {
		gs_TagPair tag;
		gs_ReadTagPair(diskFile, &tag);
		
		if (gs_IsTagPair(&tag, 'L', 'F', 'L', 'F')) {
			break;
		}

		if (gs_IsTagPair(&tag, 'S', 'C', 'R', 'P')) {
			gs_verbose_fmt("%lu:%lu Skip %s %lu %lu", diskNum, roomNum, gs_TagPair2Str(&tag), gs_FilePosition(diskFile), (gs_TagPairDataLength(&tag) + 8));
			gs_SeekTagPairEnd(diskFile, &tag);
			continue;
		}
		

		gs_WriteTagPair(&dst, &tag);
		uint32 tagLen = gs_TagPairDataLength(&tag);
		length += tagLen + 8;
		gs_verbose_fmt("%lu:%lu Copy %s %lu %lu", diskNum, roomNum, gs_TagPair2Str(&tag), gs_FilePosition(diskFile), tagLen);
		gs_FileCopy(&dst, diskFile, tagLen);
	}

	gs_Seek(&dst, 4);
	gs_WriteUInt32_BE(&dst, length);

	gs_CloseFile(&dst);

	gs_debug_fmt("Wrote Room %ld", roomNum);

}

GS_PRIVATE int convertRoomIndexData(gs_File* indexFile, gs_File* diskFiles) {
	int rc = 0;
	uint8* roomDiskNums = NULL;
	uint32* roomDiskOffsets = NULL;

	gs_TagPair tag;
	
	roomDiskNums = gs_Allocate(GS_NUM_ROOMS, sizeof(byte), MF_Clear, GS_COMMENT_FILE_LINE);
	roomDiskOffsets = gs_Allocate(GS_NUM_ROOMS, sizeof(uint32), MF_Clear, GS_COMMENT_FILE_LINE);

	for (uint8 diskNum = 0; diskNum < GS_NUM_DISKS; diskNum++) {

		gs_File* diskFile = &diskFiles[diskNum];

		if (gs_SeekToAndFindTag(diskFile, 8, gs_MakeTag('L', 'O', 'F', 'F'), NULL) == FALSE) {
			gs_error_fmt("Could not find LOFF tag in LA%d file", diskNum);
		}

		uint8 numRooms = gs_ReadByte(diskFile);

		for (uint8 i = 0; i < numRooms; i++) {
			uint8 roomNum = gs_ReadByte(diskFile);
			uint32 roomOffset = gs_ReadUInt32_LE(diskFile);

			roomDiskNums[roomNum] = diskNum;
			roomDiskOffsets[roomNum] = roomOffset;
		
			// gs_verbose_fmt("Room %lu on disk %lu is at %lx", (uint32) roomNum, (uint32) diskNum, (uint32) roomOffset);
		}

		
		for (uint8 roomNum = 1; roomNum < GS_NUM_ROOMS; roomNum++) {

			uint8 roomDiskNum = roomDiskNums[roomNum];

			if (roomDiskNum != diskNum)
				continue;

			uint32 roomOffset = roomDiskOffsets[roomNum];

			if (roomOffset == 0)
				continue;

			extractRoom(diskFile, roomNum, diskNum, roomDiskOffsets[roomNum]);

		}

	}



exit:
	gs_Deallocate(roomDiskOffsets);
	gs_Deallocate(roomDiskNums);
	return rc;
}

GS_EXPORT int gs_LA0_ConvertToOptimized() {
	int rc = 0;
	gs_File indexFile = { 0 };
	gs_File diskFiles[GS_NUM_DISKS] = { 0 };
	char diskPath[sizeof(GS_PATH_LA_DISK_FMT) + 4];

	if (createDrawers() != 0) {
		rc = 1;
		goto exit;
	}


	// Load Index File
	if (gs_OpenFileRead(&indexFile, GS_PATH_LA_INDEX, GS_COMMENT_FILE_LINE_NOTE("Index File")) == FALSE) {
		gs_error_str("Could not open index file.");
		rc = 1;
		goto exit;
	}
	
	// Load Disks
	for (uint8 i = 0; i < GS_NUM_DISKS; i++) {
		gs_format(diskPath, sizeof(diskPath), GS_PATH_LA_DISK_FMT, 1 + i);

		gs_debug_fmt("Loading Room %s", diskPath);
		
		if (gs_OpenFileRead(&diskFiles[i], diskPath, GS_COMMENT_FILE_LINE_NOTE("Room File")) == FALSE) {
			gs_error_fmt("Could not open disk file %lu.", (uint32) i);
			rc = 1;
			goto exit;
		}

	}

	if (checkMAXS(&indexFile) != 0) {
		rc = 1;
		goto exit;
	}

	if (convertRoomIndexData(&indexFile, &diskFiles[0]) != 0) {
		rc = 1;
		goto exit;
	}


exit:
	
	for (uint8 i = 0; i < GS_NUM_DISKS; i++) {
		gs_CloseFile(&diskFiles[i]);
	}

	gs_CloseFile(&indexFile);


	return 0;
}