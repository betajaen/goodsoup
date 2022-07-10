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

#ifndef GS_VM_H
#define GS_VM_H

#include "types.h"
#include "buffer.h"
#include "array.h"
#include "vm_stack.h"
#include "vm_array.h"
#include "profile.h"
#include "script.h"

namespace gs
{
#define MAX_CUTSCENES_STACK 5

	class VirtualMachine;

	extern VirtualMachine* VM;

	enum ScriptContextState
	{
		SCS_Dead = 0,
		SCS_Paused = 1,
		SCS_Running = 2,
		SCS_Frozen = 0x80
	};

	
	enum ObjectWhere
	{
		OW_Unknown = 0,
		OW_NotFound = 1,
		OW_Inventory = 2,
		OW_Room = 3,
		OW_Global = 4,
		OW_Local = 5,
		OW_FLObject = 6,
		OW_ObjectVerb = 7
	};
	
	const char* ObjectWhereToString(uint8 where);
	const char* ObjectStateToString(uint8 state);
    const char* OpcodeToString(uint8 opcode);

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
		uint8  _verb;
        uint8  _indexNum;
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


	struct CutsceneScriptStackItem {
		int32 _data;
		uint32 _pc;
		uint8  _context;
	};

	struct CutsceneScriptState {

		CutsceneScriptStackItem _items[MAX_CUTSCENES_STACK];
		uint8 _stackSize;
		uint32 _index;
		uint8 _contextIndex;

		CutsceneScriptState();
	};

	class VirtualMachine
	{
	private:

		struct PcState
		{
			uint16 pc, pcAfter, scriptNum;
			uint8  opcode, context, contextAfter;
		};

		OpcodeSpan						_nullScript;
		Buffer<int32>					_intGlobals;
		Buffer<byte>					_boolGlobals;
		ScriptContext					_context[MAX_SCRIPT_CONTEXTS];
		ScriptStackItem					_contextStack[NUM_STACK_SCRIPTS];
		CutsceneScriptState				_cutscenes;
		uint16							_contextStackSize;
		uint32							_pc, _pcAfter, _pcOpcode;
		ScriptDataReference			_scriptReference;
		OpcodeSpan						_script;
		byte							_opcode;
		Array<char>						_messageTemp;
		RingLog<PcState>				_lastPcStates;
		PcState							_pcState;
		bool							_pushPcState;
		VmStack<256>					_stack;
		Array<byte, uint16>				_arrayTemp;


		bool _findFreeContext(uint8& num);
		bool _updateScriptData(ScriptContext& context);
		void _pushAndRunScript(uint8 newContextNum);
		void _step();
		void _stopScript(uint16 scriptNum);
		void _stopObjectScript(uint16 scriptNum);
		void _stopObjectCode();
		void _delay(uint32 seconds);
		void _break();

		byte _readByte();
		int32  _readWord();
		uint32  _readUnsignedWord();
		int32  _readSignedWord();
		void _readStringLength(uint16& from, uint16& length);
		void _decodeParseString(uint8 m, uint8 n);

		void _dumpState();
		void _forceQuit();

		void _runExitScript();
		void _runEnterScript();
		void _unloadAllRoomScripts();

		const char* _getOpcodeName(uint8 opcode) const;

		void _beginCutscene(uint16 stackListCount);
		void _endCutscene();
		void _beginOverride();
		void _endOverride();

		void _readBytesForArray();
	public:

		VirtualMachine();
		~VirtualMachine();

		void   reset();


		void runCurrentScript();
		void runScript(uint16 scriptNum, bool freezeResistant, bool recursive, int32* data = NULL, uint8 dataCount = 0);
		void runObjectScript(uint16 objectNum, uint8 verb, bool freezeResistant, bool recursive, int32* data = NULL, uint8 dataCount = 0);
		void runRoomScript(uint16 scriptNum);
		void runAllScripts();
		void runInputScript(uint16 scriptNum, int32 clickArea, int32 code, int32 mode);

		bool isScriptRunning(uint16 scriptNum);
		bool isRoomScriptRunning(uint16 scriptNum);

		void freezeScripts(uint16 flag);
		void freezeAll();
		void unfreezeAll();

		void abort() {
			_dumpState();
			_forceQuit();
		}

		void dumpStack();

		void processScriptDelays(uint32 delta);


		void _actorSay(uint16 actorNum, uint16 length, uint16 offset);
	};
}

#endif