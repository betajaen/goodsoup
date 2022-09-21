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

#define GS_FILE "gsi"

#include "shared/forward.h"
#include "shared/file.h"
#include "shared/tag.h"
#include "room.h"

GS_PRIVATE saveRoomData(gs_File* dst, gs_Room* room) {

	gs_TagPair dataTag;
	dataTag.tag = gs_MakeId('D', 'A', 'T', 'A');
	dataTag.start = gs_FilePosition(dst);
	gs_WriteTagPair(dst, &dataTag);

	gs_WriteUInt16_Native(dst, room->num);
	gs_WriteUInt16_Native(dst, room->data.width);
	gs_WriteUInt16_Native(dst, room->data.height);
	gs_WriteUInt8(dst, room->data.flags);;
	gs_WriteUInt8(dst, room->data.layers);
	
	dataTag.end = gs_FilePosition(dst);
	/* TODO: Update tag length and commit to file */

}

GS_PRIVATE saveRoomBackground(gs_File* dst, gs_Image* image) {
	/* TODO */
}

GS_EXPORT gs_SaveRoom(gs_Room* room) {
	char path[sizeof(GS_PATH_GS_ROOM_FMT) + 4];
	gs_File dst;

	gs_format(path, sizeof(path), GS_PATH_GS_ROOM_FMT, room->num);
	gs_OpenFileWrite(&dst, path, GS_COMMENT_FILE_LINE);

#if defined(GS_BIG)
	gs_WriteTagStr(&dst, "BEBE");
#else
	gs_WriteTagStr(&dst, "LELE");
#endif
	gs_WriteTagStr(&dst, "ROOM");
	gs_WriteUInt32_Native(&dst, 0);
	
	saveRoomData(&dst, room);
	
	if ((room->loadFlags & RLF_Background) && room->background) {
		saveRoomBackground(&dst, room->background);
	}
	



	// Commit length.
	uint32 length = gs_FilePosition(&dst) - 12;
	gs_Seek(&dst, 8);
	gs_WriteUInt32_Native(&dst, length);
	gs_CloseFile(&dst);

}