/* This is an automatically generated file */
#ifndef STATE
#error "STATE was not defined"
#endif
#ifndef OP
#error "OP was not defined"
#endif

#include "shared/forward.h"

GS_PRIVATE gs_bool decodeOpcode(STATE state)
{
	byte op1 = 0, op2 = 0;
	switch((op1 = READ_BYTE()))
	{
		case 0x00:
		{

			/**
			 * pushByte
			 * @param byte[1..1] value
			 */
			byte value = READ_BYTE();
			OP(pushByte, value);
		}
		return TRUE;
		case 0x01:
		{

			/**
			 * pushWord
			 * @param word[1..4] value
			 */
			int32 value = READ_WORD_AS_LONG();
			OP(pushWord, value);
		}
		return TRUE;
		case 0x02:
		{

			/**
			 * pushWordVar
			 * @param word[1..4] index
			 */
			int32 index = READ_WORD_AS_LONG();
			OP(pushWordVar, index);
		}
		return TRUE;
		case 0x03:
		{

			/**
			 * wordArrayRead
			 * @param word[1..4] arrayNum
			 * @param long[stack, 0] base
			 */
			int32 arrayNum = READ_WORD_AS_LONG();
			int32 base = PULL_LONG();
			OP(wordArrayRead, arrayNum, base);
		}
		return TRUE;
		case 0x04:
		{

			/**
			 * wordArrayIndexedRead
			 * @param word[1..4] arrayNum
			 * @param long[stack, 0] index
			 * @param long[stack,-1] base
			 */
			int32 arrayNum = READ_WORD_AS_LONG();
			int32 base = PULL_LONG();
			int32 index = PULL_LONG();
			OP(wordArrayIndexedRead, arrayNum, index, base);
		}
		return TRUE;
		case 0x05:
		{

			/**
			 * dup
			 * @param long[stack, 0] value
			 */
			int32 value = PULL_LONG();
			OP(dup, value);
		}
		return TRUE;
		case 0x06:
		{

			/**
			 * pop
			 * @param long[stack, 0] discard
			 */
			int32 discard = PULL_LONG();
			OP(pop, discard);
		}
		return TRUE;
		case 0x07:
		{

			/**
			 * not
			 * @param long[stack, 0] value
			 */
			int32 value = PULL_LONG();
			OP(not, value);
		}
		return TRUE;
		case 0x08:
		{

			/**
			 * eq
			 * @param long[stack, 0] a
			 * @param long[stack,-1] b
			 */
			int32 b = PULL_LONG();
			int32 a = PULL_LONG();
			OP(eq, a, b);
		}
		return TRUE;
		case 0x09:
		{

			/**
			 * neq
			 * @param long[stack, 0] a
			 * @param long[stack,-1] b
			 */
			int32 b = PULL_LONG();
			int32 a = PULL_LONG();
			OP(neq, a, b);
		}
		return TRUE;
		case 0x0A:
		{

			/**
			 * gt
			 * @param long[stack, 0] a
			 * @param long[stack,-1] b
			 */
			int32 b = PULL_LONG();
			int32 a = PULL_LONG();
			OP(gt, a, b);
		}
		return TRUE;
		case 0x0B:
		{

			/**
			 * lt
			 * @param long[stack, 0] a
			 * @param long[stack,-1] b
			 */
			int32 b = PULL_LONG();
			int32 a = PULL_LONG();
			OP(lt, a, b);
		}
		return TRUE;
		case 0x0C:
		{

			/**
			 * le
			 * @param long[stack, 0] a
			 * @param long[stack,-1] b
			 */
			int32 b = PULL_LONG();
			int32 a = PULL_LONG();
			OP(le, a, b);
		}
		return TRUE;
		case 0x0D:
		{

			/**
			 * ge
			 * @param long[stack, 0] a
			 * @param long[stack,-1] b
			 */
			int32 b = PULL_LONG();
			int32 a = PULL_LONG();
			OP(ge, a, b);
		}
		return TRUE;
		case 0x0E:
		{

			/**
			 * add
			 * @param long[stack, 0] a
			 * @param long[stack,-1] b
			 */
			int32 b = PULL_LONG();
			int32 a = PULL_LONG();
			OP(add, a, b);
		}
		return TRUE;
		case 0x0F:
		{

			/**
			 * sub
			 * @param long[stack, 0] a
			 * @param long[stack,-1] b
			 */
			int32 b = PULL_LONG();
			int32 a = PULL_LONG();
			OP(sub, a, b);
		}
		return TRUE;
		case 0x10:
		{

			/**
			 * mul
			 * @param long[stack, 0] a
			 * @param long[stack,-1] b
			 */
			int32 b = PULL_LONG();
			int32 a = PULL_LONG();
			OP(mul, a, b);
		}
		return TRUE;
		case 0x11:
		{

			/**
			 * div
			 * @param long[stack, 0] a
			 * @param long[stack,-1] b
			 */
			int32 b = PULL_LONG();
			int32 a = PULL_LONG();
			OP(div, a, b);
		}
		return TRUE;
		case 0x12:
		{

			/**
			 * land
			 * @param long[stack, 0] a
			 * @param long[stack,-1] b
			 */
			int32 b = PULL_LONG();
			int32 a = PULL_LONG();
			OP(land, a, b);
		}
		return TRUE;
		case 0x13:
		{

			/**
			 * lor
			 * @param long[stack, 0] a
			 * @param long[stack,-1] b
			 */
			int32 b = PULL_LONG();
			int32 a = PULL_LONG();
			OP(lor, a, b);
		}
		return TRUE;
		case 0x14:
		{

			/**
			 * band
			 * @param long[stack, 0] a
			 * @param long[stack,-1] b
			 */
			int32 b = PULL_LONG();
			int32 a = PULL_LONG();
			OP(band, a, b);
		}
		return TRUE;
		case 0x15:
		{

			/**
			 * bor
			 * @param long[stack, 0] a
			 * @param long[stack,-1] b
			 */
			int32 b = PULL_LONG();
			int32 a = PULL_LONG();
			OP(bor, a, b);
		}
		return TRUE;
		case 0x16:
		{

			/**
			 * mod
			 */
			OP(mod);
		}
		return TRUE;
		case 0x42:
		{

			/**
			 * writeByteVar
			 * @param long[stack, 0] value
			 */
			int32 value = PULL_LONG();
			OP(writeByteVar, value);
		}
		return TRUE;
		case 0x46:
		{

			/**
			 * byteArrayWrite
			 * @param long[stack, 0] base
			 * @param long[stack,-1] value
			 */
			int32 value = PULL_LONG();
			int32 base = PULL_LONG();
			OP(byteArrayWrite, base, value);
		}
		return TRUE;
		case 0x4A:
		{

			/**
			 * byteArrayIndexedWrite
			 * @param long[stack, 0] index
			 * @param long[stack,-1] base
			 * @param long[stack,-2] value
			 */
			int32 value = PULL_LONG();
			int32 base = PULL_LONG();
			int32 index = PULL_LONG();
			OP(byteArrayIndexedWrite, index, base, value);
		}
		return TRUE;
		case 0x4E:
		{

			/**
			 * byteVarInc
			 */
			OP(byteVarInc);
		}
		return TRUE;
		case 0x52:
		{

			/**
			 * byteArrayInc
			 * @param long[stack, 0] base
			 */
			int32 base = PULL_LONG();
			OP(byteArrayInc, base);
		}
		return TRUE;
		case 0x56:
		{

			/**
			 * byteVarDec
			 */
			OP(byteVarDec);
		}
		return TRUE;
		case 0x5A:
		{

			/**
			 * byteArrayDec
			 * @param long[stack, 0] base
			 */
			int32 base = PULL_LONG();
			OP(byteArrayDec, base);
		}
		return TRUE;
		case 0x61:
		{

			/**
			 * drawObject
			 * @param long[stack, 0] obj
			 * @param long[stack,-1] state
			 */
			int32 state = PULL_LONG();
			int32 obj = PULL_LONG();
			OP(drawObject, obj, state);
		}
		return TRUE;
		case 0x62:
		{

			/**
			 * drawObjectAt
			 * @param long[stack, 0] obj
			 * @param long[stack,-1] x
			 * @param long[stack,-2] y
			 */
			int32 y = PULL_LONG();
			int32 x = PULL_LONG();
			int32 obj = PULL_LONG();
			OP(drawObjectAt, obj, x, y);
		}
		return TRUE;
		case 0x63:
		{

			/**
			 * drawBlastObject
			 * @param long[stack, 0] a
			 * @param long[stack,-1] b
			 * @param long[stack,-2] c
			 * @param long[stack,-3] d
			 * @param long[stack,-4] e
			 * @param args[stack,-5] args
			 */
			int* args = PULL_ARGS();
			int32 e = PULL_LONG();
			int32 d = PULL_LONG();
			int32 c = PULL_LONG();
			int32 b = PULL_LONG();
			int32 a = PULL_LONG();
			OP(drawBlastObject, a, b, c, d, e, args);
		}
		return TRUE;
		case 0x64:
		{

			/**
			 * if
			 * @param word[1..4] relOffset
			 * @param long[stack, 0] condition
			 */
			int32 relOffset = READ_WORD_AS_LONG();
			int32 condition = PULL_LONG();
			OP(if, condition, relOffset);
		}
		return TRUE;
		case 0x65:
		{

			/**
			 * ifNot
			 * @param word[1..4] relOffset
			 * @param long[stack, 0] condition
			 */
			int32 relOffset = READ_WORD_AS_LONG();
			int32 condition = PULL_LONG();
			OP(ifNot, condition, relOffset);
		}
		return TRUE;
		case 0x66:
		{

			/**
			 * jump
			 * @param word[1..4] relOffset
			 */
			int32 relOffset = READ_WORD_AS_LONG();
			OP(jump, relOffset);
		}
		return TRUE;
		case 0x67:
		{

			/**
			 * breakHere
			 */
			OP(breakHere);
		}
		return TRUE;
		case 0x68:
		{

			/**
			 * delayFrames
			 */
			OP(delayFrames);
		}
		return TRUE;
		case 0x69:
		{
			switch((op2 = READ_BYTE()))
			{
				case 0x1E:
				{

					/**
					 * waitForActor
					 * @param word[2..5] actorNum
					 * @param long[stack, 0] offset
					 */
					int32 actorNum = READ_WORD_AS_LONG();
					int32 offset = PULL_LONG();
					OP(waitForActor, offset, actorNum);
				}
				return TRUE;
				case 0x1F:
				{

					/**
					 * waitForMessage
					 * @const offset = -2
					 */
					OP(waitForMessage, -2);
				}
				return TRUE;
				case 0x20:
				{

					/**
					 * waitForCamera
					 * @const offset = -2
					 */
					OP(waitForCamera, -2);
				}
				return TRUE;
				case 0x21:
				{

					/**
					 * waitForSentence
					 * @const offset = -2
					 */
					OP(waitForSentence, -2);
				}
				return TRUE;
				case 0x22:
				{

					/**
					 * waitForAnimation
					 * @param word[2..5] actorNum
					 * @param long[stack, 0] offset
					 */
					int32 actorNum = READ_WORD_AS_LONG();
					int32 offset = PULL_LONG();
					OP(waitForAnimation, offset, actorNum);
				}
				return TRUE;
				case 0x23:
				{

					/**
					 * waitForTurn
					 * @param word[2..5] actorNum
					 * @param long[stack, 0] offset
					 */
					int32 actorNum = READ_WORD_AS_LONG();
					int32 offset = PULL_LONG();
					OP(waitForTurn, offset, actorNum);
				}
				return TRUE;
			}
		}
		return FALSE;
		case 0x6A:
		{

			/**
			 * delay
			 * @param long[stack, 0] delay
			 */
			int32 delay = PULL_LONG();
			OP(delay, delay);
		}
		return TRUE;
		case 0x6B:
		{

			/**
			 * delaySeconds
			 * @param long[stack, 0] seconds
			 */
			int32 seconds = PULL_LONG();
			OP(delaySeconds, seconds);
		}
		return TRUE;
		case 0x6C:
		{

			/**
			 * delayMinutes
			 * @param long[stack, 0] minutes
			 */
			int32 minutes = PULL_LONG();
			OP(delayMinutes, minutes);
		}
		return TRUE;
		case 0x6D:
		{

			/**
			 * writeWordVar
			 * @param long[1..4] varIndex
			 * @param long[stack, 0] value
			 */
			int32 varIndex = READ_LONG();
			int32 value = PULL_LONG();
			OP(writeWordVar, varIndex, value);
		}
		return TRUE;
		case 0x6E:
		{

			/**
			 * wordVarInc
			 * @param long[1..4] varIndex
			 */
			int32 varIndex = READ_LONG();
			OP(wordVarInc, varIndex);
		}
		return TRUE;
		case 0x6F:
		{

			/**
			 * wordVarDec
			 * @param long[1..4] varIndex
			 */
			int32 varIndex = READ_LONG();
			OP(wordVarDec, varIndex);
		}
		return TRUE;
		case 0x70:
		{
			switch((op2 = READ_BYTE()))
			{
				case 0x0A:
				{

					/**
					 * newIntArray
					 * @param word[2..5] arrayNum
					 * @param long[stack, 0] dim1
					 */
					int32 arrayNum = READ_WORD_AS_LONG();
					int32 dim1 = PULL_LONG();
					OP(newIntArray, arrayNum, dim1);
				}
				return TRUE;
				case 0x0B:
				{

					/**
					 * newStringArray
					 * @param word[2..5] arrayNum
					 * @param long[stack, 0] dim1
					 */
					int32 arrayNum = READ_WORD_AS_LONG();
					int32 dim1 = PULL_LONG();
					OP(newStringArray, arrayNum, dim1);
				}
				return TRUE;
				case 0x0C:
				{

					/**
					 * deleteArray
					 * @param word[2..5] arrayNum
					 */
					int32 arrayNum = READ_WORD_AS_LONG();
					OP(deleteArray, arrayNum);
				}
				return TRUE;
			}
		}
		return FALSE;
		case 0x71:
		{

			/**
			 * wordArrayWrite
			 * @param word[1..4] arrayNum
			 * @param long[stack, 0] base
			 * @param long[stack,-1] value
			 */
			int32 arrayNum = READ_WORD_AS_LONG();
			int32 value = PULL_LONG();
			int32 base = PULL_LONG();
			OP(wordArrayWrite, arrayNum, base, value);
		}
		return TRUE;
		case 0x72:
		{

			/**
			 * wordArrayInc
			 * @param word[1..4] arrayNum
			 * @param long[stack, 0] base
			 */
			int32 arrayNum = READ_WORD_AS_LONG();
			int32 base = PULL_LONG();
			OP(wordArrayInc, arrayNum, base);
		}
		return TRUE;
		case 0x73:
		{

			/**
			 * wordArrayDec
			 * @param word[1..4] arrayNum
			 * @param long[stack, 0] base
			 */
			int32 arrayNum = READ_WORD_AS_LONG();
			int32 base = PULL_LONG();
			OP(wordArrayDec, arrayNum, base);
		}
		return TRUE;
		case 0x74:
		{
			switch((op2 = READ_BYTE()))
			{
				case 0x0A:
				{

					/**
					 * newIntArray2
					 * @param word[2..5] arrayNum
					 * @param long[stack, 0] dim1
					 * @param long[stack,-1] dim2
					 */
					int32 arrayNum = READ_WORD_AS_LONG();
					int32 dim2 = PULL_LONG();
					int32 dim1 = PULL_LONG();
					OP(newIntArray2, arrayNum, dim1, dim2);
				}
				return TRUE;
				case 0x0B:
				{

					/**
					 * newStringArray2
					 * @param word[2..5] arrayNum
					 * @param long[stack, 0] dim1
					 * @param long[stack,-1] dim2
					 */
					int32 arrayNum = READ_WORD_AS_LONG();
					int32 dim2 = PULL_LONG();
					int32 dim1 = PULL_LONG();
					OP(newStringArray2, arrayNum, dim1, dim2);
				}
				return TRUE;
				case 0x0C:
				{

					/**
					 * deleteARray2
					 * @param word[2..5] arrayNum
					 * @param long[stack, 0] dim1
					 * @param long[stack,-1] dim2
					 */
					int32 arrayNum = READ_WORD_AS_LONG();
					int32 dim2 = PULL_LONG();
					int32 dim1 = PULL_LONG();
					OP(deleteARray2, arrayNum, dim1, dim2);
				}
				return TRUE;
			}
		}
		return FALSE;
		case 0x75:
		{

			/**
			 * wordArrayIndexedWrite
			 * @param word[1..4] arrayNum
			 * @param long[stack, 0] index
			 * @param long[stack,-1] base
			 * @param long[stack,-2] value
			 */
			int32 arrayNum = READ_WORD_AS_LONG();
			int32 value = PULL_LONG();
			int32 base = PULL_LONG();
			int32 index = PULL_LONG();
			OP(wordArrayIndexedWrite, arrayNum, index, base, value);
		}
		return TRUE;
		case 0x76:
		{
			switch((op2 = READ_BYTE()))
			{
				case 0x14:
				{

					/**
					 * copyStringArray
					 * @param word[2..5] arrayNum
					 * @param string[6...] data
					 * @param long[stack, 0] b
					 */
					int32 arrayNum = READ_WORD_AS_LONG();
					byte* data = READ_STRING();
					int32 b = PULL_LONG();
					OP(copyStringArray, arrayNum, data, b);
				}
				return TRUE;
				case 0x15:
				{

					/**
					 * copyIntArray
					 * @param word[2..5] arrayNum
					 * @param args[stack, 0] args
					 * @param long[stack,-1] b
					 */
					int32 arrayNum = READ_WORD_AS_LONG();
					int32 b = PULL_LONG();
					int* args = PULL_ARGS();
					OP(copyIntArray, arrayNum, args, b);
				}
				return TRUE;
				case 0x16:
				{

					/**
					 * copyDim2Array
					 * @param word[2..5] arrayNum
					 * @param args[stack, 0] args
					 * @param long[stack,-1] b
					 */
					int32 arrayNum = READ_WORD_AS_LONG();
					int32 b = PULL_LONG();
					int* args = PULL_ARGS();
					OP(copyDim2Array, arrayNum, args, b);
				}
				return TRUE;
			}
		}
		return FALSE;
		case 0x79:
		{

			/**
			 * startScript
			 * @param long[stack, 0] flags
			 * @param long[stack,-1] script
			 * @param args[stack,-2] args
			 */
			int* args = PULL_ARGS();
			int32 script = PULL_LONG();
			int32 flags = PULL_LONG();
			OP(startScript, flags, script, args);
		}
		return TRUE;
		case 0x7A:
		{

			/**
			 * startScriptQuick
			 * @param long[stack, 0] script
			 * @param args[stack,-1] args
			 */
			int* args = PULL_ARGS();
			int32 script = PULL_LONG();
			OP(startScriptQuick, script, args);
		}
		return TRUE;
		case 0x7B:
		{

			/**
			 * stopObjectCode6
			 */
			OP(stopObjectCode6);
		}
		return TRUE;
		case 0x7C:
		{

			/**
			 * stopScript6
			 * @param long[stack, 0] script
			 */
			int32 script = PULL_LONG();
			OP(stopScript6, script);
		}
		return TRUE;
		case 0x7D:
		{

			/**
			 * jumpToScript
			 * @param long[stack, 0] flags
			 * @param long[stack,-1] script
			 * @param args[stack,-2] args
			 */
			int* args = PULL_ARGS();
			int32 script = PULL_LONG();
			int32 flags = PULL_LONG();
			OP(jumpToScript, flags, script, args);
		}
		return TRUE;
		case 0x7E:
		{

			/**
			 * dummy
			 */
			OP(dummy);
		}
		return TRUE;
		case 0x7F:
		{

			/**
			 * startObject
			 * @param long[stack, 0] flags
			 * @param long[stack,-1] script
			 * @param byte[stack,-2] entryp
			 * @param args[stack,-3] args
			 */
			int* args = PULL_ARGS();
			byte entryp = PULL_BYTE();
			int32 script = PULL_LONG();
			int32 flags = PULL_LONG();
			OP(startObject, flags, script, entryp, args);
		}
		return TRUE;
		case 0x80:
		{

			/**
			 * stopObjectScript
			 * @param word[stack, 0] script
			 */
			int16 script = PULL_WORD();
			OP(stopObjectScript, script);
		}
		return TRUE;
		case 0x81:
		{

			/**
			 * cutscene
			 * @param args[stack, 0] args
			 */
			int* args = PULL_ARGS();
			OP(cutscene, args);
		}
		return TRUE;
		case 0x82:
		{

			/**
			 * endCutscene
			 */
			OP(endCutscene);
		}
		return TRUE;
		case 0x83:
		{

			/**
			 * freezeUnfreeze
			 * @param long[stack, 0] scriptNum
			 */
			int32 scriptNum = PULL_LONG();
			OP(freezeUnfreeze, scriptNum);
		}
		return TRUE;
		case 0x84:
		{

			/**
			 * beginOverride
			 */
			OP(beginOverride);
		}
		return TRUE;
		case 0x85:
		{

			/**
			 * endOverride
			 */
			OP(endOverride);
		}
		return TRUE;
		case 0x86:
		{

			/**
			 * stopSentence
			 */
			OP(stopSentence);
		}
		return TRUE;
		case 0x87:
		{

			/**
			 * debug
			 */
			OP(debug);
		}
		return TRUE;
		case 0x89:
		{

			/**
			 * setClass
			 * @param long[stack, 0] obj
			 * @param args[stack,-1] args
			 */
			int* args = PULL_ARGS();
			int32 obj = PULL_LONG();
			OP(setClass, obj, args);
		}
		return TRUE;
		case 0x8A:
		{

			/**
			 * setState
			 * @param long[stack, 0] obj
			 * @param long[stack,-1] state
			 */
			int32 state = PULL_LONG();
			int32 obj = PULL_LONG();
			OP(setState, obj, state);
		}
		return TRUE;
		case 0x8B:
		{

			/**
			 * setOwner
			 * @param long[stack, 0] obj
			 * @param long[stack,-1] owner
			 */
			int32 owner = PULL_LONG();
			int32 obj = PULL_LONG();
			OP(setOwner, obj, owner);
		}
		return TRUE;
		case 0x8C:
		{

			/**
			 * panCameraTo
			 */
			OP(panCameraTo);
		}
		return TRUE;
		case 0x8D:
		{

			/**
			 * actorFollowCamera
			 * @param long[stack, 0] index
			 */
			int32 index = PULL_LONG();
			OP(actorFollowCamera, index);
		}
		return TRUE;
		case 0x8E:
		{

			/**
			 * setCameraAt
			 */
			OP(setCameraAt);
		}
		return TRUE;
		case 0x8F:
		{
			switch((op2 = READ_BYTE()))
			{
				case 0xC8:
				{

					/**
					 * printActor_ResetState
					 * @const target = 0
					 * @const pullActor = 1
					 */
					OP(printActor_ResetState, 0, 1);
				}
				return TRUE;
				case 0xC9:
				{

					/**
					 * printActor_SaveState
					 * @const target = 0
					 * @const pullActor = 1
					 */
					OP(printActor_SaveState, 0, 1);
				}
				return TRUE;
				case 0xCA:
				{

					/**
					 * printActor_SetPos
					 * @param word[stack, 0] x
					 * @param word[stack,-1] y
					 * @const target = 0
					 * @const pullActor = 1
					 */
					int16 y = PULL_WORD();
					int16 x = PULL_WORD();
					OP(printActor_SetPos, x, y, 0, 1);
				}
				return TRUE;
				case 0xCB:
				{

					/**
					 * printActor_SetColor
					 * @param byte[stack, 0] index
					 * @const target = 0
					 * @const pullActor = 1
					 */
					byte index = PULL_BYTE();
					OP(printActor_SetColor, index, 0, 1);
				}
				return TRUE;
				case 0xCC:
				{

					/**
					 * printActor_AlignCenter
					 * @const target = 0
					 * @const pullActor = 1
					 */
					OP(printActor_AlignCenter, 0, 1);
				}
				return TRUE;
				case 0xCD:
				{

					/**
					 * printActor_SetCharSet
					 * @param word[stack, 0] charsetNum
					 * @const target = 0
					 * @const pullActor = 1
					 */
					int16 charsetNum = PULL_WORD();
					OP(printActor_SetCharSet, charsetNum, 0, 1);
				}
				return TRUE;
				case 0xCE:
				{

					/**
					 * printActor_AlignLeft
					 * @const target = 0
					 * @const pullActor = 1
					 */
					OP(printActor_AlignLeft, 0, 1);
				}
				return TRUE;
				case 0xCF:
				{

					/**
					 * printActor_SetOverhead
					 * @const target = 0
					 * @const pullActor = 1
					 */
					OP(printActor_SetOverhead, 0, 1);
				}
				return TRUE;
				case 0xD0:
				{

					/**
					 * printActor_SetMumble
					 * @const target = 0
					 * @const pullActor = 1
					 */
					OP(printActor_SetMumble, 0, 1);
				}
				return TRUE;
				case 0xD1:
				{

					/**
					 * printActor
					 * @param string[2...] text
					 * @const target = 0
					 * @const pullActor = 1
					 */
					byte* text = READ_STRING();
					OP(printActor, text, 0, 1);
				}
				return TRUE;
				case 0xD2:
				{

					/**
					 * printActor_SetWrapped
					 * @const target = 0
					 * @const pullActor = 1
					 */
					OP(printActor_SetWrapped, 0, 1);
				}
				return TRUE;
			}
		}
		return FALSE;
		case 0x90:
		{
			switch((op2 = READ_BYTE()))
			{
				case 0xC8:
				{

					/**
					 * printEgo_ResetState
					 * @const target = 0
					 * @const pullActor = 2
					 */
					OP(printEgo_ResetState, 0, 2);
				}
				return TRUE;
				case 0xC9:
				{

					/**
					 * printEgo_SaveState
					 * @const target = 0
					 * @const pullActor = 2
					 */
					OP(printEgo_SaveState, 0, 2);
				}
				return TRUE;
				case 0xCA:
				{

					/**
					 * printEgo_SetPos
					 * @param word[stack, 0] x
					 * @param word[stack,-1] y
					 * @const target = 0
					 * @const pullActor = 2
					 */
					int16 y = PULL_WORD();
					int16 x = PULL_WORD();
					OP(printEgo_SetPos, x, y, 0, 2);
				}
				return TRUE;
				case 0xCB:
				{

					/**
					 * printEgo_SetColor
					 * @param byte[stack, 0] index
					 * @const target = 0
					 * @const pullActor = 2
					 */
					byte index = PULL_BYTE();
					OP(printEgo_SetColor, index, 0, 2);
				}
				return TRUE;
				case 0xCC:
				{

					/**
					 * printEgo_AlignCenter
					 * @const target = 0
					 * @const pullActor = 2
					 */
					OP(printEgo_AlignCenter, 0, 2);
				}
				return TRUE;
				case 0xCD:
				{

					/**
					 * printEgo_SetCharSet
					 * @param word[stack, 0] charsetNum
					 * @const target = 0
					 * @const pullActor = 2
					 */
					int16 charsetNum = PULL_WORD();
					OP(printEgo_SetCharSet, charsetNum, 0, 2);
				}
				return TRUE;
				case 0xCE:
				{

					/**
					 * printEgo_AlignLeft
					 * @const target = 0
					 * @const pullActor = 2
					 */
					OP(printEgo_AlignLeft, 0, 2);
				}
				return TRUE;
				case 0xCF:
				{

					/**
					 * printEgo_SetOverhead
					 * @const target = 0
					 * @const pullActor = 2
					 */
					OP(printEgo_SetOverhead, 0, 2);
				}
				return TRUE;
				case 0xD0:
				{

					/**
					 * printEgo_SetMumble
					 * @const target = 0
					 * @const pullActor = 2
					 */
					OP(printEgo_SetMumble, 0, 2);
				}
				return TRUE;
				case 0xD1:
				{

					/**
					 * printEgo
					 * @param string[2...] text
					 * @const target = 0
					 * @const pullActor = 2
					 */
					byte* text = READ_STRING();
					OP(printEgo, text, 0, 2);
				}
				return TRUE;
				case 0xD2:
				{

					/**
					 * printEgo_SetWrapped
					 * @const target = 0
					 * @const pullActor = 2
					 */
					OP(printEgo_SetWrapped, 0, 2);
				}
				return TRUE;
			}
		}
		return FALSE;
		case 0x91:
		{

			/**
			 * talkActor
			 * @param string[1...] text
			 * @param word[stack, 0] actorNum
			 */
			byte* text = READ_STRING();
			int16 actorNum = PULL_WORD();
			OP(talkActor, actorNum, text);
		}
		return TRUE;
		case 0x92:
		{

			/**
			 * talkEgo
			 * @param string[1...] text
			 */
			byte* text = READ_STRING();
			OP(talkEgo, text);
		}
		return TRUE;
		case 0x93:
		{
			switch((op2 = READ_BYTE()))
			{
				case 0xC8:
				{

					/**
					 * printLine_ResetState
					 * @const target = 0
					 * @const pullActor = 0
					 */
					OP(printLine_ResetState, 0, 0);
				}
				return TRUE;
				case 0xC9:
				{

					/**
					 * printLine_SaveState
					 * @const target = 0
					 * @const pullActor = 0
					 */
					OP(printLine_SaveState, 0, 0);
				}
				return TRUE;
				case 0xCA:
				{

					/**
					 * printLine_SetPos
					 * @param word[stack, 0] x
					 * @param word[stack,-1] y
					 * @const target = 0
					 * @const pullActor = 0
					 */
					int16 y = PULL_WORD();
					int16 x = PULL_WORD();
					OP(printLine_SetPos, x, y, 0, 0);
				}
				return TRUE;
				case 0xCB:
				{

					/**
					 * printLine_SetColor
					 * @param byte[stack, 0] index
					 * @const target = 0
					 * @const pullActor = 0
					 */
					byte index = PULL_BYTE();
					OP(printLine_SetColor, index, 0, 0);
				}
				return TRUE;
				case 0xCC:
				{

					/**
					 * printLine_AlignCenter
					 * @const target = 0
					 * @const pullActor = 0
					 */
					OP(printLine_AlignCenter, 0, 0);
				}
				return TRUE;
				case 0xCD:
				{

					/**
					 * printLine_SetCharSet
					 * @param word[stack, 0] charsetNum
					 * @const target = 0
					 * @const pullActor = 0
					 */
					int16 charsetNum = PULL_WORD();
					OP(printLine_SetCharSet, charsetNum, 0, 0);
				}
				return TRUE;
				case 0xCE:
				{

					/**
					 * printLine_AlignLeft
					 * @const target = 0
					 * @const pullActor = 0
					 */
					OP(printLine_AlignLeft, 0, 0);
				}
				return TRUE;
				case 0xCF:
				{

					/**
					 * printLine_SetOverhead
					 * @const target = 0
					 * @const pullActor = 0
					 */
					OP(printLine_SetOverhead, 0, 0);
				}
				return TRUE;
				case 0xD0:
				{

					/**
					 * printLine_SetMumble
					 * @const target = 0
					 * @const pullActor = 0
					 */
					OP(printLine_SetMumble, 0, 0);
				}
				return TRUE;
				case 0xD1:
				{

					/**
					 * printLine
					 * @param string[2...] text
					 * @const target = 0
					 * @const pullActor = 0
					 */
					byte* text = READ_STRING();
					OP(printLine, text, 0, 0);
				}
				return TRUE;
				case 0xD2:
				{

					/**
					 * printLine_SetWrapped
					 * @const target = 0
					 * @const pullActor = 0
					 */
					OP(printLine_SetWrapped, 0, 0);
				}
				return TRUE;
			}
		}
		return FALSE;
		case 0x94:
		{
			switch((op2 = READ_BYTE()))
			{
				case 0xC8:
				{

					/**
					 * printText_ResetState
					 * @const target = 1
					 * @const pullActor = 0
					 */
					OP(printText_ResetState, 1, 0);
				}
				return TRUE;
				case 0xC9:
				{

					/**
					 * printText_SaveState
					 * @const target = 1
					 * @const pullActor = 0
					 */
					OP(printText_SaveState, 1, 0);
				}
				return TRUE;
				case 0xCA:
				{

					/**
					 * printText_SetPos
					 * @param word[stack, 0] x
					 * @param word[stack,-1] y
					 * @const target = 1
					 * @const pullActor = 0
					 */
					int16 y = PULL_WORD();
					int16 x = PULL_WORD();
					OP(printText_SetPos, x, y, 1, 0);
				}
				return TRUE;
				case 0xCB:
				{

					/**
					 * printText_SetColor
					 * @param byte[stack, 0] index
					 * @const target = 1
					 * @const pullActor = 0
					 */
					byte index = PULL_BYTE();
					OP(printText_SetColor, index, 1, 0);
				}
				return TRUE;
				case 0xCC:
				{

					/**
					 * printText_AlignCenter
					 * @const target = 1
					 * @const pullActor = 0
					 */
					OP(printText_AlignCenter, 1, 0);
				}
				return TRUE;
				case 0xCD:
				{

					/**
					 * printText_SetCharSet
					 * @param word[stack, 0] charsetNum
					 * @const target = 1
					 * @const pullActor = 0
					 */
					int16 charsetNum = PULL_WORD();
					OP(printText_SetCharSet, charsetNum, 1, 0);
				}
				return TRUE;
				case 0xCE:
				{

					/**
					 * printText_AlignLeft
					 * @const target = 1
					 * @const pullActor = 0
					 */
					OP(printText_AlignLeft, 1, 0);
				}
				return TRUE;
				case 0xCF:
				{

					/**
					 * printText_SetOverhead
					 * @const target = 1
					 * @const pullActor = 0
					 */
					OP(printText_SetOverhead, 1, 0);
				}
				return TRUE;
				case 0xD0:
				{

					/**
					 * printText_SetMumble
					 * @const target = 1
					 * @const pullActor = 0
					 */
					OP(printText_SetMumble, 1, 0);
				}
				return TRUE;
				case 0xD1:
				{

					/**
					 * printText
					 * @param string[2...] text
					 * @const target = 1
					 * @const pullActor = 0
					 */
					byte* text = READ_STRING();
					OP(printText, text, 1, 0);
				}
				return TRUE;
				case 0xD2:
				{

					/**
					 * printText_SetWrapped
					 * @const target = 1
					 * @const pullActor = 0
					 */
					OP(printText_SetWrapped, 1, 0);
				}
				return TRUE;
			}
		}
		return FALSE;
		case 0x95:
		{
			switch((op2 = READ_BYTE()))
			{
				case 0xC8:
				{

					/**
					 * printDebug_ResetState
					 * @const target = 2
					 * @const pullActor = 0
					 */
					OP(printDebug_ResetState, 2, 0);
				}
				return TRUE;
				case 0xC9:
				{

					/**
					 * printDebug_SaveState
					 * @const target = 2
					 * @const pullActor = 0
					 */
					OP(printDebug_SaveState, 2, 0);
				}
				return TRUE;
				case 0xCA:
				{

					/**
					 * printDebug_SetPos
					 * @param word[stack, 0] x
					 * @param word[stack,-1] y
					 * @const target = 2
					 * @const pullActor = 0
					 */
					int16 y = PULL_WORD();
					int16 x = PULL_WORD();
					OP(printDebug_SetPos, x, y, 2, 0);
				}
				return TRUE;
				case 0xCB:
				{

					/**
					 * printDebug_SetColor
					 * @param byte[stack, 0] index
					 * @const target = 2
					 * @const pullActor = 0
					 */
					byte index = PULL_BYTE();
					OP(printDebug_SetColor, index, 2, 0);
				}
				return TRUE;
				case 0xCC:
				{

					/**
					 * printDebug_AlignCenter
					 * @const target = 2
					 * @const pullActor = 0
					 */
					OP(printDebug_AlignCenter, 2, 0);
				}
				return TRUE;
				case 0xCD:
				{

					/**
					 * printDebug_SetCharSet
					 * @param word[stack, 0] charsetNum
					 * @const target = 2
					 * @const pullActor = 0
					 */
					int16 charsetNum = PULL_WORD();
					OP(printDebug_SetCharSet, charsetNum, 2, 0);
				}
				return TRUE;
				case 0xCE:
				{

					/**
					 * printDebug_AlignLeft
					 * @const target = 2
					 * @const pullActor = 0
					 */
					OP(printDebug_AlignLeft, 2, 0);
				}
				return TRUE;
				case 0xCF:
				{

					/**
					 * printDebug_SetOverhead
					 * @const target = 2
					 * @const pullActor = 0
					 */
					OP(printDebug_SetOverhead, 2, 0);
				}
				return TRUE;
				case 0xD0:
				{

					/**
					 * printDebug_SetMumble
					 * @const target = 2
					 * @const pullActor = 0
					 */
					OP(printDebug_SetMumble, 2, 0);
				}
				return TRUE;
				case 0xD1:
				{

					/**
					 * printDebug
					 * @param string[2...] text
					 * @const target = 2
					 * @const pullActor = 0
					 */
					byte* text = READ_STRING();
					OP(printDebug, text, 2, 0);
				}
				return TRUE;
				case 0xD2:
				{

					/**
					 * printDebug_SetWrapped
					 * @const target = 2
					 * @const pullActor = 0
					 */
					OP(printDebug_SetWrapped, 2, 0);
				}
				return TRUE;
			}
		}
		return FALSE;
		case 0x96:
		{
			switch((op2 = READ_BYTE()))
			{
				case 0xC8:
				{

					/**
					 * printSystem_ResetState
					 * @const target = 3
					 * @const pullActor = 0
					 */
					OP(printSystem_ResetState, 3, 0);
				}
				return TRUE;
				case 0xC9:
				{

					/**
					 * printSystem_SaveState
					 * @const target = 3
					 * @const pullActor = 0
					 */
					OP(printSystem_SaveState, 3, 0);
				}
				return TRUE;
				case 0xCA:
				{

					/**
					 * printSystem_SetPos
					 * @param word[stack, 0] x
					 * @param word[stack,-1] y
					 * @const target = 3
					 * @const pullActor = 0
					 */
					int16 y = PULL_WORD();
					int16 x = PULL_WORD();
					OP(printSystem_SetPos, x, y, 3, 0);
				}
				return TRUE;
				case 0xCB:
				{

					/**
					 * printSystem_SetColor
					 * @param byte[stack, 0] index
					 * @const target = 3
					 * @const pullActor = 0
					 */
					byte index = PULL_BYTE();
					OP(printSystem_SetColor, index, 3, 0);
				}
				return TRUE;
				case 0xCC:
				{

					/**
					 * printSystem_AlignCenter
					 * @const target = 3
					 * @const pullActor = 0
					 */
					OP(printSystem_AlignCenter, 3, 0);
				}
				return TRUE;
				case 0xCD:
				{

					/**
					 * printSystem_SetCharSet
					 * @param word[stack, 0] charsetNum
					 * @const target = 3
					 * @const pullActor = 0
					 */
					int16 charsetNum = PULL_WORD();
					OP(printSystem_SetCharSet, charsetNum, 3, 0);
				}
				return TRUE;
				case 0xCE:
				{

					/**
					 * printSystem_AlignLeft
					 * @const target = 3
					 * @const pullActor = 0
					 */
					OP(printSystem_AlignLeft, 3, 0);
				}
				return TRUE;
				case 0xCF:
				{

					/**
					 * printSystem_SetOverhead
					 * @const target = 3
					 * @const pullActor = 0
					 */
					OP(printSystem_SetOverhead, 3, 0);
				}
				return TRUE;
				case 0xD0:
				{

					/**
					 * printSystem_SetMumble
					 * @const target = 3
					 * @const pullActor = 0
					 */
					OP(printSystem_SetMumble, 3, 0);
				}
				return TRUE;
				case 0xD1:
				{

					/**
					 * printSystem
					 * @param string[2...] text
					 * @const target = 3
					 * @const pullActor = 0
					 */
					byte* text = READ_STRING();
					OP(printSystem, text, 3, 0);
				}
				return TRUE;
				case 0xD2:
				{

					/**
					 * printSystem_SetWrapped
					 * @const target = 3
					 * @const pullActor = 0
					 */
					OP(printSystem_SetWrapped, 3, 0);
				}
				return TRUE;
			}
		}
		return FALSE;
		case 0x97:
		{
			switch((op2 = READ_BYTE()))
			{
				case 0xC8:
				{

					/**
					 * blastText_ResetState
					 * @const target = 4
					 * @const pullActor = 0
					 */
					OP(blastText_ResetState, 4, 0);
				}
				return TRUE;
				case 0xC9:
				{

					/**
					 * blastText_SaveState
					 * @const target = 4
					 * @const pullActor = 0
					 */
					OP(blastText_SaveState, 4, 0);
				}
				return TRUE;
				case 0xCA:
				{

					/**
					 * blastText_SetPos
					 * @param word[stack, 0] x
					 * @param word[stack,-1] y
					 * @const target = 4
					 * @const pullActor = 0
					 */
					int16 y = PULL_WORD();
					int16 x = PULL_WORD();
					OP(blastText_SetPos, x, y, 4, 0);
				}
				return TRUE;
				case 0xCB:
				{

					/**
					 * blastText_SetColor
					 * @param byte[stack, 0] index
					 * @const target = 4
					 * @const pullActor = 0
					 */
					byte index = PULL_BYTE();
					OP(blastText_SetColor, index, 4, 0);
				}
				return TRUE;
				case 0xCC:
				{

					/**
					 * blastText_AlignCenter
					 * @const target = 4
					 * @const pullActor = 0
					 */
					OP(blastText_AlignCenter, 4, 0);
				}
				return TRUE;
				case 0xCD:
				{

					/**
					 * blastText_SetCharSet
					 * @param word[stack, 0] charsetNum
					 * @const target = 4
					 * @const pullActor = 0
					 */
					int16 charsetNum = PULL_WORD();
					OP(blastText_SetCharSet, charsetNum, 4, 0);
				}
				return TRUE;
				case 0xCE:
				{

					/**
					 * blastText_AlignLeft
					 * @const target = 4
					 * @const pullActor = 0
					 */
					OP(blastText_AlignLeft, 4, 0);
				}
				return TRUE;
				case 0xCF:
				{

					/**
					 * blastText_SetOverhead
					 * @const target = 4
					 * @const pullActor = 0
					 */
					OP(blastText_SetOverhead, 4, 0);
				}
				return TRUE;
				case 0xD0:
				{

					/**
					 * blastText_SetMumble
					 * @const target = 4
					 * @const pullActor = 0
					 */
					OP(blastText_SetMumble, 4, 0);
				}
				return TRUE;
				case 0xD1:
				{

					/**
					 * blastText
					 * @param string[2...] text
					 * @const target = 4
					 * @const pullActor = 0
					 */
					byte* text = READ_STRING();
					OP(blastText, text, 4, 0);
				}
				return TRUE;
				case 0xD2:
				{

					/**
					 * blastText_SetWrapped
					 * @const target = 4
					 * @const pullActor = 0
					 */
					OP(blastText_SetWrapped, 4, 0);
				}
				return TRUE;
			}
		}
		return FALSE;
		case 0x98:
		{

			/**
			 * drawObject
			 * @param long[stack, 0] obj
			 * @param long[stack,-1] x
			 * @param long[stack,-2] y
			 * @param long[stack,-3] state
			 */
			int32 state = PULL_LONG();
			int32 y = PULL_LONG();
			int32 x = PULL_LONG();
			int32 obj = PULL_LONG();
			OP(drawObject, obj, x, y, state);
		}
		return TRUE;
		case 0x9C:
		{
			switch((op2 = READ_BYTE()))
			{
				case 0xDC:
				{

					/**
					 * cursorSetOn
					 */
					OP(cursorSetOn);
				}
				return TRUE;
				case 0xDD:
				{

					/**
					 * cursorSetOff
					 */
					OP(cursorSetOff);
				}
				return TRUE;
				case 0xDE:
				{

					/**
					 * cursorSetSoftOn
					 */
					OP(cursorSetSoftOn);
				}
				return TRUE;
				case 0xDF:
				{

					/**
					 * cursorSetSoftOff
					 */
					OP(cursorSetSoftOff);
				}
				return TRUE;
				case 0xE0:
				{

					/**
					 * cursorSetUserPutOn
					 */
					OP(cursorSetUserPutOn);
				}
				return TRUE;
				case 0xE1:
				{

					/**
					 * cursorSetUserPutOff
					 */
					OP(cursorSetUserPutOff);
				}
				return TRUE;
				case 0xE2:
				{

					/**
					 * cursorSetUserPutSoftOn
					 */
					OP(cursorSetUserPutSoftOn);
				}
				return TRUE;
				case 0xE3:
				{

					/**
					 * cursorSetUserPutSoftOff
					 */
					OP(cursorSetUserPutSoftOff);
				}
				return TRUE;
				case 0xE4:
				{

					/**
					 * cursorSetImage
					 * @param word[stack, 0] objNum
					 * @param long[stack,-1] index
					 */
					int32 index = PULL_LONG();
					int16 objNum = PULL_WORD();
					OP(cursorSetImage, objNum, index);
				}
				return TRUE;
				case 0xE5:
				{

					/**
					 * cursorSetHotSpot
					 * @param long[stack, 0] x
					 * @param long[stack,-1] y
					 */
					int32 y = PULL_LONG();
					int32 x = PULL_LONG();
					OP(cursorSetHotSpot, x, y);
				}
				return TRUE;
				case 0xE6:
				{

					/**
					 * cursorSetTransparent
					 * @param long[stack, 0] isTransparent
					 */
					int32 isTransparent = PULL_LONG();
					OP(cursorSetTransparent, isTransparent);
				}
				return TRUE;
				case 0xE7:
				{

					/**
					 * cursorSetCharSet
					 * @param word[stack, 0] charsetNum
					 */
					int16 charsetNum = PULL_WORD();
					OP(cursorSetCharSet, charsetNum);
				}
				return TRUE;
				case 0xE8:
				{

					/**
					 * cursorSetCharSetColour
					 * @param args[stack, 0] args
					 */
					int* args = PULL_ARGS();
					OP(cursorSetCharSetColour, args);
				}
				return TRUE;
				case 0xE9:
				{

					/**
					 * cursorSetPos
					 * @param long[stack, 0] x
					 * @param long[stack,-1] y
					 */
					int32 y = PULL_LONG();
					int32 x = PULL_LONG();
					OP(cursorSetPos, x, y);
				}
				return TRUE;
			}
		}
		return FALSE;
		case 0x9D:
		{

			/**
			 * loadRoom
			 * @param byte[stack, 0] room
			 */
			byte room = PULL_BYTE();
			OP(loadRoom, room);
		}
		return TRUE;
		case 0x9E:
		{

			/**
			 * loadRoomWithEgo
			 * @param long[stack, 0] x
			 * @param long[stack,-1] y
			 */
			int32 y = PULL_LONG();
			int32 x = PULL_LONG();
			OP(loadRoomWithEgo, x, y);
		}
		return TRUE;
		case 0x9F:
		{

			/**
			 * walkActorToObj
			 * @param long[stack, 0] index
			 * @param long[stack,-1] obj
			 * @param long[stack,-2] dist
			 */
			int32 dist = PULL_LONG();
			int32 obj = PULL_LONG();
			int32 index = PULL_LONG();
			OP(walkActorToObj, index, obj, dist);
		}
		return TRUE;
		case 0xA0:
		{

			/**
			 * walkActorTo
			 * @param long[stack, 0] index
			 * @param long[stack,-1] x
			 * @param long[stack,-2] y
			 */
			int32 y = PULL_LONG();
			int32 x = PULL_LONG();
			int32 index = PULL_LONG();
			OP(walkActorTo, index, x, y);
		}
		return TRUE;
		case 0xA1:
		{

			/**
			 * putActorAtXY
			 * @param long[stack, 0] actorIndex
			 * @param long[stack,-1] x
			 * @param long[stack,-2] y
			 * @param long[stack,-3] room
			 */
			int32 room = PULL_LONG();
			int32 y = PULL_LONG();
			int32 x = PULL_LONG();
			int32 actorIndex = PULL_LONG();
			OP(putActorAtXY, actorIndex, x, y, room);
		}
		return TRUE;
		case 0xA2:
		{

			/**
			 * putActorAtObject
			 */
			OP(putActorAtObject);
		}
		return TRUE;
		case 0xA3:
		{

			/**
			 * faceActor
			 * @param long[stack, 0] index
			 * @param long[stack,-1] obj
			 */
			int32 obj = PULL_LONG();
			int32 index = PULL_LONG();
			OP(faceActor, index, obj);
		}
		return TRUE;
		case 0xA4:
		{

			/**
			 * animateActor
			 * @param long[stack, 0] index
			 * @param long[stack,-1] anim
			 */
			int32 anim = PULL_LONG();
			int32 index = PULL_LONG();
			OP(animateActor, index, anim);
		}
		return TRUE;
		case 0xA5:
		{

			/**
			 * doSentence8
			 * @param byte[stack, 0] verb
			 * @param word[stack,-1] objectA
			 * @param word[stack,-2] objectB
			 */
			int16 objectB = PULL_WORD();
			int16 objectA = PULL_WORD();
			byte verb = PULL_BYTE();
			OP(doSentence8, verb, objectA, objectB);
		}
		return TRUE;
		case 0xA6:
		{

			/**
			 * pickupObject
			 */
			OP(pickupObject);
		}
		return TRUE;
		case 0xA7:
		{

			/**
			 * setBoxFlags
			 * @param args[stack, 0] args
			 * @param long[stack,-1] value
			 */
			int32 value = PULL_LONG();
			int* args = PULL_ARGS();
			OP(setBoxFlags, args, value);
		}
		return TRUE;
		case 0xA8:
		{

			/**
			 * createBoxMatrix
			 */
			OP(createBoxMatrix);
		}
		return TRUE;
		case 0xA9:
		{

			/**
			 * wait
			 */
			OP(wait);
		}
		return TRUE;
		case 0xAA:
		{
			switch((op2 = READ_BYTE()))
			{
				case 0x3D:
				{

					/**
					 * loadCostume
					 * @param word[stack, 0] costumeNum
					 */
					int16 costumeNum = PULL_WORD();
					OP(loadCostume, costumeNum);
				}
				return TRUE;
				case 0x3E:
				{

					/**
					 * loadObject
					 * @param word[stack, 0] objectNum
					 */
					int16 objectNum = PULL_WORD();
					OP(loadObject, objectNum);
				}
				return TRUE;
				case 0x3F:
				{

					/**
					 * loadRoom
					 * @param word[stack, 0] roomNum
					 */
					int16 roomNum = PULL_WORD();
					OP(loadRoom, roomNum);
				}
				return TRUE;
				case 0x40:
				{

					/**
					 * loadScript
					 * @param word[stack, 0] scriptNum
					 */
					int16 scriptNum = PULL_WORD();
					OP(loadScript, scriptNum);
				}
				return TRUE;
				case 0x41:
				{

					/**
					 * loadSound
					 * @param word[stack, 0] soundNum
					 */
					int16 soundNum = PULL_WORD();
					OP(loadSound, soundNum);
				}
				return TRUE;
				case 0x42:
				{

					/**
					 * lockCostume
					 * @param word[stack, 0] costumeNum
					 */
					int16 costumeNum = PULL_WORD();
					OP(lockCostume, costumeNum);
				}
				return TRUE;
				case 0x43:
				{

					/**
					 * lockRoom
					 * @param word[stack, 0] roomNum
					 */
					int16 roomNum = PULL_WORD();
					OP(lockRoom, roomNum);
				}
				return TRUE;
				case 0x44:
				{

					/**
					 * lockScript
					 * @param word[stack, 0] scriptNum
					 */
					int16 scriptNum = PULL_WORD();
					OP(lockScript, scriptNum);
				}
				return TRUE;
				case 0x45:
				{

					/**
					 * lockSound
					 * @param word[stack, 0] soundNum
					 */
					int16 soundNum = PULL_WORD();
					OP(lockSound, soundNum);
				}
				return TRUE;
				case 0x46:
				{

					/**
					 * unlockCostume
					 * @param word[stack, 0] costumeNum
					 */
					int16 costumeNum = PULL_WORD();
					OP(unlockCostume, costumeNum);
				}
				return TRUE;
				case 0x47:
				{

					/**
					 * unlockRoom
					 * @param word[stack, 0] roomNum
					 */
					int16 roomNum = PULL_WORD();
					OP(unlockRoom, roomNum);
				}
				return TRUE;
				case 0x48:
				{

					/**
					 * unlockScript
					 * @param word[stack, 0] scriptNum
					 */
					int16 scriptNum = PULL_WORD();
					OP(unlockScript, scriptNum);
				}
				return TRUE;
				case 0x49:
				{

					/**
					 * unlockSound
					 * @param word[stack, 0] soundNum
					 */
					int16 soundNum = PULL_WORD();
					OP(unlockSound, soundNum);
				}
				return TRUE;
				case 0x4A:
				{

					/**
					 * deleteCostume
					 * @param word[stack, 0] costumeNum
					 */
					int16 costumeNum = PULL_WORD();
					OP(deleteCostume, costumeNum);
				}
				return TRUE;
				case 0x4B:
				{

					/**
					 * deleteRoom
					 * @param word[stack, 0] roomNum
					 */
					int16 roomNum = PULL_WORD();
					OP(deleteRoom, roomNum);
				}
				return TRUE;
				case 0x4C:
				{

					/**
					 * deleteScript
					 * @param word[stack, 0] scriptNum
					 */
					int16 scriptNum = PULL_WORD();
					OP(deleteScript, scriptNum);
				}
				return TRUE;
				case 0x4D:
				{

					/**
					 * deleteSound
					 * @param word[stack, 0] soundNum
					 */
					int16 soundNum = PULL_WORD();
					OP(deleteSound, soundNum);
				}
				return TRUE;
			}
		}
		return FALSE;
		case 0xAB:
		{
			switch((op2 = READ_BYTE()))
			{
				case 0x52:
				{

					/**
					 * setRoomPalette
					 * @param byte[stack, 0] idx
					 * @param byte[stack,-1] r
					 * @param byte[stack,-2] g
					 * @param byte[stack,-3] b
					 */
					byte b = PULL_BYTE();
					byte g = PULL_BYTE();
					byte r = PULL_BYTE();
					byte idx = PULL_BYTE();
					OP(setRoomPalette, idx, r, g, b);
				}
				return TRUE;
				case 0x57:
				{

					/**
					 * fadeRoom
					 * @param word[stack, 0] effect
					 */
					int16 effect = PULL_WORD();
					OP(fadeRoom, effect);
				}
				return TRUE;
				case 0x58:
				{

					/**
					 * darkenPalette
					 * @param long[stack, 0] redScale
					 * @param long[stack,-1] greenScale
					 * @param long[stack,-2] blueScale
					 * @param word[stack,-3] startColor
					 * @param word[stack,-4] endColor
					 */
					int16 endColor = PULL_WORD();
					int16 startColor = PULL_WORD();
					int32 blueScale = PULL_LONG();
					int32 greenScale = PULL_LONG();
					int32 redScale = PULL_LONG();
					OP(darkenPalette, redScale, greenScale, blueScale, startColor, endColor);
				}
				return TRUE;
				case 0x59:
				{

					/**
					 * manipulatePalette
					 * @param word[stack, 0] resourceNum
					 * @param long[stack,-1] start
					 * @param long[stack,-2] end
					 * @param long[stack,-3] time
					 */
					int32 time = PULL_LONG();
					int32 end = PULL_LONG();
					int32 start = PULL_LONG();
					int16 resourceNum = PULL_WORD();
					OP(manipulatePalette, resourceNum, start, end, time);
				}
				return TRUE;
				case 0x5C:
				{

					/**
					 * setPalette
					 * @param word[stack, 0] palNum
					 */
					int16 palNum = PULL_WORD();
					OP(setPalette, palNum);
				}
				return TRUE;
				case 0x5D:
				{

					/**
					 * roomSaveGame
					 */
					OP(roomSaveGame);
				}
				return TRUE;
				case 0x5E:
				{

					/**
					 * roomLoadGame
					 */
					OP(roomLoadGame);
				}
				return TRUE;
				case 0x5F:
				{

					/**
					 * desaturatePalette
					 * @param long[stack, 0] hueScale
					 * @param long[stack,-1] satScale
					 * @param long[stack,-2] lightScale
					 * @param word[stack,-3] startColor
					 * @param word[stack,-4] endColor
					 */
					int16 endColor = PULL_WORD();
					int16 startColor = PULL_WORD();
					int32 lightScale = PULL_LONG();
					int32 satScale = PULL_LONG();
					int32 hueScale = PULL_LONG();
					OP(desaturatePalette, hueScale, satScale, lightScale, startColor, endColor);
				}
				return TRUE;
			}
		}
		return FALSE;
		case 0xAC:
		{
			switch((op2 = READ_BYTE()))
			{
				case 0x64:
				{

					/**
					 * setActorCostume
					 * @param word[stack, 0] costumeNum
					 */
					int16 costumeNum = PULL_WORD();
					OP(setActorCostume, costumeNum);
				}
				return TRUE;
				case 0x65:
				{

					/**
					 * setActorStepDistance
					 * @param word[stack, 0] x
					 * @param word[stack,-1] y
					 */
					int16 y = PULL_WORD();
					int16 x = PULL_WORD();
					OP(setActorStepDistance, x, y);
				}
				return TRUE;
				case 0x67:
				{

					/**
					 * setActorAnimationToDefault
					 */
					OP(setActorAnimationToDefault);
				}
				return TRUE;
				case 0x68:
				{

					/**
					 * setActorAnimationInitFrame
					 * @param word[stack, 0] initFrame
					 */
					int16 initFrame = PULL_WORD();
					OP(setActorAnimationInitFrame, initFrame);
				}
				return TRUE;
				case 0x69:
				{

					/**
					 * setActorAnimationTalkFrame
					 * @param word[stack, 0] startFrame
					 * @param word[stack,-1] endFrame
					 */
					int16 endFrame = PULL_WORD();
					int16 startFrame = PULL_WORD();
					OP(setActorAnimationTalkFrame, startFrame, endFrame);
				}
				return TRUE;
				case 0x6A:
				{

					/**
					 * setActorAnimationWalkFrame
					 * @param word[stack, 0] walkFrame
					 */
					int16 walkFrame = PULL_WORD();
					OP(setActorAnimationWalkFrame, walkFrame);
				}
				return TRUE;
				case 0x6B:
				{

					/**
					 * setActorAnimationStandFrame
					 * @param word[stack, 0] standFrame
					 */
					int16 standFrame = PULL_WORD();
					OP(setActorAnimationStandFrame, standFrame);
				}
				return TRUE;
				case 0x6C:
				{

					/**
					 * setActorAnimationSpeed
					 * @param word[stack, 0] speed
					 */
					int16 speed = PULL_WORD();
					OP(setActorAnimationSpeed, speed);
				}
				return TRUE;
				case 0x6D:
				{

					/**
					 * newActor
					 * @const mode = 0
					 */
					OP(newActor, 0);
				}
				return TRUE;
				case 0x6E:
				{

					/**
					 * setActorElevation
					 * @param word[stack, 0] elevation
					 */
					int16 elevation = PULL_WORD();
					OP(setActorElevation, elevation);
				}
				return TRUE;
				case 0x6F:
				{

					/**
					 * setActorPalette
					 * @param word[stack, 0] idx
					 * @param long[stack,-1] val
					 */
					int32 val = PULL_LONG();
					int16 idx = PULL_WORD();
					OP(setActorPalette, idx, val);
				}
				return TRUE;
				case 0x70:
				{

					/**
					 * setActorTalkColor
					 * @param word[stack, 0] idx
					 */
					int16 idx = PULL_WORD();
					OP(setActorTalkColor, idx);
				}
				return TRUE;
				case 0x71:
				{

					/**
					 * setActorName
					 */
					OP(setActorName);
				}
				return TRUE;
				case 0x72:
				{

					/**
					 * setActorWidth
					 * @param word[stack, 0] width
					 */
					int16 width = PULL_WORD();
					OP(setActorWidth, width);
				}
				return TRUE;
				case 0x73:
				{

					/**
					 * setActorScale
					 * @param word[stack, 0] scale
					 */
					int16 scale = PULL_WORD();
					OP(setActorScale, scale);
				}
				return TRUE;
				case 0x74:
				{

					/**
					 * setActorNeverZClip
					 */
					OP(setActorNeverZClip);
				}
				return TRUE;
				case 0x75:
				{

					/**
					 * setActorAlwaysZClip
					 * @param word[stack, 0] forceClip
					 */
					int16 forceClip = PULL_WORD();
					OP(setActorAlwaysZClip, forceClip);
				}
				return TRUE;
				case 0x76:
				{

					/**
					 * setActorFollowBoxes
					 * @const follow = 0
					 */
					OP(setActorFollowBoxes, 0);
				}
				return TRUE;
				case 0x77:
				{

					/**
					 * setActorFollowBoxes
					 * @const follow = 1
					 */
					OP(setActorFollowBoxes, 1);
				}
				return TRUE;
				case 0x78:
				{

					/**
					 * setActorShadowDraw
					 * @param byte[stack, 0] enabled
					 */
					byte enabled = PULL_BYTE();
					OP(setActorShadowDraw, enabled);
				}
				return TRUE;
				case 0x79:
				{

					/**
					 * setActorTextOffset
					 * @param long[stack, 0] x
					 * @param long[stack,-1] y
					 */
					int32 y = PULL_LONG();
					int32 x = PULL_LONG();
					OP(setActorTextOffset, x, y);
				}
				return TRUE;
				case 0x7A:
				{

					/**
					 * initActor
					 * @param word[stack, 0] actorNum
					 */
					int16 actorNum = PULL_WORD();
					OP(initActor, actorNum);
				}
				return TRUE;
				case 0x7B:
				{

					/**
					 * setActorVar
					 * @param long[stack, 0] varNum
					 * @param long[stack,-1] value
					 */
					int32 value = PULL_LONG();
					int32 varNum = PULL_LONG();
					OP(setActorVar, varNum, value);
				}
				return TRUE;
				case 0x7C:
				{

					/**
					 * setActorFollowTurns
					 * @const follow = 0
					 */
					OP(setActorFollowTurns, 0);
				}
				return TRUE;
				case 0x7D:
				{

					/**
					 * setActorFollowTurns
					 * @const follow = 1
					 */
					OP(setActorFollowTurns, 1);
				}
				return TRUE;
				case 0x7E:
				{

					/**
					 * newActor
					 * @const mode = 2
					 */
					OP(newActor, 2);
				}
				return TRUE;
				case 0x7F:
				{

					/**
					 * setActorZ
					 * @param word[stack, 0] z
					 */
					int16 z = PULL_WORD();
					OP(setActorZ, z);
				}
				return TRUE;
				case 0x80:
				{

					/**
					 * stopActorMoving
					 */
					OP(stopActorMoving);
				}
				return TRUE;
				case 0x81:
				{

					/**
					 * 
					 * @const force = 1
					 */
					OP(, 1);
				}
				return TRUE;
				case 0x82:
				{

					/**
					 * turnActor
					 * @param word[stack, 0] direction
					 * @const force = 0
					 */
					int16 direction = PULL_WORD();
					OP(turnActor, direction, 0);
				}
				return TRUE;
				case 0x83:
				{

					/**
					 * setWalkScript
					 * @param word[stack, 0] scriptNum
					 */
					int16 scriptNum = PULL_WORD();
					OP(setWalkScript, scriptNum);
				}
				return TRUE;
				case 0x84:
				{

					/**
					 * setTalkScript
					 * @param word[stack, 0] scriptNum
					 */
					int16 scriptNum = PULL_WORD();
					OP(setTalkScript, scriptNum);
				}
				return TRUE;
				case 0x85:
				{

					/**
					 * setWalkPaused
					 * @const paused = 1
					 */
					OP(setWalkPaused, 1);
				}
				return TRUE;
				case 0x86:
				{

					/**
					 * setWalkPaused
					 * @const paused = 0
					 */
					OP(setWalkPaused, 0);
				}
				return TRUE;
				case 0x87:
				{

					/**
					 * setActorVolume
					 * @param word[stack, 0] volume
					 */
					int16 volume = PULL_WORD();
					OP(setActorVolume, volume);
				}
				return TRUE;
				case 0x88:
				{

					/**
					 * setActorFrequency
					 * @param word[stack, 0] frequency
					 */
					int16 frequency = PULL_WORD();
					OP(setActorFrequency, frequency);
				}
				return TRUE;
				case 0x89:
				{

					/**
					 * setActorPan
					 * @param word[stack, 0] pan
					 */
					int16 pan = PULL_WORD();
					OP(setActorPan, pan);
				}
				return TRUE;
			}
		}
		return FALSE;
		case 0xAD:
		{
			switch((op2 = READ_BYTE()))
			{
				case 0x32:
				{

					/**
					 * setCameraFrozen
					 * @const frozen = 1
					 */
					OP(setCameraFrozen, 1);
				}
				return TRUE;
				case 0x33:
				{

					/**
					 * setCameraFrozen
					 * @const frozen = 0
					 */
					OP(setCameraFrozen, 0);
				}
				return TRUE;
			}
		}
		return FALSE;
		case 0xAE:
		{
			switch((op2 = READ_BYTE()))
			{
				case 0x96:
				{

					/**
					 * initVerb
					 * @param word[stack, 0] verbNum
					 */
					int16 verbNum = PULL_WORD();
					OP(initVerb, verbNum);
				}
				return TRUE;
				case 0x97:
				{

					/**
					 * newVerb
					 */
					OP(newVerb);
				}
				return TRUE;
				case 0x98:
				{

					/**
					 * deleteVerb
					 */
					OP(deleteVerb);
				}
				return TRUE;
				case 0x99:
				{

					/**
					 * setVerbName
					 * @param string[2...] name
					 * @param byte[stack, 0] showName
					 */
					byte* name = READ_STRING();
					byte showName = PULL_BYTE();
					OP(setVerbName, showName, name);
				}
				return TRUE;
				case 0x9A:
				{

					/**
					 * setVerbAt
					 * @param word[stack, 0] x
					 * @param word[stack,-1] y
					 */
					int16 y = PULL_WORD();
					int16 x = PULL_WORD();
					OP(setVerbAt, x, y);
				}
				return TRUE;
				case 0x9B:
				{

					/**
					 * setVerbEnabled
					 * @const enabled = 1
					 */
					OP(setVerbEnabled, 1);
				}
				return TRUE;
				case 0x9C:
				{

					/**
					 * setVerbEnabled
					 * @const enabled = 0
					 */
					OP(setVerbEnabled, 0);
				}
				return TRUE;
				case 0x9D:
				{

					/**
					 * setVerbColor
					 * @param byte[stack, 0] idx
					 */
					byte idx = PULL_BYTE();
					OP(setVerbColor, idx);
				}
				return TRUE;
				case 0x9E:
				{

					/**
					 * setVerbHiColor
					 * @param byte[stack, 0] idx
					 */
					byte idx = PULL_BYTE();
					OP(setVerbHiColor, idx);
				}
				return TRUE;
				case 0xA0:
				{

					/**
					 * setVerbDimColor
					 * @param byte[stack, 0] idx
					 */
					byte idx = PULL_BYTE();
					OP(setVerbDimColor, idx);
				}
				return TRUE;
				case 0xA1:
				{

					/**
					 * dimVerb
					 */
					OP(dimVerb);
				}
				return TRUE;
				case 0xA2:
				{

					/**
					 * setVerbKey
					 * @param word[stack, 0] keyNum
					 */
					int16 keyNum = PULL_WORD();
					OP(setVerbKey, keyNum);
				}
				return TRUE;
				case 0xA3:
				{

					/**
					 * setVerbImage
					 * @param word[stack, 0] roomNum
					 * @param word[stack,-1] objectNum
					 */
					int16 objectNum = PULL_WORD();
					int16 roomNum = PULL_WORD();
					OP(setVerbImage, roomNum, objectNum);
				}
				return TRUE;
				case 0xA4:
				{

					/**
					 * setVerbText
					 * @param long[stack, 0] textAddress
					 */
					int32 textAddress = PULL_LONG();
					OP(setVerbText, textAddress);
				}
				return TRUE;
				case 0xA5:
				{

					/**
					 * centerVerb
					 */
					OP(centerVerb);
				}
				return TRUE;
				case 0xA6:
				{

					/**
					 * setVerbCharSet
					 * @param word[stack, 0] charsetNum
					 */
					int16 charsetNum = PULL_WORD();
					OP(setVerbCharSet, charsetNum);
				}
				return TRUE;
				case 0xA7:
				{

					/**
					 * setVerbLineSpacing
					 * @param long[stack, 0] lineSpacing
					 */
					int32 lineSpacing = PULL_LONG();
					OP(setVerbLineSpacing, lineSpacing);
				}
				return TRUE;
			}
		}
		return FALSE;
		case 0xAF:
		{

			/**
			 * startSound
			 * @param long[stack, 0] sound
			 */
			int32 sound = PULL_LONG();
			OP(startSound, sound);
		}
		return TRUE;
		case 0xB0:
		{

			/**
			 * startMusic
			 * @param long[stack, 0] sound
			 */
			int32 sound = PULL_LONG();
			OP(startMusic, sound);
		}
		return TRUE;
		case 0xB1:
		{

			/**
			 * stopSound
			 * @param long[stack, 0] sound
			 */
			int32 sound = PULL_LONG();
			OP(stopSound, sound);
		}
		return TRUE;
		case 0xB2:
		{

			/**
			 * soundKludge
			 * @param args[stack, 0] args
			 */
			int* args = PULL_ARGS();
			OP(soundKludge, args);
		}
		return TRUE;
		case 0xB3:
		{
			switch((op2 = READ_BYTE()))
			{
				case 0x28:
				{

					/**
					 * restartGame
					 */
					OP(restartGame);
				}
				return TRUE;
				case 0x29:
				{

					/**
					 * quitGame
					 */
					OP(quitGame);
				}
				return TRUE;
			}
		}
		return FALSE;
		case 0xB4:
		{

			/**
			 * saveRestoreVerbs
			 * @param long[stack, 0] a
			 * @param long[stack,-1] b
			 * @param long[stack,-2] c
			 */
			int32 c = PULL_LONG();
			int32 b = PULL_LONG();
			int32 a = PULL_LONG();
			OP(saveRestoreVerbs, a, b, c);
		}
		return TRUE;
		case 0xB5:
		{

			/**
			 * setObjectName
			 * @param string[1...] text
			 * @param word[stack, 0] objectNum
			 */
			byte* text = READ_STRING();
			int16 objectNum = PULL_WORD();
			OP(setObjectName, objectNum, text);
		}
		return TRUE;
		case 0xB6:
		{

			/**
			 * getDateTime
			 */
			OP(getDateTime);
		}
		return TRUE;
		case 0xB7:
		{

			/**
			 * drawBox
			 * @param long[stack, 0] x
			 * @param long[stack,-1] y
			 * @param long[stack,-2] x2
			 * @param long[stack,-3] y2
			 * @param long[stack,-4] color
			 */
			int32 color = PULL_LONG();
			int32 y2 = PULL_LONG();
			int32 x2 = PULL_LONG();
			int32 y = PULL_LONG();
			int32 x = PULL_LONG();
			OP(drawBox, x, y, x2, y2, color);
		}
		return TRUE;
		case 0xB9:
		{

			/**
			 * startVideo
			 * @param string[1...] path
			 */
			byte* path = READ_STRING();
			OP(startVideo, path);
		}
		return TRUE;
		case 0xBA:
		{

			/**
			 * kernelSetFunctions
			 * @param args[stack, 0] args
			 */
			int* args = PULL_ARGS();
			OP(kernelSetFunctions, args);
		}
		return TRUE;
		case 0xC0:
		{

			/**
			 * dim2DimArray
			 * @param long[stack, 0] dim2
			 * @param long[stack,-1] dim1
			 */
			int32 dim1 = PULL_LONG();
			int32 dim2 = PULL_LONG();
			OP(dim2DimArray, dim2, dim1);
		}
		return TRUE;
		case 0xC6:
		{

			/**
			 * distObjectPt
			 * @param long[stack, 0] a
			 * @param long[stack,-1] b
			 * @param long[stack,-2] c
			 */
			int32 c = PULL_LONG();
			int32 b = PULL_LONG();
			int32 a = PULL_LONG();
			OP(distObjectPt, a, b, c);
		}
		return TRUE;
		case 0xC8:
		{

			/**
			 * startScriptQuick2
			 * @param long[stack, 0] script
			 * @param args[stack,-1] args
			 */
			int* args = PULL_ARGS();
			int32 script = PULL_LONG();
			OP(startScriptQuick2, script, args);
		}
		return TRUE;
		case 0xC9:
		{

			/**
			 * startObjectQuick
			 * @param long[stack, 0] script
			 * @param byte[stack,-1] entryp
			 * @param args[stack,-2] args
			 */
			int* args = PULL_ARGS();
			byte entryp = PULL_BYTE();
			int32 script = PULL_LONG();
			OP(startObjectQuick, script, entryp, args);
		}
		return TRUE;
		case 0xCA:
		{

			/**
			 * pickOneOf
			 * @param long[stack, 0] i
			 * @param args[stack,-1] args
			 */
			int* args = PULL_ARGS();
			int32 i = PULL_LONG();
			OP(pickOneOf, i, args);
		}
		return TRUE;
		case 0xCB:
		{

			/**
			 * pickOneOfDefault
			 * @param long[stack, 0] i
			 * @param args[stack,-1] args
			 * @param long[stack,-2] def
			 */
			int32 def = PULL_LONG();
			int* args = PULL_ARGS();
			int32 i = PULL_LONG();
			OP(pickOneOfDefault, i, args, def);
		}
		return TRUE;
		case 0xCD:
		{

			/**
			 * isAnyOf
			 * @param long[stack, 0] value
			 * @param args[stack,-1] args
			 */
			int* args = PULL_ARGS();
			int32 value = PULL_LONG();
			OP(isAnyOf, value, args);
		}
		return TRUE;
		case 0xCE:
		{

			/**
			 * getRandomNumber
			 * @param long[stack, 0] max
			 */
			int32 max = PULL_LONG();
			OP(getRandomNumber, max);
		}
		return TRUE;
		case 0xCF:
		{

			/**
			 * getRandomNumberRange
			 * @param long[stack, 0] min
			 * @param long[stack,-1] max
			 */
			int32 max = PULL_LONG();
			int32 min = PULL_LONG();
			OP(getRandomNumberRange, min, max);
		}
		return TRUE;
		case 0xD0:
		{

			/**
			 * ifClassOfIs
			 * @param long[stack, 0] obj
			 * @param args[stack,-1] args
			 */
			int* args = PULL_ARGS();
			int32 obj = PULL_LONG();
			OP(ifClassOfIs, obj, args);
		}
		return TRUE;
		case 0xD1:
		{

			/**
			 * getState
			 * @param long[stack, 0] obj
			 */
			int32 obj = PULL_LONG();
			OP(getState, obj);
		}
		return TRUE;
		case 0xD2:
		{

			/**
			 * getOwner
			 * @param long[stack, 0] obj
			 */
			int32 obj = PULL_LONG();
			OP(getOwner, obj);
		}
		return TRUE;
		case 0xD3:
		{

			/**
			 * isScriptRunning
			 * @param long[stack, 0] script
			 */
			int32 script = PULL_LONG();
			OP(isScriptRunning, script);
		}
		return TRUE;
		case 0xD4:
		{

			/**
			 * shuffle
			 * @param long[stack, 0] a
			 * @param long[stack,-1] b
			 */
			int32 b = PULL_LONG();
			int32 a = PULL_LONG();
			OP(shuffle, a, b);
		}
		return TRUE;
		case 0xD5:
		{

			/**
			 * isSoundRunning
			 * @param long[stack, 0] sound
			 */
			int32 sound = PULL_LONG();
			OP(isSoundRunning, sound);
		}
		return TRUE;
		case 0xD6:
		{

			/**
			 * abs
			 * @param long[stack, 0] value
			 */
			int32 value = PULL_LONG();
			OP(abs, value);
		}
		return TRUE;
		case 0xD8:
		{

			/**
			 * kernelGetFunctions
			 */
			OP(kernelGetFunctions);
		}
		return TRUE;
		case 0xD9:
		{

			/**
			 * isActorInBox
			 * @param long[stack, 0] index
			 * @param long[stack,-1] box
			 */
			int32 box = PULL_LONG();
			int32 index = PULL_LONG();
			OP(isActorInBox, index, box);
		}
		return TRUE;
		case 0xDA:
		{

			/**
			 * getVerbEntrypoint
			 * @param long[stack, 0] verb
			 * @param long[stack,-1] entryp
			 */
			int32 entryp = PULL_LONG();
			int32 verb = PULL_LONG();
			OP(getVerbEntrypoint, verb, entryp);
		}
		return TRUE;
		case 0xDB:
		{

			/**
			 * getActorFromXY
			 * @param long[stack, 0] x
			 * @param long[stack,-1] y
			 */
			int32 y = PULL_LONG();
			int32 x = PULL_LONG();
			OP(getActorFromXY, x, y);
		}
		return TRUE;
		case 0xDC:
		{

			/**
			 * findObject
			 * @param long[stack, 0] x
			 * @param long[stack,-1] y
			 */
			int32 y = PULL_LONG();
			int32 x = PULL_LONG();
			OP(findObject, x, y);
		}
		return TRUE;
		case 0xDD:
		{

			/**
			 * getVerbFromXY
			 * @param long[stack, 0] x
			 * @param long[stack,-1] y
			 */
			int32 y = PULL_LONG();
			int32 x = PULL_LONG();
			OP(getVerbFromXY, x, y);
		}
		return TRUE;
		case 0xDF:
		{

			/**
			 * findInventory
			 * @param long[stack, 0] owner
			 * @param long[stack,-1] index
			 */
			int32 index = PULL_LONG();
			int32 owner = PULL_LONG();
			OP(findInventory, owner, index);
		}
		return TRUE;
		case 0xE0:
		{

			/**
			 * getInventoryCount
			 * @param long[stack, 0] owner
			 */
			int32 owner = PULL_LONG();
			OP(getInventoryCount, owner);
		}
		return TRUE;
		case 0xE1:
		{

			/**
			 * getAnimateVariable
			 * @param long[stack, 0] index
			 * @param long[stack,-1] variable
			 */
			int32 variable = PULL_LONG();
			int32 index = PULL_LONG();
			OP(getAnimateVariable, index, variable);
		}
		return TRUE;
		case 0xE2:
		{

			/**
			 * getActorRoom
			 * @param long[stack, 0] index
			 */
			int32 index = PULL_LONG();
			OP(getActorRoom, index);
		}
		return TRUE;
		case 0xE3:
		{

			/**
			 * getActorWalkBox
			 * @param long[stack, 0] index
			 */
			int32 index = PULL_LONG();
			OP(getActorWalkBox, index);
		}
		return TRUE;
		case 0xE4:
		{

			/**
			 * getActorMoving
			 * @param long[stack, 0] index
			 */
			int32 index = PULL_LONG();
			OP(getActorMoving, index);
		}
		return TRUE;
		case 0xE5:
		{

			/**
			 * getActorCostume
			 * @param long[stack, 0] index
			 */
			int32 index = PULL_LONG();
			OP(getActorCostume, index);
		}
		return TRUE;
		case 0xE6:
		{

			/**
			 * getActorScaleX
			 * @param long[stack, 0] index
			 */
			int32 index = PULL_LONG();
			OP(getActorScaleX, index);
		}
		return TRUE;
		case 0xE7:
		{

			/**
			 * getActorLayer
			 * @param long[stack, 0] index
			 */
			int32 index = PULL_LONG();
			OP(getActorLayer, index);
		}
		return TRUE;
		case 0xE8:
		{

			/**
			 * getActorElevation
			 * @param long[stack, 0] index
			 */
			int32 index = PULL_LONG();
			OP(getActorElevation, index);
		}
		return TRUE;
		case 0xE9:
		{

			/**
			 * getActorWidth
			 * @param long[stack, 0] index
			 */
			int32 index = PULL_LONG();
			OP(getActorWidth, index);
		}
		return TRUE;
		case 0xEA:
		{

			/**
			 * getObjectNewDir
			 * @param long[stack, 0] index
			 */
			int32 index = PULL_LONG();
			OP(getObjectNewDir, index);
		}
		return TRUE;
		case 0xEB:
		{

			/**
			 * getObjectX
			 * @param long[stack, 0] index
			 */
			int32 index = PULL_LONG();
			OP(getObjectX, index);
		}
		return TRUE;
		case 0xEC:
		{

			/**
			 * getObjectY
			 * @param long[stack, 0] index
			 */
			int32 index = PULL_LONG();
			OP(getObjectY, index);
		}
		return TRUE;
		case 0xED:
		{

			/**
			 * getActorChore
			 */
			OP(getActorChore);
		}
		return TRUE;
		case 0xEE:
		{

			/**
			 * distObjectObject
			 * @param long[stack, 0] a
			 * @param long[stack,-1] b
			 */
			int32 b = PULL_LONG();
			int32 a = PULL_LONG();
			OP(distObjectObject, a, b);
		}
		return TRUE;
		case 0xEF:
		{

			/**
			 * distObjectPtPt
			 * @param long[stack, 0] a
			 * @param long[stack,-1] b
			 * @param long[stack,-2] c
			 * @param long[stack,-3] d
			 */
			int32 d = PULL_LONG();
			int32 c = PULL_LONG();
			int32 b = PULL_LONG();
			int32 a = PULL_LONG();
			OP(distObjectPtPt, a, b, c, d);
		}
		return TRUE;
		case 0xF0:
		{

			/**
			 * getObjectImageX
			 */
			OP(getObjectImageX);
		}
		return TRUE;
		case 0xF1:
		{

			/**
			 * getObjectImageY
			 */
			OP(getObjectImageY);
		}
		return TRUE;
		case 0xF2:
		{

			/**
			 * getObjectImageWidth
			 */
			OP(getObjectImageWidth);
		}
		return TRUE;
		case 0xF3:
		{

			/**
			 * getObjectImageHeight
			 */
			OP(getObjectImageHeight);
		}
		return TRUE;
		case 0xF6:
		{

			/**
			 * getStringWidth
			 * @param string[1...] text
			 * @param word[stack, 0] charsetNum
			 */
			byte* text = READ_STRING();
			int16 charsetNum = PULL_WORD();
			OP(getStringWidth, charsetNum, text);
		}
		return TRUE;
		case 0xF7:
		{

			/**
			 * getActorZPlane
			 */
			OP(getActorZPlane);
		}
		return TRUE;
	}
	return FALSE;
}
