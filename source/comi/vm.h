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

#ifndef COMI_VM_H
#define COMI_VM_H

#include "common/types.h"
#include "common/buffer.h"
#include "common/array.h"
#include "vm_stack.h"
#include "vm_array.h"
#include "constants.h"

using namespace common;

namespace comi
{
	class VirtualMachine;
	class Script;

	extern VirtualMachine* VM;

	enum
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
		VAR_SYNC = 134
	};

	enum ScriptContextState
	{
		SCS_Dead = 0,
		SCS_Paused = 1,
		SCS_Running = 2,
		SCS_Frozen = 0x80
	};

	enum ArrayKind
	{
		AK_Bit = 1,
		AK_Nibble = 2,
		AK_Byte = 3,
		AK_String = 4,
		AK_Int = 5,
		AK_DWord = 6
	};

	struct ScriptContext
	{
		void reset();

		inline void markDead() {
			_scriptNum = 0;
			_scriptWhere = OW_NotFound;
			_state = SCS_Dead;
		}

		inline bool isFrozen() const {
			return _freezeCount > 0;
		}

		inline bool isDead() const {
			return _state == 0;
		}

		inline void freeze() {
			_freezeCount++;
			if (_freezeCount) {
				_state |= SCS_Frozen;
			}
		}

		inline void unfreeze() {
			if (_freezeCount) {
				_freezeCount--;
				if (_freezeCount == 0) {
					_state &= ~SCS_Frozen;
				}
			}
		}

		inline void unfreezeAll() {
			_freezeCount = 0;
			_state &= ~SCS_Frozen;
		}

		uint16 _scriptNum;
		uint32 _lastPC;
		int32  _delay;
		uint16 _delayFrameCount;
		uint8  _scriptWhere;
		uint8  _state;
		uint8  _freezeCount;
		uint8  _bFreezeResistant;
		uint8  _bRecursive;
		uint8  _bIsExecuted;
		uint8  _cutsceneOverride;
		int32  _locals[NUM_INT_LOCALS];
	};

	struct ScriptStackItem {
		void reset();

		uint16 _scriptNum;
		uint8  _scriptWhere;
		uint8  _contextNum;
	};

	struct ArrayHeader {
		uint16 dim1;
		uint16 dim2;
		uint8  kind;
		uint8  data[1];

		inline void WriteByte(uint16 offset, byte value) {
			data[offset] = value;
		}
		
		inline void WriteUInt16_Native(uint16 offset, uint16 value) {
#if GS_BIG
			data[offset] = value >> 8;
			data[offset+1] = value & 0xFF;
#else
			data[offset] = value & 0xFF;
			data[offset+1] = value >> 8;
#endif
		}

	};

	class VirtualMachine
	{
	private:

		struct PcState
		{
			uint16 pc, pcAfter, scriptNum;
			uint8  opcode, context, contextAfter;
		};

		Buffer<byte>					_nullScript;
		Buffer<int32>					_intGlobals;
		Buffer<byte>					_boolGlobals;
		ScriptContext					_context[MAX_SCRIPT_CONTEXTS];
		ScriptStackItem					_contextStack[NUM_STACK_SCRIPTS];
		uint16							_contextStackSize;
		uint16							_currentContext;
		uint32							_pc, _pcAfter, _pcOpcode;
		Buffer<byte>*					_script;
		byte							_opcode;
		Array<char>						_messageTemp;
		RingLog<PcState>				_lastPcStates;
		PcState							_pcState;
		bool							_pushPcState;
		VmStack<256>					_stack;


		bool _findFreeContext(uint8& num);
		void _updateScriptData(ScriptContext& context);
		void _placeContextOnStackAndRun(uint8 newContextNum);
		void _step();
		void _stopScript(uint16 scriptNum);
		void _stopObjectScript(uint16 scriptNum);
		void _stopObjectCode();
		void _delay(uint32 seconds);
		void _break();

		byte _readByte();
		int32  _readWord();
		uint32  _readUnsignedWord();
		void _readStringLength(uint16& from, uint16& length);
		void _decodeParseString(uint8 m, uint8 n);

		void _dumpState();
		void _forceQuit();

		const char* _getOpcodeName(uint8 opcode) const;

	public:

		VirtualMachine();
		~VirtualMachine();

		void   reset();
		int32  readVar(uint32 var);
		void   writeVar(uint32 var, int32 value);
		VmArray* newArray(uint32 num, uint8 kind, uint16 y, uint16 x);
		void deleteArray(uint32 num);


		void runCurrentScript();
		void runScript(uint16 scriptNum, bool freezeResistant, bool recursive, int32* data = NULL, uint8 dataCount = 0);
		void runObjectScript(uint16 objectNum, uint16 entryPc, bool freezeResistant, bool recursive, int32* data = NULL, uint8 dataCount = 0);
		
		void abort() {
			_dumpState();
			_forceQuit();
		}

	};
}

#endif