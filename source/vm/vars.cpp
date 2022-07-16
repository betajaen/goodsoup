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

#include "vars.h"
#include "vm.h"
#include "../globals.h"

#include "memory.h"

namespace gs
{
	VmIntVars* INTS = NULL;
	VmBoolVars* BOOLS = NULL;
	VmLocalVars* LOCALS = NULL;

	
	void resetVars() {
		clearMemoryNonAllocated(INTS, sizeof(VmIntVars));
		clearMemoryNonAllocated(BOOLS, sizeof(VmBoolVars));
		clearMemoryNonAllocated(LOCALS, sizeof(VmLocalVars));
	}

	void setVar(uint32 varName, int32 value) {

		// Global Ints
		if (!(varName & 0xF0000000)) {
#if GS_CHECKED == 1
			if (varName >= NUM_INT_GLOBALS) {
				error(GS_THIS, "Int Global %d out of range!", varName);
				abort_quit_stop();
				return;
			}
#endif
			INTS->set(varName, value);
			return;
		}

		// Global Bools
		if (varName & 0x80000000) {
			varName &= 0x7FFFFFFF;
#if GS_CHECKED == 1
			if (varName >= NUM_BOOL_GLOBALS) {
				error(GS_THIS, "Bool Global variable %d out of range!", varName);
				abort_quit_stop();
				return;
			}
#endif
			BOOLS->set_unchecked(varName, value);
			return;
		}

		// VM Local Ints
		if (varName & 0x40000000) {
			varName &= 0xFFFFFFF;
#if GS_CHECKED == 1
			if (varName >= NUM_INT_LOCALS) {
				error(GS_THIS, "Script variable %d out of range!", varName);
				abort_quit_stop();
				return;
			}
#endif

			LOCALS->set_unchecked(CURRENT_CONTEXT, varName, value);
			return;
		}

	}

	int32 getVar(uint32 varName) {

		// Global Ints
		if (!(varName & 0xF0000000)) {
#if GS_CHECKED == 1
			if (varName >= NUM_INT_GLOBALS) {
				error(GS_THIS, "Int Global %d out of range!", varName);
				abort_quit_stop();
				return 0;
			}
#endif
			return INTS->get(varName);
		}

		// Global Bools
		if (varName & 0x80000000) {
			varName &= 0x7FFFFFFF;
#if GS_CHECKED == 1
			if (varName >= NUM_BOOL_GLOBALS) {
				error(GS_THIS, "Bool Global variable %d out of range!", varName);
				abort_quit_stop();
				return 0;
			}
#endif
			return BOOLS->get_unchecked(varName);
		}

		// Local Ints
		if (varName & 0x40000000) {
			varName &= 0xFFFFFFF;

#if GS_CHECKED == 1
			if (varName >= NUM_INT_LOCALS) {
				error(GS_THIS, "Script variable %d out of range!", varName);
				abort_quit_stop();
				return 0;
			}
#endif

			return LOCALS->get_unchecked(CURRENT_CONTEXT, varName);
		}

		return 0;
	}

	void VmLocalVars::clear(uint8 context) {
#if GS_CHECKED == 1
		if (context >= MAX_SCRIPT_CONTEXTS) {
			error(GS_THIS, "Context out of range %ld!", (uint32) context);
			abort_quit_stop();
			return;
		}
#endif

		for (uint8 i = 0; i < NUM_INT_LOCALS; i++) {
			_locals[context][i] = 0;
		}
	}

	void VmLocalVars::copyInto(uint8 context, int32* values, uint8 numValues) {

#if GS_CHECKED == 1
		if (context >= MAX_SCRIPT_CONTEXTS) {
			error(GS_THIS, "Context out of range %ld!", (uint32) context);
			abort_quit_stop();
			return;
		}

		
		if (numValues >= NUM_INT_LOCALS) {
			error(GS_THIS, "numValues out of range %ld!", (uint32) context, (uint32) numValues);
			abort_quit_stop();
			return;
		}
#endif
		
		for (uint8 i = 0; i < numValues; i++) {
			_locals[context][i] = values[i];
		}

	}
}
