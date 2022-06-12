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

#define GS_FILE_NAME "opcodes"

#include "opcodes.h"
#include "vm.h"
#include "context.h"
#include "debug.h"

namespace comi
{
	static const uint8 NO_CONTEXT = 0xFF;

	void VirtualMachine::_step() {
		_opcode = _readByte();

		switch (_opcode) {
			case OP_SysCall: {

				byte param = _readByte();

				if (param == OpSyscall_Quit) {
					CTX->quit = true;
					info(COMI_THIS, "Quit has been called");
					return;
				}
				
				error(COMI_THIS, "Unhandled SysCall! %ld", (uint32) param);
				_currentContext = NO_CONTEXT;

			}
			return;
			default:

				debug_write_str("opcode=");
				debug_write_unsigned_int(_opcode);
				debug_write_str("\n");

				error(COMI_THIS, "(%2x) Unhandled Opcode!", _opcode);
				_currentContext = NO_CONTEXT;
			return;
			
		}
	}

}
