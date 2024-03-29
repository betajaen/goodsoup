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

#include "opcodes.h"
#include "vm.h"
#include "containers.h"
#include "vars.h"
#include "debugger.h"
#include "stack.h"

#include "../globals.h"
#include "../debug.h"
#include "../utils.h"
#include "../functions.h"
#include "../object_functions.h"
#include "../object.h"
#include "../verb.h"
#include "../actor.h"
#include "../index.h"
#include "../screen.h"
#include "../costume.h"
#include "draw.h"

#define DEBUG_OPCODES 0

namespace gs
{
	const char* ObjectWhereToString(uint8 where);
	void startRoom(uint16 roomNum, bool runExitScript, bool runEnterScript);

	static const uint8 NO_CONTEXT = 0xFF;

#if GS_RELEASE == 0
	#define GS_UNHANDLED_OP\
		do {\
			abort_quit_stop();\
			error(GS_THIS, "Unhandled Opcode! %lx 'OP_%s'", _opcode, getOpcodeString(_opcode));\
		} while(0);
#else
	#define GS_UNHANDLED_OP\
		do {\
			abort_quit_stop();\
			error(GS_THIS, "Unhandled Opcode");\
		} while(0);
#endif

	void VmContext::_step() {
		uint8 _opcode = _readByte();

#if defined(GS_VM_DEBUG) && GS_VM_DEBUG==1
        vmDebugOpcode(_pc - 1, _opcode);
#endif

		switch (_opcode) {
			case OP_00:
				GS_UNHANDLED_OP;
			return;
			case OP_pushWord: {
				uint32 value = _readWord();

				STACK.push(value);

#if defined(GS_VM_DEBUG) && GS_VM_DEBUG==1
                vmDebugResult(STACK.getSize(), value);
#endif

			}
			return;
			case OP_pushWordVar: {

				uint32 varName = _readUnsignedWord();
				int32 varValue = getVar(varName);



				STACK.push(varValue);

#if defined(GS_VM_DEBUG) && GS_VM_DEBUG==1
                vmDebugResult(STACK.getSize(), varName, varValue);
#endif
			}
			return;
			case OP_wordArrayRead: {
				uint32 base = STACK.pop();
				uint16 arrayNum = _readWord();

				VmArray* array = ARRAYS->findFromNum(arrayNum);
				if (array) {
					int32 value = array->read(0, base);
					STACK.push(value);
				}
				else {
					error(GS_THIS, "NULL VmArray (%ld) used with OP_wordArrayRead", (uint32) arrayNum);
					abort_quit_stop();
				}
			}
			return;
			case OP_wordArrayIndexedRead: {
				int32 base = STACK.pop();
				int32 index = STACK.pop();
				uint16 arrayNum = _readWord();

				VmArray* array = ARRAYS->findFromNum(arrayNum);
				if (array) {
					int32 value = array->read(index, base);
					STACK.push(value);
				}
				else {
					error(GS_THIS, "NULL VmArray (%ld) used with OP_wordArrayIndexedRead", (uint32) arrayNum);
					abort_quit_stop();
				}
			}
			return;
			case OP_dup: {
				int32 value = STACK.pop();
				STACK.push(value);
				STACK.push(value);
			}
			return;
			case OP_pop: {
				STACK.pop();
			}
			return;
			case OP_not: {
				int32 left = STACK.pop();
				STACK.push(left == 0 ? 1 : 0);
			}
			return;
			case OP_eq: {
				int32 right = STACK.pop();
				int32 left = STACK.pop();
				STACK.push(left == right ? 1 : 0);
			}
			return;
			case OP_neq: {
				int32 right = STACK.pop();
				int32 left = STACK.pop();
				STACK.push(left != right ? 1 : 0);
			}
			return;
			case OP_gt: {
				int32 right = STACK.pop();
				int32 left = STACK.pop();
				STACK.push(left > right ? 1 : 0);
			}
			return;
			case OP_lt: {
				int32 right = STACK.pop();
				int32 left = STACK.pop();
				STACK.push(left < right ? 1 : 0);
			}
			return;
			case OP_le: {
				int32 right = STACK.pop();
				int32 left = STACK.pop();
				STACK.push(left <= right ? 1 : 0);
			}
			return;
			case OP_ge: {
				int32 right = STACK.pop();
				int32 left = STACK.pop();
				STACK.push(left >= right ? 1 : 0);
			}
			return;
			case OP_add: {
				int32 right = STACK.pop();
				int32 left = STACK.pop();
				STACK.push(left + right);
			}
			return;
			case OP_sub: {
				int32 right = STACK.pop();
				int32 left = STACK.pop();
				STACK.push(left - right);
			}
			return;
			case OP_mul: {
				int32 right = STACK.pop();
				int32 left = STACK.pop();
				STACK.push(left * right);
			}
			return;
			case OP_div: {
				int32 right = STACK.pop();
				int32 left = STACK.pop();
				STACK.push(left / right);
			}
			return;
			case OP_land: {
				int32 right = STACK.pop();
				int32 left = STACK.pop();
				STACK.push(left && right ? 1 : 0);
			}
			return;
			case OP_lor: {
				int32 right = STACK.pop();
				int32 left = STACK.pop();
				STACK.push(left || right ? 1 : 0);
			}
			return;
			case OP_band: {
				int32 right = STACK.pop();
				int32 left = STACK.pop();
				STACK.push(left & right);
			}
			return;
			case OP_bor: {
				int32 right = STACK.pop();
				int32 left = STACK.pop();
				STACK.push(left | right);
			}
			return;
			case OP_mod: {
				int32 right = STACK.pop();
				int32 left = STACK.pop();
				STACK.push(left % right);
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
				int32 cond = STACK.pop();
				int32 relOffset = _readWord();
				
				if (cond != 0) {
					_pc += relOffset;
				}
			}
			return;
			case OP_ifNot: {
				int32 cond = STACK.pop();
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
				VM->_break();
			}
			return;
			case OP_delayFrames: {
				if (_delayFrameCount == 0) {
					_delayFrameCount = STACK.pop();
				}
				else {
					_delayFrameCount--;
				}
				if (_delayFrameCount != 0) {
					_pc--;
					VM->_break();
				}
			}
			return;
			case OP_wait: {
				byte subOp = _readByte();
				int32 offset = -2;

				switch (subOp) {
					case WaitOp_WaitActor: {
						offset = _readSignedWord();
						STACK.pop();
						NO_FEATURE(GS_THIS, "Not implemented OP_cursorCommand WaitOp_WaitActor");
					}
					break;
					case WaitOp_WaitMessage: {
						NO_FEATURE(GS_THIS, "Not implemented OP_cursorCommand WaitOp_WaitMessage");
					}
					break;
					case WaitOp_WaitCamera: {
						NO_FEATURE(GS_THIS, "Not implemented OP_cursorCommand WaitOp_WaitCamera");
					}
					break;
					case WaitOp_WaitSentence: {
						NO_FEATURE(GS_THIS, "Not implemented OP_cursorCommand WaitOp_WaitSentence");
					}
					break;
					case WaitOp_WaitAnimation: {
						offset = _readSignedWord();
						STACK.pop();
						NO_FEATURE(GS_THIS, "Not implemented OP_cursorCommand WaitOp_WaitAnimation");
					}
					break;
					case WaitOp_WaitTurn: {
						offset = _readSignedWord();
						STACK.pop();
						NO_FEATURE(GS_THIS, "Not implemented OP_cursorCommand WaitOp_WaitTurn");
					}
					break;
				}
#if 0
				/* TODO: The subOps decide when the wait is over, and returns early preventing the break here */
				_pc += offset;
				_break();
#endif
			}
			return;
			case OP_delay: {
				_delay = STACK.pop();
				_state = SCS_Paused;
				VM->_break();
			}
			return;
			case OP_delaySeconds: {
				_delay = STACK.pop() * 60;
				_state = SCS_Paused;
				VM->_break();
			}
			return;
			case OP_delayMinutes: {
				_delay = STACK.pop() * 3600;
				_state = SCS_Paused;
				VM->_break();
			}
			return;
			case OP_writeWordVar: {
				uint32 varWhere = _readUnsignedWord();
				int32 value = STACK.pop();
#if defined(GS_VM_DEBUG) && GS_VM_DEBUG==1
                vmDebugResult(varWhere, value);
#endif
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
						size = STACK.pop();
						ARRAYS->allocate(arrayNum, 0, size, VAK_Integer);
					return;
					case DimArrayOp_NewString:
						size = STACK.pop();
						ARRAYS->allocate(arrayNum, 0, size, VAK_String);
					return;
					case DimArrayOp_Delete:
						ARRAYS->deallocateFromArray(ARRAYS->findFromNum(arrayNum));
					return;
				}
				
				error(GS_THIS, "Not implemented OP_dimArray(%ld,%ld)", (uint32) subOp, (uint32) arrayNum);
				abort_quit_stop();
			}
			return;
			case OP_wordArrayWrite: {
				uint16 arrayNum = _readWord();
				int32 value = STACK.pop();
				int32 base = STACK.pop();

				VmArray* array = ARRAYS->findFromNum(arrayNum);
				if (array) {
					array->write(value, 0, base);
				}
				else {
					error(GS_THIS, "NULL VmArray (%ld) used with OP_wordArrayWrite", (uint32) arrayNum);
					abort_quit_stop();
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
						uint16 y = STACK.pop();
						uint16 x = STACK.pop();
						ARRAYS->allocate(arrayNum, x, y, VAK_Integer);
					}
					return;
					case Dim2DimOp_String: {
						uint16 y = STACK.pop();
						uint16 x = STACK.pop();
						ARRAYS->allocate(arrayNum, x, y,VAK_String);
					}
					return;
					case Dim2DimOp_Delete: {
						ARRAYS->deallocateFromArray(ARRAYS->findFromNum(arrayNum));
					}
					return;
				}

				error(GS_THIS, "Not implemented OP_dim2dimArray(%ld,%ld)", (uint32) subOp, (uint32) arrayNum);
				abort_quit_stop();
			}
			return;
			case OP_wordArrayIndexedWrite: {

				int32 value = STACK.pop();
				int32 base = STACK.pop();
				int32 index = STACK.pop();
				uint16 arrayNum = _readWord();

				VmArray* array = ARRAYS->findFromNum(arrayNum);
				if (array) {
					array->write(value, index, base);
				}
				else {
					error(GS_THIS, "NULL VmArray (%ld) used with OP_wordArrayIndexedWrite", (uint32) arrayNum);
					abort_quit_stop();
				}

			}
			return;
			case OP_arrayOps: {
				byte subOp = _readByte();
				uint32 arrayNum = _readUnsignedWord();
				VmArray* array;
				switch (subOp) {
					case ArrayOps_AssignString: {
						Array<byte, uint16>& _arrayTemp = VM->_arrayTemp;
						uint16 offset = STACK.pop();
						_readBytesForArray();
						uint16 len = _arrayTemp.getSize();

						array = ARRAYS->allocate(arrayNum, 0, len + 1, VAK_String);

						for(uint16 i=0;i < len;i++) {
							array->_data[offset + i] = _arrayTemp.get_unchecked(i);
						}

#if defined(GS_VM_DEBUG) && GS_VM_DEBUG==1
						vmDebugResult(subOp, arrayNum, offset, len);
#endif
					}
					return;
					case ArrayOps_AssignScummVarList: {
						/* TODO */
						uint16 offset = STACK.pop();
						uint16 len = STACK.readList(128);
						VmArray* array = ARRAYS->findFromNum(arrayNum);

						if (array == NULL) {
							array = ARRAYS->allocate(arrayNum, 0, offset + len, VAK_Integer);
						}

						array->writeFromCArray(0, offset, STACK.getList(), len);


#if defined(GS_VM_DEBUG) && GS_VM_DEBUG==1
						vmDebugResult(subOp, arrayNum, offset, len);
#endif
					}
					return;
					case ArrayOps_Assign2DimList: {
						uint16 offset = STACK.pop();
						uint16 len = STACK.readList(128);
						VmArray* array = ARRAYS->findFromNum(arrayNum);

						if (array) {
							int32* list = STACK.getList();
							uint16 index = STACK.pop();
							for(uint16 i=0;i < len;i++) {
								array->write(list[i], index, offset + i);
							}

#if defined(GS_VM_DEBUG) && GS_VM_DEBUG==1
							vmDebugResult(subOp, arrayNum, offset, index, len);
#endif
						}
						else {
							error(GS_THIS, "NULL VmArray (%ld) used with OP_arrayOps ArrayOps_AssignScummVarList", (uint32) arrayNum);
							abort_quit_stop();
							return;
						}

					}
					return;
				}

				error(GS_THIS, "Not implemented OP_arrayOps (%ld, %ld)", (uint32) subOp, (uint32) arrayNum);
				abort_quit_stop();
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

				uint8 count = STACK.readList(25);
				script = STACK.pop();
				flags = STACK.pop();

				VM->runScript(script, (flags & 1) !=0, (flags & 2) !=0, STACK.getList(), count);
			}
			return;
			case OP_startScriptQuick: {
				uint32 script, flags;

				uint8 count = STACK.readList(25);
				script = STACK.pop();

				VM->runScript(script, false, true, STACK.getList(), count);
			}
			return;
			case OP_stopObjectCode: {
				_reset();
				VM->_break();
			}
			return;
			case OP_stopScript: {
				uint32 scriptNum = STACK.pop();
				if (scriptNum == 0) {
					_reset();
					VM->_break();
				}
				else {
					VM->_stopScript(scriptNum);
				}
			}
			return;
			case OP_jumpToScript: {
				uint16 num = STACK.readList(25);
				uint16 scriptNum = STACK.pop();
				uint16 flags = STACK.pop();
				_reset();
				VM->_break();
				VM->runScript(scriptNum, (flags & 1) !=0, (flags & 2) !=0, STACK.getList(), num);
			}
			return;
			case OP_dummy:
			return;
			case OP_startObject: {
				uint16 num = STACK.readList(25);
				uint32 entryPc = STACK.pop();
				uint16 scriptNum = STACK.pop();
				uint16 flags = STACK.pop();
				
				VM->runObjectScript(scriptNum, entryPc, (flags & 1) !=0, (flags & 2) !=0, STACK.getList(), num);
			}
			return;
			case OP_stopObjectScript:
				GS_UNHANDLED_OP;
			return;
			case OP_cutscene: {
				uint16 num = STACK.readList(25);
				VM->_beginCutscene(*this, num);
			}
			return;
			case OP_endCutscene: {
				VM->_endCutscene(*this);
			}
			return;
			case OP_freezeUnfreeze: {
				int32 script = STACK.pop();

				vmDebugResult(script);

				if (script) {
					VM->freezeScripts(script);
				}
				else {
					VM->unfreezeAll();
				}
			}
			return;
			case OP_beginOverride:
				VM->_beginOverride(*this);
			return;
			case OP_endOverride:
				VM->_endOverride(*this);
			return;
			case OP_stopSentence: {
				SENTENCE_NUM = 0;
				VM->_stopScript(INTS->sentenceScript);
				/* TODO: Clear Input Flags */
			}
			return;
			case OP_87:
				GS_UNHANDLED_OP;
			return;
			case OP_88:
				GS_UNHANDLED_OP;
			return;
			case OP_setClass: {
				int16 num = STACK.readList(16);
				int32 obj = STACK.pop();

				for(int16 i=(num-1);i > -1;i--) {

					int32 classNum = STACK.getListItem(i);

					if (classNum == 0) {
						ObjectData* object = OBJECTS->findObject(num);
						if (object) { // Possible memory overwrite crash?
							object->setClass(0);
						}
					}
					else if ((classNum & 0x80) != 0) {
						ObjectData* object = OBJECTS->findObject(num);
						if (object) {
							object->setClassFlags(classNum, true);
						}
					}
					else {
						ObjectData* object = OBJECTS->findObject(num);
						if (object) {
							object->setClassFlags(classNum, false);
						}
					}
				}
			}
			return;
			case OP_setState: {
				int32 state = STACK.pop();
				int32 obj = STACK.pop();
				OBJECTS->setState(obj,state);
			}
			return;
			case OP_setOwner:
				GS_UNHANDLED_OP;
			return;
			case OP_panCameraTo:
				GS_UNHANDLED_OP;
			return;
			case OP_actorFollowCamera: {
				STACK.pop();
				NO_FEATURE(GS_THIS, "Not implemented OP_actorFollowCamera");
			}
			return;
			case OP_setCameraAt:
				GS_UNHANDLED_OP;
			return;
			case OP_printActor:
				_decodeParseString(0, 1);
			return;
			case OP_printEgo:
				STACK.push(INTS->ego);
				_decodeParseString(0, 1);
			return;
			case OP_talkActor: {
				uint16 actorNum = STACK.pop();
				uint16 offset, length;
				_readStringLength(offset, length);
				_actorSay(actorNum, length, offset);
			}
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
						//NO_FEATURE(GS_THIS, "Not implemented OP_cursorCommand CursorCommandOp_CursorOn");
					return;
					case CursorCommandOp_CursorOff:
						//NO_FEATURE(GS_THIS, "Not implemented OP_cursorCommand CursorCommandOp_CursorOff");
					return;
					case CursorCommandOp_SoftCursorOn:
						//NO_FEATURE(GS_THIS, "Not implemented OP_cursorCommand CursorCommandOp_SoftCursorOn");
					return;
					case CursorCommandOp_SoftCursorOff:
						//NO_FEATURE(GS_THIS, "Not implemented OP_cursorCommand CursorCommandOp_SoftCursorOff");
					return;
					case CursorCommandOp_UserPutOn:
						//NO_FEATURE(GS_THIS, "Not implemented OP_cursorCommand CursorCommandOp_UserPutOn");
					return;
					case CursorCommandOp_UserPutOff:
						//NO_FEATURE(GS_THIS, "Not implemented OP_cursorCommand CursorCommandOp_UserPutOff");
					return;
					case CursorCommandOp_SoftUserPutOn:
						//NO_FEATURE(GS_THIS, "Not implemented OP_cursorCommand CursorCommandOp_SoftUserPutOn");
					return;
					case CursorCommandOp_SoftUserPutOff:
						//NO_FEATURE(GS_THIS, "Not implemented OP_cursorCommand CursorCommandOp_SoftUserPutOff");
					return;
					case CursorCommandOp_CursorImage:
						STACK.pop();
						STACK.pop();
						//// NO_FEATURE(GS_THIS, "Not implemented OP_cursorCommand CursorCommandOp_CursorImage");
					return;
					case CursorCommandOp_HotSpot:
						STACK.pop();
						STACK.pop();
						//NO_FEATURE(GS_THIS, "Not implemented OP_cursorCommand CursorCommandOp_HotSpot");
					return;
					case CursorCommandOp_Transparency:
						STACK.pop();
						NO_FEATURE(GS_THIS, "Not implemented OP_cursorCommand CursorCommandOp_Transparency");
					return;
					case CursorCommandOp_CharsetSet:
						STACK.pop();
						NO_FEATURE(GS_THIS, "Not implemented OP_cursorCommand CursorCommandOp_CharsetSet");
					return;
					case CursorCommandOp_CharsetColour:
						STACK.readList(16);
						// NO_FEATURE(GS_THIS, "Not implemented OP_cursorCommand CursorCommandOp_CharsetColour");
					return;
					case CursorCommandOp_CursorPut:
						STACK.pop();
						STACK.pop();
						NO_FEATURE(GS_THIS, "Not implemented OP_cursorCommand CursorCommandOp_CursorPut");
					return;
				}

				NO_FEATURE(GS_THIS, "Not implemented OP_cursorCommand(%ld)", (uint32) param);
				abort_quit_stop();
			}
			return;
			case OP_loadRoom: {
				uint16 roomNum = STACK.pop();
				startRoom(roomNum, true, true);
			}
			return;
			case OP_loadRoomWithEgo:
				GS_UNHANDLED_OP;
			return;
			case OP_walkActorToObj: {
				STACK.pop(); // distance
				STACK.pop(); // object;
				STACK.pop(); // actor

				NO_FEATURE(GS_THIS, "Not implemented OP_walkActorToObj");
			}
			return;
			case OP_walkActorTo:
				GS_UNHANDLED_OP;
			return;
			case OP_putActorAtXY: {
				int32 roomNum, actorNum, x, y;

				roomNum = STACK.pop();
				y = STACK.pop();
				x = STACK.pop();
				actorNum = STACK.pop();

				ACTORS->putActorAtXY(actorNum, roomNum, x, y);

				/* TODO: If this actor is the talking actor and visible. It should stop talking */
			}
			return;
			case OP_putActorAtObject:
				GS_UNHANDLED_OP;
			return;
			case OP_faceActor:
				GS_UNHANDLED_OP;
			return;
			case OP_animateActor: {
				uint32 animation = STACK.pop();
				uint16 actorNum = STACK.pop();

				ActorData* actor = ACTORS->getActor(actorNum);

				if (actor) {
					actor->animate(animation);
				}

			}
			return;
			case OP_doSentence:
				GS_UNHANDLED_OP;
			return;
			case OP_pickupObject: {
				uint16 objectNum = STACK.pop();
				ObjectData* object = NULL;
				if (OBJECTS->loadInventoryObject(objectNum, object) && object) {
					object->setOwner(INTS->ego);
					object->setClassFlags(OCF_Untouchable, true);
					object->setState(1);
					/* TODO: Mark Object Rect as dirty */
					/* TODO: Clear Object Draw Queue */
					/* TODO: Run Inventory Script from VariableInventoryScript, if it exists. Pass in objectNum as the single argument for data */
				}
			}
			return;
			case OP_setBoxFlags: {
				STACK.pop();
				STACK.readList(65);
			}
			return;
			case OP_createBoxMatrix: {
				warn(GS_THIS, "createBoxMatrix not implemented %ld");
			}
			return;
			case OP_a9:
				GS_UNHANDLED_OP;
			return;
			case OP_resourceRoutines: {
				byte  subOp = _readByte();
				int32 resourceNum = STACK.pop();

				switch (subOp) {
					case ResourceRoutineOp_Dummy:
						NO_FEATURE(GS_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_Dummy");
					return;
					case ResourceRoutineOp_LoadCostume:
						COSTUMES->findOrLoadFromNum(resourceNum);
					return;
					case ResourceRoutineOp_LoadObject: {
						ObjectData* object = NULL;
						object = OBJECTS->findObject(resourceNum);
						if (object == NULL) {
							OBJECTS->loadInventoryObject(resourceNum, object);
						}
					}
					return;
					case ResourceRoutineOp_LoadRoom:
						NO_FEATURE(GS_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_LoadRoom %ld", resourceNum);
					return;
					case ResourceRoutineOp_LoadScript: {
						SCRIPTS->getOrLoadGlobalScript(resourceNum);
					}
					return;
					case ResourceRoutineOp_LoadSound:
						NO_FEATURE(GS_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_LoadSound %ld", resourceNum);
					return;
					case ResourceRoutineOp_LockCostume: {
						CostumeData* data = COSTUMES->findOrLoadFromNum(resourceNum);
						if (data != NULL) {
							data->_bResourceLocked = true;
						}
						else {
							COSTUMES->addResourceLock(resourceNum);
						}
					}
					return;
					case ResourceRoutineOp_LockRoom:
						NO_FEATURE(GS_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_LockRoom %ld", resourceNum);
					return;
					case ResourceRoutineOp_LockScript: {
						ScriptData* script = SCRIPTS->find(resourceNum);
						if (script) {
							script->_bResourceLock = true;
						}
						else {
							SCRIPTS->addResourceLock(resourceNum);
						}
					}
					return;
					case ResourceRoutineOp_LockSound:
						NO_FEATURE(GS_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_LockSound %ld", resourceNum);
					return;
					case ResourceRoutineOp_UnlockCostume: {
						CostumeData* data = COSTUMES->findFromNum(resourceNum);
						if (data != NULL) {
							data->_bResourceLocked = false;
						}
						else {
							COSTUMES->removeResourceLock(resourceNum);
						}
					}
					return;
					case ResourceRoutineOp_UnlockRoom:
						NO_FEATURE(GS_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_UnlockRoom %ld", resourceNum);
					return;
					case ResourceRoutineOp_UnlockScript: {
						ScriptData* script = SCRIPTS->find(resourceNum);
						if (script) {
							script->_bResourceLock = false;
						}
						else {
							SCRIPTS->removeResourceLock(resourceNum);
						}
					}
					return;
					case ResourceRoutineOp_UnlockSound:
						NO_FEATURE(GS_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_UnlockSound %ld", resourceNum);
					return;
					case ResourceRoutineOp_SetResourceCounterCostume:
						NO_FEATURE(GS_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_SetResourceCounterCostume %ld", resourceNum);
					return;
					case ResourceRoutineOp_SetResourceCounterRoom:
						NO_FEATURE(GS_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_SetResourceCounterRoom %ld", resourceNum);
					return;
					case ResourceRoutineOp_SetResourceCounterScript:
						NO_FEATURE(GS_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_SetResourceCounterScript %ld", resourceNum);
					return;
					case ResourceRoutineOp_SetResourceCounterSound:
						NO_FEATURE(GS_THIS, "Not implemented OP_resourceRoutines ResourceRoutineOp_SetResourceCounterSound %ld", resourceNum);
					return;
				}


				NO_FEATURE(GS_THIS, "Not implemented OP_resourceRoutines(%ld,%ld)", (uint32) subOp, (uint32) resourceNum);
				abort_quit_stop();

			}
			return;
			case OP_roomOps: {

				byte subOp = _readByte();

				switch (subOp) {
					case RoomOp_SetColour:
						STACK.pop();
						STACK.pop();
						STACK.pop();
						STACK.pop();
						NO_FEATURE(GS_THIS, "Not implemented OP_roomOps RoomOp_SetColour");
					return;
					case RoomOp_FadePalette: {
						uint16 pal = STACK.pop();
						NO_FEATURE(GS_THIS, "Not implemented OP_roomOps RoomOp_FadePalette");
					}
					return;
					case RoomOp_DarkenPalette: {
						uint8 endColour = STACK.pop();
						uint8 startColour = STACK.pop();
						int32 blueScale = STACK.pop();
						int32 greenScale =STACK.pop();
						int32 redScale = STACK.pop();
						drawScalePalette(startColour, endColour, redScale, greenScale, blueScale);
					}
					return;
					case RoomOp_PaletteManipulate:
						STACK.pop();
						STACK.pop();
						STACK.pop();
						STACK.pop();
						NO_FEATURE(GS_THIS, "Not implemented OP_roomOps RoomOp_PaletteManipulate");
					return;
					case RoomOp_SetPalette:
						STACK.pop();
						NO_FEATURE(GS_THIS, "Not implemented OP_roomOps RoomOp_SetPalette");
					return;
					case RoomOp_SaveGame:
						NO_FEATURE(GS_THIS, "Not implemented OP_roomOps RoomOp_SaveGame");
					return;
					case RoomOp_LoadGame:
						NO_FEATURE(GS_THIS, "Not implemented OP_roomOps RoomOp_LoadGame");
					return;
					case RoomOp_DesaturatePalette:
						STACK.pop();
						STACK.pop();
						STACK.pop();
						STACK.pop();
						STACK.pop();
						NO_FEATURE(GS_THIS, "Not implemented OP_roomOps RoomOp_DesaturatePalette");
					return;
				}

				error(GS_THIS, "Not implemented OP_roomOps(%ld)", (uint32) subOp);
				abort_quit_stop();
			}
			return;
			case OP_actorOps: {
				byte subOp = _readByte();
#if defined(GS_VM_DEBUG) && GS_VM_DEBUG==1
				vmDebugResult(subOp);
#endif
				switch(subOp) {
					case ActorOp_SetCostume: {
                        ActorData* actor = ACTORS->getActor();
                        uint16 costumeNum = STACK.pop();
                        if (actor) {
                            actor->setCostume(costumeNum);
                        }
                    }
					return;
					case ActorOp_SetWalkSpeed: {
                        int32 x = STACK.pop();   // y speed
                        int32 y = STACK.pop();   // x speed
						ActorData* actor = ACTORS->getActor();
                        if (actor) {
                            actor->setWalkSpeed(x, y);
                        }
                    }
					return;
					case ActorOp_SetAnimationDefault: {
						ActorData* actor = ACTORS->getActor();
                        if (actor) {
                            actor->setAnimationDefault();
                        }
                    }
					return;
					case ActorOp_InitAnimation: {
                        uint8 frame = STACK.pop();
						ActorData* actor = ACTORS->getActor();
                        if (actor) {
                            actor->_initFrame = frame;
                        }
                    }
					return;
					case ActorOp_SetAnimationTalk: {
                        uint8 stopFrame = STACK.pop();
                        uint8 startFrame = STACK.pop();
						ActorData* actor = ACTORS->getActor();
                        if (actor) {
                            actor->_talkStopFrame = stopFrame;
                            actor->_talkStartFrame = startFrame;
                        }
                    }
					return;
					case ActorOp_SetAnimationWalk:  {
                        uint8 walkFrame = STACK.pop();
						ActorData* actor = ACTORS->getActor();
                        if (actor) {
                            actor->_walkFrame = walkFrame;
                        }
                    }
					return;
					case ActorOp_SetAnimationStand:  {
                        uint8 standFrame = STACK.pop();
						ActorData* actor = ACTORS->getActor();
                        if (actor) {
                            actor->_standFrame = standFrame;
                        }
                    }
					return;
					case ActorOp_SetAnimationSpeed: {
						uint8 speed = STACK.pop();
						ActorData* actor = ACTORS->getActor();
						if (actor) {
							actor->setAnimationSpeed(speed);
						}
                    }
					return;
					case ActorOp_Default: {
						ActorData* actor = ACTORS->getActor();
						if (actor) {
							actor->initialiseDefault();
						}
					}
					return;
					case ActorOp_SetElevation: {
						int16 elevation = STACK.pop();
						ActorData* actor = ACTORS->getActor();
						if (actor) {
							actor->setElevation(elevation);
						}
					}
					return;
					case ActorOp_SetPalette: {
						uint16 paletteNum = STACK.pop();
						uint8 idx = STACK.pop();
						ActorData* actor = ACTORS->getActor();
						if (actor) {
							actor->setPalette(idx, paletteNum);
						}
					}
					return;
					case ActorOp_SetTalkColour: {
						int32 colour = STACK.pop();
						ActorData* actor = ACTORS->getActor();
						if (actor) {
							actor->_talkColour = colour;
						}
					}
					return;
					case ActorOp_SetActorName: {
						uint16 from, length;
						_readStringLength(from, length);
						/* TODO */
					}
					return;
					case ActorOp_SetActorWidth: {
						int32 width = STACK.pop();
						ActorData* actor = ACTORS->getActor();
						if (actor) {
							actor->_w = width;
						}
					}
					return;
					case ActorOp_SetActorScale: {
						int32 scale = STACK.pop();
						ActorData* actor = ACTORS->getActor();
						if (actor) {
							actor->setScale(scale, scale);
						}
					}
					return;
					case ActorOp_SetNeverZClip: {
						ActorData* actor = ACTORS->getActor();
						if (actor) {
							actor->_forceClip = 0;
						}
					}
					return;
					case ActorOP_SetAlwaysZClip: {
						int32 clip = STACK.pop();
						ActorData* actor = ACTORS->getActor();
						if (actor) {
							if (clip == 255)
								clip = 100;
							actor->_forceClip = clip;
						}
					}
					return;
					case ActorOp_SetIgnoreBoxes: {
						ActorData* actor = ACTORS->getActor();
						if (actor) {
							actor->_bIgnoreBoxes = false;
							actor->_forceClip = 100;
							/* TODO: Update Actor Pos in Room */
						}
					}
					return;
					case ActorOp_SetFollowBoxes: {
						ActorData* actor = ACTORS->getActor();
						if (actor) {
							actor->_bIgnoreBoxes = true;
							actor->_forceClip = 100;
							/* TODO: Update Actor Pos in Room */
						}
					}
					return;
					case ActorOp_SetSpecialDraw: {
						uint8 shadowMode = STACK.pop();
						ActorData *actor = ACTORS->getActor();
						if (actor) {
							actor->_shadowMode = shadowMode;
						}
					}
					return;
					case ActorOp_SetTextOffset: {
						int32 y = STACK.pop();
						int32 x = STACK.pop();
						ActorData* actor = ACTORS->getActor();
						if (actor) {
							actor->_talkX = x;
							actor->_talkY = y;
						}
					}
					return;
					case ActorOp_Init: {
						int32 currentActor = STACK.pop();
						if (currentActor < 0 || currentActor > NUM_ACTORS) {
							warn(GS_THIS, "ActorOp_Init has an invalid actor num %ld", currentActor);
						}
						else {
							CURRENT_ACTOR = (uint8) currentActor;
						}
					}
					return;
					case ActorOp_SetActorVariable: {
						int32 value = STACK.pop();
						uint8 idx = STACK.pop();
						ActorData* actor = ACTORS->getActor();
						if (actor) {
							actor->setVar(idx, value);
						}
					}
					return;
					case ActorOp_SetIgnoreTurnsOn: {
						ActorData* actor = ACTORS->getActor();
						if (actor) {
							actor->_bIgnoreTurns = true;
						}
					}
					return;
					case ActorOp_SetIgnoreTurnsOff: {
						ActorData* actor = ACTORS->getActor();
						if (actor) {
							actor->_bIgnoreTurns = false;
						}
					}
					return;
					case ActorOp_ActorNew: {
						ActorData* actor = ACTORS->getActor();
						if (actor) {
							actor->newDefault();
						}
					}
					return;
					case ActorOp_SetActorZ: {
						int16 layer = STACK.pop();
						ActorData* actor = ACTORS->getActor();
						if (actor) {
							actor->_layer = layer;
						}
					}
					return;
					case ActorOp_ActorStop: {
						ActorData* actor = ACTORS->getActor();
						if (actor) {
							actor->stopMoving();
							actor->startAnimation(actor->_standFrame);
						}
					}
					return;
					case ActorOp_SetAngle: {
						int16 angle = STACK.pop();
						ActorData* actor = ACTORS->getActor();
						if (actor) {
							actor->_moving &= ~AMF_Turn;
							actor->setDirection(angle);
						}
					}
					return;
					case ActorOp_TurnAngle: {
						int16 angle = STACK.pop();
						ActorData *actor = ACTORS->getActor();
						if (actor) {
							actor->turnToDirection(angle);
						}
					}
					return;
					case ActorOp_SetWalkScript: {
						uint16 walkScript = STACK.pop();
						ActorData* actor = ACTORS->getActor();
						if (actor) {
							actor->_walkScript = walkScript;
						}
					}
					return;
					case ActorOp_SetTalkScript:{
						uint16 talkScript = STACK.pop();
						ActorData* actor = ACTORS->getActor();
						if (actor) {
							actor->_talkScript = talkScript;
						}
					}
					return;
					case ActorOp_WalkPause: {
						ActorData* actor = ACTORS->getActor();
						if (actor) {
							actor->_moving |= AMF_Frozen;
						}
					}
					return;
					case ActorOp_WalkResume:{
						ActorData* actor = ACTORS->getActor();
						if (actor) {
							actor->_moving &= ~AMF_Frozen;
						}
					}
					return;
					case ActorOp_SetTalkVolume: {
						int32 volume = STACK.pop();
						ActorData* actor = ACTORS->getActor();
						if (actor) {
							actor->_talkFrequency = volume;
						}
					}
					return;
					case ActorOp_SetTalkFrequency: {
						int32 frequency = STACK.pop();
						ActorData* actor = ACTORS->getActor();
						if (actor) {
							actor->_talkFrequency = frequency;
						}
					}
					return;
					case ActorOp_SetActorPan: {
						int32 pan = STACK.pop();
						ActorData* actor = ACTORS->getActor();
						if (actor) {
							actor->_talkPan = pan;
						}
					}
					return;
				}

				error(GS_THIS, "Unsupported Actor Operation %ld", subOp);
				abort_quit_stop();
			}
			return;
			case OP_cameraOps: {
				/* byte subOp = */ _readByte();
				/* subOp is purposely unused */
			}
			return;
			case OP_verbOps: {
				byte subOp = _readByte();

				switch (subOp) {
					case VerbOp_GetOrNew: {
						int32 verbNum = STACK.pop();
						VERBS->getOrNew(verbNum);
					}
					return;
					case VerbOp_New:
						NO_FEATURE(GS_THIS, "Not implemented OP_verbOps VerbOp_Init");
					return;
					case VerbOp_Delete:
						NO_FEATURE(GS_THIS, "Not implemented OP_verbOps VerbOp_Delete");
					return;
					case VerbOp_SetName:
						NO_FEATURE(GS_THIS, "Not implemented OP_verbOps VerbOp_SetName");
					return;
					case VerbOp_SetPosition:
						STACK.pop();
						STACK.pop();
						NO_FEATURE(GS_THIS, "Not implemented OP_verbOps VerbOp_SetPosition");
					return;
					case VerbOp_Enable:
						NO_FEATURE(GS_THIS, "Not implemented OP_verbOps VerbOp_Enable");
					return;
					case VerbOp_Disable:
						NO_FEATURE(GS_THIS, "Not implemented OP_verbOps VerbOp_Disable");
					return;
					case VerbOp_SetColour:
						STACK.pop();
						NO_FEATURE(GS_THIS, "Not implemented OP_verbOps VerbOp_SetColour");
					return;
					case VerbOp_SetHilightColour:
						STACK.pop();
						NO_FEATURE(GS_THIS, "Not implemented OP_verbOps VerbOp_SetHilightColour");
					return;
					case VerbOp_SetDimmedColour:
						STACK.pop();
						NO_FEATURE(GS_THIS, "Not implemented OP_verbOps VerbOp_SetDimmedColour");
					return;
					case VerbOp_Dim:
						NO_FEATURE(GS_THIS, "Not implemented OP_verbOps VerbOp_Dim");
					return;
					case VerbOp_SetKey:
						STACK.pop();
						NO_FEATURE(GS_THIS, "Not implemented OP_verbOps VerbOp_SetKey");
					return;
					case VerbOp_SetImage:
						STACK.pop();
						STACK.pop();
						NO_FEATURE(GS_THIS, "Not implemented OP_verbOps VerbOp_SetImage");
					return;
					case VerbOp_SetNameString:
						STACK.pop();
						NO_FEATURE(GS_THIS, "Not implemented OP_verbOps VerbOp_SetNameString");
					return;
					case VerbOp_Centre:
						NO_FEATURE(GS_THIS, "Not implemented OP_verbOps VerbOp_Centre");
					return;
					case VerbOp_SetCharSet:
						STACK.pop();
						NO_FEATURE(GS_THIS, "Not implemented OP_verbOps VerbOp_SetCharSet");
					return;
					case VerbOp_SetLineSpacing: {
						Verb* verb = VERBS->getLastVerbUsed();
						verb->_lineSpacing = STACK.pop();
					}
					return;
				}

				NO_FEATURE(GS_THIS, "Not implemented OP_verbOps(%ld)", (uint32) subOp);
				abort_quit_stop();
			}
			return;
			case OP_startSound: {
				uint32 soundNum = STACK.pop();
				NO_FEATURE(GS_THIS, "No audio support for audio %lx", soundNum);
			}
			return;
			case OP_startMusic:
				GS_UNHANDLED_OP;
			return;
			case OP_stopSound: {
				uint16 soundNum = STACK.pop();
				NO_FEATURE(GS_THIS, "Not implemented OP_stopSound %ld", soundNum);
			}
			return;
			case OP_soundKludge: {

				uint16 num = STACK.readList(16);

				NO_FEATURE(GS_THIS, "Not implemented OP_soundKludge %ld", num);

				/* TODO: WORKAROUND for bug #1398195 */
				NO_FEATURE(GS_THIS, "Not implemented WORKAROUND for bug #1398195");
			}
			return;
			case OP_systemOps: {
				byte param = _readByte();

				if (param == SystemOps_Quit) {
					VM->_forceQuit();
					info(GS_THIS, "Quit has been called!");
					return;
				}
				else if (param == SystemOps_AbortQuitStop) {
					abort_quit_stop();
					error(GS_THIS, "AbortQuitStop has been called through a Script!");
					return;
				}
				else if (param == SystemOps_Noop) {
					return;
				}

				NO_FEATURE(GS_THIS, "Not implemented SysCall! %ld", (uint32)param);
				
				/* UNHANDLED */
			}
			return;
			case OP_saveRestoreVerbs: {
				byte subOp = _readByte();
				int32 c = STACK.pop();
				int32 b = STACK.pop();
				int32 a = STACK.pop();
				NO_FEATURE(GS_THIS, "Not implemented OP_saveRestoreVerbs! %ld", (uint32) subOp);
			}
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
			case OP_startVideo: {
				_readString();
				uint8 videoNum;

				if (tryGetVideoId(videoNum, sStringTemp.getString())) {
					setNextGameState(GSK_Video, videoNum);
					VM->interrupt();
				}
				else {
					warn(GS_THIS, "Could not play unknown named video %s", sStringTemp.getString());
				}
			}
			return;
			case OP_kernelSetFunctions: {

				uint8 length = STACK.readList(30);
				byte subOp = STACK.getListItem(0);

				switch(subOp) {

					case KernelSetOp_LockObject: {
						uint16 objectNum = STACK.getListItem(1);

						ObjectData* object = OBJECTS->findObject(objectNum);
						if (object) {
							object->setLocked(true);
						}
						else {
							error(GS_THIS, "Object %ld does not exist!", (uint32) objectNum);
							OBJECTS->dumpObjects();
							abort_quit_stop();
						}
					}
					return;
					case KernelSetOp_UnlockObject:{
						ObjectData* object = OBJECTS->findObject(STACK.getListItem(1));
						if (object) {
							object->setLocked(false);
						}
						else {
							error(GS_THIS, "Object does not exist!");
							abort_quit_stop();
						}
					}
					return;
					case KernelSetOp_RemapCostume:
						NO_FEATURE(GS_THIS, "Not implemented KernelSetOp_RemapCostume");
					return;
					case KernelSetOp_RemapCostumeInert:
						NO_FEATURE(GS_THIS, "Not implemented KernelSetOp_RemapCostumeInert");
					return;
					case KernelSetOp_Unused_0xF:
						/* Legacy */
					return;
					case KernelSetOp_SetBoxScaleSlot:
						NO_FEATURE(GS_THIS, "Not implemented KernelSetOp_SetBoxScaleSlot");
					return;
					case KernelSetOp_SetScaleSlot:
						NO_FEATURE(GS_THIS, "Not implemented KernelSetOp_SetScaleSlot");
					return;
					case KernelSetOp_SetBannerColours:
						// Disabled, due to lack of clarity of what this actually does and amount of spam.
						// NO_FEATURE(GS_THIS, "Not implemented KernelSetOp_SetBannerColours");
					return;
					case KernelSetOp_SetActorChoreLimbFrame:
						NO_FEATURE(GS_THIS, "Not implemented KernelSetOp_SetActorChoreLimbFrame");
					return;
					case KernelSetOp_ClearTextQueue:
						NO_FEATURE(GS_THIS, "Not implemented KernelSetOp_ClearTextQueue");
					return;
					case KernelSetOp_Unused_0x1A:
					case KernelSetOp_Unused_0x1B:
					case KernelSetOp_Unused_0x1C:
					case KernelSetOp_Unused_0x1D: {
						/* Unused Save Game Functionality */
					}
					return;
					case KernelSetOp_KillAllScriptsExceptCurrent:
						NO_FEATURE(GS_THIS, "Not implemented KernelSetOp_KillAllScriptsExceptCurrent");
					return;
					case KernelSetOp_StopAllVideo:
						NO_FEATURE(GS_THIS, "Not implemented KernelSetOp_StopAllVideo");
					return;
					case KernelSetOp_WriteRegistryValue:
						NO_FEATURE(GS_THIS, "Not implemented KernelSetOp_WriteRegistryValue");
					return;
					case KernelSetOp_QueryQuit:
						NO_FEATURE(GS_THIS, "Not implemented KernelSetOp_QueryQuit");
					return;
					case KernelSetOp_BuildShadowPalette:
						NO_FEATURE(GS_THIS, "Not implemented KernelSetOp_BuildShadowPalette");
					return;
					case KernelSetOp_SetShadowPalette:
						NO_FEATURE(GS_THIS, "Not implemented KernelSetOp_SetShadowPalette");
					return;
					case KernelSetOp_BlastShadowObject:
						NO_FEATURE(GS_THIS, "Not implemented KernelSetOp_BlastShadowObject");
					return;
					case KernelSetOp_SuperBlastObject:
						NO_FEATURE(GS_THIS, "Not implemented KernelSetOp_SuperBlastObject");
					return;
				}

				NO_FEATURE(GS_THIS, "Not implemented KernelSetFunctions(%ld, %ld)", (uint32) subOp, length);
				abort_quit_stop();
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
			case OP_startScriptQuick2: {
				uint8 num = STACK.readList(25);
				uint16 scriptNum = STACK.pop();
#if defined(GS_VM_DEBUG) && GS_VM_DEBUG==1
				vmDebugResult(scriptNum, num, STACK.getSize());
#endif
				VM->runScript(scriptNum, false, true, STACK.getList(), num);
			}
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
				int16 num = STACK.readList(100);
				int32 val = STACK.pop();

				while (--num >= 0) {
					if (STACK.getListItem(num) == val) {
						STACK.push(1);
						return;
					}
				}
				
				STACK.push(0);
			}
			return;
			case OP_getRandomNumber: {
				uint32 max = STACK.pop();
				uint32 num = getRandom(max);
				STACK.push(num);
			}
			return;
			case OP_getRandomNumberRange: {
				uint32 max = STACK.pop();
				uint32 min = STACK.pop();
				uint32 num = getRandomRange(min, max);
				STACK.push(num);
			}
			return;
			case OP_ifClassOfIs: {
				int16 num = STACK.readList(16);
				uint16 obj = STACK.pop();
				uint32 flags;
				bool b;
				int32 cond = 1;
				ObjectData* object = OBJECTS->findObject(obj);

				if (object) {

					while (--num >= 0) {
						flags = STACK.getListItem(num);
						b = object->getClassFlags(flags);
						if ((flags & 0x80 && !b) || (!(flags & 0x80) && b))
							cond = 0;
					}
				}

				STACK.push(cond);
			}
			return;
			case OP_getState: {
				uint16 obj = STACK.pop();
				STACK.push(OBJECTS->getState(obj));
			}
			return;
			case OP_getOwner: {
				uint16 obj = STACK.pop();
				STACK.push(OBJECTS->getOwner(obj));
			}
			return;
			case OP_isScriptRunning: {
				int32 scriptNum = STACK.pop();
				bool isRunning = VM->isScriptRunning(scriptNum);
				STACK.push(isRunning ? 1 : 0);
			}
			return;
			case OP_d4:
				GS_UNHANDLED_OP;
			return;
			case OP_isSoundRunning: {
				uint16 soundNum = STACK.pop();
				STACK.push(0);
				NO_FEATURE(GS_THIS, "No Sound Support for OP_isSoundRunning %ld", (uint32) soundNum);
			}
			return;
			case OP_abs: {
				int32 v = STACK.pop();
				if (!(v >= 0))
					v = -v;
				STACK.push(v);
			}
			return;
			case OP_d7:
				GS_UNHANDLED_OP;
			return;
			case OP_kernelGetFunctions: {
				uint16 len = STACK.readList(30);
				byte opcode = STACK.getListItem(0);

				switch (opcode) {
					case KernelGetOp_GetRGBSlot: {
						NO_FEATURE(GS_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetRGBSlot");
						STACK.push(0);
					}
					return;
					case KernelGetOp_GetKeyState: {
						NO_FEATURE(GS_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetKeyState");
						STACK.push(0);
					}
					return;
					case KernelGetOp_CheckXYInBoxBounds: {
						NO_FEATURE(GS_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetBox");
						STACK.push(0);
					}
					return;
					case KernelGetOp_FindBlastObject: {
						NO_FEATURE(GS_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_FindBlastObject");
						STACK.push(0);
					}
					return;
					case KernelGetOp_TestActorHit: {
						NO_FEATURE(GS_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_TestActorHit");
						STACK.push(0);
					}
					return;
					case KernelGetOp_GetLipSyncWidth: {
						NO_FEATURE(GS_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetLipSyncWidth");
						STACK.push(0);
					}
					return;
					case KernelGetOp_GetLipSyncHeight: {
						NO_FEATURE(GS_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetLipSyncHeight");
						STACK.push(0);
					}
					return;
					case KernelGetOp_GetTalkAnimation: {
						NO_FEATURE(GS_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetTalkAnimation");
						STACK.push(0);
					}
					return;
					case KernelGetOp_GetGroupSfxVolume: {
						NO_FEATURE(GS_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetGroupSfxVolume");
						STACK.push(0);
					}
					return;
					case KernelGetOp_GetGroupVoiceVolume: {
						NO_FEATURE(GS_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetGroupVoiceVolume");
						STACK.push(0);
					}
					return;
					case KernelGetOp_GetGroupMusicVolume: {
						NO_FEATURE(GS_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetGroupMusicVolume");
						STACK.push(0);
					}
					return;
					case KernelGetOp_ReadRegistryValue: {
						// NO_FEATURE(GS_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_ReadRegistryValue");
						STACK.push(-1);
					}
					return;
					case KernelGetOp_ImGetMusicPosition: {
						NO_FEATURE(GS_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_ImGetMusicPosition");
						STACK.push(0);
					}
					return;
					case KernelGetOp_MusicLipGetSyncWidth: {
						NO_FEATURE(GS_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_MusicLipGetSyncWidth");
						STACK.push(0);
					}
					return;
					case KernelGetOp_MusicLipGetSyncHeight: {
						NO_FEATURE(GS_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_MusicLipGetSyncHeight");
						STACK.push(0);
					}
					return;
					case KernelGetOp_GetWalkBoxAt: {
						NO_FEATURE(GS_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_GetWalkBoxAt");
						STACK.push(-1);
					}
					return;
					case KernelGetOp_IsPointInBox: {
						NO_FEATURE(GS_THIS, "Not implemented OP_kernelGetFunctions KernelGetOp_IsPointInBox");
						STACK.push(0);
					}
					return;
				}
				
				NO_FEATURE(GS_THIS, "Not implemented OP_kernelGetFunctions(%ld)", (uint32) opcode);
				abort_quit_stop();
			}
			return;
			case OP_isActorInBox: {
				STACK.pop();
				STACK.pop();
				STACK.push(0);
				NO_FEATURE(GS_THIS, "Not implemented OP_isActorInBox");
			}
			return;
			case OP_getVerbEntrypoint:
				GS_UNHANDLED_OP;
			return;
			case OP_getActorFromXY: {
				STACK.pop();
				STACK.pop();
				STACK.push(0);
				NO_FEATURE(GS_THIS, "Not implemented OP_getActorFromXY");
			}
			return;
			case OP_findObjectFromXY: {
				int32 y = STACK.pop();
				int32 x = STACK.pop();
				STACK.push(OBJECTS->findRoomObjectNumFromXY(x, y));
			}
			return;
			case OP_getVerbFromXY: {
				STACK.pop();
				STACK.pop();
				STACK.push(0);
				NO_FEATURE(GS_THIS, "Not implemented OP_getVerbFromXY");
			}
			return;
			case OP_de:
				GS_UNHANDLED_OP;
			return;
			/*
			 protected int FindInventoryCore(int owner, int idx)
        {
            int count = 1, i, obj;
            for (i = 0; i < _resManager.NumInventory; i++)
            {
                obj = _inventory[i];
                if (obj != 0 && GetOwnerCore(obj) == owner && count++ == idx)
                    return obj;
            }
            return 0;
        }

			 */
			case OP_findInventory: {
				uint8 idx = STACK.pop();
				uint16 owner = STACK.pop();

				STACK.push(OBJECTS->findNthInventoryItem(owner, idx));
			}
			return;
			case OP_getInventoryCount: {
				uint16 owner = STACK.pop();
				STACK.push(OBJECTS->calculateInventoryCountForOwner(owner));
			}
			return;
			case OP_getAnimateVariable: {
				uint8 varNum = STACK.pop();
				uint8 actorNum = STACK.pop();
				ActorData* actor = ACTORS->getActor(actorNum);
				if (actor) {
					STACK.push(actor->getVar(varNum));
				}
				else {
					STACK.push(0);
				}
			}
			return;
			case OP_getActorRoom: {
				uint16 actorNum = STACK.pop();

				if (actorNum == 0 || actorNum == 255) {
					STACK.push(0);
#if defined(GS_VM_DEBUG) && GS_VM_DEBUG==1
                    vmDebugResult(STACK.getSize(), actorNum, 0);
#endif
					return;
				}

				ActorData* actor = ACTORS->getActor(actorNum);
				if (actor) {
					STACK.push(actor->_roomNum);
#if defined(GS_VM_DEBUG) && GS_VM_DEBUG==1
                    vmDebugResult(STACK.getSize(), actorNum, actor->_roomNum);
#endif
				}
				else {
					warn(GS_THIS, "Unknown actor %ld to get room from", (uint16) actorNum);
					STACK.push(0);
#if defined(GS_VM_DEBUG) && GS_VM_DEBUG==1
                    vmDebugResult(STACK.getSize(), 0);
#endif
				}
			}
			return;
			case OP_getActorWalkBox:  {
				uint16 actorNum = STACK.pop();
				ActorData* actor = ACTORS->getActor(actorNum);

				if (actor != NULL) {
					STACK.push(actor->_bIgnoreBoxes ? 0 : actor->_walkBox);
				}
				else {
					STACK.push(0);
				}
			}
			return;
			case OP_getActorMoving: {
				uint16 actorNum = STACK.pop();
				ActorData* actor = ACTORS->getActor(actorNum);

				if (actor != NULL) {
					STACK.push(actor->_moving);
				}
				else {
					STACK.push(0);
				}
			}
			return;
			case OP_getActorCostume: {
				uint16 actorNum = STACK.pop();
				ActorData* actor = ACTORS->getActor(actorNum);

				if (actor != NULL) {
					STACK.push(actor->_costume);
				}
				else {
					STACK.push(0);
				}
			}
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
			case OP_getObjectNewDir: {
				STACK.pop();
				/// NO_FEATURE(GS_THIS, "Not implemented OP_getObjectNewDir");
				STACK.push(0);
			}
			return;
			case OP_getObjectX: {
				uint16 objectNum = STACK.pop();
				/* TODO - Actors - I assume the ID < NUM_ACTORS */
				ObjectData* object = OBJECTS->findObject(objectNum);
				if (object != NULL) {
					STACK.push(object->_x);
				}
				else {
					STACK.push(0);
				}
			}
			return;
			case OP_getObjectY: {
				uint16 objectNum = STACK.pop();
				/* TODO - Actors - I assume the ID < NUM_ACTORS */
				ObjectData* object = OBJECTS->findObject(objectNum);
				if (object != NULL) {
					STACK.push(object->_y);
				}
				else {
					STACK.push(0);
				}
			}
			return;
			case OP_getActorChore: {
				uint16 actorNum = STACK.pop();
				ActorData* actor = ACTORS->getActor(actorNum);

				if (actor != NULL) {
					STACK.push(actor->_frame);
				}
				else {
					STACK.push(0);
				}
			}
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
