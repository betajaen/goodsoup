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

#include "room.h"

#define T gs_Room
#include "shared/list.h"

gs_Room_List sRooms = { NULL, NULL };

GS_PRIVATE void gs_Room_Ctor(gs_Room* room) {
	room->background = NULL;
	room->loadFlags = 0;
	room->next = NULL;
	room->prev = NULL;
	room->num = 0;
	room->palette = NULL;
	
	gs_Room_List_PushBack(&sRooms, room);
}

GS_PRIVATE void gs_Room_Dtor(gs_Room* room) {
	/* TODO: Unload Loaded Data */

	gs_Room_List_Remove(&sRooms, room);
}



GS_EXPORT gs_Room* gs_NewRoom(gs_bool addToList) {
	gs_Room* room = gs_new(gs_Room, GS_COMMENT_FILE_LINE_NOTE("ROOM"));
	gs_Room_Ctor(room, addToList);
	return room;
}

GS_EXPORT void gs_DeleteRoom(gs_Room* room) {
	gs_Room_Dtor(room);
	gs_delete(room);
}
