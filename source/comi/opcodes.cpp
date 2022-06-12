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

			case OP_00:
				error(COMI_THIS, "Unhandled 0x00");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_01:
				error(COMI_THIS, "Unhandled 0x01");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_02:
				error(COMI_THIS, "Unhandled 0x02");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_03:
				error(COMI_THIS, "Unhandled 0x03");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_04:
				error(COMI_THIS, "Unhandled 0x04");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_05:
				error(COMI_THIS, "Unhandled 0x05");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_06:
				error(COMI_THIS, "Unhandled 0x06");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_07:
				error(COMI_THIS, "Unhandled 0x07");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_08:
				error(COMI_THIS, "Unhandled 0x08");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_09:
				error(COMI_THIS, "Unhandled 0x09");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_0a:
				error(COMI_THIS, "Unhandled 0x0a");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_0b:
				error(COMI_THIS, "Unhandled 0x0b");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_0c:
				error(COMI_THIS, "Unhandled 0x0c");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_0d:
				error(COMI_THIS, "Unhandled 0x0d");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_0e:
				error(COMI_THIS, "Unhandled 0x0e");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_0f:
				error(COMI_THIS, "Unhandled 0x0f");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_10:
				error(COMI_THIS, "Unhandled 0x10");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_11:
				error(COMI_THIS, "Unhandled 0x11");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_12:
				error(COMI_THIS, "Unhandled 0x12");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_13:
				error(COMI_THIS, "Unhandled 0x13");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_14:
				error(COMI_THIS, "Unhandled 0x14");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_15:
				error(COMI_THIS, "Unhandled 0x15");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_16:
				error(COMI_THIS, "Unhandled 0x16");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_17:
				error(COMI_THIS, "Unhandled 0x17");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_18:
				error(COMI_THIS, "Unhandled 0x18");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_19:
				error(COMI_THIS, "Unhandled 0x19");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_1a:
				error(COMI_THIS, "Unhandled 0x1a");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_1b:
				error(COMI_THIS, "Unhandled 0x1b");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_1c:
				error(COMI_THIS, "Unhandled 0x1c");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_1d:
				error(COMI_THIS, "Unhandled 0x1d");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_1e:
				error(COMI_THIS, "Unhandled 0x1e");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_1f:
				error(COMI_THIS, "Unhandled 0x1f");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_20:
				error(COMI_THIS, "Unhandled 0x20");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_21:
				error(COMI_THIS, "Unhandled 0x21");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_22:
				error(COMI_THIS, "Unhandled 0x22");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_23:
				error(COMI_THIS, "Unhandled 0x23");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_24:
				error(COMI_THIS, "Unhandled 0x24");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_25:
				error(COMI_THIS, "Unhandled 0x25");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_26:
				error(COMI_THIS, "Unhandled 0x26");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_27:
				error(COMI_THIS, "Unhandled 0x27");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_28:
				error(COMI_THIS, "Unhandled 0x28");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_29:
				error(COMI_THIS, "Unhandled 0x29");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_2a:
				error(COMI_THIS, "Unhandled 0x2a");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_2b:
				error(COMI_THIS, "Unhandled 0x2b");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_2c:
				error(COMI_THIS, "Unhandled 0x2c");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_2d:
				error(COMI_THIS, "Unhandled 0x2d");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_2e:
				error(COMI_THIS, "Unhandled 0x2e");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_2f:
				error(COMI_THIS, "Unhandled 0x2f");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_30:
				error(COMI_THIS, "Unhandled 0x30");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_31:
				error(COMI_THIS, "Unhandled 0x31");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_32:
				error(COMI_THIS, "Unhandled 0x32");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_33:
				error(COMI_THIS, "Unhandled 0x33");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_34:
				error(COMI_THIS, "Unhandled 0x34");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_35:
				error(COMI_THIS, "Unhandled 0x35");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_36:
				error(COMI_THIS, "Unhandled 0x36");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_37:
				error(COMI_THIS, "Unhandled 0x37");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_38:
				error(COMI_THIS, "Unhandled 0x38");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_39:
				error(COMI_THIS, "Unhandled 0x39");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_3a:
				error(COMI_THIS, "Unhandled 0x3a");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_3b:
				error(COMI_THIS, "Unhandled 0x3b");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_3c:
				error(COMI_THIS, "Unhandled 0x3c");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_3d:
				error(COMI_THIS, "Unhandled 0x3d");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_3e:
				error(COMI_THIS, "Unhandled 0x3e");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_3f:
				error(COMI_THIS, "Unhandled 0x3f");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_40:
				error(COMI_THIS, "Unhandled 0x40");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_41:
				error(COMI_THIS, "Unhandled 0x41");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_42:
				error(COMI_THIS, "Unhandled 0x42");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_43:
				error(COMI_THIS, "Unhandled 0x43");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_44:
				error(COMI_THIS, "Unhandled 0x44");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_45:
				error(COMI_THIS, "Unhandled 0x45");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_46:
				error(COMI_THIS, "Unhandled 0x46");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_47:
				error(COMI_THIS, "Unhandled 0x47");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_48:
				error(COMI_THIS, "Unhandled 0x48");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_49:
				error(COMI_THIS, "Unhandled 0x49");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_4a:
				error(COMI_THIS, "Unhandled 0x4a");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_4b:
				error(COMI_THIS, "Unhandled 0x4b");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_4c:
				error(COMI_THIS, "Unhandled 0x4c");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_4d:
				error(COMI_THIS, "Unhandled 0x4d");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_4e:
				error(COMI_THIS, "Unhandled 0x4e");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_4f:
				error(COMI_THIS, "Unhandled 0x4f");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_50:
				error(COMI_THIS, "Unhandled 0x50");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_51:
				error(COMI_THIS, "Unhandled 0x51");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_52:
				error(COMI_THIS, "Unhandled 0x52");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_53:
				error(COMI_THIS, "Unhandled 0x53");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_54:
				error(COMI_THIS, "Unhandled 0x54");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_55:
				error(COMI_THIS, "Unhandled 0x55");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_56:
				error(COMI_THIS, "Unhandled 0x56");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_57:
				error(COMI_THIS, "Unhandled 0x57");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_58:
				error(COMI_THIS, "Unhandled 0x58");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_59:
				error(COMI_THIS, "Unhandled 0x59");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_5a:
				error(COMI_THIS, "Unhandled 0x5a");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_5b:
				error(COMI_THIS, "Unhandled 0x5b");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_5c:
				error(COMI_THIS, "Unhandled 0x5c");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_5d:
				error(COMI_THIS, "Unhandled 0x5d");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_5e:
				error(COMI_THIS, "Unhandled 0x5e");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_5f:
				error(COMI_THIS, "Unhandled 0x5f");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_60:
				error(COMI_THIS, "Unhandled 0x60");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_61:
				error(COMI_THIS, "Unhandled 0x61");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_62:
				error(COMI_THIS, "Unhandled 0x62");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_63:
				error(COMI_THIS, "Unhandled 0x63");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_64:
				error(COMI_THIS, "Unhandled 0x64");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_65:
				error(COMI_THIS, "Unhandled 0x65");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_66:
				error(COMI_THIS, "Unhandled 0x66");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_67:
				error(COMI_THIS, "Unhandled 0x67");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_68:
				error(COMI_THIS, "Unhandled 0x68");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_69:
				error(COMI_THIS, "Unhandled 0x69");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_6a:
				error(COMI_THIS, "Unhandled 0x6a");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_6b:
				error(COMI_THIS, "Unhandled 0x6b");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_6c:
				error(COMI_THIS, "Unhandled 0x6c");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_6d:
				error(COMI_THIS, "Unhandled 0x6d");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_6e:
				error(COMI_THIS, "Unhandled 0x6e");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_6f:
				error(COMI_THIS, "Unhandled 0x6f");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_70:
				error(COMI_THIS, "Unhandled 0x70");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_71:
				error(COMI_THIS, "Unhandled 0x71");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_72:
				error(COMI_THIS, "Unhandled 0x72");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_73:
				error(COMI_THIS, "Unhandled 0x73");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_74:
				error(COMI_THIS, "Unhandled 0x74");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_75:
				error(COMI_THIS, "Unhandled 0x75");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_76:
				error(COMI_THIS, "Unhandled 0x76");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_77:
				error(COMI_THIS, "Unhandled 0x77");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_78:
				error(COMI_THIS, "Unhandled 0x78");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_79:
				error(COMI_THIS, "Unhandled 0x79");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_7a:
				error(COMI_THIS, "Unhandled 0x7a");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_7b:
				error(COMI_THIS, "Unhandled 0x7b");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_7c:
				error(COMI_THIS, "Unhandled 0x7c");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_7d:
				error(COMI_THIS, "Unhandled 0x7d");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_7e:
				error(COMI_THIS, "Unhandled 0x7e");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_7f:
				error(COMI_THIS, "Unhandled 0x7f");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_80:
				error(COMI_THIS, "Unhandled 0x80");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_81:
				error(COMI_THIS, "Unhandled 0x81");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_82:
				error(COMI_THIS, "Unhandled 0x82");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_83:
				error(COMI_THIS, "Unhandled 0x83");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_84:
				error(COMI_THIS, "Unhandled 0x84");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_85:
				error(COMI_THIS, "Unhandled 0x85");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_86:
				error(COMI_THIS, "Unhandled 0x86");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_87:
				error(COMI_THIS, "Unhandled 0x87");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_88:
				error(COMI_THIS, "Unhandled 0x88");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_89:
				error(COMI_THIS, "Unhandled 0x89");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_8a:
				error(COMI_THIS, "Unhandled 0x8a");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_8b:
				error(COMI_THIS, "Unhandled 0x8b");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_8c:
				error(COMI_THIS, "Unhandled 0x8c");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_8d:
				error(COMI_THIS, "Unhandled 0x8d");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_8e:
				error(COMI_THIS, "Unhandled 0x8e");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_8f:
				error(COMI_THIS, "Unhandled 0x8f");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_90:
				error(COMI_THIS, "Unhandled 0x90");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_91:
				error(COMI_THIS, "Unhandled 0x91");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_92:
				error(COMI_THIS, "Unhandled 0x92");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_93:
				error(COMI_THIS, "Unhandled 0x93");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_94:
				error(COMI_THIS, "Unhandled 0x94");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_95:
				error(COMI_THIS, "Unhandled 0x95");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_96:
				error(COMI_THIS, "Unhandled 0x96");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_97:
				error(COMI_THIS, "Unhandled 0x97");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_98:
				error(COMI_THIS, "Unhandled 0x98");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_99:
				error(COMI_THIS, "Unhandled 0x99");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_9a:
				error(COMI_THIS, "Unhandled 0x9a");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_9b:
				error(COMI_THIS, "Unhandled 0x9b");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_9c:
				error(COMI_THIS, "Unhandled 0x9c");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_9d:
				error(COMI_THIS, "Unhandled 0x9d");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_9e:
				error(COMI_THIS, "Unhandled 0x9e");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_9f:
				error(COMI_THIS, "Unhandled 0x9f");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_a0:
				error(COMI_THIS, "Unhandled 0xa0");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_a1:
				error(COMI_THIS, "Unhandled 0xa1");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_a2:
				error(COMI_THIS, "Unhandled 0xa2");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_a3:
				error(COMI_THIS, "Unhandled 0xa3");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_a4:
				error(COMI_THIS, "Unhandled 0xa4");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_a5:
				error(COMI_THIS, "Unhandled 0xa5");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_a6:
				error(COMI_THIS, "Unhandled 0xa6");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_a7:
				error(COMI_THIS, "Unhandled 0xa7");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_a8:
				error(COMI_THIS, "Unhandled 0xa8");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_a9:
				error(COMI_THIS, "Unhandled 0xa9");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_aa:
				error(COMI_THIS, "Unhandled 0xaa");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_ab:
				error(COMI_THIS, "Unhandled 0xab");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_ac:
				error(COMI_THIS, "Unhandled 0xac");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_ad:
				error(COMI_THIS, "Unhandled 0xad");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_ae:
				error(COMI_THIS, "Unhandled 0xae");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_af:
				error(COMI_THIS, "Unhandled 0xaf");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_b0:
				error(COMI_THIS, "Unhandled 0xb0");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_b1:
				error(COMI_THIS, "Unhandled 0xb1");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_b2:
				error(COMI_THIS, "Unhandled 0xb2");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_SysCall: {
				byte param = _readByte();

				if (param == OpSyscall_Quit) {
					CTX->quit = true;
					info(COMI_THIS, "Quit has been called");
					return;
				}

				error(COMI_THIS, "Unhandled SysCall! %ld", (uint32)param);
				_currentContext = NO_CONTEXT;
			}
			return;
			case OP_b4:
				error(COMI_THIS, "Unhandled 0xb4");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_b5:
				error(COMI_THIS, "Unhandled 0xb5");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_b6:
				error(COMI_THIS, "Unhandled 0xb6");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_b7:
				error(COMI_THIS, "Unhandled 0xb7");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_b8:
				error(COMI_THIS, "Unhandled 0xb8");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_b9:
				error(COMI_THIS, "Unhandled 0xb9");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_ba:
				error(COMI_THIS, "Unhandled 0xba");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_bb:
				error(COMI_THIS, "Unhandled 0xbb");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_bc:
				error(COMI_THIS, "Unhandled 0xbc");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_bd:
				error(COMI_THIS, "Unhandled 0xbd");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_be:
				error(COMI_THIS, "Unhandled 0xbe");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_bf:
				error(COMI_THIS, "Unhandled 0xbf");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_c0:
				error(COMI_THIS, "Unhandled 0xc0");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_c1:
				error(COMI_THIS, "Unhandled 0xc1");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_c2:
				error(COMI_THIS, "Unhandled 0xc2");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_c3:
				error(COMI_THIS, "Unhandled 0xc3");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_c4:
				error(COMI_THIS, "Unhandled 0xc4");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_c5:
				error(COMI_THIS, "Unhandled 0xc5");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_c6:
				error(COMI_THIS, "Unhandled 0xc6");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_c7:
				error(COMI_THIS, "Unhandled 0xc7");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_c8:
				error(COMI_THIS, "Unhandled 0xc8");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_c9:
				error(COMI_THIS, "Unhandled 0xc9");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_ca:
				error(COMI_THIS, "Unhandled 0xca");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_cb:
				error(COMI_THIS, "Unhandled 0xcb");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_cc:
				error(COMI_THIS, "Unhandled 0xcc");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_cd:
				error(COMI_THIS, "Unhandled 0xcd");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_ce:
				error(COMI_THIS, "Unhandled 0xce");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_cf:
				error(COMI_THIS, "Unhandled 0xcf");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_d0:
				error(COMI_THIS, "Unhandled 0xd0");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_d1:
				error(COMI_THIS, "Unhandled 0xd1");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_d2:
				error(COMI_THIS, "Unhandled 0xd2");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_d3:
				error(COMI_THIS, "Unhandled 0xd3");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_d4:
				error(COMI_THIS, "Unhandled 0xd4");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_d5:
				error(COMI_THIS, "Unhandled 0xd5");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_d6:
				error(COMI_THIS, "Unhandled 0xd6");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_d7:
				error(COMI_THIS, "Unhandled 0xd7");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_d8:
				error(COMI_THIS, "Unhandled 0xd8");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_d9:
				error(COMI_THIS, "Unhandled 0xd9");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_da:
				error(COMI_THIS, "Unhandled 0xda");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_db:
				error(COMI_THIS, "Unhandled 0xdb");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_dc:
				error(COMI_THIS, "Unhandled 0xdc");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_dd:
				error(COMI_THIS, "Unhandled 0xdd");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_de:
				error(COMI_THIS, "Unhandled 0xde");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_df:
				error(COMI_THIS, "Unhandled 0xdf");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_e0:
				error(COMI_THIS, "Unhandled 0xe0");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_e1:
				error(COMI_THIS, "Unhandled 0xe1");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_e2:
				error(COMI_THIS, "Unhandled 0xe2");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_e3:
				error(COMI_THIS, "Unhandled 0xe3");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_e4:
				error(COMI_THIS, "Unhandled 0xe4");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_e5:
				error(COMI_THIS, "Unhandled 0xe5");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_e6:
				error(COMI_THIS, "Unhandled 0xe6");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_e7:
				error(COMI_THIS, "Unhandled 0xe7");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_e8:
				error(COMI_THIS, "Unhandled 0xe8");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_e9:
				error(COMI_THIS, "Unhandled 0xe9");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_ea:
				error(COMI_THIS, "Unhandled 0xea");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_eb:
				error(COMI_THIS, "Unhandled 0xeb");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_ec:
				error(COMI_THIS, "Unhandled 0xec");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_ed:
				error(COMI_THIS, "Unhandled 0xed");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_ee:
				error(COMI_THIS, "Unhandled 0xee");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_ef:
				error(COMI_THIS, "Unhandled 0xef");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_f0:
				error(COMI_THIS, "Unhandled 0xf0");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_f1:
				error(COMI_THIS, "Unhandled 0xf1");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_f2:
				error(COMI_THIS, "Unhandled 0xf2");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_f3:
				error(COMI_THIS, "Unhandled 0xf3");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_f4:
				error(COMI_THIS, "Unhandled 0xf4");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_f5:
				error(COMI_THIS, "Unhandled 0xf5");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_f6:
				error(COMI_THIS, "Unhandled 0xf6");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_f7:
				error(COMI_THIS, "Unhandled 0xf7");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_f8:
				error(COMI_THIS, "Unhandled 0xf8");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_f9:
				error(COMI_THIS, "Unhandled 0xf9");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_fa:
				error(COMI_THIS, "Unhandled 0xfa");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_fb:
				error(COMI_THIS, "Unhandled 0xfb");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_fc:
				error(COMI_THIS, "Unhandled 0xfc");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_fd:
				error(COMI_THIS, "Unhandled 0xfd");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_fe:
				error(COMI_THIS, "Unhandled 0xfe");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_ff:
				error(COMI_THIS, "Unhandled 0xff");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
		}
	}

}
