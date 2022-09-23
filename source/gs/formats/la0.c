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

#include "graphics/image.h"
#include "graphics/palette.h"
#include "room.h"

typedef int(*RoomTagExportFn)(gs_File* srcFile, gs_TagPair* tag);

struct RoomTagExportFnTagged {
	uint32 tag;
	RoomTagExportFn fn;
};

GS_PRIVATE gs_Room* sCurrentRoom = NULL;
uint16 sCurrentRoomNumObjects = 0;

GS_PRIVATE int enterIntoTag_impl(gs_File* srcFile, uint32 expectedTag, gs_TagPair* out_tagPair) {
	gs_ReadTagPair(srcFile, out_tagPair);

	if (out_tagPair->tag != expectedTag) {
		gs_warn_fmt("Unexpected Tag to enter into wanted %s got %s", gs_Tag2Str(expectedTag), gs_TagPair2Str(out_tagPair));
		return 1;
	}

	return 0;
}

GS_PRIVATE int skipOverTag_impl(gs_File* srcFile, uint32 expectedTag, gs_TagPair* out_tagPair) {
	gs_ReadTagPair(srcFile, out_tagPair);

	if (out_tagPair->tag != expectedTag) {
		gs_warn_fmt("Unexpected Tag to skip over wanted %s got %s", gs_Tag2Str(expectedTag), gs_TagPair2Str(out_tagPair));
		return 1;
	}

	gs_SeekTagPairEnd(srcFile, out_tagPair);

	return 0;
}

#define enterIntoTagOrFail(FILE, EXPECT_TAG_NAME, OUT_TAGPAIR) if (enterIntoTag_impl(FILE, EXPECT_TAG_NAME, OUT_TAGPAIR) == 1) { return 1;}
#define skipOverTagOrFail(FILE, EXPECT_TAG_NAME, OUT_TAGPAIR) if (skipOverTag_impl(FILE, EXPECT_TAG_NAME, OUT_TAGPAIR) == 1) { return 1;}

GS_PRIVATE int loadRHMD(gs_File* srcFile, gs_TagPair* tag) {
	
	gs_debug_str("Load RMHD");

	sCurrentRoom->loadFlags |= RLF_Data;

	gs_Skip(srcFile, 4);	// Version
	sCurrentRoom->data.width = gs_ReadUInt32_LE(srcFile); // width
	sCurrentRoom->data.height = gs_ReadUInt32_LE(srcFile); // height
	sCurrentRoomNumObjects = gs_ReadUInt32_LE(srcFile);
	gs_Skip(srcFile, 4);	// Unknown
	sCurrentRoom->data.layers = gs_ReadUInt32_LE(srcFile); // Number of Z Buffers/Layers

	gs_SeekTagPairEnd(srcFile, tag);
	return 0;
}

GS_PRIVATE int loadPALS(gs_File* srcFile, gs_TagPair* palsTag) {
	
	gs_TagPair tag;

	gs_debug_str("Load PALS");
	
	if (sCurrentRoom->palettes != NULL) {
		gs_warn_str("Room has double palette entry!");
		return 1;
	}

	// + PALS
	// +- WRAP
	// +---OFFS
	// +---APAL
	enterIntoTagOrFail(srcFile, gs_MakeId('W', 'R', 'A', 'P'), &tag);
	skipOverTagOrFail(srcFile, gs_MakeId('O', 'F', 'F', 'S'), &tag);

	uint32 numPalettes = gs_TagPairDataLength(&tag) / sizeof(uint32);

	if (numPalettes == 0) {
		gs_warn_fmt("Too little palettes! %ld", numPalettes);
		return 1;
	}
	
	if (numPalettes >= 255) {
		gs_warn_fmt("Too many palettes! %ld", numPalettes);
		return 1;
	}

	sCurrentRoom->palettes = gs_NewCObjectArray(numPalettes, gs_Palette, COT_Palette);
	sCurrentRoom->data.numPalettes = numPalettes;

	for(uint8 i=0;i < numPalettes;i++) {
		enterIntoTagOrFail(srcFile, gs_MakeId('A', 'P', 'A', 'L'), &tag);

		gs_Palette* palette = sCurrentRoom->palettes + i;
		palette->parent = sCurrentRoom->num;
		palette->parentCObjectType = COT_Room;
		palette->paletteType = PT_Chunky_256;
		gs_ReadBytes(srcFile, &palette->palette[0], (3 * 256));
	}
	
	gs_SeekTagPairEnd(srcFile, palsTag);
	return 0;
}

GS_PRIVATE int loadENCD(gs_File* srcFile, gs_TagPair* tag) {
	gs_debug_str("Load ENCD");
	gs_SeekTagPairEnd(srcFile, tag);
	return 0;
}

GS_PRIVATE int loadEXCD(gs_File* srcFile, gs_TagPair* tag) {
	gs_debug_str("Load EXCD");
	gs_SeekTagPairEnd(srcFile, tag);
	return 0;
}

GS_PRIVATE int loadOBCD(gs_File* srcFile, gs_TagPair* tag) {
	gs_debug_str("Load OBCD");
	gs_SeekTagPairEnd(srcFile, tag);
	return 0;
}

GS_PRIVATE int loadLSCR(gs_File* srcFile, gs_TagPair* tag) {
	gs_debug_str("Load LSCR");
	gs_SeekTagPairEnd(srcFile, tag);
	return 0;
}

GS_PRIVATE int loadIMAG(gs_File* srcFile, gs_TagPair* tag) {
	gs_debug_str("Load IMAG");
	gs_SeekTagPairEnd(srcFile, tag);
	return 0;
}

GS_PRIVATE int loadTagContainer(gs_File* srcFile, gs_TagPair* tag);

GS_PRIVATE struct RoomTagExportFnTagged sLFLFExporters[] = {
	{ gs_MakeId('L', 'F', 'L', 'F'), loadTagContainer },
	{ gs_MakeId('R', 'O', 'O', 'M'), loadTagContainer },
	{ gs_MakeId('R', 'M', 'H', 'D'), loadRHMD },
	{ gs_MakeId('P', 'A', 'L', 'S'), loadPALS },
	{ gs_MakeId('R', 'M', 'S', 'C'), loadTagContainer },
	{ gs_MakeId('E', 'N', 'C', 'D'), loadENCD },
	{ gs_MakeId('E', 'X', 'C', 'D'), loadEXCD },
	{ gs_MakeId('O', 'B', 'C', 'D'), loadOBCD },
	{ gs_MakeId('L', 'S', 'C', 'R'), loadLSCR },
	{ gs_MakeId('I', 'M', 'A', 'G'), loadIMAG },
	{ 0, NULL }
};

GS_PRIVATE int loadTagContainer(gs_File* srcFile, gs_TagPair* tag) {

	while(gs_FilePosition(srcFile) < tag->end) {
		gs_TagPair subTag;
		gs_ReadTagPair(srcFile, &subTag);
		
		struct RoomTagExportFnTagged* taggedFn = &sLFLFExporters[0];

		while (TRUE) {
			
			if (taggedFn->fn == NULL) {
				// Not handled
				// gs_debug_fmt("Not handled %s", gs_TagPair2Str(&subTag));
				gs_SeekTagPairEnd(srcFile, &subTag);
				break;
			}

			if (taggedFn->tag == subTag.tag) {
				int res = taggedFn->fn(srcFile, &subTag);
				if (res != 0)
					return res;

				break;
			}

			taggedFn++;
		}
	}

	return 0;
}

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
	if (gs_SeekToAndFindTag(src, 0, gs_MakeId('M', 'A', 'X', 'S'), &maxs) == FALSE) {
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

	gs_TagPair lflf;
	
	gs_Seek(diskFile, offset);
	gs_ReadTagPair(diskFile, &lflf);
	
	sCurrentRoom = gs_NewRoom(FALSE);
	sCurrentRoom->num = roomNum;
	sCurrentRoomNumObjects = 0;

	int r = loadTagContainer(diskFile, &lflf);

	if (gs_SaveRoomFile(sCurrentRoom) == FALSE) {
		r = 1;
	}
	else {
		gs_debug_fmt("Wrote Room %ld", roomNum);
	}

	gs_DeleteRoom(sCurrentRoom);
	

	return r;
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

		if (gs_SeekToAndFindTag(diskFile, 8, gs_MakeId('L', 'O', 'F', 'F'), NULL) == FALSE) {
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
			
			gs_debug_fmt("** Room %ld on Disk %ld at %lx", roomNum, diskNum, roomDiskOffsets[roomNum]);

			int r = extractRoom(diskFile, roomNum, diskNum, roomDiskOffsets[roomNum]);

			if (r != 0) {
				return r;
			}

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