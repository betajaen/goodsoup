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

#define GS_FILE_NAME "vm_opcodes"

#include "vm_opcodes.h"
#include "vm.h"
#include "globals.h"
#include "debug.h"
#include "vm_array.h"
#include "vm_vars.h"
#include "utils.h"
#include "functions.h"

namespace comi
{
	void startRoom(uint16 roomNum, bool runExitScript, bool runEnterScript);

	static const uint8 NO_CONTEXT = 0xFF;

#if defined(GS_DEBUG)
	#define GS_UNHANDLED_OP\
		do {\
			_dumpState();\
			_forceQuit();\
			error(COMI_THIS, "Unhandled Opcode! %lx 'OP_%s'", _opcode, _getOpcodeName(_opcode));\
		} while(0);
#else
	#define GS_UNHANDLED_OP\
		do {\
			_dumpState();\
			_forceQuit();\
			error(COMI_THIS, "Unhandled Opcode");\
		} while(0);
#endif

	void VirtualMachine::_step() {
		_pcOpcode = _pc;
		_opcode = _readByte();	
		_pcState.opcode = _opcode;

		// debug(COMI_THIS, "%ld : %2lx %s", _pc-1, (uint32) _opcode, _getOpcodeName(_opcode));

		switch (_opcode) {
			case OP_00:
				GS_UNHANDLED_OP;
			return;
			case OP_pushWord:
				_stack.push(_readUnsignedWord());
			return;
			case OP_pushWordVar:
				_stack.push(getVar(_readUnsignedWord()));
			return;
			case OP_wordArrayRead: {
				uint32 base = _stack.pop();
				uint16 arrayNum = _readWord();

				VmArray* array = ARRAYS->findFromNum(arrayNum);
				if (array) {
					int32 value = array->read(0, base);
					_stack.push(value);
				}
				else {
					NO_FEATURE(COMI_THIS, "NULL VmArray (%ld) used with OP_wordArrayRead", (uint32) arrayNum);
					_dumpState();
					_forceQuit();
				}
			}
			return;
			case OP_wordArrayIndexedRead: {
				int32 base = _stack.pop();
				int32 index = _stack.pop();
				uint16 arrayNum = _readWord();

				VmArray* array = ARRAYS->findFromNum(arrayNum);
				if (array) {
					int32 value = array->read(index, base);
					_stack.push(value);
				}
				else {
					NO_FEATURE(COMI_THIS, "NULL VmArray (%ld) used with OP_wordArrayRead", (uint32) arrayNum);
					_dumpState();
					_forceQuit();
				}
			}
			return;
			case OP_dup: {
				int32 value = _stack.pop();
				_stack.push(value);
				_stack.push(value);
			}
			return;
			case OP_pop: {
				_stack.pop();
			}
			return;
			case OP_not: {
				int32 left = _stack.pop();
				_stack.push(left == 0 ? 1 : 0);
			}
			return;
			case OP_eq: {
				int32 right = _stack.pop();
				int32 left = _stack.pop();
				_stack.push(left == right ? 1 : 0);
			}
			return;
			case OP_neq: {
				int32 right = _stack.pop();
				int32 left = _stack.pop();
				_stack.push(left != right ? 1 : 0);
			}
			return;
			case OP_gt: {
				int32 right = _stack.pop();
				int32 left = _stack.pop();
				_stack.push(left > right ? 1 : 0);
			}
			return;
			case OP_lt: {
				int32 right = _stack.pop();
				int32 left = _stack.pop();
				_stack.push(left < right ? 1 : 0);
			}
			return;
			case OP_le: {
				int32 right = _stack.pop();
				int32 left = _stack.pop();
				_stack.push(left <= right ? 1 : 0);
			}
			return;
			case OP_ge: {
				int32 right = _stack.pop();
				int32 left = _stack.pop();
				_stack.push(left >= right ? 1 : 0);
			}
			return;
			case OP_add: {
				int32 right = _stack.pop();
				int32 left = _stack.pop();
				_stack.push(left + right);
			}
			return;
			case OP_sub: {
				int32 right = _stack.pop();
				int32 left = _stack.pop();
				_stack.push(left - right);
			}
			return;
			case OP_mul: {
				int32 right = _stack.pop();
				int32 left = _stack.pop();
				_stack.push(left * right);
			}
			return;
			case OP_div: {
				int32 right = _stack.pop();
				int32 left = _stack.pop();
				_stack.push(left / right);
			}
			return;
			case OP_land: {
				int32 right = _stack.pop();
				int32 left = _stack.pop();
				_stack.push(left && right ? 1 : 0);
			}
			return;
			case OP_lor: {
				int32 right = _stack.pop();
				int32 left = _stack.pop();
				_stack.push(left || right ? 1 : 0);
			}
			return;
			case OP_band: {
				int32 right = _stack.pop();
				int32 left = _stack.pop();
				_stack.push(left & right);
			}
			return;
			case OP_bor: {
				int32 right = _stack.pop();
				int32 left = _stack.pop();
				_stack.push(left | right);
			}
			return;
			case OP_mod: {
				int32 right = _stack.pop();
				int32 left = _stack.pop();
				_stack.push(left % right);
			}
			return;
			case OP_17:
				GS_UNHANDLED_OP;
			return;
			case OP_18:
				GS_UNHANDLED_OP;
			return;
			case OP_19:
				GS_UNHANDLED_OP;
			return;
			case OP_1a:
				GS_UNHANDLED_OP;
			return;
			case OP_1b:
				GS_UNHANDLED_OP;
			return;
			case OP_1c:
				GS_UNHANDLED_OP;
			return;
			case OP_1d:
				GS_UNHANDLED_OP;
			return;
			case OP_1e:
				GS_UNHANDLED_OP;
			return;
			case OP_1f:
				GS_UNHANDLED_OP;
			return;
			case OP_20:
				GS_UNHANDLED_OP;
			return;
			case OP_21:
				GS_UNHANDLED_OP;
			return;
			case OP_22:
				GS_UNHANDLED_OP;
			return;
			case OP_23:
				GS_UNHANDLED_OP;
			return;
			case OP_24:
				GS_UNHANDLED_OP;
			return;
			case OP_25:
				GS_UNHANDLED_OP;
			return;
			case OP_26:
				GS_UNHANDLED_OP;
			return;
			case OP_27:
				GS_UNHANDLED_OP;
			return;
			case OP_28:
				GS_UNHANDLED_OP;
			return;
			case OP_29:
				GS_UNHANDLED_OP;
			return;
			case OP_2a:
				GS_UNHANDLED_OP;
			return;
			case OP_2b:
				GS_UNHANDLED_OP;
			return;
			case OP_2c:
				GS_UNHANDLED_OP;
			return;
			case OP_2d:
				GS_UNHANDLED_OP;
			return;
			case OP_2e:
				GS_UNHANDLED_OP;
			return;
			case OP_2f:
				GS_UNHANDLED_OP;
			return;
			case OP_30:
				GS_UNHANDLED_OP;
			return;
			case OP_31:
				GS_UNHANDLED_OP;
			return;
			case OP_32:
				GS_UNHANDLED_OP;
			return;
			case OP_33:
				GS_UNHANDLED_OP;
			return;
			case OP_34:
				GS_UNHANDLED_OP;
			return;
			case OP_35:
				GS_UNHANDLED_OP;
			return;
			case OP_36:
				GS_UNHANDLED_OP;
			return;
			case OP_37:
				GS_UNHANDLED_OP;
			return;
			case OP_38:
				GS_UNHANDLED_OP;
			return;
			case OP_39:
				GS_UNHANDLED_OP;
			return;
			case OP_3a:
				GS_UNHANDLED_OP;
			return;
			case OP_3b:
				GS_UNHANDLED_OP;
			return;
			case OP_3c:
				GS_UNHANDLED_OP;
			return;
			case OP_3d:
				GS_UNHANDLED_OP;
			return;
			case OP_3e:
				GS_UNHANDLED_OP;
			return;
			case OP_3f:
				GS_UNHANDLED_OP;
			return;
			case OP_40:
				GS_UNHANDLED_OP;
			return;
			case OP_41:
				GS_UNHANDLED_OP;
			return;
			case OP_42:
				GS_UNHANDLED_OP;
			return;
			case OP_43:
				GS_UNHANDLED_OP;
			return;
			case OP_44:
				GS_UNHANDLED_OP;
			return;
			case OP_45:
				GS_UNHANDLED_OP;
			return;
			case OP_46:
				GS_UNHANDLED_OP;
			return;
			case OP_47:
				GS_UNHANDLED_OP;
			return;
			case OP_48:
				GS_UNHANDLED_OP;
			return;
			case OP_49:
				GS_UNHANDLED_OP;
			return;
			case OP_4a:
				GS_UNHANDLED_OP;
			return;
			case OP_4b:
				GS_UNHANDLED_OP;
			return;
			case OP_4c:
				GS_UNHANDLED_OP;
			return;
			case OP_4d:
				GS_UNHANDLED_OP;
			return;
			case OP_4e:
				GS_UNHANDLED_OP;
			return;
			case OP_4f:
				GS_UNHANDLED_OP;
			return;
			case OP_50:
				GS_UNHANDLED_OP;
			return;
			case OP_51:
				GS_UNHANDLED_OP;
			return;
			case OP_52:
				GS_UNHANDLED_OP;
			return;
			case OP_53:
				GS_UNHANDLED_OP;
			return;
			case OP_54:
				GS_UNHANDLED_OP;
			return;
			case OP_55:
				GS_UNHANDLED_OP;
			return;
			case OP_56:
				GS_UNHANDLED_OP;
			return;
			case OP_57:
				GS_UNHANDLED_OP;
			return;
			case OP_58:
				GS_UNHANDLED_OP;
			return;
			case OP_59:
				GS_UNHANDLED_OP;
			return;
			case OP_5a:
				GS_UNHANDLED_OP;
			return;
			case OP_5b:
				GS_UNHANDLED_OP;
			return;
			case OP_5c:
				GS_UNHANDLED_OP;
			return;
			case OP_5d:
				GS_UNHANDLED_OP;
			return;
			case OP_5e:
				GS_UNHANDLED_OP;
			return;
			case OP_5f:
				GS_UNHANDLED_OP;
			return;
			case OP_60:
				GS_UNHANDLED_OP;
			return;
			case OP_61:
				GS_UNHANDLED_OP;
			return;
			case OP_62:
				GS_UNHANDLED_OP;
			return;
			case OP_63:
				GS_UNHANDLED_OP;
			return;
			case OP_if: {
				int32 cond = _stack.pop();
				int32 relOffset = _readWord();
				
				if (cond != 0) {
					_pc += relOffset;
				}
			}
			return;
			case OP_ifNot: {
				int32 cond = _stack.pop();
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
			case OP_breakHere: {
				_break();
			}
			return;
			case OP_delayFrames: {
				ScriptContext& context = _context[CURRENT_CONTEXT];
				if (context._delayFrameCount == 0) {
					context._delayFrameCount = _stack.pop();
				}
				else {
					context._delayFrameCount--;
				}
				if (context._delayFrameCount) {
					_pc--;
					_break();
				}
			}
			return;
			case OP_wait:
				GS_UNHANDLED_OP;
			return;
			case OP_delay: {
				int32 time = _stack.pop();
				_delay(time);
			}
			return;
			case OP_delaySeconds: {
				int32 time = _stack.pop() * 60;
				_delay(time);
			}
			return;
			case OP_delayMinutes: {
				int32 time = _stack.pop() * 3600;
				_delay(time);
			}
			return;
			case OP_writeWordVar: {
				uint32 varWhere = _readUnsignedWord();
				int32 value = _stack.pop();
				setVar(varWhere, value);
			}
			return;
			case OP_wordVarInc: {
				uint32 varNum = _readUnsignedWord();
				int32 var = getVar(varNum);
				var++;
				setVar(varNum, var);
			}
			return;
			case OP_wordVarDec: {
				uint32 varNum = _readUnsignedWord();
				int32 var = getVar(varNum);
				var--;
				setVar(varNum, var);
			}
			return;
			case OP_dimArray: {
				byte subOp = _readByte();
				int32 arrayNum = _readUnsignedWord();
				int32 size;

				switch (subOp) {
					case DimArrayOp_NewInt:
						size = _stack.pop();
						newArray(arrayNum, AK_Int, size, 0);
					return;
					case DimArrayOp_NewString:
						size = _stack.pop();
						newArray(arrayNum, AK_String, size, 0);
					return;
					case DimArrayOp_Delete:
						deleteArray(arrayNum);
					return;
				}
				
				NO_FEATURE(COMI_THIS, "Not implemented OP_dimArray(%ld,%ld)", (uint32) subOp, (uint32) arrayNum);
				_dumpState();
				_forceQuit();
			}
			return;
			case OP_wordArrayWrite: {
				uint16 arrayNum = _readWord();
				int32 value = _stack.pop();
				int32 base = _stack.pop();

				VmArray* array = ARRAYS->findFromNum(arrayNum);
				if (array) {
					array->write(value, 0, base);
				}
				else {
					NO_FEATURE(COMI_THIS, "NULL VmArray (%ld) used with OP_wordArrayWrite", (uint32) arrayNum);
					_dumpState();
					_forceQuit();
				}
			}
			return;
			case OP_wordArrayInc:
				GS_UNHANDLED_OP;
			return;
			case OP_wordArrayDec:
				GS_UNHANDLED_OP;
			return;
			case OP_dim2dimArray: {
				byte subOp = _readByte();
				uint16 arrayNum = _readWord();

				switch (subOp) {
					case Dim2DimOp_Int: {
						uint16 y = _stack.pop();
						uint16 x = _stack.pop();
						newArray(arrayNum, VAK_Integer, y, x);
					}
					return;
					case Dim2DimOp_String: {
						uint16 y = _stack.pop();
						uint16 x = _stack.pop();
						newArray(arrayNum, VAK_String, y, x);
					}
					return;
					case Dim2DimOp_Delete: {
						deleteArray(arrayNum);
					}
					return;
				}

				NO_FEATURE(COMI_THIS, "Not implemented OP_dim2dimArray(%ld,%ld)", (uint32) subOp, (uint32) arrayNum);
				_dumpState();
				_forceQuit();
			}
			return;
			case OP_wordArrayIndexedWrite: {

				int32 value = _stack.pop();
				int32 base = _stack.pop();
				int32 index = _stack.pop();
				uint16 arrayNum = _readWord();

				VmArray* array = ARRAYS->findFromNum(arrayNum);
				if (array) {
					array->write(value, index, base);
				}
				else {
					NO_FEATURE(COMI_THIS, "NULL VmArray (%ld) used with OP_wordArrayIndexedWrite", (uint32) arrayNum);
					_dumpState();
					_forceQuit();
				}

			}
			return;
			case OP_arrayOps: {
				byte subOp = _readByte();
				uint32 arrayNum = _readUnsignedWord();
				VmArray* array;
				switch (subOp) {
					case ArrayOps_AssignString: {
						uint16 offset = _stack.pop();
						uint16 from, len;
						_readStringLength(from, len);
						array = newArray(arrayNum, VAK_String, len, 0);
						array->writeBytes(
							_script.ptr(from),
							offset,
							len
						);
					}
					return;
					case ArrayOps_AssignScummVarList: {
						/* TODO */
						uint16 offset = _stack.pop();
						uint16 num = _stack.readList(128);
						VmArray* array = ARRAYS->findFromNum(arrayNum);
						
						if (array) {
							array->writeFromCArray(0, offset, _stack.getList(), num);
						}
						else {
							error(COMI_THIS, "NULL VmArray (%ld) used with OP_arrayOps ArrayOps_AssignScummVarList", (uint32) arrayNum);
							_dumpState();
							_forceQuit();
						}

					}
					return;
					case ArrayOps_Assign2DimList: {
						uint16 offset = _stack.pop();
						uint16 len = _stack.readList(128);
						VmArray* array = ARRAYS->findFromNum(arrayNum);

						if (array) {
							int32* list = _stack.getList();
							uint16 index = _stack.pop();
							for(uint16 i=0;i < len;i++) {
								array->write(list[i], index, offset + i);
							}
						}
						else {
							error(COMI_THIS, "NULL VmArray (%ld) used with OP_arrayOps ArrayOps_AssignScummVarList", (uint32) arrayNum);
							_dumpState();
							_forceQuit();
						}
					}
					return;
				}

				NO_FEATURE(COMI_THIS, "Not implemented OP_arrayOps (%ld, %ld)", (uint32) subOp, (uint32) arrayNum);
				_dumpState();
				_forceQuit();
			}
			return;
			case OP_77:
				GS_UNHANDLED_OP;
			return;
			case OP_78:
				GS_UNHANDLED_OP;
			return;
			case OP_startScript: {
				uint32 script, flags;

				uint8 count = _stack.readList(25);
				script = _stack.pop();
				flags = _stack.pop();

				runScript(script, (flags & 1) !=0, (flags & 2) !=0, _stack.getList(), count);
			}
			return;
			case OP_startScriptQuick: {
				uint32 script, flags;

				uint8 count = _stack.readList(25);
				script = _stack.pop();

				runScript(script, false, true, _stack.getList(), count);
			}
			return;
			case OP_stopObjectCode: {
				_stopObjectCode();
			}
			return;
			case OP_stopScript: {
				uint32 scriptNum = _stack.pop();
				debug(COMI_THIS, "** %ld", scriptNum);
				if (scriptNum == 0) {
					_stopObjectCode();
				}
				else {
					_stopScript(scriptNum);
				}
			}
			return;
			case OP_jumpToScript:
				GS_UNHANDLED_OP;
			return;
			case OP_dummy:
				GS_UNHANDLED_OP;
			return;
			case OP_startObject: {
				uint16 num = _stack.readList(25);
				uint32 entryPc = _stack.pop();
				uint16 scriptNum = _stack.pop();
				uint16 flags = _stack.pop();
				
				runObjectScript(scriptNum, entryPc, (flags & 1) !=0, (flags & 2) !=0, _stack.getList(), num);
			}
			return;
			case OP_stopObjectScript:
				GS_UNHANDLED_OP;
			return;
			case OP_cutscene:
				GS_UNHANDLED_OP;
			return;
			case OP_endCutscene:
				GS_UNHANDLED_OP;
			return;
			case OP_freezeUnfreeze:
				GS_UNHANDLED_OP;
			return;
			case OP_beginOverride:
				GS_UNHANDLED_OP;
			return;
			case OP_endOverride:
				GS_UNHANDLED_OP;
			return;
			case OP_stopSentence:
				GS_UNHANDLED_OP;
			return;
			case OP_87:
				GS_UNHANDLED_OP;
			return;
			case OP_88:
				GS_UNHANDLED_OP;
			return;
			case OP_setClass: {
				int16 num = _stack.readList(16);
				int32 obj = _stack.pop();

				NO_FEATURE(COMI_THIS, "Not implemented OP_setClass (%ld, %ld)", num, obj);
			}
			return;
			case OP_setState:
				GS_UNHANDLED_OP;
			return;
			case OP_setOwner:
				GS_UNHANDLED_OP;
			return;
			case OP_panCameraTo:
				GS_UNHANDLED_OP;
			return;
			case OP_actorFollowCamera:
				GS_UNHANDLED_OP;
			return;
			case OP_setCameraAt:
				GS_UNHANDLED_OP;
			return;
			case OP_printActor:
				_decodeParseString(0, 1);
			return;
			case OP_printEgo:
				_stack.push(INTS->ego);
				_decodeParseString(0, 1);
			return;
			case OP_talkActor:
				GS_UNHANDLED_OP;
			return;
			case OP_talkEgo:
				GS_UNHANDLED_OP;
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
				GS_UNHANDLED_OP;
			return;
			case OP_drawObject:
				GS_UNHANDLED_OP;
			return;
			case OP_99:
				GS_UNHANDLED_OP;
			return;
			case OP_9a:
				GS_UNHANDLED_OP;
			return;
			case OP_9b:
				GS_UNHANDLED_OP;
			return;
			case OP_cursorCommand: {
				
				byte param = _readByte();

				switch (param) {
					case CursorCommandOp_CursorOn:
						NO_FEATURE(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_CursorOn");
					return;
					case CursorCommandOp_CursorOff:
						NO_FEATURE(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_CursorOff");
					return;
					case CursorCommandOp_SoftCursorOn:
						NO_FEATURE(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_SoftCursorOn");
					return;
					case CursorCommandOp_SoftCursorOff:
						NO_FEATURE(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_SoftCursorOff");
					return;
					case CursorCommandOp_UserPutOn:
						NO_FEATURE(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_UserPutOn");
					return;
					case CursorCommandOp_UserPutOff:
						NO_FEATURE(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_UserPutOff");
					return;
					case CursorCommandOp_SoftUserPutOn:
						NO_FEATURE(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_SoftUserPutOn");
					return;
					case CursorCommandOp_SoftUserPutOff:
						NO_FEATURE(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_SoftUserPutOff");
					return;
					case CursorCommandOp_CursorImage:
						_stack.pop();
						NO_FEATURE(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_CursorImage");
					return;
					case CursorCommandOp_HotSpot:
						_stack.pop();
						_stack.pop();
						NO_FEATURE(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_HotSpot");
					return;
					case CursorCommandOp_Transparency:
						_stack.pop();
						NO_FEATURE(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_Transparency");
					return;
					case CursorCommandOp_CharsetSet:
						_stack.pop();
						NO_FEATURE(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_CharsetSet");
					return;
					case CursorCommandOp_CharsetColour:
						NO_FEATURE(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_CharsetColour");
					return;
					case CursorCommandOp_CursorPut:
						_stack.pop();
						_stack.pop();
						NO_FEATURE(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_CursorPut");
					return;
				}

				NO_FEATURE(COMI_THIS, "Not implemented OP_cursorCommand(%ld)", (uint32) param);
				_dumpState();
				_forceQuit();
			}
			return;
			case OP_loadRoom: {
				uint16 roomNum = _stack.pop();
				startRoom(roomNum, true, true);
			}
			return;
			case OP_loadRoomWithEgo:
				GS_UNHANDLED_OP;
			return;
			case OP_walkActorToObj:
				GS_UNHANDLED_OP;
			return;
			case OP_walkActorTo:
				GS_UNHANDLED_OP;
			return;
			case OP_putActorAtXY: {

				int32 roomNum, actorNum, x, y;

				roomNum = _stack.pop();
				y = _stack.pop();
				x = _stack.pop();
				actorNum = _stack.pop();

				NO_FEATURE(COMI_THIS, "Not implemented OP_putActorAtXY (%ld, %ld, %ld, %ld)", roomNum, x, y, actorNum);
			}
			return;
			case OP_putActorAtObject:
				GS_UNHANDLED_OP;
			return;
			case OP_faceActor:
				GS_UNHANDLED_OP;
			return;
			case OP_animateActor: {
				uint16 animationNum = _stack.pop();
				uint16 actorNum = _stack.pop();
				
				NO_FEATURE(COMI_THIS, "Not implemented OP_animateActor (%ld, %ld)", (uint32) animationNum, (uint32) actorNum);
			}
			return;
			case OP_doSentence:
				GS_UNHANDLED_OP;
			return;
			case OP_pickupObject:
				GS_UNHANDLED_OP;
			return;
			case OP_setBoxFlags:
				GS_UNHANDLED_OP;
			return;
			case OP_createBoxMatrix:
				GS_UNHANDLED_OP;
			return;
			case OP_a9:
				GS_UNHANDLED_OP;
			return;
			case OP_resourceRoutines: {
				byte  subOp = _readByte();
				int32 resId = _stack.pop();

				switch (subOp) {
					case ResourceRoutineOp_Dummy:
						NO_FEATURE(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_Dummy");
					return;
					case ResourceRoutineOp_LoadCostume:
						NO_FEATURE(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_LoadCostume");
					return;
					case ResourceRoutineOp_LoadObject:
						NO_FEATURE(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_LoadObject");
					return;
					case ResourceRoutineOp_LoadRoom:
						NO_FEATURE(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_LoadRoom");
					return;
					case ResourceRoutineOp_LoadScript:
						NO_FEATURE(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_LoadScript");
					return;
					case ResourceRoutineOp_LoadSound:
						NO_FEATURE(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_LoadSound");
					return;
					case ResourceRoutineOp_LockCostume:
						NO_FEATURE(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_LockCostume");
					return;
					case ResourceRoutineOp_LockRoom:
						NO_FEATURE(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_LockRoom");
					return;
					case ResourceRoutineOp_LockScript:
						NO_FEATURE(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_LockScript");
					return;
					case ResourceRoutineOp_LockSound:
						NO_FEATURE(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_LockSound");
					return;
					case ResourceRoutineOp_UnlockCostume:
						NO_FEATURE(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_UnlockCostume");
					return;
					case ResourceRoutineOp_UnlockRoom:
						NO_FEATURE(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_UnlockRoom");
					return;
					case ResourceRoutineOp_UnlockScript:
						NO_FEATURE(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_UnlockScript");
					return;
					case ResourceRoutineOp_UnlockSound:
						NO_FEATURE(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_UnlockSound");
					return;
					case ResourceRoutineOp_SetResourceCounterCostume:
						NO_FEATURE(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_SetResourceCounterCostume");
					return;
					case ResourceRoutineOp_SetResourceCounterRoom:
						NO_FEATURE(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_SetResourceCounterRoom");
					return;
					case ResourceRoutineOp_SetResourceCounterScript:
						NO_FEATURE(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_SetResourceCounterScript");
					return;
					case ResourceRoutineOp_SetResourceCounterSound:
						NO_FEATURE(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_SetResourceCounterSound");
					return;
				}


				NO_FEATURE(COMI_THIS, "Not implemented OP_resourceRoutines(%ld,%ld)", (uint32) subOp, (uint32) resId);
				_dumpState();
				_forceQuit();

			}
			return;
			case OP_roomOps: {

				byte subOp = _readByte();

				switch (subOp) {
					case RoomOp_SetColour:
						_stack.pop();
						_stack.pop();
						_stack.pop();
						_stack.pop();
						NO_FEATURE(COMI_THIS, "Not implemented OP_roomOps RoomOp_SetColour");
					return;
					case RoomOp_FadePalette:
						_stack.pop();
						NO_FEATURE(COMI_THIS, "Not implemented OP_roomOps RoomOp_FadePalette");
					return;
					case RoomOp_DarkenPalette:
						_stack.pop();
						_stack.pop();
						_stack.pop();
						_stack.pop();
						_stack.pop();
						NO_FEATURE(COMI_THIS, "Not implemented OP_roomOps RoomOp_DarkenPalette");
					return;
					case RoomOp_PaletteManipulate:
						_stack.pop();
						_stack.pop();
						_stack.pop();
						_stack.pop();
						NO_FEATURE(COMI_THIS, "Not implemented OP_roomOps RoomOp_PaletteManipulate");
					return;
					case RoomOp_SetPalette:
						_stack.pop();
						NO_FEATURE(COMI_THIS, "Not implemented OP_roomOps RoomOp_SetPalette");
					return;
					case RoomOp_SaveGame:
						NO_FEATURE(COMI_THIS, "Not implemented OP_roomOps RoomOp_SaveGame");
					return;
					case RoomOp_LoadGame:
						NO_FEATURE(COMI_THIS, "Not implemented OP_roomOps RoomOp_LoadGame");
					return;
					case RoomOp_DesaturatePalette:
						_stack.pop();
						_stack.pop();
						_stack.pop();
						_stack.pop();
						_stack.pop();
						NO_FEATURE(COMI_THIS, "Not implemented OP_roomOps RoomOp_DesaturatePalette");
					return;
				}

				error(COMI_THIS, "Not implemented OP_roomOps(%ld)", (uint32) subOp);
				_dumpState();
				_forceQuit();
			}
			return;
			case OP_actorOps: {
				byte subOp = _readByte();
				switch(subOp) {
					case ActorOp_SetCostume:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetCostume");
					return;
					case ActorOp_SetWalkSpeed:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetWalkSpeed");
					return;
					case ActorOp_SetAnimationDefault:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetAnimationDefault");
					return;
					case ActorOp_InitAnimation:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_InitAnimation");
					return;
					case ActorOp_SetAnimationTalk:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetAnimationTalk");
					return;
					case ActorOp_SetAnimationWalk:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetAnimationWalk");
					return;
					case ActorOp_SetAnimationStand:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetAnimationStand");
					return;
					case ActorOp_SetAnimationSpeed:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetAnimationSpeed");
					return;
					case ActorOp_Default:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_Default");
					return;
					case ActorOp_SetElevation:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetElevation");
					return;
					case ActorOp_SetPalette:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetPalette");
					return;
					case ActorOp_SetTalkColour:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetTalkColour");
					return;
					case ActorOp_SetActorName:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetActorName");
					return;
					case ActorOp_SetActorWidth:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetActorWidth");
					return;
					case ActorOp_SetActorScale:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetActorScale");
					return;
					case ActorOp_SetNeverZClip:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetNeverZClip");
					return;
					case ActorOP_SetAlwaysZClip:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOP_SetAlwaysZClip");
					return;
					case ActorOp_SetIgnoreBoxes:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetIgnoreBoxes");
					return;
					case ActorOp_SetFollowBoxes:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetFollowBoxes");
					return;
					case ActorOp_SetSpecialDraw:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetSpecialDraw");
					return;
					case ActorOp_SetTextOffset:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetTextOffset");
					return;
					case ActorOp_Init:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_Init");
					return;
					case ActorOp_SetActorVariable:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetActorVariable");
					return;
					case ActorOp_SetIgnoreTurnsOn:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetIgnoreTurnsOn");
					return;
					case ActorOp_SetIgnoreTurnsOff:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetIgnoreTurnsOff");
					return;
					case ActorOp_ActorNew:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_ActorNew");
					return;
					case ActorOp_SetActorZ:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetActorZ");
					return;
					case ActorOp_ActorStop:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_ActorStop");
					return;
					case ActorOp_SetAngle:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetAngle");
					return;
					case ActorOp_TurnAngle:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_TurnAngle");
					return;
					case ActorOp_SetWalkScript:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetWalkScript");
					return;
					case ActorOp_SetTalkScript:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetTalkScript");
					return;
					case ActorOp_WalkPause:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_WalkPause");
					return;
					case ActorOp_WalkResume:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_WalkResume");
					return;
					case ActorOp_SetTalkVolume:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetTalkVolume");
					return;
					case ActorOp_SetTalkFrequency:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetTalkFrequency");
					return;
					case ActorOp_SetActorPan:
						NO_FEATURE(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetActorPan");
					return;
				}
			}
			return;
			case OP_cameraOps:
				GS_UNHANDLED_OP;
			return;
			case OP_verbOps: {
				byte subOp = _readByte();

				switch (subOp) {
					case VerbOp_Init:
						_stack.pop();
						NO_FEATURE(COMI_THIS, "Not implemented OP_verbOps VerbOp_Init");
					return;
					case VerbOp_New:
						NO_FEATURE(COMI_THIS, "Not implemented OP_verbOps VerbOp_New");
					return;
					case VerbOp_Delete:
						NO_FEATURE(COMI_THIS, "Not implemented OP_verbOps VerbOp_Delete");
					return;
					case VerbOp_SetName:
						NO_FEATURE(COMI_THIS, "Not implemented OP_verbOps VerbOp_SetName");
					return;
					case VerbOp_SetPosition:
						_stack.pop();
						_stack.pop();
						NO_FEATURE(COMI_THIS, "Not implemented OP_verbOps VerbOp_SetPosition");
					return;
					case VerbOp_Enable:
						NO_FEATURE(COMI_THIS, "Not implemented OP_verbOps VerbOp_Enable");
					return;
					case VerbOp_Disable:
						NO_FEATURE(COMI_THIS, "Not implemented OP_verbOps VerbOp_Disable");
					return;
					case VerbOp_SetColour:
						_stack.pop();
						NO_FEATURE(COMI_THIS, "Not implemented OP_verbOps VerbOp_SetColour");
					return;
					case VerbOp_SetHilightColour:
						_stack.pop();
						NO_FEATURE(COMI_THIS, "Not implemented OP_verbOps VerbOp_SetHilightColour");
					return;
					case VerbOp_SetDimmedColour:
						_stack.pop();
						NO_FEATURE(COMI_THIS, "Not implemented OP_verbOps VerbOp_SetDimmedColour");
					return;
					case VerbOp_Dim:
						NO_FEATURE(COMI_THIS, "Not implemented OP_verbOps VerbOp_Dim");
					return;
					case VerbOp_SetKey:
						_stack.pop();
						NO_FEATURE(COMI_THIS, "Not implemented OP_verbOps VerbOp_SetKey");
					return;
					case VerbOp_SetImage:
						_stack.pop();
						_stack.pop();
						NO_FEATURE(COMI_THIS, "Not implemented OP_verbOps VerbOp_SetImage");
					return;
					case VerbOp_SetNameString:
						_stack.pop();
						NO_FEATURE(COMI_THIS, "Not implemented OP_verbOps VerbOp_SetNameString");
					return;
					case VerbOp_Centre:
						NO_FEATURE(COMI_THIS, "Not implemented OP_verbOps VerbOp_Centre");
					return;
					case VerbOp_SetCharSet:
						_stack.pop();
						NO_FEATURE(COMI_THIS, "Not implemented OP_verbOps VerbOp_SetCharSet");
					return;
					case VerbOp_SetLineSpacing:
						_stack.pop();
						NO_FEATURE(COMI_THIS, "Not implemented OP_verbOps VerbOp_SetLineSpacing");
					return;
				}

				NO_FEATURE(COMI_THIS, "Not implemented OP_verbOps(%ld)", (uint32) subOp);
				_dumpState();
				_forceQuit();
			}
			return;
			case OP_startSound:
				GS_UNHANDLED_OP;
			return;
			case OP_startMusic:
				GS_UNHANDLED_OP;
			return;
			case OP_stopSound: {
				uint16 soundNum = _stack.pop();
				NO_FEATURE(COMI_THIS, "Not implemented OP_stopSound %ld", soundNum);
			}
			return;
			case OP_soundKludge: {

				uint16 num = _stack.readList(16);

				NO_FEATURE(COMI_THIS, "Not implemented OP_soundKludge %ld", num);

				/* TODO: WORKAROUND for bug #1398195 */
				NO_FEATURE(COMI_THIS, "Not implemented WORKAROUND for bug #1398195");
			}
			return;
			case OP_systemOps: {
				byte param = _readByte();

				if (param == SystemOps_Quit) {
					_forceQuit();
					info(COMI_THIS, "Quit has been called!");
					return;
				}

				NO_FEATURE(COMI_THIS, "Not implemented SysCall! %ld", (uint32)param);
				
				/* UNHANDLED */
			}
			return;
			case OP_saveRestoreVerbs:
				GS_UNHANDLED_OP;
			return;
			case OP_setObjectName:
				GS_UNHANDLED_OP;
			return;
			case OP_getDateTime:
				GS_UNHANDLED_OP;
			return;
			case OP_drawBox:
				GS_UNHANDLED_OP;
			return;
			case OP_b8:
				GS_UNHANDLED_OP;
			return;
			case OP_startVideo:
				GS_UNHANDLED_OP;
			return;
			case OP_kernelSetFunctions: {

				uint8 length = _stack.readList(30);
				byte subOp = _stack.getListItem(0);

				switch(subOp) {

					case KernelSetOp_LockObject:
						NO_FEATURE(COMI_THIS, "Not implemented KernelSetOp_LockObject");
					return;
					case KernelSetOp_UnlockObject:
						NO_FEATURE(COMI_THIS, "Not implemented KernelSetOp_UnlockObject");
					return;
					case KernelSetOp_RemapCostume:
						NO_FEATURE(COMI_THIS, "Not implemented KernelSetOp_RemapCostume");
					return;
					case KernelSetOp_RemapCostumeInert:
						NO_FEATURE(COMI_THIS, "Not implemented KernelSetOp_RemapCostumeInert");
					return;
					case KernelSetOp_Unused_0xF:
						/* Legacy */
					return;
					case KernelSetOp_SetBoxScaleSlot:
						NO_FEATURE(COMI_THIS, "Not implemented KernelSetOp_SetBoxScaleSlot");
					return;
					case KernelSetOp_SetScaleSlot:
						NO_FEATURE(COMI_THIS, "Not implemented KernelSetOp_SetScaleSlot");
					return;
					case KernelSetOp_SetBannerColours:
						NO_FEATURE(COMI_THIS, "Not implemented KernelSetOp_SetBannerColours");
					return;
					case KernelSetOp_SetActorChoreLimbFrame:
						NO_FEATURE(COMI_THIS, "Not implemented KernelSetOp_SetActorChoreLimbFrame");
					return;
					case KernelSetOp_ClearTextQueue:
						NO_FEATURE(COMI_THIS, "Not implemented KernelSetOp_ClearTextQueue");
					return;
					case KernelSetOp_Unused_0x1A:
					case KernelSetOp_Unused_0x1B:
					case KernelSetOp_Unused_0x1C:
					case KernelSetOp_Unused_0x1D: {
						/* Unused Save Game Functionality */
					}
					return;
					case KernelSetOp_SetKeyScript: {
						NO_FEATURE(COMI_THIS, "Not implemented KernelSetOp_SetKeyScript");
					}
					return;
					case KernelSetOp_KillAllScriptsExceptCurrent:
						NO_FEATURE(COMI_THIS, "Not implemented KernelSetOp_KillAllScriptsExceptCurrent");
					return;
					case KernelSetOp_StopAllVideo:
						NO_FEATURE(COMI_THIS, "Not implemented KernelSetOp_StopAllVideo");
					return;
					case KernelSetOp_WriteRegistryValue:
						NO_FEATURE(COMI_THIS, "Not implemented KernelSetOp_WriteRegistryValue");
					return;
					case KernelSetOp_QueryQuit:
						NO_FEATURE(COMI_THIS, "Not implemented KernelSetOp_QueryQuit");
					return;
					case KernelSetOp_BuildShadowPalette:
						NO_FEATURE(COMI_THIS, "Not implemented KernelSetOp_BuildShadowPalette");
					return;
					case KernelSetOp_SetShadowPalette:
						NO_FEATURE(COMI_THIS, "Not implemented KernelSetOp_SetShadowPalette");
					return;
					case KernelSetOp_BlastShadowObject:
						NO_FEATURE(COMI_THIS, "Not implemented KernelSetOp_BlastShadowObject");
					return;
					case KernelSetOp_SuperBlastObject:
						NO_FEATURE(COMI_THIS, "Not implemented KernelSetOp_SuperBlastObject");
					return;
				}

				_dumpState();
				_forceQuit();
				NO_FEATURE(COMI_THIS, "Not implemented KernelSetFunctions(%ld, %ld)", (uint32) subOp, length);
			}
			return;
			case OP_bb:
				GS_UNHANDLED_OP;
			return;
			case OP_bc:
				GS_UNHANDLED_OP;
			return;
			case OP_bd:
				GS_UNHANDLED_OP;
			return;
			case OP_be:
				GS_UNHANDLED_OP;
			return;
			case OP_bf:
				GS_UNHANDLED_OP;
			return;
			case OP_c0:
				GS_UNHANDLED_OP;
			return;
			case OP_c1:
				GS_UNHANDLED_OP;
			return;
			case OP_c2:
				GS_UNHANDLED_OP;
			return;
			case OP_c3:
				GS_UNHANDLED_OP;
			return;
			case OP_c4:
				GS_UNHANDLED_OP;
			return;
			case OP_c5:
				GS_UNHANDLED_OP;
			return;
			case OP_c6:
				GS_UNHANDLED_OP;
			return;
			case OP_c7:
				GS_UNHANDLED_OP;
			return;
			case OP_startScriptQuick2:
				GS_UNHANDLED_OP;
			return;
			case OP_startObjectQuick:
				GS_UNHANDLED_OP;
			return;
			case OP_pickOneOf:
				GS_UNHANDLED_OP;
			return;
			case OP_pickOneOfDefault:
				GS_UNHANDLED_OP;
			return;
			case OP_cc:
				GS_UNHANDLED_OP;
			return;
			case OP_isAnyOf: {
				int16 num = _stack.readList(100);
				int32 val = _stack.pop();

				while (--num >= 0) {
					if (_stack.getListItem(num) == val) {
						_stack.push(1);
						return;
					}
				}
				
				_stack.push(0);
			}
			return;
			case OP_getRandomNumber: {
				uint32 max = _stack.pop();
				uint32 num = getRandom(max);
				_stack.push(num);
			}
			return;
			case OP_getRandomNumberRange: {
				uint32 max = _stack.pop();
				uint32 min = _stack.pop();
				uint32 num = getRandomRange(min, max);
				_stack.push(num);
			}
			return;
			case OP_ifClassOfIs: {
				uint16 num = _stack.readList(16);
				uint16 obj = _stack.pop();

				_stack.push(0);
				NO_FEATURE(COMI_THIS, "Not implemented OP_ifClassOfIs");
			}
			return;
			case OP_getState:
				GS_UNHANDLED_OP;
			return;
			case OP_getOwner:
				GS_UNHANDLED_OP;
			return;
			case OP_isScriptRunning:
				GS_UNHANDLED_OP;
			return;
			case OP_d4:
				GS_UNHANDLED_OP;
			return;
			case OP_isSoundRunning:
				GS_UNHANDLED_OP;
			return;
			case OP_abs:
				GS_UNHANDLED_OP;
			return;
			case OP_d7:
				GS_UNHANDLED_OP;
			return;
			case OP_kernelGetFunctions: {
				uint16 len = _stack.readList(30);
				byte opcode = _stack.getListItem(0);

				switch (opcode) {
					case KernelGetOp_GetRGBSlot: {
						NO_FEATURE(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetRGBSlot");
						_stack.push(0);
					}
					return;
					case KernelGetOp_GetKeyState: {
						NO_FEATURE(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetKeyState");
						_stack.push(0);
					}
					return;
					case KernelGetOp_CheckXYInBoxBounds: {
						NO_FEATURE(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetBox");
						_stack.push(0);
					}
					return;
					case KernelGetOp_FindBlastObject: {
						NO_FEATURE(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_FindBlastObject");
						_stack.push(0);
					}
					return;
					case KernelGetOp_TestActorHit: {
						NO_FEATURE(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_TestActorHit");
						_stack.push(0);
					}
					return;
					case KernelGetOp_GetLipSyncWidth: {
						NO_FEATURE(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetLipSyncWidth");
						_stack.push(0);
					}
					return;
					case KernelGetOp_GetLipSyncHeight: {
						NO_FEATURE(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetLipSyncHeight");
						_stack.push(0);
					}
					return;
					case KernelGetOp_GetTalkAnimation: {
						NO_FEATURE(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetTalkAnimation");
						_stack.push(0);
					}
					return;
					case KernelGetOp_GetGroupSfxVolume: {
						NO_FEATURE(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetGroupSfxVolume");
						_stack.push(0);
					}
					return;
					case KernelGetOp_GetGroupVoiceVolume: {
						NO_FEATURE(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetGroupVoiceVolume");
						_stack.push(0);
					}
					return;
					case KernelGetOp_GetGroupMusicVolume: {
						NO_FEATURE(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetGroupMusicVolume");
						_stack.push(0);
					}
					return;
					case KernelGetOp_ReadRegistryValue: {
						NO_FEATURE(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_ReadRegistryValue");
						_stack.push(-1);
					}
					return;
					case KernelGetOp_ImGetMusicPosition: {
						NO_FEATURE(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_ImGetMusicPosition");
						_stack.push(0);
					}
					return;
					case KernelGetOp_MusicLipGetSyncWidth: {
						NO_FEATURE(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_MusicLipGetSyncWidth");
						_stack.push(0);
					}
					return;
					case KernelGetOp_MusicLipGetSyncHeight: {
						NO_FEATURE(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_MusicLipGetSyncHeight");
						_stack.push(0);
					}
					return;
					case KernelGetOp_GetWalkBoxAt: {
						NO_FEATURE(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetWalkBoxAt");
						_stack.push(-1);
					}
					return;
					case KernelGetOp_IsPointInBox: {
						NO_FEATURE(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_IsPointInBox");
						_stack.push(0);
					}
					return;
				}
				_dumpState();
				_forceQuit();
				NO_FEATURE(COMI_THIS, "Not implemented OP_kernelGetFunctions(%ld)", (uint32) opcode);
			}
			return;
			case OP_isActorInBox:
				GS_UNHANDLED_OP;
			return;
			case OP_getVerbEntrypoint:
				GS_UNHANDLED_OP;
			return;
			case OP_getActorFromXY: {
				_stack.pop();
				_stack.pop();
				_stack.push(0);
				NO_FEATURE(COMI_THIS, "Not implemented OP_getActorFromXY");
			}
			return;
			case OP_findObject: {
				_stack.pop();
				_stack.pop();
				_stack.push(0);
				NO_FEATURE(COMI_THIS, "Not implemented OP_findObject");
			}
			return;
			case OP_getVerbFromXY: {
				_stack.pop();
				_stack.pop();
				_stack.push(0);
				NO_FEATURE(COMI_THIS, "Not implemented OP_getVerbFromXY");
			}
			return;
			case OP_de:
				GS_UNHANDLED_OP;
			return;
			case OP_findInventory:
				GS_UNHANDLED_OP;
			return;
			case OP_getInventoryCount:
				GS_UNHANDLED_OP;
			return;
			case OP_getAnimateVariable:
				GS_UNHANDLED_OP;
			return;
			case OP_getActorRoom: {
				uint16 actorNum = _stack.pop();

				if (actorNum == 0 || actorNum == 255) {
					_stack.push(0);
					return;
				}
				
				NO_FEATURE(COMI_THIS, "Not implemented OP_getActorRoom");
				_stack.push(0);
			}
			return;
			case OP_getActorWalkBox:
				GS_UNHANDLED_OP;
			return;
			case OP_getActorMoving:
				GS_UNHANDLED_OP;
			return;
			case OP_getActorCostume:
				GS_UNHANDLED_OP;
			return;
			case OP_getActorScaleX:
				GS_UNHANDLED_OP;
			return;
			case OP_getActorLayer:
				GS_UNHANDLED_OP;
			return;
			case OP_getActorElevation:
				GS_UNHANDLED_OP;
			return;
			case OP_getActorWidth:
				GS_UNHANDLED_OP;
			return;
			case OP_getObjectNewDir:
				GS_UNHANDLED_OP;
			return;
			case OP_getObjectX:
				GS_UNHANDLED_OP;
			return;
			case OP_getObjectY:
				GS_UNHANDLED_OP;
			return;
			case OP_getActorChore:
				GS_UNHANDLED_OP;
			return;
			case OP_distObjectObject:
				GS_UNHANDLED_OP;
			return;
			case OP_distPtPt:
				GS_UNHANDLED_OP;
			return;
			case OP_getObjectImageX:
				GS_UNHANDLED_OP;
			return;
			case OP_getObjectImageY:
				GS_UNHANDLED_OP;
			return;
			case OP_getObjectImageWidth:
				GS_UNHANDLED_OP;
			return;
			case OP_getObjectImageHeight:
				GS_UNHANDLED_OP;
			return;
			case OP_f4:
				GS_UNHANDLED_OP;
			return;
			case OP_f5:
				GS_UNHANDLED_OP;
			return;
			case OP_getStringWidth:
				GS_UNHANDLED_OP;
			return;
			case OP_getActorZPlane:
				GS_UNHANDLED_OP;
			return;
			case OP_f8:
				GS_UNHANDLED_OP;
			return;
			case OP_f9:
				GS_UNHANDLED_OP;
			return;
			case OP_fa:
				GS_UNHANDLED_OP;
			return;
			case OP_fb:
				GS_UNHANDLED_OP;
			return;
			case OP_fc:
				GS_UNHANDLED_OP;
			return;
			case OP_fd:
				GS_UNHANDLED_OP;
			return;
			case OP_fe:
				GS_UNHANDLED_OP;
			return;
			case OP_ff:
				GS_UNHANDLED_OP;
			return;
		}
	}

}
