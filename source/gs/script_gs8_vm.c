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

#include "vm_context.h"
#include "script.h"

#define pullStackWord() 0
#define pullStackByte() 0
#define pullStackLong() 0
#define pullStack() 0 
#define pullList(X, Y) NULL

/* 00 pushByte */
GS_PRIVATE GS_INLINE void op_pushByte(gs_VmContext* ctx, byte value) {
	/* TODO */
}

/* 01 pushWord */
GS_PRIVATE GS_INLINE void op_pushWord(gs_VmContext* ctx, int32 value) {
	/* TODO */
}

/* 02 pushWordVar */
GS_PRIVATE GS_INLINE void op_pushWordVar(gs_VmContext* ctx, int32 name) {
	/* TODO */
}

/* 03 wordArrayRead */
GS_PRIVATE GS_INLINE void op_wordArrayRead(gs_VmContext* ctx, int32 base) {
	/* TODO */
}

/* 04 wordArrayIndexedRead */
GS_PRIVATE GS_INLINE void op_wordArrayIndexedRead(gs_VmContext* ctx, int32 index, int32 base, int32 arrayNum) {
	/* TODO */
}

/* 05 dup */
GS_PRIVATE GS_INLINE void op_dup(gs_VmContext* ctx, int32 value) {
	/* TODO */
}

/* 06 pop */
GS_PRIVATE GS_INLINE void op_pop(gs_VmContext* ctx, int32 discard) {
	/* TODO */
}

/* 07 not */
GS_PRIVATE GS_INLINE void op_not(gs_VmContext* ctx, int32 value) {
	/* TODO */
}

/* 08 eq */
GS_PRIVATE GS_INLINE void op_eq(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 09 neq */
GS_PRIVATE GS_INLINE void op_neq(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 0A gt */
GS_PRIVATE GS_INLINE void op_gt(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 0B lt */
GS_PRIVATE GS_INLINE void op_lt(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 0C le */
GS_PRIVATE GS_INLINE void op_le(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 0D ge */
GS_PRIVATE GS_INLINE void op_ge(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 0E add */
GS_PRIVATE GS_INLINE void op_add(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 0F sub */
GS_PRIVATE GS_INLINE void op_sub(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 10 mul */
GS_PRIVATE GS_INLINE void op_mul(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 11 div */
GS_PRIVATE GS_INLINE void op_div(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 12 land */
GS_PRIVATE GS_INLINE void op_land(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 13 lor */
GS_PRIVATE GS_INLINE void op_lor(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 14 band */
GS_PRIVATE GS_INLINE void op_band(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 15 bor */
GS_PRIVATE GS_INLINE void op_bor(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 16 mod */
GS_PRIVATE GS_INLINE void op_mod(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 42 writeByteVar */
GS_PRIVATE GS_INLINE void op_writeByteVar(gs_VmContext* ctx, int32 value) {
	/* TODO */
}

/* 46 byteArrayWrite */
GS_PRIVATE GS_INLINE void op_byteArrayWrite(gs_VmContext* ctx, int32 base, int32 value) {
	/* TODO */
}

/* 4A byteArrayIndexedWrite */
GS_PRIVATE GS_INLINE void op_byteArrayIndexedWrite(gs_VmContext* ctx, int32 index, int32 base, int32 value) {
	/* TODO */
}

/* 4E byteVarInc */
GS_PRIVATE GS_INLINE void op_byteVarInc(gs_VmContext* ctx) {
	/* TODO */
}

/* 52 byteArrayInc */
GS_PRIVATE GS_INLINE void op_byteArrayInc(gs_VmContext* ctx, int32 base) {
	/* TODO */
}

/* 56 byteVarDec */
GS_PRIVATE GS_INLINE void op_byteVarDec(gs_VmContext* ctx) {
	/* TODO */
}

/* 5A byteArrayDec */
GS_PRIVATE GS_INLINE void op_byteArrayDec(gs_VmContext* ctx, int32 base) {
	/* TODO */
}

/* 61 drawObject */
GS_PRIVATE GS_INLINE void op_drawObject(gs_VmContext* ctx, int32 obj, int32 state) {
	/* TODO */
}

/* 62 drawObjectAt */
GS_PRIVATE GS_INLINE void op_drawObjectAt(gs_VmContext* ctx, int32 obj, int32 x, int32 y) {
	/* TODO */
}

/* 63 drawBlastObject */
GS_PRIVATE GS_INLINE void op_drawBlastObject(gs_VmContext* ctx, int32 a, int32 b, int32 c, int32 d, int32 e, int32 argsLength, int32* args) {
	/* TODO */
}

/* 64 if */
GS_PRIVATE GS_INLINE void op_if(gs_VmContext* ctx, int32 condition, int32 offset) {
	/* TODO */
}

/* 65 ifNot */
GS_PRIVATE GS_INLINE void op_ifNot(gs_VmContext* ctx, int32 condition, int32 offset) {
	/* TODO */
}

/* 66 jump */
GS_PRIVATE GS_INLINE void op_jump(gs_VmContext* ctx, int32 offset) {
	/* TODO */
}

/* 67 breakHere */
GS_PRIVATE GS_INLINE void op_breakHere(gs_VmContext* ctx) {
	/* TODO */
}

/* 68 delayFrames */
GS_PRIVATE GS_INLINE void op_delayFrames(gs_VmContext* ctx) {
	/* TODO */
}

/* 691E waitActor */
GS_INLINE void op_waitActor(gs_VmContext* ctx, int32 offset, int32 actorNum) {
	/* TODO */
}

/* 691F waitMessage */
GS_INLINE void op_waitMessage(gs_VmContext* ctx) {
	/* TODO */
}

/* 6920 waitCamera */
GS_INLINE void op_waitCamera(gs_VmContext* ctx) {
	/* TODO */
}

/* 6921 waitSentence */
GS_INLINE void op_waitSentence(gs_VmContext* ctx) {
	/* TODO */
}

/* 6922 waitAnimation */
GS_INLINE void op_waitAnimation(gs_VmContext* ctx) {
	/* TODO */
}

/* 6923 waitTurn */
GS_INLINE void op_waitTurn(gs_VmContext* ctx, int32 offset, int32 actorNum) {
	/* TODO */
}

/* 6A delay */
GS_PRIVATE GS_INLINE void op_delay(gs_VmContext* ctx, int32 delay) {
	/* TODO */
}

/* 6B delaySeconds */
GS_PRIVATE GS_INLINE void op_delaySeconds(gs_VmContext* ctx, int32 seconds) {
	/* TODO */
}

/* 6C delayMinutes */
GS_PRIVATE GS_INLINE void op_delayMinutes(gs_VmContext* ctx, int32 minutes) {
	/* TODO */
}

/* 6D writeWordVar */
GS_PRIVATE GS_INLINE void op_writeWordVar(gs_VmContext* ctx, int32 value) {
	/* TODO */
}

/* 6E wordVarInc */
GS_PRIVATE GS_INLINE void op_wordVarInc(gs_VmContext* ctx, int32 var) {
	/* TODO */
}

/* 6F wordVarDec */
GS_PRIVATE GS_INLINE void op_wordVarDec(gs_VmContext* ctx, int32 var) {
	/* TODO */
}

/* 700A newArrayInt */
GS_INLINE void op_newArrayInt(gs_VmContext* ctx, int32 arrayNum, int32 dim1) {
	/* TODO */
}

/* 700B newArrayString */
GS_INLINE void op_newArrayString(gs_VmContext* ctx, int32 arrayNum, int32 dim1) {
	/* TODO */
}

/* 700C deleteArray */
GS_INLINE void op_deleteArray(gs_VmContext* ctx, int32 arrayNum) {
	/* TODO */
}

/* 71 wordArrayWrite */
GS_PRIVATE GS_INLINE void op_wordArrayWrite(gs_VmContext* ctx, int32 base, int32 value) {
	/* TODO */
}

/* 72 wordArrayInc */
GS_PRIVATE GS_INLINE void op_wordArrayInc(gs_VmContext* ctx, int32 base) {
	/* TODO */
}

/* 73 wordArrayDec */
GS_PRIVATE GS_INLINE void op_wordArrayDec(gs_VmContext* ctx, int32 base) {
	/* TODO */
}

/* 740A newArray2Int */
GS_INLINE void op_newArray2Int(gs_VmContext* ctx, int32 arrayNum, int32 dim1, int32 dim2) {
	/* TODO */
}

/* 740B newArray2String */
GS_INLINE void op_newArray2String(gs_VmContext* ctx, int32 arrayNum, int32 dim1, int32 dim2) {
	/* TODO */
}

/* 740C deleteArray2 */
GS_INLINE void op_deleteArray2(gs_VmContext* ctx, int32 arrayNum) {
	/* TODO */
}

/* 75 wordArrayIndexedWrite */
GS_PRIVATE GS_INLINE void op_wordArrayIndexedWrite(gs_VmContext* ctx, int32 index, int32 base, int32 value, int32 arrayNum) {
	/* TODO */
}

/* 7614 setArrayString */
GS_INLINE void op_setArrayString(gs_VmContext* ctx, char* string, int32 offset, int32 arrayNum) {
	/* TODO */
}

/* 7615 setArrayList */
GS_INLINE void op_setArrayList(gs_VmContext* ctx, int32 listLength, int32* list, int32 offset, int32 arrayNum) {
	/* TODO */
}

/* 7616 setArray2List */
GS_INLINE void op_setArray2List(gs_VmContext* ctx, int32 listLength, int32* list, int32 offset, int32 arrayNum) {
	/* TODO */
}

/* 79 startScript */
GS_PRIVATE GS_INLINE void op_startScript(gs_VmContext* ctx, int32 flags, int32 script, int32 argsLength, int32* args) {
	/* TODO */
}

/* 7A startScriptQuick */
GS_PRIVATE GS_INLINE void op_startScriptQuick(gs_VmContext* ctx, int32 script, int32 argsLength, int32* args) {
	/* TODO */
}

/* 7B stopObjectCode */
GS_PRIVATE GS_INLINE void op_stopObjectCode(gs_VmContext* ctx) {
	/* TODO */
}

/* 7C stopScript */
GS_PRIVATE GS_INLINE void op_stopScript(gs_VmContext* ctx, int32 scriptNum) {
	/* TODO */
}

/* 7D jumpToScript */
GS_PRIVATE GS_INLINE void op_jumpToScript(gs_VmContext* ctx, int32 flags, int32 scriptNum, int32 argsLength, int32* args) {
	/* TODO */
}

/* 7E dummy */
GS_PRIVATE GS_INLINE void op_dummy(gs_VmContext* ctx) {
	/* TODO */
}

/* 7F startObject */
GS_PRIVATE GS_INLINE void op_startObject(gs_VmContext* ctx, int32 flags, int32 script, byte entryp, int32 argsLength, int32* args) {
	/* TODO */
}

/* 80 stopObjectScript */
GS_PRIVATE GS_INLINE void op_stopObjectScript(gs_VmContext* ctx, int16 script) {
	/* TODO */
}

/* 81 cutscene */
GS_PRIVATE GS_INLINE void op_cutscene(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* 82 endCutscene */
GS_PRIVATE GS_INLINE void op_endCutscene(gs_VmContext* ctx) {
	/* TODO */
}

/* 83 freezeUnfreeze */
GS_PRIVATE GS_INLINE void op_freezeUnfreeze(gs_VmContext* ctx, int32 script) {
	/* TODO */
}

/* 84 beginOverride */
GS_PRIVATE GS_INLINE void op_beginOverride(gs_VmContext* ctx) {
	/* TODO */
}

/* 85 endOverride */
GS_PRIVATE GS_INLINE void op_endOverride(gs_VmContext* ctx) {
	/* TODO */
}

/* 86 stopSentence */
GS_PRIVATE GS_INLINE void op_stopSentence(gs_VmContext* ctx) {
	/* TODO */
}

/* 89 setClass */
GS_PRIVATE GS_INLINE void op_setClass(gs_VmContext* ctx, int32 obj, int32 argsLength, int32* args) {
	/* TODO */
}

/* 8A setState */
GS_PRIVATE GS_INLINE void op_setState(gs_VmContext* ctx, int32 obj, int32 state) {
	/* TODO */
}

/* 8B setOwner */
GS_PRIVATE GS_INLINE void op_setOwner(gs_VmContext* ctx, int32 obj, int32 owner) {
	/* TODO */
}

/* 8C panCameraTo */
GS_PRIVATE GS_INLINE void op_panCameraTo(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* 8D actorFollowCamera */
GS_PRIVATE GS_INLINE void op_actorFollowCamera(gs_VmContext* ctx, int32 index) {
	/* TODO */
}

/* 8E setCameraAt */
GS_PRIVATE GS_INLINE void op_setCameraAt(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* 8F41 printActorAt */
GS_INLINE void op_printActorAt(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* 8F42 printActorColour */
GS_INLINE void op_printActorColour(gs_VmContext* ctx, int32 col) {
	/* TODO */
}

/* 8F43 printActorClipped */
GS_INLINE void op_printActorClipped(gs_VmContext* ctx, int32 right) {
	/* TODO */
}

/* 8F45 printActorCentre */
GS_INLINE void op_printActorCentre(gs_VmContext* ctx) {
	/* TODO */
}

/* 8F47 printActorLeft */
GS_INLINE void op_printActorLeft(gs_VmContext* ctx) {
	/* TODO */
}

/* 8F48 printActorOverhead */
GS_INLINE void op_printActorOverhead(gs_VmContext* ctx) {
	/* TODO */
}

/* 8F4A printActorMumble */
GS_INLINE void op_printActorMumble(gs_VmContext* ctx) {
	/* TODO */
}

/* 8F4B printActorText */
GS_INLINE void op_printActorText(gs_VmContext* ctx, char* text) {
	/* TODO */
}

/* 8FFE printActorLoadDefault */
GS_INLINE void op_printActorLoadDefault(gs_VmContext* ctx, int32 actorNum) {
	/* TODO */
}

/* 8FFF printActorSaveDefault */
GS_INLINE void op_printActorSaveDefault(gs_VmContext* ctx) {
	/* TODO */
}

/* 9041 printEgoAt */
GS_INLINE void op_printEgoAt(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* 9042 printEgoColour */
GS_INLINE void op_printEgoColour(gs_VmContext* ctx, int32 col) {
	/* TODO */
}

/* 9043 printEgoClipped */
GS_INLINE void op_printEgoClipped(gs_VmContext* ctx, int32 right) {
	/* TODO */
}

/* 9045 printEgoCentre */
GS_INLINE void op_printEgoCentre(gs_VmContext* ctx) {
	/* TODO */
}

/* 9047 printEgoLeft */
GS_INLINE void op_printEgoLeft(gs_VmContext* ctx) {
	/* TODO */
}

/* 9048 printEgoOverhead */
GS_INLINE void op_printEgoOverhead(gs_VmContext* ctx) {
	/* TODO */
}

/* 904A printEgoMumble */
GS_INLINE void op_printEgoMumble(gs_VmContext* ctx) {
	/* TODO */
}

/* 904B printEgoText */
GS_INLINE void op_printEgoText(gs_VmContext* ctx, char* text) {
	/* TODO */
}

/* 90FE printEgoLoadDefault */
GS_INLINE void op_printEgoLoadDefault(gs_VmContext* ctx, int32 actorNum) {
	/* TODO */
}

/* 90FF printEgoSaveDefault */
GS_INLINE void op_printEgoSaveDefault(gs_VmContext* ctx) {
	/* TODO */
}

/* 91 talkActor */
GS_PRIVATE GS_INLINE void op_talkActor(gs_VmContext* ctx, char* text, int32 actor) {
	/* TODO */
}

/* 92 talkEgo */
GS_PRIVATE GS_INLINE void op_talkEgo(gs_VmContext* ctx, char* text) {
	/* TODO */
}

/* 9341 printLineAt */
GS_INLINE void op_printLineAt(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* 9342 printLineColour */
GS_INLINE void op_printLineColour(gs_VmContext* ctx, int32 col) {
	/* TODO */
}

/* 9343 printLineClipped */
GS_INLINE void op_printLineClipped(gs_VmContext* ctx, int32 right) {
	/* TODO */
}

/* 9345 printLineCentre */
GS_INLINE void op_printLineCentre(gs_VmContext* ctx) {
	/* TODO */
}

/* 9347 printLineLeft */
GS_INLINE void op_printLineLeft(gs_VmContext* ctx) {
	/* TODO */
}

/* 9348 printLineOverhead */
GS_INLINE void op_printLineOverhead(gs_VmContext* ctx) {
	/* TODO */
}

/* 934A printLineMumble */
GS_INLINE void op_printLineMumble(gs_VmContext* ctx) {
	/* TODO */
}

/* 934B printLineText */
GS_INLINE void op_printLineText(gs_VmContext* ctx, char* text) {
	/* TODO */
}

/* 93FE printLineLoadDefault */
GS_INLINE void op_printLineLoadDefault(gs_VmContext* ctx) {
	/* TODO */
}

/* 93FF printLineSaveDefault */
GS_INLINE void op_printLineSaveDefault(gs_VmContext* ctx) {
	/* TODO */
}

/* 9441 printTextAt */
GS_INLINE void op_printTextAt(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* 9442 printTextColour */
GS_INLINE void op_printTextColour(gs_VmContext* ctx, int32 col) {
	/* TODO */
}

/* 9443 printTextClipped */
GS_INLINE void op_printTextClipped(gs_VmContext* ctx, int32 right) {
	/* TODO */
}

/* 9445 printTextCentre */
GS_INLINE void op_printTextCentre(gs_VmContext* ctx) {
	/* TODO */
}

/* 9447 printTextLeft */
GS_INLINE void op_printTextLeft(gs_VmContext* ctx) {
	/* TODO */
}

/* 9448 printTextOverhead */
GS_INLINE void op_printTextOverhead(gs_VmContext* ctx) {
	/* TODO */
}

/* 944A printTextMumble */
GS_INLINE void op_printTextMumble(gs_VmContext* ctx) {
	/* TODO */
}

/* 944B printTextText */
GS_INLINE void op_printTextText(gs_VmContext* ctx, char* text) {
	/* TODO */
}

/* 94FE printTextLoadDefault */
GS_INLINE void op_printTextLoadDefault(gs_VmContext* ctx) {
	/* TODO */
}

/* 94FF printTextSaveDefault */
GS_INLINE void op_printTextSaveDefault(gs_VmContext* ctx) {
	/* TODO */
}

/* 9541 printDebugAt */
GS_INLINE void op_printDebugAt(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* 9542 printDebugColour */
GS_INLINE void op_printDebugColour(gs_VmContext* ctx, int32 col) {
	/* TODO */
}

/* 9543 printDebugClipped */
GS_INLINE void op_printDebugClipped(gs_VmContext* ctx, int32 right) {
	/* TODO */
}

/* 9545 printDebugCentre */
GS_INLINE void op_printDebugCentre(gs_VmContext* ctx) {
	/* TODO */
}

/* 9547 printDebugLeft */
GS_INLINE void op_printDebugLeft(gs_VmContext* ctx) {
	/* TODO */
}

/* 9548 printDebugOverhead */
GS_INLINE void op_printDebugOverhead(gs_VmContext* ctx) {
	/* TODO */
}

/* 954A printDebugMumble */
GS_INLINE void op_printDebugMumble(gs_VmContext* ctx) {
	/* TODO */
}

/* 954B printDebugText */
GS_INLINE void op_printDebugText(gs_VmContext* ctx, char* text) {
	/* TODO */
}

/* 95FE printDebugLoadDefault */
GS_INLINE void op_printDebugLoadDefault(gs_VmContext* ctx) {
	/* TODO */
}

/* 95FF printDebugSaveDefault */
GS_INLINE void op_printDebugSaveDefault(gs_VmContext* ctx) {
	/* TODO */
}

/* 9641 printSystemAt */
GS_INLINE void op_printSystemAt(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* 9642 printSystemColour */
GS_INLINE void op_printSystemColour(gs_VmContext* ctx, int32 col) {
	/* TODO */
}

/* 9643 printSystemClipped */
GS_INLINE void op_printSystemClipped(gs_VmContext* ctx, int32 right) {
	/* TODO */
}

/* 9645 printSystemCentre */
GS_INLINE void op_printSystemCentre(gs_VmContext* ctx) {
	/* TODO */
}

/* 9647 printSystemLeft */
GS_INLINE void op_printSystemLeft(gs_VmContext* ctx) {
	/* TODO */
}

/* 9648 printSystemOverhead */
GS_INLINE void op_printSystemOverhead(gs_VmContext* ctx) {
	/* TODO */
}

/* 964A printSystemMumble */
GS_INLINE void op_printSystemMumble(gs_VmContext* ctx) {
	/* TODO */
}

/* 964B printSystemText */
GS_INLINE void op_printSystemText(gs_VmContext* ctx, char* text) {
	/* TODO */
}

/* 96FE printSystemLoadDefault */
GS_INLINE void op_printSystemLoadDefault(gs_VmContext* ctx) {
	/* TODO */
}

/* 96FF printSystemSaveDefault */
GS_INLINE void op_printSystemSaveDefault(gs_VmContext* ctx) {
	/* TODO */
}

/* 9741 blastTextAt */
GS_INLINE void op_blastTextAt(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* 9742 blastTextColour */
GS_INLINE void op_blastTextColour(gs_VmContext* ctx, int32 col) {
	/* TODO */
}

/* 9743 blastTextClipped */
GS_INLINE void op_blastTextClipped(gs_VmContext* ctx, int32 right) {
	/* TODO */
}

/* 9745 blastTextCentre */
GS_INLINE void op_blastTextCentre(gs_VmContext* ctx) {
	/* TODO */
}

/* 9747 blastTextLeft */
GS_INLINE void op_blastTextLeft(gs_VmContext* ctx) {
	/* TODO */
}

/* 9748 blastTextOverhead */
GS_INLINE void op_blastTextOverhead(gs_VmContext* ctx) {
	/* TODO */
}

/* 974A blastTextMumble */
GS_INLINE void op_blastTextMumble(gs_VmContext* ctx) {
	/* TODO */
}

/* 974B blastTextText */
GS_INLINE void op_blastTextText(gs_VmContext* ctx, char* text) {
	/* TODO */
}

/* 97FE blastTextLoadDefault */
GS_INLINE void op_blastTextLoadDefault(gs_VmContext* ctx) {
	/* TODO */
}

/* 97FF blastTextSaveDefault */
GS_INLINE void op_blastTextSaveDefault(gs_VmContext* ctx) {
	/* TODO */
}

/* 98 drawObject */
GS_PRIVATE GS_INLINE void op_drawObject(gs_VmContext* ctx, int32 obj, int32 x, int32 y, int32 state) {
	/* TODO */
}

/* 9CDC cursorOn */
GS_INLINE void op_cursorOn(gs_VmContext* ctx) {
	/* TODO */
}

/* 9CDD cursorOff */
GS_INLINE void op_cursorOff(gs_VmContext* ctx) {
	/* TODO */
}

/* 9CDE cursorSoftOn */
GS_INLINE void op_cursorSoftOn(gs_VmContext* ctx) {
	/* TODO */
}

/* 9CDF cursorSoftOff */
GS_INLINE void op_cursorSoftOff(gs_VmContext* ctx) {
	/* TODO */
}

/* 9CE0 cursorUserPutOn */
GS_INLINE void op_cursorUserPutOn(gs_VmContext* ctx) {
	/* TODO */
}

/* 9CE1 cursorUserPutOff */
GS_INLINE void op_cursorUserPutOff(gs_VmContext* ctx) {
	/* TODO */
}

/* 9CE2 cursorUserPutSoftOn */
GS_INLINE void op_cursorUserPutSoftOn(gs_VmContext* ctx) {
	/* TODO */
}

/* 9CE3 cursorUserPutSoftOff */
GS_INLINE void op_cursorUserPutSoftOff(gs_VmContext* ctx) {
	/* TODO */
}

/* 9CE4 cursorUserCursorImage */
GS_INLINE void op_cursorUserCursorImage(gs_VmContext* ctx, int32 idx, int32 obj) {
	/* TODO */
}

/* 9CE5 cursorHotSpot */
GS_INLINE void op_cursorHotSpot(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* 9CE6 cursorSetTransparency */
GS_INLINE void op_cursorSetTransparency(gs_VmContext* ctx, int32 enabled) {
	/* TODO */
}

/* 9CE7 cursorSetCharSet */
GS_INLINE void op_cursorSetCharSet(gs_VmContext* ctx, int32 charsetNum) {
	/* TODO */
}

/* 9CE8 cursorSetColour */
GS_INLINE void op_cursorSetColour(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* 9CE9 cursorSetPos */
GS_INLINE void op_cursorSetPos(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* 9D loadRoom */
GS_PRIVATE GS_INLINE void op_loadRoom(gs_VmContext* ctx, byte room) {
	/* TODO */
}

/* 9E loadRoomWithEgo */
GS_PRIVATE GS_INLINE void op_loadRoomWithEgo(gs_VmContext* ctx, int32 x, int32 y, int32 room) {
	/* TODO */
}

/* 9F walkActorToObj */
GS_PRIVATE GS_INLINE void op_walkActorToObj(gs_VmContext* ctx, int32 index, int32 obj, int32 dist) {
	/* TODO */
}

/* A0 walkActorTo */
GS_PRIVATE GS_INLINE void op_walkActorTo(gs_VmContext* ctx, int32 index, int32 x, int32 y) {
	/* TODO */
}

/* A1 putActorAtXY */
GS_PRIVATE GS_INLINE void op_putActorAtXY(gs_VmContext* ctx, int32 actorIndex, int32 x, int32 y, int32 room) {
	/* TODO */
}

/* A2 putActorAtObject */
GS_PRIVATE GS_INLINE void op_putActorAtObject(gs_VmContext* ctx, int32 obj) {
	/* TODO */
}

/* A3 faceActor */
GS_PRIVATE GS_INLINE void op_faceActor(gs_VmContext* ctx, int32 index, int32 obj) {
	/* TODO */
}

/* A4 animateActor */
GS_PRIVATE GS_INLINE void op_animateActor(gs_VmContext* ctx, int32 index, int32 anim) {
	/* TODO */
}

/* A5 doSentence */
GS_PRIVATE GS_INLINE void op_doSentence(gs_VmContext* ctx, byte verb, int16 objectA, int16 objectB) {
	/* TODO */
}

/* A6 pickupObject */
GS_PRIVATE GS_INLINE void op_pickupObject(gs_VmContext* ctx, int32 obj) {
	/* TODO */
}

/* A7 setBoxFlags */
GS_PRIVATE GS_INLINE void op_setBoxFlags(gs_VmContext* ctx, int32 argsLength, int32* args, int32 value) {
	/* TODO */
}

/* A8 createBoxMatrix */
GS_PRIVATE GS_INLINE void op_createBoxMatrix(gs_VmContext* ctx) {
	/* TODO */
}

/* A9 wait */
GS_PRIVATE GS_INLINE void op_wait(gs_VmContext* ctx) {
	/* TODO */
}

/* AA3C resourceRoutine3C */
GS_INLINE void op_resourceRoutine3C(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA3D loadCostume */
GS_INLINE void op_loadCostume(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA3E loadObject */
GS_INLINE void op_loadObject(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA3F loadRoom */
GS_INLINE void op_loadRoom(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA40 loadScript */
GS_INLINE void op_loadScript(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA41 loadSound */
GS_INLINE void op_loadSound(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA42 lockCostume */
GS_INLINE void op_lockCostume(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA43 lockRoom */
GS_INLINE void op_lockRoom(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA44 lockScript */
GS_INLINE void op_lockScript(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA45 lockSound */
GS_INLINE void op_lockSound(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA46 unlockCostume */
GS_INLINE void op_unlockCostume(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA47 unlockRoom */
GS_INLINE void op_unlockRoom(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA48 unlockScript */
GS_INLINE void op_unlockScript(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA49 unlockSound */
GS_INLINE void op_unlockSound(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA4A unloadCostume */
GS_INLINE void op_unloadCostume(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA4B unloadRoom */
GS_INLINE void op_unloadRoom(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA4C unloadScript */
GS_INLINE void op_unloadScript(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA4D unloadSound */
GS_INLINE void op_unloadSound(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AB52 setRoomRGB */
GS_INLINE void op_setRoomRGB(gs_VmContext* ctx, byte r, byte g, byte b, int32 index) {
	/* TODO */
}

/* AB57 fadeRoom */
GS_INLINE void op_fadeRoom(gs_VmContext* ctx, int32 param) {
	/* TODO */
}

/* AB58 setRoomRGBIntensity */
GS_INLINE void op_setRoomRGBIntensity(gs_VmContext* ctx, int32 redScale, int32 greenScale, int32 blueScale, int16 startColour, int16 endColour) {
	/* TODO */
}

/* AB59 setRoomRGBTransform */
GS_INLINE void op_setRoomRGBTransform(gs_VmContext* ctx, int32 resId, int16 start, int16 end, int32 time) {
	/* TODO */
}

/* AB5C setRoomPalette */
GS_INLINE void op_setRoomPalette(gs_VmContext* ctx, int16 paletteNum) {
	/* TODO */
}

/* AB5D saveGame */
GS_INLINE void op_saveGame(gs_VmContext* ctx) {
	/* TODO */
}

/* AB5E loadGame */
GS_INLINE void op_loadGame(gs_VmContext* ctx, byte saveSound) {
	/* TODO */
}

/* AB5F setRoomSaturation */
GS_INLINE void op_setRoomSaturation(gs_VmContext* ctx, int32 hueScale, int32 satScale, int32 lightScale, int16 startColour, int16 endColour) {
	/* TODO */
}

/* AC64 setActorCostume */
GS_INLINE void op_setActorCostume(gs_VmContext* ctx, int16 costumeNum) {
	/* TODO */
}

/* AC65 setActorWalkSpeed */
GS_INLINE void op_setActorWalkSpeed(gs_VmContext* ctx, int16 x, int16 y) {
	/* TODO */
}

/* AC67 setActorAnimationDefault */
GS_INLINE void op_setActorAnimationDefault(gs_VmContext* ctx) {
	/* TODO */
}

/* AC68 setActorAnimationInit */
GS_INLINE void op_setActorAnimationInit(gs_VmContext* ctx, byte frameNum) {
	/* TODO */
}

/* AC69 setActorAnimationTalk */
GS_INLINE void op_setActorAnimationTalk(gs_VmContext* ctx, byte startFrameNum, byte endFrameNum) {
	/* TODO */
}

/* AC6A setActorAnimationWalk */
GS_INLINE void op_setActorAnimationWalk(gs_VmContext* ctx, byte walkFrameNum) {
	/* TODO */
}

/* AC6B setActorAnimationStand */
GS_INLINE void op_setActorAnimationStand(gs_VmContext* ctx, byte standFrameNum) {
	/* TODO */
}

/* AC6C setActorAnimationSpeed */
GS_INLINE void op_setActorAnimationSpeed(gs_VmContext* ctx, byte animationSpeed) {
	/* TODO */
}

/* AC6D setActorDefault */
GS_INLINE void op_setActorDefault(gs_VmContext* ctx) {
	/* TODO */
}

/* AC6E setActorElevation */
GS_INLINE void op_setActorElevation(gs_VmContext* ctx, int16 elevation) {
	/* TODO */
}

/* AC6F setActorPalette */
GS_INLINE void op_setActorPalette(gs_VmContext* ctx, byte index, int16 value) {
	/* TODO */
}

/* AC70 setActorTalkColour */
GS_INLINE void op_setActorTalkColour(gs_VmContext* ctx, byte colourIndex) {
	/* TODO */
}

/* AC71 setActorName */
GS_INLINE void op_setActorName(gs_VmContext* ctx, char* text) {
	/* TODO */
}

/* AC72 setActorWidth */
GS_INLINE void op_setActorWidth(gs_VmContext* ctx, int16 width) {
	/* TODO */
}

/* AC73 setActorScale */
GS_INLINE void op_setActorScale(gs_VmContext* ctx, int16 size) {
	/* TODO */
}

/* AC74 setActorNeverZClip */
GS_INLINE void op_setActorNeverZClip(gs_VmContext* ctx) {
	/* TODO */
}

/* AC75 setActorAlwaysZClip */
GS_INLINE void op_setActorAlwaysZClip(gs_VmContext* ctx, byte forceClip) {
	/* TODO */
}

/* AC76 setActorIgnoreBoxes */
GS_INLINE void op_setActorIgnoreBoxes(gs_VmContext* ctx) {
	/* TODO */
}

/* AC77 setActorFollowBoxes */
GS_INLINE void op_setActorFollowBoxes(gs_VmContext* ctx) {
	/* TODO */
}

/* AC78 setActorSpecialDraw */
GS_INLINE void op_setActorSpecialDraw(gs_VmContext* ctx) {
	/* TODO */
}

/* AC79 setActorTextOffset */
GS_INLINE void op_setActorTextOffset(gs_VmContext* ctx, int16 x, int16 y) {
	/* TODO */
}

/* AC7B setActorVar */
GS_INLINE void op_setActorVar(gs_VmContext* ctx, int32 name, int32 value) {
	/* TODO */
}

/* AC7C setActorIgnoreTurns */
GS_INLINE void op_setActorIgnoreTurns(gs_VmContext* ctx) {
	/* TODO */
}

/* AC7D setActorFollowTurns */
GS_INLINE void op_setActorFollowTurns(gs_VmContext* ctx) {
	/* TODO */
}

/* AC7E setActorNew */
GS_INLINE void op_setActorNew(gs_VmContext* ctx) {
	/* TODO */
}

/* AC7F setActorDepth */
GS_INLINE void op_setActorDepth(gs_VmContext* ctx, int16 depth) {
	/* TODO */
}

/* AC80 setActorStop */
GS_INLINE void op_setActorStop(gs_VmContext* ctx) {
	/* TODO */
}

/* AC81 setActorDirection */
GS_INLINE void op_setActorDirection(gs_VmContext* ctx, int16 direction) {
	/* TODO */
}

/* AC82 actorTurn */
GS_INLINE void op_actorTurn(gs_VmContext* ctx, int16 direction) {
	/* TODO */
}

/* AC83 setActorWalkScript */
GS_INLINE void op_setActorWalkScript(gs_VmContext* ctx, int16 scriptNum) {
	/* TODO */
}

/* AC84 setActorTalkScript */
GS_INLINE void op_setActorTalkScript(gs_VmContext* ctx, int16 scriptNum) {
	/* TODO */
}

/* AC85 setActorWalkingFrozen */
GS_INLINE void op_setActorWalkingFrozen(gs_VmContext* ctx) {
	/* TODO */
}

/* AC86 setActorWalkingResume */
GS_INLINE void op_setActorWalkingResume(gs_VmContext* ctx) {
	/* TODO */
}

/* AC87 setActorTalkVolume */
GS_INLINE void op_setActorTalkVolume(gs_VmContext* ctx, int32 volume) {
	/* TODO */
}

/* AC88 setActorTalkFrequency */
GS_INLINE void op_setActorTalkFrequency(gs_VmContext* ctx, int32 frequency) {
	/* TODO */
}

/* AC89 setActorTalkPan */
GS_INLINE void op_setActorTalkPan(gs_VmContext* ctx, int32 pan) {
	/* TODO */
}

/* AD32 setCameraPause */
GS_INLINE void op_setCameraPause(gs_VmContext* ctx) {
	/* TODO */
}

/* AD33 setCameraResume */
GS_INLINE void op_setCameraResume(gs_VmContext* ctx) {
	/* TODO */
}

/* AE96 initVerb */
GS_INLINE void op_initVerb(gs_VmContext* ctx, int16 verbNum) {
	/* TODO */
}

/* AE97 newVerb */
GS_INLINE void op_newVerb(gs_VmContext* ctx, int16 verbNum) {
	/* TODO */
}

/* AE98 deleteVerb */
GS_INLINE void op_deleteVerb(gs_VmContext* ctx, int16 verbNum) {
	/* TODO */
}

/* AE99 setVerbName */
GS_INLINE void op_setVerbName(gs_VmContext* ctx, char* name) {
	/* TODO */
}

/* AE9A setVerbXY */
GS_INLINE void op_setVerbXY(gs_VmContext* ctx, int16 x, int16 y) {
	/* TODO */
}

/* AE9B setVerbOn */
GS_INLINE void op_setVerbOn(gs_VmContext* ctx) {
	/* TODO */
}

/* AE9C setVerbOff */
GS_INLINE void op_setVerbOff(gs_VmContext* ctx) {
	/* TODO */
}

/* AE9D setVerbColour */
GS_INLINE void op_setVerbColour(gs_VmContext* ctx, byte colourIndex) {
	/* TODO */
}

/* AE9E setVerbHilightColour */
GS_INLINE void op_setVerbHilightColour(gs_VmContext* ctx, byte colourIndex) {
	/* TODO */
}

/* AEA0 setVerbDimColour */
GS_INLINE void op_setVerbDimColour(gs_VmContext* ctx, byte colourIndex) {
	/* TODO */
}

/* AEA1 setVerbDim */
GS_INLINE void op_setVerbDim(gs_VmContext* ctx) {
	/* TODO */
}

/* AEA2 setVerbKey */
GS_INLINE void op_setVerbKey(gs_VmContext* ctx, byte keyCode) {
	/* TODO */
}

/* AEA3 setVerbImage */
GS_INLINE void op_setVerbImage(gs_VmContext* ctx, int16 objectNum, byte roomNum) {
	/* TODO */
}

/* AEA4 setVerbNameStr */
GS_INLINE void op_setVerbNameStr(gs_VmContext* ctx, int32 textAddress) {
	/* TODO */
}

/* AEA5 setVerbCenter */
GS_INLINE void op_setVerbCenter(gs_VmContext* ctx) {
	/* TODO */
}

/* AEA6 setVerbCharSet */
GS_INLINE void op_setVerbCharSet(gs_VmContext* ctx, byte charSetNum) {
	/* TODO */
}

/* AEA7 setVerbLinesSpacing */
GS_INLINE void op_setVerbLinesSpacing(gs_VmContext* ctx, int16 lineSpacing) {
	/* TODO */
}

/* AF startSound */
GS_PRIVATE GS_INLINE void op_startSound(gs_VmContext* ctx, int32 sound) {
	/* TODO */
}

/* B0 startMusic */
GS_PRIVATE GS_INLINE void op_startMusic(gs_VmContext* ctx, int32 sound) {
	/* TODO */
}

/* B1 stopSound */
GS_PRIVATE GS_INLINE void op_stopSound(gs_VmContext* ctx, int32 sound) {
	/* TODO */
}

/* B2 soundKludge */
GS_PRIVATE GS_INLINE void op_soundKludge(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* B39E restartGame */
GS_INLINE void op_restartGame(gs_VmContext* ctx) {
	/* TODO */
}

/* B39F pauseGame */
GS_INLINE void op_pauseGame(gs_VmContext* ctx) {
	/* TODO */
}

/* B3A0 quitGame */
GS_INLINE void op_quitGame(gs_VmContext* ctx) {
	/* TODO */
}

/* B4 saveRestoreVerbs */
GS_PRIVATE GS_INLINE void op_saveRestoreVerbs(gs_VmContext* ctx, int32 a, int32 b, int32 c) {
	/* TODO */
}

/* B5 setObjectName */
GS_PRIVATE GS_INLINE void op_setObjectName(gs_VmContext* ctx, int32 obj, char* name) {
	/* TODO */
}

/* B6 getDateTime */
GS_PRIVATE GS_INLINE void op_getDateTime(gs_VmContext* ctx) {
	/* TODO */
}

/* B7 drawBox */
GS_PRIVATE GS_INLINE void op_drawBox(gs_VmContext* ctx, int32 x, int32 y, int32 x2, int32 y2, int32 color) {
	/* TODO */
}

/* B9 startVideo */
GS_PRIVATE GS_INLINE void op_startVideo(gs_VmContext* ctx, char* fileName) {
	/* TODO */
}

/* BA0B lockObject */
GS_INLINE void op_lockObject(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA0C unlockObject */
GS_INLINE void op_unlockObject(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA0D remapCostumePalette */
GS_INLINE void op_remapCostumePalette(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA0E remapCostumeInsert */
GS_INLINE void op_remapCostumeInsert(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA0F setVideoFrameRate */
GS_INLINE void op_setVideoFrameRate(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA14 setBoxScaleSlot */
GS_INLINE void op_setBoxScaleSlot(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA15 setScaleSlot */
GS_INLINE void op_setScaleSlot(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA16 setBannerColours */
GS_INLINE void op_setBannerColours(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA17 setActorChoreLimbFrame */
GS_INLINE void op_setActorChoreLimbFrame(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA18 clearTextQueue */
GS_INLINE void op_clearTextQueue(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA19 saveGameReadName */
GS_INLINE void op_saveGameReadName(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA1A saveGameWrite */
GS_INLINE void op_saveGameWrite(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA1B saveGameRead */
GS_INLINE void op_saveGameRead(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA1C saveGameScreenshot */
GS_INLINE void op_saveGameScreenshot(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA1D setKeyScript */
GS_INLINE void op_setKeyScript(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA1E killAllScriptsExceptCurrent */
GS_INLINE void op_killAllScriptsExceptCurrent(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA1F stopAllVideo */
GS_INLINE void op_stopAllVideo(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA20 writeRegistryValue */
GS_INLINE void op_writeRegistryValue(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA21 setPaletteIntensity */
GS_INLINE void op_setPaletteIntensity(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA22 queryQuit */
GS_INLINE void op_queryQuit(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA6C buildPaletteShadow */
GS_INLINE void op_buildPaletteShadow(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA6D setPaletteShadow */
GS_INLINE void op_setPaletteShadow(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA6E blastShadowObject */
GS_INLINE void op_blastShadowObject(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA6F superBlastObject */
GS_INLINE void op_superBlastObject(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* C0 dim2DimArray */
GS_PRIVATE GS_INLINE void op_dim2DimArray(gs_VmContext* ctx, int32 dim2, int32 dim1) {
	/* TODO */
}

/* C6 distObjectPt */
GS_PRIVATE GS_INLINE void op_distObjectPt(gs_VmContext* ctx, int32 a, int32 b, int32 c) {
	/* TODO */
}

/* C8 startScriptQuick2 */
GS_PRIVATE GS_INLINE void op_startScriptQuick2(gs_VmContext* ctx, int32 script, int32 argsLength, int32* args) {
	/* TODO */
}

/* C9 startObjectQuick */
GS_PRIVATE GS_INLINE void op_startObjectQuick(gs_VmContext* ctx, int32 script, byte entryPc, int32 argsLength, int32* args) {
	/* TODO */
}

/* CA pickOneOf */
GS_PRIVATE GS_INLINE void op_pickOneOf(gs_VmContext* ctx, int32 i, int32 argsLength, int32* args) {
	/* TODO */
}

/* CB pickOneOfDefault */
GS_PRIVATE GS_INLINE void op_pickOneOfDefault(gs_VmContext* ctx, int32 i, int32 argsLength, int32* args, int32 def) {
	/* TODO */
}

/* CD isAnyOf */
GS_PRIVATE GS_INLINE void op_isAnyOf(gs_VmContext* ctx, int32 value, int32 argsLength, int32* args) {
	/* TODO */
}

/* CE getRandomNumber */
GS_PRIVATE GS_INLINE void op_getRandomNumber(gs_VmContext* ctx, int32 max) {
	/* TODO */
}

/* CF getRandomNumberRange */
GS_PRIVATE GS_INLINE void op_getRandomNumberRange(gs_VmContext* ctx, int32 min, int32 max) {
	/* TODO */
}

/* D0 ifClassOfIs */
GS_PRIVATE GS_INLINE void op_ifClassOfIs(gs_VmContext* ctx, int32 obj, int32 argsLength, int32* args) {
	/* TODO */
}

/* D1 getState */
GS_PRIVATE GS_INLINE void op_getState(gs_VmContext* ctx, int32 obj) {
	/* TODO */
}

/* D2 getOwner */
GS_PRIVATE GS_INLINE void op_getOwner(gs_VmContext* ctx, int32 obj) {
	/* TODO */
}

/* D3 isScriptRunning */
GS_PRIVATE GS_INLINE void op_isScriptRunning(gs_VmContext* ctx, int32 script) {
	/* TODO */
}

/* D4 shuffle */
GS_PRIVATE GS_INLINE void op_shuffle(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* D5 isSoundRunning */
GS_PRIVATE GS_INLINE void op_isSoundRunning(gs_VmContext* ctx, int32 sound) {
	/* TODO */
}

/* D6 abs */
GS_PRIVATE GS_INLINE void op_abs(gs_VmContext* ctx, int32 value) {
	/* TODO */
}

/* D873 getWalkBoxAt */
GS_INLINE void op_getWalkBoxAt(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D874 isPointInBox */
GS_INLINE void op_isPointInBox(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8CE getRGBSlot */
GS_INLINE void op_getRGBSlot(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8D3 getKeyState */
GS_INLINE void op_getKeyState(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8D7 getBox */
GS_INLINE void op_getBox(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8D8 findBlastObject */
GS_INLINE void op_findBlastObject(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8D9 actorHitTest */
GS_INLINE void op_actorHitTest(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8DA setLipSyncWidth */
GS_INLINE void op_setLipSyncWidth(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8DB setLipSyncHeight */
GS_INLINE void op_setLipSyncHeight(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8DC setTalkAnimation */
GS_INLINE void op_setTalkAnimation(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8DD getGroupSfxVol */
GS_INLINE void op_getGroupSfxVol(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8DE getGroupVoiceVol */
GS_INLINE void op_getGroupVoiceVol(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8DF getGroupMusicVol */
GS_INLINE void op_getGroupMusicVol(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8E0 readRegistryValue */
GS_INLINE void op_readRegistryValue(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8E1 imuseGetMusicPosition */
GS_INLINE void op_imuseGetMusicPosition(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8E2 imuseGetMusicLipSyncWidth */
GS_INLINE void op_imuseGetMusicLipSyncWidth(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8E3 imuseGetMusicLipSyncHeight */
GS_INLINE void op_imuseGetMusicLipSyncHeight(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D9 isActorInBox */
GS_PRIVATE GS_INLINE void op_isActorInBox(gs_VmContext* ctx, int32 index, int32 box) {
	/* TODO */
}

/* DA getVerbEntrypoint */
GS_PRIVATE GS_INLINE void op_getVerbEntrypoint(gs_VmContext* ctx, int32 verb, int32 entryp) {
	/* TODO */
}

/* DB getActorFromXY */
GS_PRIVATE GS_INLINE void op_getActorFromXY(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* DC findObject */
GS_PRIVATE GS_INLINE void op_findObject(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* DD getVerbFromXY */
GS_PRIVATE GS_INLINE void op_getVerbFromXY(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* DF findInventory */
GS_PRIVATE GS_INLINE void op_findInventory(gs_VmContext* ctx, int32 owner, int32 index) {
	/* TODO */
}

/* E0 getInventoryCount */
GS_PRIVATE GS_INLINE void op_getInventoryCount(gs_VmContext* ctx, int32 owner) {
	/* TODO */
}

/* E1 getAnimateVariable */
GS_PRIVATE GS_INLINE void op_getAnimateVariable(gs_VmContext* ctx, int32 index, int32 variable) {
	/* TODO */
}

/* E2 getActorRoom */
GS_PRIVATE GS_INLINE void op_getActorRoom(gs_VmContext* ctx, int32 index) {
	/* TODO */
}

/* E3 getActorWalkBox */
GS_PRIVATE GS_INLINE void op_getActorWalkBox(gs_VmContext* ctx, int32 index) {
	/* TODO */
}

/* E4 getActorMoving */
GS_PRIVATE GS_INLINE void op_getActorMoving(gs_VmContext* ctx, int32 index) {
	/* TODO */
}

/* E5 getActorCostume */
GS_PRIVATE GS_INLINE void op_getActorCostume(gs_VmContext* ctx, int32 index) {
	/* TODO */
}

/* E6 getActorScaleX */
GS_PRIVATE GS_INLINE void op_getActorScaleX(gs_VmContext* ctx, int32 index) {
	/* TODO */
}

/* E7 getActorLayer */
GS_PRIVATE GS_INLINE void op_getActorLayer(gs_VmContext* ctx, int32 index) {
	/* TODO */
}

/* E8 getActorElevation */
GS_PRIVATE GS_INLINE void op_getActorElevation(gs_VmContext* ctx, int32 index) {
	/* TODO */
}

/* E9 getActorWidth */
GS_PRIVATE GS_INLINE void op_getActorWidth(gs_VmContext* ctx, int32 index) {
	/* TODO */
}

/* EA getObjectNewDir */
GS_PRIVATE GS_INLINE void op_getObjectNewDir(gs_VmContext* ctx, int32 index) {
	/* TODO */
}

/* EB getObjectX */
GS_PRIVATE GS_INLINE void op_getObjectX(gs_VmContext* ctx, int32 index) {
	/* TODO */
}

/* EC getObjectY */
GS_PRIVATE GS_INLINE void op_getObjectY(gs_VmContext* ctx, int32 index) {
	/* TODO */
}

/* ED getActorChore */
GS_PRIVATE GS_INLINE void op_getActorChore(gs_VmContext* ctx, int16 actorNum) {
	/* TODO */
}

/* EE distObjectObject */
GS_PRIVATE GS_INLINE void op_distObjectObject(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* EF distObjectPtPt */
GS_PRIVATE GS_INLINE void op_distObjectPtPt(gs_VmContext* ctx, int32 a, int32 b, int32 c, int32 d) {
	/* TODO */
}

/* F0 getObjectImageX */
GS_PRIVATE GS_INLINE void op_getObjectImageX(gs_VmContext* ctx, int16 objectNum) {
	/* TODO */
}

/* F1 getObjectImageY */
GS_PRIVATE GS_INLINE void op_getObjectImageY(gs_VmContext* ctx, int16 objectNum) {
	/* TODO */
}

/* F2 getObjectImageWidth */
GS_PRIVATE GS_INLINE void op_getObjectImageWidth(gs_VmContext* ctx, int16 objectNum) {
	/* TODO */
}

/* F3 getObjectImageHeight */
GS_PRIVATE GS_INLINE void op_getObjectImageHeight(gs_VmContext* ctx, int16 objectNum) {
	/* TODO */
}

/* F6 getStringWidth */
GS_PRIVATE GS_INLINE void op_getStringWidth(gs_VmContext* ctx, char* text, int16 charsetNum) {
	/* TODO */
}

/* F7 getActorZPlane */
GS_PRIVATE GS_INLINE void op_getActorZPlane(gs_VmContext* ctx, int16 actorNum) {
	/* TODO */
}






void decoder(gs_VmContext* ctx, byte op1, byte op2) {
	switch(op1) {
		default:
			return 1;
		/* pushByte */
		case 0x00: {
			byte value = readByte();
			op_pushByte(ctx, value);
		}
		return 0;
		/* pushWord */
		case 0x01: {
			int32 value = readLong();
			op_pushWord(ctx, value);
		}
		return 0;
		/* pushWordVar */
		case 0x02: {
			int32 name = readLong();
			op_pushWordVar(ctx, name);
		}
		return 0;
		/* wordArrayRead */
		case 0x03: {
			int32 base = pullStackLong();
			op_wordArrayRead(ctx, base);
		}
		return 0;
		/* wordArrayIndexedRead */
		case 0x04: {
			int32 arrayNum = readLong();
			int32 base = pullStackLong();
			int32 index = pullStackLong();
			op_wordArrayIndexedRead(ctx, index, base, arrayNum);
		}
		return 0;
		/* dup */
		case 0x05: {
			int32 value = pullStackLong();
			op_dup(ctx, value);
		}
		return 0;
		/* pop */
		case 0x06: {
			int32 discard = pullStackLong();
			op_pop(ctx, discard);
		}
		return 0;
		/* not */
		case 0x07: {
			int32 value = pullStackLong();
			op_not(ctx, value);
		}
		return 0;
		/* eq */
		case 0x08: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_eq(ctx, left, right);
		}
		return 0;
		/* neq */
		case 0x09: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_neq(ctx, left, right);
		}
		return 0;
		/* gt */
		case 0x0A: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_gt(ctx, left, right);
		}
		return 0;
		/* lt */
		case 0x0B: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_lt(ctx, left, right);
		}
		return 0;
		/* le */
		case 0x0C: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_le(ctx, left, right);
		}
		return 0;
		/* ge */
		case 0x0D: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_ge(ctx, left, right);
		}
		return 0;
		/* add */
		case 0x0E: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_add(ctx, left, right);
		}
		return 0;
		/* sub */
		case 0x0F: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_sub(ctx, left, right);
		}
		return 0;
		/* mul */
		case 0x10: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_mul(ctx, left, right);
		}
		return 0;
		/* div */
		case 0x11: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_div(ctx, left, right);
		}
		return 0;
		/* land */
		case 0x12: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_land(ctx, left, right);
		}
		return 0;
		/* lor */
		case 0x13: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_lor(ctx, left, right);
		}
		return 0;
		/* band */
		case 0x14: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_band(ctx, left, right);
		}
		return 0;
		/* bor */
		case 0x15: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_bor(ctx, left, right);
		}
		return 0;
		/* mod */
		case 0x16: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_mod(ctx, left, right);
		}
		return 0;
		/* writeByteVar */
		case 0x42: {
			int32 value = pullStackLong();
			op_writeByteVar(ctx, value);
		}
		return 0;
		/* byteArrayWrite */
		case 0x46: {
			int32 value = pullStackLong();
			int32 base = pullStackLong();
			op_byteArrayWrite(ctx, base, value);
		}
		return 0;
		/* byteArrayIndexedWrite */
		case 0x4A: {
			int32 value = pullStackLong();
			int32 base = pullStackLong();
			int32 index = pullStackLong();
			op_byteArrayIndexedWrite(ctx, index, base, value);
		}
		return 0;
		/* byteVarInc */
		case 0x4E: {
			op_byteVarInc(ctx);
		}
		return 0;
		/* byteArrayInc */
		case 0x52: {
			int32 base = pullStackLong();
			op_byteArrayInc(ctx, base);
		}
		return 0;
		/* byteVarDec */
		case 0x56: {
			op_byteVarDec(ctx);
		}
		return 0;
		/* byteArrayDec */
		case 0x5A: {
			int32 base = pullStackLong();
			op_byteArrayDec(ctx, base);
		}
		return 0;
		/* drawObject */
		case 0x61: {
			int32 state = pullStackLong();
			int32 obj = pullStackLong();
			op_drawObject(ctx, obj, state);
		}
		return 0;
		/* drawObjectAt */
		case 0x62: {
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			int32 obj = pullStackLong();
			op_drawObjectAt(ctx, obj, x, y);
		}
		return 0;
		/* drawBlastObject */
		case 0x63: {
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			int32 e = pullStackLong();
			int32 d = pullStackLong();
			int32 c = pullStackLong();
			int32 b = pullStackLong();
			int32 a = pullStackLong();
			op_drawBlastObject(ctx, a, b, c, d, e, argsLength, args);
		}
		return 0;
		/* if */
		case 0x64: {
			int32 offset = readLong();
			int32 condition = pullStackLong();
			op_if(ctx, condition, offset);
		}
		return 0;
		/* ifNot */
		case 0x65: {
			int32 offset = readLong();
			int32 condition = pullStackLong();
			op_ifNot(ctx, condition, offset);
		}
		return 0;
		/* jump */
		case 0x66: {
			int32 offset = readLong();
			op_jump(ctx, offset);
		}
		return 0;
		/* breakHere */
		case 0x67: {
			op_breakHere(ctx);
		}
		return 0;
		/* delayFrames */
		case 0x68: {
			op_delayFrames(ctx);
		}
		return 0;
		case 0x69: {
			consumeByte();
			switch(op2) {
				default:
					return 1;
				/* waitActor */
				case 0x1E: {
					int32 actorNum = pullStackLong();
					int32 offset = readLong();
					op_waitActor(ctx, offset, actorNum);
				}
				return 0;
				/* waitMessage */
				case 0x1F: {
					op_waitMessage(ctx);
				}
				return 0;
				/* waitCamera */
				case 0x20: {
					op_waitCamera(ctx);
				}
				return 0;
				/* waitSentence */
				case 0x21: {
					op_waitSentence(ctx);
				}
				return 0;
				/* waitAnimation */
				case 0x22: {
					op_waitAnimation(ctx);
				}
				return 0;
				/* waitTurn */
				case 0x23: {
					int32 actorNum = pullStackLong();
					int32 offset = readLong();
					op_waitTurn(ctx, offset, actorNum);
				}
				return 0;
		}
		return 1;
		/* delay */
		case 0x6A: {
			int32 delay = pullStackLong();
			op_delay(ctx, delay);
		}
		return 0;
		/* delaySeconds */
		case 0x6B: {
			int32 seconds = pullStackLong();
			op_delaySeconds(ctx, seconds);
		}
		return 0;
		/* delayMinutes */
		case 0x6C: {
			int32 minutes = pullStackLong();
			op_delayMinutes(ctx, minutes);
		}
		return 0;
		/* writeWordVar */
		case 0x6D: {
			int32 value = pullStackLong();
			op_writeWordVar(ctx, value);
		}
		return 0;
		/* wordVarInc */
		case 0x6E: {
			int32 var = readLong();
			op_wordVarInc(ctx, var);
		}
		return 0;
		/* wordVarDec */
		case 0x6F: {
			int32 var = readLong();
			op_wordVarDec(ctx, var);
		}
		return 0;
		case 0x70: {
			consumeByte();
			switch(op2) {
				default:
					return 1;
				/* newArrayInt */
				case 0x0A: {
					int32 dim1 = pullStackLong();
					int32 arrayNum = readLong();
					op_newArrayInt(ctx, arrayNum, dim1);
				}
				return 0;
				/* newArrayString */
				case 0x0B: {
					int32 dim1 = pullStackLong();
					int32 arrayNum = readLong();
					op_newArrayString(ctx, arrayNum, dim1);
				}
				return 0;
				/* deleteArray */
				case 0x0C: {
					int32 arrayNum = readLong();
					op_deleteArray(ctx, arrayNum);
				}
				return 0;
		}
		return 1;
		/* wordArrayWrite */
		case 0x71: {
			int32 value = pullStackLong();
			int32 base = pullStackLong();
			op_wordArrayWrite(ctx, base, value);
		}
		return 0;
		/* wordArrayInc */
		case 0x72: {
			int32 base = pullStackLong();
			op_wordArrayInc(ctx, base);
		}
		return 0;
		/* wordArrayDec */
		case 0x73: {
			int32 base = pullStackLong();
			op_wordArrayDec(ctx, base);
		}
		return 0;
		case 0x74: {
			consumeByte();
			switch(op2) {
				default:
					return 1;
				/* newArray2Int */
				case 0x0A: {
					int32 dim2 = pullStackLong();
					int32 dim1 = pullStackLong();
					int32 arrayNum = readLong();
					op_newArray2Int(ctx, arrayNum, dim1, dim2);
				}
				return 0;
				/* newArray2String */
				case 0x0B: {
					int32 dim2 = pullStackLong();
					int32 dim1 = pullStackLong();
					int32 arrayNum = readLong();
					op_newArray2String(ctx, arrayNum, dim1, dim2);
				}
				return 0;
				/* deleteArray2 */
				case 0x0C: {
					int32 arrayNum = readLong();
					op_deleteArray2(ctx, arrayNum);
				}
				return 0;
		}
		return 1;
		/* wordArrayIndexedWrite */
		case 0x75: {
			int32 arrayNum = readLong();
			int32 value = pullStackLong();
			int32 base = pullStackLong();
			int32 index = pullStackLong();
			op_wordArrayIndexedWrite(ctx, index, base, value, arrayNum);
		}
		return 0;
		case 0x76: {
			consumeByte();
			switch(op2) {
				default:
					return 1;
				/* setArrayString */
				case 0x14: {
					int32 arrayNum = readLong();
					int32 offset = pullStackLong();
					char* string = readText();
					op_setArrayString(ctx, string, offset, arrayNum);
				}
				return 0;
				/* setArrayList */
				case 0x15: {
					int32 arrayNum = readLong();
					int32 offset = pullStackLong();
					int32 listLength = pullStack();
					int32* list = pullList(listLength, 25);
					op_setArrayList(ctx, listLength, list, offset, arrayNum);
				}
				return 0;
				/* setArray2List */
				case 0x16: {
					int32 arrayNum = readLong();
					int32 offset = pullStackLong();
					int32 listLength = pullStack();
					int32* list = pullList(listLength, 25);
					op_setArray2List(ctx, listLength, list, offset, arrayNum);
				}
				return 0;
		}
		return 1;
		/* startScript */
		case 0x79: {
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			int32 script = pullStackLong();
			int32 flags = pullStackLong();
			op_startScript(ctx, flags, script, argsLength, args);
		}
		return 0;
		/* startScriptQuick */
		case 0x7A: {
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			int32 script = pullStackLong();
			op_startScriptQuick(ctx, script, argsLength, args);
		}
		return 0;
		/* stopObjectCode */
		case 0x7B: {
			op_stopObjectCode(ctx);
		}
		return 0;
		/* stopScript */
		case 0x7C: {
			int32 scriptNum = pullStackLong();
			op_stopScript(ctx, scriptNum);
		}
		return 0;
		/* jumpToScript */
		case 0x7D: {
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			int32 scriptNum = pullStackLong();
			int32 flags = pullStackLong();
			op_jumpToScript(ctx, flags, scriptNum, argsLength, args);
		}
		return 0;
		/* dummy */
		case 0x7E: {
			op_dummy(ctx);
		}
		return 0;
		/* startObject */
		case 0x7F: {
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			byte entryp = pullStackByte();
			int32 script = pullStackLong();
			int32 flags = pullStackLong();
			op_startObject(ctx, flags, script, entryp, argsLength, args);
		}
		return 0;
		/* stopObjectScript */
		case 0x80: {
			int16 script = pullStackWord();
			op_stopObjectScript(ctx, script);
		}
		return 0;
		/* cutscene */
		case 0x81: {
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			op_cutscene(ctx, argsLength, args);
		}
		return 0;
		/* endCutscene */
		case 0x82: {
			op_endCutscene(ctx);
		}
		return 0;
		/* freezeUnfreeze */
		case 0x83: {
			int32 script = pullStackLong();
			op_freezeUnfreeze(ctx, script);
		}
		return 0;
		/* beginOverride */
		case 0x84: {
			op_beginOverride(ctx);
		}
		return 0;
		/* endOverride */
		case 0x85: {
			op_endOverride(ctx);
		}
		return 0;
		/* stopSentence */
		case 0x86: {
			op_stopSentence(ctx);
		}
		return 0;
		/* setClass */
		case 0x89: {
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			int32 obj = pullStackLong();
			op_setClass(ctx, obj, argsLength, args);
		}
		return 0;
		/* setState */
		case 0x8A: {
			int32 state = pullStackLong();
			int32 obj = pullStackLong();
			op_setState(ctx, obj, state);
		}
		return 0;
		/* setOwner */
		case 0x8B: {
			int32 owner = pullStackLong();
			int32 obj = pullStackLong();
			op_setOwner(ctx, obj, owner);
		}
		return 0;
		/* panCameraTo */
		case 0x8C: {
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			op_panCameraTo(ctx, x, y);
		}
		return 0;
		/* actorFollowCamera */
		case 0x8D: {
			int32 index = pullStackLong();
			op_actorFollowCamera(ctx, index);
		}
		return 0;
		/* setCameraAt */
		case 0x8E: {
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			op_setCameraAt(ctx, x, y);
		}
		return 0;
		case 0x8F: {
			consumeByte();
			switch(op2) {
				default:
					return 1;
				/* printActorAt */
				case 0x41: {
					int32 y = pullStackLong();
					int32 x = pullStackLong();
					op_printActorAt(ctx, x, y);
				}
				return 0;
				/* printActorColour */
				case 0x42: {
					int32 col = pullStackLong();
					op_printActorColour(ctx, col);
				}
				return 0;
				/* printActorClipped */
				case 0x43: {
					int32 right = pullStackLong();
					op_printActorClipped(ctx, right);
				}
				return 0;
				/* printActorCentre */
				case 0x45: {
					op_printActorCentre(ctx);
				}
				return 0;
				/* printActorLeft */
				case 0x47: {
					op_printActorLeft(ctx);
				}
				return 0;
				/* printActorOverhead */
				case 0x48: {
					op_printActorOverhead(ctx);
				}
				return 0;
				/* printActorMumble */
				case 0x4A: {
					op_printActorMumble(ctx);
				}
				return 0;
				/* printActorText */
				case 0x4B: {
					char* text = readText();
					op_printActorText(ctx, text);
				}
				return 0;
				/* printActorLoadDefault */
				case 0xFE: {
					int32 actorNum = pullStackLong();
					op_printActorLoadDefault(ctx, actorNum);
				}
				return 0;
				/* printActorSaveDefault */
				case 0xFF: {
					op_printActorSaveDefault(ctx);
				}
				return 0;
		}
		return 1;
		case 0x90: {
			consumeByte();
			switch(op2) {
				default:
					return 1;
				/* printEgoAt */
				case 0x41: {
					int32 y = pullStackLong();
					int32 x = pullStackLong();
					op_printEgoAt(ctx, x, y);
				}
				return 0;
				/* printEgoColour */
				case 0x42: {
					int32 col = pullStackLong();
					op_printEgoColour(ctx, col);
				}
				return 0;
				/* printEgoClipped */
				case 0x43: {
					int32 right = pullStackLong();
					op_printEgoClipped(ctx, right);
				}
				return 0;
				/* printEgoCentre */
				case 0x45: {
					op_printEgoCentre(ctx);
				}
				return 0;
				/* printEgoLeft */
				case 0x47: {
					op_printEgoLeft(ctx);
				}
				return 0;
				/* printEgoOverhead */
				case 0x48: {
					op_printEgoOverhead(ctx);
				}
				return 0;
				/* printEgoMumble */
				case 0x4A: {
					op_printEgoMumble(ctx);
				}
				return 0;
				/* printEgoText */
				case 0x4B: {
					char* text = readText();
					op_printEgoText(ctx, text);
				}
				return 0;
				/* printEgoLoadDefault */
				case 0xFE: {
					int32 actorNum = pullStackLong();
					op_printEgoLoadDefault(ctx, actorNum);
				}
				return 0;
				/* printEgoSaveDefault */
				case 0xFF: {
					op_printEgoSaveDefault(ctx);
				}
				return 0;
		}
		return 1;
		/* talkActor */
		case 0x91: {
			int32 actor = pullStackLong();
			char* text = readText();
			op_talkActor(ctx, text, actor);
		}
		return 0;
		/* talkEgo */
		case 0x92: {
			char* text = readText();
			op_talkEgo(ctx, text);
		}
		return 0;
		case 0x93: {
			consumeByte();
			switch(op2) {
				default:
					return 1;
				/* printLineAt */
				case 0x41: {
					int32 y = pullStackLong();
					int32 x = pullStackLong();
					op_printLineAt(ctx, x, y);
				}
				return 0;
				/* printLineColour */
				case 0x42: {
					int32 col = pullStackLong();
					op_printLineColour(ctx, col);
				}
				return 0;
				/* printLineClipped */
				case 0x43: {
					int32 right = pullStackLong();
					op_printLineClipped(ctx, right);
				}
				return 0;
				/* printLineCentre */
				case 0x45: {
					op_printLineCentre(ctx);
				}
				return 0;
				/* printLineLeft */
				case 0x47: {
					op_printLineLeft(ctx);
				}
				return 0;
				/* printLineOverhead */
				case 0x48: {
					op_printLineOverhead(ctx);
				}
				return 0;
				/* printLineMumble */
				case 0x4A: {
					op_printLineMumble(ctx);
				}
				return 0;
				/* printLineText */
				case 0x4B: {
					char* text = readText();
					op_printLineText(ctx, text);
				}
				return 0;
				/* printLineLoadDefault */
				case 0xFE: {
					op_printLineLoadDefault(ctx);
				}
				return 0;
				/* printLineSaveDefault */
				case 0xFF: {
					op_printLineSaveDefault(ctx);
				}
				return 0;
		}
		return 1;
		case 0x94: {
			consumeByte();
			switch(op2) {
				default:
					return 1;
				/* printTextAt */
				case 0x41: {
					int32 y = pullStackLong();
					int32 x = pullStackLong();
					op_printTextAt(ctx, x, y);
				}
				return 0;
				/* printTextColour */
				case 0x42: {
					int32 col = pullStackLong();
					op_printTextColour(ctx, col);
				}
				return 0;
				/* printTextClipped */
				case 0x43: {
					int32 right = pullStackLong();
					op_printTextClipped(ctx, right);
				}
				return 0;
				/* printTextCentre */
				case 0x45: {
					op_printTextCentre(ctx);
				}
				return 0;
				/* printTextLeft */
				case 0x47: {
					op_printTextLeft(ctx);
				}
				return 0;
				/* printTextOverhead */
				case 0x48: {
					op_printTextOverhead(ctx);
				}
				return 0;
				/* printTextMumble */
				case 0x4A: {
					op_printTextMumble(ctx);
				}
				return 0;
				/* printTextText */
				case 0x4B: {
					char* text = readText();
					op_printTextText(ctx, text);
				}
				return 0;
				/* printTextLoadDefault */
				case 0xFE: {
					op_printTextLoadDefault(ctx);
				}
				return 0;
				/* printTextSaveDefault */
				case 0xFF: {
					op_printTextSaveDefault(ctx);
				}
				return 0;
		}
		return 1;
		case 0x95: {
			consumeByte();
			switch(op2) {
				default:
					return 1;
				/* printDebugAt */
				case 0x41: {
					int32 y = pullStackLong();
					int32 x = pullStackLong();
					op_printDebugAt(ctx, x, y);
				}
				return 0;
				/* printDebugColour */
				case 0x42: {
					int32 col = pullStackLong();
					op_printDebugColour(ctx, col);
				}
				return 0;
				/* printDebugClipped */
				case 0x43: {
					int32 right = pullStackLong();
					op_printDebugClipped(ctx, right);
				}
				return 0;
				/* printDebugCentre */
				case 0x45: {
					op_printDebugCentre(ctx);
				}
				return 0;
				/* printDebugLeft */
				case 0x47: {
					op_printDebugLeft(ctx);
				}
				return 0;
				/* printDebugOverhead */
				case 0x48: {
					op_printDebugOverhead(ctx);
				}
				return 0;
				/* printDebugMumble */
				case 0x4A: {
					op_printDebugMumble(ctx);
				}
				return 0;
				/* printDebugText */
				case 0x4B: {
					char* text = readText();
					op_printDebugText(ctx, text);
				}
				return 0;
				/* printDebugLoadDefault */
				case 0xFE: {
					op_printDebugLoadDefault(ctx);
				}
				return 0;
				/* printDebugSaveDefault */
				case 0xFF: {
					op_printDebugSaveDefault(ctx);
				}
				return 0;
		}
		return 1;
		case 0x96: {
			consumeByte();
			switch(op2) {
				default:
					return 1;
				/* printSystemAt */
				case 0x41: {
					int32 y = pullStackLong();
					int32 x = pullStackLong();
					op_printSystemAt(ctx, x, y);
				}
				return 0;
				/* printSystemColour */
				case 0x42: {
					int32 col = pullStackLong();
					op_printSystemColour(ctx, col);
				}
				return 0;
				/* printSystemClipped */
				case 0x43: {
					int32 right = pullStackLong();
					op_printSystemClipped(ctx, right);
				}
				return 0;
				/* printSystemCentre */
				case 0x45: {
					op_printSystemCentre(ctx);
				}
				return 0;
				/* printSystemLeft */
				case 0x47: {
					op_printSystemLeft(ctx);
				}
				return 0;
				/* printSystemOverhead */
				case 0x48: {
					op_printSystemOverhead(ctx);
				}
				return 0;
				/* printSystemMumble */
				case 0x4A: {
					op_printSystemMumble(ctx);
				}
				return 0;
				/* printSystemText */
				case 0x4B: {
					char* text = readText();
					op_printSystemText(ctx, text);
				}
				return 0;
				/* printSystemLoadDefault */
				case 0xFE: {
					op_printSystemLoadDefault(ctx);
				}
				return 0;
				/* printSystemSaveDefault */
				case 0xFF: {
					op_printSystemSaveDefault(ctx);
				}
				return 0;
		}
		return 1;
		case 0x97: {
			consumeByte();
			switch(op2) {
				default:
					return 1;
				/* blastTextAt */
				case 0x41: {
					int32 y = pullStackLong();
					int32 x = pullStackLong();
					op_blastTextAt(ctx, x, y);
				}
				return 0;
				/* blastTextColour */
				case 0x42: {
					int32 col = pullStackLong();
					op_blastTextColour(ctx, col);
				}
				return 0;
				/* blastTextClipped */
				case 0x43: {
					int32 right = pullStackLong();
					op_blastTextClipped(ctx, right);
				}
				return 0;
				/* blastTextCentre */
				case 0x45: {
					op_blastTextCentre(ctx);
				}
				return 0;
				/* blastTextLeft */
				case 0x47: {
					op_blastTextLeft(ctx);
				}
				return 0;
				/* blastTextOverhead */
				case 0x48: {
					op_blastTextOverhead(ctx);
				}
				return 0;
				/* blastTextMumble */
				case 0x4A: {
					op_blastTextMumble(ctx);
				}
				return 0;
				/* blastTextText */
				case 0x4B: {
					char* text = readText();
					op_blastTextText(ctx, text);
				}
				return 0;
				/* blastTextLoadDefault */
				case 0xFE: {
					op_blastTextLoadDefault(ctx);
				}
				return 0;
				/* blastTextSaveDefault */
				case 0xFF: {
					op_blastTextSaveDefault(ctx);
				}
				return 0;
		}
		return 1;
		/* drawObject */
		case 0x98: {
			int32 state = pullStackLong();
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			int32 obj = pullStackLong();
			op_drawObject(ctx, obj, x, y, state);
		}
		return 0;
		case 0x9C: {
			consumeByte();
			switch(op2) {
				default:
					return 1;
				/* cursorOn */
				case 0xDC: {
					op_cursorOn(ctx);
				}
				return 0;
				/* cursorOff */
				case 0xDD: {
					op_cursorOff(ctx);
				}
				return 0;
				/* cursorSoftOn */
				case 0xDE: {
					op_cursorSoftOn(ctx);
				}
				return 0;
				/* cursorSoftOff */
				case 0xDF: {
					op_cursorSoftOff(ctx);
				}
				return 0;
				/* cursorUserPutOn */
				case 0xE0: {
					op_cursorUserPutOn(ctx);
				}
				return 0;
				/* cursorUserPutOff */
				case 0xE1: {
					op_cursorUserPutOff(ctx);
				}
				return 0;
				/* cursorUserPutSoftOn */
				case 0xE2: {
					op_cursorUserPutSoftOn(ctx);
				}
				return 0;
				/* cursorUserPutSoftOff */
				case 0xE3: {
					op_cursorUserPutSoftOff(ctx);
				}
				return 0;
				/* cursorUserCursorImage */
				case 0xE4: {
					int32 obj = pullStackLong();
					int32 idx = pullStackLong();
					op_cursorUserCursorImage(ctx, idx, obj);
				}
				return 0;
				/* cursorHotSpot */
				case 0xE5: {
					int32 y = pullStackLong();
					int32 x = pullStackLong();
					op_cursorHotSpot(ctx, x, y);
				}
				return 0;
				/* cursorSetTransparency */
				case 0xE6: {
					int32 enabled = pullStackLong();
					op_cursorSetTransparency(ctx, enabled);
				}
				return 0;
				/* cursorSetCharSet */
				case 0xE7: {
					int32 charsetNum = pullStackLong();
					op_cursorSetCharSet(ctx, charsetNum);
				}
				return 0;
				/* cursorSetColour */
				case 0xE8: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_cursorSetColour(ctx, argsLength, args);
				}
				return 0;
				/* cursorSetPos */
				case 0xE9: {
					int32 y = pullStackLong();
					int32 x = pullStackLong();
					op_cursorSetPos(ctx, x, y);
				}
				return 0;
		}
		return 1;
		/* loadRoom */
		case 0x9D: {
			byte room = pullStackByte();
			op_loadRoom(ctx, room);
		}
		return 0;
		/* loadRoomWithEgo */
		case 0x9E: {
			int32 room = pullStackLong();
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			op_loadRoomWithEgo(ctx, x, y, room);
		}
		return 0;
		/* walkActorToObj */
		case 0x9F: {
			int32 dist = pullStackLong();
			int32 obj = pullStackLong();
			int32 index = pullStackLong();
			op_walkActorToObj(ctx, index, obj, dist);
		}
		return 0;
		/* walkActorTo */
		case 0xA0: {
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			int32 index = pullStackLong();
			op_walkActorTo(ctx, index, x, y);
		}
		return 0;
		/* putActorAtXY */
		case 0xA1: {
			int32 room = pullStackLong();
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			int32 actorIndex = pullStackLong();
			op_putActorAtXY(ctx, actorIndex, x, y, room);
		}
		return 0;
		/* putActorAtObject */
		case 0xA2: {
			int32 obj = pullStackLong();
			op_putActorAtObject(ctx, obj);
		}
		return 0;
		/* faceActor */
		case 0xA3: {
			int32 obj = pullStackLong();
			int32 index = pullStackLong();
			op_faceActor(ctx, index, obj);
		}
		return 0;
		/* animateActor */
		case 0xA4: {
			int32 anim = pullStackLong();
			int32 index = pullStackLong();
			op_animateActor(ctx, index, anim);
		}
		return 0;
		/* doSentence */
		case 0xA5: {
			int16 objectB = pullStackWord();
			int16 objectA = pullStackWord();
			byte verb = pullStackByte();
			op_doSentence(ctx, verb, objectA, objectB);
		}
		return 0;
		/* pickupObject */
		case 0xA6: {
			int32 obj = pullStackLong();
			op_pickupObject(ctx, obj);
		}
		return 0;
		/* setBoxFlags */
		case 0xA7: {
			int32 value = pullStackLong();
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			op_setBoxFlags(ctx, argsLength, args, value);
		}
		return 0;
		/* createBoxMatrix */
		case 0xA8: {
			op_createBoxMatrix(ctx);
		}
		return 0;
		/* wait */
		case 0xA9: {
			op_wait(ctx);
		}
		return 0;
		case 0xAA: {
			consumeByte();
			switch(op2) {
				default:
					return 1;
				/* resourceRoutine3C */
				case 0x3C: {
					int16 num = pullStackWord();
					op_resourceRoutine3C(ctx, num);
				}
				return 0;
				/* loadCostume */
				case 0x3D: {
					int16 num = pullStackWord();
					op_loadCostume(ctx, num);
				}
				return 0;
				/* loadObject */
				case 0x3E: {
					int16 num = pullStackWord();
					op_loadObject(ctx, num);
				}
				return 0;
				/* loadRoom */
				case 0x3F: {
					int16 num = pullStackWord();
					op_loadRoom(ctx, num);
				}
				return 0;
				/* loadScript */
				case 0x40: {
					int16 num = pullStackWord();
					op_loadScript(ctx, num);
				}
				return 0;
				/* loadSound */
				case 0x41: {
					int16 num = pullStackWord();
					op_loadSound(ctx, num);
				}
				return 0;
				/* lockCostume */
				case 0x42: {
					int16 num = pullStackWord();
					op_lockCostume(ctx, num);
				}
				return 0;
				/* lockRoom */
				case 0x43: {
					int16 num = pullStackWord();
					op_lockRoom(ctx, num);
				}
				return 0;
				/* lockScript */
				case 0x44: {
					int16 num = pullStackWord();
					op_lockScript(ctx, num);
				}
				return 0;
				/* lockSound */
				case 0x45: {
					int16 num = pullStackWord();
					op_lockSound(ctx, num);
				}
				return 0;
				/* unlockCostume */
				case 0x46: {
					int16 num = pullStackWord();
					op_unlockCostume(ctx, num);
				}
				return 0;
				/* unlockRoom */
				case 0x47: {
					int16 num = pullStackWord();
					op_unlockRoom(ctx, num);
				}
				return 0;
				/* unlockScript */
				case 0x48: {
					int16 num = pullStackWord();
					op_unlockScript(ctx, num);
				}
				return 0;
				/* unlockSound */
				case 0x49: {
					int16 num = pullStackWord();
					op_unlockSound(ctx, num);
				}
				return 0;
				/* unloadCostume */
				case 0x4A: {
					int16 num = pullStackWord();
					op_unloadCostume(ctx, num);
				}
				return 0;
				/* unloadRoom */
				case 0x4B: {
					int16 num = pullStackWord();
					op_unloadRoom(ctx, num);
				}
				return 0;
				/* unloadScript */
				case 0x4C: {
					int16 num = pullStackWord();
					op_unloadScript(ctx, num);
				}
				return 0;
				/* unloadSound */
				case 0x4D: {
					int16 num = pullStackWord();
					op_unloadSound(ctx, num);
				}
				return 0;
		}
		return 1;
		case 0xAB: {
			consumeByte();
			switch(op2) {
				default:
					return 1;
				/* setRoomRGB */
				case 0x52: {
					int32 index = pullStackLong();
					byte b = pullStackByte();
					byte g = pullStackByte();
					byte r = pullStackByte();
					op_setRoomRGB(ctx, r, g, b, index);
				}
				return 0;
				/* fadeRoom */
				case 0x57: {
					int32 param = pullStackLong();
					op_fadeRoom(ctx, param);
				}
				return 0;
				/* setRoomRGBIntensity */
				case 0x58: {
					int16 endColour = pullStackWord();
					int16 startColour = pullStackWord();
					int32 blueScale = pullStackLong();
					int32 greenScale = pullStackLong();
					int32 redScale = pullStackLong();
					op_setRoomRGBIntensity(ctx, redScale, greenScale, blueScale, startColour, endColour);
				}
				return 0;
				/* setRoomRGBTransform */
				case 0x59: {
					int32 time = pullStackLong();
					int16 end = pullStackWord();
					int16 start = pullStackWord();
					int32 resId = pullStackLong();
					op_setRoomRGBTransform(ctx, resId, start, end, time);
				}
				return 0;
				/* setRoomPalette */
				case 0x5C: {
					int16 paletteNum = pullStackWord();
					op_setRoomPalette(ctx, paletteNum);
				}
				return 0;
				/* saveGame */
				case 0x5D: {
					op_saveGame(ctx);
				}
				return 0;
				/* loadGame */
				case 0x5E: {
					byte saveSound = pullStackByte();
					op_loadGame(ctx, saveSound);
				}
				return 0;
				/* setRoomSaturation */
				case 0x5F: {
					int16 endColour = pullStackWord();
					int16 startColour = pullStackWord();
					int32 lightScale = pullStackLong();
					int32 satScale = pullStackLong();
					int32 hueScale = pullStackLong();
					op_setRoomSaturation(ctx, hueScale, satScale, lightScale, startColour, endColour);
				}
				return 0;
		}
		return 1;
		case 0xAC: {
			consumeByte();
			switch(op2) {
				default:
					return 1;
				/* setActorCostume */
				case 0x64: {
					int16 costumeNum = pullStackWord();
					op_setActorCostume(ctx, costumeNum);
				}
				return 0;
				/* setActorWalkSpeed */
				case 0x65: {
					int16 y = pullStackWord();
					int16 x = pullStackWord();
					op_setActorWalkSpeed(ctx, x, y);
				}
				return 0;
				/* setActorAnimationDefault */
				case 0x67: {
					op_setActorAnimationDefault(ctx);
				}
				return 0;
				/* setActorAnimationInit */
				case 0x68: {
					byte frameNum = pullStackByte();
					op_setActorAnimationInit(ctx, frameNum);
				}
				return 0;
				/* setActorAnimationTalk */
				case 0x69: {
					byte endFrameNum = pullStackByte();
					byte startFrameNum = pullStackByte();
					op_setActorAnimationTalk(ctx, startFrameNum, endFrameNum);
				}
				return 0;
				/* setActorAnimationWalk */
				case 0x6A: {
					byte walkFrameNum = pullStackByte();
					op_setActorAnimationWalk(ctx, walkFrameNum);
				}
				return 0;
				/* setActorAnimationStand */
				case 0x6B: {
					byte standFrameNum = pullStackByte();
					op_setActorAnimationStand(ctx, standFrameNum);
				}
				return 0;
				/* setActorAnimationSpeed */
				case 0x6C: {
					byte animationSpeed = pullStackByte();
					op_setActorAnimationSpeed(ctx, animationSpeed);
				}
				return 0;
				/* setActorDefault */
				case 0x6D: {
					op_setActorDefault(ctx);
				}
				return 0;
				/* setActorElevation */
				case 0x6E: {
					int16 elevation = pullStackWord();
					op_setActorElevation(ctx, elevation);
				}
				return 0;
				/* setActorPalette */
				case 0x6F: {
					int16 value = pullStackWord();
					byte index = pullStackByte();
					op_setActorPalette(ctx, index, value);
				}
				return 0;
				/* setActorTalkColour */
				case 0x70: {
					byte colourIndex = pullStackByte();
					op_setActorTalkColour(ctx, colourIndex);
				}
				return 0;
				/* setActorName */
				case 0x71: {
					char* text = readText();
					op_setActorName(ctx, text);
				}
				return 0;
				/* setActorWidth */
				case 0x72: {
					int16 width = pullStackWord();
					op_setActorWidth(ctx, width);
				}
				return 0;
				/* setActorScale */
				case 0x73: {
					int16 size = pullStackWord();
					op_setActorScale(ctx, size);
				}
				return 0;
				/* setActorNeverZClip */
				case 0x74: {
					op_setActorNeverZClip(ctx);
				}
				return 0;
				/* setActorAlwaysZClip */
				case 0x75: {
					byte forceClip = pullStackByte();
					op_setActorAlwaysZClip(ctx, forceClip);
				}
				return 0;
				/* setActorIgnoreBoxes */
				case 0x76: {
					op_setActorIgnoreBoxes(ctx);
				}
				return 0;
				/* setActorFollowBoxes */
				case 0x77: {
					op_setActorFollowBoxes(ctx);
				}
				return 0;
				/* setActorSpecialDraw */
				case 0x78: {
					op_setActorSpecialDraw(ctx);
				}
				return 0;
				/* setActorTextOffset */
				case 0x79: {
					int16 y = pullStackWord();
					int16 x = pullStackWord();
					op_setActorTextOffset(ctx, x, y);
				}
				return 0;
				/* setActorVar */
				case 0x7B: {
					int32 value = pullStackLong();
					int32 name = pullStackLong();
					op_setActorVar(ctx, name, value);
				}
				return 0;
				/* setActorIgnoreTurns */
				case 0x7C: {
					op_setActorIgnoreTurns(ctx);
				}
				return 0;
				/* setActorFollowTurns */
				case 0x7D: {
					op_setActorFollowTurns(ctx);
				}
				return 0;
				/* setActorNew */
				case 0x7E: {
					op_setActorNew(ctx);
				}
				return 0;
				/* setActorDepth */
				case 0x7F: {
					int16 depth = pullStackWord();
					op_setActorDepth(ctx, depth);
				}
				return 0;
				/* setActorStop */
				case 0x80: {
					op_setActorStop(ctx);
				}
				return 0;
				/* setActorDirection */
				case 0x81: {
					int16 direction = pullStackWord();
					op_setActorDirection(ctx, direction);
				}
				return 0;
				/* actorTurn */
				case 0x82: {
					int16 direction = pullStackWord();
					op_actorTurn(ctx, direction);
				}
				return 0;
				/* setActorWalkScript */
				case 0x83: {
					int16 scriptNum = pullStackWord();
					op_setActorWalkScript(ctx, scriptNum);
				}
				return 0;
				/* setActorTalkScript */
				case 0x84: {
					int16 scriptNum = pullStackWord();
					op_setActorTalkScript(ctx, scriptNum);
				}
				return 0;
				/* setActorWalkingFrozen */
				case 0x85: {
					op_setActorWalkingFrozen(ctx);
				}
				return 0;
				/* setActorWalkingResume */
				case 0x86: {
					op_setActorWalkingResume(ctx);
				}
				return 0;
				/* setActorTalkVolume */
				case 0x87: {
					int32 volume = pullStackLong();
					op_setActorTalkVolume(ctx, volume);
				}
				return 0;
				/* setActorTalkFrequency */
				case 0x88: {
					int32 frequency = pullStackLong();
					op_setActorTalkFrequency(ctx, frequency);
				}
				return 0;
				/* setActorTalkPan */
				case 0x89: {
					int32 pan = pullStackLong();
					op_setActorTalkPan(ctx, pan);
				}
				return 0;
		}
		return 1;
		case 0xAD: {
			consumeByte();
			switch(op2) {
				default:
					return 1;
				/* setCameraPause */
				case 0x32: {
					op_setCameraPause(ctx);
				}
				return 0;
				/* setCameraResume */
				case 0x33: {
					op_setCameraResume(ctx);
				}
				return 0;
		}
		return 1;
		case 0xAE: {
			consumeByte();
			switch(op2) {
				default:
					return 1;
				/* initVerb */
				case 0x96: {
					int16 verbNum = pullStackWord();
					op_initVerb(ctx, verbNum);
				}
				return 0;
				/* newVerb */
				case 0x97: {
					int16 verbNum = pullStackWord();
					op_newVerb(ctx, verbNum);
				}
				return 0;
				/* deleteVerb */
				case 0x98: {
					int16 verbNum = pullStackWord();
					op_deleteVerb(ctx, verbNum);
				}
				return 0;
				/* setVerbName */
				case 0x99: {
					char* name = readText();
					op_setVerbName(ctx, name);
				}
				return 0;
				/* setVerbXY */
				case 0x9A: {
					int16 y = pullStackWord();
					int16 x = pullStackWord();
					op_setVerbXY(ctx, x, y);
				}
				return 0;
				/* setVerbOn */
				case 0x9B: {
					op_setVerbOn(ctx);
				}
				return 0;
				/* setVerbOff */
				case 0x9C: {
					op_setVerbOff(ctx);
				}
				return 0;
				/* setVerbColour */
				case 0x9D: {
					byte colourIndex = pullStackByte();
					op_setVerbColour(ctx, colourIndex);
				}
				return 0;
				/* setVerbHilightColour */
				case 0x9E: {
					byte colourIndex = pullStackByte();
					op_setVerbHilightColour(ctx, colourIndex);
				}
				return 0;
				/* setVerbDimColour */
				case 0xA0: {
					byte colourIndex = pullStackByte();
					op_setVerbDimColour(ctx, colourIndex);
				}
				return 0;
				/* setVerbDim */
				case 0xA1: {
					op_setVerbDim(ctx);
				}
				return 0;
				/* setVerbKey */
				case 0xA2: {
					byte keyCode = pullStackByte();
					op_setVerbKey(ctx, keyCode);
				}
				return 0;
				/* setVerbImage */
				case 0xA3: {
					byte roomNum = pullStackByte();
					int16 objectNum = pullStackWord();
					op_setVerbImage(ctx, objectNum, roomNum);
				}
				return 0;
				/* setVerbNameStr */
				case 0xA4: {
					int32 textAddress = pullStackLong();
					op_setVerbNameStr(ctx, textAddress);
				}
				return 0;
				/* setVerbCenter */
				case 0xA5: {
					op_setVerbCenter(ctx);
				}
				return 0;
				/* setVerbCharSet */
				case 0xA6: {
					byte charSetNum = pullStackByte();
					op_setVerbCharSet(ctx, charSetNum);
				}
				return 0;
				/* setVerbLinesSpacing */
				case 0xA7: {
					int16 lineSpacing = pullStackWord();
					op_setVerbLinesSpacing(ctx, lineSpacing);
				}
				return 0;
		}
		return 1;
		/* startSound */
		case 0xAF: {
			int32 sound = pullStackLong();
			op_startSound(ctx, sound);
		}
		return 0;
		/* startMusic */
		case 0xB0: {
			int32 sound = pullStackLong();
			op_startMusic(ctx, sound);
		}
		return 0;
		/* stopSound */
		case 0xB1: {
			int32 sound = pullStackLong();
			op_stopSound(ctx, sound);
		}
		return 0;
		/* soundKludge */
		case 0xB2: {
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			op_soundKludge(ctx, argsLength, args);
		}
		return 0;
		case 0xB3: {
			consumeByte();
			switch(op2) {
				default:
					return 1;
				/* restartGame */
				case 0x9E: {
					op_restartGame(ctx);
				}
				return 0;
				/* pauseGame */
				case 0x9F: {
					op_pauseGame(ctx);
				}
				return 0;
				/* quitGame */
				case 0xA0: {
					op_quitGame(ctx);
				}
				return 0;
		}
		return 1;
		/* saveRestoreVerbs */
		case 0xB4: {
			int32 c = pullStackLong();
			int32 b = pullStackLong();
			int32 a = pullStackLong();
			op_saveRestoreVerbs(ctx, a, b, c);
		}
		return 0;
		/* setObjectName */
		case 0xB5: {
			char* name = readText();
			int32 obj = pullStackLong();
			op_setObjectName(ctx, obj, name);
		}
		return 0;
		/* getDateTime */
		case 0xB6: {
			op_getDateTime(ctx);
		}
		return 0;
		/* drawBox */
		case 0xB7: {
			int32 color = pullStackLong();
			int32 y2 = pullStackLong();
			int32 x2 = pullStackLong();
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			op_drawBox(ctx, x, y, x2, y2, color);
		}
		return 0;
		/* startVideo */
		case 0xB9: {
			char* fileName = readText();
			op_startVideo(ctx, fileName);
		}
		return 0;
		case 0xBA: {
			consumeByte();
			switch(op2) {
				default:
					return 1;
				/* lockObject */
				case 0x0B: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_lockObject(ctx, argsLength, args);
				}
				return 0;
				/* unlockObject */
				case 0x0C: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_unlockObject(ctx, argsLength, args);
				}
				return 0;
				/* remapCostumePalette */
				case 0x0D: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_remapCostumePalette(ctx, argsLength, args);
				}
				return 0;
				/* remapCostumeInsert */
				case 0x0E: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_remapCostumeInsert(ctx, argsLength, args);
				}
				return 0;
				/* setVideoFrameRate */
				case 0x0F: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_setVideoFrameRate(ctx, argsLength, args);
				}
				return 0;
				/* setBoxScaleSlot */
				case 0x14: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_setBoxScaleSlot(ctx, argsLength, args);
				}
				return 0;
				/* setScaleSlot */
				case 0x15: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_setScaleSlot(ctx, argsLength, args);
				}
				return 0;
				/* setBannerColours */
				case 0x16: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_setBannerColours(ctx, argsLength, args);
				}
				return 0;
				/* setActorChoreLimbFrame */
				case 0x17: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_setActorChoreLimbFrame(ctx, argsLength, args);
				}
				return 0;
				/* clearTextQueue */
				case 0x18: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_clearTextQueue(ctx, argsLength, args);
				}
				return 0;
				/* saveGameReadName */
				case 0x19: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_saveGameReadName(ctx, argsLength, args);
				}
				return 0;
				/* saveGameWrite */
				case 0x1A: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_saveGameWrite(ctx, argsLength, args);
				}
				return 0;
				/* saveGameRead */
				case 0x1B: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_saveGameRead(ctx, argsLength, args);
				}
				return 0;
				/* saveGameScreenshot */
				case 0x1C: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_saveGameScreenshot(ctx, argsLength, args);
				}
				return 0;
				/* setKeyScript */
				case 0x1D: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_setKeyScript(ctx, argsLength, args);
				}
				return 0;
				/* killAllScriptsExceptCurrent */
				case 0x1E: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_killAllScriptsExceptCurrent(ctx, argsLength, args);
				}
				return 0;
				/* stopAllVideo */
				case 0x1F: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_stopAllVideo(ctx, argsLength, args);
				}
				return 0;
				/* writeRegistryValue */
				case 0x20: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_writeRegistryValue(ctx, argsLength, args);
				}
				return 0;
				/* setPaletteIntensity */
				case 0x21: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_setPaletteIntensity(ctx, argsLength, args);
				}
				return 0;
				/* queryQuit */
				case 0x22: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_queryQuit(ctx, argsLength, args);
				}
				return 0;
				/* buildPaletteShadow */
				case 0x6C: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_buildPaletteShadow(ctx, argsLength, args);
				}
				return 0;
				/* setPaletteShadow */
				case 0x6D: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_setPaletteShadow(ctx, argsLength, args);
				}
				return 0;
				/* blastShadowObject */
				case 0x6E: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_blastShadowObject(ctx, argsLength, args);
				}
				return 0;
				/* superBlastObject */
				case 0x6F: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_superBlastObject(ctx, argsLength, args);
				}
				return 0;
		}
		return 1;
		/* dim2DimArray */
		case 0xC0: {
			int32 dim1 = pullStackLong();
			int32 dim2 = pullStackLong();
			op_dim2DimArray(ctx, dim2, dim1);
		}
		return 0;
		/* distObjectPt */
		case 0xC6: {
			int32 c = pullStackLong();
			int32 b = pullStackLong();
			int32 a = pullStackLong();
			op_distObjectPt(ctx, a, b, c);
		}
		return 0;
		/* startScriptQuick2 */
		case 0xC8: {
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			int32 script = pullStackLong();
			op_startScriptQuick2(ctx, script, argsLength, args);
		}
		return 0;
		/* startObjectQuick */
		case 0xC9: {
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			byte entryPc = pullStackByte();
			int32 script = pullStackLong();
			op_startObjectQuick(ctx, script, entryPc, argsLength, args);
		}
		return 0;
		/* pickOneOf */
		case 0xCA: {
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			int32 i = pullStackLong();
			op_pickOneOf(ctx, i, argsLength, args);
		}
		return 0;
		/* pickOneOfDefault */
		case 0xCB: {
			int32 def = pullStackLong();
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			int32 i = pullStackLong();
			op_pickOneOfDefault(ctx, i, argsLength, args, def);
		}
		return 0;
		/* isAnyOf */
		case 0xCD: {
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			int32 value = pullStackLong();
			op_isAnyOf(ctx, value, argsLength, args);
		}
		return 0;
		/* getRandomNumber */
		case 0xCE: {
			int32 max = pullStackLong();
			op_getRandomNumber(ctx, max);
		}
		return 0;
		/* getRandomNumberRange */
		case 0xCF: {
			int32 max = pullStackLong();
			int32 min = pullStackLong();
			op_getRandomNumberRange(ctx, min, max);
		}
		return 0;
		/* ifClassOfIs */
		case 0xD0: {
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			int32 obj = pullStackLong();
			op_ifClassOfIs(ctx, obj, argsLength, args);
		}
		return 0;
		/* getState */
		case 0xD1: {
			int32 obj = pullStackLong();
			op_getState(ctx, obj);
		}
		return 0;
		/* getOwner */
		case 0xD2: {
			int32 obj = pullStackLong();
			op_getOwner(ctx, obj);
		}
		return 0;
		/* isScriptRunning */
		case 0xD3: {
			int32 script = pullStackLong();
			op_isScriptRunning(ctx, script);
		}
		return 0;
		/* shuffle */
		case 0xD4: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_shuffle(ctx, left, right);
		}
		return 0;
		/* isSoundRunning */
		case 0xD5: {
			int32 sound = pullStackLong();
			op_isSoundRunning(ctx, sound);
		}
		return 0;
		/* abs */
		case 0xD6: {
			int32 value = pullStackLong();
			op_abs(ctx, value);
		}
		return 0;
		case 0xD8: {
			consumeByte();
			switch(op2) {
				default:
					return 1;
				/* getWalkBoxAt */
				case 0x73: {
					int32 args = pullStackLong();
					op_getWalkBoxAt(ctx, args);
				}
				return 0;
				/* isPointInBox */
				case 0x74: {
					int32 args = pullStackLong();
					op_isPointInBox(ctx, args);
				}
				return 0;
				/* getRGBSlot */
				case 0xCE: {
					int32 args = pullStackLong();
					op_getRGBSlot(ctx, args);
				}
				return 0;
				/* getKeyState */
				case 0xD3: {
					int32 args = pullStackLong();
					op_getKeyState(ctx, args);
				}
				return 0;
				/* getBox */
				case 0xD7: {
					int32 args = pullStackLong();
					op_getBox(ctx, args);
				}
				return 0;
				/* findBlastObject */
				case 0xD8: {
					int32 args = pullStackLong();
					op_findBlastObject(ctx, args);
				}
				return 0;
				/* actorHitTest */
				case 0xD9: {
					int32 args = pullStackLong();
					op_actorHitTest(ctx, args);
				}
				return 0;
				/* setLipSyncWidth */
				case 0xDA: {
					int32 args = pullStackLong();
					op_setLipSyncWidth(ctx, args);
				}
				return 0;
				/* setLipSyncHeight */
				case 0xDB: {
					int32 args = pullStackLong();
					op_setLipSyncHeight(ctx, args);
				}
				return 0;
				/* setTalkAnimation */
				case 0xDC: {
					int32 args = pullStackLong();
					op_setTalkAnimation(ctx, args);
				}
				return 0;
				/* getGroupSfxVol */
				case 0xDD: {
					int32 args = pullStackLong();
					op_getGroupSfxVol(ctx, args);
				}
				return 0;
				/* getGroupVoiceVol */
				case 0xDE: {
					int32 args = pullStackLong();
					op_getGroupVoiceVol(ctx, args);
				}
				return 0;
				/* getGroupMusicVol */
				case 0xDF: {
					int32 args = pullStackLong();
					op_getGroupMusicVol(ctx, args);
				}
				return 0;
				/* readRegistryValue */
				case 0xE0: {
					int32 args = pullStackLong();
					op_readRegistryValue(ctx, args);
				}
				return 0;
				/* imuseGetMusicPosition */
				case 0xE1: {
					int32 args = pullStackLong();
					op_imuseGetMusicPosition(ctx, args);
				}
				return 0;
				/* imuseGetMusicLipSyncWidth */
				case 0xE2: {
					int32 args = pullStackLong();
					op_imuseGetMusicLipSyncWidth(ctx, args);
				}
				return 0;
				/* imuseGetMusicLipSyncHeight */
				case 0xE3: {
					int32 args = pullStackLong();
					op_imuseGetMusicLipSyncHeight(ctx, args);
				}
				return 0;
		}
		return 1;
		/* isActorInBox */
		case 0xD9: {
			int32 box = pullStackLong();
			int32 index = pullStackLong();
			op_isActorInBox(ctx, index, box);
		}
		return 0;
		/* getVerbEntrypoint */
		case 0xDA: {
			int32 entryp = pullStackLong();
			int32 verb = pullStackLong();
			op_getVerbEntrypoint(ctx, verb, entryp);
		}
		return 0;
		/* getActorFromXY */
		case 0xDB: {
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			op_getActorFromXY(ctx, x, y);
		}
		return 0;
		/* findObject */
		case 0xDC: {
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			op_findObject(ctx, x, y);
		}
		return 0;
		/* getVerbFromXY */
		case 0xDD: {
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			op_getVerbFromXY(ctx, x, y);
		}
		return 0;
		/* findInventory */
		case 0xDF: {
			int32 index = pullStackLong();
			int32 owner = pullStackLong();
			op_findInventory(ctx, owner, index);
		}
		return 0;
		/* getInventoryCount */
		case 0xE0: {
			int32 owner = pullStackLong();
			op_getInventoryCount(ctx, owner);
		}
		return 0;
		/* getAnimateVariable */
		case 0xE1: {
			int32 variable = pullStackLong();
			int32 index = pullStackLong();
			op_getAnimateVariable(ctx, index, variable);
		}
		return 0;
		/* getActorRoom */
		case 0xE2: {
			int32 index = pullStackLong();
			op_getActorRoom(ctx, index);
		}
		return 0;
		/* getActorWalkBox */
		case 0xE3: {
			int32 index = pullStackLong();
			op_getActorWalkBox(ctx, index);
		}
		return 0;
		/* getActorMoving */
		case 0xE4: {
			int32 index = pullStackLong();
			op_getActorMoving(ctx, index);
		}
		return 0;
		/* getActorCostume */
		case 0xE5: {
			int32 index = pullStackLong();
			op_getActorCostume(ctx, index);
		}
		return 0;
		/* getActorScaleX */
		case 0xE6: {
			int32 index = pullStackLong();
			op_getActorScaleX(ctx, index);
		}
		return 0;
		/* getActorLayer */
		case 0xE7: {
			int32 index = pullStackLong();
			op_getActorLayer(ctx, index);
		}
		return 0;
		/* getActorElevation */
		case 0xE8: {
			int32 index = pullStackLong();
			op_getActorElevation(ctx, index);
		}
		return 0;
		/* getActorWidth */
		case 0xE9: {
			int32 index = pullStackLong();
			op_getActorWidth(ctx, index);
		}
		return 0;
		/* getObjectNewDir */
		case 0xEA: {
			int32 index = pullStackLong();
			op_getObjectNewDir(ctx, index);
		}
		return 0;
		/* getObjectX */
		case 0xEB: {
			int32 index = pullStackLong();
			op_getObjectX(ctx, index);
		}
		return 0;
		/* getObjectY */
		case 0xEC: {
			int32 index = pullStackLong();
			op_getObjectY(ctx, index);
		}
		return 0;
		/* getActorChore */
		case 0xED: {
			int16 actorNum = pullStackWord();
			op_getActorChore(ctx, actorNum);
		}
		return 0;
		/* distObjectObject */
		case 0xEE: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_distObjectObject(ctx, left, right);
		}
		return 0;
		/* distObjectPtPt */
		case 0xEF: {
			int32 d = pullStackLong();
			int32 c = pullStackLong();
			int32 b = pullStackLong();
			int32 a = pullStackLong();
			op_distObjectPtPt(ctx, a, b, c, d);
		}
		return 0;
		/* getObjectImageX */
		case 0xF0: {
			int16 objectNum = pullStackWord();
			op_getObjectImageX(ctx, objectNum);
		}
		return 0;
		/* getObjectImageY */
		case 0xF1: {
			int16 objectNum = pullStackWord();
			op_getObjectImageY(ctx, objectNum);
		}
		return 0;
		/* getObjectImageWidth */
		case 0xF2: {
			int16 objectNum = pullStackWord();
			op_getObjectImageWidth(ctx, objectNum);
		}
		return 0;
		/* getObjectImageHeight */
		case 0xF3: {
			int16 objectNum = pullStackWord();
			op_getObjectImageHeight(ctx, objectNum);
		}
		return 0;
		/* getStringWidth */
		case 0xF6: {
			int16 charsetNum = pullStackWord();
			char* text = readText();
			op_getStringWidth(ctx, text, charsetNum);
		}
		return 0;
		/* getActorZPlane */
		case 0xF7: {
			int16 actorNum = pullStackWord();
			op_getActorZPlane(ctx, actorNum);
		}
		return 0;
	};
	return 1;
}
