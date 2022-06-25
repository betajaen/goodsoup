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

#ifndef GS_VM_VARS_H
#define GS_VM_VARS_H

#include "types.h"
#include "constants.h"
#include "debug.h"

namespace gs
{
	
	#pragma pack(push, 4)
	struct VmIntVars {

		int32 get(uint32 name) {
			if (name >= NUM_INT_GLOBALS) {
				return 0;
			}
			return (&unnamed_00)[name];
		}

		void set(uint32 name, int32 value) {
			if (name >= NUM_INT_GLOBALS) {
				return;
			}
			(&unnamed_00)[name] = value;
		}

		int32 unnamed_00;
		int32 roomWidth;
		int32 roomHeight;
		int32 mouseX;
		int32 mouseY;
		int32 virtMouseX;
		int32 virtMouseY;
		int32 cursorstate;
		int32 userput;
		int32 cameraPosX;
		int32 cameraPosY;
		int32 cameraDestX;
		int32 cameraDestY;
		int32 cameraFollowedActor;
		int32 talkActor;
		int32 haveMsg;
		int32 leftbtnDown;
		int32 rightbtnDown;
		int32 leftbtnHold;
		int32 rightbtnHold;
		int32 unnamed_14;
		int32 unnamed_15;
		int32 unnamed_16;
		int32 unnamed_17;
		int32 timedateYear;
		int32 timedateMonth;
		int32 timedateDay;
		int32 timedateHour;
		int32 timedateMinute;
		int32 timedateSecond;
		int32 override_;
		int32 room;
		int32 newRoom;
		int32 walktoObj;
		int32 timer;
		int32 unnamed_23;
		int32 unnamed_24;
		int32 unnamed_25;
		int32 unnamed_26;
		int32 voiceMode;
		int32 gameLoaded;
		int32 language;
		int32 currentdisk;
		int32 unnamed_2b;
		int32 unnamed_2c;
		int32 musicBundleLoaded;
		int32 voiceBundleLoaded;
		int32 unnamed_2f;
		int32 unnamed_30;
		int32 unnamed_31;
		int32 scrollScript;
		int32 entryScript;
		int32 entryScript2;
		int32 exitScript;
		int32 exitScript2;
		int32 verbScript;
		int32 sentenceScript;
		int32 inventoryScript;
		int32 cutsceneStartScript;
		int32 cutsceneEndScript;
		int32 unnamed_3c;
		int32 unnamed_3d;
		int32 cutsceneexitKey;
		int32 unnamed_3f;
		int32 pauseKey;
		int32 mainmenuKey;
		int32 versionKey;
		int32 talkstopKey;
		int32 unnamed_44;
		int32 unnamed_45;
		int32 unnamed_46;
		int32 unnamed_47;
		int32 unnamed_48;
		int32 unnamed_49;
		int32 unnamed_4a;
		int32 unnamed_4b;
		int32 unnamed_4c;
		int32 unnamed_4d;
		int32 unnamed_4e;
		int32 unnamed_4f;
		int32 unnamed_50;
		int32 unnamed_51;
		int32 unnamed_52;
		int32 unnamed_53;
		int32 unnamed_54;
		int32 unnamed_55;
		int32 unnamed_56;
		int32 unnamed_57;
		int32 unnamed_58;
		int32 unnamed_59;
		int32 unnamed_5a;
		int32 unnamed_5b;
		int32 unnamed_5c;
		int32 unnamed_5d;
		int32 unnamed_5e;
		int32 unnamed_5f;
		int32 unnamed_60;
		int32 unnamed_61;
		int32 unnamed_62;
		int32 unnamed_63;
		int32 unnamed_64;
		int32 unnamed_65;
		int32 unnamed_66;
		int32 unnamed_67;
		int32 unnamed_68;
		int32 unnamed_69;
		int32 unnamed_6a;
		int32 unnamed_6b;
		int32 unnamed_6c;
		int32 unnamed_6d;
		int32 unnamed_6e;
		int32 customscaletable;
		int32 timerNext;
		int32 tmr1;
		int32 tmr2;
		int32 tmr3;
		int32 cameraMinX;
		int32 cameraMaxX;
		int32 cameraMinY;
		int32 cameraMaxY;
		int32 cameraSpeedX;
		int32 cameraSpeedY;
		int32 cameraAccelX;
		int32 cameraAccelY;
		int32 cameraThresholdX;
		int32 cameraThresholdY;
		int32 ego;
		int32 unnamed_7f;
		int32 defaultTalkDelay;
		int32 charinc;
		int32 debugmode;
		int32 unnamed_83;
		int32 keypress;
		int32 blastAboveText;
		int32 sync;
		int32 others[1365];
	};
	#pragma pack(pop)

	typedef char __GS_ASSERT_VM_INT_VARS_SIZE_WRONG__[(!!(sizeof(VmIntVars) ==  (sizeof(int32) * NUM_INT_GLOBALS) )) * 2 - 1];

	extern VmIntVars* INTS;
	
	#pragma pack(push, 4)
	struct VmBoolVars {
		
		int32 get_unchecked(uint32 name) const {
			return (_bools[name >> 5] & (1 << (name & 31))) ? 1 : 0;
		}

		void set_unchecked(uint32 name, bool value) {
			if (value) {
				_bools[name >> 5] |= (1 << (name & 31));
			}
			else {
				_bools[name >> 5] &= ~(1 << (name & 31));
			}
		}

		uint32 _bools[NUM_BOOL_GLOBALS>>5];
	};
	#pragma pack(pop)
	
	extern VmBoolVars* BOOLS;

	#pragma pack(push, 4)
	struct VmLocalVars {
		
		void clear(uint8 context);

		void copyInto(uint8 context, int32* values, uint8 numValues);

		int32 get_unchecked(uint8 context, uint8 varName) const {
			return _locals[context][varName];
		}

		void set_unchecked(uint8 context, uint8 varName, int32 value) {
			_locals[context][varName] = value;
		}

		int32 _locals[MAX_SCRIPT_CONTEXTS][NUM_INT_LOCALS];
	};
	#pragma pack(pop)

	extern VmLocalVars* LOCALS;

	void resetVars();

	void setVar(uint32 varName, int32 value);
	int32 getVar(uint32 varName);

}

#endif
