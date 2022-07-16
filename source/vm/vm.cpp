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

#define GS_FILE_NAME "vm"

#include "vm.h"
#include "opcodes.h"
#include "vars.h"
#include "debugger.h"
#include "../globals.h"
#include "../script.h"
#include "../index.h"
#include "../debug.h"
#include "../profile.h"
#include "../room.h"
#include "../endian.h"
#include "../object.h"

#define DEBUG_CONTEXT_STACK 0

namespace gs
{
	static const uint8 NO_CONTEXT = 0xFF;

	const char* ObjectWhereToString(uint8 where) {
		switch (where) {
			default:
				return "Unknown";
			case OW_NotFound:
				return "NotFound";
			case OW_Inventory:
				return "Inventory";
			case OW_Room:
				return "Room";
			case OW_Global:
				return "Global";
			case OW_Local:
				return "Local";
			case OW_FLObject:
				return "FLObject";
			case OW_ObjectVerb:
				return "ObjectVerb";
		}
	}
	const char* ObjectStateToString(uint8 state) {
		switch(state) {
			default:
				return "Unknown";
			case 0:
				return "Dead";
			case 1:
				return "Paused";
			case 2:
				return "Running";
			case 0x80:
				return "Frozen+Dead";
			case 0x81:
				return "Frozen+Paused";
			case 0x82:
				return "Frozen+Running";
		}
	}

	VirtualMachine* VM = NULL;
	uint8 CURRENT_CONTEXT = NO_CONTEXT;

	static const byte kNullScript[4] = {
		OP_systemOps, SystemOps_AbortQuitStop, 0xFF, 0xFF
	};
	
	VirtualMachine::VirtualMachine() :
		_contextStackNewSize(0)
	{
		_nullScript = ReadSpan<byte, uint16>(&kNullScript[0], 4);
		_arrayTemp.reserve(256);
		
		_contextAllocator.clear();

		for (uint8 i=0;i < MAX_CONTEXT_STACK_SIZE;i++) {
			_contextStackNew[i] = NO_CONTEXT;
		}


	}

	VirtualMachine::~VirtualMachine() {
	}

	void VirtualMachine::reset() {
		int32 i;

		if (_messageTemp.getCapacity() == 0) {
			_messageTemp.reserve(384);
		}
		else {
			_messageTemp.clear();
		}
		
		STACK.reset();

		for (i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			_contextAllocator.get_unchecked(i)._reset();
		}

		for (i=0;i < MAX_CONTEXT_STACK_SIZE;i++) {
			_contextStackNew[i] = NO_CONTEXT;
		}

		INTS->currentdisk = 1;

		_cutscenes._index = 0;
		_cutscenes._contextIndex = 0;
		_cutscenes._stackSize = 0;
	}
	
	void VirtualMachine::runAllScripts() {

		CURRENT_CONTEXT = NO_CONTEXT;

		for (uint8 i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			ScriptContext& context = _contextAllocator.get_unchecked(i);
			context._bIsExecuted = false;
		}

		for (uint8 i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			ScriptContext& context = _contextAllocator.get_unchecked(i);
			if (context._state == SCS_Running && context._bIsExecuted == false) {
				CURRENT_CONTEXT = i;
				context.run();

				if (QUIT_NOW)
					break;
			}
		}

		CURRENT_CONTEXT = NO_CONTEXT;
	}

	void VirtualMachine::runScript(uint16 scriptNum, bool freezeResistant, bool recursive, int32* data, uint8 dataCount)
	{

#if GS_CHECKED == 1
		if (scriptNum == 0) {
			warn(GS_THIS, "VM tried to run NULL script 0");
			return;
		}
#endif

		if (recursive == false) {
			_stopScript(scriptNum);
		}

		ScriptContext& context = _contextAllocator.acquire();

		if (QUIT_NOW)
			return;

		context._scriptNum = scriptNum;
		context._state = SCS_Running;
		context._bFreezeResistant = freezeResistant;
		context._bRecursive = recursive;
		context._scriptWhere = (scriptNum < NUM_SCRIPTS) ? OW_Global : OW_Local;

		if (context._getScriptData()) {
			context.copyIntoLocals(data, dataCount);
			_pushAndRunScript(context);
		}
	}


	void VirtualMachine::runObjectScript(uint16 objectNum, uint8 verb, bool freezeResistant, bool recursive, int32* data, uint8 dataCount) {

		// This can be normal. Observed in Script 51+0x7B
		if (objectNum == 0) {
			return;
		}

		// Check Object Exists; Room, Global or Inventory
		ObjectData* objectData = OBJECTS->findObject(objectNum);
		if (objectData == NULL) {
			error(GS_THIS, "Could not run a object script %ld on a unloaded object", (uint32) objectNum);
			abort_quit_stop();
			return;
		}

		// Check that there is data.
		if (objectData->_script.isNull()) {
			warn(GS_THIS, "Null script for Object %ld", objectNum);
			return;
		}

		if (recursive == false) {
			_stopObjectScript(objectNum);
		}

		ScriptContext& context = _contextAllocator.acquire();

		if (QUIT_NOW)
			return;

		context._scriptNum = objectNum;
		context._verb = verb;
		context._state = SCS_Running;
		context._bFreezeResistant = false;
		context._bRecursive = false;
		context._scriptWhere = OW_ObjectVerb;

		if (context._getScriptData()) {
			context.copyIntoLocals(data, dataCount);
			_pushAndRunScript(context);
		}
	}
	
	void VirtualMachine::runRoomScript(uint16 scriptNum) {

#if GS_CHECKED == 1
		if (scriptNum == 0) {
			error(GS_THIS, "Could not run a NULL room script %ld", (uint32) scriptNum);
			abort_quit_stop();
			return;
		}
#endif

		ScriptContext& context = _contextAllocator.acquire();

		if (QUIT_NOW)
			return;

		context._scriptNum = scriptNum;
		context._state = SCS_Running;
		context._bFreezeResistant = false;
		context._bRecursive = false;
		context._scriptWhere = OW_Room;
		
#if DEBUG_CONTEXT_STACK == 1
		debug(GS_THIS, "Attached Script %ld (Room) to Context %ld", (uint32) scriptNum, (uint32) contextNum);
#endif

		if (context._getScriptData()) {
			_pushAndRunScript(context);
		}
	}

	void VirtualMachine::runInputScript(uint16 scriptNum, int32 clickArea, int32 code, int32 mode) {

#if GS_CHECKED == 1
		if (scriptNum == 0) {
			error(GS_THIS, "Could not run a NULL room script %ld", (uint32) scriptNum);
			abort_quit_stop();
			return;
		}
#endif

		ScriptContext& context = _contextAllocator.acquire();

		if (QUIT_NOW)
			return;

		context._scriptNum = scriptNum;
		context._state = SCS_Running;
		context._bFreezeResistant = false;
		context._bRecursive = false;
		context._scriptWhere = OW_Room;


		if (context._getScriptData()) {
			context.setLocal_unchecked(0, clickArea);
			context.setLocal_unchecked(1, code);
			context.setLocal_unchecked(2, mode);

			_pushAndRunScript(context);
		}
	}

	void VirtualMachine::_stopScript(uint16 scriptNum) {

#if GS_CHECKED == 1
		if (scriptNum == 0)
			return;
#endif

		uint8 contextIndex = NO_CONTEXT;

		for (uint8 i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			ScriptContext& context = _contextAllocator.get_unchecked(i);

			if (context._scriptNum == scriptNum && 
				context._isDead() == false &&
				(
					context._scriptWhere == OW_Global ||
					context._scriptWhere == OW_Local
				)
			) {

				if (context._cutsceneOverride != 0) {
					error(GS_THIS, "Stopped Context %ld:%ld(%s) with an cutscene override", i, scriptNum, ObjectWhereToString(context._scriptWhere));
					abort_quit_stop();
					return;
				}

				context._reset();
				contextIndex = i;

				if (CURRENT_CONTEXT == i) {
					CURRENT_CONTEXT = NO_CONTEXT;
				}

				break;
			}
		}

		// Remove instance from stack
		if (contextIndex != NO_CONTEXT) {
			for(uint8 i=0;i < MAX_CONTEXT_STACK_SIZE;i++) {
				if (_contextStackNew[i] == contextIndex) {
					_contextStackNew[i] = NO_CONTEXT;
				}
			}
		}

	}
	
	void VirtualMachine::_stopObjectScript(uint16 scriptNum) {

#if GS_CHECKED == 1
		if (scriptNum == 0)
			return;
#endif

		uint8 contextIndex = NO_CONTEXT;

		for (uint8 i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			ScriptContext& context = _contextAllocator.get_unchecked(i);

			if (context._scriptNum == scriptNum && 
				context._isDead() == false &&
				(
					context._scriptWhere == OW_Room ||
					context._scriptWhere == OW_Inventory ||
					context._scriptWhere == OW_FLObject

				)
			) {

				if (context._cutsceneOverride != 0) {
					error(GS_THIS, "Stopped Context %ld:%ld(%s) with an cutscene override", i, scriptNum, ObjectWhereToString(context._scriptWhere));
					abort_quit_stop();
					return;
				}

				context._reset();
				contextIndex = i;

				if (CURRENT_CONTEXT == i) {
					CURRENT_CONTEXT = NO_CONTEXT;
				}
			}
		}

		// Remove instance from stack
		if (contextIndex != NO_CONTEXT) {
			for(uint8 i=0;i < MAX_CONTEXT_STACK_SIZE;i++) {
				if (_contextStackNew[i] == contextIndex) {
					_contextStackNew[i] = NO_CONTEXT;
				}
			}
		}

	}

	void VirtualMachine::freezeScripts(uint16 flags) {
		for (uint8 i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			ScriptContext& context = _contextAllocator.get_unchecked(i);

			if (CURRENT_CONTEXT != i && context._isDead() == false && (!context._bFreezeResistant  || flags >= 0x80)) {
				context._freeze();
			}
		}

		/* TODO: Sentence Scripts */

		if (_cutscenes._contextIndex != 0xFF) {
			bool hasCutSceneContext;
			ScriptContext& cutSceneContext = _contextAllocator.get(_cutscenes._contextIndex, hasCutSceneContext);

			if (hasCutSceneContext) {
				cutSceneContext._unfreezeAll();
			}

		}
	}

	void VirtualMachine::freezeAll() {
		for (uint8 i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			ScriptContext& context = _contextAllocator.get_unchecked(i);

			if (i == CURRENT_CONTEXT)
				continue;

			if (context._isDead())
				continue;

			if (context._bFreezeResistant)
				continue;

			context._freeze();
		}

		/* TODO: Sentence Scripts */

		if (_cutscenes._contextIndex != 0xFF) {
			bool hasCutSceneContext;
			ScriptContext& cutSceneContext = _contextAllocator.get(_cutscenes._contextIndex, hasCutSceneContext);

			if (hasCutSceneContext) {
				cutSceneContext._unfreezeAll();
			}
		}
	}

	void VirtualMachine::unfreezeAll() {
		for (uint8 i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			ScriptContext& context = _contextAllocator.get_unchecked(i);

			if (i == CURRENT_CONTEXT)
				continue;

			if (context._isDead())
				continue;

			if (context._bFreezeResistant)
				continue;

			context._unfreeze();
		}
	}

	bool VirtualMachine::isScriptRunning(uint16 scriptNum) {
		
		for (uint8 i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			ScriptContext& context = _contextAllocator.get_unchecked(i);

			if (context._scriptNum == scriptNum && 
				context._isDead() == false &&
				(
					context._scriptWhere == OW_Global ||
					context._scriptWhere == OW_Local

				)
			) {
				return true;
			}
		}

		return false;
	}

	bool VirtualMachine::isRoomScriptRunning(uint16 scriptNum) {
		
		for (uint8 i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			ScriptContext& context = _contextAllocator.get_unchecked(i);

			if (context._scriptNum == scriptNum && 
				context._isDead() == false &&
				(
					context._scriptWhere == OW_Room
				)
			) {
				return true;
			}
		}

		return false;
	}

	void VirtualMachine::_pushAndRunScript(ScriptContext &context) {

		_contextStackNewNew.push(context._indexNum);
		CURRENT_CONTEXT = context._indexNum;
		context.run();
		uint8 oldContextIdx;
		_contextStackNewNew.pop(oldContextIdx);

#if GS_CHECKED == 1
		if (oldContextIdx != context._indexNum) {
			warn(GS_THIS, "Incorrect context (%ld, %ld) was popped from stack", context._indexNum, oldContextIdx);
		}
#endif

		if (_contextStackNewNew.peek(CURRENT_CONTEXT) == false) {
			CURRENT_CONTEXT = NO_CONTEXT;
		}

	}

	void VirtualMachine::_beginCutscene(ScriptContext& context, uint16 stackListCount) {
		debug(GS_THIS, "Starting Cutscene");
		context._cutsceneOverride++;
		_cutscenes._stackSize++;

		CutsceneScriptStackItem& cutsceneItem = _cutscenes._items[_cutscenes._stackSize];
		cutsceneItem._data = stackListCount > 0 ? STACK.getListItem(0) : 0;
		cutsceneItem._context = 0;
		cutsceneItem._pc = 0;

		_cutscenes._contextIndex = context._indexNum;

		debug(GS_THIS, "Cutscene script Context=%ld Script=%ld",
			  _cutscenes._contextIndex, INTS->cutsceneStartScript);

		if (INTS->cutsceneStartScript != 0) {
			runScript(INTS->cutsceneStartScript, false, false, STACK.getList(), stackListCount);
		}

		_cutscenes._contextIndex = NO_CONTEXT;

	}

	void VirtualMachine::_endCutscene(ScriptContext& context) {

		if (context._cutsceneOverride > 0) {
			context._cutsceneOverride--;
		}

		CutsceneScriptStackItem& cutsceneItem = _cutscenes._items[_cutscenes._stackSize];

		int32 arg = cutsceneItem._data;

		INTS->override_ = 0;

		if (cutsceneItem._pc !=0 && cutsceneItem._context != 0) {
			context._cutsceneOverride--;
		}

		cutsceneItem._context = 0;
		cutsceneItem._pc = 0;
		cutsceneItem._data = 0;

		_cutscenes._stackSize--;

		if (INTS->cutsceneEndScript != 0) {
			runScript(INTS->cutsceneEndScript, false, false, &arg, 1);
		}

		debug(GS_THIS, "End Cutscene");

	}

	void VirtualMachine::_beginOverride(ScriptContext& context) {
		CutsceneScriptStackItem& cutsceneItem = _cutscenes._items[_cutscenes._stackSize];
		cutsceneItem._context = context._indexNum;
		cutsceneItem._pc = context._pc;

		context._pc += 1 + 4;
		// _readByte();
		// _readWord();

		INTS->override_ = 0;
	}

	void VirtualMachine::_endOverride(ScriptContext& context) {
		CutsceneScriptStackItem& cutsceneItem = _cutscenes._items[_cutscenes._stackSize];
		cutsceneItem._context = 0;
		cutsceneItem._pc = 0;

		INTS->override_ = 0;
	}

	void VirtualMachine::_break() {
		CURRENT_CONTEXT = NO_CONTEXT;
	}

	void VirtualMachine::processScriptDelays(uint32 delta) {
		/* TODO: Talk Delay */

		for (uint8 i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			ScriptContext &context = _contextAllocator.get_unchecked(i);

			if (context._state == SCS_Paused) {
				context._delay -= delta;

				if (context._delay <= 0) {
					debug(GS_THIS, "*** End Delay %ld", (uint32) context._scriptNum);
					context._state = SCS_Running;
					context._delay = 0;
				}

			}

		}
	}


	void VirtualMachine::dumpStack() {

		debug(GS_THIS, "---Begin VM Dump---");

		for(uint8 i=0;i < _contextStackNewSize;i++) {
			uint8 contextIdx = _contextStackNew[i];

			if (contextIdx == NO_CONTEXT)
				continue;

			bool hasContext;
			ScriptContext& context = _contextAllocator.get(contextIdx, hasContext);

			if (hasContext) {
				debug(GS_THIS, "[Context Stack, %ld] %ld => %ld", i, contextIdx, context._scriptNum, ObjectWhereToString(context._scriptWhere));
			}
			else {
				debug(GS_THIS, "[Context Stack, %ld %ld => ???");
			}
		}

		for(uint8 i=0;i < MAX_SCRIPT_CONTEXTS;i++) {
			ScriptContext& context = _contextAllocator.get_unchecked(i);

			if (context._scriptNum == 0)
				continue;

			debug(GS_THIS, "[Context Script, %d] %d %s %s %d %d", i, context._scriptNum, ObjectWhereToString(context._scriptWhere), ObjectStateToString(context._state), context._delay, context._delayFrameCount);
		}

		debug(GS_THIS, "[CutScenes] %d %d", _cutscenes._contextIndex, _cutscenes._index);

		for(uint8 i=0;i < _cutscenes._stackSize;i++) {
			CutsceneScriptStackItem& cutscene =  _cutscenes._items[i];

			debug(GS_THIS, "[CutScene, %d] Context=%ld Pc=%ld", cutscene._context, cutscene._pc);
		}

		OBJECTS->dumpObjects();
		debug(GS_THIS, "---End VM Dump---");

	}

	void VirtualMachine::_forceQuit() {
		QUIT_NOW = true;
		CURRENT_CONTEXT = NO_CONTEXT;
	}

	void VirtualMachine::unloadAllRoomScripts() {
		for (uint8 i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			ScriptContext& context = _contextAllocator.get_unchecked(i);
			const uint8 where = context._scriptWhere;

			if (where == OW_Room || where == OW_FLObject || where == OW_Local) {
				context._reset();
			}
		}

		/* TODO: Delete New Names */
	}

	CutsceneScriptState::CutsceneScriptState() {
		for(uint8 i=0; i < MAX_CUTSCENES_STACK; i++) {
			CutsceneScriptStackItem& item = _items[i];
			item._context = 0;
			item._data = 0;
			item._pc = 0;
		}
	}


}
