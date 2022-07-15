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
#include "globals.h"
#include "script.h"
#include "index.h"
#include "debug.h"
#include "profile.h"
#include "vm_opcodes.h"
#include "vm_vars.h"
#include "room.h"
#include "endian.h"
#include "vm_debugger.h"
#include "object.h"

#define DEBUG_CONTEXT_STACK 0

namespace gs
{
	static const uint8 NO_CONTEXT = 0xFF;

#if defined(GS_DEBUG)
	static const char* OPCODE_NAME[256] = {
		"00",
		"pushWord",
		"pushWordVar",
		"wordArrayRead",
		"wordArrayIndexedRead",
		"dup",
		"pop",
		"not",
		"eq",
		"neq",
		"gt",
		"lt",
		"le",
		"ge",
		"add",
		"sub",
		"mul",
		"div",
		"land",
		"lor",
		"band",
		"bor",
		"mod",
		"17",
		"18",
		"19",
		"1a",
		"1b",
		"1c",
		"1d",
		"1e",
		"1f",
		"20",
		"21",
		"22",
		"23",
		"24",
		"25",
		"26",
		"27",
		"28",
		"29",
		"2a",
		"2b",
		"2c",
		"2d",
		"2e",
		"2f",
		"30",
		"31",
		"32",
		"33",
		"34",
		"35",
		"36",
		"37",
		"38",
		"39",
		"3a",
		"3b",
		"3c",
		"3d",
		"3e",
		"3f",
		"40",
		"41",
		"42",
		"43",
		"44",
		"45",
		"46",
		"47",
		"48",
		"49",
		"4a",
		"4b",
		"4c",
		"4d",
		"4e",
		"4f",
		"50",
		"51",
		"52",
		"53",
		"54",
		"55",
		"56",
		"57",
		"58",
		"59",
		"5a",
		"5b",
		"5c",
		"5d",
		"5e",
		"5f",
		"60",
		"61",
		"62",
		"63",
		"if",
		"ifNot",
		"jump",
		"breakHere",
		"delayFrames",
		"wait",
		"delay",
		"delaySeconds",
		"delayMinutes",
		"writeWordVar",
		"wordVarInc",
		"wordVarDec",
		"dimArray",
		"wordArrayWrite",
		"wordArrayInc",
		"wordArrayDec",
		"dim2dimArray",
		"wordArrayIndexedWrite",
		"arrayOps",
		"77",
		"78",
		"startScript",
		"startScriptQuick",
		"stopObjectCode",
		"stopScript",
		"jumpToScript",
		"dummy",
		"startObject",
		"stopObjectScript",
		"cutscene",
		"endCutscene",
		"freezeUnfreeze",
		"beginOverride",
		"endOverride",
		"stopSentence",
		"87",
		"88",
		"setClass",
		"setState",
		"setOwner",
		"panCameraTo",
		"actorFollowCamera",
		"setCameraAt",
		"printActor",
		"printEgo",
		"talkActor",
		"talkEgo",
		"printLine",
		"printText",
		"printDebug",
		"printSystem",
		"blastText",
		"drawObject",
		"99",
		"9a",
		"9b",
		"cursorCommand",
		"loadRoom",
		"loadRoomWithEgo",
		"walkActorToObj",
		"walkActorTo",
		"putActorAtXY",
		"putActorAtObject",
		"faceActor",
		"animateActor",
		"doSentence",
		"pickupObject",
		"setBoxFlags",
		"createBoxMatrix",
		"a9",
		"resourceRoutines",
		"roomOps",
		"actorOps",
		"cameraOps",
		"verbOps",
		"startSound",
		"startMusic",
		"stopSound",
		"soundKludge",
		"systemOps",
		"saveRestoreVerbs",
		"setObjectName",
		"getDateTime",
		"drawBox",
		"b8",
		"startVideo",
		"kernelSetFunctions",
		"bb",
		"bc",
		"bd",
		"be",
		"bf",
		"c0",
		"c1",
		"c2",
		"c3",
		"c4",
		"c5",
		"c6",
		"c7",
		"startScriptQuick2",
		"startObjectQuick",
		"pickOneOf",
		"pickOneOfDefault",
		"cc",
		"isAnyOf",
		"getRandomNumber",
		"getRandomNumberRange",
		"ifClassOfIs",
		"getState",
		"getOwner",
		"isScriptRunning",
		"d4",
		"isSoundRunning",
		"abs",
		"d7",
		"kernelGetFunctions",
		"isActorInBox",
		"getVerbEntrypoint",
		"getActorFromXY",
		"findObject",
		"getVerbFromXY",
		"de",
		"findInventory",
		"getInventoryCount",
		"getAnimateVariable",
		"getActorRoom",
		"getActorWalkBox",
		"getActorMoving",
		"getActorCostume",
		"getActorScaleX",
		"getActorLayer",
		"getActorElevation",
		"getActorWidth",
		"getObjectNewDir",
		"getObjectX",
		"getObjectY",
		"getActorChore",
		"distObjectObject",
		"distPtPt",
		"getObjectImageX",
		"getObjectImageY",
		"getObjectImageWidth",
		"getObjectImageHeight",
		"f4",
		"f5",
		"getStringWidth",
		"getActorZPlane",
		"f8",
		"f9",
		"fa",
		"fb",
		"fc",
		"fd",
		"fe",
		"ff",
	};

    const char* OpcodeToString(uint8 opcode) {
        return OPCODE_NAME[opcode];
    }
#else

    const char* OpcodeToString(uint8 opcode) {
        return "?";
    }
#endif

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
		_script(), 
		_contextStackSize(0)
	{
		_nullScript = ReadSpan<byte, uint16>(&kNullScript[0], 4);
		_arrayTemp.reserve(256);
		
		for (uint8 i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			_context[i].reset();
            _context[i]._indexNum = i;
			LOCALS->clear(i);
		}

		for (uint8 i = 0; i < NUM_STACK_SCRIPTS; i++) {
			_contextStack[i].reset();
		}

	}

	VirtualMachine::~VirtualMachine() {
	}

	void VirtualMachine::reset() {
		int32 i;

		_script = ReadSpan<byte, uint16>();

		if (_messageTemp.getCapacity() == 0) {
			_messageTemp.reserve(384);
		}
		else {
			_messageTemp.clear();
		}
		
		_stack.reset();

		if (_intGlobals.hasMem() == false) {
			_intGlobals.setSize(NUM_INT_GLOBALS);
		}
		else {

			_intGlobals.zeroMem();
		}

		if (_boolGlobals.hasMem() == false) {
			_boolGlobals.setSize(NUM_BOOL_GLOBALS);
		}
		else {
			_boolGlobals.zeroMem();
		}

		for (i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			_context[i].reset();
			LOCALS->clear(i);
		}

		INTS->currentdisk = 1;

	}
	
	void VirtualMachine::runAllScripts() {
		
		for (uint8 i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			ScriptContext& context = _context[i];
			context._bIsExecuted = false;
		}

		CURRENT_CONTEXT = NO_CONTEXT;

		
		for (uint8 i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			ScriptContext& context = _context[i];
			if (context._state == SCS_Running && context._bIsExecuted == false) {
				CURRENT_CONTEXT = i;
				_updateScriptData(context);
				_pc = context._lastPC;
				runCurrentScript();

				if (QUIT_NOW)
					return;
			}
		}
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

		uint8 contextNum = 0;

		if (_acquireContext(contextNum) == false) {
			error(GS_THIS, "Could not find free ScriptContext for %ld", (uint32)scriptNum);
			abort_quit_stop();
			return;
		}

		ScriptContext& context = _context[contextNum];
		context._scriptNum = scriptNum;
		context._state = SCS_Running;
		context._bFreezeResistant = freezeResistant;
		context._bRecursive = recursive;
		context._scriptWhere = (scriptNum < NUM_SCRIPTS) ? OW_Global : OW_Local;

		if (_updateScriptData(context)) {
			LOCALS->clear(contextNum);
			LOCALS->copyInto(contextNum, data, dataCount);

			_pushAndRunScript(contextNum);
		}
	}


	void VirtualMachine::runObjectScript(uint16 objectNum, uint8 verb, bool freezeResistant, bool recursive, int32* data, uint8 dataCount) {

#if GS_CHECKED == 1
		if (objectNum == 0) {
			warn(GS_THIS, "Could not run a NULL object script %ld", (uint32) objectNum);
			return;
		}
#endif

		// Check Object Exists; Room, Global or Inventory
		ObjectData* objectData = OBJECTS->findObject(objectNum);
		if (objectData == NULL) {
			error(GS_THIS, "Could not run a object script %ld on a unloaded object", (uint32) objectNum);
			abort_quit_stop();
			return;
		}

		// Check that there is data.
		if (objectData->_script.isNull()) {
			return;
		}

		if (recursive == false) {
			_stopObjectScript(objectNum);
		}

		uint8 contextNum;

		if (_acquireContext(contextNum) == false) {
			error(GS_THIS, "Could not find free ScriptContext for %ld : %ld", (uint32) objectNum, (uint32) verb);
			abort_quit_stop();
			return;
		}

		ScriptContext& context = _context[contextNum];
		context.reset();
		context._scriptNum = objectNum;
		context._verb = verb;
		context._state = SCS_Running;
		context._bFreezeResistant = false;
		context._bRecursive = false;
		context._scriptWhere = OW_ObjectVerb;

		if (_updateScriptData(context)) {
			LOCALS->clear(contextNum);
			LOCALS->copyInto(contextNum, data, dataCount);
			_pushAndRunScript(contextNum);
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

		uint8 contextNum;

		if (_acquireContext(contextNum) == false) {
			error(GS_THIS, "Could not find free ScriptContext for %ld", (uint32)scriptNum);
			abort_quit_stop();
			return;
		}

		
		ScriptContext& context = _context[contextNum];
		context.reset();
		context._scriptNum = scriptNum;
		context._state = SCS_Running;
		context._bFreezeResistant = false;
		context._bRecursive = false;
		context._scriptWhere = OW_Room;
		
#if DEBUG_CONTEXT_STACK == 1
		debug(GS_THIS, "Attached Script %ld (Room) to Context %ld", (uint32) scriptNum, (uint32) contextNum);
#endif

		if (_updateScriptData(context)) {
			LOCALS->clear(contextNum);
			_pushAndRunScript(contextNum);
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

		uint8 contextNum;

		if (_acquireContext(contextNum) == false) {
			error(GS_THIS, "Could not find free ScriptContext for %ld", (uint32)scriptNum);
			abort_quit_stop();
			return;
		}


		ScriptContext& context = _context[contextNum];
		context.reset();
		context._scriptNum = scriptNum;
		context._state = SCS_Running;
		context._bFreezeResistant = false;
		context._bRecursive = false;
		context._scriptWhere = OW_Room;


		if (_updateScriptData(context)) {

			LOCALS->clear(contextNum);
			LOCALS->set_unchecked(contextNum, 0, clickArea);
			LOCALS->set_unchecked(contextNum, 1, code);
			LOCALS->set_unchecked(contextNum, 2, mode);

			_pushAndRunScript(contextNum);
		}
	}

	bool VirtualMachine::_acquireContext(uint8& num) {
		for (uint8 i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			if (_context[i].isDead()) {
				_context[i].reset();
				num = i;
				return true;
			}
		}
		return false;
	}
	

	void VirtualMachine::_stopObjectCode() {
		
		ScriptContext& context = _context[CURRENT_CONTEXT];

#if GS_CHECKED == 1
		if (context._cutsceneOverride) {
			error(GS_THIS, "Ending with active cutscene");
			abort_quit_stop();
			return;
		}
#endif

		context._scriptNum = 0;
		context._state = SCS_Dead;

		CURRENT_CONTEXT = NO_CONTEXT;
	}

	void VirtualMachine::_stopScript(uint16 scriptNum) {

#if GS_CHECKED == 1
		if (scriptNum == 0)
			return;
#endif

		for (uint8 i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			ScriptContext& context = _context[i];

			if (context._scriptNum == scriptNum && 
				context.isDead() == false &&
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

				context.reset();

				if (CURRENT_CONTEXT == i) {
					CURRENT_CONTEXT = NO_CONTEXT;
				}
			}
		}

		for (uint8 i = 0; i < NUM_STACK_SCRIPTS; i++) {
			ScriptStackItem& stackItem = _contextStack[i];
			if (stackItem._scriptNum == scriptNum &&
				(
					stackItem._scriptWhere == OW_Global ||
					stackItem._scriptWhere == OW_Local
				)
			) {
				stackItem.reset();
			}
		}

	}
	
	void VirtualMachine::_stopObjectScript(uint16 scriptNum) {

#if GS_CHECKED == 1
		if (scriptNum == 0)
			return;
#endif

		for (uint8 i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			ScriptContext& context = _context[i];

			if (context._scriptNum == scriptNum && 
				context.isDead() == false &&
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

				context.reset();

				if (CURRENT_CONTEXT == i) {
					CURRENT_CONTEXT = NO_CONTEXT;
				}
			}
		}

		for (uint8 i = 0; i < NUM_STACK_SCRIPTS; i++) {
			ScriptStackItem& stackItem = _contextStack[i];
			if (stackItem._scriptNum == scriptNum &&
				(
					stackItem._scriptWhere == OW_Room ||
					stackItem._scriptWhere == OW_Inventory ||
					stackItem._scriptWhere == OW_FLObject
				)
			) {
				stackItem.reset();
			}
		}
	}

	void VirtualMachine::freezeScripts(uint16 flags) {
		for (uint8 i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			ScriptContext& context = _context[i];

			if (CURRENT_CONTEXT != i && context.isDead() == false && (!context._bFreezeResistant  || flags >= 0x80)) {
				context.freeze();
			}
		}

		/* TODO: Sentence Scripts */


		if (_cutscenes._contextIndex != 0xFF) {
			_context[_cutscenes._contextIndex].unfreezeAll();
		}
	}

	void VirtualMachine::freezeAll() {
		for (uint8 i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			ScriptContext& context = _context[i];

			if (i == CURRENT_CONTEXT)
				continue;

			if (context.isDead())
				continue;

			if (context._bFreezeResistant)
				continue;

			context.freeze();
		}

		/* TODO: Sentence Scripts */

		if (_cutscenes._contextIndex != 0xFF) {
			_context[_cutscenes._contextIndex].unfreezeAll();
		}
	}

	void VirtualMachine::unfreezeAll() {
		for (uint8 i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			ScriptContext& context = _context[i];

			if (i == CURRENT_CONTEXT)
				continue;

			if (context.isDead())
				continue;

			if (context._bFreezeResistant)
				continue;

			context.unfreeze();
		}
	}

	bool VirtualMachine::isScriptRunning(uint16 scriptNum) {
		
		for (uint8 i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			ScriptContext& context = _context[i];

			if (context._scriptNum == scriptNum && 
				context.isDead() == false &&
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
			ScriptContext& context = _context[i];

			if (context._scriptNum == scriptNum && 
				context.isDead() == false &&
				(
					context._scriptWhere == OW_Room
				)
			) {
				return true;
			}
		}

		return false;
	}

	bool VirtualMachine::_updateScriptData(ScriptContext& context) {
		
		const uint16 num = context._scriptNum;
		const uint8 where = context._scriptWhere;

		_scriptReference.gcForget();
		_script = _nullScript;

		if (num < NUM_GLOBAL_SCRIPTS && where == OW_Global) {
			// SCRP (<2000)
			_scriptReference = SCRIPTS->getOrLoadGlobalScript(context._scriptNum);

			if (_scriptReference.isNull()) {
				_script = _nullScript;
				return false;
			}

			_script = _scriptReference.getData();
			context._scriptWhere = OW_Global;

#if defined(GS_VM_DEBUG) && GS_VM_DEBUG==1
		vmDebugScript(context._indexNum, num, context._scriptWhere, context._verb, _script.getSize());
        vmDebugLocals(26, &LOCALS->_locals[context._indexNum][0]);
        vmDebugStack(_stack.getSize(), _stack.items());
#endif

			return true;
		}
		else if (num >= NUM_GLOBAL_SCRIPTS) {
			// LSCR (>2000), EXCD (10001) and ENCD (10002) scripts
			RoomData* room = getRoom();

			if (room) {
				if (room->getLocalScript(num, _scriptReference)) {
					_script = _scriptReference.getData();
					context._scriptWhere = num < HSN_RoomExit ? OW_Local : OW_Room;

#if defined(GS_VM_DEBUG) && GS_VM_DEBUG==1
		vmDebugScript(context._indexNum, num, context._scriptWhere, context._verb, _script.getSize());
        vmDebugLocals(26, &LOCALS->_locals[context._indexNum][0]);
        vmDebugStack(_stack.getSize(), _stack.items());
#endif
					return true;
				}
			}
		}
		else if (where == OW_ObjectVerb) {

			_scriptReference = SCRIPTS->getObjectVerbScript(context._scriptNum, context._verb);

			if (_scriptReference.isNull()) {
				error(GS_THIS, "Unhandled ObjectVerb Script Data! Num=%ld, Verb=%ld Where=%s", (uint32) num, (uint32) context._verb, ObjectWhereToString(where));
				return false;
			}

			if (_scriptReference.getData(context._verb, _script) == false) {
				error(GS_THIS, "Unhandled ObjectVerb Script Verb Table Data! Num=%ld, Verb=%ld Where=%s", (uint32) num, (uint32) context._verb, ObjectWhereToString(where));
				return false;
			}
#if defined(GS_VM_DEBUG) && GS_VM_DEBUG==1
		vmDebugScript(context._indexNum, num, context._scriptWhere, context._verb, _script.getSize());
        vmDebugLocals(26, &LOCALS->_locals[context._indexNum][0]);
        vmDebugStack(_stack.getSize(), _stack.items());
#endif

			return true;
		}

		error(GS_THIS, "Unhandled Script Data! Num=%ld, Where=%s", (uint32) num, ObjectWhereToString(where));
		_script = _nullScript;
		abort_quit_stop();

		return false;
	}

	void VirtualMachine::_pushAndRunScript(uint8 newContextNum) {

		ScriptStackItem& last = _contextStack[_contextStackSize];
		
		if (CURRENT_CONTEXT == NO_CONTEXT) {
			last._scriptWhere = OW_NotFound;
			last._scriptNum = 0;
			last._contextNum = NO_CONTEXT;
		}
		else {
			ScriptContext& current = _context[CURRENT_CONTEXT];
			last._contextNum = CURRENT_CONTEXT;
			last._scriptNum = current._scriptNum;
			last._scriptWhere = current._scriptWhere;
			current._lastPC = _pc;
		
#if DEBUG_CONTEXT_STACK == 1	
			debug(GS_THIS, "Pushing Context %ld:%ld(%s) onto stack", (uint32)CURRENT_CONTEXT, (uint32) current._scriptNum, ObjectWhereToString(current._scriptWhere));
#endif
		}
		
		_contextStackSize++;

		CURRENT_CONTEXT = newContextNum;
		
		ScriptContext& context = _context[CURRENT_CONTEXT];
		_pc = context._lastPC;

#if DEBUG_CONTEXT_STACK == 1
		debug(GS_THIS, "Running Context %ld:%ld(%s)", (uint32) CURRENT_CONTEXT, context._scriptNum, ObjectWhereToString(context._scriptWhere));
#endif

		runCurrentScript();

		if (_contextStackSize) {
			_contextStackSize--;
		}

		if (QUIT_NOW) {
			CURRENT_CONTEXT = NO_CONTEXT;
			_contextStackSize = 0;
			return;
		}

		// Resume.
		if (last._scriptNum != 0 && last._contextNum < MAX_SCRIPT_CONTEXTS) {
			ScriptContext& lastContext = _context[last._contextNum];

			if (lastContext._scriptNum == last._scriptNum &&
				lastContext._scriptWhere == last._scriptWhere &&
				lastContext.isFrozen() == false &&
				lastContext.isDead() == false
				)
			{
#if DEBUG_CONTEXT_STACK == 1
				debug(GS_THIS, "Popping Context %ld:%ld(%s)", (uint32)last._contextNum, lastContext._scriptNum, ObjectWhereToString(lastContext._scriptWhere));
#endif
				CURRENT_CONTEXT = last._contextNum;
				if (_updateScriptData(lastContext) == false) {
					abort_quit_stop();
					return;
				}

				_pc = lastContext._lastPC;

				return;
			}

		}

		CURRENT_CONTEXT = NO_CONTEXT;
	}

	void VirtualMachine::runCurrentScript() {
		ScriptContext& context = _context[CURRENT_CONTEXT];
		while (CURRENT_CONTEXT != NO_CONTEXT) {

#if GS_DEBUG == 1
			if (_pc >= _script.getSize()) {
				error(GS_THIS, "Out of program space!");
				abort_quit_stop();
				return;
			}
#endif

            context._bIsExecuted = true;
			_step();
		}
	}

	void VirtualMachine::_delay(uint32 time) {
		ScriptContext& context = _context[CURRENT_CONTEXT];
		if (CURRENT_CONTEXT != NO_CONTEXT) {
			context._bIsExecuted = true;
			context._delay = time;
			context._state = SCS_Paused;
			_break();
		}
	}

	void VirtualMachine::_beginCutscene(uint16 stackListCount) {
		uint8 contextIdx = CURRENT_CONTEXT;
		ScriptContext& context = _context[CURRENT_CONTEXT];
		context._cutsceneOverride++;
		_cutscenes._stackSize++;

		CutsceneScriptStackItem& cutsceneItem = _cutscenes._items[_cutscenes._stackSize];
		cutsceneItem._data = stackListCount > 0 ? _stack.getListItem(0) : 0;
		cutsceneItem._context = 0;
		cutsceneItem._pc = 0;

		_cutscenes._contextIndex = contextIdx;

		if (INTS->cutsceneStartScript != 0) {
			runScript(INTS->cutsceneStartScript, false, false, _stack.getList(), stackListCount);
		}

		_cutscenes._contextIndex = NO_CONTEXT;


		debug(GS_THIS, "Start Cutscene");
	}

	void VirtualMachine::_endCutscene() {
		uint8 contextIdx = CURRENT_CONTEXT;
		ScriptContext& context = _context[CURRENT_CONTEXT];

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

	void VirtualMachine::_beginOverride() {
		CutsceneScriptStackItem& cutsceneItem = _cutscenes._items[_cutscenes._stackSize];
		cutsceneItem._context = CURRENT_CONTEXT;
		cutsceneItem._pc = _pc;

		_readByte();
		_readWord();

		INTS->override_ = 0;
	}

	void VirtualMachine::_endOverride() {
		CutsceneScriptStackItem& cutsceneItem = _cutscenes._items[_cutscenes._stackSize];
		cutsceneItem._context = 0;
		cutsceneItem._pc = 0;

		INTS->override_ = 0;
	}

	void VirtualMachine::_break() {
		if (CURRENT_CONTEXT != NO_CONTEXT) {
			ScriptContext& context = _context[CURRENT_CONTEXT];
			context._lastPC = _pc;
			CURRENT_CONTEXT = NO_CONTEXT;
		}
	}


	void VirtualMachine::processScriptDelays(uint32 delta) {
		/* TODO: Talk Delay */

		for (uint8 i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			ScriptContext &context = _context[i];

			if (context._state == SCS_Paused) {
				context._delay -= delta;

				if (context._delay <= 0) {
					context._state = SCS_Running;
					context._delay = 0;
				}

			}

		}
	}


	byte VirtualMachine::_readByte() {
		byte value = _script.get_unchecked(_pc++);
		return value;
	}
	
	int32 VirtualMachine::_readWord() {
		int32 value = *( (int32*) _script.ptr(_pc));
		value = FROM_LE_32(value);
		_pc += 4;
		return value;
	}

	uint32 VirtualMachine::_readUnsignedWord() {

		uint32 value = *((uint32*) _script.ptr(_pc));
		value = FROM_LE_32(value);
		_pc += 4;
		return value;
	}

	int32 VirtualMachine::_readSignedWord() {

		int32 value = *((int32*) _script.ptr(_pc));
		value = FROM_LE_32(value);
		_pc += 4;
		return value;
	}
	
	void VirtualMachine::_readStringLength(uint16& from, uint16& len) {
		len = 0;
		from = _pc;
		while (true) {
			byte ch = _readByte();
			if (ch == 0)
				break;
			len++;
			if (ch == 0xFF) {
				ch = _readByte();
				len++;
				
				if (ch != 1 && ch != 2 && ch != 3 && ch != 8) {
					_pc += 4;
					len += 4;
				}
			}
		}
	}

	void VirtualMachine::_readBytesForArray() {
		_arrayTemp.clear();

		byte ch = _readByte();
		while(ch != 0) {
			_arrayTemp.push(ch);
			if (ch == 0xFF) {
				ch = _readByte();
				_arrayTemp.push(ch);

				if (ch != 1 && ch != 2 && ch != 3 && ch != 8) {
					_arrayTemp.push(_readByte());
					_arrayTemp.push(_readByte());
					_arrayTemp.push(_readByte());
					_arrayTemp.push(_readByte());
				}

			}
			ch = _readByte();
		}

	}

	void VirtualMachine::_decodeParseString(uint8 m, uint8 n) {
		byte subOp = _readByte();

        /* TODO */

        switch(subOp) {
            default:
                error(GS_THIS, "Unhandled subop %02lx", (uint32) subOp);
                abort_quit_stop();
            return;

            case ParseStringOp_Load: {
                if (n != 0) {
                    _stack.pop(); // actor to print
                }
            }
            break;
            case ParseStringOp_Save: {
            }
            break;
            case ParseStringOp_SetPos: {
                _stack.pop(); // y
                _stack.pop(); // x
            }
            break;
            case ParseStringOp_SetColour: {
                    _stack.pop(); // colour
            }
            break;
            case ParseStringOp_SetCenter: {
            }
            break;
            case ParseStringOp_SetCharset: {
                _stack.pop(); // charset
            }
            break;
            case ParseStringOp_SetLeft: {
            }
            break;
            case ParseStringOp_SetOverhead: {
            }
            break;
            case ParseStringOp_SetMumble: {
            }
            break;
            case ParseStringOp_PrintString: {
                uint16 from, length;
                _readStringLength(from, length);	/* Not Implemented */
            }
            break;
            case ParseStringOp_SetWrap: {
            }
            break;
        }

	}

	void VirtualMachine::dumpStack() {
#if GS_DEBUG==1
		debug(GS_THIS, "VMContext **START");
		for(uint8 i=0;i < MAX_SCRIPT_CONTEXTS;i++) {
			ScriptContext& context = _context[i];

			if (context._scriptNum == 0)
				continue;

			debug(GS_THIS, "VMContext [%d] %d %s %s", i, context._scriptNum, ObjectWhereToString(context._scriptWhere), ObjectStateToString(context._state));
		}
		debug(GS_THIS, "VMContext **END");
#endif
#if GS_DEBUG==1
		debug(GS_THIS, "Objects **START");
		OBJECTS->dumpObjects();
		debug(GS_THIS, "Objects **END");
#endif
	}

	void VirtualMachine::_forceQuit() {
		QUIT_NOW = true;
		CURRENT_CONTEXT = NO_CONTEXT;
	}
	
	const char* VirtualMachine::_getOpcodeName(uint8 opcode) const {
#if defined(GS_DEBUG)
		return OPCODE_NAME[opcode];
#else
		return "?";
#endif
	}
	
	void VirtualMachine::unloadAllRoomScripts() {
		for (uint8 i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			ScriptContext& context = _context[i];
			const uint8 where = context._scriptWhere;

			if (where == OW_Room || where == OW_FLObject || where == OW_Local) {
				context._cutsceneOverride = 0;
				context._state = SCS_Dead;
			}
		}

		/* TODO: Delete New Names */
	}

	void VirtualMachine::_actorSay(uint16 actorNum, uint16 length, uint16 offset) {
		info(GS_THIS, "%s", _script.ptr(offset));
	}

	void ScriptContext::reset() {
		uint8 i = 0;

		_scriptNum = 0;
		_verb = 0;
		_scriptWhere = OW_NotFound;
		_lastPC = 0;
		_delay = 0;
		_state = 0;
		_freezeCount = 0;
		_bFreezeResistant = false;
		_bRecursive = false;
		_bIsExecuted = false;
		_cutsceneOverride = false;
		_delay = 0;
		_delayFrameCount = 0;
	}

	void ScriptStackItem::reset() {
		_scriptNum = 0xFF;
		_scriptWhere = OW_NotFound;
		_contextNum = 0;
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
