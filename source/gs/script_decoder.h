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
			 * - ImmByte value
			 */
			byte value = READ_BYTE();
			OP(pushByte, value);
		}
		return TRUE;
		case 0x01:
		{

			/**
			 * pushWord
			 * - ImmWord value
			 */
			int32 value = READ_LONG();
			OP(pushWord, value);
		}
		return TRUE;
		case 0x02:
		{

			/**
			 * pushWordVar
			 * - ImmWord index
			 */
			int32 index = READ_LONG();
			OP(pushWordVar, index);
		}
		return TRUE;
		case 0x03:
		{

			/**
			 * wordArrayRead
			 * - Long base
			 */
			int32 base = PULL_LONG();
			OP(wordArrayRead, base);
		}
		return TRUE;
		case 0x04:
		{

			/**
			 * wordArrayIndexedRead
			 * - Long index
			 * - Long base
			 */
			int32 base = PULL_LONG();
			int32 index = PULL_LONG();
			OP(wordArrayIndexedRead, index, base);
		}
		return TRUE;
		case 0x05:
		{

			/**
			 * dup
			 * - Long value
			 */
			int32 value = PULL_LONG();
			OP(dup, value);
		}
		return TRUE;
		case 0x06:
		{

			/**
			 * pop
			 * - Long discard
			 */
			int32 discard = PULL_LONG();
			OP(pop, discard);
		}
		return TRUE;
		case 0x07:
		{

			/**
			 * not
			 * - Long value
			 */
			int32 value = PULL_LONG();
			OP(not, value);
		}
		return TRUE;
		case 0x08:
		{

			/**
			 * eq
			 * - Long a
			 * - Long b
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
			 * - Long a
			 * - Long b
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
			 * - Long a
			 * - Long b
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
			 * - Long a
			 * - Long b
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
			 * - Long a
			 * - Long b
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
			 * - Long a
			 * - Long b
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
			 * - Long a
			 * - Long b
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
			 * - Long a
			 * - Long b
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
			 * - Long a
			 * - Long b
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
			 * - Long a
			 * - Long b
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
			 * - Long a
			 * - Long b
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
			 * - Long a
			 * - Long b
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
			 * - Long a
			 * - Long b
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
			 * - Long a
			 * - Long b
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
			 * - Long value
			 */
			int32 value = PULL_LONG();
			OP(writeByteVar, value);
		}
		return TRUE;
		case 0x46:
		{

			/**
			 * byteArrayWrite
			 * - Long base
			 * - Long value
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
			 * - Long index
			 * - Long base
			 * - Long value
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
			 * - Long base
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
			 * - Long base
			 */
			int32 base = PULL_LONG();
			OP(byteArrayDec, base);
		}
		return TRUE;
		case 0x61:
		{

			/**
			 * drawObject
			 * - Long obj
			 * - Long state
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
			 * - Long obj
			 * - Long x
			 * - Long y
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
			 * - Long a
			 * - Long b
			 * - Long c
			 * - Long d
			 * - Long e
			 * - Args args
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
			 * - Long condition
			 * - ImmWord relOffset
			 */
			int32 relOffset = READ_LONG();
			int32 condition = PULL_LONG();
			OP(if, condition, relOffset);
		}
		return TRUE;
		case 0x65:
		{

			/**
			 * ifNot
			 * - Long condition
			 * - ImmWord relOffset
			 */
			int32 relOffset = READ_LONG();
			int32 condition = PULL_LONG();
			OP(ifNot, condition, relOffset);
		}
		return TRUE;
		case 0x66:
		{

			/**
			 * jump
			 * - ImmWord absOffset
			 */
			int32 absOffset = READ_LONG();
			OP(jump, absOffset);
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

			/**
			 * wait
			 */
			OP(wait);
		}
		return TRUE;
		case 0x6A:
		{

			/**
			 * delay
			 * - Long delay
			 */
			int32 delay = PULL_LONG();
			OP(delay, delay);
		}
		return TRUE;
		case 0x6B:
		{

			/**
			 * delaySeconds
			 * - Long seconds
			 */
			int32 seconds = PULL_LONG();
			OP(delaySeconds, seconds);
		}
		return TRUE;
		case 0x6C:
		{

			/**
			 * delayMinutes
			 * - Long minutes
			 */
			int32 minutes = PULL_LONG();
			OP(delayMinutes, minutes);
		}
		return TRUE;
		case 0x6D:
		{

			/**
			 * writeWordVar
			 * - ImmLong varIndex
			 * - Long value
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
			 * - ImmLong varIndex
			 */
			int32 varIndex = READ_LONG();
			OP(wordVarInc, varIndex);
		}
		return TRUE;
		case 0x6F:
		{

			/**
			 * wordVarDec
			 * - ImmLong varIndex
			 */
			int32 varIndex = READ_LONG();
			OP(wordVarDec, varIndex);
		}
		return TRUE;
		case 0x70:
		{

			/**
			 * dimArray
			 */
			OP(dimArray);
		}
		return TRUE;
		case 0x71:
		{

			/**
			 * wordArrayWrite
			 * - Long base
			 * - Long value
			 */
			int32 value = PULL_LONG();
			int32 base = PULL_LONG();
			OP(wordArrayWrite, base, value);
		}
		return TRUE;
		case 0x72:
		{

			/**
			 * wordArrayInc
			 * - Long base
			 */
			int32 base = PULL_LONG();
			OP(wordArrayInc, base);
		}
		return TRUE;
		case 0x73:
		{

			/**
			 * wordArrayDec
			 * - Long base
			 */
			int32 base = PULL_LONG();
			OP(wordArrayDec, base);
		}
		return TRUE;
		case 0x74:
		{

			/**
			 * dim2DimArray
			 */
			OP(dim2DimArray);
		}
		return TRUE;
		case 0x75:
		{

			/**
			 * wordArrayIndexedWrite
			 * - Long index
			 * - Long base
			 * - Long value
			 */
			int32 value = PULL_LONG();
			int32 base = PULL_LONG();
			int32 index = PULL_LONG();
			OP(wordArrayIndexedWrite, index, base, value);
		}
		return TRUE;
		case 0x76:
		{

			/**
			 * arrayOps
			 */
			OP(arrayOps);
		}
		return TRUE;
		case 0x79:
		{

			/**
			 * startScript
			 * - Long flags
			 * - Long script
			 * - Args args
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
			 * - Long script
			 * - Args args
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
			 * - Long script
			 */
			int32 script = PULL_LONG();
			OP(stopScript6, script);
		}
		return TRUE;
		case 0x7D:
		{

			/**
			 * jumpToScript
			 * - Long flags
			 * - Long script
			 * - Args args
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
			 * - Long flags
			 * - Long script
			 * - Byte entryp
			 * - Args args
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
			 * - Word script
			 */
			int16 script = PULL_WORD();
			OP(stopObjectScript, script);
		}
		return TRUE;
		case 0x81:
		{

			/**
			 * cutscene
			 * - Args args
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
			 * - Long script
			 */
			int32 script = PULL_LONG();
			OP(freezeUnfreeze, script);
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
		case 0x89:
		{

			/**
			 * setClass
			 * - Long obj
			 * - Args args
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
			 * - Long obj
			 * - Long state
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
			 * - Long obj
			 * - Long owner
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
			 * - Long index
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
					 */
					OP(printActor_ResetState, 0, 1);
				}
				return TRUE;
				case 0xC9:
				{

					/**
					 * printActor_SaveState
					 */
					OP(printActor_SaveState, 0, 1);
				}
				return TRUE;
				case 0xCA:
				{

					/**
					 * printActor_SetPos
					 * - Word x
					 * - Word y
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
					 * - Byte index
					 */
					byte index = PULL_BYTE();
					OP(printActor_SetColor, index, 0, 1);
				}
				return TRUE;
				case 0xCC:
				{

					/**
					 * printActor_AlignCenter
					 */
					OP(printActor_AlignCenter, 0, 1);
				}
				return TRUE;
				case 0xCD:
				{

					/**
					 * printActor_SetCharSet
					 * - Word charsetNum
					 */
					int16 charsetNum = PULL_WORD();
					OP(printActor_SetCharSet, charsetNum, 0, 1);
				}
				return TRUE;
				case 0xCE:
				{

					/**
					 * printActor_AlignLeft
					 */
					OP(printActor_AlignLeft, 0, 1);
				}
				return TRUE;
				case 0xCF:
				{

					/**
					 * printActor_SetOverhead
					 */
					OP(printActor_SetOverhead, 0, 1);
				}
				return TRUE;
				case 0xD0:
				{

					/**
					 * printActor_SetMumble
					 */
					OP(printActor_SetMumble, 0, 1);
				}
				return TRUE;
				case 0xD1:
				{

					/**
					 * printActor
					 * - ImmString text
					 */
					byte* text = READ_STRING();
					OP(printActor, text, 0, 1);
				}
				return TRUE;
				case 0xD2:
				{

					/**
					 * printActor_SetWrapped
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
					 */
					OP(printEgo_ResetState, 0, 2);
				}
				return TRUE;
				case 0xC9:
				{

					/**
					 * printEgo_SaveState
					 */
					OP(printEgo_SaveState, 0, 2);
				}
				return TRUE;
				case 0xCA:
				{

					/**
					 * printEgo_SetPos
					 * - Word x
					 * - Word y
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
					 * - Byte index
					 */
					byte index = PULL_BYTE();
					OP(printEgo_SetColor, index, 0, 2);
				}
				return TRUE;
				case 0xCC:
				{

					/**
					 * printEgo_AlignCenter
					 */
					OP(printEgo_AlignCenter, 0, 2);
				}
				return TRUE;
				case 0xCD:
				{

					/**
					 * printEgo_SetCharSet
					 * - Word charsetNum
					 */
					int16 charsetNum = PULL_WORD();
					OP(printEgo_SetCharSet, charsetNum, 0, 2);
				}
				return TRUE;
				case 0xCE:
				{

					/**
					 * printEgo_AlignLeft
					 */
					OP(printEgo_AlignLeft, 0, 2);
				}
				return TRUE;
				case 0xCF:
				{

					/**
					 * printEgo_SetOverhead
					 */
					OP(printEgo_SetOverhead, 0, 2);
				}
				return TRUE;
				case 0xD0:
				{

					/**
					 * printEgo_SetMumble
					 */
					OP(printEgo_SetMumble, 0, 2);
				}
				return TRUE;
				case 0xD1:
				{

					/**
					 * printEgo
					 * - ImmString text
					 */
					byte* text = READ_STRING();
					OP(printEgo, text, 0, 2);
				}
				return TRUE;
				case 0xD2:
				{

					/**
					 * printEgo_SetWrapped
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
			 * - Long actor
			 */
			int32 actor = PULL_LONG();
			OP(talkActor, actor);
		}
		return TRUE;
		case 0x92:
		{

			/**
			 * talkEgo
			 */
			OP(talkEgo);
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
					 */
					OP(printLine_ResetState, 0, 0);
				}
				return TRUE;
				case 0xC9:
				{

					/**
					 * printLine_SaveState
					 */
					OP(printLine_SaveState, 0, 0);
				}
				return TRUE;
				case 0xCA:
				{

					/**
					 * printLine_SetPos
					 * - Word x
					 * - Word y
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
					 * - Byte index
					 */
					byte index = PULL_BYTE();
					OP(printLine_SetColor, index, 0, 0);
				}
				return TRUE;
				case 0xCC:
				{

					/**
					 * printLine_AlignCenter
					 */
					OP(printLine_AlignCenter, 0, 0);
				}
				return TRUE;
				case 0xCD:
				{

					/**
					 * printLine_SetCharSet
					 * - Word charsetNum
					 */
					int16 charsetNum = PULL_WORD();
					OP(printLine_SetCharSet, charsetNum, 0, 0);
				}
				return TRUE;
				case 0xCE:
				{

					/**
					 * printLine_AlignLeft
					 */
					OP(printLine_AlignLeft, 0, 0);
				}
				return TRUE;
				case 0xCF:
				{

					/**
					 * printLine_SetOverhead
					 */
					OP(printLine_SetOverhead, 0, 0);
				}
				return TRUE;
				case 0xD0:
				{

					/**
					 * printLine_SetMumble
					 */
					OP(printLine_SetMumble, 0, 0);
				}
				return TRUE;
				case 0xD1:
				{

					/**
					 * printLine
					 * - ImmString text
					 */
					byte* text = READ_STRING();
					OP(printLine, text, 0, 0);
				}
				return TRUE;
				case 0xD2:
				{

					/**
					 * printLine_SetWrapped
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
					 */
					OP(printText_ResetState, 1, 0);
				}
				return TRUE;
				case 0xC9:
				{

					/**
					 * printText_SaveState
					 */
					OP(printText_SaveState, 1, 0);
				}
				return TRUE;
				case 0xCA:
				{

					/**
					 * printText_SetPos
					 * - Word x
					 * - Word y
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
					 * - Byte index
					 */
					byte index = PULL_BYTE();
					OP(printText_SetColor, index, 1, 0);
				}
				return TRUE;
				case 0xCC:
				{

					/**
					 * printText_AlignCenter
					 */
					OP(printText_AlignCenter, 1, 0);
				}
				return TRUE;
				case 0xCD:
				{

					/**
					 * printText_SetCharSet
					 * - Word charsetNum
					 */
					int16 charsetNum = PULL_WORD();
					OP(printText_SetCharSet, charsetNum, 1, 0);
				}
				return TRUE;
				case 0xCE:
				{

					/**
					 * printText_AlignLeft
					 */
					OP(printText_AlignLeft, 1, 0);
				}
				return TRUE;
				case 0xCF:
				{

					/**
					 * printText_SetOverhead
					 */
					OP(printText_SetOverhead, 1, 0);
				}
				return TRUE;
				case 0xD0:
				{

					/**
					 * printText_SetMumble
					 */
					OP(printText_SetMumble, 1, 0);
				}
				return TRUE;
				case 0xD1:
				{

					/**
					 * printText
					 * - ImmString text
					 */
					byte* text = READ_STRING();
					OP(printText, text, 1, 0);
				}
				return TRUE;
				case 0xD2:
				{

					/**
					 * printText_SetWrapped
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
					 */
					OP(printDebug_ResetState, 2, 0);
				}
				return TRUE;
				case 0xC9:
				{

					/**
					 * printDebug_SaveState
					 */
					OP(printDebug_SaveState, 2, 0);
				}
				return TRUE;
				case 0xCA:
				{

					/**
					 * printDebug_SetPos
					 * - Word x
					 * - Word y
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
					 * - Byte index
					 */
					byte index = PULL_BYTE();
					OP(printDebug_SetColor, index, 2, 0);
				}
				return TRUE;
				case 0xCC:
				{

					/**
					 * printDebug_AlignCenter
					 */
					OP(printDebug_AlignCenter, 2, 0);
				}
				return TRUE;
				case 0xCD:
				{

					/**
					 * printDebug_SetCharSet
					 * - Word charsetNum
					 */
					int16 charsetNum = PULL_WORD();
					OP(printDebug_SetCharSet, charsetNum, 2, 0);
				}
				return TRUE;
				case 0xCE:
				{

					/**
					 * printDebug_AlignLeft
					 */
					OP(printDebug_AlignLeft, 2, 0);
				}
				return TRUE;
				case 0xCF:
				{

					/**
					 * printDebug_SetOverhead
					 */
					OP(printDebug_SetOverhead, 2, 0);
				}
				return TRUE;
				case 0xD0:
				{

					/**
					 * printDebug_SetMumble
					 */
					OP(printDebug_SetMumble, 2, 0);
				}
				return TRUE;
				case 0xD1:
				{

					/**
					 * printDebug
					 * - ImmString text
					 */
					byte* text = READ_STRING();
					OP(printDebug, text, 2, 0);
				}
				return TRUE;
				case 0xD2:
				{

					/**
					 * printDebug_SetWrapped
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
					 */
					OP(printSystem_ResetState, 3, 0);
				}
				return TRUE;
				case 0xC9:
				{

					/**
					 * printSystem_SaveState
					 */
					OP(printSystem_SaveState, 3, 0);
				}
				return TRUE;
				case 0xCA:
				{

					/**
					 * printSystem_SetPos
					 * - Word x
					 * - Word y
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
					 * - Byte index
					 */
					byte index = PULL_BYTE();
					OP(printSystem_SetColor, index, 3, 0);
				}
				return TRUE;
				case 0xCC:
				{

					/**
					 * printSystem_AlignCenter
					 */
					OP(printSystem_AlignCenter, 3, 0);
				}
				return TRUE;
				case 0xCD:
				{

					/**
					 * printSystem_SetCharSet
					 * - Word charsetNum
					 */
					int16 charsetNum = PULL_WORD();
					OP(printSystem_SetCharSet, charsetNum, 3, 0);
				}
				return TRUE;
				case 0xCE:
				{

					/**
					 * printSystem_AlignLeft
					 */
					OP(printSystem_AlignLeft, 3, 0);
				}
				return TRUE;
				case 0xCF:
				{

					/**
					 * printSystem_SetOverhead
					 */
					OP(printSystem_SetOverhead, 3, 0);
				}
				return TRUE;
				case 0xD0:
				{

					/**
					 * printSystem_SetMumble
					 */
					OP(printSystem_SetMumble, 3, 0);
				}
				return TRUE;
				case 0xD1:
				{

					/**
					 * printSystem
					 * - ImmString text
					 */
					byte* text = READ_STRING();
					OP(printSystem, text, 3, 0);
				}
				return TRUE;
				case 0xD2:
				{

					/**
					 * printSystem_SetWrapped
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
					 */
					OP(blastText_ResetState, 4, 0);
				}
				return TRUE;
				case 0xC9:
				{

					/**
					 * blastText_SaveState
					 */
					OP(blastText_SaveState, 4, 0);
				}
				return TRUE;
				case 0xCA:
				{

					/**
					 * blastText_SetPos
					 * - Word x
					 * - Word y
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
					 * - Byte index
					 */
					byte index = PULL_BYTE();
					OP(blastText_SetColor, index, 4, 0);
				}
				return TRUE;
				case 0xCC:
				{

					/**
					 * blastText_AlignCenter
					 */
					OP(blastText_AlignCenter, 4, 0);
				}
				return TRUE;
				case 0xCD:
				{

					/**
					 * blastText_SetCharSet
					 * - Word charsetNum
					 */
					int16 charsetNum = PULL_WORD();
					OP(blastText_SetCharSet, charsetNum, 4, 0);
				}
				return TRUE;
				case 0xCE:
				{

					/**
					 * blastText_AlignLeft
					 */
					OP(blastText_AlignLeft, 4, 0);
				}
				return TRUE;
				case 0xCF:
				{

					/**
					 * blastText_SetOverhead
					 */
					OP(blastText_SetOverhead, 4, 0);
				}
				return TRUE;
				case 0xD0:
				{

					/**
					 * blastText_SetMumble
					 */
					OP(blastText_SetMumble, 4, 0);
				}
				return TRUE;
				case 0xD1:
				{

					/**
					 * blastText
					 * - ImmString text
					 */
					byte* text = READ_STRING();
					OP(blastText, text, 4, 0);
				}
				return TRUE;
				case 0xD2:
				{

					/**
					 * blastText_SetWrapped
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
			 * - Long obj
			 * - Long x
			 * - Long y
			 * - Long state
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
					 * - Word objNum
					 * - Long index
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
					 * - Long x
					 * - Long y
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
					 * - Long isTransparent
					 */
					int32 isTransparent = PULL_LONG();
					OP(cursorSetTransparent, isTransparent);
				}
				return TRUE;
				case 0xE7:
				{

					/**
					 * cursorSetCharSet
					 * - Word charsetNum
					 */
					int16 charsetNum = PULL_WORD();
					OP(cursorSetCharSet, charsetNum);
				}
				return TRUE;
				case 0xE8:
				{

					/**
					 * cursorSetCharSetColour
					 * - Args args
					 */
					int* args = PULL_ARGS();
					OP(cursorSetCharSetColour, args);
				}
				return TRUE;
				case 0xE9:
				{

					/**
					 * cursorSetPos
					 * - Long x
					 * - Long y
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
			 * - Byte room
			 */
			byte room = PULL_BYTE();
			OP(loadRoom, room);
		}
		return TRUE;
		case 0x9E:
		{

			/**
			 * loadRoomWithEgo
			 * - Long x
			 * - Long y
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
			 * - Long index
			 * - Long obj
			 * - Long dist
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
			 * - Long index
			 * - Long x
			 * - Long y
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
			 * - Long actorIndex
			 * - Long x
			 * - Long y
			 * - Long room
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
			 * - Long index
			 * - Long obj
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
			 * - Long index
			 * - Long anim
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
			 * - Byte verb
			 * - Word objectA
			 * - Word objectB
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
			 * - Args args
			 * - Long value
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
				case 0x3E:
				{

					/**
					 * loadObject
					 * - Word objectNum
					 */
					int16 objectNum = PULL_WORD();
					OP(loadObject, objectNum);
				}
				return TRUE;
			}
		}
		return FALSE;
		case 0xAB:
		{

			/**
			 * roomOps
			 */
			OP(roomOps);
		}
		return TRUE;
		case 0xAC:
		{

			/**
			 * actorOps
			 */
			OP(actorOps);
		}
		return TRUE;
		case 0xAD:
		{

			/**
			 * cameraOps
			 */
			OP(cameraOps);
		}
		return TRUE;
		case 0xAE:
		{

			/**
			 * verbOps
			 */
			OP(verbOps);
		}
		return TRUE;
		case 0xAF:
		{

			/**
			 * startSound
			 * - Long sound
			 */
			int32 sound = PULL_LONG();
			OP(startSound, sound);
		}
		return TRUE;
		case 0xB0:
		{

			/**
			 * startMusic
			 * - Long sound
			 */
			int32 sound = PULL_LONG();
			OP(startMusic, sound);
		}
		return TRUE;
		case 0xB1:
		{

			/**
			 * stopSound
			 * - Long sound
			 */
			int32 sound = PULL_LONG();
			OP(stopSound, sound);
		}
		return TRUE;
		case 0xB2:
		{

			/**
			 * soundKludge
			 * - Args args
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
			 * - Long a
			 * - Long b
			 * - Long c
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
			 * - Long obj
			 */
			int32 obj = PULL_LONG();
			OP(setObjectName, obj);
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
			 * - Long x
			 * - Long y
			 * - Long x2
			 * - Long y2
			 * - Long color
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
			 */
			OP(startVideo);
		}
		return TRUE;
		case 0xBA:
		{
			switch((op2 = READ_BYTE()))
			{
				case 0x0B:
				{

					/**
					 * lockObject
					 * - Args args
					 */
					int* args = PULL_ARGS();
					OP(lockObject, args);
				}
				return TRUE;
				case 0x0C:
				{

					/**
					 * unlockObject
					 * - Args args
					 */
					int* args = PULL_ARGS();
					OP(unlockObject, args);
				}
				return TRUE;
			}
		}
		return FALSE;
		case 0xC0:
		{

			/**
			 * dim2DimArray
			 * - Long dim2
			 * - Long dim1
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
			 * - Long a
			 * - Long b
			 * - Long c
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
			 * - Long script
			 * - Args args
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
			 * - Long script
			 * - Byte entryp
			 * - Args args
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
			 * - Long i
			 * - Args args
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
			 * - Long i
			 * - Args args
			 * - Long def
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
			 * - Long value
			 * - Args args
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
			 * - Long max
			 */
			int32 max = PULL_LONG();
			OP(getRandomNumber, max);
		}
		return TRUE;
		case 0xCF:
		{

			/**
			 * getRandomNumberRange
			 * - Long min
			 * - Long max
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
			 * - Long obj
			 * - Args args
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
			 * - Long obj
			 */
			int32 obj = PULL_LONG();
			OP(getState, obj);
		}
		return TRUE;
		case 0xD2:
		{

			/**
			 * getOwner
			 * - Long obj
			 */
			int32 obj = PULL_LONG();
			OP(getOwner, obj);
		}
		return TRUE;
		case 0xD3:
		{

			/**
			 * isScriptRunning
			 * - Long script
			 */
			int32 script = PULL_LONG();
			OP(isScriptRunning, script);
		}
		return TRUE;
		case 0xD4:
		{

			/**
			 * shuffle
			 * - Long a
			 * - Long b
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
			 * - Long sound
			 */
			int32 sound = PULL_LONG();
			OP(isSoundRunning, sound);
		}
		return TRUE;
		case 0xD6:
		{

			/**
			 * abs
			 * - Long value
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
			 * - Long index
			 * - Long box
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
			 * - Long verb
			 * - Long entryp
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
			 * - Long x
			 * - Long y
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
			 * - Long x
			 * - Long y
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
			 * - Long x
			 * - Long y
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
			 * - Long owner
			 * - Long index
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
			 * - Long owner
			 */
			int32 owner = PULL_LONG();
			OP(getInventoryCount, owner);
		}
		return TRUE;
		case 0xE1:
		{

			/**
			 * getAnimateVariable
			 * - Long index
			 * - Long variable
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
			 * - Long index
			 */
			int32 index = PULL_LONG();
			OP(getActorRoom, index);
		}
		return TRUE;
		case 0xE3:
		{

			/**
			 * getActorWalkBox
			 * - Long index
			 */
			int32 index = PULL_LONG();
			OP(getActorWalkBox, index);
		}
		return TRUE;
		case 0xE4:
		{

			/**
			 * getActorMoving
			 * - Long index
			 */
			int32 index = PULL_LONG();
			OP(getActorMoving, index);
		}
		return TRUE;
		case 0xE5:
		{

			/**
			 * getActorCostume
			 * - Long index
			 */
			int32 index = PULL_LONG();
			OP(getActorCostume, index);
		}
		return TRUE;
		case 0xE6:
		{

			/**
			 * getActorScaleX
			 * - Long index
			 */
			int32 index = PULL_LONG();
			OP(getActorScaleX, index);
		}
		return TRUE;
		case 0xE7:
		{

			/**
			 * getActorLayer
			 * - Long index
			 */
			int32 index = PULL_LONG();
			OP(getActorLayer, index);
		}
		return TRUE;
		case 0xE8:
		{

			/**
			 * getActorElevation
			 * - Long index
			 */
			int32 index = PULL_LONG();
			OP(getActorElevation, index);
		}
		return TRUE;
		case 0xE9:
		{

			/**
			 * getActorWidth
			 * - Long index
			 */
			int32 index = PULL_LONG();
			OP(getActorWidth, index);
		}
		return TRUE;
		case 0xEA:
		{

			/**
			 * getObjectNewDir
			 * - Long index
			 */
			int32 index = PULL_LONG();
			OP(getObjectNewDir, index);
		}
		return TRUE;
		case 0xEB:
		{

			/**
			 * getObjectX
			 * - Long index
			 */
			int32 index = PULL_LONG();
			OP(getObjectX, index);
		}
		return TRUE;
		case 0xEC:
		{

			/**
			 * getObjectY
			 * - Long index
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
			 * - Long a
			 * - Long b
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
			 * - Long a
			 * - Long b
			 * - Long c
			 * - Long d
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
			 */
			OP(getStringWidth);
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
