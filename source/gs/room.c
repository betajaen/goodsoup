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

#define GS_FILE "room"

#include "shared/forward.h"
#include "shared/error.h"
#include "shared/game.h"
#include "shared/memory.h"
#include "shared/tag.h"
#include "shared/file.h"
#include "shared/string.h"


#include "room.h"
#include "graphics/image.h"
#include "graphics/palette.h"

#define T gs_Room
#include "shared/list.h"

gs_Room_List sRooms = { NULL, NULL };

GS_PRIVATE void gs_Room_Ctor(gs_Room* room) {
	room->background = NULL;
	room->loadFlags = 0;
	room->next = NULL;
	room->prev = NULL;
	room->num = 0;
	room->palettes = NULL;
	room->data.numPalettes = 0;
	room->data.flags = 0;
	room->data.width = 0;
	room->data.height = 0;
	room->data.layers = 0;

	gs_Room_List_PushBack(&sRooms, room);
}

GS_PRIVATE void gs_Room_Dtor(gs_Room* room) {
	/* TODO: Unload Loaded Data */

	gs_Room_List_Remove(&sRooms, room);
}



GS_EXPORT gs_Room* gs_NewRoom() {
	gs_Room* room = gs_New(gs_Room, GS_COMMENT_FILE_LINE_NOTE("ROOM"));
	gs_Room_Ctor(room);
	return room;
}

GS_EXPORT void gs_DeleteRoom(gs_Room* room) {
	gs_Room_Dtor(room);
	gs_Delete(room);
}

GS_IMPORT gs_Room* gs_GetRoom(uint16 roomNum) {
	gs_Room* room = sRooms.head;
	while (room) {
		if (room->num == roomNum) {
			return room;
		}

		room = room->next;
	}
}

/**
 */
GS_EXPORT void gs_LoadRoom(gs_Room* room, struct gs_File* file, gs_TagPair* tag) {
	/* TODO */
}

GS_PRIVATE void saveRoomData(gs_File* dst, gs_Room* room) {

	gs_SaveOpenKnown(dst, 
		GS_TAG_GSD_INFO,
		GS_FIELD_SIZEOF(gs_Room, num) +
		GS_FIELD_SIZEOF(gs_RoomData, width) +
		GS_FIELD_SIZEOF(gs_RoomData, height) +
		GS_FIELD_SIZEOF(gs_RoomData, flags) +
		GS_FIELD_SIZEOF(gs_RoomData, layers)
	);

	gs_SaveValue(dst, room->num);
	gs_SaveValue(dst, room->data.width);
	gs_SaveValue(dst, room->data.height);
	gs_SaveValue(dst, room->data.flags);;
	gs_SaveValue(dst, room->data.layers);	
}

/**
 */
GS_EXPORT void gs_SaveRoom(gs_Room* room, struct gs_File* dst) {
	gs_TagPair roomTag;

	gs_SaveOpen(dst, &roomTag, GS_TAG_GSC_ROOM);

	saveRoomData(dst, room);

	if (room->background) {
		gs_TagPair backgroundTag;
		gs_SaveOpen(dst, &backgroundTag, GS_TAG_GSC_ROOM_BACKGROUND);
		gs_SaveImage(dst, room->background);
		gs_SaveClose(dst, &backgroundTag);
	}

	gs_SaveClose(dst, &roomTag);
}

/**
 */
GS_EXPORT gs_Room* gs_LoadRoomFile(uint32 roomNum) {
	/* TODO */
}

/**
 */
GS_EXPORT gs_bool gs_SaveRoomFile(gs_Room* room) {
	char path[sizeof(GS_PATH_GS_ROOM_FMT) + 4];
	gs_File dst;

	gs_format(path, sizeof(path), GS_PATH_GS_ROOM_FMT, room->num);
	if (gs_OpenFileWrite(&dst, path, GS_COMMENT_FILE_LINE) == FALSE) {
		return FALSE;
	}
	
	gs_SaveBinaryFileHeader(&dst);
	gs_SaveRoom(room, &dst);

	gs_CloseFile(&dst);

	return TRUE;
}
