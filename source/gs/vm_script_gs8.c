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

#define GS_FILE "vm_script_gs8"

#include "shared/forward.h"
#include "vm_context.h"
#include "vm_stack.h"

#define READ_WORD_AS_LONG(X) 0
#define READ_BYTE(X) 0
#define READ_LONG(X) 0
#define PULL_LONG() (gs_PopStack())
#define PULL_WORD() (gs_PopStack())
#define PULL_BYTE() ((byte) gs_PopStack())



/**
 * pushByte
 * @param byte[1..1] value
 */
GS_PRIVATE GS_INLINE void op__pushByte(gs_VmContext* ctx, byte value)
{
	/* TODO */
}


/**
 * pushWord
 * @param word[1..4] value
 */
GS_PRIVATE GS_INLINE void op__pushWord(gs_VmContext* ctx, int32 value)
{
	/* TODO */
}


/**
 * pushWordVar
 * @param word[1..4] index
 */
GS_PRIVATE GS_INLINE void op__pushWordVar(gs_VmContext* ctx, int32 index)
{
	/* TODO */
}


/**
 * wordArrayRead
 * @param word[1..4] arrayNum
 * @param long[stack, 0] base
 */
GS_PRIVATE GS_INLINE void op__wordArrayRead(gs_VmContext* ctx, int32 arrayNum, int32 base)
{
	/* TODO */
}


/**
 * wordArrayIndexedRead
 * @param word[1..4] arrayNum
 * @param long[stack, 0] index
 * @param long[stack,-1] base
 */
GS_PRIVATE GS_INLINE void op__wordArrayIndexedRead(gs_VmContext* ctx, int32 arrayNum, int32 index, int32 base)
{
	/* TODO */
}


/**
 * dup
 * @param long[stack, 0] value
 */
GS_PRIVATE GS_INLINE void op__dup(gs_VmContext* ctx, int32 value)
{
	/* TODO */
}


/**
 * pop
 * @param long[stack, 0] discard
 */
GS_PRIVATE GS_INLINE void op__pop(gs_VmContext* ctx, int32 discard)
{
	/* TODO */
}


/**
 * not
 * @param long[stack, 0] value
 */
GS_PRIVATE GS_INLINE void op__not(gs_VmContext* ctx, int32 value)
{
	/* TODO */
}


/**
 * eq
 * @param long[stack, 0] a
 * @param long[stack,-1] b
 */
GS_PRIVATE GS_INLINE void op__eq(gs_VmContext* ctx, int32 a, int32 b)
{
	/* TODO */
}


/**
 * neq
 * @param long[stack, 0] a
 * @param long[stack,-1] b
 */
GS_PRIVATE GS_INLINE void op__neq(gs_VmContext* ctx, int32 a, int32 b)
{
	/* TODO */
}


/**
 * gt
 * @param long[stack, 0] a
 * @param long[stack,-1] b
 */
GS_PRIVATE GS_INLINE void op__gt(gs_VmContext* ctx, int32 a, int32 b)
{
	/* TODO */
}


/**
 * lt
 * @param long[stack, 0] a
 * @param long[stack,-1] b
 */
GS_PRIVATE GS_INLINE void op__lt(gs_VmContext* ctx, int32 a, int32 b)
{
	/* TODO */
}


/**
 * le
 * @param long[stack, 0] a
 * @param long[stack,-1] b
 */
GS_PRIVATE GS_INLINE void op__le(gs_VmContext* ctx, int32 a, int32 b)
{
	/* TODO */
}


/**
 * ge
 * @param long[stack, 0] a
 * @param long[stack,-1] b
 */
GS_PRIVATE GS_INLINE void op__ge(gs_VmContext* ctx, int32 a, int32 b)
{
	/* TODO */
}


/**
 * add
 * @param long[stack, 0] a
 * @param long[stack,-1] b
 */
GS_PRIVATE GS_INLINE void op__add(gs_VmContext* ctx, int32 a, int32 b)
{
	/* TODO */
}


/**
 * sub
 * @param long[stack, 0] a
 * @param long[stack,-1] b
 */
GS_PRIVATE GS_INLINE void op__sub(gs_VmContext* ctx, int32 a, int32 b)
{
	/* TODO */
}


/**
 * mul
 * @param long[stack, 0] a
 * @param long[stack,-1] b
 */
GS_PRIVATE GS_INLINE void op__mul(gs_VmContext* ctx, int32 a, int32 b)
{
	/* TODO */
}


/**
 * div
 * @param long[stack, 0] a
 * @param long[stack,-1] b
 */
GS_PRIVATE GS_INLINE void op__div(gs_VmContext* ctx, int32 a, int32 b)
{
	/* TODO */
}


/**
 * land
 * @param long[stack, 0] a
 * @param long[stack,-1] b
 */
GS_PRIVATE GS_INLINE void op__land(gs_VmContext* ctx, int32 a, int32 b)
{
	/* TODO */
}


/**
 * lor
 * @param long[stack, 0] a
 * @param long[stack,-1] b
 */
GS_PRIVATE GS_INLINE void op__lor(gs_VmContext* ctx, int32 a, int32 b)
{
	/* TODO */
}


/**
 * band
 * @param long[stack, 0] a
 * @param long[stack,-1] b
 */
GS_PRIVATE GS_INLINE void op__band(gs_VmContext* ctx, int32 a, int32 b)
{
	/* TODO */
}


/**
 * bor
 * @param long[stack, 0] a
 * @param long[stack,-1] b
 */
GS_PRIVATE GS_INLINE void op__bor(gs_VmContext* ctx, int32 a, int32 b)
{
	/* TODO */
}


/**
 * mod
 * @param long[stack, 0] a
 * @param long[stack,-1] b
 */
GS_PRIVATE GS_INLINE void op__mod(gs_VmContext* ctx, int32 a, int32 b)
{
	/* TODO */
}


/**
 * writeByteVar
 * @param long[stack, 0] value
 */
GS_PRIVATE GS_INLINE void op__writeByteVar(gs_VmContext* ctx, int32 value)
{
	/* TODO */
}


/**
 * byteArrayWrite
 * @param long[stack, 0] base
 * @param long[stack,-1] value
 */
GS_PRIVATE GS_INLINE void op__byteArrayWrite(gs_VmContext* ctx, int32 base, int32 value)
{
	/* TODO */
}


/**
 * byteArrayIndexedWrite
 * @param long[stack, 0] index
 * @param long[stack,-1] base
 * @param long[stack,-2] value
 */
GS_PRIVATE GS_INLINE void op__byteArrayIndexedWrite(gs_VmContext* ctx, int32 index, int32 base, int32 value)
{
	/* TODO */
}


/**
 * byteVarInc
 */
GS_PRIVATE GS_INLINE void op__byteVarInc(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * byteArrayInc
 * @param long[stack, 0] base
 */
GS_PRIVATE GS_INLINE void op__byteArrayInc(gs_VmContext* ctx, int32 base)
{
	/* TODO */
}


/**
 * byteVarDec
 */
GS_PRIVATE GS_INLINE void op__byteVarDec(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * byteArrayDec
 * @param long[stack, 0] base
 */
GS_PRIVATE GS_INLINE void op__byteArrayDec(gs_VmContext* ctx, int32 base)
{
	/* TODO */
}


/**
 * drawObject
 * @param long[stack, 0] obj
 * @param long[stack,-1] state
 */
GS_PRIVATE GS_INLINE void op__drawObject(gs_VmContext* ctx, int32 obj, int32 state)
{
	/* TODO */
}


/**
 * drawObjectAt
 * @param long[stack, 0] obj
 * @param long[stack,-1] x
 * @param long[stack,-2] y
 */
GS_PRIVATE GS_INLINE void op__drawObjectAt(gs_VmContext* ctx, int32 obj, int32 x, int32 y)
{
	/* TODO */
}


/**
 * drawBlastObject
 * @param long[stack, 0] a
 * @param long[stack,-1] b
 * @param long[stack,-2] c
 * @param long[stack,-3] d
 * @param long[stack,-4] e
 * @param args[stack,-5] args
 */
GS_PRIVATE GS_INLINE void op__drawBlastObject(gs_VmContext* ctx, int32 a, int32 b, int32 c, int32 d, int32 e, int32* args)
{
	/* TODO */
}


/**
 * if
 * @param word[1..4] relOffset
 * @param long[stack, 0] condition
 */
GS_PRIVATE GS_INLINE void op__if(gs_VmContext* ctx, int32 condition, int32 relOffset)
{
	/* TODO */
}


/**
 * ifNot
 * @param word[1..4] relOffset
 * @param long[stack, 0] condition
 */
GS_PRIVATE GS_INLINE void op__ifNot(gs_VmContext* ctx, int32 condition, int32 relOffset)
{
	/* TODO */
}


/**
 * jump
 * @param word[1..4] relOffset
 */
GS_PRIVATE GS_INLINE void op__jump(gs_VmContext* ctx, int32 relOffset)
{
	/* TODO */
}


/**
 * breakHere
 */
GS_PRIVATE GS_INLINE void op__breakHere(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * delayFrames
 */
GS_PRIVATE GS_INLINE void op__delayFrames(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * waitForActor
 * @param word[2..5] actorNum
 * @param long[stack, 0] offset
 */
GS_PRIVATE GS_INLINE void op__waitForActor(gs_VmContext* ctx, int32 offset, int32 actorNum)
{
	/* TODO */
}


/**
 * waitForMessage
 * @const offset = -2
 */
GS_PRIVATE GS_INLINE void op__waitForMessage(gs_VmContext* ctx, int32 offset)
{
	/* TODO */
}


/**
 * waitForCamera
 * @const offset = -2
 */
GS_PRIVATE GS_INLINE void op__waitForCamera(gs_VmContext* ctx, int32 offset)
{
	/* TODO */
}


/**
 * waitForSentence
 * @const offset = -2
 */
GS_PRIVATE GS_INLINE void op__waitForSentence(gs_VmContext* ctx, int32 offset)
{
	/* TODO */
}


/**
 * waitForAnimation
 * @param word[2..5] actorNum
 * @param long[stack, 0] offset
 */
GS_PRIVATE GS_INLINE void op__waitForAnimation(gs_VmContext* ctx, int32 offset, int32 actorNum)
{
	/* TODO */
}


/**
 * waitForTurn
 * @param word[2..5] actorNum
 * @param long[stack, 0] offset
 */
GS_PRIVATE GS_INLINE void op__waitForTurn(gs_VmContext* ctx, int32 offset, int32 actorNum)
{
	/* TODO */
}


/**
 * delay
 * @param long[stack, 0] delay
 */
GS_PRIVATE GS_INLINE void op__delay(gs_VmContext* ctx, int32 delay)
{
	/* TODO */
}


/**
 * delaySeconds
 * @param long[stack, 0] seconds
 */
GS_PRIVATE GS_INLINE void op__delaySeconds(gs_VmContext* ctx, int32 seconds)
{
	/* TODO */
}


/**
 * delayMinutes
 * @param long[stack, 0] minutes
 */
GS_PRIVATE GS_INLINE void op__delayMinutes(gs_VmContext* ctx, int32 minutes)
{
	/* TODO */
}


/**
 * writeWordVar
 * @param long[1..4] varIndex
 * @param long[stack, 0] value
 */
GS_PRIVATE GS_INLINE void op__writeWordVar(gs_VmContext* ctx, int32 varIndex, int32 value)
{
	/* TODO */
}


/**
 * wordVarInc
 * @param long[1..4] varIndex
 */
GS_PRIVATE GS_INLINE void op__wordVarInc(gs_VmContext* ctx, int32 varIndex)
{
	/* TODO */
}


/**
 * wordVarDec
 * @param long[1..4] varIndex
 */
GS_PRIVATE GS_INLINE void op__wordVarDec(gs_VmContext* ctx, int32 varIndex)
{
	/* TODO */
}


/**
 * newIntArray
 * @param word[2..5] arrayNum
 * @param long[stack, 0] dim1
 */
GS_PRIVATE GS_INLINE void op__newIntArray(gs_VmContext* ctx, int32 arrayNum, int32 dim1)
{
	/* TODO */
}


/**
 * newStringArray
 * @param word[2..5] arrayNum
 * @param long[stack, 0] dim1
 */
GS_PRIVATE GS_INLINE void op__newStringArray(gs_VmContext* ctx, int32 arrayNum, int32 dim1)
{
	/* TODO */
}


/**
 * deleteArray
 * @param word[2..5] arrayNum
 */
GS_PRIVATE GS_INLINE void op__deleteArray(gs_VmContext* ctx, int32 arrayNum)
{
	/* TODO */
}


/**
 * wordArrayWrite
 * @param word[1..4] arrayNum
 * @param long[stack, 0] base
 * @param long[stack,-1] value
 */
GS_PRIVATE GS_INLINE void op__wordArrayWrite(gs_VmContext* ctx, int32 arrayNum, int32 base, int32 value)
{
	/* TODO */
}


/**
 * wordArrayInc
 * @param word[1..4] arrayNum
 * @param long[stack, 0] base
 */
GS_PRIVATE GS_INLINE void op__wordArrayInc(gs_VmContext* ctx, int32 arrayNum, int32 base)
{
	/* TODO */
}


/**
 * wordArrayDec
 * @param word[1..4] arrayNum
 * @param long[stack, 0] base
 */
GS_PRIVATE GS_INLINE void op__wordArrayDec(gs_VmContext* ctx, int32 arrayNum, int32 base)
{
	/* TODO */
}


/**
 * newIntArray2
 * @param word[2..5] arrayNum
 * @param long[stack, 0] dim1
 * @param long[stack,-1] dim2
 */
GS_PRIVATE GS_INLINE void op__newIntArray2(gs_VmContext* ctx, int32 arrayNum, int32 dim1, int32 dim2)
{
	/* TODO */
}


/**
 * newStringArray2
 * @param word[2..5] arrayNum
 * @param long[stack, 0] dim1
 * @param long[stack,-1] dim2
 */
GS_PRIVATE GS_INLINE void op__newStringArray2(gs_VmContext* ctx, int32 arrayNum, int32 dim1, int32 dim2)
{
	/* TODO */
}


/**
 * deleteARray2
 * @param word[2..5] arrayNum
 * @param long[stack, 0] dim1
 * @param long[stack,-1] dim2
 */
GS_PRIVATE GS_INLINE void op__deleteARray2(gs_VmContext* ctx, int32 arrayNum, int32 dim1, int32 dim2)
{
	/* TODO */
}


/**
 * wordArrayIndexedWrite
 * @param word[1..4] arrayNum
 * @param long[stack, 0] index
 * @param long[stack,-1] base
 * @param long[stack,-2] value
 */
GS_PRIVATE GS_INLINE void op__wordArrayIndexedWrite(gs_VmContext* ctx, int32 arrayNum, int32 index, int32 base, int32 value)
{
	/* TODO */
}


/**
 * copyStringArray
 * @param word[2..5] arrayNum
 * @param string[6...] data
 * @param long[stack, 0] b
 */
GS_PRIVATE GS_INLINE void op__copyStringArray(gs_VmContext* ctx, int32 arrayNum, char* data, int32 b)
{
	/* TODO */
}


/**
 * copyIntArray
 * @param word[2..5] arrayNum
 * @param args[stack, 0] args
 * @param long[stack,-1] b
 */
GS_PRIVATE GS_INLINE void op__copyIntArray(gs_VmContext* ctx, int32 arrayNum, int32* args, int32 b)
{
	/* TODO */
}


/**
 * copyDim2Array
 * @param word[2..5] arrayNum
 * @param args[stack, 0] args
 * @param long[stack,-1] b
 */
GS_PRIVATE GS_INLINE void op__copyDim2Array(gs_VmContext* ctx, int32 arrayNum, int32* args, int32 b)
{
	/* TODO */
}


/**
 * startScript
 * @param long[stack, 0] flags
 * @param long[stack,-1] script
 * @param args[stack,-2] args
 */
GS_PRIVATE GS_INLINE void op__startScript(gs_VmContext* ctx, int32 flags, int32 script, int32* args)
{
	/* TODO */
}


/**
 * startScriptQuick
 * @param long[stack, 0] script
 * @param args[stack,-1] args
 */
GS_PRIVATE GS_INLINE void op__startScriptQuick(gs_VmContext* ctx, int32 script, int32* args)
{
	/* TODO */
}


/**
 * stopObjectCode6
 */
GS_PRIVATE GS_INLINE void op__stopObjectCode6(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * stopScript6
 * @param long[stack, 0] script
 */
GS_PRIVATE GS_INLINE void op__stopScript6(gs_VmContext* ctx, int32 script)
{
	/* TODO */
}


/**
 * jumpToScript
 * @param long[stack, 0] flags
 * @param long[stack,-1] script
 * @param args[stack,-2] args
 */
GS_PRIVATE GS_INLINE void op__jumpToScript(gs_VmContext* ctx, int32 flags, int32 script, int32* args)
{
	/* TODO */
}


/**
 * dummy
 */
GS_PRIVATE GS_INLINE void op__dummy(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * startObject
 * @param long[stack, 0] flags
 * @param long[stack,-1] script
 * @param byte[stack,-2] entryp
 * @param args[stack,-3] args
 */
GS_PRIVATE GS_INLINE void op__startObject(gs_VmContext* ctx, int32 flags, int32 script, byte entryp, int32* args)
{
	/* TODO */
}


/**
 * stopObjectScript
 * @param word[stack, 0] script
 */
GS_PRIVATE GS_INLINE void op__stopObjectScript(gs_VmContext* ctx, int32 script)
{
	/* TODO */
}


/**
 * cutscene
 * @param args[stack, 0] args
 */
GS_PRIVATE GS_INLINE void op__cutscene(gs_VmContext* ctx, int32* args)
{
	/* TODO */
}


/**
 * endCutscene
 */
GS_PRIVATE GS_INLINE void op__endCutscene(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * freezeUnfreeze
 * @param long[stack, 0] scriptNum
 */
GS_PRIVATE GS_INLINE void op__freezeUnfreeze(gs_VmContext* ctx, int32 scriptNum)
{
	/* TODO */
}


/**
 * beginOverride
 */
GS_PRIVATE GS_INLINE void op__beginOverride(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * endOverride
 */
GS_PRIVATE GS_INLINE void op__endOverride(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * stopSentence
 */
GS_PRIVATE GS_INLINE void op__stopSentence(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * unknown_87
 */
GS_PRIVATE GS_INLINE void op__unknown_87(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * setClass
 * @param long[stack, 0] obj
 * @param args[stack,-1] args
 */
GS_PRIVATE GS_INLINE void op__setClass(gs_VmContext* ctx, int32 obj, int32* args)
{
	/* TODO */
}


/**
 * setState
 * @param long[stack, 0] obj
 * @param long[stack,-1] state
 */
GS_PRIVATE GS_INLINE void op__setState(gs_VmContext* ctx, int32 obj, int32 state)
{
	/* TODO */
}


/**
 * setOwner
 * @param long[stack, 0] obj
 * @param long[stack,-1] owner
 */
GS_PRIVATE GS_INLINE void op__setOwner(gs_VmContext* ctx, int32 obj, int32 owner)
{
	/* TODO */
}


/**
 * panCameraTo
 */
GS_PRIVATE GS_INLINE void op__panCameraTo(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * actorFollowCamera
 * @param long[stack, 0] index
 */
GS_PRIVATE GS_INLINE void op__actorFollowCamera(gs_VmContext* ctx, int32 index)
{
	/* TODO */
}


/**
 * setCameraAt
 */
GS_PRIVATE GS_INLINE void op__setCameraAt(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * printActor_ResetState
 * @const target = 0
 * @const pullActor = 1
 */
GS_PRIVATE GS_INLINE void op__printActor_ResetState(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printActor_SaveState
 * @const target = 0
 * @const pullActor = 1
 */
GS_PRIVATE GS_INLINE void op__printActor_SaveState(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printActor_SetPos
 * @param word[stack, 0] x
 * @param word[stack,-1] y
 * @const target = 0
 * @const pullActor = 1
 */
GS_PRIVATE GS_INLINE void op__printActor_SetPos(gs_VmContext* ctx, int32 x, int32 y, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printActor_SetColor
 * @param byte[stack, 0] index
 * @const target = 0
 * @const pullActor = 1
 */
GS_PRIVATE GS_INLINE void op__printActor_SetColor(gs_VmContext* ctx, byte index, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printActor_AlignCenter
 * @const target = 0
 * @const pullActor = 1
 */
GS_PRIVATE GS_INLINE void op__printActor_AlignCenter(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printActor_SetCharSet
 * @param word[stack, 0] charsetNum
 * @const target = 0
 * @const pullActor = 1
 */
GS_PRIVATE GS_INLINE void op__printActor_SetCharSet(gs_VmContext* ctx, int32 charsetNum, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printActor_AlignLeft
 * @const target = 0
 * @const pullActor = 1
 */
GS_PRIVATE GS_INLINE void op__printActor_AlignLeft(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printActor_SetOverhead
 * @const target = 0
 * @const pullActor = 1
 */
GS_PRIVATE GS_INLINE void op__printActor_SetOverhead(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printActor_SetMumble
 * @const target = 0
 * @const pullActor = 1
 */
GS_PRIVATE GS_INLINE void op__printActor_SetMumble(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printActor
 * @param string[2...] text
 * @const target = 0
 * @const pullActor = 1
 */
GS_PRIVATE GS_INLINE void op__printActor(gs_VmContext* ctx, char* text, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printActor_SetWrapped
 * @const target = 0
 * @const pullActor = 1
 */
GS_PRIVATE GS_INLINE void op__printActor_SetWrapped(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printEgo_ResetState
 * @const target = 0
 * @const pullActor = 2
 */
GS_PRIVATE GS_INLINE void op__printEgo_ResetState(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printEgo_SaveState
 * @const target = 0
 * @const pullActor = 2
 */
GS_PRIVATE GS_INLINE void op__printEgo_SaveState(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printEgo_SetPos
 * @param word[stack, 0] x
 * @param word[stack,-1] y
 * @const target = 0
 * @const pullActor = 2
 */
GS_PRIVATE GS_INLINE void op__printEgo_SetPos(gs_VmContext* ctx, int32 x, int32 y, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printEgo_SetColor
 * @param byte[stack, 0] index
 * @const target = 0
 * @const pullActor = 2
 */
GS_PRIVATE GS_INLINE void op__printEgo_SetColor(gs_VmContext* ctx, byte index, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printEgo_AlignCenter
 * @const target = 0
 * @const pullActor = 2
 */
GS_PRIVATE GS_INLINE void op__printEgo_AlignCenter(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printEgo_SetCharSet
 * @param word[stack, 0] charsetNum
 * @const target = 0
 * @const pullActor = 2
 */
GS_PRIVATE GS_INLINE void op__printEgo_SetCharSet(gs_VmContext* ctx, int32 charsetNum, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printEgo_AlignLeft
 * @const target = 0
 * @const pullActor = 2
 */
GS_PRIVATE GS_INLINE void op__printEgo_AlignLeft(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printEgo_SetOverhead
 * @const target = 0
 * @const pullActor = 2
 */
GS_PRIVATE GS_INLINE void op__printEgo_SetOverhead(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printEgo_SetMumble
 * @const target = 0
 * @const pullActor = 2
 */
GS_PRIVATE GS_INLINE void op__printEgo_SetMumble(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printEgo
 * @param string[2...] text
 * @const target = 0
 * @const pullActor = 2
 */
GS_PRIVATE GS_INLINE void op__printEgo(gs_VmContext* ctx, char* text, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printEgo_SetWrapped
 * @const target = 0
 * @const pullActor = 2
 */
GS_PRIVATE GS_INLINE void op__printEgo_SetWrapped(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * talkActor
 * @param string[1...] text
 * @param word[stack, 0] actorNum
 */
GS_PRIVATE GS_INLINE void op__talkActor(gs_VmContext* ctx, int32 actorNum, char* text)
{
	/* TODO */
}


/**
 * talkEgo
 * @param string[1...] text
 */
GS_PRIVATE GS_INLINE void op__talkEgo(gs_VmContext* ctx, char* text)
{
	/* TODO */
}


/**
 * printLine_ResetState
 * @const target = 0
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printLine_ResetState(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printLine_SaveState
 * @const target = 0
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printLine_SaveState(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printLine_SetPos
 * @param word[stack, 0] x
 * @param word[stack,-1] y
 * @const target = 0
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printLine_SetPos(gs_VmContext* ctx, int32 x, int32 y, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printLine_SetColor
 * @param byte[stack, 0] index
 * @const target = 0
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printLine_SetColor(gs_VmContext* ctx, byte index, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printLine_AlignCenter
 * @const target = 0
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printLine_AlignCenter(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printLine_SetCharSet
 * @param word[stack, 0] charsetNum
 * @const target = 0
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printLine_SetCharSet(gs_VmContext* ctx, int32 charsetNum, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printLine_AlignLeft
 * @const target = 0
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printLine_AlignLeft(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printLine_SetOverhead
 * @const target = 0
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printLine_SetOverhead(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printLine_SetMumble
 * @const target = 0
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printLine_SetMumble(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printLine
 * @param string[2...] text
 * @const target = 0
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printLine(gs_VmContext* ctx, char* text, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printLine_SetWrapped
 * @const target = 0
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printLine_SetWrapped(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printText_ResetState
 * @const target = 1
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printText_ResetState(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printText_SaveState
 * @const target = 1
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printText_SaveState(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printText_SetPos
 * @param word[stack, 0] x
 * @param word[stack,-1] y
 * @const target = 1
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printText_SetPos(gs_VmContext* ctx, int32 x, int32 y, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printText_SetColor
 * @param byte[stack, 0] index
 * @const target = 1
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printText_SetColor(gs_VmContext* ctx, byte index, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printText_AlignCenter
 * @const target = 1
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printText_AlignCenter(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printText_SetCharSet
 * @param word[stack, 0] charsetNum
 * @const target = 1
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printText_SetCharSet(gs_VmContext* ctx, int32 charsetNum, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printText_AlignLeft
 * @const target = 1
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printText_AlignLeft(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printText_SetOverhead
 * @const target = 1
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printText_SetOverhead(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printText_SetMumble
 * @const target = 1
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printText_SetMumble(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printText
 * @param string[2...] text
 * @const target = 1
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printText(gs_VmContext* ctx, char* text, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printText_SetWrapped
 * @const target = 1
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printText_SetWrapped(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printDebug_ResetState
 * @const target = 2
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printDebug_ResetState(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printDebug_SaveState
 * @const target = 2
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printDebug_SaveState(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printDebug_SetPos
 * @param word[stack, 0] x
 * @param word[stack,-1] y
 * @const target = 2
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printDebug_SetPos(gs_VmContext* ctx, int32 x, int32 y, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printDebug_SetColor
 * @param byte[stack, 0] index
 * @const target = 2
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printDebug_SetColor(gs_VmContext* ctx, byte index, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printDebug_AlignCenter
 * @const target = 2
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printDebug_AlignCenter(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printDebug_SetCharSet
 * @param word[stack, 0] charsetNum
 * @const target = 2
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printDebug_SetCharSet(gs_VmContext* ctx, int32 charsetNum, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printDebug_AlignLeft
 * @const target = 2
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printDebug_AlignLeft(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printDebug_SetOverhead
 * @const target = 2
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printDebug_SetOverhead(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printDebug_SetMumble
 * @const target = 2
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printDebug_SetMumble(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printDebug
 * @param string[2...] text
 * @const target = 2
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printDebug(gs_VmContext* ctx, char* text, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printDebug_SetWrapped
 * @const target = 2
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printDebug_SetWrapped(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printSystem_ResetState
 * @const target = 3
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printSystem_ResetState(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printSystem_SaveState
 * @const target = 3
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printSystem_SaveState(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printSystem_SetPos
 * @param word[stack, 0] x
 * @param word[stack,-1] y
 * @const target = 3
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printSystem_SetPos(gs_VmContext* ctx, int32 x, int32 y, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printSystem_SetColor
 * @param byte[stack, 0] index
 * @const target = 3
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printSystem_SetColor(gs_VmContext* ctx, byte index, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printSystem_AlignCenter
 * @const target = 3
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printSystem_AlignCenter(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printSystem_SetCharSet
 * @param word[stack, 0] charsetNum
 * @const target = 3
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printSystem_SetCharSet(gs_VmContext* ctx, int32 charsetNum, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printSystem_AlignLeft
 * @const target = 3
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printSystem_AlignLeft(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printSystem_SetOverhead
 * @const target = 3
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printSystem_SetOverhead(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printSystem_SetMumble
 * @const target = 3
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printSystem_SetMumble(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printSystem
 * @param string[2...] text
 * @const target = 3
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printSystem(gs_VmContext* ctx, char* text, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * printSystem_SetWrapped
 * @const target = 3
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__printSystem_SetWrapped(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * blastText_ResetState
 * @const target = 4
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__blastText_ResetState(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * blastText_SaveState
 * @const target = 4
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__blastText_SaveState(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * blastText_SetPos
 * @param word[stack, 0] x
 * @param word[stack,-1] y
 * @const target = 4
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__blastText_SetPos(gs_VmContext* ctx, int32 x, int32 y, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * blastText_SetColor
 * @param byte[stack, 0] index
 * @const target = 4
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__blastText_SetColor(gs_VmContext* ctx, byte index, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * blastText_AlignCenter
 * @const target = 4
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__blastText_AlignCenter(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * blastText_SetCharSet
 * @param word[stack, 0] charsetNum
 * @const target = 4
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__blastText_SetCharSet(gs_VmContext* ctx, int32 charsetNum, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * blastText_AlignLeft
 * @const target = 4
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__blastText_AlignLeft(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * blastText_SetOverhead
 * @const target = 4
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__blastText_SetOverhead(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * blastText_SetMumble
 * @const target = 4
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__blastText_SetMumble(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * blastText
 * @param string[2...] text
 * @const target = 4
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__blastText(gs_VmContext* ctx, char* text, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * blastText_SetWrapped
 * @const target = 4
 * @const pullActor = 0
 */
GS_PRIVATE GS_INLINE void op__blastText_SetWrapped(gs_VmContext* ctx, int32 target, int32 pullActor)
{
	/* TODO */
}


/**
 * drawObject
 * @param long[stack, 0] obj
 * @param long[stack,-1] x
 * @param long[stack,-2] y
 * @param long[stack,-3] state
 */
GS_PRIVATE GS_INLINE void op__drawObject(gs_VmContext* ctx, int32 obj, int32 x, int32 y, int32 state)
{
	/* TODO */
}


/**
 * cursorSetOn
 */
GS_PRIVATE GS_INLINE void op__cursorSetOn(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * cursorSetOff
 */
GS_PRIVATE GS_INLINE void op__cursorSetOff(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * cursorSetSoftOn
 */
GS_PRIVATE GS_INLINE void op__cursorSetSoftOn(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * cursorSetSoftOff
 */
GS_PRIVATE GS_INLINE void op__cursorSetSoftOff(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * cursorSetUserPutOn
 */
GS_PRIVATE GS_INLINE void op__cursorSetUserPutOn(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * cursorSetUserPutOff
 */
GS_PRIVATE GS_INLINE void op__cursorSetUserPutOff(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * cursorSetUserPutSoftOn
 */
GS_PRIVATE GS_INLINE void op__cursorSetUserPutSoftOn(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * cursorSetUserPutSoftOff
 */
GS_PRIVATE GS_INLINE void op__cursorSetUserPutSoftOff(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * cursorSetImage
 * @param word[stack, 0] objNum
 * @param long[stack,-1] index
 */
GS_PRIVATE GS_INLINE void op__cursorSetImage(gs_VmContext* ctx, int32 objNum, int32 index)
{
	/* TODO */
}


/**
 * cursorSetHotSpot
 * @param long[stack, 0] x
 * @param long[stack,-1] y
 */
GS_PRIVATE GS_INLINE void op__cursorSetHotSpot(gs_VmContext* ctx, int32 x, int32 y)
{
	/* TODO */
}


/**
 * cursorSetTransparent
 * @param long[stack, 0] isTransparent
 */
GS_PRIVATE GS_INLINE void op__cursorSetTransparent(gs_VmContext* ctx, int32 isTransparent)
{
	/* TODO */
}


/**
 * cursorSetCharSet
 * @param word[stack, 0] charsetNum
 */
GS_PRIVATE GS_INLINE void op__cursorSetCharSet(gs_VmContext* ctx, int32 charsetNum)
{
	/* TODO */
}


/**
 * cursorSetCharSetColour
 * @param args[stack, 0] args
 */
GS_PRIVATE GS_INLINE void op__cursorSetCharSetColour(gs_VmContext* ctx, int32* args)
{
	/* TODO */
}


/**
 * cursorSetPos
 * @param long[stack, 0] x
 * @param long[stack,-1] y
 */
GS_PRIVATE GS_INLINE void op__cursorSetPos(gs_VmContext* ctx, int32 x, int32 y)
{
	/* TODO */
}


/**
 * loadRoom
 * @param byte[stack, 0] room
 */
GS_PRIVATE GS_INLINE void op__loadRoom(gs_VmContext* ctx, byte room)
{
	/* TODO */
}


/**
 * loadRoomWithEgo
 * @param long[stack, 0] x
 * @param long[stack,-1] y
 */
GS_PRIVATE GS_INLINE void op__loadRoomWithEgo(gs_VmContext* ctx, int32 x, int32 y)
{
	/* TODO */
}


/**
 * walkActorToObj
 * @param long[stack, 0] index
 * @param long[stack,-1] obj
 * @param long[stack,-2] dist
 */
GS_PRIVATE GS_INLINE void op__walkActorToObj(gs_VmContext* ctx, int32 index, int32 obj, int32 dist)
{
	/* TODO */
}


/**
 * walkActorTo
 * @param long[stack, 0] index
 * @param long[stack,-1] x
 * @param long[stack,-2] y
 */
GS_PRIVATE GS_INLINE void op__walkActorTo(gs_VmContext* ctx, int32 index, int32 x, int32 y)
{
	/* TODO */
}


/**
 * putActorAtXY
 * @param long[stack, 0] actorIndex
 * @param long[stack,-1] x
 * @param long[stack,-2] y
 * @param long[stack,-3] room
 */
GS_PRIVATE GS_INLINE void op__putActorAtXY(gs_VmContext* ctx, int32 actorIndex, int32 x, int32 y, int32 room)
{
	/* TODO */
}


/**
 * putActorAtObject
 */
GS_PRIVATE GS_INLINE void op__putActorAtObject(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * faceActor
 * @param long[stack, 0] index
 * @param long[stack,-1] obj
 */
GS_PRIVATE GS_INLINE void op__faceActor(gs_VmContext* ctx, int32 index, int32 obj)
{
	/* TODO */
}


/**
 * animateActor
 * @param long[stack, 0] index
 * @param long[stack,-1] anim
 */
GS_PRIVATE GS_INLINE void op__animateActor(gs_VmContext* ctx, int32 index, int32 anim)
{
	/* TODO */
}


/**
 * doSentence8
 * @param byte[stack, 0] verb
 * @param word[stack,-1] objectA
 * @param word[stack,-2] objectB
 */
GS_PRIVATE GS_INLINE void op__doSentence8(gs_VmContext* ctx, byte verb, int32 objectA, int32 objectB)
{
	/* TODO */
}


/**
 * pickupObject
 */
GS_PRIVATE GS_INLINE void op__pickupObject(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * setBoxFlags
 * @param args[stack, 0] args
 * @param long[stack,-1] value
 */
GS_PRIVATE GS_INLINE void op__setBoxFlags(gs_VmContext* ctx, int32* args, int32 value)
{
	/* TODO */
}


/**
 * createBoxMatrix
 */
GS_PRIVATE GS_INLINE void op__createBoxMatrix(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * wait
 */
GS_PRIVATE GS_INLINE void op__wait(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * loadCostume
 * @param word[stack, 0] costumeNum
 */
GS_PRIVATE GS_INLINE void op__loadCostume(gs_VmContext* ctx, int32 costumeNum)
{
	/* TODO */
}


/**
 * loadObject
 * @param word[stack, 0] objectNum
 */
GS_PRIVATE GS_INLINE void op__loadObject(gs_VmContext* ctx, int32 objectNum)
{
	/* TODO */
}


/**
 * loadRoom
 * @param word[stack, 0] roomNum
 */
GS_PRIVATE GS_INLINE void op__loadRoom(gs_VmContext* ctx, int32 roomNum)
{
	/* TODO */
}


/**
 * loadScript
 * @param word[stack, 0] scriptNum
 */
GS_PRIVATE GS_INLINE void op__loadScript(gs_VmContext* ctx, int32 scriptNum)
{
	/* TODO */
}


/**
 * loadSound
 * @param word[stack, 0] soundNum
 */
GS_PRIVATE GS_INLINE void op__loadSound(gs_VmContext* ctx, int32 soundNum)
{
	/* TODO */
}


/**
 * lockCostume
 * @param word[stack, 0] costumeNum
 */
GS_PRIVATE GS_INLINE void op__lockCostume(gs_VmContext* ctx, int32 costumeNum)
{
	/* TODO */
}


/**
 * lockRoom
 * @param word[stack, 0] roomNum
 */
GS_PRIVATE GS_INLINE void op__lockRoom(gs_VmContext* ctx, int32 roomNum)
{
	/* TODO */
}


/**
 * lockScript
 * @param word[stack, 0] scriptNum
 */
GS_PRIVATE GS_INLINE void op__lockScript(gs_VmContext* ctx, int32 scriptNum)
{
	/* TODO */
}


/**
 * lockSound
 * @param word[stack, 0] soundNum
 */
GS_PRIVATE GS_INLINE void op__lockSound(gs_VmContext* ctx, int32 soundNum)
{
	/* TODO */
}


/**
 * unlockCostume
 * @param word[stack, 0] costumeNum
 */
GS_PRIVATE GS_INLINE void op__unlockCostume(gs_VmContext* ctx, int32 costumeNum)
{
	/* TODO */
}


/**
 * unlockRoom
 * @param word[stack, 0] roomNum
 */
GS_PRIVATE GS_INLINE void op__unlockRoom(gs_VmContext* ctx, int32 roomNum)
{
	/* TODO */
}


/**
 * unlockScript
 * @param word[stack, 0] scriptNum
 */
GS_PRIVATE GS_INLINE void op__unlockScript(gs_VmContext* ctx, int32 scriptNum)
{
	/* TODO */
}


/**
 * unlockSound
 * @param word[stack, 0] soundNum
 */
GS_PRIVATE GS_INLINE void op__unlockSound(gs_VmContext* ctx, int32 soundNum)
{
	/* TODO */
}


/**
 * deleteCostume
 * @param word[stack, 0] costumeNum
 */
GS_PRIVATE GS_INLINE void op__deleteCostume(gs_VmContext* ctx, int32 costumeNum)
{
	/* TODO */
}


/**
 * deleteRoom
 * @param word[stack, 0] roomNum
 */
GS_PRIVATE GS_INLINE void op__deleteRoom(gs_VmContext* ctx, int32 roomNum)
{
	/* TODO */
}


/**
 * deleteScript
 * @param word[stack, 0] scriptNum
 */
GS_PRIVATE GS_INLINE void op__deleteScript(gs_VmContext* ctx, int32 scriptNum)
{
	/* TODO */
}


/**
 * deleteSound
 * @param word[stack, 0] soundNum
 */
GS_PRIVATE GS_INLINE void op__deleteSound(gs_VmContext* ctx, int32 soundNum)
{
	/* TODO */
}


/**
 * setRoomPalette
 * @param byte[stack, 0] idx
 * @param byte[stack,-1] r
 * @param byte[stack,-2] g
 * @param byte[stack,-3] b
 */
GS_PRIVATE GS_INLINE void op__setRoomPalette(gs_VmContext* ctx, byte idx, byte r, byte g, byte b)
{
	/* TODO */
}


/**
 * fadeRoom
 * @param word[stack, 0] effect
 */
GS_PRIVATE GS_INLINE void op__fadeRoom(gs_VmContext* ctx, int32 effect)
{
	/* TODO */
}


/**
 * darkenPalette
 * @param long[stack, 0] redScale
 * @param long[stack,-1] greenScale
 * @param long[stack,-2] blueScale
 * @param word[stack,-3] startColor
 * @param word[stack,-4] endColor
 */
GS_PRIVATE GS_INLINE void op__darkenPalette(gs_VmContext* ctx, int32 redScale, int32 greenScale, int32 blueScale, int32 startColor, int32 endColor)
{
	/* TODO */
}


/**
 * manipulatePalette
 * @param word[stack, 0] resourceNum
 * @param long[stack,-1] start
 * @param long[stack,-2] end
 * @param long[stack,-3] time
 */
GS_PRIVATE GS_INLINE void op__manipulatePalette(gs_VmContext* ctx, int32 resourceNum, int32 start, int32 end, int32 time)
{
	/* TODO */
}


/**
 * setPalette
 * @param word[stack, 0] palNum
 */
GS_PRIVATE GS_INLINE void op__setPalette(gs_VmContext* ctx, int32 palNum)
{
	/* TODO */
}


/**
 * roomSaveGame
 */
GS_PRIVATE GS_INLINE void op__roomSaveGame(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * roomLoadGame
 */
GS_PRIVATE GS_INLINE void op__roomLoadGame(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * desaturatePalette
 * @param long[stack, 0] hueScale
 * @param long[stack,-1] satScale
 * @param long[stack,-2] lightScale
 * @param word[stack,-3] startColor
 * @param word[stack,-4] endColor
 */
GS_PRIVATE GS_INLINE void op__desaturatePalette(gs_VmContext* ctx, int32 hueScale, int32 satScale, int32 lightScale, int32 startColor, int32 endColor)
{
	/* TODO */
}


/**
 * setActorCostume
 * @param word[stack, 0] costumeNum
 */
GS_PRIVATE GS_INLINE void op__setActorCostume(gs_VmContext* ctx, int32 costumeNum)
{
	/* TODO */
}


/**
 * setActorStepDistance
 * @param word[stack, 0] x
 * @param word[stack,-1] y
 */
GS_PRIVATE GS_INLINE void op__setActorStepDistance(gs_VmContext* ctx, int32 x, int32 y)
{
	/* TODO */
}


/**
 * setActorAnimationToDefault
 */
GS_PRIVATE GS_INLINE void op__setActorAnimationToDefault(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * setActorAnimationInitFrame
 * @param word[stack, 0] initFrame
 */
GS_PRIVATE GS_INLINE void op__setActorAnimationInitFrame(gs_VmContext* ctx, int32 initFrame)
{
	/* TODO */
}


/**
 * setActorAnimationTalkFrame
 * @param word[stack, 0] startFrame
 * @param word[stack,-1] endFrame
 */
GS_PRIVATE GS_INLINE void op__setActorAnimationTalkFrame(gs_VmContext* ctx, int32 startFrame, int32 endFrame)
{
	/* TODO */
}


/**
 * setActorAnimationWalkFrame
 * @param word[stack, 0] walkFrame
 */
GS_PRIVATE GS_INLINE void op__setActorAnimationWalkFrame(gs_VmContext* ctx, int32 walkFrame)
{
	/* TODO */
}


/**
 * setActorAnimationStandFrame
 * @param word[stack, 0] standFrame
 */
GS_PRIVATE GS_INLINE void op__setActorAnimationStandFrame(gs_VmContext* ctx, int32 standFrame)
{
	/* TODO */
}


/**
 * setActorAnimationSpeed
 * @param word[stack, 0] speed
 */
GS_PRIVATE GS_INLINE void op__setActorAnimationSpeed(gs_VmContext* ctx, int32 speed)
{
	/* TODO */
}


/**
 * newActor
 * @const mode = 0
 */
GS_PRIVATE GS_INLINE void op__newActor(gs_VmContext* ctx, int32 mode)
{
	/* TODO */
}


/**
 * setActorElevation
 * @param word[stack, 0] elevation
 */
GS_PRIVATE GS_INLINE void op__setActorElevation(gs_VmContext* ctx, int32 elevation)
{
	/* TODO */
}


/**
 * setActorPalette
 * @param word[stack, 0] idx
 * @param long[stack,-1] val
 */
GS_PRIVATE GS_INLINE void op__setActorPalette(gs_VmContext* ctx, int32 idx, int32 val)
{
	/* TODO */
}


/**
 * setActorTalkColor
 * @param word[stack, 0] idx
 */
GS_PRIVATE GS_INLINE void op__setActorTalkColor(gs_VmContext* ctx, int32 idx)
{
	/* TODO */
}


/**
 * setActorName
 */
GS_PRIVATE GS_INLINE void op__setActorName(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * setActorWidth
 * @param word[stack, 0] width
 */
GS_PRIVATE GS_INLINE void op__setActorWidth(gs_VmContext* ctx, int32 width)
{
	/* TODO */
}


/**
 * setActorScale
 * @param word[stack, 0] scale
 */
GS_PRIVATE GS_INLINE void op__setActorScale(gs_VmContext* ctx, int32 scale)
{
	/* TODO */
}


/**
 * setActorNeverZClip
 */
GS_PRIVATE GS_INLINE void op__setActorNeverZClip(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * setActorAlwaysZClip
 * @param word[stack, 0] forceClip
 */
GS_PRIVATE GS_INLINE void op__setActorAlwaysZClip(gs_VmContext* ctx, int32 forceClip)
{
	/* TODO */
}


/**
 * setActorFollowBoxes
 * @const follow = 0
 */
GS_PRIVATE GS_INLINE void op__setActorFollowBoxes(gs_VmContext* ctx, int32 follow)
{
	/* TODO */
}


/**
 * setActorFollowBoxes
 * @const follow = 1
 */
GS_PRIVATE GS_INLINE void op__setActorFollowBoxes(gs_VmContext* ctx, int32 follow)
{
	/* TODO */
}


/**
 * setActorShadowDraw
 * @param byte[stack, 0] enabled
 */
GS_PRIVATE GS_INLINE void op__setActorShadowDraw(gs_VmContext* ctx, byte enabled)
{
	/* TODO */
}


/**
 * setActorTextOffset
 * @param long[stack, 0] x
 * @param long[stack,-1] y
 */
GS_PRIVATE GS_INLINE void op__setActorTextOffset(gs_VmContext* ctx, int32 x, int32 y)
{
	/* TODO */
}


/**
 * initActor
 * @param word[stack, 0] actorNum
 */
GS_PRIVATE GS_INLINE void op__initActor(gs_VmContext* ctx, int32 actorNum)
{
	/* TODO */
}


/**
 * setActorVar
 * @param long[stack, 0] varNum
 * @param long[stack,-1] value
 */
GS_PRIVATE GS_INLINE void op__setActorVar(gs_VmContext* ctx, int32 varNum, int32 value)
{
	/* TODO */
}


/**
 * setActorFollowTurns
 * @const follow = 0
 */
GS_PRIVATE GS_INLINE void op__setActorFollowTurns(gs_VmContext* ctx, int32 follow)
{
	/* TODO */
}


/**
 * setActorFollowTurns
 * @const follow = 1
 */
GS_PRIVATE GS_INLINE void op__setActorFollowTurns(gs_VmContext* ctx, int32 follow)
{
	/* TODO */
}


/**
 * newActor
 * @const mode = 2
 */
GS_PRIVATE GS_INLINE void op__newActor(gs_VmContext* ctx, int32 mode)
{
	/* TODO */
}


/**
 * setActorZ
 * @param word[stack, 0] z
 */
GS_PRIVATE GS_INLINE void op__setActorZ(gs_VmContext* ctx, int32 z)
{
	/* TODO */
}


/**
 * stopActorMoving
 */
GS_PRIVATE GS_INLINE void op__stopActorMoving(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * 
 * @const force = 1
 */
GS_PRIVATE GS_INLINE void op__(gs_VmContext* ctx, int32 force)
{
	/* TODO */
}


/**
 * turnActor
 * @param word[stack, 0] direction
 * @const force = 0
 */
GS_PRIVATE GS_INLINE void op__turnActor(gs_VmContext* ctx, int32 direction, int32 force)
{
	/* TODO */
}


/**
 * setWalkScript
 * @param word[stack, 0] scriptNum
 */
GS_PRIVATE GS_INLINE void op__setWalkScript(gs_VmContext* ctx, int32 scriptNum)
{
	/* TODO */
}


/**
 * setTalkScript
 * @param word[stack, 0] scriptNum
 */
GS_PRIVATE GS_INLINE void op__setTalkScript(gs_VmContext* ctx, int32 scriptNum)
{
	/* TODO */
}


/**
 * setWalkPaused
 * @const paused = 1
 */
GS_PRIVATE GS_INLINE void op__setWalkPaused(gs_VmContext* ctx, int32 paused)
{
	/* TODO */
}


/**
 * setWalkPaused
 * @const paused = 0
 */
GS_PRIVATE GS_INLINE void op__setWalkPaused(gs_VmContext* ctx, int32 paused)
{
	/* TODO */
}


/**
 * setActorVolume
 * @param word[stack, 0] volume
 */
GS_PRIVATE GS_INLINE void op__setActorVolume(gs_VmContext* ctx, int32 volume)
{
	/* TODO */
}


/**
 * setActorFrequency
 * @param word[stack, 0] frequency
 */
GS_PRIVATE GS_INLINE void op__setActorFrequency(gs_VmContext* ctx, int32 frequency)
{
	/* TODO */
}


/**
 * setActorPan
 * @param word[stack, 0] pan
 */
GS_PRIVATE GS_INLINE void op__setActorPan(gs_VmContext* ctx, int32 pan)
{
	/* TODO */
}


/**
 * setCameraFrozen
 * @const frozen = 1
 */
GS_PRIVATE GS_INLINE void op__setCameraFrozen(gs_VmContext* ctx, int32 frozen)
{
	/* TODO */
}


/**
 * setCameraFrozen
 * @const frozen = 0
 */
GS_PRIVATE GS_INLINE void op__setCameraFrozen(gs_VmContext* ctx, int32 frozen)
{
	/* TODO */
}


/**
 * initVerb
 * @param word[stack, 0] verbNum
 */
GS_PRIVATE GS_INLINE void op__initVerb(gs_VmContext* ctx, int32 verbNum)
{
	/* TODO */
}


/**
 * newVerb
 */
GS_PRIVATE GS_INLINE void op__newVerb(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * deleteVerb
 */
GS_PRIVATE GS_INLINE void op__deleteVerb(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * setVerbName
 * @param string[2...] name
 * @param byte[stack, 0] showName
 */
GS_PRIVATE GS_INLINE void op__setVerbName(gs_VmContext* ctx, byte showName, char* name)
{
	/* TODO */
}


/**
 * setVerbAt
 * @param word[stack, 0] x
 * @param word[stack,-1] y
 */
GS_PRIVATE GS_INLINE void op__setVerbAt(gs_VmContext* ctx, int32 x, int32 y)
{
	/* TODO */
}


/**
 * setVerbEnabled
 * @const enabled = 1
 */
GS_PRIVATE GS_INLINE void op__setVerbEnabled(gs_VmContext* ctx, int32 enabled)
{
	/* TODO */
}


/**
 * setVerbEnabled
 * @const enabled = 0
 */
GS_PRIVATE GS_INLINE void op__setVerbEnabled(gs_VmContext* ctx, int32 enabled)
{
	/* TODO */
}


/**
 * setVerbColor
 * @param byte[stack, 0] idx
 */
GS_PRIVATE GS_INLINE void op__setVerbColor(gs_VmContext* ctx, byte idx)
{
	/* TODO */
}


/**
 * setVerbHiColor
 * @param byte[stack, 0] idx
 */
GS_PRIVATE GS_INLINE void op__setVerbHiColor(gs_VmContext* ctx, byte idx)
{
	/* TODO */
}


/**
 * setVerbDimColor
 * @param byte[stack, 0] idx
 */
GS_PRIVATE GS_INLINE void op__setVerbDimColor(gs_VmContext* ctx, byte idx)
{
	/* TODO */
}


/**
 * dimVerb
 */
GS_PRIVATE GS_INLINE void op__dimVerb(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * setVerbKey
 * @param word[stack, 0] keyNum
 */
GS_PRIVATE GS_INLINE void op__setVerbKey(gs_VmContext* ctx, int32 keyNum)
{
	/* TODO */
}


/**
 * setVerbImage
 * @param word[stack, 0] roomNum
 * @param word[stack,-1] objectNum
 */
GS_PRIVATE GS_INLINE void op__setVerbImage(gs_VmContext* ctx, int32 roomNum, int32 objectNum)
{
	/* TODO */
}


/**
 * setVerbText
 * @param long[stack, 0] textAddress
 */
GS_PRIVATE GS_INLINE void op__setVerbText(gs_VmContext* ctx, int32 textAddress)
{
	/* TODO */
}


/**
 * centerVerb
 */
GS_PRIVATE GS_INLINE void op__centerVerb(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * setVerbCharSet
 * @param word[stack, 0] charsetNum
 */
GS_PRIVATE GS_INLINE void op__setVerbCharSet(gs_VmContext* ctx, int32 charsetNum)
{
	/* TODO */
}


/**
 * setVerbLineSpacing
 * @param long[stack, 0] lineSpacing
 */
GS_PRIVATE GS_INLINE void op__setVerbLineSpacing(gs_VmContext* ctx, int32 lineSpacing)
{
	/* TODO */
}


/**
 * startSound
 * @param long[stack, 0] sound
 */
GS_PRIVATE GS_INLINE void op__startSound(gs_VmContext* ctx, int32 sound)
{
	/* TODO */
}


/**
 * startMusic
 * @param long[stack, 0] sound
 */
GS_PRIVATE GS_INLINE void op__startMusic(gs_VmContext* ctx, int32 sound)
{
	/* TODO */
}


/**
 * stopSound
 * @param long[stack, 0] sound
 */
GS_PRIVATE GS_INLINE void op__stopSound(gs_VmContext* ctx, int32 sound)
{
	/* TODO */
}


/**
 * soundKludge
 * @param args[stack, 0] args
 */
GS_PRIVATE GS_INLINE void op__soundKludge(gs_VmContext* ctx, int32* args)
{
	/* TODO */
}


/**
 * restartGame
 */
GS_PRIVATE GS_INLINE void op__restartGame(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * quitGame
 */
GS_PRIVATE GS_INLINE void op__quitGame(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * saveRestoreVerbs
 * @param long[stack, 0] a
 * @param long[stack,-1] b
 * @param long[stack,-2] c
 */
GS_PRIVATE GS_INLINE void op__saveRestoreVerbs(gs_VmContext* ctx, int32 a, int32 b, int32 c)
{
	/* TODO */
}


/**
 * setObjectName
 * @param string[1...] text
 * @param word[stack, 0] objectNum
 */
GS_PRIVATE GS_INLINE void op__setObjectName(gs_VmContext* ctx, int32 objectNum, char* text)
{
	/* TODO */
}


/**
 * getDateTime
 */
GS_PRIVATE GS_INLINE void op__getDateTime(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * drawBox
 * @param long[stack, 0] x
 * @param long[stack,-1] y
 * @param long[stack,-2] x2
 * @param long[stack,-3] y2
 * @param long[stack,-4] color
 */
GS_PRIVATE GS_INLINE void op__drawBox(gs_VmContext* ctx, int32 x, int32 y, int32 x2, int32 y2, int32 color)
{
	/* TODO */
}


/**
 * startVideo
 * @param string[1...] path
 */
GS_PRIVATE GS_INLINE void op__startVideo(gs_VmContext* ctx, char* path)
{
	/* TODO */
}


/**
 * kernelSetFunctions
 * @param args[stack, 0] args
 */
GS_PRIVATE GS_INLINE void op__kernelSetFunctions(gs_VmContext* ctx, int32* args)
{
	/* TODO */
}


/**
 * dim2DimArray
 * @param long[stack, 0] dim2
 * @param long[stack,-1] dim1
 */
GS_PRIVATE GS_INLINE void op__dim2DimArray(gs_VmContext* ctx, int32 dim2, int32 dim1)
{
	/* TODO */
}


/**
 * distObjectPt
 * @param long[stack, 0] a
 * @param long[stack,-1] b
 * @param long[stack,-2] c
 */
GS_PRIVATE GS_INLINE void op__distObjectPt(gs_VmContext* ctx, int32 a, int32 b, int32 c)
{
	/* TODO */
}


/**
 * startScriptQuick2
 * @param long[stack, 0] script
 * @param args[stack,-1] args
 */
GS_PRIVATE GS_INLINE void op__startScriptQuick2(gs_VmContext* ctx, int32 script, int32* args)
{
	/* TODO */
}


/**
 * startObjectQuick
 * @param long[stack, 0] script
 * @param byte[stack,-1] entryp
 * @param args[stack,-2] args
 */
GS_PRIVATE GS_INLINE void op__startObjectQuick(gs_VmContext* ctx, int32 script, byte entryp, int32* args)
{
	/* TODO */
}


/**
 * pickOneOf
 * @param long[stack, 0] i
 * @param args[stack,-1] args
 */
GS_PRIVATE GS_INLINE void op__pickOneOf(gs_VmContext* ctx, int32 i, int32* args)
{
	/* TODO */
}


/**
 * pickOneOfDefault
 * @param long[stack, 0] i
 * @param args[stack,-1] args
 * @param long[stack,-2] def
 */
GS_PRIVATE GS_INLINE void op__pickOneOfDefault(gs_VmContext* ctx, int32 i, int32* args, int32 def)
{
	/* TODO */
}


/**
 * isAnyOf
 * @param long[stack, 0] value
 * @param args[stack,-1] args
 */
GS_PRIVATE GS_INLINE void op__isAnyOf(gs_VmContext* ctx, int32 value, int32* args)
{
	/* TODO */
}


/**
 * getRandomNumber
 * @param long[stack, 0] max
 */
GS_PRIVATE GS_INLINE void op__getRandomNumber(gs_VmContext* ctx, int32 max)
{
	/* TODO */
}


/**
 * getRandomNumberRange
 * @param long[stack, 0] min
 * @param long[stack,-1] max
 */
GS_PRIVATE GS_INLINE void op__getRandomNumberRange(gs_VmContext* ctx, int32 min, int32 max)
{
	/* TODO */
}


/**
 * ifClassOfIs
 * @param long[stack, 0] obj
 * @param args[stack,-1] args
 */
GS_PRIVATE GS_INLINE void op__ifClassOfIs(gs_VmContext* ctx, int32 obj, int32* args)
{
	/* TODO */
}


/**
 * getState
 * @param long[stack, 0] obj
 */
GS_PRIVATE GS_INLINE void op__getState(gs_VmContext* ctx, int32 obj)
{
	/* TODO */
}


/**
 * getOwner
 * @param long[stack, 0] obj
 */
GS_PRIVATE GS_INLINE void op__getOwner(gs_VmContext* ctx, int32 obj)
{
	/* TODO */
}


/**
 * isScriptRunning
 * @param long[stack, 0] script
 */
GS_PRIVATE GS_INLINE void op__isScriptRunning(gs_VmContext* ctx, int32 script)
{
	/* TODO */
}


/**
 * shuffle
 * @param long[stack, 0] a
 * @param long[stack,-1] b
 */
GS_PRIVATE GS_INLINE void op__shuffle(gs_VmContext* ctx, int32 a, int32 b)
{
	/* TODO */
}


/**
 * isSoundRunning
 * @param long[stack, 0] sound
 */
GS_PRIVATE GS_INLINE void op__isSoundRunning(gs_VmContext* ctx, int32 sound)
{
	/* TODO */
}


/**
 * abs
 * @param long[stack, 0] value
 */
GS_PRIVATE GS_INLINE void op__abs(gs_VmContext* ctx, int32 value)
{
	/* TODO */
}


/**
 * kernelGetFunctions
 */
GS_PRIVATE GS_INLINE void op__kernelGetFunctions(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * isActorInBox
 * @param long[stack, 0] index
 * @param long[stack,-1] box
 */
GS_PRIVATE GS_INLINE void op__isActorInBox(gs_VmContext* ctx, int32 index, int32 box)
{
	/* TODO */
}


/**
 * getVerbEntrypoint
 * @param long[stack, 0] verb
 * @param long[stack,-1] entryp
 */
GS_PRIVATE GS_INLINE void op__getVerbEntrypoint(gs_VmContext* ctx, int32 verb, int32 entryp)
{
	/* TODO */
}


/**
 * getActorFromXY
 * @param long[stack, 0] x
 * @param long[stack,-1] y
 */
GS_PRIVATE GS_INLINE void op__getActorFromXY(gs_VmContext* ctx, int32 x, int32 y)
{
	/* TODO */
}


/**
 * findObject
 * @param long[stack, 0] x
 * @param long[stack,-1] y
 */
GS_PRIVATE GS_INLINE void op__findObject(gs_VmContext* ctx, int32 x, int32 y)
{
	/* TODO */
}


/**
 * getVerbFromXY
 * @param long[stack, 0] x
 * @param long[stack,-1] y
 */
GS_PRIVATE GS_INLINE void op__getVerbFromXY(gs_VmContext* ctx, int32 x, int32 y)
{
	/* TODO */
}


/**
 * findInventory
 * @param long[stack, 0] owner
 * @param long[stack,-1] index
 */
GS_PRIVATE GS_INLINE void op__findInventory(gs_VmContext* ctx, int32 owner, int32 index)
{
	/* TODO */
}


/**
 * getInventoryCount
 * @param long[stack, 0] owner
 */
GS_PRIVATE GS_INLINE void op__getInventoryCount(gs_VmContext* ctx, int32 owner)
{
	/* TODO */
}


/**
 * getAnimateVariable
 * @param long[stack, 0] index
 * @param long[stack,-1] variable
 */
GS_PRIVATE GS_INLINE void op__getAnimateVariable(gs_VmContext* ctx, int32 index, int32 variable)
{
	/* TODO */
}


/**
 * getActorRoom
 * @param long[stack, 0] index
 */
GS_PRIVATE GS_INLINE void op__getActorRoom(gs_VmContext* ctx, int32 index)
{
	/* TODO */
}


/**
 * getActorWalkBox
 * @param long[stack, 0] index
 */
GS_PRIVATE GS_INLINE void op__getActorWalkBox(gs_VmContext* ctx, int32 index)
{
	/* TODO */
}


/**
 * getActorMoving
 * @param long[stack, 0] index
 */
GS_PRIVATE GS_INLINE void op__getActorMoving(gs_VmContext* ctx, int32 index)
{
	/* TODO */
}


/**
 * getActorCostume
 * @param long[stack, 0] index
 */
GS_PRIVATE GS_INLINE void op__getActorCostume(gs_VmContext* ctx, int32 index)
{
	/* TODO */
}


/**
 * getActorScaleX
 * @param long[stack, 0] index
 */
GS_PRIVATE GS_INLINE void op__getActorScaleX(gs_VmContext* ctx, int32 index)
{
	/* TODO */
}


/**
 * getActorLayer
 * @param long[stack, 0] index
 */
GS_PRIVATE GS_INLINE void op__getActorLayer(gs_VmContext* ctx, int32 index)
{
	/* TODO */
}


/**
 * getActorElevation
 * @param long[stack, 0] index
 */
GS_PRIVATE GS_INLINE void op__getActorElevation(gs_VmContext* ctx, int32 index)
{
	/* TODO */
}


/**
 * getActorWidth
 * @param long[stack, 0] index
 */
GS_PRIVATE GS_INLINE void op__getActorWidth(gs_VmContext* ctx, int32 index)
{
	/* TODO */
}


/**
 * getObjectNewDir
 * @param long[stack, 0] index
 */
GS_PRIVATE GS_INLINE void op__getObjectNewDir(gs_VmContext* ctx, int32 index)
{
	/* TODO */
}


/**
 * getObjectX
 * @param long[stack, 0] index
 */
GS_PRIVATE GS_INLINE void op__getObjectX(gs_VmContext* ctx, int32 index)
{
	/* TODO */
}


/**
 * getObjectY
 * @param long[stack, 0] index
 */
GS_PRIVATE GS_INLINE void op__getObjectY(gs_VmContext* ctx, int32 index)
{
	/* TODO */
}


/**
 * getActorChore
 */
GS_PRIVATE GS_INLINE void op__getActorChore(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * distObjectObject
 * @param long[stack, 0] a
 * @param long[stack,-1] b
 */
GS_PRIVATE GS_INLINE void op__distObjectObject(gs_VmContext* ctx, int32 a, int32 b)
{
	/* TODO */
}


/**
 * distObjectPtPt
 * @param long[stack, 0] a
 * @param long[stack,-1] b
 * @param long[stack,-2] c
 * @param long[stack,-3] d
 */
GS_PRIVATE GS_INLINE void op__distObjectPtPt(gs_VmContext* ctx, int32 a, int32 b, int32 c, int32 d)
{
	/* TODO */
}


/**
 * getObjectImageX
 */
GS_PRIVATE GS_INLINE void op__getObjectImageX(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * getObjectImageY
 */
GS_PRIVATE GS_INLINE void op__getObjectImageY(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * getObjectImageWidth
 */
GS_PRIVATE GS_INLINE void op__getObjectImageWidth(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * getObjectImageHeight
 */
GS_PRIVATE GS_INLINE void op__getObjectImageHeight(gs_VmContext* ctx)
{
	/* TODO */
}


/**
 * getStringWidth
 * @param string[1...] text
 * @param word[stack, 0] charsetNum
 */
GS_PRIVATE GS_INLINE void op__getStringWidth(gs_VmContext* ctx, int32 charsetNum, char* text)
{
	/* TODO */
}


/**
 * getActorZPlane
 */
GS_PRIVATE GS_INLINE void op__getActorZPlane(gs_VmContext* ctx)
{
	/* TODO */
}



/** BEGIN **/
/* This section is automatically generated. */


GS_EXPORT gs_bool gs_RunOpcode(gs_VmContext* ctx)
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
			op__pushByte(ctx, value);
		}
		return TRUE;
		case 0x01:
		{

			/**
			 * pushWord
			 * @param word[1..4] value
			 */
			int32 value = READ_WORD_AS_LONG();
			op__pushWord(ctx, value);
		}
		return TRUE;
		case 0x02:
		{

			/**
			 * pushWordVar
			 * @param word[1..4] index
			 */
			int32 index = READ_WORD_AS_LONG();
			op__pushWordVar(ctx, index);
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
			op__wordArrayRead(ctx, arrayNum, base);
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
			op__wordArrayIndexedRead(ctx, arrayNum, index, base);
		}
		return TRUE;
		case 0x05:
		{

			/**
			 * dup
			 * @param long[stack, 0] value
			 */
			int32 value = PULL_LONG();
			op__dup(ctx, value);
		}
		return TRUE;
		case 0x06:
		{

			/**
			 * pop
			 * @param long[stack, 0] discard
			 */
			int32 discard = PULL_LONG();
			op__pop(ctx, discard);
		}
		return TRUE;
		case 0x07:
		{

			/**
			 * not
			 * @param long[stack, 0] value
			 */
			int32 value = PULL_LONG();
			op__not(ctx, value);
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
			op__eq(ctx, a, b);
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
			op__neq(ctx, a, b);
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
			op__gt(ctx, a, b);
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
			op__lt(ctx, a, b);
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
			op__le(ctx, a, b);
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
			op__ge(ctx, a, b);
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
			op__add(ctx, a, b);
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
			op__sub(ctx, a, b);
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
			op__mul(ctx, a, b);
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
			op__div(ctx, a, b);
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
			op__land(ctx, a, b);
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
			op__lor(ctx, a, b);
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
			op__band(ctx, a, b);
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
			op__bor(ctx, a, b);
		}
		return TRUE;
		case 0x16:
		{

			/**
			 * mod
			 * @param long[stack, 0] a
			 * @param long[stack,-1] b
			 */
			int32 b = PULL_LONG();
			int32 a = PULL_LONG();
			op__mod(ctx, a, b);
		}
		return TRUE;
		case 0x42:
		{

			/**
			 * writeByteVar
			 * @param long[stack, 0] value
			 */
			int32 value = PULL_LONG();
			op__writeByteVar(ctx, value);
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
			op__byteArrayWrite(ctx, base, value);
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
			op__byteArrayIndexedWrite(ctx, index, base, value);
		}
		return TRUE;
		case 0x4E:
		{

			/**
			 * byteVarInc
			 */
			op__byteVarInc(ctx);
		}
		return TRUE;
		case 0x52:
		{

			/**
			 * byteArrayInc
			 * @param long[stack, 0] base
			 */
			int32 base = PULL_LONG();
			op__byteArrayInc(ctx, base);
		}
		return TRUE;
		case 0x56:
		{

			/**
			 * byteVarDec
			 */
			op__byteVarDec(ctx);
		}
		return TRUE;
		case 0x5A:
		{

			/**
			 * byteArrayDec
			 * @param long[stack, 0] base
			 */
			int32 base = PULL_LONG();
			op__byteArrayDec(ctx, base);
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
			op__drawObject(ctx, obj, state);
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
			op__drawObjectAt(ctx, obj, x, y);
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
			op__drawBlastObject(ctx, a, b, c, d, e, args);
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
			op__if(ctx, condition, relOffset);
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
			op__ifNot(ctx, condition, relOffset);
		}
		return TRUE;
		case 0x66:
		{

			/**
			 * jump
			 * @param word[1..4] relOffset
			 */
			int32 relOffset = READ_WORD_AS_LONG();
			op__jump(ctx, relOffset);
		}
		return TRUE;
		case 0x67:
		{

			/**
			 * breakHere
			 */
			op__breakHere(ctx);
		}
		return TRUE;
		case 0x68:
		{

			/**
			 * delayFrames
			 */
			op__delayFrames(ctx);
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
					op__waitForActor(ctx, offset, actorNum);
				}
				return TRUE;
				case 0x1F:
				{

					/**
					 * waitForMessage
					 * @const offset = -2
					 */
					op__waitForMessage(ctx, -2);
				}
				return TRUE;
				case 0x20:
				{

					/**
					 * waitForCamera
					 * @const offset = -2
					 */
					op__waitForCamera(ctx, -2);
				}
				return TRUE;
				case 0x21:
				{

					/**
					 * waitForSentence
					 * @const offset = -2
					 */
					op__waitForSentence(ctx, -2);
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
					op__waitForAnimation(ctx, offset, actorNum);
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
					op__waitForTurn(ctx, offset, actorNum);
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
			op__delay(ctx, delay);
		}
		return TRUE;
		case 0x6B:
		{

			/**
			 * delaySeconds
			 * @param long[stack, 0] seconds
			 */
			int32 seconds = PULL_LONG();
			op__delaySeconds(ctx, seconds);
		}
		return TRUE;
		case 0x6C:
		{

			/**
			 * delayMinutes
			 * @param long[stack, 0] minutes
			 */
			int32 minutes = PULL_LONG();
			op__delayMinutes(ctx, minutes);
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
			op__writeWordVar(ctx, varIndex, value);
		}
		return TRUE;
		case 0x6E:
		{

			/**
			 * wordVarInc
			 * @param long[1..4] varIndex
			 */
			int32 varIndex = READ_LONG();
			op__wordVarInc(ctx, varIndex);
		}
		return TRUE;
		case 0x6F:
		{

			/**
			 * wordVarDec
			 * @param long[1..4] varIndex
			 */
			int32 varIndex = READ_LONG();
			op__wordVarDec(ctx, varIndex);
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
					op__newIntArray(ctx, arrayNum, dim1);
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
					op__newStringArray(ctx, arrayNum, dim1);
				}
				return TRUE;
				case 0x0C:
				{

					/**
					 * deleteArray
					 * @param word[2..5] arrayNum
					 */
					int32 arrayNum = READ_WORD_AS_LONG();
					op__deleteArray(ctx, arrayNum);
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
			op__wordArrayWrite(ctx, arrayNum, base, value);
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
			op__wordArrayInc(ctx, arrayNum, base);
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
			op__wordArrayDec(ctx, arrayNum, base);
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
					op__newIntArray2(ctx, arrayNum, dim1, dim2);
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
					op__newStringArray2(ctx, arrayNum, dim1, dim2);
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
					op__deleteARray2(ctx, arrayNum, dim1, dim2);
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
			op__wordArrayIndexedWrite(ctx, arrayNum, index, base, value);
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
					op__copyStringArray(ctx, arrayNum, data, b);
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
					op__copyIntArray(ctx, arrayNum, args, b);
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
					op__copyDim2Array(ctx, arrayNum, args, b);
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
			op__startScript(ctx, flags, script, args);
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
			op__startScriptQuick(ctx, script, args);
		}
		return TRUE;
		case 0x7B:
		{

			/**
			 * stopObjectCode6
			 */
			op__stopObjectCode6(ctx);
		}
		return TRUE;
		case 0x7C:
		{

			/**
			 * stopScript6
			 * @param long[stack, 0] script
			 */
			int32 script = PULL_LONG();
			op__stopScript6(ctx, script);
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
			op__jumpToScript(ctx, flags, script, args);
		}
		return TRUE;
		case 0x7E:
		{

			/**
			 * dummy
			 */
			op__dummy(ctx);
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
			op__startObject(ctx, flags, script, entryp, args);
		}
		return TRUE;
		case 0x80:
		{

			/**
			 * stopObjectScript
			 * @param word[stack, 0] script
			 */
			int16 script = PULL_WORD();
			op__stopObjectScript(ctx, script);
		}
		return TRUE;
		case 0x81:
		{

			/**
			 * cutscene
			 * @param args[stack, 0] args
			 */
			int* args = PULL_ARGS();
			op__cutscene(ctx, args);
		}
		return TRUE;
		case 0x82:
		{

			/**
			 * endCutscene
			 */
			op__endCutscene(ctx);
		}
		return TRUE;
		case 0x83:
		{

			/**
			 * freezeUnfreeze
			 * @param long[stack, 0] scriptNum
			 */
			int32 scriptNum = PULL_LONG();
			op__freezeUnfreeze(ctx, scriptNum);
		}
		return TRUE;
		case 0x84:
		{

			/**
			 * beginOverride
			 */
			op__beginOverride(ctx);
		}
		return TRUE;
		case 0x85:
		{

			/**
			 * endOverride
			 */
			op__endOverride(ctx);
		}
		return TRUE;
		case 0x86:
		{

			/**
			 * stopSentence
			 */
			op__stopSentence(ctx);
		}
		return TRUE;
		case 0x87:
		{

			/**
			 * unknown_87
			 */
			op__unknown_87(ctx);
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
			op__setClass(ctx, obj, args);
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
			op__setState(ctx, obj, state);
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
			op__setOwner(ctx, obj, owner);
		}
		return TRUE;
		case 0x8C:
		{

			/**
			 * panCameraTo
			 */
			op__panCameraTo(ctx);
		}
		return TRUE;
		case 0x8D:
		{

			/**
			 * actorFollowCamera
			 * @param long[stack, 0] index
			 */
			int32 index = PULL_LONG();
			op__actorFollowCamera(ctx, index);
		}
		return TRUE;
		case 0x8E:
		{

			/**
			 * setCameraAt
			 */
			op__setCameraAt(ctx);
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
					op__printActor_ResetState(ctx, 0, 1);
				}
				return TRUE;
				case 0xC9:
				{

					/**
					 * printActor_SaveState
					 * @const target = 0
					 * @const pullActor = 1
					 */
					op__printActor_SaveState(ctx, 0, 1);
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
					op__printActor_SetPos(ctx, x, y, 0, 1);
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
					op__printActor_SetColor(ctx, index, 0, 1);
				}
				return TRUE;
				case 0xCC:
				{

					/**
					 * printActor_AlignCenter
					 * @const target = 0
					 * @const pullActor = 1
					 */
					op__printActor_AlignCenter(ctx, 0, 1);
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
					op__printActor_SetCharSet(ctx, charsetNum, 0, 1);
				}
				return TRUE;
				case 0xCE:
				{

					/**
					 * printActor_AlignLeft
					 * @const target = 0
					 * @const pullActor = 1
					 */
					op__printActor_AlignLeft(ctx, 0, 1);
				}
				return TRUE;
				case 0xCF:
				{

					/**
					 * printActor_SetOverhead
					 * @const target = 0
					 * @const pullActor = 1
					 */
					op__printActor_SetOverhead(ctx, 0, 1);
				}
				return TRUE;
				case 0xD0:
				{

					/**
					 * printActor_SetMumble
					 * @const target = 0
					 * @const pullActor = 1
					 */
					op__printActor_SetMumble(ctx, 0, 1);
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
					op__printActor(ctx, text, 0, 1);
				}
				return TRUE;
				case 0xD2:
				{

					/**
					 * printActor_SetWrapped
					 * @const target = 0
					 * @const pullActor = 1
					 */
					op__printActor_SetWrapped(ctx, 0, 1);
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
					op__printEgo_ResetState(ctx, 0, 2);
				}
				return TRUE;
				case 0xC9:
				{

					/**
					 * printEgo_SaveState
					 * @const target = 0
					 * @const pullActor = 2
					 */
					op__printEgo_SaveState(ctx, 0, 2);
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
					op__printEgo_SetPos(ctx, x, y, 0, 2);
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
					op__printEgo_SetColor(ctx, index, 0, 2);
				}
				return TRUE;
				case 0xCC:
				{

					/**
					 * printEgo_AlignCenter
					 * @const target = 0
					 * @const pullActor = 2
					 */
					op__printEgo_AlignCenter(ctx, 0, 2);
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
					op__printEgo_SetCharSet(ctx, charsetNum, 0, 2);
				}
				return TRUE;
				case 0xCE:
				{

					/**
					 * printEgo_AlignLeft
					 * @const target = 0
					 * @const pullActor = 2
					 */
					op__printEgo_AlignLeft(ctx, 0, 2);
				}
				return TRUE;
				case 0xCF:
				{

					/**
					 * printEgo_SetOverhead
					 * @const target = 0
					 * @const pullActor = 2
					 */
					op__printEgo_SetOverhead(ctx, 0, 2);
				}
				return TRUE;
				case 0xD0:
				{

					/**
					 * printEgo_SetMumble
					 * @const target = 0
					 * @const pullActor = 2
					 */
					op__printEgo_SetMumble(ctx, 0, 2);
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
					op__printEgo(ctx, text, 0, 2);
				}
				return TRUE;
				case 0xD2:
				{

					/**
					 * printEgo_SetWrapped
					 * @const target = 0
					 * @const pullActor = 2
					 */
					op__printEgo_SetWrapped(ctx, 0, 2);
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
			op__talkActor(ctx, actorNum, text);
		}
		return TRUE;
		case 0x92:
		{

			/**
			 * talkEgo
			 * @param string[1...] text
			 */
			byte* text = READ_STRING();
			op__talkEgo(ctx, text);
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
					op__printLine_ResetState(ctx, 0, 0);
				}
				return TRUE;
				case 0xC9:
				{

					/**
					 * printLine_SaveState
					 * @const target = 0
					 * @const pullActor = 0
					 */
					op__printLine_SaveState(ctx, 0, 0);
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
					op__printLine_SetPos(ctx, x, y, 0, 0);
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
					op__printLine_SetColor(ctx, index, 0, 0);
				}
				return TRUE;
				case 0xCC:
				{

					/**
					 * printLine_AlignCenter
					 * @const target = 0
					 * @const pullActor = 0
					 */
					op__printLine_AlignCenter(ctx, 0, 0);
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
					op__printLine_SetCharSet(ctx, charsetNum, 0, 0);
				}
				return TRUE;
				case 0xCE:
				{

					/**
					 * printLine_AlignLeft
					 * @const target = 0
					 * @const pullActor = 0
					 */
					op__printLine_AlignLeft(ctx, 0, 0);
				}
				return TRUE;
				case 0xCF:
				{

					/**
					 * printLine_SetOverhead
					 * @const target = 0
					 * @const pullActor = 0
					 */
					op__printLine_SetOverhead(ctx, 0, 0);
				}
				return TRUE;
				case 0xD0:
				{

					/**
					 * printLine_SetMumble
					 * @const target = 0
					 * @const pullActor = 0
					 */
					op__printLine_SetMumble(ctx, 0, 0);
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
					op__printLine(ctx, text, 0, 0);
				}
				return TRUE;
				case 0xD2:
				{

					/**
					 * printLine_SetWrapped
					 * @const target = 0
					 * @const pullActor = 0
					 */
					op__printLine_SetWrapped(ctx, 0, 0);
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
					op__printText_ResetState(ctx, 1, 0);
				}
				return TRUE;
				case 0xC9:
				{

					/**
					 * printText_SaveState
					 * @const target = 1
					 * @const pullActor = 0
					 */
					op__printText_SaveState(ctx, 1, 0);
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
					op__printText_SetPos(ctx, x, y, 1, 0);
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
					op__printText_SetColor(ctx, index, 1, 0);
				}
				return TRUE;
				case 0xCC:
				{

					/**
					 * printText_AlignCenter
					 * @const target = 1
					 * @const pullActor = 0
					 */
					op__printText_AlignCenter(ctx, 1, 0);
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
					op__printText_SetCharSet(ctx, charsetNum, 1, 0);
				}
				return TRUE;
				case 0xCE:
				{

					/**
					 * printText_AlignLeft
					 * @const target = 1
					 * @const pullActor = 0
					 */
					op__printText_AlignLeft(ctx, 1, 0);
				}
				return TRUE;
				case 0xCF:
				{

					/**
					 * printText_SetOverhead
					 * @const target = 1
					 * @const pullActor = 0
					 */
					op__printText_SetOverhead(ctx, 1, 0);
				}
				return TRUE;
				case 0xD0:
				{

					/**
					 * printText_SetMumble
					 * @const target = 1
					 * @const pullActor = 0
					 */
					op__printText_SetMumble(ctx, 1, 0);
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
					op__printText(ctx, text, 1, 0);
				}
				return TRUE;
				case 0xD2:
				{

					/**
					 * printText_SetWrapped
					 * @const target = 1
					 * @const pullActor = 0
					 */
					op__printText_SetWrapped(ctx, 1, 0);
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
					op__printDebug_ResetState(ctx, 2, 0);
				}
				return TRUE;
				case 0xC9:
				{

					/**
					 * printDebug_SaveState
					 * @const target = 2
					 * @const pullActor = 0
					 */
					op__printDebug_SaveState(ctx, 2, 0);
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
					op__printDebug_SetPos(ctx, x, y, 2, 0);
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
					op__printDebug_SetColor(ctx, index, 2, 0);
				}
				return TRUE;
				case 0xCC:
				{

					/**
					 * printDebug_AlignCenter
					 * @const target = 2
					 * @const pullActor = 0
					 */
					op__printDebug_AlignCenter(ctx, 2, 0);
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
					op__printDebug_SetCharSet(ctx, charsetNum, 2, 0);
				}
				return TRUE;
				case 0xCE:
				{

					/**
					 * printDebug_AlignLeft
					 * @const target = 2
					 * @const pullActor = 0
					 */
					op__printDebug_AlignLeft(ctx, 2, 0);
				}
				return TRUE;
				case 0xCF:
				{

					/**
					 * printDebug_SetOverhead
					 * @const target = 2
					 * @const pullActor = 0
					 */
					op__printDebug_SetOverhead(ctx, 2, 0);
				}
				return TRUE;
				case 0xD0:
				{

					/**
					 * printDebug_SetMumble
					 * @const target = 2
					 * @const pullActor = 0
					 */
					op__printDebug_SetMumble(ctx, 2, 0);
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
					op__printDebug(ctx, text, 2, 0);
				}
				return TRUE;
				case 0xD2:
				{

					/**
					 * printDebug_SetWrapped
					 * @const target = 2
					 * @const pullActor = 0
					 */
					op__printDebug_SetWrapped(ctx, 2, 0);
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
					op__printSystem_ResetState(ctx, 3, 0);
				}
				return TRUE;
				case 0xC9:
				{

					/**
					 * printSystem_SaveState
					 * @const target = 3
					 * @const pullActor = 0
					 */
					op__printSystem_SaveState(ctx, 3, 0);
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
					op__printSystem_SetPos(ctx, x, y, 3, 0);
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
					op__printSystem_SetColor(ctx, index, 3, 0);
				}
				return TRUE;
				case 0xCC:
				{

					/**
					 * printSystem_AlignCenter
					 * @const target = 3
					 * @const pullActor = 0
					 */
					op__printSystem_AlignCenter(ctx, 3, 0);
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
					op__printSystem_SetCharSet(ctx, charsetNum, 3, 0);
				}
				return TRUE;
				case 0xCE:
				{

					/**
					 * printSystem_AlignLeft
					 * @const target = 3
					 * @const pullActor = 0
					 */
					op__printSystem_AlignLeft(ctx, 3, 0);
				}
				return TRUE;
				case 0xCF:
				{

					/**
					 * printSystem_SetOverhead
					 * @const target = 3
					 * @const pullActor = 0
					 */
					op__printSystem_SetOverhead(ctx, 3, 0);
				}
				return TRUE;
				case 0xD0:
				{

					/**
					 * printSystem_SetMumble
					 * @const target = 3
					 * @const pullActor = 0
					 */
					op__printSystem_SetMumble(ctx, 3, 0);
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
					op__printSystem(ctx, text, 3, 0);
				}
				return TRUE;
				case 0xD2:
				{

					/**
					 * printSystem_SetWrapped
					 * @const target = 3
					 * @const pullActor = 0
					 */
					op__printSystem_SetWrapped(ctx, 3, 0);
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
					op__blastText_ResetState(ctx, 4, 0);
				}
				return TRUE;
				case 0xC9:
				{

					/**
					 * blastText_SaveState
					 * @const target = 4
					 * @const pullActor = 0
					 */
					op__blastText_SaveState(ctx, 4, 0);
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
					op__blastText_SetPos(ctx, x, y, 4, 0);
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
					op__blastText_SetColor(ctx, index, 4, 0);
				}
				return TRUE;
				case 0xCC:
				{

					/**
					 * blastText_AlignCenter
					 * @const target = 4
					 * @const pullActor = 0
					 */
					op__blastText_AlignCenter(ctx, 4, 0);
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
					op__blastText_SetCharSet(ctx, charsetNum, 4, 0);
				}
				return TRUE;
				case 0xCE:
				{

					/**
					 * blastText_AlignLeft
					 * @const target = 4
					 * @const pullActor = 0
					 */
					op__blastText_AlignLeft(ctx, 4, 0);
				}
				return TRUE;
				case 0xCF:
				{

					/**
					 * blastText_SetOverhead
					 * @const target = 4
					 * @const pullActor = 0
					 */
					op__blastText_SetOverhead(ctx, 4, 0);
				}
				return TRUE;
				case 0xD0:
				{

					/**
					 * blastText_SetMumble
					 * @const target = 4
					 * @const pullActor = 0
					 */
					op__blastText_SetMumble(ctx, 4, 0);
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
					op__blastText(ctx, text, 4, 0);
				}
				return TRUE;
				case 0xD2:
				{

					/**
					 * blastText_SetWrapped
					 * @const target = 4
					 * @const pullActor = 0
					 */
					op__blastText_SetWrapped(ctx, 4, 0);
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
			op__drawObject(ctx, obj, x, y, state);
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
					op__cursorSetOn(ctx);
				}
				return TRUE;
				case 0xDD:
				{

					/**
					 * cursorSetOff
					 */
					op__cursorSetOff(ctx);
				}
				return TRUE;
				case 0xDE:
				{

					/**
					 * cursorSetSoftOn
					 */
					op__cursorSetSoftOn(ctx);
				}
				return TRUE;
				case 0xDF:
				{

					/**
					 * cursorSetSoftOff
					 */
					op__cursorSetSoftOff(ctx);
				}
				return TRUE;
				case 0xE0:
				{

					/**
					 * cursorSetUserPutOn
					 */
					op__cursorSetUserPutOn(ctx);
				}
				return TRUE;
				case 0xE1:
				{

					/**
					 * cursorSetUserPutOff
					 */
					op__cursorSetUserPutOff(ctx);
				}
				return TRUE;
				case 0xE2:
				{

					/**
					 * cursorSetUserPutSoftOn
					 */
					op__cursorSetUserPutSoftOn(ctx);
				}
				return TRUE;
				case 0xE3:
				{

					/**
					 * cursorSetUserPutSoftOff
					 */
					op__cursorSetUserPutSoftOff(ctx);
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
					op__cursorSetImage(ctx, objNum, index);
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
					op__cursorSetHotSpot(ctx, x, y);
				}
				return TRUE;
				case 0xE6:
				{

					/**
					 * cursorSetTransparent
					 * @param long[stack, 0] isTransparent
					 */
					int32 isTransparent = PULL_LONG();
					op__cursorSetTransparent(ctx, isTransparent);
				}
				return TRUE;
				case 0xE7:
				{

					/**
					 * cursorSetCharSet
					 * @param word[stack, 0] charsetNum
					 */
					int16 charsetNum = PULL_WORD();
					op__cursorSetCharSet(ctx, charsetNum);
				}
				return TRUE;
				case 0xE8:
				{

					/**
					 * cursorSetCharSetColour
					 * @param args[stack, 0] args
					 */
					int* args = PULL_ARGS();
					op__cursorSetCharSetColour(ctx, args);
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
					op__cursorSetPos(ctx, x, y);
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
			op__loadRoom(ctx, room);
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
			op__loadRoomWithEgo(ctx, x, y);
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
			op__walkActorToObj(ctx, index, obj, dist);
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
			op__walkActorTo(ctx, index, x, y);
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
			op__putActorAtXY(ctx, actorIndex, x, y, room);
		}
		return TRUE;
		case 0xA2:
		{

			/**
			 * putActorAtObject
			 */
			op__putActorAtObject(ctx);
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
			op__faceActor(ctx, index, obj);
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
			op__animateActor(ctx, index, anim);
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
			op__doSentence8(ctx, verb, objectA, objectB);
		}
		return TRUE;
		case 0xA6:
		{

			/**
			 * pickupObject
			 */
			op__pickupObject(ctx);
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
			op__setBoxFlags(ctx, args, value);
		}
		return TRUE;
		case 0xA8:
		{

			/**
			 * createBoxMatrix
			 */
			op__createBoxMatrix(ctx);
		}
		return TRUE;
		case 0xA9:
		{

			/**
			 * wait
			 */
			op__wait(ctx);
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
					op__loadCostume(ctx, costumeNum);
				}
				return TRUE;
				case 0x3E:
				{

					/**
					 * loadObject
					 * @param word[stack, 0] objectNum
					 */
					int16 objectNum = PULL_WORD();
					op__loadObject(ctx, objectNum);
				}
				return TRUE;
				case 0x3F:
				{

					/**
					 * loadRoom
					 * @param word[stack, 0] roomNum
					 */
					int16 roomNum = PULL_WORD();
					op__loadRoom(ctx, roomNum);
				}
				return TRUE;
				case 0x40:
				{

					/**
					 * loadScript
					 * @param word[stack, 0] scriptNum
					 */
					int16 scriptNum = PULL_WORD();
					op__loadScript(ctx, scriptNum);
				}
				return TRUE;
				case 0x41:
				{

					/**
					 * loadSound
					 * @param word[stack, 0] soundNum
					 */
					int16 soundNum = PULL_WORD();
					op__loadSound(ctx, soundNum);
				}
				return TRUE;
				case 0x42:
				{

					/**
					 * lockCostume
					 * @param word[stack, 0] costumeNum
					 */
					int16 costumeNum = PULL_WORD();
					op__lockCostume(ctx, costumeNum);
				}
				return TRUE;
				case 0x43:
				{

					/**
					 * lockRoom
					 * @param word[stack, 0] roomNum
					 */
					int16 roomNum = PULL_WORD();
					op__lockRoom(ctx, roomNum);
				}
				return TRUE;
				case 0x44:
				{

					/**
					 * lockScript
					 * @param word[stack, 0] scriptNum
					 */
					int16 scriptNum = PULL_WORD();
					op__lockScript(ctx, scriptNum);
				}
				return TRUE;
				case 0x45:
				{

					/**
					 * lockSound
					 * @param word[stack, 0] soundNum
					 */
					int16 soundNum = PULL_WORD();
					op__lockSound(ctx, soundNum);
				}
				return TRUE;
				case 0x46:
				{

					/**
					 * unlockCostume
					 * @param word[stack, 0] costumeNum
					 */
					int16 costumeNum = PULL_WORD();
					op__unlockCostume(ctx, costumeNum);
				}
				return TRUE;
				case 0x47:
				{

					/**
					 * unlockRoom
					 * @param word[stack, 0] roomNum
					 */
					int16 roomNum = PULL_WORD();
					op__unlockRoom(ctx, roomNum);
				}
				return TRUE;
				case 0x48:
				{

					/**
					 * unlockScript
					 * @param word[stack, 0] scriptNum
					 */
					int16 scriptNum = PULL_WORD();
					op__unlockScript(ctx, scriptNum);
				}
				return TRUE;
				case 0x49:
				{

					/**
					 * unlockSound
					 * @param word[stack, 0] soundNum
					 */
					int16 soundNum = PULL_WORD();
					op__unlockSound(ctx, soundNum);
				}
				return TRUE;
				case 0x4A:
				{

					/**
					 * deleteCostume
					 * @param word[stack, 0] costumeNum
					 */
					int16 costumeNum = PULL_WORD();
					op__deleteCostume(ctx, costumeNum);
				}
				return TRUE;
				case 0x4B:
				{

					/**
					 * deleteRoom
					 * @param word[stack, 0] roomNum
					 */
					int16 roomNum = PULL_WORD();
					op__deleteRoom(ctx, roomNum);
				}
				return TRUE;
				case 0x4C:
				{

					/**
					 * deleteScript
					 * @param word[stack, 0] scriptNum
					 */
					int16 scriptNum = PULL_WORD();
					op__deleteScript(ctx, scriptNum);
				}
				return TRUE;
				case 0x4D:
				{

					/**
					 * deleteSound
					 * @param word[stack, 0] soundNum
					 */
					int16 soundNum = PULL_WORD();
					op__deleteSound(ctx, soundNum);
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
					op__setRoomPalette(ctx, idx, r, g, b);
				}
				return TRUE;
				case 0x57:
				{

					/**
					 * fadeRoom
					 * @param word[stack, 0] effect
					 */
					int16 effect = PULL_WORD();
					op__fadeRoom(ctx, effect);
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
					op__darkenPalette(ctx, redScale, greenScale, blueScale, startColor, endColor);
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
					op__manipulatePalette(ctx, resourceNum, start, end, time);
				}
				return TRUE;
				case 0x5C:
				{

					/**
					 * setPalette
					 * @param word[stack, 0] palNum
					 */
					int16 palNum = PULL_WORD();
					op__setPalette(ctx, palNum);
				}
				return TRUE;
				case 0x5D:
				{

					/**
					 * roomSaveGame
					 */
					op__roomSaveGame(ctx);
				}
				return TRUE;
				case 0x5E:
				{

					/**
					 * roomLoadGame
					 */
					op__roomLoadGame(ctx);
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
					op__desaturatePalette(ctx, hueScale, satScale, lightScale, startColor, endColor);
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
					op__setActorCostume(ctx, costumeNum);
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
					op__setActorStepDistance(ctx, x, y);
				}
				return TRUE;
				case 0x67:
				{

					/**
					 * setActorAnimationToDefault
					 */
					op__setActorAnimationToDefault(ctx);
				}
				return TRUE;
				case 0x68:
				{

					/**
					 * setActorAnimationInitFrame
					 * @param word[stack, 0] initFrame
					 */
					int16 initFrame = PULL_WORD();
					op__setActorAnimationInitFrame(ctx, initFrame);
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
					op__setActorAnimationTalkFrame(ctx, startFrame, endFrame);
				}
				return TRUE;
				case 0x6A:
				{

					/**
					 * setActorAnimationWalkFrame
					 * @param word[stack, 0] walkFrame
					 */
					int16 walkFrame = PULL_WORD();
					op__setActorAnimationWalkFrame(ctx, walkFrame);
				}
				return TRUE;
				case 0x6B:
				{

					/**
					 * setActorAnimationStandFrame
					 * @param word[stack, 0] standFrame
					 */
					int16 standFrame = PULL_WORD();
					op__setActorAnimationStandFrame(ctx, standFrame);
				}
				return TRUE;
				case 0x6C:
				{

					/**
					 * setActorAnimationSpeed
					 * @param word[stack, 0] speed
					 */
					int16 speed = PULL_WORD();
					op__setActorAnimationSpeed(ctx, speed);
				}
				return TRUE;
				case 0x6D:
				{

					/**
					 * newActor
					 * @const mode = 0
					 */
					op__newActor(ctx, 0);
				}
				return TRUE;
				case 0x6E:
				{

					/**
					 * setActorElevation
					 * @param word[stack, 0] elevation
					 */
					int16 elevation = PULL_WORD();
					op__setActorElevation(ctx, elevation);
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
					op__setActorPalette(ctx, idx, val);
				}
				return TRUE;
				case 0x70:
				{

					/**
					 * setActorTalkColor
					 * @param word[stack, 0] idx
					 */
					int16 idx = PULL_WORD();
					op__setActorTalkColor(ctx, idx);
				}
				return TRUE;
				case 0x71:
				{

					/**
					 * setActorName
					 */
					op__setActorName(ctx);
				}
				return TRUE;
				case 0x72:
				{

					/**
					 * setActorWidth
					 * @param word[stack, 0] width
					 */
					int16 width = PULL_WORD();
					op__setActorWidth(ctx, width);
				}
				return TRUE;
				case 0x73:
				{

					/**
					 * setActorScale
					 * @param word[stack, 0] scale
					 */
					int16 scale = PULL_WORD();
					op__setActorScale(ctx, scale);
				}
				return TRUE;
				case 0x74:
				{

					/**
					 * setActorNeverZClip
					 */
					op__setActorNeverZClip(ctx);
				}
				return TRUE;
				case 0x75:
				{

					/**
					 * setActorAlwaysZClip
					 * @param word[stack, 0] forceClip
					 */
					int16 forceClip = PULL_WORD();
					op__setActorAlwaysZClip(ctx, forceClip);
				}
				return TRUE;
				case 0x76:
				{

					/**
					 * setActorFollowBoxes
					 * @const follow = 0
					 */
					op__setActorFollowBoxes(ctx, 0);
				}
				return TRUE;
				case 0x77:
				{

					/**
					 * setActorFollowBoxes
					 * @const follow = 1
					 */
					op__setActorFollowBoxes(ctx, 1);
				}
				return TRUE;
				case 0x78:
				{

					/**
					 * setActorShadowDraw
					 * @param byte[stack, 0] enabled
					 */
					byte enabled = PULL_BYTE();
					op__setActorShadowDraw(ctx, enabled);
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
					op__setActorTextOffset(ctx, x, y);
				}
				return TRUE;
				case 0x7A:
				{

					/**
					 * initActor
					 * @param word[stack, 0] actorNum
					 */
					int16 actorNum = PULL_WORD();
					op__initActor(ctx, actorNum);
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
					op__setActorVar(ctx, varNum, value);
				}
				return TRUE;
				case 0x7C:
				{

					/**
					 * setActorFollowTurns
					 * @const follow = 0
					 */
					op__setActorFollowTurns(ctx, 0);
				}
				return TRUE;
				case 0x7D:
				{

					/**
					 * setActorFollowTurns
					 * @const follow = 1
					 */
					op__setActorFollowTurns(ctx, 1);
				}
				return TRUE;
				case 0x7E:
				{

					/**
					 * newActor
					 * @const mode = 2
					 */
					op__newActor(ctx, 2);
				}
				return TRUE;
				case 0x7F:
				{

					/**
					 * setActorZ
					 * @param word[stack, 0] z
					 */
					int16 z = PULL_WORD();
					op__setActorZ(ctx, z);
				}
				return TRUE;
				case 0x80:
				{

					/**
					 * stopActorMoving
					 */
					op__stopActorMoving(ctx);
				}
				return TRUE;
				case 0x81:
				{

					/**
					 * 
					 * @const force = 1
					 */
					op__(ctx, 1);
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
					op__turnActor(ctx, direction, 0);
				}
				return TRUE;
				case 0x83:
				{

					/**
					 * setWalkScript
					 * @param word[stack, 0] scriptNum
					 */
					int16 scriptNum = PULL_WORD();
					op__setWalkScript(ctx, scriptNum);
				}
				return TRUE;
				case 0x84:
				{

					/**
					 * setTalkScript
					 * @param word[stack, 0] scriptNum
					 */
					int16 scriptNum = PULL_WORD();
					op__setTalkScript(ctx, scriptNum);
				}
				return TRUE;
				case 0x85:
				{

					/**
					 * setWalkPaused
					 * @const paused = 1
					 */
					op__setWalkPaused(ctx, 1);
				}
				return TRUE;
				case 0x86:
				{

					/**
					 * setWalkPaused
					 * @const paused = 0
					 */
					op__setWalkPaused(ctx, 0);
				}
				return TRUE;
				case 0x87:
				{

					/**
					 * setActorVolume
					 * @param word[stack, 0] volume
					 */
					int16 volume = PULL_WORD();
					op__setActorVolume(ctx, volume);
				}
				return TRUE;
				case 0x88:
				{

					/**
					 * setActorFrequency
					 * @param word[stack, 0] frequency
					 */
					int16 frequency = PULL_WORD();
					op__setActorFrequency(ctx, frequency);
				}
				return TRUE;
				case 0x89:
				{

					/**
					 * setActorPan
					 * @param word[stack, 0] pan
					 */
					int16 pan = PULL_WORD();
					op__setActorPan(ctx, pan);
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
					op__setCameraFrozen(ctx, 1);
				}
				return TRUE;
				case 0x33:
				{

					/**
					 * setCameraFrozen
					 * @const frozen = 0
					 */
					op__setCameraFrozen(ctx, 0);
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
					op__initVerb(ctx, verbNum);
				}
				return TRUE;
				case 0x97:
				{

					/**
					 * newVerb
					 */
					op__newVerb(ctx);
				}
				return TRUE;
				case 0x98:
				{

					/**
					 * deleteVerb
					 */
					op__deleteVerb(ctx);
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
					op__setVerbName(ctx, showName, name);
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
					op__setVerbAt(ctx, x, y);
				}
				return TRUE;
				case 0x9B:
				{

					/**
					 * setVerbEnabled
					 * @const enabled = 1
					 */
					op__setVerbEnabled(ctx, 1);
				}
				return TRUE;
				case 0x9C:
				{

					/**
					 * setVerbEnabled
					 * @const enabled = 0
					 */
					op__setVerbEnabled(ctx, 0);
				}
				return TRUE;
				case 0x9D:
				{

					/**
					 * setVerbColor
					 * @param byte[stack, 0] idx
					 */
					byte idx = PULL_BYTE();
					op__setVerbColor(ctx, idx);
				}
				return TRUE;
				case 0x9E:
				{

					/**
					 * setVerbHiColor
					 * @param byte[stack, 0] idx
					 */
					byte idx = PULL_BYTE();
					op__setVerbHiColor(ctx, idx);
				}
				return TRUE;
				case 0xA0:
				{

					/**
					 * setVerbDimColor
					 * @param byte[stack, 0] idx
					 */
					byte idx = PULL_BYTE();
					op__setVerbDimColor(ctx, idx);
				}
				return TRUE;
				case 0xA1:
				{

					/**
					 * dimVerb
					 */
					op__dimVerb(ctx);
				}
				return TRUE;
				case 0xA2:
				{

					/**
					 * setVerbKey
					 * @param word[stack, 0] keyNum
					 */
					int16 keyNum = PULL_WORD();
					op__setVerbKey(ctx, keyNum);
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
					op__setVerbImage(ctx, roomNum, objectNum);
				}
				return TRUE;
				case 0xA4:
				{

					/**
					 * setVerbText
					 * @param long[stack, 0] textAddress
					 */
					int32 textAddress = PULL_LONG();
					op__setVerbText(ctx, textAddress);
				}
				return TRUE;
				case 0xA5:
				{

					/**
					 * centerVerb
					 */
					op__centerVerb(ctx);
				}
				return TRUE;
				case 0xA6:
				{

					/**
					 * setVerbCharSet
					 * @param word[stack, 0] charsetNum
					 */
					int16 charsetNum = PULL_WORD();
					op__setVerbCharSet(ctx, charsetNum);
				}
				return TRUE;
				case 0xA7:
				{

					/**
					 * setVerbLineSpacing
					 * @param long[stack, 0] lineSpacing
					 */
					int32 lineSpacing = PULL_LONG();
					op__setVerbLineSpacing(ctx, lineSpacing);
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
			op__startSound(ctx, sound);
		}
		return TRUE;
		case 0xB0:
		{

			/**
			 * startMusic
			 * @param long[stack, 0] sound
			 */
			int32 sound = PULL_LONG();
			op__startMusic(ctx, sound);
		}
		return TRUE;
		case 0xB1:
		{

			/**
			 * stopSound
			 * @param long[stack, 0] sound
			 */
			int32 sound = PULL_LONG();
			op__stopSound(ctx, sound);
		}
		return TRUE;
		case 0xB2:
		{

			/**
			 * soundKludge
			 * @param args[stack, 0] args
			 */
			int* args = PULL_ARGS();
			op__soundKludge(ctx, args);
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
					op__restartGame(ctx);
				}
				return TRUE;
				case 0x29:
				{

					/**
					 * quitGame
					 */
					op__quitGame(ctx);
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
			op__saveRestoreVerbs(ctx, a, b, c);
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
			op__setObjectName(ctx, objectNum, text);
		}
		return TRUE;
		case 0xB6:
		{

			/**
			 * getDateTime
			 */
			op__getDateTime(ctx);
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
			op__drawBox(ctx, x, y, x2, y2, color);
		}
		return TRUE;
		case 0xB9:
		{

			/**
			 * startVideo
			 * @param string[1...] path
			 */
			byte* path = READ_STRING();
			op__startVideo(ctx, path);
		}
		return TRUE;
		case 0xBA:
		{

			/**
			 * kernelSetFunctions
			 * @param args[stack, 0] args
			 */
			int* args = PULL_ARGS();
			op__kernelSetFunctions(ctx, args);
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
			op__dim2DimArray(ctx, dim2, dim1);
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
			op__distObjectPt(ctx, a, b, c);
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
			op__startScriptQuick2(ctx, script, args);
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
			op__startObjectQuick(ctx, script, entryp, args);
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
			op__pickOneOf(ctx, i, args);
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
			op__pickOneOfDefault(ctx, i, args, def);
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
			op__isAnyOf(ctx, value, args);
		}
		return TRUE;
		case 0xCE:
		{

			/**
			 * getRandomNumber
			 * @param long[stack, 0] max
			 */
			int32 max = PULL_LONG();
			op__getRandomNumber(ctx, max);
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
			op__getRandomNumberRange(ctx, min, max);
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
			op__ifClassOfIs(ctx, obj, args);
		}
		return TRUE;
		case 0xD1:
		{

			/**
			 * getState
			 * @param long[stack, 0] obj
			 */
			int32 obj = PULL_LONG();
			op__getState(ctx, obj);
		}
		return TRUE;
		case 0xD2:
		{

			/**
			 * getOwner
			 * @param long[stack, 0] obj
			 */
			int32 obj = PULL_LONG();
			op__getOwner(ctx, obj);
		}
		return TRUE;
		case 0xD3:
		{

			/**
			 * isScriptRunning
			 * @param long[stack, 0] script
			 */
			int32 script = PULL_LONG();
			op__isScriptRunning(ctx, script);
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
			op__shuffle(ctx, a, b);
		}
		return TRUE;
		case 0xD5:
		{

			/**
			 * isSoundRunning
			 * @param long[stack, 0] sound
			 */
			int32 sound = PULL_LONG();
			op__isSoundRunning(ctx, sound);
		}
		return TRUE;
		case 0xD6:
		{

			/**
			 * abs
			 * @param long[stack, 0] value
			 */
			int32 value = PULL_LONG();
			op__abs(ctx, value);
		}
		return TRUE;
		case 0xD8:
		{

			/**
			 * kernelGetFunctions
			 */
			op__kernelGetFunctions(ctx);
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
			op__isActorInBox(ctx, index, box);
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
			op__getVerbEntrypoint(ctx, verb, entryp);
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
			op__getActorFromXY(ctx, x, y);
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
			op__findObject(ctx, x, y);
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
			op__getVerbFromXY(ctx, x, y);
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
			op__findInventory(ctx, owner, index);
		}
		return TRUE;
		case 0xE0:
		{

			/**
			 * getInventoryCount
			 * @param long[stack, 0] owner
			 */
			int32 owner = PULL_LONG();
			op__getInventoryCount(ctx, owner);
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
			op__getAnimateVariable(ctx, index, variable);
		}
		return TRUE;
		case 0xE2:
		{

			/**
			 * getActorRoom
			 * @param long[stack, 0] index
			 */
			int32 index = PULL_LONG();
			op__getActorRoom(ctx, index);
		}
		return TRUE;
		case 0xE3:
		{

			/**
			 * getActorWalkBox
			 * @param long[stack, 0] index
			 */
			int32 index = PULL_LONG();
			op__getActorWalkBox(ctx, index);
		}
		return TRUE;
		case 0xE4:
		{

			/**
			 * getActorMoving
			 * @param long[stack, 0] index
			 */
			int32 index = PULL_LONG();
			op__getActorMoving(ctx, index);
		}
		return TRUE;
		case 0xE5:
		{

			/**
			 * getActorCostume
			 * @param long[stack, 0] index
			 */
			int32 index = PULL_LONG();
			op__getActorCostume(ctx, index);
		}
		return TRUE;
		case 0xE6:
		{

			/**
			 * getActorScaleX
			 * @param long[stack, 0] index
			 */
			int32 index = PULL_LONG();
			op__getActorScaleX(ctx, index);
		}
		return TRUE;
		case 0xE7:
		{

			/**
			 * getActorLayer
			 * @param long[stack, 0] index
			 */
			int32 index = PULL_LONG();
			op__getActorLayer(ctx, index);
		}
		return TRUE;
		case 0xE8:
		{

			/**
			 * getActorElevation
			 * @param long[stack, 0] index
			 */
			int32 index = PULL_LONG();
			op__getActorElevation(ctx, index);
		}
		return TRUE;
		case 0xE9:
		{

			/**
			 * getActorWidth
			 * @param long[stack, 0] index
			 */
			int32 index = PULL_LONG();
			op__getActorWidth(ctx, index);
		}
		return TRUE;
		case 0xEA:
		{

			/**
			 * getObjectNewDir
			 * @param long[stack, 0] index
			 */
			int32 index = PULL_LONG();
			op__getObjectNewDir(ctx, index);
		}
		return TRUE;
		case 0xEB:
		{

			/**
			 * getObjectX
			 * @param long[stack, 0] index
			 */
			int32 index = PULL_LONG();
			op__getObjectX(ctx, index);
		}
		return TRUE;
		case 0xEC:
		{

			/**
			 * getObjectY
			 * @param long[stack, 0] index
			 */
			int32 index = PULL_LONG();
			op__getObjectY(ctx, index);
		}
		return TRUE;
		case 0xED:
		{

			/**
			 * getActorChore
			 */
			op__getActorChore(ctx);
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
			op__distObjectObject(ctx, a, b);
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
			op__distObjectPtPt(ctx, a, b, c, d);
		}
		return TRUE;
		case 0xF0:
		{

			/**
			 * getObjectImageX
			 */
			op__getObjectImageX(ctx);
		}
		return TRUE;
		case 0xF1:
		{

			/**
			 * getObjectImageY
			 */
			op__getObjectImageY(ctx);
		}
		return TRUE;
		case 0xF2:
		{

			/**
			 * getObjectImageWidth
			 */
			op__getObjectImageWidth(ctx);
		}
		return TRUE;
		case 0xF3:
		{

			/**
			 * getObjectImageHeight
			 */
			op__getObjectImageHeight(ctx);
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
			op__getStringWidth(ctx, charsetNum, text);
		}
		return TRUE;
		case 0xF7:
		{

			/**
			 * getActorZPlane
			 */
			op__getActorZPlane(ctx);
		}
		return TRUE;
	}
	return FALSE;
}
/** END **/
