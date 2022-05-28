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

#define GS_FILE_NAME "common/script"

#include "script.h"

#include "debug.h"
#include "constants.h"

using namespace common;

namespace comi
{
	VirtualMachine::VirtualMachine() {
		comi_debug(".");
	}

	VirtualMachine::~VirtualMachine() {
		comi_debug(".");
	}

	void VirtualMachine::reset() {
		comi_debug(".");

		int32 i;

		_currentScript = 0;

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

		for (i = 0; i < NUM_CONCURRENT_SCRIPTS; i++) {
			_scripts[i].reset();
		}

	}

	int32 VirtualMachine::readVar(uint32 var) {
		comi_debug("readvar(%d)", var);

		// Global Ints
		if (!(var & 0xF0000000)) {
			if (var >= NUM_INT_GLOBALS) {
				comi_error("Int Global %d out of range!", var);
			}
			return _intGlobals.get_unchecked(var);
		}

		// Global Bits
		if (var & 0x80000000) {
			var &= 0x7FFFFFFF;
			if (var >= NUM_BOOL_GLOBALS) {
				comi_error("Bool Global variable %d out of range!", var);
			}
			return _boolGlobals.get_unchecked(var);
		}

		// Locals
		if (var & 0x40000000) {
			var &= 0xFFFFFFF;
			if (var >= NUM_INT_LOCALS) {
				comi_error("Script variable %d out of range!", var);
			}
			return _scripts[_currentScript]._locals[var];
		}

		comi_error("Unsupported variable index! %d", var);
		return -1;
	}

	ConcurrentScript::ConcurrentScript() {
	}

	ConcurrentScript::~ConcurrentScript() {
	}

	void ConcurrentScript::reset() {
		int32 i = 0;


		for (i = 0; i < NUM_INT_LOCALS; i++) {
			_locals[i] = 0;
		}
	}


}
