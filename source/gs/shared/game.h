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

#ifndef GS_GAME_H
#define GS_GAME_H

#define GS_WIDTH 640
#define GS_HEIGHT 480
#define GS_DEPTH 8
#define GS_GAME_NAME "COMI"
#define GS_GAME_TITLE "The Curse of Monkey Island"

// MAXS Constants
#define GS_NUM_INT_GLOBALS 1500
#define GS_NUM_BOOL_GLOBALS 2048
#define GS_NUM_LOCAL_INTS 26
#define GS_NUM_GLOBAL_SCRIPTS 458
#define GS_NUM_SOUNDS 789
#define GS_NUM_CHARSETS 1
#define GS_NUM_COSTUMES 446
#define GS_NUM_ROOMS 95
#define GS_NUM_GLOBAL_OBJECTS 1401
#define GS_NUM_LOCAL_OBJECTS 200
#define GS_NUM_NEWNAMES 100
#define GS_NUM_FLOBJECTS 128
#define GS_NUM_INVENTORY 80
#define GS_NUM_ARRAY 200
#define GS_NUM_VERBS 50
#define GS_NUM_AARY 142
#define GS_NUM_DISKS 2
#define GS_NUM_ACTORS 80
#define GS_OBJECT_MIN 100
#define GS_MAX_FONTS 5
#define GS_MAX_AUDIO_MIXERS 4,
#define GS_MAX_DIALOGUE_LENGTH 384
#define GS_MAX_VIDEOS 15
#define GS_MAX_COROUTINES 80
#define GS_COROUTINE_STACK_SIZE 15
	
// Game Paths
#define GS_PATH_INDEX GS_PATH_DIR "COMI.LA0"
#define GS_PATH_DISKN GS_PATH_DIR "COMI.LA%ld"

// GS Paths
#define GS_PATH_OBJECT_NAME GS_PATH_DIR  "onames.gs"
#define GS_PATH_OBJECT_PROTO GS_PATH_DIR "oproto.gs"

// CLI Params
#define GS_PARAM_CONVERT_SCRIPTS 700

#endif