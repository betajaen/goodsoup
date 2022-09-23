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

#define GS_FILE "LFLF"

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

typedef int(*LaExportFn)(gs_File* srcFile, gs_TagPair* tag);

struct LaExportFnTagged {
	uint32 tag;
	LaExportFn fn;
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

GS_PRIVATE struct LaExportFnTagged sLFLFExporters[] = {
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
		
		struct LaExportFnTagged* taggedFn = &sLFLFExporters[0];

		while (TRUE) {
			
			if (taggedFn->fn == NULL) {
				// Not handled
				//// gs_debug_fmt("Not handled %s", gs_TagPair2Str(&subTag));
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

GS_EXPORT int gs_LFLF_ExtractRoom(gs_File* diskFile, uint8 roomNum, uint8 diskNum, uint32 offset) {

	gs_TagPair lflf;
	int r;
	
	sCurrentRoom = gs_NewRoom(FALSE);
	sCurrentRoom->num = roomNum;
	sCurrentRoomNumObjects = 0;
	
	gs_Seek(diskFile, offset);
	gs_ReadTagPair(diskFile, &lflf);
	
	r = loadTagContainer(diskFile, &lflf);

	if (r == 0 && gs_SaveRoomFile(sCurrentRoom) == FALSE) {
		r = 1;
	}
	else {
		gs_debug_fmt("Wrote Room %ld", roomNum);
	}

	gs_DeleteRoom(sCurrentRoom);
	

	return r;
}