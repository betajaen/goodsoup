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
		debug(COMI_THIS, "%ld : %2lx", _pc-1, (uint32) _opcode);

		switch (_opcode) {
			case OP_00:
				error(COMI_THIS, "Unhandled OP_00");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_pushWord:
				_pushStack(_readUnsignedWord());
			return;
			case OP_pushWordVar:
				_pushStack(readVar(_readUnsignedWord()));
			return;
			case OP_wordArrayRead:
				error(COMI_THIS, "Unhandled OP_wordArrayRead");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_wordArrayIndexedRead:
				error(COMI_THIS, "Unhandled OP_wordArrayIndexedRead");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_dup:
				error(COMI_THIS, "Unhandled OP_dup");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_pop:
				error(COMI_THIS, "Unhandled OP_pop");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_not:
				error(COMI_THIS, "Unhandled OP_not");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_eq: {
				debug_write_unsigned_int(_pc);
				debug_write_str(",");
				int32 left = _popStack();
				int32 right = _popStack();
				_pushStack(left == right ? 1 : 0);
			}
			return;
			case OP_neq:
				error(COMI_THIS, "Unhandled OP_neq");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_gt:
				error(COMI_THIS, "Unhandled OP_gt");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_lt:
				error(COMI_THIS, "Unhandled OP_lt");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_le:
				error(COMI_THIS, "Unhandled OP_le");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_ge:
				error(COMI_THIS, "Unhandled OP_ge");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_add:
				error(COMI_THIS, "Unhandled OP_add");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_sub:
				error(COMI_THIS, "Unhandled OP_sub");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_mul:
				error(COMI_THIS, "Unhandled OP_mul");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_div:
				error(COMI_THIS, "Unhandled OP_div");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_land: {
				int32 a = _popStack();
				int32 b = _popStack();
				_pushStack(a && b);
			}
			return;
			case OP_lor:
				error(COMI_THIS, "Unhandled OP_lor");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_band:
				error(COMI_THIS, "Unhandled OP_band");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_bor:
				error(COMI_THIS, "Unhandled OP_bor");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_mod:
				error(COMI_THIS, "Unhandled OP_mod");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_17:
				error(COMI_THIS, "Unhandled OP_17");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_18:
				error(COMI_THIS, "Unhandled OP_18");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_19:
				error(COMI_THIS, "Unhandled OP_19");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_1a:
				error(COMI_THIS, "Unhandled OP_1a");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_1b:
				error(COMI_THIS, "Unhandled OP_1b");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_1c:
				error(COMI_THIS, "Unhandled OP_1c");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_1d:
				error(COMI_THIS, "Unhandled OP_1d");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_1e:
				error(COMI_THIS, "Unhandled OP_1e");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_1f:
				error(COMI_THIS, "Unhandled OP_1f");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_20:
				error(COMI_THIS, "Unhandled OP_20");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_21:
				error(COMI_THIS, "Unhandled OP_21");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_22:
				error(COMI_THIS, "Unhandled OP_22");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_23:
				error(COMI_THIS, "Unhandled OP_23");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_24:
				error(COMI_THIS, "Unhandled OP_24");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_25:
				error(COMI_THIS, "Unhandled OP_25");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_26:
				error(COMI_THIS, "Unhandled OP_26");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_27:
				error(COMI_THIS, "Unhandled OP_27");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_28:
				error(COMI_THIS, "Unhandled OP_28");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_29:
				error(COMI_THIS, "Unhandled OP_29");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_2a:
				error(COMI_THIS, "Unhandled OP_2a");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_2b:
				error(COMI_THIS, "Unhandled OP_2b");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_2c:
				error(COMI_THIS, "Unhandled OP_2c");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_2d:
				error(COMI_THIS, "Unhandled OP_2d");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_2e:
				error(COMI_THIS, "Unhandled OP_2e");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_2f:
				error(COMI_THIS, "Unhandled OP_2f");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_30:
				error(COMI_THIS, "Unhandled OP_30");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_31:
				error(COMI_THIS, "Unhandled OP_31");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_32:
				error(COMI_THIS, "Unhandled OP_32");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_33:
				error(COMI_THIS, "Unhandled OP_33");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_34:
				error(COMI_THIS, "Unhandled OP_34");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_35:
				error(COMI_THIS, "Unhandled OP_35");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_36:
				error(COMI_THIS, "Unhandled OP_36");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_37:
				error(COMI_THIS, "Unhandled OP_37");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_38:
				error(COMI_THIS, "Unhandled OP_38");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_39:
				error(COMI_THIS, "Unhandled OP_39");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_3a:
				error(COMI_THIS, "Unhandled OP_3a");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_3b:
				error(COMI_THIS, "Unhandled OP_3b");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_3c:
				error(COMI_THIS, "Unhandled OP_3c");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_3d:
				error(COMI_THIS, "Unhandled OP_3d");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_3e:
				error(COMI_THIS, "Unhandled OP_3e");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_3f:
				error(COMI_THIS, "Unhandled OP_3f");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_40:
				error(COMI_THIS, "Unhandled OP_40");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_41:
				error(COMI_THIS, "Unhandled OP_41");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_42:
				error(COMI_THIS, "Unhandled OP_42");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_43:
				error(COMI_THIS, "Unhandled OP_43");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_44:
				error(COMI_THIS, "Unhandled OP_44");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_45:
				error(COMI_THIS, "Unhandled OP_45");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_46:
				error(COMI_THIS, "Unhandled OP_46");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_47:
				error(COMI_THIS, "Unhandled OP_47");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_48:
				error(COMI_THIS, "Unhandled OP_48");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_49:
				error(COMI_THIS, "Unhandled OP_49");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_4a:
				error(COMI_THIS, "Unhandled OP_4a");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_4b:
				error(COMI_THIS, "Unhandled OP_4b");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_4c:
				error(COMI_THIS, "Unhandled OP_4c");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_4d:
				error(COMI_THIS, "Unhandled OP_4d");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_4e:
				error(COMI_THIS, "Unhandled OP_4e");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_4f:
				error(COMI_THIS, "Unhandled OP_4f");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_50:
				error(COMI_THIS, "Unhandled OP_50");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_51:
				error(COMI_THIS, "Unhandled OP_51");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_52:
				error(COMI_THIS, "Unhandled OP_52");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_53:
				error(COMI_THIS, "Unhandled OP_53");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_54:
				error(COMI_THIS, "Unhandled OP_54");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_55:
				error(COMI_THIS, "Unhandled OP_55");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_56:
				error(COMI_THIS, "Unhandled OP_56");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_57:
				error(COMI_THIS, "Unhandled OP_57");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_58:
				error(COMI_THIS, "Unhandled OP_58");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_59:
				error(COMI_THIS, "Unhandled OP_59");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_5a:
				error(COMI_THIS, "Unhandled OP_5a");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_5b:
				error(COMI_THIS, "Unhandled OP_5b");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_5c:
				error(COMI_THIS, "Unhandled OP_5c");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_5d:
				error(COMI_THIS, "Unhandled OP_5d");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_5e:
				error(COMI_THIS, "Unhandled OP_5e");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_5f:
				error(COMI_THIS, "Unhandled OP_5f");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_60:
				error(COMI_THIS, "Unhandled OP_60");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_61:
				error(COMI_THIS, "Unhandled OP_61");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_62:
				error(COMI_THIS, "Unhandled OP_62");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_63:
				error(COMI_THIS, "Unhandled OP_63");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_if: {
				int32 cond = _popStack();
				int32 relOffset = _readWord();
				
				if (cond != 0) {
					_pc += relOffset;
				}
			}
			return;
			case OP_ifNot: {
				int32 cond = _popStack();
				int32 relOffset = _readWord();
				
				if (cond == 0) {
					_pc += relOffset;
				}
			}
			return;
			case OP_jump: {
				int32 relOffset = _readWord();
				_pc += relOffset;
			}
			return;
			case OP_breakHere:
				error(COMI_THIS, "Unhandled OP_breakHere");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_delayFrames:
				error(COMI_THIS, "Unhandled OP_delayFrames");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_wait:
				error(COMI_THIS, "Unhandled OP_wait");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_delay:
				error(COMI_THIS, "Unhandled OP_delay");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_delaySeconds:
				error(COMI_THIS, "Unhandled OP_delaySeconds");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_delayMinutes:
				error(COMI_THIS, "Unhandled OP_delayMinutes");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_writeWordVar:
				error(COMI_THIS, "Unhandled OP_writeWordVar");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_wordVarInc:
				error(COMI_THIS, "Unhandled OP_wordVarInc");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_wordVarDec:
				error(COMI_THIS, "Unhandled OP_wordVarDec");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_dimArray:
				error(COMI_THIS, "Unhandled OP_dimArray");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_wordArrayWrite:
				error(COMI_THIS, "Unhandled OP_wordArrayWrite");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_wordArrayInc:
				error(COMI_THIS, "Unhandled OP_wordArrayInc");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_wordArrayDec:
				error(COMI_THIS, "Unhandled OP_wordArrayDec");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_dim2dimArray:
				error(COMI_THIS, "Unhandled OP_dim2dimArray");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_wordArrayIndexedWrite:
				error(COMI_THIS, "Unhandled OP_wordArrayIndexedWrite");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_arrayOps:
				error(COMI_THIS, "Unhandled OP_arrayOps");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_77:
				error(COMI_THIS, "Unhandled OP_77");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_78:
				error(COMI_THIS, "Unhandled OP_78");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_startScript:
				error(COMI_THIS, "Unhandled OP_startScript");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_startScriptQuick:
				error(COMI_THIS, "Unhandled OP_startScriptQuick");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_stopObjectCode:
				error(COMI_THIS, "Unhandled OP_stopObjectCode");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_stopScript:
				error(COMI_THIS, "Unhandled OP_stopScript");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_jumpToScript:
				error(COMI_THIS, "Unhandled OP_jumpToScript");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_dummy:
				error(COMI_THIS, "Unhandled OP_dummy");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_startObject:
				error(COMI_THIS, "Unhandled OP_startObject");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_stopObjectScript:
				error(COMI_THIS, "Unhandled OP_stopObjectScript");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_cutscene:
				error(COMI_THIS, "Unhandled OP_cutscene");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_endCutscene:
				error(COMI_THIS, "Unhandled OP_endCutscene");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_freezeUnfreeze:
				error(COMI_THIS, "Unhandled OP_freezeUnfreeze");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_beginOverride:
				error(COMI_THIS, "Unhandled OP_beginOverride");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_endOverride:
				error(COMI_THIS, "Unhandled OP_endOverride");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_stopSentence:
				error(COMI_THIS, "Unhandled OP_stopSentence");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_87:
				error(COMI_THIS, "Unhandled OP_87");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_88:
				error(COMI_THIS, "Unhandled OP_88");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_setClass:
				error(COMI_THIS, "Unhandled OP_setClass");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_setState:
				error(COMI_THIS, "Unhandled OP_setState");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_setOwner:
				error(COMI_THIS, "Unhandled OP_setOwner");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_panCameraTo:
				error(COMI_THIS, "Unhandled OP_panCameraTo");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_actorFollowCamera:
				error(COMI_THIS, "Unhandled OP_actorFollowCamera");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_setCameraAt:
				error(COMI_THIS, "Unhandled OP_setCameraAt");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_printActor:
				_decodeParseString(0, 1);
			return;
			case OP_printEgo:
				_pushStack(readVar(VAR_EGO));
				_decodeParseString(0, 1);
			return;
			case OP_talkActor:
				error(COMI_THIS, "Unhandled OP_talkActor");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_talkEgo:
				error(COMI_THIS, "Unhandled OP_talkEgo");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_printLine:
				_decodeParseString(0, 0);
				return;
			case OP_printText:
				_decodeParseString(1, 0);
			return;
			case OP_printDebug:
				_decodeParseString(2, 0);
			return;
			case OP_printSystem:
				_decodeParseString(3, 0);
			return;
			case OP_blastText:
				error(COMI_THIS, "Unhandled OP_blastText");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_drawObject:
				error(COMI_THIS, "Unhandled OP_drawObject");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_99:
				error(COMI_THIS, "Unhandled OP_99");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_9a:
				error(COMI_THIS, "Unhandled OP_9a");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_9b:
				error(COMI_THIS, "Unhandled OP_9b");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_cursorCommand: {
				/* NOT PROPERLY IMPLEMENTED */
				byte param = _readByte();
				warn(COMI_THIS, "Not properly implemented OP_cursorCommand(%ld)", (uint32) param);

				switch (param) {
					case 0xDC:
					break;
					case 0xDD:
					break;
					case 0xDE:
					break;
					case 0xDF:
					break;
					case 0xE0:
					break;
					case 0xE1:
					break;
					case 0xE2:
					break;
					case 0xE3:
					break;
					case 0xE4:
						_popStack();
					break;
					case 0xE5:
						_popStack();
						_popStack();
					break;
					case 0xE6:
						_popStack();
					break;
					case 0xE7:
						_popStack();
					break;
					case 0xE8:
					break;
					case 0xE9:
						_popStack();
						_popStack();
					break;
				}
			}
			return;
			case OP_loadRoom:
				error(COMI_THIS, "Unhandled OP_loadRoom");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_loadRoomWithEgo:
				error(COMI_THIS, "Unhandled OP_loadRoomWithEgo");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_walkActorToObj:
				error(COMI_THIS, "Unhandled OP_walkActorToObj");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_walkActorTo:
				error(COMI_THIS, "Unhandled OP_walkActorTo");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_putActorAtXY:
				error(COMI_THIS, "Unhandled OP_putActorAtXY");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_putActorAtObject:
				error(COMI_THIS, "Unhandled OP_putActorAtObject");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_faceActor:
				error(COMI_THIS, "Unhandled OP_faceActor");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_animateActor:
				error(COMI_THIS, "Unhandled OP_animateActor");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_doSentence:
				error(COMI_THIS, "Unhandled OP_doSentence");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_pickupObject:
				error(COMI_THIS, "Unhandled OP_pickupObject");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_setBoxFlags:
				error(COMI_THIS, "Unhandled OP_setBoxFlags");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_createBoxMatrix:
				error(COMI_THIS, "Unhandled OP_createBoxMatrix");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_a9:
				error(COMI_THIS, "Unhandled OP_a9");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_resourceRoutines:
				error(COMI_THIS, "Unhandled OP_resourceRoutines");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_roomOps:
				error(COMI_THIS, "Unhandled OP_roomOps");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_actorOps:
				error(COMI_THIS, "Unhandled OP_actorOps");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_cameraOps:
				error(COMI_THIS, "Unhandled OP_cameraOps");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_verbOps:
				error(COMI_THIS, "Unhandled OP_verbOps");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_startSound:
				error(COMI_THIS, "Unhandled OP_startSound");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_startMusic:
				error(COMI_THIS, "Unhandled OP_startMusic");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_stopSound:
				error(COMI_THIS, "Unhandled OP_stopSound");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_soundKludge:
				error(COMI_THIS, "Unhandled OP_soundKludge");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_systemOps: {
				byte param = _readByte();

				if (param == SysOps_Quit) {
					CTX->quit = true;
					info(COMI_THIS, "Quit has been called");
					return;
				}

				error(COMI_THIS, "Unhandled SysCall! %ld", (uint32)param);
				_currentContext = NO_CONTEXT;
			}
			return;
			case OP_saveRestoreVerbs:
				error(COMI_THIS, "Unhandled OP_saveRestoreVerbs");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_setObjectName:
				error(COMI_THIS, "Unhandled OP_setObjectName");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getDateTime:
				error(COMI_THIS, "Unhandled OP_getDateTime");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_drawBox:
				error(COMI_THIS, "Unhandled OP_drawBox");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_b8:
				error(COMI_THIS, "Unhandled OP_b8");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_startVideo:
				error(COMI_THIS, "Unhandled OP_startVideo");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_kernelSetFunctions:
				error(COMI_THIS, "Unhandled OP_kernelSetFunctions");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_bb:
				error(COMI_THIS, "Unhandled OP_bb");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_bc:
				error(COMI_THIS, "Unhandled OP_bc");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_bd:
				error(COMI_THIS, "Unhandled OP_bd");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_be:
				error(COMI_THIS, "Unhandled OP_be");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_bf:
				error(COMI_THIS, "Unhandled OP_bf");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_c0:
				error(COMI_THIS, "Unhandled OP_c0");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_c1:
				error(COMI_THIS, "Unhandled OP_c1");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_c2:
				error(COMI_THIS, "Unhandled OP_c2");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_c3:
				error(COMI_THIS, "Unhandled OP_c3");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_c4:
				error(COMI_THIS, "Unhandled OP_c4");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_c5:
				error(COMI_THIS, "Unhandled OP_c5");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_c6:
				error(COMI_THIS, "Unhandled OP_c6");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_c7:
				error(COMI_THIS, "Unhandled OP_c7");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_startScriptQuick2:
				error(COMI_THIS, "Unhandled OP_startScriptQuick2");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_startObjectQuick:
				error(COMI_THIS, "Unhandled OP_startObjectQuick");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_pickOneOf:
				error(COMI_THIS, "Unhandled OP_pickOneOf");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_pickOneOfDefault:
				error(COMI_THIS, "Unhandled OP_pickOneOfDefault");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_cc:
				error(COMI_THIS, "Unhandled OP_cc");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_isAnyOf:
				error(COMI_THIS, "Unhandled OP_isAnyOf");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getRandomNumber:
				error(COMI_THIS, "Unhandled OP_getRandomNumber");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getRandomNumberRange:
				error(COMI_THIS, "Unhandled OP_getRandomNumberRange");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_ifClassOfIs:
				error(COMI_THIS, "Unhandled OP_ifClassOfIs");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getState:
				error(COMI_THIS, "Unhandled OP_getState");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getOwner:
				error(COMI_THIS, "Unhandled OP_getOwner");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_isScriptRunning:
				error(COMI_THIS, "Unhandled OP_isScriptRunning");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_d4:
				error(COMI_THIS, "Unhandled OP_d4");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_isSoundRunning:
				error(COMI_THIS, "Unhandled OP_isSoundRunning");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_abs:
				error(COMI_THIS, "Unhandled OP_abs");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_d7:
				error(COMI_THIS, "Unhandled OP_d7");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_kernelGetFunctions:
				error(COMI_THIS, "Unhandled OP_kernelGetFunctions");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_isActorInBox:
				error(COMI_THIS, "Unhandled OP_isActorInBox");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getVerbEntrypoint:
				error(COMI_THIS, "Unhandled OP_getVerbEntrypoint");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getActorFromXY:
				error(COMI_THIS, "Unhandled OP_getActorFromXY");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_findObject:
				error(COMI_THIS, "Unhandled OP_findObject");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getVerbFromXY:
				error(COMI_THIS, "Unhandled OP_getVerbFromXY");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_de:
				error(COMI_THIS, "Unhandled OP_de");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_findInventory:
				error(COMI_THIS, "Unhandled OP_findInventory");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getInventoryCount:
				error(COMI_THIS, "Unhandled OP_getInventoryCount");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getAnimateVariable:
				error(COMI_THIS, "Unhandled OP_getAnimateVariable");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getActorRoom:
				error(COMI_THIS, "Unhandled OP_getActorRoom");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getActorWalkBox:
				error(COMI_THIS, "Unhandled OP_getActorWalkBox");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getActorMoving:
				error(COMI_THIS, "Unhandled OP_getActorMoving");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getActorCostume:
				error(COMI_THIS, "Unhandled OP_getActorCostume");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getActorScaleX:
				error(COMI_THIS, "Unhandled OP_getActorScaleX");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getActorLayer:
				error(COMI_THIS, "Unhandled OP_getActorLayer");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getActorElevation:
				error(COMI_THIS, "Unhandled OP_getActorElevation");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getActorWidth:
				error(COMI_THIS, "Unhandled OP_getActorWidth");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getObjectNewDir:
				error(COMI_THIS, "Unhandled OP_getObjectNewDir");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getObjectX:
				error(COMI_THIS, "Unhandled OP_getObjectX");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getObjectY:
				error(COMI_THIS, "Unhandled OP_getObjectY");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getActorChore:
				error(COMI_THIS, "Unhandled OP_getActorChore");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_distObjectObject:
				error(COMI_THIS, "Unhandled OP_distObjectObject");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_distPtPt:
				error(COMI_THIS, "Unhandled OP_distPtPt");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getObjectImageX:
				error(COMI_THIS, "Unhandled OP_getObjectImageX");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getObjectImageY:
				error(COMI_THIS, "Unhandled OP_getObjectImageY");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getObjectImageWidth:
				error(COMI_THIS, "Unhandled OP_getObjectImageWidth");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getObjectImageHeight:
				error(COMI_THIS, "Unhandled OP_getObjectImageHeight");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_f4:
				error(COMI_THIS, "Unhandled OP_f4");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_f5:
				error(COMI_THIS, "Unhandled OP_f5");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getStringWidth:
				error(COMI_THIS, "Unhandled OP_getStringWidth");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_getActorZPlane:
				error(COMI_THIS, "Unhandled OP_getActorZPlane");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_f8:
				error(COMI_THIS, "Unhandled OP_f8");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_f9:
				error(COMI_THIS, "Unhandled OP_f9");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_fa:
				error(COMI_THIS, "Unhandled OP_fa");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_fb:
				error(COMI_THIS, "Unhandled OP_fb");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_fc:
				error(COMI_THIS, "Unhandled OP_fc");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_fd:
				error(COMI_THIS, "Unhandled OP_fd");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_fe:
				error(COMI_THIS, "Unhandled OP_fe");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
			case OP_ff:
				error(COMI_THIS, "Unhandled OP_ff");
				CTX->quit = true;
				_currentContext = NO_CONTEXT;
			return;
		}
	}

}
