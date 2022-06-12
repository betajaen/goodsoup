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
#include "script.h"
#include "index.h"
#include "debug.h"
#include "constants.h"
#include "opcodes.h"

#include "common/endian.h"

using namespace common;

namespace comi
{
	static const uint8 NO_CONTEXT = 0xFF;

	VirtualMachine* VM = NULL;
	
	VirtualMachine::VirtualMachine() :
		_currentContext(NO_CONTEXT),
		_script(NULL), 
		_stackSize(0)
	{
		_nullScript.setSize(4);
		_nullScript.set(0, OP_systemOps);
		_nullScript.set(1, SysOps_Quit);
		_nullScript.set(2, 0xFF);
		_nullScript.set(3, 0xFF);

		_messageTemp.reserve(384);
		
		for (uint8 i = 0; i < MAX_SCRIPT_CONTEXTS; i++) {
			_context[i].reset();
		}

		for (uint8 i = 0; i < NUM_STACK_SCRIPTS; i++) {
			_stack[i].reset();
		}

		_vmStack.setSize(150);

	}

	VirtualMachine::~VirtualMachine() {
	}

	void VirtualMachine::reset() {
		int32 i;

		_script = NULL;

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
		}

		writeVar(VAR_CURRENTDISK, 1);

	}

	int32 VirtualMachine::readVar(uint32 var) {

		// Global Ints
		if (!(var & 0xF0000000)) {
			if (var >= NUM_INT_GLOBALS) {
				error(COMI_THIS, "Int Global %d out of range!", var);
			}
			verbose(COMI_THIS, "(GLOBAL, INT, %d)", var);
			return _intGlobals.get_unchecked(var);
		}

		// Global Bits
		if (var & 0x80000000) {
			var &= 0x7FFFFFFF;
			if (var >= NUM_BOOL_GLOBALS) {
				error(COMI_THIS, "Bool Global variable %d out of range!", var);
			}
			verbose(COMI_THIS, "(GLOBAL, BOOL, %d)", var);
			return _boolGlobals.get_unchecked(var);
		}

		// Local Ints
		if (var & 0x40000000) {
			var &= 0xFFFFFFF;
			if (var >= NUM_INT_LOCALS) {
				error(COMI_THIS, "Script variable %d out of range!", var);
			}
			verbose(COMI_THIS, "(SCRIPT, INT, %d, %d)", _currentContext, var);
			return _context[_currentContext]._locals[var];
		}

		error(COMI_THIS, "(?, ?, %d) Unsupported variable index! ", var);
		return -1;
	}

	void VirtualMachine::writeVar(uint32 var, int32 value) {
		
		// Global Ints
		if (!(var & 0xF0000000)) {
			if (var >= NUM_INT_GLOBALS) {
				error(COMI_THIS, "Int Global %d out of range!", var);
			}
			verbose(COMI_THIS, "(GLOBAL, INT, %d, %d)", var, value);
			_intGlobals.set_unchecked(var, value);
			return;
		}

		// Global Booleans
		if (var & 0x80000000) {
			var &= 0x7FFFFFFF;
			if (var >= NUM_BOOL_GLOBALS) {
				error(COMI_THIS, "Bool Global variable %d out of range!", var);
			}
			verbose(COMI_THIS, "(GLOBAL, BOOL, %d, %d)", var, value);
			_boolGlobals.set_unchecked(var, var);
			return;
		}

		// Local Ints
		if (var & 0x40000000) {
			var &= 0xFFFFFFF;
			if (var >= NUM_INT_LOCALS) {
				error(COMI_THIS, "Script variable %d out of range!", var);
			}
			verbose(COMI_THIS, "(SCRIPT, INT, %d, %d, %d)", _currentContext, var, value);
			_context[_currentContext]._locals[var] = value;
			return;
		}

		error(COMI_THIS, "(?, ?, %d, %d) Unsupported variable index!", var, value);
	}

	void VirtualMachine::runScript(uint16 scriptNum, bool freezeResistant, bool recursive, int32* data, uint8 dataCount)
	{
		debug(COMI_THIS, "runScript %ld", (uint32) scriptNum);

		if (scriptNum == 0) {
			warn(COMI_THIS, "VM tried to run NULL script 0");
			return;
		}

		if (recursive == false) {
			stopScript(scriptNum);
		}

		if (scriptNum < NUM_SCRIPTS) {
			debug(COMI_THIS, "%ld load script", (uint32) scriptNum);
			RESOURCES->loadGlobalScript(scriptNum);
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
		context._state = SSS_Running;
		context._bFreezeResistant = freezeResistant;
		context._bRecursive = recursive;
		context._scriptWhere = (scriptNum < NUM_SCRIPTS) ? OW_Global : OW_Local;

		_updateScriptData(context);
		if (data != NULL && dataCount > 0 && dataCount <= NUM_INT_LOCALS) {
			for (uint8 i = 0; i < dataCount; i++) {
				context._locals[i] = data[i];
			}
		}
		_placeContextOnStackAndRun(contextNum);
	}

	void VirtualMachine::stopScript(uint16 scriptNum)
	{
		debug(COMI_THIS, "(%ld)", scriptNum);

		/* TODO */
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

	void VirtualMachine::_updateScriptData(ScriptContext& context) {
		uint16 _scriptNum = context._scriptNum;

		if (context._scriptNum < NUM_GLOBAL_SCRIPTS && context._scriptWhere == OW_Global) {
			Script* script = RESOURCES->getGlobalScript(context._scriptNum);
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

		ScriptStackItem& last = _stack[_stackSize];
		
		if (_currentContext == NO_CONTEXT) {
			last._scriptWhere = OW_NotFound;
			last._scriptNum = 0;
			last._contextNum = NO_CONTEXT;
		}
		else {
			ScriptContext& current = _context[_currentContext];
			last._contextNum = _currentContext;
			last._scriptNum = current._scriptNum;
			last._scriptWhere = current._scriptWhere;
			current._lastPC = _pc;
		}
		
		_stackSize++;

		_currentContext = newContextNum;
		
		ScriptContext& context = _context[_currentContext];
		_pc = context._lastPC;
		runCurrentScript();

		if (_stackSize) {
			_stackSize--;
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

				_currentContext = last._contextNum;
				_updateScriptData(lastContext);
				_pc = lastContext._lastPC;
				return;
			}

		}

		_currentContext = NO_CONTEXT;
	}

	void VirtualMachine::runCurrentScript() {
		/* TODO */
		debug(GS_THIS, "RUN %ld", (uint32) _currentContext);

		while (_currentContext != 0xFF) {
			_step();
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
	
	void VirtualMachine::_readMessage() {

		uint32 pc = _pc;

		_messageTemp.clear();
		while (true) {
			byte ch = (char) _readByte();
			_messageTemp.push(ch);
			if (ch == 0)
				break;
			if (ch == 0xFF) {
				ch = _readByte();
				_messageTemp.push(ch);

				if (ch != 1 && ch != 2 && ch != 3 && ch != 8) {
					_messageTemp.push(_readByte());
					_messageTemp.push(_readByte());
					_messageTemp.push(_readByte());
					_messageTemp.push(_readByte());
				}
			}
			else {
			}
		}
		debug(COMI_THIS, "Read message %ld %ld", pc, (uint32) _messageTemp.size());
	}
	
	uint16 VirtualMachine::_readMessageSize() {
		uint16 size = 0;
		while (true) {
			byte ch = _readByte();
			size++;
			if (ch == 0)
				break;
			if (ch == 0xFF) {
				ch = _readByte();
				size++;
				
				if (ch != 1 && ch != 2 && ch != 3 && ch != 8) {
					_pc += 4;
					size += 4;
				}
			}
		}
		return size;
	}

	void VirtualMachine::_decodeParseString(uint8 m, uint8 n) {
		byte b = _readByte();

		warn(COMI_THIS, "Not properly implemented");

		switch (b) {
			case 0xC8: {	// Print BaseOP
				// ...
				if (n != 0) {
					_popStack();
				}
			}
			break;
			case 0xC9:		// Print End
			break;
			case 0xCA:		// Print At
				_popStack();
				_popStack();
			break;
			case 0xCB:		// Print Colour
			break;
			case 0xCC:		// Print Center
			break;
			case 0xCD:		// Print Charset
				_popStack();
			break;
			case 0xCE:		// Print Left
			break;
			case 0xCF:		// Print Overhead
			break;
			case 0xD0:		// Print Mumble
			break;
			case 0xD1:		// Print String
			{
				_readMessageSize();	/* Not Implemented */
			}
			break;
			case 0xD2:
			break;
		}
	}

	void VirtualMachine::_pushStack(int32 value) {
		_vmStack.set_unchecked(_stackSize, value);
		_stackSize++;
	}

	int32 VirtualMachine::_popStack() {
		_stackSize--;
		_vmStack.get_unchecked(_stackSize);
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

		for (i = 0; i < NUM_INT_LOCALS; i++) {
			_locals[i] = 0;
		}
	}

	void ScriptStackItem::reset() {
		_scriptNum = 0xFF;
		_scriptWhere = OW_NotFound;
		_contextNum = 0;
	}


}
