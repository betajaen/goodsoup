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

#define GS_FILE_NAME "vm_context"

#include "context.h"
#include "opcodes.h"
#include "stack.h"
#include "vm.h"
#include "vars.h"
#include "debugger.h"

#include "../array.h"
#include "../endian.h"
#include "../globals.h"
#include "../room.h"


namespace gs {

	ScriptContextAllocator::ScriptContextAllocator() {
		clear();
	}

	ScriptContextAllocator::~ScriptContextAllocator() {
	}

	void ScriptContextAllocator::clear() {
		for(uint8 i=0;i < MAX_SCRIPT_CONTEXTS+1;i++) {
			_contexts[i]._reset();
			_contexts[i]._indexNum = i;
		}
	}

	ScriptContext& ScriptContextAllocator::acquire() {
		for(uint8 i=0;i < MAX_SCRIPT_CONTEXTS;i++) {
			ScriptContext& context = _contexts[i];
			if (context._isDead()) {
				context._reset();
				return context;
			}
		}

		error(GS_THIS, "Out of ScriptContextes!");
		abort_quit_stop();
		return _contexts[0];
	}


	byte ScriptContext::_readByte() {
		byte value = _script.get_unchecked(_pc++);
		return value;
	}

	int32 ScriptContext::_readWord() {
		int32 value = *( (int32*) _script.ptr(_pc));
		value = FROM_LE_32(value);
		_pc += 4;
		return value;
	}

	uint32 ScriptContext::_readUnsignedWord() {

		uint32 value = *((uint32*) _script.ptr(_pc));
		value = FROM_LE_32(value);
		_pc += 4;
		return value;
	}

	int32 ScriptContext::_readSignedWord() {

		int32 value = *((int32*) _script.ptr(_pc));
		value = FROM_LE_32(value);
		_pc += 4;
		return value;
	}

	void ScriptContext::_readStringLength(uint16& from, uint16& len) {
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

	void ScriptContext::_readBytesForArray() {

		Array<byte, uint16>& _arrayTemp = VM->_arrayTemp;

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

	void ScriptContext::_decodeParseString(uint8 m, uint8 n) {
		byte subOp = _readByte();

		/* TODO */

		switch(subOp) {
			default:
				error(GS_THIS, "Unhandled subop %02lx", (uint32) subOp);
				abort_quit_stop();
				return;

			case ParseStringOp_Load: {
				if (n != 0) {
					STACK.pop(); // actor to print
				}
			}
				break;
			case ParseStringOp_Save: {
			}
				break;
			case ParseStringOp_SetPos: {
				STACK.pop(); // y
				STACK.pop(); // x
			}
				break;
			case ParseStringOp_SetColour: {
				STACK.pop(); // colour
			}
				break;
			case ParseStringOp_SetCenter: {
			}
				break;
			case ParseStringOp_SetCharset: {
				STACK.pop(); // charset
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

	void ScriptContext::_actorSay(uint16 actorNum, uint16 length, uint16 offset) {
		info(GS_THIS, "%s", _script.ptr(offset));
	}

	bool ScriptContext::_getScriptData() {

		if (_bHasScript) {
			return true;
		}

		_scriptReference.gcForget();
		_script = OpcodeSpan();

		if (_scriptNum < NUM_GLOBAL_SCRIPTS && _scriptWhere == OW_Global) {
			// SCRP (<2000)
			_scriptReference = SCRIPTS->getOrLoadGlobalScript(_scriptNum);

			if (_scriptReference.isNull()) {
				return false;
			}

			_script = _scriptReference.getData();
			_scriptWhere = OW_Global;

#if defined(GS_VM_DEBUG) && GS_VM_DEBUG==1
			vmDebugScript(_indexNum, _scriptNum, _scriptWhere, _verb, _script.getSize());
        	vmDebugLocals(NUM_INT_LOCALS, &_locals[0]);
        	vmDebugStack(STACK.getSize(), STACK.items());
#endif

			_bHasScript = true;
			return true;
		}
		else if (_scriptNum >= NUM_GLOBAL_SCRIPTS) {
			// LSCR (>2000), EXCD (10001) and ENCD (10002) scripts
			RoomData* room = getRoom();

			if (room) {
				if (room->getLocalScript(_scriptNum, _scriptReference)) {
					_script = _scriptReference.getData();
					_scriptWhere = _scriptNum < HSN_RoomExit ? OW_Local : OW_Room;

#if defined(GS_VM_DEBUG) && GS_VM_DEBUG==1
			vmDebugScript(_indexNum, _scriptNum, _scriptWhere, _verb, _script.getSize());
        	vmDebugLocals(NUM_INT_LOCALS, &_locals[0]);
        	vmDebugStack(STACK.getSize(), STACK.items());
#endif
					_bHasScript = true;
					return true;
				}
			}
		}
		else if (_scriptWhere == OW_ObjectVerb) {

			_scriptReference = SCRIPTS->getObjectVerbScript(_scriptNum, _verb);

			if (_scriptReference.isNull()) {
				error(GS_THIS, "Unhandled ObjectVerb Script Data! Num=%ld, Verb=%ld Where=%s", (uint32) _scriptNum, (uint32) _verb, ObjectWhereToString(_scriptWhere));
				return false;
			}

			if (_scriptReference.getData(_verb, _script) == false) {
				error(GS_THIS, "Unhandled ObjectVerb Script Verb Table Data! Num=%ld, Verb=%ld Where=%s", (uint32) _scriptNum, (uint32) _verb, ObjectWhereToString(_scriptWhere));
				return false;
			}
#if defined(GS_VM_DEBUG) && GS_VM_DEBUG==1
			vmDebugScript(_indexNum, _scriptNum, _scriptWhere, _verb, _script.getSize());
        	vmDebugLocals(NUM_INT_LOCALS, &_locals[0]);
        	vmDebugStack(STACK.getSize(), STACK.items());
#endif

			_bHasScript = true;
			return true;
		}

		error(GS_THIS, "Unhandled Script Data! Num=%ld, Where=%s", (uint32) _scriptNum, ObjectWhereToString(_scriptWhere));
		abort_quit_stop();

		return false;
	}

	void ScriptContext::_forgetScriptData() {
		_script = OpcodeSpan();
		_scriptReference.gcForget();
		_bHasScript = false;
	}

	void ScriptContext::run() {

		if (_bHasScript == false) {
			if (_getScriptData() == false) {
				error(GS_THIS, "Could not find script %ld", _scriptNum);
				return;
			}
		}
#if defined(GS_VM_DEBUG) && GS_VM_DEBUG==1
		else
		{
			vmDebugScript(_indexNum, _scriptNum, _scriptWhere, _verb, _script.getSize());
        	vmDebugLocals(NUM_INT_LOCALS, &_locals[0]);
        	vmDebugStack(STACK.getSize(), STACK.items());
		}
#endif

		if (_script.getSize() == 0) {
			error(GS_THIS, "Tried to run an empty script!");
			abort_quit_stop();
			return;
		}

		while (CURRENT_CONTEXT == _indexNum) {
#if GS_DEBUG == 1
			if (_pc >= _script.getSize()) {
				error(GS_THIS, "Out of program space!");
				abort_quit_stop();
				return;
			}
#endif

			_bIsExecuted = true;
			_step();
		}
	}

	void ScriptContext::clearLocals() {
		for (uint8 i = 0; i < NUM_INT_LOCALS; i++) {
			_locals[i] = 0;
		}
	}

	void ScriptContext::setVar(uint32 name, int32 value) {

		// Local Ints
		if (name & 0x40000000) {
			name &= 0xFFFFFFF;

#if GS_CHECKED == 1
			if (name >= NUM_INT_LOCALS) {
				error(GS_THIS, "Script variable %d out of range!", name);
				abort_quit_stop();
				return;
			}
#endif

			_locals[name] = value;
			return;
		}

		setGlobalVar(name, value);
	}

	int32 ScriptContext::getVar(uint32 name) {

		// Local Ints
		if (name & 0x40000000) {
			name &= 0xFFFFFFF;

#if GS_CHECKED == 1
			if (name >= NUM_INT_LOCALS) {
				error(GS_THIS, "Script variable %d out of range!", name);
				abort_quit_stop();
				return 0;
			}
#endif

			return _locals[name];
		}

		return getGlobalVar(name);
	}

	void ScriptContext::copyIntoLocals(int32* values, uint8 numValues) {

#if GS_CHECKED == 1
		if (numValues >= NUM_INT_LOCALS) {
			error(GS_THIS, "numValues %ld out of range for Script %ld!", (uint32) numValues, (uint32) _scriptNum);
			abort_quit_stop();
			return;
		}
#endif

		for (uint8 i = 0; i < numValues; i++) {
			_locals[i] = values[i];
		}

	}

	void ScriptContext::_reset() {
		_scriptNum = 0;
		_verb = 0;
		_scriptWhere = OW_NotFound;
		_pc = 0;
		_delay = 0;
		_state = SCS_Dead;
		_freezeCount = 0;
		_bFreezeResistant = false;
		_bRecursive = false;
		_bIsExecuted = false;
		_cutsceneOverride = false;
		_delay = 0;
		_delayFrameCount = 0;
		_bHasScript = false;
		_forgetScriptData();
		clearLocals();
	}

}