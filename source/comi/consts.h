/*
 * This program is free software, you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY, without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program, if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef COMI_VARS_H
#define COMI_VARS_H

#include "../goodsoup.h"

namespace comi {

	enum
	{
		NUM_ACTORS = 80,
		OF_OWNER_ROOM = 0xFF,
		NUM_SCRIPT_SLOT = 80,

		// Hardcoded MAXS
		NUM_VARIABLES = 1500,
		NUM_BITVARIABLES = 2048,
		NUM_SCRIPTS = 458,
		NUM_SOUNDS = 789,
		NUM_CHARSETS = 1,
		NUM_COSTUMES = 446,
		NUM_ROOMS = 95,
		NUM_GLOBAL_OBJECTS = 1401,
		NUM_LOCAL_OBJECTS = 200,
		NUM_NEW_NAMES = 100,
		NUM_FL_OBJECT = 128,
		NUM_INVENTORY = 80,
		NUM_ARRAY = 200,
		NUM_VERBS = 50,
		NUM_GLOBAL_SCRIPTS = 200,
		NUM_SHADOW_PALETTE = 8
	};

	enum {
		ssDead = 0,
		ssPaused = 1,
		ssRunning = 2
	};

	enum Var
	{
		VAR_ROOM_WIDTH = 1,
		VAR_ROOM_HEIGHT = 2,

		VAR_MOUSE_X = 3,
		VAR_MOUSE_Y = 4,
		VAR_VIRT_MOUSE_X = 5,
		VAR_VIRT_MOUSE_Y = 6,

		VAR_CURSORSTATE = 7,
		VAR_USERPUT = 8,

		VAR_CAMERA_POS_X = 9,
		VAR_CAMERA_POS_Y = 10,
		VAR_CAMERA_DEST_X = 11,
		VAR_CAMERA_DEST_Y = 12,
		VAR_CAMERA_FOLLOWED_ACTOR = 13,

		VAR_TALK_ACTOR = 14,
		VAR_HAVE_MSG = 15,

		VAR_LEFTBTN_DOWN = 16,
		VAR_RIGHTBTN_DOWN = 17,
		VAR_LEFTBTN_HOLD = 18,
		VAR_RIGHTBTN_HOLD = 19,

		VAR_TIMEDATE_YEAR = 24,
		VAR_TIMEDATE_MONTH = 25,
		VAR_TIMEDATE_DAY = 26,
		VAR_TIMEDATE_HOUR = 27,
		VAR_TIMEDATE_MINUTE = 28,
		VAR_TIMEDATE_SECOND = 29,

		VAR_OVERRIDE = 30,
		VAR_ROOM = 31,
		VAR_NEW_ROOM = 32,
		VAR_WALKTO_OBJ = 33,
		VAR_TIMER = 34,

		VAR_VOICE_MODE = 39, // 0 is voice, 1 is voice+text, 2 is text only
		VAR_GAME_LOADED = 40,
		VAR_LANGUAGE = 41,

		VAR_CURRENTDISK = 42,
		VAR_MUSIC_BUNDLE_LOADED = 45,
		VAR_VOICE_BUNDLE_LOADED = 46,

		VAR_SCROLL_SCRIPT = 50,
		VAR_ENTRY_SCRIPT = 51,
		VAR_ENTRY_SCRIPT2 = 52,
		VAR_EXIT_SCRIPT = 53,
		VAR_EXIT_SCRIPT2 = 54,
		VAR_VERB_SCRIPT = 55,
		VAR_SENTENCE_SCRIPT = 56,
		VAR_INVENTORY_SCRIPT = 57,
		VAR_CUTSCENE_START_SCRIPT = 58,
		VAR_CUTSCENE_END_SCRIPT = 59,

		VAR_CUTSCENEEXIT_KEY = 62,

		VAR_PAUSE_KEY = 64,
		VAR_MAINMENU_KEY = 65,
		VAR_VERSION_KEY = 66,
		VAR_TALKSTOP_KEY = 67,

		VAR_CUSTOMSCALETABLE = 111,

		VAR_TIMER_NEXT = 112,
		VAR_TMR_1 = 113,
		VAR_TMR_2 = 114,
		VAR_TMR_3 = 115,

		VAR_CAMERA_MIN_X = 116,
		VAR_CAMERA_MAX_X = 117,
		VAR_CAMERA_MIN_Y = 118,
		VAR_CAMERA_MAX_Y = 119,
		VAR_CAMERA_SPEED_X = 120,
		VAR_CAMERA_SPEED_Y = 121,
		VAR_CAMERA_ACCEL_X = 122,
		VAR_CAMERA_ACCEL_Y = 123,
		VAR_CAMERA_THRESHOLD_X = 124,
		VAR_CAMERA_THRESHOLD_Y = 125,

		VAR_EGO = 126,

		VAR_DEFAULT_TALK_DELAY = 128,
		VAR_CHARINC = 129,

		VAR_DEBUGMODE = 130,
		VAR_KEYPRESS = 132,
		VAR_BLAST_ABOVE_TEXT = 133,
		VAR_SYNC = 134,
	};
}

#endif