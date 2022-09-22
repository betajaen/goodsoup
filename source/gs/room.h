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

#ifndef GS_ROOM_H
#define GS_ROOM_H

#include "shared/forward.h"
#include "shared/game.h"

typedef struct gs_Palette gs_Palette;
typedef struct gs_Image gs_Image;

typedef enum gs_RoomLoadFlags {
	RLF_Data = 1,
	RLF_Palette = 2,
	RLF_Background = 4,
	RLF_LocalObjects = 8,
	RLF_LocalScripts = 16,
	RLF_WalkBoxes = 32
} gs_RoomLoadFlags;

typedef struct gs_RoomData {
	uint16 width, height;
	uint8  layers, flags;
	uint8  numPalettes;
} gs_RoomData;

typedef struct gs_Room {
	struct gs_Room *next, *prev;
	uint16 num;
	uint16 loadFlags;
	gs_RoomData data;
	gs_Palette* palettes;
	gs_Image* background;
} gs_Room;


/**
 *	Create a Room onto the Heap  
 */
GS_IMPORT gs_Room* gs_NewRoom();

/**
 *	Delete Room onto the Heap  
 */
GS_IMPORT void gs_DeleteRoom(gs_Room* room);


/**
 */
GS_IMPORT void gs_LoadRoom(gs_Room* room, struct gs_File* file, gs_TagPair* tag);

/**
 */
GS_IMPORT void gs_SaveRoom(gs_Room* room, struct gs_File* file);

/**
 */
GS_IMPORT gs_Room* gs_LoadRoomFile(uint32 roomNum);

/**
 */
GS_IMPORT gs_Room* gs_GetRoom(uint16 roomNum);

/**
 */
GS_IMPORT void gs_SaveRoomFile(gs_Room* room);


#endif
