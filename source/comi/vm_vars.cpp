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

#define GS_FILE_NAME "vars"

#include "vm_vars.h"
#include "vm.h"

#include "common/memory.h"

namespace comi
{
	VmIntVars INTS;
	VmBoolVars BOOLS;

	
	void resetVars() {
		common::clearMemoryNonAllocated(&INTS, sizeof(INTS));
		common::clearMemoryNonAllocated(&BOOLS, sizeof(BOOLS));
	}

	void setVar(uint32 varName, int32 value) {

		// Global Ints
		if (!(varName & 0xF0000000)) {
			if (varName >= NUM_INT_GLOBALS) {
				error(COMI_THIS, "Int Global %d out of range!", varName);
				return;
			}
			INTS.set(varName, value);
			return;
		}

		// Global Bools
		if (varName & 0x80000000) {
			varName &= 0x7FFFFFFF;
			if (varName >= NUM_BOOL_GLOBALS) {
				error(COMI_THIS, "Bool Global variable %d out of range!", varName);
			}

			BOOLS.set_unchecked(varName, value);
			return;
		}

		// VM Local Ints
		if (varName & 0x40000000) {
			varName &= 0xFFFFFFF;
			if (varName >= NUM_INT_LOCALS) {
				error(COMI_THIS, "Script variable %d out of range!", varName);
			}
			VM->setLocalVar_unchecked(varName, value);
			return;
		}

	}

	int32 getVar(uint32 varName) {


		// Global Ints
		if (!(varName & 0xF0000000)) {
			if (varName >= NUM_INT_GLOBALS) {
				error(COMI_THIS, "Int Global %d out of range!", varName);
				return 0;
			}
			return INTS.get(varName);
		}

		// Global Bools
		if (varName & 0x80000000) {
			varName &= 0x7FFFFFFF;
			if (varName >= NUM_BOOL_GLOBALS) {
				error(COMI_THIS, "Bool Global variable %d out of range!", varName);
			}
			return BOOLS.get_unchecked(varName);
		}

		// Local Ints
		if (varName & 0x40000000) {
			varName &= 0xFFFFFFF;
			if (varName >= NUM_INT_LOCALS) {
				error(COMI_THIS, "Script variable %d out of range!", varName);
			}
			return VM->getLocalVar_unchecked(varName);
		}

		return 0;
	}
}
