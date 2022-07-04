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

#ifndef GS_PROFILE_H
#define GS_PROFILE_H

#define GS_GAME_NAME "COMI"
#define GS_GAME_VERSION 8
#define GS_SCREEN_WIDTH 640
#define GS_SCREEN_HEIGHT 480
#define GS_SCREEN_DEPTH 8
#define GS_BITMAP_PITCH 640
#define GS_BITMAP_ROWS 480
#define GS_INDEX_FILENAME "COMI.LA0"
#define GS_DISK_FILENAME_PATTERN "COMI.LA%ld"
#define GS_FRAME_DELAY_MSEC 33333

namespace gs
{
	enum GameConstants
	{
		MAX_SCRIPT_CONTEXTS = 80,
		NUM_STACK_SCRIPTS = 15,

		// MAXS Constants
		NUM_INT_GLOBALS = 1500,
		NUM_BOOL_GLOBALS = 2048,
		NUM_INT_LOCALS = 26,
		NUM_SCRIPTS = 458,
		NUM_SOUNDS = 789,
		NUM_CHARSETS = 1,
		NUM_COSTUMES = 446,
		NUM_ROOMS = 95,
		NUM_OBJECT_GLOBALS = 1401,
		NUM_OBJECT_LOCALS = 200,
		NUM_NEWNAMES = 100,
		NUM_FLOBJECTS = 128,
		NUM_INVENTORY = 80,
		NUM_ARRAY = 200,
		NUM_VERBS = 50,
		NUM_GLOBAL_SCRIPTS = 2000,
		NUM_AARY = 142,
		NUM_DISKS = 2,
		NUM_ACTORS = 80
	};

}

#endif