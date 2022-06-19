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
#include "constants.h"
#include "vm_opcodes.h"
#include "vm_vars.h"

#include "common/endian.h"

using namespace common;

namespace comi
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
#endif

	VirtualMachine* VM = NULL;
	uint8 CURRENT_CONTEXT = NO_CONTEXT;
	
	VirtualMachine::VirtualMachine() :
		_script(NULL), 
		_contextStackSize(0)
	{
		_nullScript.setSize(4);
		_nullScript.set(0, OP_systemOps);
		_nullScript.set(1, SystemOps_Quit);
		_nullScript.set(2, 0xFF);
		_nullScript.set(3, 0xFF);

		
		for (uint8 i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			_context[i].reset();
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

		_script = NULL;

		if (_messageTemp.capacity() == 0) {
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

		_pushPcState = false;

		INTS->currentdisk = 1;

	}
	
	void VirtualMachine::runScript(uint16 scriptNum, bool freezeResistant, bool recursive, int32* data, uint8 dataCount)
	{
		debug(COMI_THIS, "runScript %ld", (uint32) scriptNum);

		if (scriptNum == 0) {
			warn(COMI_THIS, "VM tried to run NULL script 0");
			return;
		}

		if (recursive == false) {
			_stopScript(scriptNum);
		}

		if (scriptNum < NUM_SCRIPTS) {
			debug(COMI_THIS, "%ld load script", (uint32) scriptNum);
			RESOURCES->loadScriptData(scriptNum);
		}
		else {
			debug(COMI_THIS, "%ld other script", (uint32)scriptNum);
		}

		uint8 contextNum = 0;

		if (_findFreeContext(contextNum) == false) {
			error(COMI_THIS, "Could not find free ScriptContext for %ld", (uint32)scriptNum);
			return;
		}

		ScriptContext& context = _context[contextNum];
		context.reset();
		context._scriptNum = scriptNum;
		context._state = SCS_Running;
		context._bFreezeResistant = freezeResistant;
		context._bRecursive = recursive;
		context._scriptWhere = (scriptNum < NUM_SCRIPTS) ? OW_Global : OW_Local;

		LOCALS->clear(contextNum);

		_updateScriptData(context);
		LOCALS->copyInto(contextNum, data, dataCount);
		_placeContextOnStackAndRun(contextNum);
	}

	
	void VirtualMachine::runObjectScript(uint16 objectNum, uint16 entryPc, bool freezeResistant, bool recursive, int32* data, uint8 dataCount) {
		if (objectNum == 0) {
			error(COMI_THIS, "Could not run a NULL object script %ld", (uint32) objectNum);
			abort_quit_stop();
			return;
		}

		if (recursive == false) {
			_stopObjectScript(objectNum);
		}

		error(COMI_THIS, "Feature not implemented (%ld)", (uint32) objectNum);
		abort_quit_stop();
	}
	
	bool VirtualMachine::_findFreeContext(uint8& num) {
		for (uint8 i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			if (_context[i].isDead()) {
				num = i;
				return true;
			}
		}
		return false;
	}

	void VirtualMachine::_stopObjectCode() {
		
		ScriptContext& context = _context[CURRENT_CONTEXT];

		if (context._cutsceneOverride == 255) {
			context._cutsceneOverride = 0;
		}


		if (context._scriptWhere != OW_Global && context._scriptWhere != OW_Local) {
			if (context._cutsceneOverride) {
				context._cutsceneOverride = 0;
			}
		}
		else {
			if (context._cutsceneOverride) {
				context._cutsceneOverride = 0;
			}
		}

		context.markDead();
		CURRENT_CONTEXT = NO_CONTEXT;
		
		if (_pushPcState) {
			_pushPcState = false;
			_pcState.contextAfter = CURRENT_CONTEXT;
			_pcState.pcAfter = _pc;
			_lastPcStates.write(_pcState);
		}

	}

	void VirtualMachine::_stopScript(uint16 scriptNum) {
		if (scriptNum == 0)
			return;

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
					error(COMI_THIS, "Stopped script %ld with an cutscene override", scriptNum);
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
				if (scriptNum == 0)
			return;

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
					error(COMI_THIS, "Stopped script %ld with an cutscene override", scriptNum);
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

	VmArray* VirtualMachine::newArray(uint32 arrayNum, uint8 kind, uint16 y, uint16 x) {
		
		VmArray* array = ARRAYS->allocate(arrayNum, x, y, kind);

		if (array == NULL) {
			return array;
		}

		INTS->set(arrayNum, array->_idx);

		return array;
	}

	void VirtualMachine::deleteArray(uint32 arrayNum) {
		
		uint32 arrayIndex = INTS->get(arrayNum);

		if (arrayIndex >= NUM_ARRAY) {
			error(COMI_THIS, "Tried to delete an array out of bounds!");
			_forceQuit();
			return;
		}

		VmArray* arrayHeader = ARRAYS->getFromIndex(arrayIndex);

		if (arrayHeader != NULL) {
			ARRAYS->deallocateFromArray(arrayHeader);
			INTS->set(arrayNum, 0);
		}
	}
	
	void VirtualMachine::_updateScriptData(ScriptContext& context) {
		uint16 _scriptNum = context._scriptNum;

		if (context._scriptNum < NUM_GLOBAL_SCRIPTS && context._scriptWhere == OW_Global) {
			ScriptData* script = RESOURCES->getScriptData(context._scriptNum);
			if (script) {
				_script = script->getDataPtr();
				return;
			}
			else {
				warn(COMI_THIS, "Unhandled ID Where for Script Data! Num=%ld, Where=%ld", (uint32)_scriptNum, (uint32)context._scriptWhere);
				_script = &_nullScript;
			}
		}

		warn(COMI_THIS, "Unhandled ID Where for Script Data! Num=%ld, Where=%ld", (uint32) _scriptNum, (uint32) context._scriptWhere);
		_script = &_nullScript;
		
	}

	void VirtualMachine::_placeContextOnStackAndRun(uint8 newContextNum) {
		
		debug(COMI_THIS, "Push (%ld)", (uint32)newContextNum);

		if (_pushPcState) {
			_pushPcState = false;
			_pcState.contextAfter = newContextNum;
			_pcState.pcAfter = _pc;
			_lastPcStates.write(_pcState);
		}

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
		}
		
		_contextStackSize++;

		CURRENT_CONTEXT = newContextNum;
		
		ScriptContext& context = _context[CURRENT_CONTEXT];
		_pc = context._lastPC;
		runCurrentScript();

		if (_contextStackSize) {
			_contextStackSize--;
		}

		if (QUIT_NOW) {
			CURRENT_CONTEXT = NO_CONTEXT;
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
				debug(COMI_THIS, "Resume (%ld)", (uint32)last._contextNum);


				CURRENT_CONTEXT = last._contextNum;
				_updateScriptData(lastContext);
				_pc = lastContext._lastPC;
				
				PcState state;
				state.context = last._contextNum;
				state.opcode = 0xFF;
				state.pc = _pc;
				state.pcAfter = _pc;
				_lastPcStates.write(state);

				return;
			}

		}

		CURRENT_CONTEXT = NO_CONTEXT;
	}

	void VirtualMachine::runCurrentScript() {
		while (CURRENT_CONTEXT != NO_CONTEXT) {
			_pushPcState = true;
			_pcState.pc = _pc;
			_pcState.context = CURRENT_CONTEXT;
			_step();
			if (_pushPcState) {
				_pcState.pcAfter = _pc;
				_pcState.contextAfter = CURRENT_CONTEXT;
				_lastPcStates.write(_pcState);
			}
		}
	}

	void VirtualMachine::_delay(uint32 time) {
		if (CURRENT_CONTEXT != NO_CONTEXT) {
			ScriptContext& context = _context[CURRENT_CONTEXT];
			context._delay = time;
			context._state = SCS_Paused;
			_break();
		}
	}

	void VirtualMachine::_break() {
		if (CURRENT_CONTEXT != NO_CONTEXT) {
			
			if (_pushPcState) {
				_pushPcState = false;
				_pcState.contextAfter = NO_CONTEXT;
				_pcState.pcAfter = _pc;
				_lastPcStates.write(_pcState);
			}

			ScriptContext& context = _context[CURRENT_CONTEXT];
			context._lastPC = _pc;
			CURRENT_CONTEXT = NO_CONTEXT;
		}
	}

	byte VirtualMachine::_readByte() {
		byte value = _script->get_unchecked(_pc++);
		return value;
	}
	
	int32 VirtualMachine::_readWord() {
		int32 value = *( (int32*) _script->ptr(_pc));
		value = FROM_LE_32(value);
		_pc += 4;
		return value;
	}

	uint32 VirtualMachine::_readUnsignedWord() {

		uint32 value = *((uint32*) _script->ptr(_pc));
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

	void VirtualMachine::_decodeParseString(uint8 m, uint8 n) {
		byte b = _readByte();

		NO_FEATURE(COMI_THIS, "Not properly implemented");

		switch (b) {
			case 0xC8: {	// Print BaseOP
				// ...
				if (n != 0) {
					_stack.pop();
				}
			}
			break;
			case 0xC9:		// Print End
			break;
			case 0xCA:		// Print At
				_stack.pop();
				_stack.pop();
			break;
			case 0xCB:		// Print Colour
			break;
			case 0xCC:		// Print Center
			break;
			case 0xCD:		// Print Charset
				_stack.pop();
			break;
			case 0xCE:		// Print Left
			break;
			case 0xCF:		// Print Overhead
			break;
			case 0xD0:		// Print Mumble
			break;
			case 0xD1:		// Print String
			{
				uint16 from, length;
				_readStringLength(from, length);	/* Not Implemented */
			}
			break;
			case 0xD2:
			break;
		}
	}

	void VirtualMachine::_dumpState() {
		
		debug_write(DC_Debug, GS_FILE_NAME, __FILE__, __FUNCTION__, __LINE__, "VM State as follows:");
		
		uint8 lastContext = CURRENT_CONTEXT;

		for (uint16 i = 0; i < 8; i++) {
			PcState state;
			_lastPcStates.read(7-i, state);

			if (state.pc == state.pcAfter && state.opcode == 0xFF) {
				debug_write_str("## Resume to ");
				debug_write_byte(state.context);
				debug_write_char('\n');
				continue;
			}
				
			if (i == 0 || state.context != lastContext) {
				debug_write_byte((byte) (state.context));
			}
			else {
				debug_write_char('.');
				debug_write_char('.');
			}
			debug_write_char(' ');
				
			lastContext = state.context;
				
			debug_write_char(' ');
			debug_write_int(state.pc);
			debug_write_char(' ');
			debug_write_str(_getOpcodeName(state.opcode));
			debug_write_char('@');
			debug_write_byte(state.opcode);
				
			debug_write_char(' ');
			debug_write_char('(');

			if (state.context == CURRENT_CONTEXT && _script != NULL) {

				for (uint16 j = state.pc; j < state.pcAfter; j++) {
					if (j != state.pc) {
						debug_write_char(' ');
					}
					debug_write_byte(_script->get_unchecked(j));
				}

			}
			else {
				debug_write_char('?');
			}
				
			debug_write_char(')');
			debug_write_char('\n');

			if (state.context != state.contextAfter && state.opcode != OP_stopObjectCode) {
				debug_write_str("##  ");
				debug_write_byte(state.context);
				debug_write_str(" to ");
				debug_write_byte(state.contextAfter);
				debug_write_char('\n');
			}

		}
			
		debug_write_str("??  ");
		debug_write_int(_pcOpcode);
		debug_write_char(' ');
		debug_write_str(_getOpcodeName(_opcode));
		debug_write_char('@');
		debug_write_byte(_opcode);

		uint16 end = _pcOpcode + 15;
		if (end > _script->getSize()) {
			end = _script->getSize();
		}
			
		debug_write_char(' ');
		debug_write_char('(');
			


		for (uint16 i = _pc; i < end; i++) {
			if (i != _pc) {
				debug_write_char(' ');
			}
			debug_write_byte(_script->get_unchecked(i));
		}
			
		debug_write_str(" ...)\n");

		int16 stackMin = _stack.getSize() - 16;
		if (stackMin < 0)
			stackMin = 0;

		int16 stackMax = _stack.getSize();
		
		if (stackMax > 0) {
			for (int16 i = stackMin; i < stackMax; i++) {
				debug_write_str("    ");
				debug_write_byte(i);
				debug_write_char('=');
				debug_write_int(_stack.get_unchecked(i));
				debug_write_char('\n');
			}
		}

	
		debug_write_char('\n');

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

	void ScriptContext::reset() {
		uint8 i = 0;

		_scriptNum = 0;
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


}
