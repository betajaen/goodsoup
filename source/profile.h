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

#include "types.h"

#define GS_GAME_NAME "COMI"
#define GS_GAME_VERSION 8
#define GS_SCREEN_WIDTH 640
#define GS_SCREEN_HEIGHT 480
#define GS_SCREEN_DEPTH 8
#define GS_BITMAP_PITCH 640
#define GS_BITMAP_ROWS 480
#define GS_BITMAP_SIZE (640 * 480)
#define GS_INDEX_FILENAME "COMI.LA0"
#define GS_DISK_FILENAME_PATTERN "COMI.LA%ld"
#define GS_MAXIMUM_FRAMES_PER_SECOND (25)
#define GS_FRAME_DELAY_USEC (1000000 / GS_MAXIMUM_FRAMES_PER_SECOND)
#define GS_AUDIO_FREQUENCY_HZ 22050
#define GS_AUDIO_SAMPLES_PER_SECOND 8192
#define GS_AUDIO_SAMPLES_SIZE 4096				//
#define GS_AUDIO_SAMPLE_BUFFER_SIZE_BYTES 16384	// 4096 Samples * 2 Channels * 2 Bytes Per Sample

namespace gs
{
	enum GameConstants
	{
		MAX_SCRIPT_CONTEXTS = 80,
		MAX_CONTEXT_STACK_SIZE = 15,

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
		NUM_ACTORS = 80,
		OBJECT_MIN = 100,
		MAX_FONTS = 5,
		MAX_AUDIO_MIXERS = 4,
		MAX_DIALOGUE_LENGTH = 384,
		MAX_VIDEOS = 15
	};

	const char* const RESOURCE_PATH = "RESOURCES/";

	extern const char* RESOURCE_VIDEO[MAX_VIDEOS];

}

#endif