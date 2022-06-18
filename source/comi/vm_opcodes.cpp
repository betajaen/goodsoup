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
#include "context.h"
#include "debug.h"
#include "vm_array.h"

namespace comi
{
	static const uint8 NO_CONTEXT = 0xFF;

#define GS_UNHANDLED_OP\
	do {\
		_dumpState();\
		_forceQuit();\
		error(COMI_THIS, "Unhandled Opcode! %lx 'OP_%s'", _opcode, _getOpcodeName(_opcode));\
	} while(0);

	void VirtualMachine::_step() {
		_pcOpcode = _pc;
		_opcode = _readByte();	
		_pcState.opcode = _opcode;

		// debug(COMI_THIS, "%ld : %2lx", _pc-1, (uint32) _opcode);

		switch (_opcode) {
			case OP_00:
				GS_UNHANDLED_OP;
			return;
			case OP_pushWord:
				_stack.push(_readUnsignedWord());
			return;
			case OP_pushWordVar:
				_stack.push(readVar(_readUnsignedWord()));
			return;
			case OP_wordArrayRead:
				GS_UNHANDLED_OP;
			return;
			case OP_wordArrayIndexedRead:
				GS_UNHANDLED_OP;
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
				ScriptContext& context = _context[_currentContext];
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
				writeVar(varWhere, value);
			}
			return;
			case OP_wordVarInc: {
				uint32 varNum = _readUnsignedWord();
				int32 var = readVar(varNum);
				var++;
				writeVar(varNum, var);
			}
			return;
			case OP_wordVarDec: {
				uint32 varNum = _readUnsignedWord();
				int32 var = readVar(varNum);
				var--;
				writeVar(varNum, var);
			}
			return;
			case OP_dimArray: {
				byte subOp = _readByte();
				int32 arrayNum = _readUnsignedWord();
				int32 size;

				switch (subOp) {
					case DimArrayOp_NewInt:
						size = _stack.pop();
						_newArray(arrayNum, AK_Int, 0, size);
					return;
					case DimArrayOp_NewString:
						size = _stack.pop();
						_newArray(arrayNum, AK_String, 0, size);
					return;
					case DimArrayOp_Delete:
						_deleteArray(arrayNum);
					return;
				}
				
				error(COMI_THIS, "Not implemented OP_dimArray(%ld,%ld)", (uint32) subOp, (uint32) arrayNum);
				_dumpState();
				_forceQuit();
			}
			return;
			case OP_wordArrayWrite: {
				uint16 arrayNum = _readWord();
				int32 value = _stack.pop();
				int32 base = _stack.pop();

				VmArray* array = _arrays->findFromNum(arrayNum);
				if (array) {
					array->write(value, 0, base);
				}
				else {
					error(COMI_THIS, "NULL VmArray (%ld) used with OP_wordArrayWrite", (uint32) arrayNum);
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
			case OP_dim2dimArray:
				GS_UNHANDLED_OP;
			return;
			case OP_wordArrayIndexedWrite:
				GS_UNHANDLED_OP;
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
						array = _newArray(arrayNum, VAK_String, 0, len);
						array->writeBytes(
							_script->ptr(from),
							offset,
							len
						);
					}
					return;
					case ArrayOps_AssignScummVarList: {
						/* TODO */
						error(COMI_THIS, "Not implemented OP_arrayOps ArrayOps_AssignString");
						_dumpState();
						_forceQuit();
					}
					return;
					case ArrayOps_Assign2DimList: {
						/* TODO */
						error(COMI_THIS, "Not implemented OP_arrayOps ArrayOps_Assign2DimList");
						_dumpState();
						_forceQuit();
					}
					return;
				}

				error(COMI_THIS, "Not implemented OP_arrayOps (%ld, %ld)", (uint32) subOp, (uint32) arrayNum);
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
			case OP_startScriptQuick:
				GS_UNHANDLED_OP;
			return;
			case OP_stopObjectCode:
				_stopObjectCode();
			return;
			case OP_stopScript:
				GS_UNHANDLED_OP;
			return;
			case OP_jumpToScript:
				GS_UNHANDLED_OP;
			return;
			case OP_dummy:
				GS_UNHANDLED_OP;
			return;
			case OP_startObject:
				GS_UNHANDLED_OP;
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

				warn(COMI_THIS, "Not implemented OP_setClass (%ld, %ld)", num, obj);
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
				_stack.push(readVar(VAR_EGO));
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
						warn(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_CursorOn");
					return;
					case CursorCommandOp_CursorOff:
						warn(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_CursorOff");
					return;
					case CursorCommandOp_SoftCursorOn:
						warn(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_SoftCursorOn");
					return;
					case CursorCommandOp_SoftCursorOff:
						warn(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_SoftCursorOff");
					return;
					case CursorCommandOp_UserPutOn:
						warn(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_UserPutOn");
					return;
					case CursorCommandOp_UserPutOff:
						warn(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_UserPutOff");
					return;
					case CursorCommandOp_SoftUserPutOn:
						warn(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_SoftUserPutOn");
					return;
					case CursorCommandOp_SoftUserPutOff:
						warn(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_SoftUserPutOff");
					return;
					case CursorCommandOp_CursorImage:
						_stack.pop();
						warn(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_CursorImage");
					return;
					case CursorCommandOp_HotSpot:
						_stack.pop();
						_stack.pop();
						warn(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_HotSpot");
					return;
					case CursorCommandOp_Transparency:
						_stack.pop();
						warn(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_Transparency");
					return;
					case CursorCommandOp_CharsetSet:
						_stack.pop();
						warn(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_CharsetSet");
					return;
					case CursorCommandOp_CharsetColour:
						warn(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_CharsetColour");
					return;
					case CursorCommandOp_CursorPut:
						_stack.pop();
						_stack.pop();
						warn(COMI_THIS, "Not implemented OP_cursorCommand CursorCommandOp_CursorPut");
					return;
				}

				error(COMI_THIS, "Not implemented OP_cursorCommand(%ld)", (uint32) param);
				_dumpState();
				_forceQuit();
			}
			return;
			case OP_loadRoom:
				GS_UNHANDLED_OP;
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

				warn(COMI_THIS, "Not implemented OP_putActorAtXY (%ld, %ld, %ld, %ld)", roomNum, x, y, actorNum);
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
				
				warn(COMI_THIS, "Not implemented OP_animateActor (%ld, %ld)", (uint32) animationNum, (uint32) actorNum);
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
						warn(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_Dummy");
					return;
					case ResourceRoutineOp_LoadCostume:
						warn(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_LoadCostume");
					return;
					case ResourceRoutineOp_LoadObject:
						warn(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_LoadObject");
					return;
					case ResourceRoutineOp_LoadRoom:
						warn(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_LoadRoom");
					return;
					case ResourceRoutineOp_LoadScript:
						warn(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_LoadScript");
					return;
					case ResourceRoutineOp_LoadSound:
						warn(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_LoadSound");
					return;
					case ResourceRoutineOp_LockCostume:
						warn(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_LockCostume");
					return;
					case ResourceRoutineOp_LockRoom:
						warn(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_LockRoom");
					return;
					case ResourceRoutineOp_LockScript:
						warn(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_LockScript");
					return;
					case ResourceRoutineOp_LockSound:
						warn(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_LockSound");
					return;
					case ResourceRoutineOp_UnlockCostume:
						warn(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_UnlockCostume");
					return;
					case ResourceRoutineOp_UnlockRoom:
						warn(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_UnlockRoom");
					return;
					case ResourceRoutineOp_UnlockScript:
						warn(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_UnlockScript");
					return;
					case ResourceRoutineOp_UnlockSound:
						warn(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_UnlockSound");
					return;
					case ResourceRoutineOp_SetResourceCounterCostume:
						warn(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_SetResourceCounterCostume");
					return;
					case ResourceRoutineOp_SetResourceCounterRoom:
						warn(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_SetResourceCounterRoom");
					return;
					case ResourceRoutineOp_SetResourceCounterScript:
						warn(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_SetResourceCounterScript");
					return;
					case ResourceRoutineOp_SetResourceCounterSound:
						warn(COMI_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_SetResourceCounterSound");
					return;
				}


				error(COMI_THIS, "Not implemented OP_resourceRoutines(%ld,%ld)", (uint32) subOp, (uint32) resId);
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
						warn(COMI_THIS, "Not implemented OP_roomOps RoomOp_SetColour");
					return;
					case RoomOp_FadePalette:
						_stack.pop();
						warn(COMI_THIS, "Not implemented OP_roomOps RoomOp_FadePalette");
					return;
					case RoomOp_DarkenPalette:
						_stack.pop();
						_stack.pop();
						_stack.pop();
						_stack.pop();
						_stack.pop();
						warn(COMI_THIS, "Not implemented OP_roomOps RoomOp_DarkenPalette");
					return;
					case RoomOp_PaletteManipulate:
						_stack.pop();
						_stack.pop();
						_stack.pop();
						_stack.pop();
						warn(COMI_THIS, "Not implemented OP_roomOps RoomOp_PaletteManipulate");
					return;
					case RoomOp_SetPalette:
						_stack.pop();
						warn(COMI_THIS, "Not implemented OP_roomOps RoomOp_SetPalette");
					return;
					case RoomOp_SaveGame:
						warn(COMI_THIS, "Not implemented OP_roomOps RoomOp_SaveGame");
					return;
					case RoomOp_LoadGame:
						warn(COMI_THIS, "Not implemented OP_roomOps RoomOp_LoadGame");
					return;
					case RoomOp_DesaturatePalette:
						_stack.pop();
						_stack.pop();
						_stack.pop();
						_stack.pop();
						_stack.pop();
						warn(COMI_THIS, "Not implemented OP_roomOps RoomOp_DesaturatePalette");
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
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetCostume");
					return;
					case ActorOp_SetWalkSpeed:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetWalkSpeed");
					return;
					case ActorOp_SetAnimationDefault:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetAnimationDefault");
					return;
					case ActorOp_InitAnimation:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_InitAnimation");
					return;
					case ActorOp_SetAnimationTalk:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetAnimationTalk");
					return;
					case ActorOp_SetAnimationWalk:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetAnimationWalk");
					return;
					case ActorOp_SetAnimationStand:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetAnimationStand");
					return;
					case ActorOp_SetAnimationSpeed:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetAnimationSpeed");
					return;
					case ActorOp_Default:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_Default");
					return;
					case ActorOp_SetElevation:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetElevation");
					return;
					case ActorOp_SetPalette:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetPalette");
					return;
					case ActorOp_SetTalkColour:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetTalkColour");
					return;
					case ActorOp_SetActorName:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetActorName");
					return;
					case ActorOp_SetActorWidth:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetActorWidth");
					return;
					case ActorOp_SetActorScale:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetActorScale");
					return;
					case ActorOp_SetNeverZClip:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetNeverZClip");
					return;
					case ActorOP_SetAlwaysZClip:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOP_SetAlwaysZClip");
					return;
					case ActorOp_SetIgnoreBoxes:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetIgnoreBoxes");
					return;
					case ActorOp_SetFollowBoxes:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetFollowBoxes");
					return;
					case ActorOp_SetSpecialDraw:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetSpecialDraw");
					return;
					case ActorOp_SetTextOffset:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetTextOffset");
					return;
					case ActorOp_Init:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_Init");
					return;
					case ActorOp_SetActorVariable:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetActorVariable");
					return;
					case ActorOp_SetIgnoreTurnsOn:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetIgnoreTurnsOn");
					return;
					case ActorOp_SetIgnoreTurnsOff:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetIgnoreTurnsOff");
					return;
					case ActorOp_ActorNew:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_ActorNew");
					return;
					case ActorOp_SetActorZ:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetActorZ");
					return;
					case ActorOp_ActorStop:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_ActorStop");
					return;
					case ActorOp_SetAngle:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetAngle");
					return;
					case ActorOp_TurnAngle:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_TurnAngle");
					return;
					case ActorOp_SetWalkScript:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetWalkScript");
					return;
					case ActorOp_SetTalkScript:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetTalkScript");
					return;
					case ActorOp_WalkPause:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_WalkPause");
					return;
					case ActorOp_WalkResume:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_WalkResume");
					return;
					case ActorOp_SetTalkVolume:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetTalkVolume");
					return;
					case ActorOp_SetTalkFrequency:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetTalkFrequency");
					return;
					case ActorOp_SetActorPan:
						warn(COMI_THIS, "Not implemented OP_actorOps ActorOp_SetActorPan");
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
						warn(COMI_THIS, "Not implemented OP_verbOps VerbOp_Init");
					return;
					case VerbOp_New:
						warn(COMI_THIS, "Not implemented OP_verbOps VerbOp_Init");
					return;
					case VerbOp_Delete:
						warn(COMI_THIS, "Not implemented OP_verbOps VerbOp_Init");
					return;
					case VerbOp_SetName:
						warn(COMI_THIS, "Not implemented OP_verbOps VerbOp_Init");
					return;
					case VerbOp_SetPosition:
						_stack.pop();
						_stack.pop();
						warn(COMI_THIS, "Not implemented OP_verbOps VerbOp_Init");
					return;
					case VerbOp_Enable:
						warn(COMI_THIS, "Not implemented OP_verbOps VerbOp_Init");
					return;
					case VerbOp_Disable:
						warn(COMI_THIS, "Not implemented OP_verbOps VerbOp_Init");
					return;
					case VerbOp_SetColour:
						_stack.pop();
						warn(COMI_THIS, "Not implemented OP_verbOps VerbOp_Init");
					return;
					case VerbOp_SetHilightColour:
						_stack.pop();
						warn(COMI_THIS, "Not implemented OP_verbOps VerbOp_Init");
					return;
					case VerbOp_SetDimmedColour:
						_stack.pop();
						warn(COMI_THIS, "Not implemented OP_verbOps VerbOp_Init");
					return;
					case VerbOp_Dim:
						warn(COMI_THIS, "Not implemented OP_verbOps VerbOp_Init");
					return;
					case VerbOp_SetKey:
						_stack.pop();
						warn(COMI_THIS, "Not implemented OP_verbOps VerbOp_Init");
					return;
					case VerbOp_SetImage:
						_stack.pop();
						_stack.pop();
						warn(COMI_THIS, "Not implemented OP_verbOps VerbOp_Init");
					return;
					case VerbOp_SetNameString:
						_stack.pop();
						warn(COMI_THIS, "Not implemented OP_verbOps VerbOp_Init");
					return;
					case VerbOp_Centre:
						warn(COMI_THIS, "Not implemented OP_verbOps VerbOp_Init");
					return;
					case VerbOp_SetCharSet:
						_stack.pop();
						warn(COMI_THIS, "Not implemented OP_verbOps VerbOp_Init");
					return;
					case VerbOp_SetLineSpacing:
						_stack.pop();
						warn(COMI_THIS, "Not implemented OP_verbOps VerbOp_Init");
					return;
				}

				error(COMI_THIS, "Not implemented OP_verbOps(%ld)", (uint32) subOp);
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
			case OP_stopSound:
				GS_UNHANDLED_OP;
			return;
			case OP_soundKludge: {

				uint16 num = _stack.readList(16);

				warn(COMI_THIS, "Not implemented OP_soundKludge %ld", num);

				/* TODO: WORKAROUND for bug #1398195 */
				warn(COMI_THIS, "Not implemented WORKAROUND for bug #1398195");
			}
			return;
			case OP_systemOps: {
				byte param = _readByte();

				if (param == SystemOps_Quit) {
					_forceQuit();
					info(COMI_THIS, "Quit has been called!");
					return;
				}

				warn(COMI_THIS, "Not implemented SysCall! %ld", (uint32)param);
				
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

					case KernelOp_LockObject:
						warn(COMI_THIS, "Not implemented KernelOp_LockObject");
					return;
					case KernelOp_UnlockObject:
						warn(COMI_THIS, "Not implemented KernelOp_UnlockObject");
					return;
					case KernelOp_RemapCostume:
						warn(COMI_THIS, "Not implemented KernelOp_RemapCostume");
					return;
					case KernelOp_RemapCostumeInert:
						warn(COMI_THIS, "Not implemented KernelOp_RemapCostumeInert");
					return;
					case KernelOp_Unused_0xF:
						/* Legacy */
					return;
					case KernelOp_SetBoxScaleSlot:
						warn(COMI_THIS, "Not implemented KernelOp_SetBoxScaleSlot");
					return;
					case KernelOp_SetScaleSlot:
						warn(COMI_THIS, "Not implemented KernelOp_SetScaleSlot");
					return;
					case KernelOp_SetBannerColours:
						warn(COMI_THIS, "Not implemented KernelOp_SetBannerColours");
					return;
					case KernelOp_SetActorChoreLimbFrame:
						warn(COMI_THIS, "Not implemented KernelOp_SetActorChoreLimbFrame");
					return;
					case KernelOp_ClearTextQueue:
						warn(COMI_THIS, "Not implemented KernelOp_ClearTextQueue");
					return;
					case KernelOp_KillAllScriptsExceptCurrent:
						warn(COMI_THIS, "Not implemented KernelOp_KillAllScriptsExceptCurrent");
					return;
					case KernelOp_StopAllVideo:
						warn(COMI_THIS, "Not implemented KernelOp_StopAllVideo");
					return;
					case KernelOp_WriteRegistryValue:
						warn(COMI_THIS, "Not implemented KernelOp_WriteRegistryValue");
					return;
					case KernelOp_QueryQuit:
						warn(COMI_THIS, "Not implemented KernelOp_QueryQuit");
					return;
					case KernelOp_BuildShadowPalette:
						warn(COMI_THIS, "Not implemented KernelOp_BuildShadowPalette");
					return;
					case KernelOp_SetShadowPalette:
						warn(COMI_THIS, "Not implemented KernelOp_SetShadowPalette");
					return;
					case KernelOp_BlastShadowObject:
						warn(COMI_THIS, "Not implemented KernelOp_BlastShadowObject");
					return;
					case KernelOp_SuperBlastObject:
						warn(COMI_THIS, "Not implemented KernelOp_SuperBlastObject");
					return;
				}

				_dumpState();
				_forceQuit();
				error(COMI_THIS, "Not implemented KernelSetFunctions(%ld, %ld)", (uint32) subOp, length);
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
			case OP_getRandomNumber:
				GS_UNHANDLED_OP;
			return;
			case OP_getRandomNumberRange:
				GS_UNHANDLED_OP;
			return;
			case OP_ifClassOfIs:
				GS_UNHANDLED_OP;
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
						warn(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetRGBSlot");
						_stack.push(0);
					}
					return;
					case KernelGetOp_GetKeyState: {
						warn(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetKeyState");
						_stack.push(0);
					}
					return;
					case KernelGetOp_CheckXYInBoxBounds: {
						warn(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetBox");
						_stack.push(0);
					}
					return;
					case KernelGetOp_FindBlastObject: {
						warn(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_FindBlastObject");
						_stack.push(0);
					}
					return;
					case KernelGetOp_TestActorHit: {
						warn(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_TestActorHit");
						_stack.push(0);
					}
					return;
					case KernelGetOp_GetLipSyncWidth: {
						warn(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetLipSyncWidth");
						_stack.push(0);
					}
					return;
					case KernelGetOp_GetLipSyncHeight: {
						warn(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetLipSyncHeight");
						_stack.push(0);
					}
					return;
					case KernelGetOp_GetTalkAnimation: {
						warn(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetTalkAnimation");
						_stack.push(0);
					}
					return;
					case KernelGetOp_GetGroupSfxVolume: {
						warn(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetGroupSfxVolume");
						_stack.push(0);
					}
					return;
					case KernelGetOp_GetGroupVoiceVolume: {
						warn(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetGroupVoiceVolume");
						_stack.push(0);
					}
					return;
					case KernelGetOp_GetGroupMusicVolume: {
						warn(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetGroupMusicVolume");
						_stack.push(0);
					}
					return;
					case KernelGetOp_ReadRegistryValue: {
						warn(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_ReadRegistryValue");
						_stack.push(-1);
					}
					return;
					case KernelGetOp_ImGetMusicPosition: {
						warn(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_ImGetMusicPosition");
						_stack.push(0);
					}
					return;
					case KernelGetOp_MusicLipGetSyncWidth: {
						warn(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_MusicLipGetSyncWidth");
						_stack.push(0);
					}
					return;
					case KernelGetOp_MusicLipGetSyncHeight: {
						warn(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_MusicLipGetSyncHeight");
						_stack.push(0);
					}
					return;
					case KernelGetOp_GetWalkBoxAt: {
						warn(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetWalkBoxAt");
						_stack.push(-1);
					}
					return;
					case KernelGetOp_IsPointInBox: {
						warn(COMI_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_IsPointInBox");
						_stack.push(0);
					}
					return;
				}
				_dumpState();
				_forceQuit();
				error(COMI_THIS, "Not implemented OP_kernelGetFunctions(%ld)", (uint32) opcode);
			}
			return;
			case OP_isActorInBox:
				GS_UNHANDLED_OP;
			return;
			case OP_getVerbEntrypoint:
				GS_UNHANDLED_OP;
			return;
			case OP_getActorFromXY:
				GS_UNHANDLED_OP;
			return;
			case OP_findObject:
				GS_UNHANDLED_OP;
			return;
			case OP_getVerbFromXY:
				GS_UNHANDLED_OP;
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
			case OP_getActorRoom:
				GS_UNHANDLED_OP;
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
