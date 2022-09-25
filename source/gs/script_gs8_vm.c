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

#define GS_FILE "script_gs8_vm"

#include "shared/forward.h"
#include "shared/error.h"
#include "shared/game.h"
#include "shared/file.h"

#include "coroutine.h"
#include "script.h"



/* 00 pushByte */
GS_PRIVATE GS_INLINE void op_pushByte(gs_Coroutine* coro, byte value) {
	/* TODO */
}

/* 01 pushWord */
GS_PRIVATE GS_INLINE void op_pushWord(gs_Coroutine* coro, int32 value) {
	/* TODO */
}

/* 02 pushWordVar */
GS_PRIVATE GS_INLINE void op_pushWordVar(gs_Coroutine* coro, int32 name) {
	/* TODO */
}

/* 03 wordArrayRead */
GS_PRIVATE GS_INLINE void op_wordArrayRead(gs_Coroutine* coro, int32 base) {
	/* TODO */
}

/* 04 wordArrayIndexedRead */
GS_PRIVATE GS_INLINE void op_wordArrayIndexedRead(gs_Coroutine* coro, int32 index, int32 base, int32 arrayNum) {
	/* TODO */
}

/* 05 dup */
GS_PRIVATE GS_INLINE void op_dup(gs_Coroutine* coro, int32 value) {
	/* TODO */
}

/* 06 pop */
GS_PRIVATE GS_INLINE void op_pop(gs_Coroutine* coro, int32 discard) {
	/* TODO */
}

/* 07 not */
GS_PRIVATE GS_INLINE void op_not(gs_Coroutine* coro, int32 value) {
	/* TODO */
}

/* 08 eq */
GS_PRIVATE GS_INLINE void op_eq(gs_Coroutine* coro, int32 left, int32 right) {
	/* TODO */
}

/* 09 neq */
GS_PRIVATE GS_INLINE void op_neq(gs_Coroutine* coro, int32 left, int32 right) {
	/* TODO */
}

/* 0A gt */
GS_PRIVATE GS_INLINE void op_gt(gs_Coroutine* coro, int32 left, int32 right) {
	/* TODO */
}

/* 0B lt */
GS_PRIVATE GS_INLINE void op_lt(gs_Coroutine* coro, int32 left, int32 right) {
	/* TODO */
}

/* 0C le */
GS_PRIVATE GS_INLINE void op_le(gs_Coroutine* coro, int32 left, int32 right) {
	/* TODO */
}

/* 0D ge */
GS_PRIVATE GS_INLINE void op_ge(gs_Coroutine* coro, int32 left, int32 right) {
	/* TODO */
}

/* 0E add */
GS_PRIVATE GS_INLINE void op_add(gs_Coroutine* coro, int32 left, int32 right) {
	/* TODO */
}

/* 0F sub */
GS_PRIVATE GS_INLINE void op_sub(gs_Coroutine* coro, int32 left, int32 right) {
	/* TODO */
}

/* 10 mul */
GS_PRIVATE GS_INLINE void op_mul(gs_Coroutine* coro, int32 left, int32 right) {
	/* TODO */
}

/* 11 div */
GS_PRIVATE GS_INLINE void op_div(gs_Coroutine* coro, int32 left, int32 right) {
	/* TODO */
}

/* 12 land */
GS_PRIVATE GS_INLINE void op_land(gs_Coroutine* coro, int32 left, int32 right) {
	/* TODO */
}

/* 13 lor */
GS_PRIVATE GS_INLINE void op_lor(gs_Coroutine* coro, int32 left, int32 right) {
	/* TODO */
}

/* 14 band */
GS_PRIVATE GS_INLINE void op_band(gs_Coroutine* coro, int32 left, int32 right) {
	/* TODO */
}

/* 15 bor */
GS_PRIVATE GS_INLINE void op_bor(gs_Coroutine* coro, int32 left, int32 right) {
	/* TODO */
}

/* 16 mod */
GS_PRIVATE GS_INLINE void op_mod(gs_Coroutine* coro, int32 left, int32 right) {
	/* TODO */
}

/* 42 writeByteVar */
GS_PRIVATE GS_INLINE void op_writeByteVar(gs_Coroutine* coro, int32 value) {
	/* TODO */
}

/* 46 byteArrayWrite */
GS_PRIVATE GS_INLINE void op_byteArrayWrite(gs_Coroutine* coro, int32 base, int32 value) {
	/* TODO */
}

/* 4A byteArrayIndexedWrite */
GS_PRIVATE GS_INLINE void op_byteArrayIndexedWrite(gs_Coroutine* coro, int32 index, int32 base, int32 value) {
	/* TODO */
}

/* 4E byteVarInc */
GS_PRIVATE GS_INLINE void op_byteVarInc(gs_Coroutine* coro) {
	/* TODO */
}

/* 52 byteArrayInc */
GS_PRIVATE GS_INLINE void op_byteArrayInc(gs_Coroutine* coro, int32 base) {
	/* TODO */
}

/* 56 byteVarDec */
GS_PRIVATE GS_INLINE void op_byteVarDec(gs_Coroutine* coro) {
	/* TODO */
}

/* 5A byteArrayDec */
GS_PRIVATE GS_INLINE void op_byteArrayDec(gs_Coroutine* coro, int32 base) {
	/* TODO */
}

/* 61 drawObject */
GS_PRIVATE GS_INLINE void op_drawObject(gs_Coroutine* coro, int32 obj, int32 state) {
	/* TODO */
}

/* 62 drawObjectAt */
GS_PRIVATE GS_INLINE void op_drawObjectAt(gs_Coroutine* coro, int32 obj, int32 x, int32 y) {
	/* TODO */
}

/* 63 drawBlastObject */
GS_PRIVATE GS_INLINE void op_drawBlastObject(gs_Coroutine* coro, int32 a, int32 b, int32 c, int32 d, int32 e, int32 argsLength, int32* args) {
	/* TODO */
}

/* 64 if */
GS_PRIVATE GS_INLINE void op_if(gs_Coroutine* coro, int32 condition, int32 offset) {
	/* TODO */
}

/* 65 ifNot */
GS_PRIVATE GS_INLINE void op_ifNot(gs_Coroutine* coro, int32 condition, int32 offset) {
	/* TODO */
}

/* 66 jump */
GS_PRIVATE GS_INLINE void op_jump(gs_Coroutine* coro, int32 offset) {
	/* TODO */
}

/* 67 breakHere */
GS_PRIVATE GS_INLINE void op_breakHere(gs_Coroutine* coro) {
	/* TODO */
}

/* 68 delayFrames */
GS_PRIVATE GS_INLINE void op_delayFrames(gs_Coroutine* coro) {
	/* TODO */
}

/* 691E waitActor */
GS_INLINE void op_waitActor(gs_Coroutine* coro, int32 offset, int32 actorNum) {
	/* TODO */
}

/* 691F waitMessage */
GS_INLINE void op_waitMessage(gs_Coroutine* coro) {
	/* TODO */
}

/* 6920 waitCamera */
GS_INLINE void op_waitCamera(gs_Coroutine* coro) {
	/* TODO */
}

/* 6921 waitSentence */
GS_INLINE void op_waitSentence(gs_Coroutine* coro) {
	/* TODO */
}

/* 6922 waitAnimation */
GS_INLINE void op_waitAnimation(gs_Coroutine* coro) {
	/* TODO */
}

/* 6923 waitTurn */
GS_INLINE void op_waitTurn(gs_Coroutine* coro, int32 offset, int32 actorNum) {
	/* TODO */
}

/* 6A delay */
GS_PRIVATE GS_INLINE void op_delay(gs_Coroutine* coro, int32 delay) {
	/* TODO */
}

/* 6B delaySeconds */
GS_PRIVATE GS_INLINE void op_delaySeconds(gs_Coroutine* coro, int32 seconds) {
	/* TODO */
}

/* 6C delayMinutes */
GS_PRIVATE GS_INLINE void op_delayMinutes(gs_Coroutine* coro, int32 minutes) {
	/* TODO */
}

/* 6D writeWordVar */
GS_PRIVATE GS_INLINE void op_writeWordVar(gs_Coroutine* coro, int32 value) {
	/* TODO */
}

/* 6E wordVarInc */
GS_PRIVATE GS_INLINE void op_wordVarInc(gs_Coroutine* coro, int32 var) {
	/* TODO */
}

/* 6F wordVarDec */
GS_PRIVATE GS_INLINE void op_wordVarDec(gs_Coroutine* coro, int32 var) {
	/* TODO */
}

/* 700A newArrayInt */
GS_INLINE void op_newArrayInt(gs_Coroutine* coro, int32 arrayNum, int32 dim1) {
	/* TODO */
}

/* 700B newArrayString */
GS_INLINE void op_newArrayString(gs_Coroutine* coro, int32 arrayNum, int32 dim1) {
	/* TODO */
}

/* 700C deleteArray */
GS_INLINE void op_deleteArray(gs_Coroutine* coro, int32 arrayNum) {
	/* TODO */
}

/* 71 wordArrayWrite */
GS_PRIVATE GS_INLINE void op_wordArrayWrite(gs_Coroutine* coro, int32 base, int32 value) {
	/* TODO */
}

/* 72 wordArrayInc */
GS_PRIVATE GS_INLINE void op_wordArrayInc(gs_Coroutine* coro, int32 base) {
	/* TODO */
}

/* 73 wordArrayDec */
GS_PRIVATE GS_INLINE void op_wordArrayDec(gs_Coroutine* coro, int32 base) {
	/* TODO */
}

/* 740A newArray2Int */
GS_INLINE void op_newArray2Int(gs_Coroutine* coro, int32 arrayNum, int32 dim1, int32 dim2) {
	/* TODO */
}

/* 740B newArray2String */
GS_INLINE void op_newArray2String(gs_Coroutine* coro, int32 arrayNum, int32 dim1, int32 dim2) {
	/* TODO */
}

/* 740C deleteArray2 */
GS_INLINE void op_deleteArray2(gs_Coroutine* coro, int32 arrayNum) {
	/* TODO */
}

/* 75 wordArrayIndexedWrite */
GS_PRIVATE GS_INLINE void op_wordArrayIndexedWrite(gs_Coroutine* coro, int32 index, int32 base, int32 value, int32 arrayNum) {
	/* TODO */
}

/* 7614 setArrayString */
GS_INLINE void op_setArrayString(gs_Coroutine* coro, char* string, int32 offset, int32 arrayNum) {
	/* TODO */
}

/* 7615 setArrayList */
GS_INLINE void op_setArrayList(gs_Coroutine* coro, int32 listLength, int32* list, int32 offset, int32 arrayNum) {
	/* TODO */
}

/* 7616 setArray2List */
GS_INLINE void op_setArray2List(gs_Coroutine* coro, int32 listLength, int32* list, int32 offset, int32 arrayNum) {
	/* TODO */
}

/* 79 startScript */
GS_PRIVATE GS_INLINE void op_startScript(gs_Coroutine* coro, int32 flags, int32 script, int32 argsLength, int32* args) {
	/* TODO */
}

/* 7A startScriptQuick */
GS_PRIVATE GS_INLINE void op_startScriptQuick(gs_Coroutine* coro, int32 script, int32 argsLength, int32* args) {
	/* TODO */
}

/* 7B stopObjectCode */
GS_PRIVATE GS_INLINE void op_stopObjectCode(gs_Coroutine* coro) {
	/* TODO */
}

/* 7C stopScript */
GS_PRIVATE GS_INLINE void op_stopScript(gs_Coroutine* coro, int32 scriptNum) {
	/* TODO */
}

/* 7D jumpToScript */
GS_PRIVATE GS_INLINE void op_jumpToScript(gs_Coroutine* coro, int32 flags, int32 scriptNum, int32 argsLength, int32* args) {
	/* TODO */
}

/* 7E dummy */
GS_PRIVATE GS_INLINE void op_dummy(gs_Coroutine* coro) {
	/* TODO */
}

/* 7F startObject */
GS_PRIVATE GS_INLINE void op_startObject(gs_Coroutine* coro, int32 flags, int32 script, byte entryp, int32 argsLength, int32* args) {
	/* TODO */
}

/* 80 stopObjectScript */
GS_PRIVATE GS_INLINE void op_stopObjectScript(gs_Coroutine* coro, int16 script) {
	/* TODO */
}

/* 81 cutscene */
GS_PRIVATE GS_INLINE void op_cutscene(gs_Coroutine* coro, int32 argsLength, int32* args) {
	/* TODO */
}

/* 82 endCutscene */
GS_PRIVATE GS_INLINE void op_endCutscene(gs_Coroutine* coro) {
	/* TODO */
}

/* 83 freezeUnfreeze */
GS_PRIVATE GS_INLINE void op_freezeUnfreeze(gs_Coroutine* coro, int32 script) {
	/* TODO */
}

/* 84 beginOverride */
GS_PRIVATE GS_INLINE void op_beginOverride(gs_Coroutine* coro) {
	/* TODO */
}

/* 85 endOverride */
GS_PRIVATE GS_INLINE void op_endOverride(gs_Coroutine* coro) {
	/* TODO */
}

/* 86 stopSentence */
GS_PRIVATE GS_INLINE void op_stopSentence(gs_Coroutine* coro) {
	/* TODO */
}

/* 89 setClass */
GS_PRIVATE GS_INLINE void op_setClass(gs_Coroutine* coro, int32 obj, int32 argsLength, int32* args) {
	/* TODO */
}

/* 8A setState */
GS_PRIVATE GS_INLINE void op_setState(gs_Coroutine* coro, int32 obj, int32 state) {
	/* TODO */
}

/* 8B setOwner */
GS_PRIVATE GS_INLINE void op_setOwner(gs_Coroutine* coro, int32 obj, int32 owner) {
	/* TODO */
}

/* 8C panCameraTo */
GS_PRIVATE GS_INLINE void op_panCameraTo(gs_Coroutine* coro, int32 x, int32 y) {
	/* TODO */
}

/* 8D actorFollowCamera */
GS_PRIVATE GS_INLINE void op_actorFollowCamera(gs_Coroutine* coro, int32 index) {
	/* TODO */
}

/* 8E setCameraAt */
GS_PRIVATE GS_INLINE void op_setCameraAt(gs_Coroutine* coro, int32 x, int32 y) {
	/* TODO */
}

/* 8F41 printActorAt */
GS_INLINE void op_printActorAt(gs_Coroutine* coro, int32 x, int32 y) {
	/* TODO */
}

/* 8F42 printActorColour */
GS_INLINE void op_printActorColour(gs_Coroutine* coro, int32 col) {
	/* TODO */
}

/* 8F43 printActorClipped */
GS_INLINE void op_printActorClipped(gs_Coroutine* coro, int32 right) {
	/* TODO */
}

/* 8F45 printActorCentre */
GS_INLINE void op_printActorCentre(gs_Coroutine* coro) {
	/* TODO */
}

/* 8F47 printActorLeft */
GS_INLINE void op_printActorLeft(gs_Coroutine* coro) {
	/* TODO */
}

/* 8F48 printActorOverhead */
GS_INLINE void op_printActorOverhead(gs_Coroutine* coro) {
	/* TODO */
}

/* 8F4A printActorMumble */
GS_INLINE void op_printActorMumble(gs_Coroutine* coro) {
	/* TODO */
}

/* 8F4B printActorText */
GS_INLINE void op_printActorText(gs_Coroutine* coro, char* text) {
	/* TODO */
}

/* 8FFE printActorLoadDefault */
GS_INLINE void op_printActorLoadDefault(gs_Coroutine* coro, int32 actorNum) {
	/* TODO */
}

/* 8FFF printActorSaveDefault */
GS_INLINE void op_printActorSaveDefault(gs_Coroutine* coro) {
	/* TODO */
}

/* 9041 printEgoAt */
GS_INLINE void op_printEgoAt(gs_Coroutine* coro, int32 x, int32 y) {
	/* TODO */
}

/* 9042 printEgoColour */
GS_INLINE void op_printEgoColour(gs_Coroutine* coro, int32 col) {
	/* TODO */
}

/* 9043 printEgoClipped */
GS_INLINE void op_printEgoClipped(gs_Coroutine* coro, int32 right) {
	/* TODO */
}

/* 9045 printEgoCentre */
GS_INLINE void op_printEgoCentre(gs_Coroutine* coro) {
	/* TODO */
}

/* 9047 printEgoLeft */
GS_INLINE void op_printEgoLeft(gs_Coroutine* coro) {
	/* TODO */
}

/* 9048 printEgoOverhead */
GS_INLINE void op_printEgoOverhead(gs_Coroutine* coro) {
	/* TODO */
}

/* 904A printEgoMumble */
GS_INLINE void op_printEgoMumble(gs_Coroutine* coro) {
	/* TODO */
}

/* 904B printEgoText */
GS_INLINE void op_printEgoText(gs_Coroutine* coro, char* text) {
	/* TODO */
}

/* 90FE printEgoLoadDefault */
GS_INLINE void op_printEgoLoadDefault(gs_Coroutine* coro, int32 actorNum) {
	/* TODO */
}

/* 90FF printEgoSaveDefault */
GS_INLINE void op_printEgoSaveDefault(gs_Coroutine* coro) {
	/* TODO */
}

/* 91 talkActor */
GS_PRIVATE GS_INLINE void op_talkActor(gs_Coroutine* coro, char* text, int32 actor) {
	/* TODO */
}

/* 92 talkEgo */
GS_PRIVATE GS_INLINE void op_talkEgo(gs_Coroutine* coro, char* text) {
	/* TODO */
}

/* 9341 printLineAt */
GS_INLINE void op_printLineAt(gs_Coroutine* coro, int32 x, int32 y) {
	/* TODO */
}

/* 9342 printLineColour */
GS_INLINE void op_printLineColour(gs_Coroutine* coro, int32 col) {
	/* TODO */
}

/* 9343 printLineClipped */
GS_INLINE void op_printLineClipped(gs_Coroutine* coro, int32 right) {
	/* TODO */
}

/* 9345 printLineCentre */
GS_INLINE void op_printLineCentre(gs_Coroutine* coro) {
	/* TODO */
}

/* 9347 printLineLeft */
GS_INLINE void op_printLineLeft(gs_Coroutine* coro) {
	/* TODO */
}

/* 9348 printLineOverhead */
GS_INLINE void op_printLineOverhead(gs_Coroutine* coro) {
	/* TODO */
}

/* 934A printLineMumble */
GS_INLINE void op_printLineMumble(gs_Coroutine* coro) {
	/* TODO */
}

/* 934B printLineText */
GS_INLINE void op_printLineText(gs_Coroutine* coro, char* text) {
	/* TODO */
}

/* 93FE printLineLoadDefault */
GS_INLINE void op_printLineLoadDefault(gs_Coroutine* coro) {
	/* TODO */
}

/* 93FF printLineSaveDefault */
GS_INLINE void op_printLineSaveDefault(gs_Coroutine* coro) {
	/* TODO */
}

/* 9441 printTextAt */
GS_INLINE void op_printTextAt(gs_Coroutine* coro, int32 x, int32 y) {
	/* TODO */
}

/* 9442 printTextColour */
GS_INLINE void op_printTextColour(gs_Coroutine* coro, int32 col) {
	/* TODO */
}

/* 9443 printTextClipped */
GS_INLINE void op_printTextClipped(gs_Coroutine* coro, int32 right) {
	/* TODO */
}

/* 9445 printTextCentre */
GS_INLINE void op_printTextCentre(gs_Coroutine* coro) {
	/* TODO */
}

/* 9447 printTextLeft */
GS_INLINE void op_printTextLeft(gs_Coroutine* coro) {
	/* TODO */
}

/* 9448 printTextOverhead */
GS_INLINE void op_printTextOverhead(gs_Coroutine* coro) {
	/* TODO */
}

/* 944A printTextMumble */
GS_INLINE void op_printTextMumble(gs_Coroutine* coro) {
	/* TODO */
}

/* 944B printTextText */
GS_INLINE void op_printTextText(gs_Coroutine* coro, char* text) {
	/* TODO */
}

/* 94FE printTextLoadDefault */
GS_INLINE void op_printTextLoadDefault(gs_Coroutine* coro) {
	/* TODO */
}

/* 94FF printTextSaveDefault */
GS_INLINE void op_printTextSaveDefault(gs_Coroutine* coro) {
	/* TODO */
}

/* 9541 printDebugAt */
GS_INLINE void op_printDebugAt(gs_Coroutine* coro, int32 x, int32 y) {
	/* TODO */
}

/* 9542 printDebugColour */
GS_INLINE void op_printDebugColour(gs_Coroutine* coro, int32 col) {
	/* TODO */
}

/* 9543 printDebugClipped */
GS_INLINE void op_printDebugClipped(gs_Coroutine* coro, int32 right) {
	/* TODO */
}

/* 9545 printDebugCentre */
GS_INLINE void op_printDebugCentre(gs_Coroutine* coro) {
	/* TODO */
}

/* 9547 printDebugLeft */
GS_INLINE void op_printDebugLeft(gs_Coroutine* coro) {
	/* TODO */
}

/* 9548 printDebugOverhead */
GS_INLINE void op_printDebugOverhead(gs_Coroutine* coro) {
	/* TODO */
}

/* 954A printDebugMumble */
GS_INLINE void op_printDebugMumble(gs_Coroutine* coro) {
	/* TODO */
}

/* 954B printDebugText */
GS_INLINE void op_printDebugText(gs_Coroutine* coro, char* text) {
	/* TODO */
}

/* 95FE printDebugLoadDefault */
GS_INLINE void op_printDebugLoadDefault(gs_Coroutine* coro) {
	/* TODO */
}

/* 95FF printDebugSaveDefault */
GS_INLINE void op_printDebugSaveDefault(gs_Coroutine* coro) {
	/* TODO */
}

/* 9641 printSystemAt */
GS_INLINE void op_printSystemAt(gs_Coroutine* coro, int32 x, int32 y) {
	/* TODO */
}

/* 9642 printSystemColour */
GS_INLINE void op_printSystemColour(gs_Coroutine* coro, int32 col) {
	/* TODO */
}

/* 9643 printSystemClipped */
GS_INLINE void op_printSystemClipped(gs_Coroutine* coro, int32 right) {
	/* TODO */
}

/* 9645 printSystemCentre */
GS_INLINE void op_printSystemCentre(gs_Coroutine* coro) {
	/* TODO */
}

/* 9647 printSystemLeft */
GS_INLINE void op_printSystemLeft(gs_Coroutine* coro) {
	/* TODO */
}

/* 9648 printSystemOverhead */
GS_INLINE void op_printSystemOverhead(gs_Coroutine* coro) {
	/* TODO */
}

/* 964A printSystemMumble */
GS_INLINE void op_printSystemMumble(gs_Coroutine* coro) {
	/* TODO */
}

/* 964B printSystemText */
GS_INLINE void op_printSystemText(gs_Coroutine* coro, char* text) {
	/* TODO */
}

/* 96FE printSystemLoadDefault */
GS_INLINE void op_printSystemLoadDefault(gs_Coroutine* coro) {
	/* TODO */
}

/* 96FF printSystemSaveDefault */
GS_INLINE void op_printSystemSaveDefault(gs_Coroutine* coro) {
	/* TODO */
}

/* 9741 blastTextAt */
GS_INLINE void op_blastTextAt(gs_Coroutine* coro, int32 x, int32 y) {
	/* TODO */
}

/* 9742 blastTextColour */
GS_INLINE void op_blastTextColour(gs_Coroutine* coro, int32 col) {
	/* TODO */
}

/* 9743 blastTextClipped */
GS_INLINE void op_blastTextClipped(gs_Coroutine* coro, int32 right) {
	/* TODO */
}

/* 9745 blastTextCentre */
GS_INLINE void op_blastTextCentre(gs_Coroutine* coro) {
	/* TODO */
}

/* 9747 blastTextLeft */
GS_INLINE void op_blastTextLeft(gs_Coroutine* coro) {
	/* TODO */
}

/* 9748 blastTextOverhead */
GS_INLINE void op_blastTextOverhead(gs_Coroutine* coro) {
	/* TODO */
}

/* 974A blastTextMumble */
GS_INLINE void op_blastTextMumble(gs_Coroutine* coro) {
	/* TODO */
}

/* 974B blastTextText */
GS_INLINE void op_blastTextText(gs_Coroutine* coro, char* text) {
	/* TODO */
}

/* 97FE blastTextLoadDefault */
GS_INLINE void op_blastTextLoadDefault(gs_Coroutine* coro) {
	/* TODO */
}

/* 97FF blastTextSaveDefault */
GS_INLINE void op_blastTextSaveDefault(gs_Coroutine* coro) {
	/* TODO */
}

/* 98 drawObject */
GS_PRIVATE GS_INLINE void op_drawObject(gs_Coroutine* coro, int32 obj, int32 x, int32 y, int32 state) {
	/* TODO */
}

/* 9CDC cursorOn */
GS_INLINE void op_cursorOn(gs_Coroutine* coro) {
	/* TODO */
}

/* 9CDD cursorOff */
GS_INLINE void op_cursorOff(gs_Coroutine* coro) {
	/* TODO */
}

/* 9CDE cursorSoftOn */
GS_INLINE void op_cursorSoftOn(gs_Coroutine* coro) {
	/* TODO */
}

/* 9CDF cursorSoftOff */
GS_INLINE void op_cursorSoftOff(gs_Coroutine* coro) {
	/* TODO */
}

/* 9CE0 cursorUserPutOn */
GS_INLINE void op_cursorUserPutOn(gs_Coroutine* coro) {
	/* TODO */
}

/* 9CE1 cursorUserPutOff */
GS_INLINE void op_cursorUserPutOff(gs_Coroutine* coro) {
	/* TODO */
}

/* 9CE2 cursorUserPutSoftOn */
GS_INLINE void op_cursorUserPutSoftOn(gs_Coroutine* coro) {
	/* TODO */
}

/* 9CE3 cursorUserPutSoftOff */
GS_INLINE void op_cursorUserPutSoftOff(gs_Coroutine* coro) {
	/* TODO */
}

/* 9CE4 cursorUserCursorImage */
GS_INLINE void op_cursorUserCursorImage(gs_Coroutine* coro, int32 idx, int32 obj) {
	/* TODO */
}

/* 9CE5 cursorHotSpot */
GS_INLINE void op_cursorHotSpot(gs_Coroutine* coro, int32 x, int32 y) {
	/* TODO */
}

/* 9CE6 cursorSetTransparency */
GS_INLINE void op_cursorSetTransparency(gs_Coroutine* coro, int32 enabled) {
	/* TODO */
}

/* 9CE7 cursorSetCharSet */
GS_INLINE void op_cursorSetCharSet(gs_Coroutine* coro, int32 charsetNum) {
	/* TODO */
}

/* 9CE8 cursorSetColour */
GS_INLINE void op_cursorSetColour(gs_Coroutine* coro, int32 argsLength, int32* args) {
	/* TODO */
}

/* 9CE9 cursorSetPos */
GS_INLINE void op_cursorSetPos(gs_Coroutine* coro, int32 x, int32 y) {
	/* TODO */
}

/* 9D loadRoom */
GS_PRIVATE GS_INLINE void op_loadRoom(gs_Coroutine* coro, byte room) {
	/* TODO */
}

/* 9E loadRoomWithEgo */
GS_PRIVATE GS_INLINE void op_loadRoomWithEgo(gs_Coroutine* coro, int32 x, int32 y, int32 room) {
	/* TODO */
}

/* 9F walkActorToObj */
GS_PRIVATE GS_INLINE void op_walkActorToObj(gs_Coroutine* coro, int32 index, int32 obj, int32 dist) {
	/* TODO */
}

/* A0 walkActorTo */
GS_PRIVATE GS_INLINE void op_walkActorTo(gs_Coroutine* coro, int32 index, int32 x, int32 y) {
	/* TODO */
}

/* A1 putActorAtXY */
GS_PRIVATE GS_INLINE void op_putActorAtXY(gs_Coroutine* coro, int32 actorIndex, int32 x, int32 y, int32 room) {
	/* TODO */
}

/* A2 putActorAtObject */
GS_PRIVATE GS_INLINE void op_putActorAtObject(gs_Coroutine* coro, int32 obj) {
	/* TODO */
}

/* A3 faceActor */
GS_PRIVATE GS_INLINE void op_faceActor(gs_Coroutine* coro, int32 index, int32 obj) {
	/* TODO */
}

/* A4 animateActor */
GS_PRIVATE GS_INLINE void op_animateActor(gs_Coroutine* coro, int32 index, int32 anim) {
	/* TODO */
}

/* A5 doSentence */
GS_PRIVATE GS_INLINE void op_doSentence(gs_Coroutine* coro, byte verb, int16 objectA, int16 objectB) {
	/* TODO */
}

/* A6 pickupObject */
GS_PRIVATE GS_INLINE void op_pickupObject(gs_Coroutine* coro, int32 obj) {
	/* TODO */
}

/* A7 setBoxFlags */
GS_PRIVATE GS_INLINE void op_setBoxFlags(gs_Coroutine* coro, int32 argsLength, int32* args, int32 value) {
	/* TODO */
}

/* A8 createBoxMatrix */
GS_PRIVATE GS_INLINE void op_createBoxMatrix(gs_Coroutine* coro) {
	/* TODO */
}

/* A9 wait */
GS_PRIVATE GS_INLINE void op_wait(gs_Coroutine* coro) {
	/* TODO */
}

/* AA3C resourceRoutine3C */
GS_INLINE void op_resourceRoutine3C(gs_Coroutine* coro, int16 num) {
	/* TODO */
}

/* AA3D loadCostume */
GS_INLINE void op_loadCostume(gs_Coroutine* coro, int16 num) {
	/* TODO */
}

/* AA3E loadObject */
GS_INLINE void op_loadObject(gs_Coroutine* coro, int16 num) {
	/* TODO */
}

/* AA3F loadRoom */
GS_INLINE void op_loadRoom(gs_Coroutine* coro, int16 num) {
	/* TODO */
}

/* AA40 loadScript */
GS_INLINE void op_loadScript(gs_Coroutine* coro, int16 num) {
	/* TODO */
}

/* AA41 loadSound */
GS_INLINE void op_loadSound(gs_Coroutine* coro, int16 num) {
	/* TODO */
}

/* AA42 lockCostume */
GS_INLINE void op_lockCostume(gs_Coroutine* coro, int16 num) {
	/* TODO */
}

/* AA43 lockRoom */
GS_INLINE void op_lockRoom(gs_Coroutine* coro, int16 num) {
	/* TODO */
}

/* AA44 lockScript */
GS_INLINE void op_lockScript(gs_Coroutine* coro, int16 num) {
	/* TODO */
}

/* AA45 lockSound */
GS_INLINE void op_lockSound(gs_Coroutine* coro, int16 num) {
	/* TODO */
}

/* AA46 unlockCostume */
GS_INLINE void op_unlockCostume(gs_Coroutine* coro, int16 num) {
	/* TODO */
}

/* AA47 unlockRoom */
GS_INLINE void op_unlockRoom(gs_Coroutine* coro, int16 num) {
	/* TODO */
}

/* AA48 unlockScript */
GS_INLINE void op_unlockScript(gs_Coroutine* coro, int16 num) {
	/* TODO */
}

/* AA49 unlockSound */
GS_INLINE void op_unlockSound(gs_Coroutine* coro, int16 num) {
	/* TODO */
}

/* AA4A unloadCostume */
GS_INLINE void op_unloadCostume(gs_Coroutine* coro, int16 num) {
	/* TODO */
}

/* AA4B unloadRoom */
GS_INLINE void op_unloadRoom(gs_Coroutine* coro, int16 num) {
	/* TODO */
}

/* AA4C unloadScript */
GS_INLINE void op_unloadScript(gs_Coroutine* coro, int16 num) {
	/* TODO */
}

/* AA4D unloadSound */
GS_INLINE void op_unloadSound(gs_Coroutine* coro, int16 num) {
	/* TODO */
}

/* AB52 setRoomRGB */
GS_INLINE void op_setRoomRGB(gs_Coroutine* coro, byte r, byte g, byte b, int32 index) {
	/* TODO */
}

/* AB57 fadeRoom */
GS_INLINE void op_fadeRoom(gs_Coroutine* coro, int32 param) {
	/* TODO */
}

/* AB58 setRoomRGBIntensity */
GS_INLINE void op_setRoomRGBIntensity(gs_Coroutine* coro, int32 redScale, int32 greenScale, int32 blueScale, int16 startColour, int16 endColour) {
	/* TODO */
}

/* AB59 setRoomRGBTransform */
GS_INLINE void op_setRoomRGBTransform(gs_Coroutine* coro, int32 resId, int16 start, int16 end, int32 time) {
	/* TODO */
}

/* AB5C setRoomPalette */
GS_INLINE void op_setRoomPalette(gs_Coroutine* coro, int16 paletteNum) {
	/* TODO */
}

/* AB5D saveGame */
GS_INLINE void op_saveGame(gs_Coroutine* coro) {
	/* TODO */
}

/* AB5E loadGame */
GS_INLINE void op_loadGame(gs_Coroutine* coro, byte saveSound) {
	/* TODO */
}

/* AB5F setRoomSaturation */
GS_INLINE void op_setRoomSaturation(gs_Coroutine* coro, int32 hueScale, int32 satScale, int32 lightScale, int16 startColour, int16 endColour) {
	/* TODO */
}

/* AC64 setActorCostume */
GS_INLINE void op_setActorCostume(gs_Coroutine* coro, int16 costumeNum) {
	/* TODO */
}

/* AC65 setActorWalkSpeed */
GS_INLINE void op_setActorWalkSpeed(gs_Coroutine* coro, int16 x, int16 y) {
	/* TODO */
}

/* AC67 setActorAnimationDefault */
GS_INLINE void op_setActorAnimationDefault(gs_Coroutine* coro) {
	/* TODO */
}

/* AC68 setActorAnimationInit */
GS_INLINE void op_setActorAnimationInit(gs_Coroutine* coro, byte frameNum) {
	/* TODO */
}

/* AC69 setActorAnimationTalk */
GS_INLINE void op_setActorAnimationTalk(gs_Coroutine* coro, byte startFrameNum, byte endFrameNum) {
	/* TODO */
}

/* AC6A setActorAnimationWalk */
GS_INLINE void op_setActorAnimationWalk(gs_Coroutine* coro, byte walkFrameNum) {
	/* TODO */
}

/* AC6B setActorAnimationStand */
GS_INLINE void op_setActorAnimationStand(gs_Coroutine* coro, byte standFrameNum) {
	/* TODO */
}

/* AC6C setActorAnimationSpeed */
GS_INLINE void op_setActorAnimationSpeed(gs_Coroutine* coro, byte animationSpeed) {
	/* TODO */
}

/* AC6D setActorDefault */
GS_INLINE void op_setActorDefault(gs_Coroutine* coro) {
	/* TODO */
}

/* AC6E setActorElevation */
GS_INLINE void op_setActorElevation(gs_Coroutine* coro, int16 elevation) {
	/* TODO */
}

/* AC6F setActorPalette */
GS_INLINE void op_setActorPalette(gs_Coroutine* coro, byte index, int16 value) {
	/* TODO */
}

/* AC70 setActorTalkColour */
GS_INLINE void op_setActorTalkColour(gs_Coroutine* coro, byte colourIndex) {
	/* TODO */
}

/* AC71 setActorName */
GS_INLINE void op_setActorName(gs_Coroutine* coro, char* text) {
	/* TODO */
}

/* AC72 setActorWidth */
GS_INLINE void op_setActorWidth(gs_Coroutine* coro, int16 width) {
	/* TODO */
}

/* AC73 setActorScale */
GS_INLINE void op_setActorScale(gs_Coroutine* coro, int16 size) {
	/* TODO */
}

/* AC74 setActorNeverZClip */
GS_INLINE void op_setActorNeverZClip(gs_Coroutine* coro) {
	/* TODO */
}

/* AC75 setActorAlwaysZClip */
GS_INLINE void op_setActorAlwaysZClip(gs_Coroutine* coro, byte forceClip) {
	/* TODO */
}

/* AC76 setActorIgnoreBoxes */
GS_INLINE void op_setActorIgnoreBoxes(gs_Coroutine* coro) {
	/* TODO */
}

/* AC77 setActorFollowBoxes */
GS_INLINE void op_setActorFollowBoxes(gs_Coroutine* coro) {
	/* TODO */
}

/* AC78 setActorSpecialDraw */
GS_INLINE void op_setActorSpecialDraw(gs_Coroutine* coro) {
	/* TODO */
}

/* AC79 setActorTextOffset */
GS_INLINE void op_setActorTextOffset(gs_Coroutine* coro, int16 x, int16 y) {
	/* TODO */
}

/* AC7B setActorVar */
GS_INLINE void op_setActorVar(gs_Coroutine* coro, int32 name, int32 value) {
	/* TODO */
}

/* AC7C setActorIgnoreTurns */
GS_INLINE void op_setActorIgnoreTurns(gs_Coroutine* coro) {
	/* TODO */
}

/* AC7D setActorFollowTurns */
GS_INLINE void op_setActorFollowTurns(gs_Coroutine* coro) {
	/* TODO */
}

/* AC7E setActorNew */
GS_INLINE void op_setActorNew(gs_Coroutine* coro) {
	/* TODO */
}

/* AC7F setActorDepth */
GS_INLINE void op_setActorDepth(gs_Coroutine* coro, int16 depth) {
	/* TODO */
}

/* AC80 setActorStop */
GS_INLINE void op_setActorStop(gs_Coroutine* coro) {
	/* TODO */
}

/* AC81 setActorDirection */
GS_INLINE void op_setActorDirection(gs_Coroutine* coro, int16 direction) {
	/* TODO */
}

/* AC82 actorTurn */
GS_INLINE void op_actorTurn(gs_Coroutine* coro, int16 direction) {
	/* TODO */
}

/* AC83 setActorWalkScript */
GS_INLINE void op_setActorWalkScript(gs_Coroutine* coro, int16 scriptNum) {
	/* TODO */
}

/* AC84 setActorTalkScript */
GS_INLINE void op_setActorTalkScript(gs_Coroutine* coro, int16 scriptNum) {
	/* TODO */
}

/* AC85 setActorWalkingFrozen */
GS_INLINE void op_setActorWalkingFrozen(gs_Coroutine* coro) {
	/* TODO */
}

/* AC86 setActorWalkingResume */
GS_INLINE void op_setActorWalkingResume(gs_Coroutine* coro) {
	/* TODO */
}

/* AC87 setActorTalkVolume */
GS_INLINE void op_setActorTalkVolume(gs_Coroutine* coro, int32 volume) {
	/* TODO */
}

/* AC88 setActorTalkFrequency */
GS_INLINE void op_setActorTalkFrequency(gs_Coroutine* coro, int32 frequency) {
	/* TODO */
}

/* AC89 setActorTalkPan */
GS_INLINE void op_setActorTalkPan(gs_Coroutine* coro, int32 pan) {
	/* TODO */
}

/* AD32 setCameraPause */
GS_INLINE void op_setCameraPause(gs_Coroutine* coro) {
	/* TODO */
}

/* AD33 setCameraResume */
GS_INLINE void op_setCameraResume(gs_Coroutine* coro) {
	/* TODO */
}

/* AE96 initVerb */
GS_INLINE void op_initVerb(gs_Coroutine* coro, int16 verbNum) {
	/* TODO */
}

/* AE97 newVerb */
GS_INLINE void op_newVerb(gs_Coroutine* coro, int16 verbNum) {
	/* TODO */
}

/* AE98 deleteVerb */
GS_INLINE void op_deleteVerb(gs_Coroutine* coro, int16 verbNum) {
	/* TODO */
}

/* AE99 setVerbName */
GS_INLINE void op_setVerbName(gs_Coroutine* coro, char* name) {
	/* TODO */
}

/* AE9A setVerbXY */
GS_INLINE void op_setVerbXY(gs_Coroutine* coro, int16 x, int16 y) {
	/* TODO */
}

/* AE9B setVerbOn */
GS_INLINE void op_setVerbOn(gs_Coroutine* coro) {
	/* TODO */
}

/* AE9C setVerbOff */
GS_INLINE void op_setVerbOff(gs_Coroutine* coro) {
	/* TODO */
}

/* AE9D setVerbColour */
GS_INLINE void op_setVerbColour(gs_Coroutine* coro, byte colourIndex) {
	/* TODO */
}

/* AE9E setVerbHilightColour */
GS_INLINE void op_setVerbHilightColour(gs_Coroutine* coro, byte colourIndex) {
	/* TODO */
}

/* AEA0 setVerbDimColour */
GS_INLINE void op_setVerbDimColour(gs_Coroutine* coro, byte colourIndex) {
	/* TODO */
}

/* AEA1 setVerbDim */
GS_INLINE void op_setVerbDim(gs_Coroutine* coro) {
	/* TODO */
}

/* AEA2 setVerbKey */
GS_INLINE void op_setVerbKey(gs_Coroutine* coro, byte keyCode) {
	/* TODO */
}

/* AEA3 setVerbImage */
GS_INLINE void op_setVerbImage(gs_Coroutine* coro, int16 objectNum, byte roomNum) {
	/* TODO */
}

/* AEA4 setVerbNameStr */
GS_INLINE void op_setVerbNameStr(gs_Coroutine* coro, int32 textAddress) {
	/* TODO */
}

/* AEA5 setVerbCenter */
GS_INLINE void op_setVerbCenter(gs_Coroutine* coro) {
	/* TODO */
}

/* AEA6 setVerbCharSet */
GS_INLINE void op_setVerbCharSet(gs_Coroutine* coro, byte charSetNum) {
	/* TODO */
}

/* AEA7 setVerbLinesSpacing */
GS_INLINE void op_setVerbLinesSpacing(gs_Coroutine* coro, int16 lineSpacing) {
	/* TODO */
}

/* AF startSound */
GS_PRIVATE GS_INLINE void op_startSound(gs_Coroutine* coro, int32 sound) {
	/* TODO */
}

/* B0 startMusic */
GS_PRIVATE GS_INLINE void op_startMusic(gs_Coroutine* coro, int32 sound) {
	/* TODO */
}

/* B1 stopSound */
GS_PRIVATE GS_INLINE void op_stopSound(gs_Coroutine* coro, int32 sound) {
	/* TODO */
}

/* B2 soundKludge */
GS_PRIVATE GS_INLINE void op_soundKludge(gs_Coroutine* coro, int32 argsLength, int32* args) {
	/* TODO */
}

/* B39E restartGame */
GS_INLINE void op_restartGame(gs_Coroutine* coro) {
	/* TODO */
}

/* B39F pauseGame */
GS_INLINE void op_pauseGame(gs_Coroutine* coro) {
	/* TODO */
}

/* B3A0 quitGame */
GS_INLINE void op_quitGame(gs_Coroutine* coro) {
	/* TODO */
}

/* B4 saveRestoreVerbs */
GS_PRIVATE GS_INLINE void op_saveRestoreVerbs(gs_Coroutine* coro, int32 a, int32 b, int32 c) {
	/* TODO */
}

/* B5 setObjectName */
GS_PRIVATE GS_INLINE void op_setObjectName(gs_Coroutine* coro, int32 obj, char* name) {
	/* TODO */
}

/* B6 getDateTime */
GS_PRIVATE GS_INLINE void op_getDateTime(gs_Coroutine* coro) {
	/* TODO */
}

/* B7 drawBox */
GS_PRIVATE GS_INLINE void op_drawBox(gs_Coroutine* coro, int32 x, int32 y, int32 x2, int32 y2, int32 color) {
	/* TODO */
}

/* B9 startVideo */
GS_PRIVATE GS_INLINE void op_startVideo(gs_Coroutine* coro, char* fileName) {
	/* TODO */
}

/* BA0B lockObject */
GS_INLINE void op_lockObject(gs_Coroutine* coro, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA0C unlockObject */
GS_INLINE void op_unlockObject(gs_Coroutine* coro, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA0D remapCostumePalette */
GS_INLINE void op_remapCostumePalette(gs_Coroutine* coro, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA0E remapCostumeInsert */
GS_INLINE void op_remapCostumeInsert(gs_Coroutine* coro, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA0F setVideoFrameRate */
GS_INLINE void op_setVideoFrameRate(gs_Coroutine* coro, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA14 setBoxScaleSlot */
GS_INLINE void op_setBoxScaleSlot(gs_Coroutine* coro, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA15 setScaleSlot */
GS_INLINE void op_setScaleSlot(gs_Coroutine* coro, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA16 setBannerColours */
GS_INLINE void op_setBannerColours(gs_Coroutine* coro, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA17 setActorChoreLimbFrame */
GS_INLINE void op_setActorChoreLimbFrame(gs_Coroutine* coro, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA18 clearTextQueue */
GS_INLINE void op_clearTextQueue(gs_Coroutine* coro, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA19 saveGameReadName */
GS_INLINE void op_saveGameReadName(gs_Coroutine* coro, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA1A saveGameWrite */
GS_INLINE void op_saveGameWrite(gs_Coroutine* coro, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA1B saveGameRead */
GS_INLINE void op_saveGameRead(gs_Coroutine* coro, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA1C saveGameScreenshot */
GS_INLINE void op_saveGameScreenshot(gs_Coroutine* coro, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA1D setKeyScript */
GS_INLINE void op_setKeyScript(gs_Coroutine* coro, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA1E killAllScriptsExceptCurrent */
GS_INLINE void op_killAllScriptsExceptCurrent(gs_Coroutine* coro, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA1F stopAllVideo */
GS_INLINE void op_stopAllVideo(gs_Coroutine* coro, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA20 writeRegistryValue */
GS_INLINE void op_writeRegistryValue(gs_Coroutine* coro, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA21 setPaletteIntensity */
GS_INLINE void op_setPaletteIntensity(gs_Coroutine* coro, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA22 queryQuit */
GS_INLINE void op_queryQuit(gs_Coroutine* coro, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA6C buildPaletteShadow */
GS_INLINE void op_buildPaletteShadow(gs_Coroutine* coro, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA6D setPaletteShadow */
GS_INLINE void op_setPaletteShadow(gs_Coroutine* coro, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA6E blastShadowObject */
GS_INLINE void op_blastShadowObject(gs_Coroutine* coro, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA6F superBlastObject */
GS_INLINE void op_superBlastObject(gs_Coroutine* coro, int32 argsLength, int32* args) {
	/* TODO */
}

/* C0 dim2DimArray */
GS_PRIVATE GS_INLINE void op_dim2DimArray(gs_Coroutine* coro, int32 dim2, int32 dim1) {
	/* TODO */
}

/* C6 distObjectPt */
GS_PRIVATE GS_INLINE void op_distObjectPt(gs_Coroutine* coro, int32 a, int32 b, int32 c) {
	/* TODO */
}

/* C8 startScriptQuick2 */
GS_PRIVATE GS_INLINE void op_startScriptQuick2(gs_Coroutine* coro, int32 script, int32 argsLength, int32* args) {
	/* TODO */
}

/* C9 startObjectQuick */
GS_PRIVATE GS_INLINE void op_startObjectQuick(gs_Coroutine* coro, int32 script, byte entryPc, int32 argsLength, int32* args) {
	/* TODO */
}

/* CA pickOneOf */
GS_PRIVATE GS_INLINE void op_pickOneOf(gs_Coroutine* coro, int32 i, int32 argsLength, int32* args) {
	/* TODO */
}

/* CB pickOneOfDefault */
GS_PRIVATE GS_INLINE void op_pickOneOfDefault(gs_Coroutine* coro, int32 i, int32 argsLength, int32* args, int32 def) {
	/* TODO */
}

/* CD isAnyOf */
GS_PRIVATE GS_INLINE void op_isAnyOf(gs_Coroutine* coro, int32 value, int32 argsLength, int32* args) {
	/* TODO */
}

/* CE getRandomNumber */
GS_PRIVATE GS_INLINE void op_getRandomNumber(gs_Coroutine* coro, int32 max) {
	/* TODO */
}

/* CF getRandomNumberRange */
GS_PRIVATE GS_INLINE void op_getRandomNumberRange(gs_Coroutine* coro, int32 min, int32 max) {
	/* TODO */
}

/* D0 ifClassOfIs */
GS_PRIVATE GS_INLINE void op_ifClassOfIs(gs_Coroutine* coro, int32 obj, int32 argsLength, int32* args) {
	/* TODO */
}

/* D1 getState */
GS_PRIVATE GS_INLINE void op_getState(gs_Coroutine* coro, int32 obj) {
	/* TODO */
}

/* D2 getOwner */
GS_PRIVATE GS_INLINE void op_getOwner(gs_Coroutine* coro, int32 obj) {
	/* TODO */
}

/* D3 isScriptRunning */
GS_PRIVATE GS_INLINE void op_isScriptRunning(gs_Coroutine* coro, int32 script) {
	/* TODO */
}

/* D4 shuffle */
GS_PRIVATE GS_INLINE void op_shuffle(gs_Coroutine* coro, int32 left, int32 right) {
	/* TODO */
}

/* D5 isSoundRunning */
GS_PRIVATE GS_INLINE void op_isSoundRunning(gs_Coroutine* coro, int32 sound) {
	/* TODO */
}

/* D6 abs */
GS_PRIVATE GS_INLINE void op_abs(gs_Coroutine* coro, int32 value) {
	/* TODO */
}

/* D873 getWalkBoxAt */
GS_INLINE void op_getWalkBoxAt(gs_Coroutine* coro, int32 args) {
	/* TODO */
}

/* D874 isPointInBox */
GS_INLINE void op_isPointInBox(gs_Coroutine* coro, int32 args) {
	/* TODO */
}

/* D8CE getRGBSlot */
GS_INLINE void op_getRGBSlot(gs_Coroutine* coro, int32 args) {
	/* TODO */
}

/* D8D3 getKeyState */
GS_INLINE void op_getKeyState(gs_Coroutine* coro, int32 args) {
	/* TODO */
}

/* D8D7 getBox */
GS_INLINE void op_getBox(gs_Coroutine* coro, int32 args) {
	/* TODO */
}

/* D8D8 findBlastObject */
GS_INLINE void op_findBlastObject(gs_Coroutine* coro, int32 args) {
	/* TODO */
}

/* D8D9 actorHitTest */
GS_INLINE void op_actorHitTest(gs_Coroutine* coro, int32 args) {
	/* TODO */
}

/* D8DA setLipSyncWidth */
GS_INLINE void op_setLipSyncWidth(gs_Coroutine* coro, int32 args) {
	/* TODO */
}

/* D8DB setLipSyncHeight */
GS_INLINE void op_setLipSyncHeight(gs_Coroutine* coro, int32 args) {
	/* TODO */
}

/* D8DC setTalkAnimation */
GS_INLINE void op_setTalkAnimation(gs_Coroutine* coro, int32 args) {
	/* TODO */
}

/* D8DD getGroupSfxVol */
GS_INLINE void op_getGroupSfxVol(gs_Coroutine* coro, int32 args) {
	/* TODO */
}

/* D8DE getGroupVoiceVol */
GS_INLINE void op_getGroupVoiceVol(gs_Coroutine* coro, int32 args) {
	/* TODO */
}

/* D8DF getGroupMusicVol */
GS_INLINE void op_getGroupMusicVol(gs_Coroutine* coro, int32 args) {
	/* TODO */
}

/* D8E0 readRegistryValue */
GS_INLINE void op_readRegistryValue(gs_Coroutine* coro, int32 args) {
	/* TODO */
}

/* D8E1 imuseGetMusicPosition */
GS_INLINE void op_imuseGetMusicPosition(gs_Coroutine* coro, int32 args) {
	/* TODO */
}

/* D8E2 imuseGetMusicLipSyncWidth */
GS_INLINE void op_imuseGetMusicLipSyncWidth(gs_Coroutine* coro, int32 args) {
	/* TODO */
}

/* D8E3 imuseGetMusicLipSyncHeight */
GS_INLINE void op_imuseGetMusicLipSyncHeight(gs_Coroutine* coro, int32 args) {
	/* TODO */
}

/* D9 isActorInBox */
GS_PRIVATE GS_INLINE void op_isActorInBox(gs_Coroutine* coro, int32 index, int32 box) {
	/* TODO */
}

/* DA getVerbEntrypoint */
GS_PRIVATE GS_INLINE void op_getVerbEntrypoint(gs_Coroutine* coro, int32 verb, int32 entryp) {
	/* TODO */
}

/* DB getActorFromXY */
GS_PRIVATE GS_INLINE void op_getActorFromXY(gs_Coroutine* coro, int32 x, int32 y) {
	/* TODO */
}

/* DC findObject */
GS_PRIVATE GS_INLINE void op_findObject(gs_Coroutine* coro, int32 x, int32 y) {
	/* TODO */
}

/* DD getVerbFromXY */
GS_PRIVATE GS_INLINE void op_getVerbFromXY(gs_Coroutine* coro, int32 x, int32 y) {
	/* TODO */
}

/* DF findInventory */
GS_PRIVATE GS_INLINE void op_findInventory(gs_Coroutine* coro, int32 owner, int32 index) {
	/* TODO */
}

/* E0 getInventoryCount */
GS_PRIVATE GS_INLINE void op_getInventoryCount(gs_Coroutine* coro, int32 owner) {
	/* TODO */
}

/* E1 getAnimateVariable */
GS_PRIVATE GS_INLINE void op_getAnimateVariable(gs_Coroutine* coro, int32 index, int32 variable) {
	/* TODO */
}

/* E2 getActorRoom */
GS_PRIVATE GS_INLINE void op_getActorRoom(gs_Coroutine* coro, int32 index) {
	/* TODO */
}

/* E3 getActorWalkBox */
GS_PRIVATE GS_INLINE void op_getActorWalkBox(gs_Coroutine* coro, int32 index) {
	/* TODO */
}

/* E4 getActorMoving */
GS_PRIVATE GS_INLINE void op_getActorMoving(gs_Coroutine* coro, int32 index) {
	/* TODO */
}

/* E5 getActorCostume */
GS_PRIVATE GS_INLINE void op_getActorCostume(gs_Coroutine* coro, int32 index) {
	/* TODO */
}

/* E6 getActorScaleX */
GS_PRIVATE GS_INLINE void op_getActorScaleX(gs_Coroutine* coro, int32 index) {
	/* TODO */
}

/* E7 getActorLayer */
GS_PRIVATE GS_INLINE void op_getActorLayer(gs_Coroutine* coro, int32 index) {
	/* TODO */
}

/* E8 getActorElevation */
GS_PRIVATE GS_INLINE void op_getActorElevation(gs_Coroutine* coro, int32 index) {
	/* TODO */
}

/* E9 getActorWidth */
GS_PRIVATE GS_INLINE void op_getActorWidth(gs_Coroutine* coro, int32 index) {
	/* TODO */
}

/* EA getObjectNewDir */
GS_PRIVATE GS_INLINE void op_getObjectNewDir(gs_Coroutine* coro, int32 index) {
	/* TODO */
}

/* EB getObjectX */
GS_PRIVATE GS_INLINE void op_getObjectX(gs_Coroutine* coro, int32 index) {
	/* TODO */
}

/* EC getObjectY */
GS_PRIVATE GS_INLINE void op_getObjectY(gs_Coroutine* coro, int32 index) {
	/* TODO */
}

/* ED getActorChore */
GS_PRIVATE GS_INLINE void op_getActorChore(gs_Coroutine* coro, int16 actorNum) {
	/* TODO */
}

/* EE distObjectObject */
GS_PRIVATE GS_INLINE void op_distObjectObject(gs_Coroutine* coro, int32 left, int32 right) {
	/* TODO */
}

/* EF distObjectPtPt */
GS_PRIVATE GS_INLINE void op_distObjectPtPt(gs_Coroutine* coro, int32 a, int32 b, int32 c, int32 d) {
	/* TODO */
}

/* F0 getObjectImageX */
GS_PRIVATE GS_INLINE void op_getObjectImageX(gs_Coroutine* coro, int16 objectNum) {
	/* TODO */
}

/* F1 getObjectImageY */
GS_PRIVATE GS_INLINE void op_getObjectImageY(gs_Coroutine* coro, int16 objectNum) {
	/* TODO */
}

/* F2 getObjectImageWidth */
GS_PRIVATE GS_INLINE void op_getObjectImageWidth(gs_Coroutine* coro, int16 objectNum) {
	/* TODO */
}

/* F3 getObjectImageHeight */
GS_PRIVATE GS_INLINE void op_getObjectImageHeight(gs_Coroutine* coro, int16 objectNum) {
	/* TODO */
}

/* F6 getStringWidth */
GS_PRIVATE GS_INLINE void op_getStringWidth(gs_Coroutine* coro, char* text, int16 charsetNum) {
	/* TODO */
}

/* F7 getActorZPlane */
GS_PRIVATE GS_INLINE void op_getActorZPlane(gs_Coroutine* coro, int16 actorNum) {
	/* TODO */
}





void gs_ScriptDecode_GS8(gs_Coroutine* coro, byte op1, byte op2)
{
	switch(op1)
	{
		default:
			return 1;
		/* pushByte */
		case 0x00:
		{
			byte value = readByte();
			op_pushByte(value);
		}
		return 0;
		/* pushWord */
		case 0x01:
		{
			int32 value = readLong();
			op_pushWord(value);
		}
		return 0;
		/* pushWordVar */
		case 0x02:
		{
			int32 name = readLong();
			op_pushWordVar(name);
		}
		return 0;
		/* wordArrayRead */
		case 0x03:
		{
			int32 base = pullStackLong();
			op_wordArrayRead(base);
		}
		return 0;
		/* wordArrayIndexedRead */
		case 0x04:
		{
			int32 arrayNum = readLong();
			int32 base = pullStackLong();
			int32 index = pullStackLong();
			op_wordArrayIndexedRead(index, base, arrayNum);
		}
		return 0;
		/* dup */
		case 0x05:
		{
			int32 value = pullStackLong();
			op_dup(value);
		}
		return 0;
		/* pop */
		case 0x06:
		{
			int32 discard = pullStackLong();
			op_pop(discard);
		}
		return 0;
		/* not */
		case 0x07:
		{
			int32 value = pullStackLong();
			op_not(value);
		}
		return 0;
		/* eq */
		case 0x08:
		{
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_eq(left, right);
		}
		return 0;
		/* neq */
		case 0x09:
		{
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_neq(left, right);
		}
		return 0;
		/* gt */
		case 0x0A:
		{
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_gt(left, right);
		}
		return 0;
		/* lt */
		case 0x0B:
		{
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_lt(left, right);
		}
		return 0;
		/* le */
		case 0x0C:
		{
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_le(left, right);
		}
		return 0;
		/* ge */
		case 0x0D:
		{
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_ge(left, right);
		}
		return 0;
		/* add */
		case 0x0E:
		{
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_add(left, right);
		}
		return 0;
		/* sub */
		case 0x0F:
		{
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_sub(left, right);
		}
		return 0;
		/* mul */
		case 0x10:
		{
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_mul(left, right);
		}
		return 0;
		/* div */
		case 0x11:
		{
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_div(left, right);
		}
		return 0;
		/* land */
		case 0x12:
		{
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_land(left, right);
		}
		return 0;
		/* lor */
		case 0x13:
		{
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_lor(left, right);
		}
		return 0;
		/* band */
		case 0x14:
		{
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_band(left, right);
		}
		return 0;
		/* bor */
		case 0x15:
		{
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_bor(left, right);
		}
		return 0;
		/* mod */
		case 0x16:
		{
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_mod(left, right);
		}
		return 0;
		/* writeByteVar */
		case 0x42:
		{
			int32 value = pullStackLong();
			op_writeByteVar(value);
		}
		return 0;
		/* byteArrayWrite */
		case 0x46:
		{
			int32 value = pullStackLong();
			int32 base = pullStackLong();
			op_byteArrayWrite(base, value);
		}
		return 0;
		/* byteArrayIndexedWrite */
		case 0x4A:
		{
			int32 value = pullStackLong();
			int32 base = pullStackLong();
			int32 index = pullStackLong();
			op_byteArrayIndexedWrite(index, base, value);
		}
		return 0;
		/* byteVarInc */
		case 0x4E:
		{
			op_byteVarInc();
		}
		return 0;
		/* byteArrayInc */
		case 0x52:
		{
			int32 base = pullStackLong();
			op_byteArrayInc(base);
		}
		return 0;
		/* byteVarDec */
		case 0x56:
		{
			op_byteVarDec();
		}
		return 0;
		/* byteArrayDec */
		case 0x5A:
		{
			int32 base = pullStackLong();
			op_byteArrayDec(base);
		}
		return 0;
		/* drawObject */
		case 0x61:
		{
			int32 state = pullStackLong();
			int32 obj = pullStackLong();
			op_drawObject(obj, state);
		}
		return 0;
		/* drawObjectAt */
		case 0x62:
		{
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			int32 obj = pullStackLong();
			op_drawObjectAt(obj, x, y);
		}
		return 0;
		/* drawBlastObject */
		case 0x63:
		{
			int32 argsLength = pullStack();
			int32* args = pullList(listLength, 25);
			int32 e = pullStackLong();
			int32 d = pullStackLong();
			int32 c = pullStackLong();
			int32 b = pullStackLong();
			int32 a = pullStackLong();
			op_drawBlastObject(a, b, c, d, e, args);
		}
		return 0;
		/* if */
		case 0x64:
		{
			int32 offset = readLong();
			int32 condition = pullStackLong();
			op_if(condition, offset);
		}
		return 0;
		/* ifNot */
		case 0x65:
		{
			int32 offset = readLong();
			int32 condition = pullStackLong();
			op_ifNot(condition, offset);
		}
		return 0;
		/* jump */
		case 0x66:
		{
			int32 offset = readLong();
			op_jump(offset);
		}
		return 0;
		/* breakHere */
		case 0x67:
		{
			op_breakHere();
		}
		return 0;
		/* delayFrames */
		case 0x68:
		{
			op_delayFrames();
		}
		return 0;
		case 0x69:
		{
			consumeByte();
			switch(op2)
			{
				default:
					return 1;
				/* waitActor */
				case 0x1E:
				{
					int32 actorNum = pullStackLong();
					int32 offset = readLong();
					op_waitActor(offset, actorNum);
				}
				return 0;
				/* waitMessage */
				case 0x1F:
				{
					op_waitMessage();
				}
				return 0;
				/* waitCamera */
				case 0x20:
				{
					op_waitCamera();
				}
				return 0;
				/* waitSentence */
				case 0x21:
				{
					op_waitSentence();
				}
				return 0;
				/* waitAnimation */
				case 0x22:
				{
					op_waitAnimation();
				}
				return 0;
				/* waitTurn */
				case 0x23:
				{
					int32 actorNum = pullStackLong();
					int32 offset = readLong();
					op_waitTurn(offset, actorNum);
				}
				return 0;
		}
		return 0;
		/* delay */
		case 0x6A:
		{
			int32 delay = pullStackLong();
			op_delay(delay);
		}
		return 0;
		/* delaySeconds */
		case 0x6B:
		{
			int32 seconds = pullStackLong();
			op_delaySeconds(seconds);
		}
		return 0;
		/* delayMinutes */
		case 0x6C:
		{
			int32 minutes = pullStackLong();
			op_delayMinutes(minutes);
		}
		return 0;
		/* writeWordVar */
		case 0x6D:
		{
			int32 value = pullStackLong();
			op_writeWordVar(value);
		}
		return 0;
		/* wordVarInc */
		case 0x6E:
		{
			int32 var = readLong();
			op_wordVarInc(var);
		}
		return 0;
		/* wordVarDec */
		case 0x6F:
		{
			int32 var = readLong();
			op_wordVarDec(var);
		}
		return 0;
		case 0x70:
		{
			consumeByte();
			switch(op2)
			{
				default:
					return 1;
				/* newArrayInt */
				case 0x0A:
				{
					int32 dim1 = pullStackLong();
					int32 arrayNum = readLong();
					op_newArrayInt(arrayNum, dim1);
				}
				return 0;
				/* newArrayString */
				case 0x0B:
				{
					int32 dim1 = pullStackLong();
					int32 arrayNum = readLong();
					op_newArrayString(arrayNum, dim1);
				}
				return 0;
				/* deleteArray */
				case 0x0C:
				{
					int32 arrayNum = readLong();
					op_deleteArray(arrayNum);
				}
				return 0;
		}
		return 0;
		/* wordArrayWrite */
		case 0x71:
		{
			int32 value = pullStackLong();
			int32 base = pullStackLong();
			op_wordArrayWrite(base, value);
		}
		return 0;
		/* wordArrayInc */
		case 0x72:
		{
			int32 base = pullStackLong();
			op_wordArrayInc(base);
		}
		return 0;
		/* wordArrayDec */
		case 0x73:
		{
			int32 base = pullStackLong();
			op_wordArrayDec(base);
		}
		return 0;
		case 0x74:
		{
			consumeByte();
			switch(op2)
			{
				default:
					return 1;
				/* newArray2Int */
				case 0x0A:
				{
					int32 dim2 = pullStackLong();
					int32 dim1 = pullStackLong();
					int32 arrayNum = readLong();
					op_newArray2Int(arrayNum, dim1, dim2);
				}
				return 0;
				/* newArray2String */
				case 0x0B:
				{
					int32 dim2 = pullStackLong();
					int32 dim1 = pullStackLong();
					int32 arrayNum = readLong();
					op_newArray2String(arrayNum, dim1, dim2);
				}
				return 0;
				/* deleteArray2 */
				case 0x0C:
				{
					int32 arrayNum = readLong();
					op_deleteArray2(arrayNum);
				}
				return 0;
		}
		return 0;
		/* wordArrayIndexedWrite */
		case 0x75:
		{
			int32 arrayNum = readLong();
			int32 value = pullStackLong();
			int32 base = pullStackLong();
			int32 index = pullStackLong();
			op_wordArrayIndexedWrite(index, base, value, arrayNum);
		}
		return 0;
		case 0x76:
		{
			consumeByte();
			switch(op2)
			{
				default:
					return 1;
				/* setArrayString */
				case 0x14:
				{
					int32 arrayNum = readLong();
					int32 offset = pullStackLong();
					char* string = readText();
					op_setArrayString(string, offset, arrayNum);
				}
				return 0;
				/* setArrayList */
				case 0x15:
				{
					int32 arrayNum = readLong();
					int32 offset = pullStackLong();
					int32 listLength = pullStack();
					int32* list = pullList(listLength, 25);
					op_setArrayList(list, offset, arrayNum);
				}
				return 0;
				/* setArray2List */
				case 0x16:
				{
					int32 arrayNum = readLong();
					int32 offset = pullStackLong();
					int32 listLength = pullStack();
					int32* list = pullList(listLength, 25);
					op_setArray2List(list, offset, arrayNum);
				}
				return 0;
		}
		return 0;
		/* startScript */
		case 0x79:
		{
			int32 argsLength = pullStack();
			int32* args = pullList(listLength, 25);
			int32 script = pullStackLong();
			int32 flags = pullStackLong();
			op_startScript(flags, script, args);
		}
		return 0;
		/* startScriptQuick */
		case 0x7A:
		{
			int32 argsLength = pullStack();
			int32* args = pullList(listLength, 25);
			int32 script = pullStackLong();
			op_startScriptQuick(script, args);
		}
		return 0;
		/* stopObjectCode */
		case 0x7B:
		{
			op_stopObjectCode();
		}
		return 0;
		/* stopScript */
		case 0x7C:
		{
			int32 scriptNum = pullStackLong();
			op_stopScript(scriptNum);
		}
		return 0;
		/* jumpToScript */
		case 0x7D:
		{
			int32 argsLength = pullStack();
			int32* args = pullList(listLength, 25);
			int32 scriptNum = pullStackLong();
			int32 flags = pullStackLong();
			op_jumpToScript(flags, scriptNum, args);
		}
		return 0;
		/* dummy */
		case 0x7E:
		{
			op_dummy();
		}
		return 0;
		/* startObject */
		case 0x7F:
		{
			int32 argsLength = pullStack();
			int32* args = pullList(listLength, 25);
			byte entryp = pullStackByte();
			int32 script = pullStackLong();
			int32 flags = pullStackLong();
			op_startObject(flags, script, entryp, args);
		}
		return 0;
		/* stopObjectScript */
		case 0x80:
		{
			int16 script = pullStackWord();
			op_stopObjectScript(script);
		}
		return 0;
		/* cutscene */
		case 0x81:
		{
			int32 argsLength = pullStack();
			int32* args = pullList(listLength, 25);
			op_cutscene(args);
		}
		return 0;
		/* endCutscene */
		case 0x82:
		{
			op_endCutscene();
		}
		return 0;
		/* freezeUnfreeze */
		case 0x83:
		{
			int32 script = pullStackLong();
			op_freezeUnfreeze(script);
		}
		return 0;
		/* beginOverride */
		case 0x84:
		{
			op_beginOverride();
		}
		return 0;
		/* endOverride */
		case 0x85:
		{
			op_endOverride();
		}
		return 0;
		/* stopSentence */
		case 0x86:
		{
			op_stopSentence();
		}
		return 0;
		/* setClass */
		case 0x89:
		{
			int32 argsLength = pullStack();
			int32* args = pullList(listLength, 25);
			int32 obj = pullStackLong();
			op_setClass(obj, args);
		}
		return 0;
		/* setState */
		case 0x8A:
		{
			int32 state = pullStackLong();
			int32 obj = pullStackLong();
			op_setState(obj, state);
		}
		return 0;
		/* setOwner */
		case 0x8B:
		{
			int32 owner = pullStackLong();
			int32 obj = pullStackLong();
			op_setOwner(obj, owner);
		}
		return 0;
		/* panCameraTo */
		case 0x8C:
		{
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			op_panCameraTo(x, y);
		}
		return 0;
		/* actorFollowCamera */
		case 0x8D:
		{
			int32 index = pullStackLong();
			op_actorFollowCamera(index);
		}
		return 0;
		/* setCameraAt */
		case 0x8E:
		{
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			op_setCameraAt(x, y);
		}
		return 0;
		case 0x8F:
		{
			consumeByte();
			switch(op2)
			{
				default:
					return 1;
				/* printActorAt */
				case 0x41:
				{
					int32 y = pullStackLong();
					int32 x = pullStackLong();
					op_printActorAt(x, y);
				}
				return 0;
				/* printActorColour */
				case 0x42:
				{
					int32 col = pullStackLong();
					op_printActorColour(col);
				}
				return 0;
				/* printActorClipped */
				case 0x43:
				{
					int32 right = pullStackLong();
					op_printActorClipped(right);
				}
				return 0;
				/* printActorCentre */
				case 0x45:
				{
					op_printActorCentre();
				}
				return 0;
				/* printActorLeft */
				case 0x47:
				{
					op_printActorLeft();
				}
				return 0;
				/* printActorOverhead */
				case 0x48:
				{
					op_printActorOverhead();
				}
				return 0;
				/* printActorMumble */
				case 0x4A:
				{
					op_printActorMumble();
				}
				return 0;
				/* printActorText */
				case 0x4B:
				{
					char* text = readText();
					op_printActorText(text);
				}
				return 0;
				/* printActorLoadDefault */
				case 0xFE:
				{
					int32 actorNum = pullStackLong();
					op_printActorLoadDefault(actorNum);
				}
				return 0;
				/* printActorSaveDefault */
				case 0xFF:
				{
					op_printActorSaveDefault();
				}
				return 0;
		}
		return 0;
		case 0x90:
		{
			consumeByte();
			switch(op2)
			{
				default:
					return 1;
				/* printEgoAt */
				case 0x41:
				{
					int32 y = pullStackLong();
					int32 x = pullStackLong();
					op_printEgoAt(x, y);
				}
				return 0;
				/* printEgoColour */
				case 0x42:
				{
					int32 col = pullStackLong();
					op_printEgoColour(col);
				}
				return 0;
				/* printEgoClipped */
				case 0x43:
				{
					int32 right = pullStackLong();
					op_printEgoClipped(right);
				}
				return 0;
				/* printEgoCentre */
				case 0x45:
				{
					op_printEgoCentre();
				}
				return 0;
				/* printEgoLeft */
				case 0x47:
				{
					op_printEgoLeft();
				}
				return 0;
				/* printEgoOverhead */
				case 0x48:
				{
					op_printEgoOverhead();
				}
				return 0;
				/* printEgoMumble */
				case 0x4A:
				{
					op_printEgoMumble();
				}
				return 0;
				/* printEgoText */
				case 0x4B:
				{
					char* text = readText();
					op_printEgoText(text);
				}
				return 0;
				/* printEgoLoadDefault */
				case 0xFE:
				{
					int32 actorNum = pullStackLong();
					op_printEgoLoadDefault(actorNum);
				}
				return 0;
				/* printEgoSaveDefault */
				case 0xFF:
				{
					op_printEgoSaveDefault();
				}
				return 0;
		}
		return 0;
		/* talkActor */
		case 0x91:
		{
			int32 actor = pullStackLong();
			char* text = readText();
			op_talkActor(text, actor);
		}
		return 0;
		/* talkEgo */
		case 0x92:
		{
			char* text = readText();
			op_talkEgo(text);
		}
		return 0;
		case 0x93:
		{
			consumeByte();
			switch(op2)
			{
				default:
					return 1;
				/* printLineAt */
				case 0x41:
				{
					int32 y = pullStackLong();
					int32 x = pullStackLong();
					op_printLineAt(x, y);
				}
				return 0;
				/* printLineColour */
				case 0x42:
				{
					int32 col = pullStackLong();
					op_printLineColour(col);
				}
				return 0;
				/* printLineClipped */
				case 0x43:
				{
					int32 right = pullStackLong();
					op_printLineClipped(right);
				}
				return 0;
				/* printLineCentre */
				case 0x45:
				{
					op_printLineCentre();
				}
				return 0;
				/* printLineLeft */
				case 0x47:
				{
					op_printLineLeft();
				}
				return 0;
				/* printLineOverhead */
				case 0x48:
				{
					op_printLineOverhead();
				}
				return 0;
				/* printLineMumble */
				case 0x4A:
				{
					op_printLineMumble();
				}
				return 0;
				/* printLineText */
				case 0x4B:
				{
					char* text = readText();
					op_printLineText(text);
				}
				return 0;
				/* printLineLoadDefault */
				case 0xFE:
				{
					op_printLineLoadDefault();
				}
				return 0;
				/* printLineSaveDefault */
				case 0xFF:
				{
					op_printLineSaveDefault();
				}
				return 0;
		}
		return 0;
		case 0x94:
		{
			consumeByte();
			switch(op2)
			{
				default:
					return 1;
				/* printTextAt */
				case 0x41:
				{
					int32 y = pullStackLong();
					int32 x = pullStackLong();
					op_printTextAt(x, y);
				}
				return 0;
				/* printTextColour */
				case 0x42:
				{
					int32 col = pullStackLong();
					op_printTextColour(col);
				}
				return 0;
				/* printTextClipped */
				case 0x43:
				{
					int32 right = pullStackLong();
					op_printTextClipped(right);
				}
				return 0;
				/* printTextCentre */
				case 0x45:
				{
					op_printTextCentre();
				}
				return 0;
				/* printTextLeft */
				case 0x47:
				{
					op_printTextLeft();
				}
				return 0;
				/* printTextOverhead */
				case 0x48:
				{
					op_printTextOverhead();
				}
				return 0;
				/* printTextMumble */
				case 0x4A:
				{
					op_printTextMumble();
				}
				return 0;
				/* printTextText */
				case 0x4B:
				{
					char* text = readText();
					op_printTextText(text);
				}
				return 0;
				/* printTextLoadDefault */
				case 0xFE:
				{
					op_printTextLoadDefault();
				}
				return 0;
				/* printTextSaveDefault */
				case 0xFF:
				{
					op_printTextSaveDefault();
				}
				return 0;
		}
		return 0;
		case 0x95:
		{
			consumeByte();
			switch(op2)
			{
				default:
					return 1;
				/* printDebugAt */
				case 0x41:
				{
					int32 y = pullStackLong();
					int32 x = pullStackLong();
					op_printDebugAt(x, y);
				}
				return 0;
				/* printDebugColour */
				case 0x42:
				{
					int32 col = pullStackLong();
					op_printDebugColour(col);
				}
				return 0;
				/* printDebugClipped */
				case 0x43:
				{
					int32 right = pullStackLong();
					op_printDebugClipped(right);
				}
				return 0;
				/* printDebugCentre */
				case 0x45:
				{
					op_printDebugCentre();
				}
				return 0;
				/* printDebugLeft */
				case 0x47:
				{
					op_printDebugLeft();
				}
				return 0;
				/* printDebugOverhead */
				case 0x48:
				{
					op_printDebugOverhead();
				}
				return 0;
				/* printDebugMumble */
				case 0x4A:
				{
					op_printDebugMumble();
				}
				return 0;
				/* printDebugText */
				case 0x4B:
				{
					char* text = readText();
					op_printDebugText(text);
				}
				return 0;
				/* printDebugLoadDefault */
				case 0xFE:
				{
					op_printDebugLoadDefault();
				}
				return 0;
				/* printDebugSaveDefault */
				case 0xFF:
				{
					op_printDebugSaveDefault();
				}
				return 0;
		}
		return 0;
		case 0x96:
		{
			consumeByte();
			switch(op2)
			{
				default:
					return 1;
				/* printSystemAt */
				case 0x41:
				{
					int32 y = pullStackLong();
					int32 x = pullStackLong();
					op_printSystemAt(x, y);
				}
				return 0;
				/* printSystemColour */
				case 0x42:
				{
					int32 col = pullStackLong();
					op_printSystemColour(col);
				}
				return 0;
				/* printSystemClipped */
				case 0x43:
				{
					int32 right = pullStackLong();
					op_printSystemClipped(right);
				}
				return 0;
				/* printSystemCentre */
				case 0x45:
				{
					op_printSystemCentre();
				}
				return 0;
				/* printSystemLeft */
				case 0x47:
				{
					op_printSystemLeft();
				}
				return 0;
				/* printSystemOverhead */
				case 0x48:
				{
					op_printSystemOverhead();
				}
				return 0;
				/* printSystemMumble */
				case 0x4A:
				{
					op_printSystemMumble();
				}
				return 0;
				/* printSystemText */
				case 0x4B:
				{
					char* text = readText();
					op_printSystemText(text);
				}
				return 0;
				/* printSystemLoadDefault */
				case 0xFE:
				{
					op_printSystemLoadDefault();
				}
				return 0;
				/* printSystemSaveDefault */
				case 0xFF:
				{
					op_printSystemSaveDefault();
				}
				return 0;
		}
		return 0;
		case 0x97:
		{
			consumeByte();
			switch(op2)
			{
				default:
					return 1;
				/* blastTextAt */
				case 0x41:
				{
					int32 y = pullStackLong();
					int32 x = pullStackLong();
					op_blastTextAt(x, y);
				}
				return 0;
				/* blastTextColour */
				case 0x42:
				{
					int32 col = pullStackLong();
					op_blastTextColour(col);
				}
				return 0;
				/* blastTextClipped */
				case 0x43:
				{
					int32 right = pullStackLong();
					op_blastTextClipped(right);
				}
				return 0;
				/* blastTextCentre */
				case 0x45:
				{
					op_blastTextCentre();
				}
				return 0;
				/* blastTextLeft */
				case 0x47:
				{
					op_blastTextLeft();
				}
				return 0;
				/* blastTextOverhead */
				case 0x48:
				{
					op_blastTextOverhead();
				}
				return 0;
				/* blastTextMumble */
				case 0x4A:
				{
					op_blastTextMumble();
				}
				return 0;
				/* blastTextText */
				case 0x4B:
				{
					char* text = readText();
					op_blastTextText(text);
				}
				return 0;
				/* blastTextLoadDefault */
				case 0xFE:
				{
					op_blastTextLoadDefault();
				}
				return 0;
				/* blastTextSaveDefault */
				case 0xFF:
				{
					op_blastTextSaveDefault();
				}
				return 0;
		}
		return 0;
		/* drawObject */
		case 0x98:
		{
			int32 state = pullStackLong();
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			int32 obj = pullStackLong();
			op_drawObject(obj, x, y, state);
		}
		return 0;
		case 0x9C:
		{
			consumeByte();
			switch(op2)
			{
				default:
					return 1;
				/* cursorOn */
				case 0xDC:
				{
					op_cursorOn();
				}
				return 0;
				/* cursorOff */
				case 0xDD:
				{
					op_cursorOff();
				}
				return 0;
				/* cursorSoftOn */
				case 0xDE:
				{
					op_cursorSoftOn();
				}
				return 0;
				/* cursorSoftOff */
				case 0xDF:
				{
					op_cursorSoftOff();
				}
				return 0;
				/* cursorUserPutOn */
				case 0xE0:
				{
					op_cursorUserPutOn();
				}
				return 0;
				/* cursorUserPutOff */
				case 0xE1:
				{
					op_cursorUserPutOff();
				}
				return 0;
				/* cursorUserPutSoftOn */
				case 0xE2:
				{
					op_cursorUserPutSoftOn();
				}
				return 0;
				/* cursorUserPutSoftOff */
				case 0xE3:
				{
					op_cursorUserPutSoftOff();
				}
				return 0;
				/* cursorUserCursorImage */
				case 0xE4:
				{
					int32 obj = pullStackLong();
					int32 idx = pullStackLong();
					op_cursorUserCursorImage(idx, obj);
				}
				return 0;
				/* cursorHotSpot */
				case 0xE5:
				{
					int32 y = pullStackLong();
					int32 x = pullStackLong();
					op_cursorHotSpot(x, y);
				}
				return 0;
				/* cursorSetTransparency */
				case 0xE6:
				{
					int32 enabled = pullStackLong();
					op_cursorSetTransparency(enabled);
				}
				return 0;
				/* cursorSetCharSet */
				case 0xE7:
				{
					int32 charsetNum = pullStackLong();
					op_cursorSetCharSet(charsetNum);
				}
				return 0;
				/* cursorSetColour */
				case 0xE8:
				{
					int32 argsLength = pullStack();
					int32* args = pullList(listLength, 25);
					op_cursorSetColour(args);
				}
				return 0;
				/* cursorSetPos */
				case 0xE9:
				{
					int32 y = pullStackLong();
					int32 x = pullStackLong();
					op_cursorSetPos(x, y);
				}
				return 0;
		}
		return 0;
		/* loadRoom */
		case 0x9D:
		{
			byte room = pullStackByte();
			op_loadRoom(room);
		}
		return 0;
		/* loadRoomWithEgo */
		case 0x9E:
		{
			int32 room = pullStackLong();
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			op_loadRoomWithEgo(x, y, room);
		}
		return 0;
		/* walkActorToObj */
		case 0x9F:
		{
			int32 dist = pullStackLong();
			int32 obj = pullStackLong();
			int32 index = pullStackLong();
			op_walkActorToObj(index, obj, dist);
		}
		return 0;
		/* walkActorTo */
		case 0xA0:
		{
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			int32 index = pullStackLong();
			op_walkActorTo(index, x, y);
		}
		return 0;
		/* putActorAtXY */
		case 0xA1:
		{
			int32 room = pullStackLong();
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			int32 actorIndex = pullStackLong();
			op_putActorAtXY(actorIndex, x, y, room);
		}
		return 0;
		/* putActorAtObject */
		case 0xA2:
		{
			int32 obj = pullStackLong();
			op_putActorAtObject(obj);
		}
		return 0;
		/* faceActor */
		case 0xA3:
		{
			int32 obj = pullStackLong();
			int32 index = pullStackLong();
			op_faceActor(index, obj);
		}
		return 0;
		/* animateActor */
		case 0xA4:
		{
			int32 anim = pullStackLong();
			int32 index = pullStackLong();
			op_animateActor(index, anim);
		}
		return 0;
		/* doSentence */
		case 0xA5:
		{
			int16 objectB = pullStackWord();
			int16 objectA = pullStackWord();
			byte verb = pullStackByte();
			op_doSentence(verb, objectA, objectB);
		}
		return 0;
		/* pickupObject */
		case 0xA6:
		{
			int32 obj = pullStackLong();
			op_pickupObject(obj);
		}
		return 0;
		/* setBoxFlags */
		case 0xA7:
		{
			int32 value = pullStackLong();
			int32 argsLength = pullStack();
			int32* args = pullList(listLength, 25);
			op_setBoxFlags(args, value);
		}
		return 0;
		/* createBoxMatrix */
		case 0xA8:
		{
			op_createBoxMatrix();
		}
		return 0;
		/* wait */
		case 0xA9:
		{
			op_wait();
		}
		return 0;
		case 0xAA:
		{
			consumeByte();
			switch(op2)
			{
				default:
					return 1;
				/* resourceRoutine3C */
				case 0x3C:
				{
					int16 num = pullStackWord();
					op_resourceRoutine3C(num);
				}
				return 0;
				/* loadCostume */
				case 0x3D:
				{
					int16 num = pullStackWord();
					op_loadCostume(num);
				}
				return 0;
				/* loadObject */
				case 0x3E:
				{
					int16 num = pullStackWord();
					op_loadObject(num);
				}
				return 0;
				/* loadRoom */
				case 0x3F:
				{
					int16 num = pullStackWord();
					op_loadRoom(num);
				}
				return 0;
				/* loadScript */
				case 0x40:
				{
					int16 num = pullStackWord();
					op_loadScript(num);
				}
				return 0;
				/* loadSound */
				case 0x41:
				{
					int16 num = pullStackWord();
					op_loadSound(num);
				}
				return 0;
				/* lockCostume */
				case 0x42:
				{
					int16 num = pullStackWord();
					op_lockCostume(num);
				}
				return 0;
				/* lockRoom */
				case 0x43:
				{
					int16 num = pullStackWord();
					op_lockRoom(num);
				}
				return 0;
				/* lockScript */
				case 0x44:
				{
					int16 num = pullStackWord();
					op_lockScript(num);
				}
				return 0;
				/* lockSound */
				case 0x45:
				{
					int16 num = pullStackWord();
					op_lockSound(num);
				}
				return 0;
				/* unlockCostume */
				case 0x46:
				{
					int16 num = pullStackWord();
					op_unlockCostume(num);
				}
				return 0;
				/* unlockRoom */
				case 0x47:
				{
					int16 num = pullStackWord();
					op_unlockRoom(num);
				}
				return 0;
				/* unlockScript */
				case 0x48:
				{
					int16 num = pullStackWord();
					op_unlockScript(num);
				}
				return 0;
				/* unlockSound */
				case 0x49:
				{
					int16 num = pullStackWord();
					op_unlockSound(num);
				}
				return 0;
				/* unloadCostume */
				case 0x4A:
				{
					int16 num = pullStackWord();
					op_unloadCostume(num);
				}
				return 0;
				/* unloadRoom */
				case 0x4B:
				{
					int16 num = pullStackWord();
					op_unloadRoom(num);
				}
				return 0;
				/* unloadScript */
				case 0x4C:
				{
					int16 num = pullStackWord();
					op_unloadScript(num);
				}
				return 0;
				/* unloadSound */
				case 0x4D:
				{
					int16 num = pullStackWord();
					op_unloadSound(num);
				}
				return 0;
		}
		return 0;
		case 0xAB:
		{
			consumeByte();
			switch(op2)
			{
				default:
					return 1;
				/* setRoomRGB */
				case 0x52:
				{
					int32 index = pullStackLong();
					byte b = pullStackByte();
					byte g = pullStackByte();
					byte r = pullStackByte();
					op_setRoomRGB(r, g, b, index);
				}
				return 0;
				/* fadeRoom */
				case 0x57:
				{
					int32 param = pullStackLong();
					op_fadeRoom(param);
				}
				return 0;
				/* setRoomRGBIntensity */
				case 0x58:
				{
					int16 endColour = pullStackWord();
					int16 startColour = pullStackWord();
					int32 blueScale = pullStackLong();
					int32 greenScale = pullStackLong();
					int32 redScale = pullStackLong();
					op_setRoomRGBIntensity(redScale, greenScale, blueScale, startColour, endColour);
				}
				return 0;
				/* setRoomRGBTransform */
				case 0x59:
				{
					int32 time = pullStackLong();
					int16 end = pullStackWord();
					int16 start = pullStackWord();
					int32 resId = pullStackLong();
					op_setRoomRGBTransform(resId, start, end, time);
				}
				return 0;
				/* setRoomPalette */
				case 0x5C:
				{
					int16 paletteNum = pullStackWord();
					op_setRoomPalette(paletteNum);
				}
				return 0;
				/* saveGame */
				case 0x5D:
				{
					op_saveGame();
				}
				return 0;
				/* loadGame */
				case 0x5E:
				{
					byte saveSound = pullStackByte();
					op_loadGame(saveSound);
				}
				return 0;
				/* setRoomSaturation */
				case 0x5F:
				{
					int16 endColour = pullStackWord();
					int16 startColour = pullStackWord();
					int32 lightScale = pullStackLong();
					int32 satScale = pullStackLong();
					int32 hueScale = pullStackLong();
					op_setRoomSaturation(hueScale, satScale, lightScale, startColour, endColour);
				}
				return 0;
		}
		return 0;
		case 0xAC:
		{
			consumeByte();
			switch(op2)
			{
				default:
					return 1;
				/* setActorCostume */
				case 0x64:
				{
					int16 costumeNum = pullStackWord();
					op_setActorCostume(costumeNum);
				}
				return 0;
				/* setActorWalkSpeed */
				case 0x65:
				{
					int16 y = pullStackWord();
					int16 x = pullStackWord();
					op_setActorWalkSpeed(x, y);
				}
				return 0;
				/* setActorAnimationDefault */
				case 0x67:
				{
					op_setActorAnimationDefault();
				}
				return 0;
				/* setActorAnimationInit */
				case 0x68:
				{
					byte frameNum = pullStackByte();
					op_setActorAnimationInit(frameNum);
				}
				return 0;
				/* setActorAnimationTalk */
				case 0x69:
				{
					byte endFrameNum = pullStackByte();
					byte startFrameNum = pullStackByte();
					op_setActorAnimationTalk(startFrameNum, endFrameNum);
				}
				return 0;
				/* setActorAnimationWalk */
				case 0x6A:
				{
					byte walkFrameNum = pullStackByte();
					op_setActorAnimationWalk(walkFrameNum);
				}
				return 0;
				/* setActorAnimationStand */
				case 0x6B:
				{
					byte standFrameNum = pullStackByte();
					op_setActorAnimationStand(standFrameNum);
				}
				return 0;
				/* setActorAnimationSpeed */
				case 0x6C:
				{
					byte animationSpeed = pullStackByte();
					op_setActorAnimationSpeed(animationSpeed);
				}
				return 0;
				/* setActorDefault */
				case 0x6D:
				{
					op_setActorDefault();
				}
				return 0;
				/* setActorElevation */
				case 0x6E:
				{
					int16 elevation = pullStackWord();
					op_setActorElevation(elevation);
				}
				return 0;
				/* setActorPalette */
				case 0x6F:
				{
					int16 value = pullStackWord();
					byte index = pullStackByte();
					op_setActorPalette(index, value);
				}
				return 0;
				/* setActorTalkColour */
				case 0x70:
				{
					byte colourIndex = pullStackByte();
					op_setActorTalkColour(colourIndex);
				}
				return 0;
				/* setActorName */
				case 0x71:
				{
					char* text = readText();
					op_setActorName(text);
				}
				return 0;
				/* setActorWidth */
				case 0x72:
				{
					int16 width = pullStackWord();
					op_setActorWidth(width);
				}
				return 0;
				/* setActorScale */
				case 0x73:
				{
					int16 size = pullStackWord();
					op_setActorScale(size);
				}
				return 0;
				/* setActorNeverZClip */
				case 0x74:
				{
					op_setActorNeverZClip();
				}
				return 0;
				/* setActorAlwaysZClip */
				case 0x75:
				{
					byte forceClip = pullStackByte();
					op_setActorAlwaysZClip(forceClip);
				}
				return 0;
				/* setActorIgnoreBoxes */
				case 0x76:
				{
					op_setActorIgnoreBoxes();
				}
				return 0;
				/* setActorFollowBoxes */
				case 0x77:
				{
					op_setActorFollowBoxes();
				}
				return 0;
				/* setActorSpecialDraw */
				case 0x78:
				{
					op_setActorSpecialDraw();
				}
				return 0;
				/* setActorTextOffset */
				case 0x79:
				{
					int16 y = pullStackWord();
					int16 x = pullStackWord();
					op_setActorTextOffset(x, y);
				}
				return 0;
				/* setActorVar */
				case 0x7B:
				{
					int32 value = pullStackLong();
					int32 name = pullStackLong();
					op_setActorVar(name, value);
				}
				return 0;
				/* setActorIgnoreTurns */
				case 0x7C:
				{
					op_setActorIgnoreTurns();
				}
				return 0;
				/* setActorFollowTurns */
				case 0x7D:
				{
					op_setActorFollowTurns();
				}
				return 0;
				/* setActorNew */
				case 0x7E:
				{
					op_setActorNew();
				}
				return 0;
				/* setActorDepth */
				case 0x7F:
				{
					int16 depth = pullStackWord();
					op_setActorDepth(depth);
				}
				return 0;
				/* setActorStop */
				case 0x80:
				{
					op_setActorStop();
				}
				return 0;
				/* setActorDirection */
				case 0x81:
				{
					int16 direction = pullStackWord();
					op_setActorDirection(direction);
				}
				return 0;
				/* actorTurn */
				case 0x82:
				{
					int16 direction = pullStackWord();
					op_actorTurn(direction);
				}
				return 0;
				/* setActorWalkScript */
				case 0x83:
				{
					int16 scriptNum = pullStackWord();
					op_setActorWalkScript(scriptNum);
				}
				return 0;
				/* setActorTalkScript */
				case 0x84:
				{
					int16 scriptNum = pullStackWord();
					op_setActorTalkScript(scriptNum);
				}
				return 0;
				/* setActorWalkingFrozen */
				case 0x85:
				{
					op_setActorWalkingFrozen();
				}
				return 0;
				/* setActorWalkingResume */
				case 0x86:
				{
					op_setActorWalkingResume();
				}
				return 0;
				/* setActorTalkVolume */
				case 0x87:
				{
					int32 volume = pullStackLong();
					op_setActorTalkVolume(volume);
				}
				return 0;
				/* setActorTalkFrequency */
				case 0x88:
				{
					int32 frequency = pullStackLong();
					op_setActorTalkFrequency(frequency);
				}
				return 0;
				/* setActorTalkPan */
				case 0x89:
				{
					int32 pan = pullStackLong();
					op_setActorTalkPan(pan);
				}
				return 0;
		}
		return 0;
		case 0xAD:
		{
			consumeByte();
			switch(op2)
			{
				default:
					return 1;
				/* setCameraPause */
				case 0x32:
				{
					op_setCameraPause();
				}
				return 0;
				/* setCameraResume */
				case 0x33:
				{
					op_setCameraResume();
				}
				return 0;
		}
		return 0;
		case 0xAE:
		{
			consumeByte();
			switch(op2)
			{
				default:
					return 1;
				/* initVerb */
				case 0x96:
				{
					int16 verbNum = pullStackWord();
					op_initVerb(verbNum);
				}
				return 0;
				/* newVerb */
				case 0x97:
				{
					int16 verbNum = pullStackWord();
					op_newVerb(verbNum);
				}
				return 0;
				/* deleteVerb */
				case 0x98:
				{
					int16 verbNum = pullStackWord();
					op_deleteVerb(verbNum);
				}
				return 0;
				/* setVerbName */
				case 0x99:
				{
					char* name = readText();
					op_setVerbName(name);
				}
				return 0;
				/* setVerbXY */
				case 0x9A:
				{
					int16 y = pullStackWord();
					int16 x = pullStackWord();
					op_setVerbXY(x, y);
				}
				return 0;
				/* setVerbOn */
				case 0x9B:
				{
					op_setVerbOn();
				}
				return 0;
				/* setVerbOff */
				case 0x9C:
				{
					op_setVerbOff();
				}
				return 0;
				/* setVerbColour */
				case 0x9D:
				{
					byte colourIndex = pullStackByte();
					op_setVerbColour(colourIndex);
				}
				return 0;
				/* setVerbHilightColour */
				case 0x9E:
				{
					byte colourIndex = pullStackByte();
					op_setVerbHilightColour(colourIndex);
				}
				return 0;
				/* setVerbDimColour */
				case 0xA0:
				{
					byte colourIndex = pullStackByte();
					op_setVerbDimColour(colourIndex);
				}
				return 0;
				/* setVerbDim */
				case 0xA1:
				{
					op_setVerbDim();
				}
				return 0;
				/* setVerbKey */
				case 0xA2:
				{
					byte keyCode = pullStackByte();
					op_setVerbKey(keyCode);
				}
				return 0;
				/* setVerbImage */
				case 0xA3:
				{
					byte roomNum = pullStackByte();
					int16 objectNum = pullStackWord();
					op_setVerbImage(objectNum, roomNum);
				}
				return 0;
				/* setVerbNameStr */
				case 0xA4:
				{
					int32 textAddress = pullStackLong();
					op_setVerbNameStr(textAddress);
				}
				return 0;
				/* setVerbCenter */
				case 0xA5:
				{
					op_setVerbCenter();
				}
				return 0;
				/* setVerbCharSet */
				case 0xA6:
				{
					byte charSetNum = pullStackByte();
					op_setVerbCharSet(charSetNum);
				}
				return 0;
				/* setVerbLinesSpacing */
				case 0xA7:
				{
					int16 lineSpacing = pullStackWord();
					op_setVerbLinesSpacing(lineSpacing);
				}
				return 0;
		}
		return 0;
		/* startSound */
		case 0xAF:
		{
			int32 sound = pullStackLong();
			op_startSound(sound);
		}
		return 0;
		/* startMusic */
		case 0xB0:
		{
			int32 sound = pullStackLong();
			op_startMusic(sound);
		}
		return 0;
		/* stopSound */
		case 0xB1:
		{
			int32 sound = pullStackLong();
			op_stopSound(sound);
		}
		return 0;
		/* soundKludge */
		case 0xB2:
		{
			int32 argsLength = pullStack();
			int32* args = pullList(listLength, 25);
			op_soundKludge(args);
		}
		return 0;
		case 0xB3:
		{
			consumeByte();
			switch(op2)
			{
				default:
					return 1;
				/* restartGame */
				case 0x9E:
				{
					op_restartGame();
				}
				return 0;
				/* pauseGame */
				case 0x9F:
				{
					op_pauseGame();
				}
				return 0;
				/* quitGame */
				case 0xA0:
				{
					op_quitGame();
				}
				return 0;
		}
		return 0;
		/* saveRestoreVerbs */
		case 0xB4:
		{
			int32 c = pullStackLong();
			int32 b = pullStackLong();
			int32 a = pullStackLong();
			op_saveRestoreVerbs(a, b, c);
		}
		return 0;
		/* setObjectName */
		case 0xB5:
		{
			char* name = readText();
			int32 obj = pullStackLong();
			op_setObjectName(obj, name);
		}
		return 0;
		/* getDateTime */
		case 0xB6:
		{
			op_getDateTime();
		}
		return 0;
		/* drawBox */
		case 0xB7:
		{
			int32 color = pullStackLong();
			int32 y2 = pullStackLong();
			int32 x2 = pullStackLong();
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			op_drawBox(x, y, x2, y2, color);
		}
		return 0;
		/* startVideo */
		case 0xB9:
		{
			char* fileName = readText();
			op_startVideo(fileName);
		}
		return 0;
		case 0xBA:
		{
			consumeByte();
			switch(op2)
			{
				default:
					return 1;
				/* lockObject */
				case 0x0B:
				{
					int32 argsLength = pullStack();
					int32* args = pullList(listLength, 25);
					op_lockObject(args);
				}
				return 0;
				/* unlockObject */
				case 0x0C:
				{
					int32 argsLength = pullStack();
					int32* args = pullList(listLength, 25);
					op_unlockObject(args);
				}
				return 0;
				/* remapCostumePalette */
				case 0x0D:
				{
					int32 argsLength = pullStack();
					int32* args = pullList(listLength, 25);
					op_remapCostumePalette(args);
				}
				return 0;
				/* remapCostumeInsert */
				case 0x0E:
				{
					int32 argsLength = pullStack();
					int32* args = pullList(listLength, 25);
					op_remapCostumeInsert(args);
				}
				return 0;
				/* setVideoFrameRate */
				case 0x0F:
				{
					int32 argsLength = pullStack();
					int32* args = pullList(listLength, 25);
					op_setVideoFrameRate(args);
				}
				return 0;
				/* setBoxScaleSlot */
				case 0x14:
				{
					int32 argsLength = pullStack();
					int32* args = pullList(listLength, 25);
					op_setBoxScaleSlot(args);
				}
				return 0;
				/* setScaleSlot */
				case 0x15:
				{
					int32 argsLength = pullStack();
					int32* args = pullList(listLength, 25);
					op_setScaleSlot(args);
				}
				return 0;
				/* setBannerColours */
				case 0x16:
				{
					int32 argsLength = pullStack();
					int32* args = pullList(listLength, 25);
					op_setBannerColours(args);
				}
				return 0;
				/* setActorChoreLimbFrame */
				case 0x17:
				{
					int32 argsLength = pullStack();
					int32* args = pullList(listLength, 25);
					op_setActorChoreLimbFrame(args);
				}
				return 0;
				/* clearTextQueue */
				case 0x18:
				{
					int32 argsLength = pullStack();
					int32* args = pullList(listLength, 25);
					op_clearTextQueue(args);
				}
				return 0;
				/* saveGameReadName */
				case 0x19:
				{
					int32 argsLength = pullStack();
					int32* args = pullList(listLength, 25);
					op_saveGameReadName(args);
				}
				return 0;
				/* saveGameWrite */
				case 0x1A:
				{
					int32 argsLength = pullStack();
					int32* args = pullList(listLength, 25);
					op_saveGameWrite(args);
				}
				return 0;
				/* saveGameRead */
				case 0x1B:
				{
					int32 argsLength = pullStack();
					int32* args = pullList(listLength, 25);
					op_saveGameRead(args);
				}
				return 0;
				/* saveGameScreenshot */
				case 0x1C:
				{
					int32 argsLength = pullStack();
					int32* args = pullList(listLength, 25);
					op_saveGameScreenshot(args);
				}
				return 0;
				/* setKeyScript */
				case 0x1D:
				{
					int32 argsLength = pullStack();
					int32* args = pullList(listLength, 25);
					op_setKeyScript(args);
				}
				return 0;
				/* killAllScriptsExceptCurrent */
				case 0x1E:
				{
					int32 argsLength = pullStack();
					int32* args = pullList(listLength, 25);
					op_killAllScriptsExceptCurrent(args);
				}
				return 0;
				/* stopAllVideo */
				case 0x1F:
				{
					int32 argsLength = pullStack();
					int32* args = pullList(listLength, 25);
					op_stopAllVideo(args);
				}
				return 0;
				/* writeRegistryValue */
				case 0x20:
				{
					int32 argsLength = pullStack();
					int32* args = pullList(listLength, 25);
					op_writeRegistryValue(args);
				}
				return 0;
				/* setPaletteIntensity */
				case 0x21:
				{
					int32 argsLength = pullStack();
					int32* args = pullList(listLength, 25);
					op_setPaletteIntensity(args);
				}
				return 0;
				/* queryQuit */
				case 0x22:
				{
					int32 argsLength = pullStack();
					int32* args = pullList(listLength, 25);
					op_queryQuit(args);
				}
				return 0;
				/* buildPaletteShadow */
				case 0x6C:
				{
					int32 argsLength = pullStack();
					int32* args = pullList(listLength, 25);
					op_buildPaletteShadow(args);
				}
				return 0;
				/* setPaletteShadow */
				case 0x6D:
				{
					int32 argsLength = pullStack();
					int32* args = pullList(listLength, 25);
					op_setPaletteShadow(args);
				}
				return 0;
				/* blastShadowObject */
				case 0x6E:
				{
					int32 argsLength = pullStack();
					int32* args = pullList(listLength, 25);
					op_blastShadowObject(args);
				}
				return 0;
				/* superBlastObject */
				case 0x6F:
				{
					int32 argsLength = pullStack();
					int32* args = pullList(listLength, 25);
					op_superBlastObject(args);
				}
				return 0;
		}
		return 0;
		/* dim2DimArray */
		case 0xC0:
		{
			int32 dim1 = pullStackLong();
			int32 dim2 = pullStackLong();
			op_dim2DimArray(dim2, dim1);
		}
		return 0;
		/* distObjectPt */
		case 0xC6:
		{
			int32 c = pullStackLong();
			int32 b = pullStackLong();
			int32 a = pullStackLong();
			op_distObjectPt(a, b, c);
		}
		return 0;
		/* startScriptQuick2 */
		case 0xC8:
		{
			int32 argsLength = pullStack();
			int32* args = pullList(listLength, 25);
			int32 script = pullStackLong();
			op_startScriptQuick2(script, args);
		}
		return 0;
		/* startObjectQuick */
		case 0xC9:
		{
			int32 argsLength = pullStack();
			int32* args = pullList(listLength, 25);
			byte entryPc = pullStackByte();
			int32 script = pullStackLong();
			op_startObjectQuick(script, entryPc, args);
		}
		return 0;
		/* pickOneOf */
		case 0xCA:
		{
			int32 argsLength = pullStack();
			int32* args = pullList(listLength, 25);
			int32 i = pullStackLong();
			op_pickOneOf(i, args);
		}
		return 0;
		/* pickOneOfDefault */
		case 0xCB:
		{
			int32 def = pullStackLong();
			int32 argsLength = pullStack();
			int32* args = pullList(listLength, 25);
			int32 i = pullStackLong();
			op_pickOneOfDefault(i, args, def);
		}
		return 0;
		/* isAnyOf */
		case 0xCD:
		{
			int32 argsLength = pullStack();
			int32* args = pullList(listLength, 25);
			int32 value = pullStackLong();
			op_isAnyOf(value, args);
		}
		return 0;
		/* getRandomNumber */
		case 0xCE:
		{
			int32 max = pullStackLong();
			op_getRandomNumber(max);
		}
		return 0;
		/* getRandomNumberRange */
		case 0xCF:
		{
			int32 max = pullStackLong();
			int32 min = pullStackLong();
			op_getRandomNumberRange(min, max);
		}
		return 0;
		/* ifClassOfIs */
		case 0xD0:
		{
			int32 argsLength = pullStack();
			int32* args = pullList(listLength, 25);
			int32 obj = pullStackLong();
			op_ifClassOfIs(obj, args);
		}
		return 0;
		/* getState */
		case 0xD1:
		{
			int32 obj = pullStackLong();
			op_getState(obj);
		}
		return 0;
		/* getOwner */
		case 0xD2:
		{
			int32 obj = pullStackLong();
			op_getOwner(obj);
		}
		return 0;
		/* isScriptRunning */
		case 0xD3:
		{
			int32 script = pullStackLong();
			op_isScriptRunning(script);
		}
		return 0;
		/* shuffle */
		case 0xD4:
		{
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_shuffle(left, right);
		}
		return 0;
		/* isSoundRunning */
		case 0xD5:
		{
			int32 sound = pullStackLong();
			op_isSoundRunning(sound);
		}
		return 0;
		/* abs */
		case 0xD6:
		{
			int32 value = pullStackLong();
			op_abs(value);
		}
		return 0;
		case 0xD8:
		{
			consumeByte();
			switch(op2)
			{
				default:
					return 1;
				/* getWalkBoxAt */
				case 0x73:
				{
					int32 args = pullStackLong();
					op_getWalkBoxAt(args);
				}
				return 0;
				/* isPointInBox */
				case 0x74:
				{
					int32 args = pullStackLong();
					op_isPointInBox(args);
				}
				return 0;
				/* getRGBSlot */
				case 0xCE:
				{
					int32 args = pullStackLong();
					op_getRGBSlot(args);
				}
				return 0;
				/* getKeyState */
				case 0xD3:
				{
					int32 args = pullStackLong();
					op_getKeyState(args);
				}
				return 0;
				/* getBox */
				case 0xD7:
				{
					int32 args = pullStackLong();
					op_getBox(args);
				}
				return 0;
				/* findBlastObject */
				case 0xD8:
				{
					int32 args = pullStackLong();
					op_findBlastObject(args);
				}
				return 0;
				/* actorHitTest */
				case 0xD9:
				{
					int32 args = pullStackLong();
					op_actorHitTest(args);
				}
				return 0;
				/* setLipSyncWidth */
				case 0xDA:
				{
					int32 args = pullStackLong();
					op_setLipSyncWidth(args);
				}
				return 0;
				/* setLipSyncHeight */
				case 0xDB:
				{
					int32 args = pullStackLong();
					op_setLipSyncHeight(args);
				}
				return 0;
				/* setTalkAnimation */
				case 0xDC:
				{
					int32 args = pullStackLong();
					op_setTalkAnimation(args);
				}
				return 0;
				/* getGroupSfxVol */
				case 0xDD:
				{
					int32 args = pullStackLong();
					op_getGroupSfxVol(args);
				}
				return 0;
				/* getGroupVoiceVol */
				case 0xDE:
				{
					int32 args = pullStackLong();
					op_getGroupVoiceVol(args);
				}
				return 0;
				/* getGroupMusicVol */
				case 0xDF:
				{
					int32 args = pullStackLong();
					op_getGroupMusicVol(args);
				}
				return 0;
				/* readRegistryValue */
				case 0xE0:
				{
					int32 args = pullStackLong();
					op_readRegistryValue(args);
				}
				return 0;
				/* imuseGetMusicPosition */
				case 0xE1:
				{
					int32 args = pullStackLong();
					op_imuseGetMusicPosition(args);
				}
				return 0;
				/* imuseGetMusicLipSyncWidth */
				case 0xE2:
				{
					int32 args = pullStackLong();
					op_imuseGetMusicLipSyncWidth(args);
				}
				return 0;
				/* imuseGetMusicLipSyncHeight */
				case 0xE3:
				{
					int32 args = pullStackLong();
					op_imuseGetMusicLipSyncHeight(args);
				}
				return 0;
		}
		return 0;
		/* isActorInBox */
		case 0xD9:
		{
			int32 box = pullStackLong();
			int32 index = pullStackLong();
			op_isActorInBox(index, box);
		}
		return 0;
		/* getVerbEntrypoint */
		case 0xDA:
		{
			int32 entryp = pullStackLong();
			int32 verb = pullStackLong();
			op_getVerbEntrypoint(verb, entryp);
		}
		return 0;
		/* getActorFromXY */
		case 0xDB:
		{
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			op_getActorFromXY(x, y);
		}
		return 0;
		/* findObject */
		case 0xDC:
		{
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			op_findObject(x, y);
		}
		return 0;
		/* getVerbFromXY */
		case 0xDD:
		{
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			op_getVerbFromXY(x, y);
		}
		return 0;
		/* findInventory */
		case 0xDF:
		{
			int32 index = pullStackLong();
			int32 owner = pullStackLong();
			op_findInventory(owner, index);
		}
		return 0;
		/* getInventoryCount */
		case 0xE0:
		{
			int32 owner = pullStackLong();
			op_getInventoryCount(owner);
		}
		return 0;
		/* getAnimateVariable */
		case 0xE1:
		{
			int32 variable = pullStackLong();
			int32 index = pullStackLong();
			op_getAnimateVariable(index, variable);
		}
		return 0;
		/* getActorRoom */
		case 0xE2:
		{
			int32 index = pullStackLong();
			op_getActorRoom(index);
		}
		return 0;
		/* getActorWalkBox */
		case 0xE3:
		{
			int32 index = pullStackLong();
			op_getActorWalkBox(index);
		}
		return 0;
		/* getActorMoving */
		case 0xE4:
		{
			int32 index = pullStackLong();
			op_getActorMoving(index);
		}
		return 0;
		/* getActorCostume */
		case 0xE5:
		{
			int32 index = pullStackLong();
			op_getActorCostume(index);
		}
		return 0;
		/* getActorScaleX */
		case 0xE6:
		{
			int32 index = pullStackLong();
			op_getActorScaleX(index);
		}
		return 0;
		/* getActorLayer */
		case 0xE7:
		{
			int32 index = pullStackLong();
			op_getActorLayer(index);
		}
		return 0;
		/* getActorElevation */
		case 0xE8:
		{
			int32 index = pullStackLong();
			op_getActorElevation(index);
		}
		return 0;
		/* getActorWidth */
		case 0xE9:
		{
			int32 index = pullStackLong();
			op_getActorWidth(index);
		}
		return 0;
		/* getObjectNewDir */
		case 0xEA:
		{
			int32 index = pullStackLong();
			op_getObjectNewDir(index);
		}
		return 0;
		/* getObjectX */
		case 0xEB:
		{
			int32 index = pullStackLong();
			op_getObjectX(index);
		}
		return 0;
		/* getObjectY */
		case 0xEC:
		{
			int32 index = pullStackLong();
			op_getObjectY(index);
		}
		return 0;
		/* getActorChore */
		case 0xED:
		{
			int16 actorNum = pullStackWord();
			op_getActorChore(actorNum);
		}
		return 0;
		/* distObjectObject */
		case 0xEE:
		{
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_distObjectObject(left, right);
		}
		return 0;
		/* distObjectPtPt */
		case 0xEF:
		{
			int32 d = pullStackLong();
			int32 c = pullStackLong();
			int32 b = pullStackLong();
			int32 a = pullStackLong();
			op_distObjectPtPt(a, b, c, d);
		}
		return 0;
		/* getObjectImageX */
		case 0xF0:
		{
			int16 objectNum = pullStackWord();
			op_getObjectImageX(objectNum);
		}
		return 0;
		/* getObjectImageY */
		case 0xF1:
		{
			int16 objectNum = pullStackWord();
			op_getObjectImageY(objectNum);
		}
		return 0;
		/* getObjectImageWidth */
		case 0xF2:
		{
			int16 objectNum = pullStackWord();
			op_getObjectImageWidth(objectNum);
		}
		return 0;
		/* getObjectImageHeight */
		case 0xF3:
		{
			int16 objectNum = pullStackWord();
			op_getObjectImageHeight(objectNum);
		}
		return 0;
		/* getStringWidth */
		case 0xF6:
		{
			int16 charsetNum = pullStackWord();
			char* text = readText();
			op_getStringWidth(text, charsetNum);
		}
		return 0;
		/* getActorZPlane */
		case 0xF7:
		{
			int16 actorNum = pullStackWord();
			op_getActorZPlane(actorNum);
		}
		return 0;
	};
};
