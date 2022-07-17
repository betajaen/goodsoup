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

#include "../types.h"
#include "../buffer.h"
#include "../array.h"
#include "../profile.h"
#include "../script.h"
#include "stack.h"
#include "array.h"
#include "context.h"

namespace gs
{
#define MAX_CUTSCENES_STACK 5

	class VirtualMachine;

	extern VirtualMachine* VM;

	const char* ObjectWhereToString(uint8 where);
	const char* ObjectStateToString(uint8 state);

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

		OpcodeSpan						_nullScript;
		VmContextAllocator			_contextAllocator;
		Stack<uint8, uint8, MAX_CONTEXT_STACK_SIZE>				_contextStackNewNew;
		uint8							_contextStackNew[MAX_CONTEXT_STACK_SIZE];
		uint8                           _contextStackNewSize;

		CutsceneScriptState				_cutscenes;
		byte							_opcode;

		bool 	_bIsInterrupting;
		uint8	_bInterruptContextIdx;
		uint8   _bInterruptContextAction;

		void _pushAndRunScript(VmContext& context);
		void _stopObjectScript(uint16 scriptNum);
		void _runExitScript();
		void _runEnterScript();
		void _readBytesForArray();
		bool _isInterrupting();

	public:

		VirtualMachine();
		~VirtualMachine();

		Array<char>						_messageTemp;
		Array<byte, uint16>				_arrayTemp;

		void   reset();

		void runScript(uint16 scriptNum, bool freezeResistant, bool recursive, int32* data = NULL, uint8 dataCount = 0);
		void runObjectScript(uint16 objectNum, uint8 verb, bool freezeResistant, bool recursive, int32* data = NULL, uint8 dataCount = 0);
		void runRoomScript(uint16 scriptNum);
		void runAllScripts();
		void runInputScript(uint16 scriptNum, int32 clickArea, int32 code, int32 mode);

		void unloadAllRoomScripts();

		bool isScriptRunning(uint16 scriptNum);
		bool isRoomScriptRunning(uint16 scriptNum);

		void freezeScripts(uint16 flag);
		void freezeAll();
		void unfreezeAll();

		void abort() {
			dumpStack();
			_forceQuit();
		}

		void dumpStack();

		void processScriptDelays(uint32 delta);


		void _actorSay(uint16 actorNum, uint16 length, uint16 offset);

		void _break();

		void _beginCutscene(VmContext& context, uint16 stackListCount);

		void _endCutscene(VmContext& context);

		void _beginOverride(VmContext& context);

		void _endOverride(VmContext& context);

		void _stopScript(uint16 scriptNum);

		void _forceQuit();

		bool isInterrupting() const {
			return _bIsInterrupting;
		}

		void interrupt();

	};
}

#endif