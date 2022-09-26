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

#define pullLong() 0
#define pullByte() 0
#define pullWord() 0
#define pullStackWord() 0
#define pullStackByte() 0
#define pullStackLong() 0
#define pullStack() 0 
#define pullList(X, Y) NULL
#define readText() NULL

/* 00 pushByte */
GS_PRIVATE GS_INLINE void op_pushByte_00(gs_VmContext* ctx, byte value) {
	/* TODO */
}

/* 01 pushWord */
GS_PRIVATE GS_INLINE void op_pushWord_01(gs_VmContext* ctx, int32 value) {
	/* TODO */
}

/* 02 pushWordVar */
GS_PRIVATE GS_INLINE void op_pushWordVar_02(gs_VmContext* ctx, int32 name) {
	/* TODO */
}

/* 03 wordArrayRead */
GS_PRIVATE GS_INLINE void op_wordArrayRead_03(gs_VmContext* ctx, int32 base) {
	/* TODO */
}

/* 04 wordArrayIndexedRead */
GS_PRIVATE GS_INLINE void op_wordArrayIndexedRead_04(gs_VmContext* ctx, int32 index, int32 base, int32 arrayNum) {
	/* TODO */
}

/* 05 dup */
GS_PRIVATE GS_INLINE void op_dup_05(gs_VmContext* ctx, int32 value) {
	/* TODO */
}

/* 06 pop */
GS_PRIVATE GS_INLINE void op_pop_06(gs_VmContext* ctx, int32 discard) {
	/* TODO */
}

/* 07 not */
GS_PRIVATE GS_INLINE void op_not_07(gs_VmContext* ctx, int32 value) {
	/* TODO */
}

/* 08 eq */
GS_PRIVATE GS_INLINE void op_eq_08(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 09 neq */
GS_PRIVATE GS_INLINE void op_neq_09(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 0A gt */
GS_PRIVATE GS_INLINE void op_gt_0A(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 0B lt */
GS_PRIVATE GS_INLINE void op_lt_0B(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 0C le */
GS_PRIVATE GS_INLINE void op_le_0C(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 0D ge */
GS_PRIVATE GS_INLINE void op_ge_0D(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 0E add */
GS_PRIVATE GS_INLINE void op_add_0E(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 0F sub */
GS_PRIVATE GS_INLINE void op_sub_0F(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 10 mul */
GS_PRIVATE GS_INLINE void op_mul_10(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 11 div */
GS_PRIVATE GS_INLINE void op_div_11(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 12 land */
GS_PRIVATE GS_INLINE void op_land_12(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 13 lor */
GS_PRIVATE GS_INLINE void op_lor_13(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 14 band */
GS_PRIVATE GS_INLINE void op_band_14(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 15 bor */
GS_PRIVATE GS_INLINE void op_bor_15(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 16 mod */
GS_PRIVATE GS_INLINE void op_mod_16(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* 42 writeByteVar */
GS_PRIVATE GS_INLINE void op_writeByteVar_42(gs_VmContext* ctx, int32 value) {
	/* TODO */
}

/* 46 byteArrayWrite */
GS_PRIVATE GS_INLINE void op_byteArrayWrite_46(gs_VmContext* ctx, int32 base, int32 value) {
	/* TODO */
}

/* 4A byteArrayIndexedWrite */
GS_PRIVATE GS_INLINE void op_byteArrayIndexedWrite_4A(gs_VmContext* ctx, int32 index, int32 base, int32 value) {
	/* TODO */
}

/* 4E byteVarInc */
GS_PRIVATE GS_INLINE void op_byteVarInc_4E(gs_VmContext* ctx) {
	/* TODO */
}

/* 52 byteArrayInc */
GS_PRIVATE GS_INLINE void op_byteArrayInc_52(gs_VmContext* ctx, int32 base) {
	/* TODO */
}

/* 56 byteVarDec */
GS_PRIVATE GS_INLINE void op_byteVarDec_56(gs_VmContext* ctx) {
	/* TODO */
}

/* 5A byteArrayDec */
GS_PRIVATE GS_INLINE void op_byteArrayDec_5A(gs_VmContext* ctx, int32 base) {
	/* TODO */
}

/* 61 drawObject */
GS_PRIVATE GS_INLINE void op_drawObject_61(gs_VmContext* ctx, int32 obj, int32 state) {
	/* TODO */
}

/* 62 drawObjectAt */
GS_PRIVATE GS_INLINE void op_drawObjectAt_62(gs_VmContext* ctx, int32 obj, int32 x, int32 y) {
	/* TODO */
}

/* 63 drawBlastObject */
GS_PRIVATE GS_INLINE void op_drawBlastObject_63(gs_VmContext* ctx, int32 a, int32 b, int32 c, int32 d, int32 e, int32 argsLength, int32* args) {
	/* TODO */
}

/* 64 if */
GS_PRIVATE GS_INLINE void op_if_64(gs_VmContext* ctx, int32 condition, int32 offset) {
	/* TODO */
}

/* 65 ifNot */
GS_PRIVATE GS_INLINE void op_ifNot_65(gs_VmContext* ctx, int32 condition, int32 offset) {
	/* TODO */
}

/* 66 jump */
GS_PRIVATE GS_INLINE void op_jump_66(gs_VmContext* ctx, int32 offset) {
	/* TODO */
}

/* 67 breakHere */
GS_PRIVATE GS_INLINE void op_breakHere_67(gs_VmContext* ctx) {
	/* TODO */
}

/* 68 delayFrames */
GS_PRIVATE GS_INLINE void op_delayFrames_68(gs_VmContext* ctx) {
	/* TODO */
}

/* 691E waitActor */
GS_PRIVATE GS_INLINE void op_waitActor_691E(gs_VmContext* ctx, int32 offset, int32 actorNum) {
	/* TODO */
}

/* 691F waitMessage */
GS_PRIVATE GS_INLINE void op_waitMessage_691F(gs_VmContext* ctx) {
	/* TODO */
}

/* 6920 waitCamera */
GS_PRIVATE GS_INLINE void op_waitCamera_6920(gs_VmContext* ctx) {
	/* TODO */
}

/* 6921 waitSentence */
GS_PRIVATE GS_INLINE void op_waitSentence_6921(gs_VmContext* ctx) {
	/* TODO */
}

/* 6922 waitAnimation */
GS_PRIVATE GS_INLINE void op_waitAnimation_6922(gs_VmContext* ctx) {
	/* TODO */
}

/* 6923 waitTurn */
GS_PRIVATE GS_INLINE void op_waitTurn_6923(gs_VmContext* ctx, int32 offset, int32 actorNum) {
	/* TODO */
}

/* 6A delay */
GS_PRIVATE GS_INLINE void op_delay_6A(gs_VmContext* ctx, int32 delay) {
	/* TODO */
}

/* 6B delaySeconds */
GS_PRIVATE GS_INLINE void op_delaySeconds_6B(gs_VmContext* ctx, int32 seconds) {
	/* TODO */
}

/* 6C delayMinutes */
GS_PRIVATE GS_INLINE void op_delayMinutes_6C(gs_VmContext* ctx, int32 minutes) {
	/* TODO */
}

/* 6D writeWordVar */
GS_PRIVATE GS_INLINE void op_writeWordVar_6D(gs_VmContext* ctx, int32 value) {
	/* TODO */
}

/* 6E wordVarInc */
GS_PRIVATE GS_INLINE void op_wordVarInc_6E(gs_VmContext* ctx, int32 var) {
	/* TODO */
}

/* 6F wordVarDec */
GS_PRIVATE GS_INLINE void op_wordVarDec_6F(gs_VmContext* ctx, int32 var) {
	/* TODO */
}

/* 700A newArrayInt */
GS_PRIVATE GS_INLINE void op_newArrayInt_700A(gs_VmContext* ctx, int32 arrayNum, int32 dim1) {
	/* TODO */
}

/* 700B newArrayString */
GS_PRIVATE GS_INLINE void op_newArrayString_700B(gs_VmContext* ctx, int32 arrayNum, int32 dim1) {
	/* TODO */
}

/* 700C deleteArray */
GS_PRIVATE GS_INLINE void op_deleteArray_700C(gs_VmContext* ctx, int32 arrayNum) {
	/* TODO */
}

/* 71 wordArrayWrite */
GS_PRIVATE GS_INLINE void op_wordArrayWrite_71(gs_VmContext* ctx, int32 base, int32 value) {
	/* TODO */
}

/* 72 wordArrayInc */
GS_PRIVATE GS_INLINE void op_wordArrayInc_72(gs_VmContext* ctx, int32 base) {
	/* TODO */
}

/* 73 wordArrayDec */
GS_PRIVATE GS_INLINE void op_wordArrayDec_73(gs_VmContext* ctx, int32 base) {
	/* TODO */
}

/* 740A newArray2Int */
GS_PRIVATE GS_INLINE void op_newArray2Int_740A(gs_VmContext* ctx, int32 arrayNum, int32 dim1, int32 dim2) {
	/* TODO */
}

/* 740B newArray2String */
GS_PRIVATE GS_INLINE void op_newArray2String_740B(gs_VmContext* ctx, int32 arrayNum, int32 dim1, int32 dim2) {
	/* TODO */
}

/* 740C deleteArray2 */
GS_PRIVATE GS_INLINE void op_deleteArray2_740C(gs_VmContext* ctx, int32 arrayNum) {
	/* TODO */
}

/* 75 wordArrayIndexedWrite */
GS_PRIVATE GS_INLINE void op_wordArrayIndexedWrite_75(gs_VmContext* ctx, int32 index, int32 base, int32 value, int32 arrayNum) {
	/* TODO */
}

/* 7614 setArrayString */
GS_PRIVATE GS_INLINE void op_setArrayString_7614(gs_VmContext* ctx, char* string, int32 offset, int32 arrayNum) {
	/* TODO */
}

/* 7615 setArrayList */
GS_PRIVATE GS_INLINE void op_setArrayList_7615(gs_VmContext* ctx, int32 listLength, int32* list, int32 offset, int32 arrayNum) {
	/* TODO */
}

/* 7616 setArray2List */
GS_PRIVATE GS_INLINE void op_setArray2List_7616(gs_VmContext* ctx, int32 listLength, int32* list, int32 offset, int32 arrayNum) {
	/* TODO */
}

/* 79 startScript */
GS_PRIVATE GS_INLINE void op_startScript_79(gs_VmContext* ctx, int32 flags, int32 script, int32 argsLength, int32* args) {
	/* TODO */
}

/* 7A startScriptQuick */
GS_PRIVATE GS_INLINE void op_startScriptQuick_7A(gs_VmContext* ctx, int32 script, int32 argsLength, int32* args) {
	/* TODO */
}

/* 7B stopObjectCode */
GS_PRIVATE GS_INLINE void op_stopObjectCode_7B(gs_VmContext* ctx) {
	/* TODO */
}

/* 7C stopScript */
GS_PRIVATE GS_INLINE void op_stopScript_7C(gs_VmContext* ctx, int32 scriptNum) {
	/* TODO */
}

/* 7D jumpToScript */
GS_PRIVATE GS_INLINE void op_jumpToScript_7D(gs_VmContext* ctx, int32 flags, int32 scriptNum, int32 argsLength, int32* args) {
	/* TODO */
}

/* 7E dummy */
GS_PRIVATE GS_INLINE void op_dummy_7E(gs_VmContext* ctx) {
	/* TODO */
}

/* 7F startObject */
GS_PRIVATE GS_INLINE void op_startObject_7F(gs_VmContext* ctx, int32 flags, int32 script, byte entryp, int32 argsLength, int32* args) {
	/* TODO */
}

/* 80 stopObjectScript */
GS_PRIVATE GS_INLINE void op_stopObjectScript_80(gs_VmContext* ctx, int16 script) {
	/* TODO */
}

/* 81 cutscene */
GS_PRIVATE GS_INLINE void op_cutscene_81(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* 82 endCutscene */
GS_PRIVATE GS_INLINE void op_endCutscene_82(gs_VmContext* ctx) {
	/* TODO */
}

/* 83 freezeUnfreeze */
GS_PRIVATE GS_INLINE void op_freezeUnfreeze_83(gs_VmContext* ctx, int32 script) {
	/* TODO */
}

/* 84 beginOverride */
GS_PRIVATE GS_INLINE void op_beginOverride_84(gs_VmContext* ctx) {
	/* TODO */
}

/* 85 endOverride */
GS_PRIVATE GS_INLINE void op_endOverride_85(gs_VmContext* ctx) {
	/* TODO */
}

/* 86 stopSentence */
GS_PRIVATE GS_INLINE void op_stopSentence_86(gs_VmContext* ctx) {
	/* TODO */
}

/* 89 setClass */
GS_PRIVATE GS_INLINE void op_setClass_89(gs_VmContext* ctx, int32 obj, int32 argsLength, int32* args) {
	/* TODO */
}

/* 8A setState */
GS_PRIVATE GS_INLINE void op_setState_8A(gs_VmContext* ctx, int32 obj, int32 state) {
	/* TODO */
}

/* 8B setOwner */
GS_PRIVATE GS_INLINE void op_setOwner_8B(gs_VmContext* ctx, int32 obj, int32 owner) {
	/* TODO */
}

/* 8C panCameraTo */
GS_PRIVATE GS_INLINE void op_panCameraTo_8C(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* 8D actorFollowCamera */
GS_PRIVATE GS_INLINE void op_actorFollowCamera_8D(gs_VmContext* ctx, int32 index) {
	/* TODO */
}

/* 8E setCameraAt */
GS_PRIVATE GS_INLINE void op_setCameraAt_8E(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* 8F41 printActorAt */
GS_PRIVATE GS_INLINE void op_printActorAt_8F41(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* 8F42 printActorColour */
GS_PRIVATE GS_INLINE void op_printActorColour_8F42(gs_VmContext* ctx, int32 col) {
	/* TODO */
}

/* 8F43 printActorClipped */
GS_PRIVATE GS_INLINE void op_printActorClipped_8F43(gs_VmContext* ctx, int32 right) {
	/* TODO */
}

/* 8F45 printActorCentre */
GS_PRIVATE GS_INLINE void op_printActorCentre_8F45(gs_VmContext* ctx) {
	/* TODO */
}

/* 8F47 printActorLeft */
GS_PRIVATE GS_INLINE void op_printActorLeft_8F47(gs_VmContext* ctx) {
	/* TODO */
}

/* 8F48 printActorOverhead */
GS_PRIVATE GS_INLINE void op_printActorOverhead_8F48(gs_VmContext* ctx) {
	/* TODO */
}

/* 8F4A printActorMumble */
GS_PRIVATE GS_INLINE void op_printActorMumble_8F4A(gs_VmContext* ctx) {
	/* TODO */
}

/* 8F4B printActorText */
GS_PRIVATE GS_INLINE void op_printActorText_8F4B(gs_VmContext* ctx, char* text) {
	/* TODO */
}

/* 8FFE printActorLoadDefault */
GS_PRIVATE GS_INLINE void op_printActorLoadDefault_8FFE(gs_VmContext* ctx, int32 actorNum) {
	/* TODO */
}

/* 8FFF printActorSaveDefault */
GS_PRIVATE GS_INLINE void op_printActorSaveDefault_8FFF(gs_VmContext* ctx) {
	/* TODO */
}

/* 9041 printEgoAt */
GS_PRIVATE GS_INLINE void op_printEgoAt_9041(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* 9042 printEgoColour */
GS_PRIVATE GS_INLINE void op_printEgoColour_9042(gs_VmContext* ctx, int32 col) {
	/* TODO */
}

/* 9043 printEgoClipped */
GS_PRIVATE GS_INLINE void op_printEgoClipped_9043(gs_VmContext* ctx, int32 right) {
	/* TODO */
}

/* 9045 printEgoCentre */
GS_PRIVATE GS_INLINE void op_printEgoCentre_9045(gs_VmContext* ctx) {
	/* TODO */
}

/* 9047 printEgoLeft */
GS_PRIVATE GS_INLINE void op_printEgoLeft_9047(gs_VmContext* ctx) {
	/* TODO */
}

/* 9048 printEgoOverhead */
GS_PRIVATE GS_INLINE void op_printEgoOverhead_9048(gs_VmContext* ctx) {
	/* TODO */
}

/* 904A printEgoMumble */
GS_PRIVATE GS_INLINE void op_printEgoMumble_904A(gs_VmContext* ctx) {
	/* TODO */
}

/* 904B printEgoText */
GS_PRIVATE GS_INLINE void op_printEgoText_904B(gs_VmContext* ctx, char* text) {
	/* TODO */
}

/* 90FE printEgoLoadDefault */
GS_PRIVATE GS_INLINE void op_printEgoLoadDefault_90FE(gs_VmContext* ctx, int32 actorNum) {
	/* TODO */
}

/* 90FF printEgoSaveDefault */
GS_PRIVATE GS_INLINE void op_printEgoSaveDefault_90FF(gs_VmContext* ctx) {
	/* TODO */
}

/* 91 talkActor */
GS_PRIVATE GS_INLINE void op_talkActor_91(gs_VmContext* ctx, char* text, int32 actor) {
	/* TODO */
}

/* 92 talkEgo */
GS_PRIVATE GS_INLINE void op_talkEgo_92(gs_VmContext* ctx, char* text) {
	/* TODO */
}

/* 9341 printLineAt */
GS_PRIVATE GS_INLINE void op_printLineAt_9341(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* 9342 printLineColour */
GS_PRIVATE GS_INLINE void op_printLineColour_9342(gs_VmContext* ctx, int32 col) {
	/* TODO */
}

/* 9343 printLineClipped */
GS_PRIVATE GS_INLINE void op_printLineClipped_9343(gs_VmContext* ctx, int32 right) {
	/* TODO */
}

/* 9345 printLineCentre */
GS_PRIVATE GS_INLINE void op_printLineCentre_9345(gs_VmContext* ctx) {
	/* TODO */
}

/* 9347 printLineLeft */
GS_PRIVATE GS_INLINE void op_printLineLeft_9347(gs_VmContext* ctx) {
	/* TODO */
}

/* 9348 printLineOverhead */
GS_PRIVATE GS_INLINE void op_printLineOverhead_9348(gs_VmContext* ctx) {
	/* TODO */
}

/* 934A printLineMumble */
GS_PRIVATE GS_INLINE void op_printLineMumble_934A(gs_VmContext* ctx) {
	/* TODO */
}

/* 934B printLineText */
GS_PRIVATE GS_INLINE void op_printLineText_934B(gs_VmContext* ctx, char* text) {
	/* TODO */
}

/* 93FE printLineLoadDefault */
GS_PRIVATE GS_INLINE void op_printLineLoadDefault_93FE(gs_VmContext* ctx) {
	/* TODO */
}

/* 93FF printLineSaveDefault */
GS_PRIVATE GS_INLINE void op_printLineSaveDefault_93FF(gs_VmContext* ctx) {
	/* TODO */
}

/* 9441 printTextAt */
GS_PRIVATE GS_INLINE void op_printTextAt_9441(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* 9442 printTextColour */
GS_PRIVATE GS_INLINE void op_printTextColour_9442(gs_VmContext* ctx, int32 col) {
	/* TODO */
}

/* 9443 printTextClipped */
GS_PRIVATE GS_INLINE void op_printTextClipped_9443(gs_VmContext* ctx, int32 right) {
	/* TODO */
}

/* 9445 printTextCentre */
GS_PRIVATE GS_INLINE void op_printTextCentre_9445(gs_VmContext* ctx) {
	/* TODO */
}

/* 9447 printTextLeft */
GS_PRIVATE GS_INLINE void op_printTextLeft_9447(gs_VmContext* ctx) {
	/* TODO */
}

/* 9448 printTextOverhead */
GS_PRIVATE GS_INLINE void op_printTextOverhead_9448(gs_VmContext* ctx) {
	/* TODO */
}

/* 944A printTextMumble */
GS_PRIVATE GS_INLINE void op_printTextMumble_944A(gs_VmContext* ctx) {
	/* TODO */
}

/* 944B printTextText */
GS_PRIVATE GS_INLINE void op_printTextText_944B(gs_VmContext* ctx, char* text) {
	/* TODO */
}

/* 94FE printTextLoadDefault */
GS_PRIVATE GS_INLINE void op_printTextLoadDefault_94FE(gs_VmContext* ctx) {
	/* TODO */
}

/* 94FF printTextSaveDefault */
GS_PRIVATE GS_INLINE void op_printTextSaveDefault_94FF(gs_VmContext* ctx) {
	/* TODO */
}

/* 9541 printDebugAt */
GS_PRIVATE GS_INLINE void op_printDebugAt_9541(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* 9542 printDebugColour */
GS_PRIVATE GS_INLINE void op_printDebugColour_9542(gs_VmContext* ctx, int32 col) {
	/* TODO */
}

/* 9543 printDebugClipped */
GS_PRIVATE GS_INLINE void op_printDebugClipped_9543(gs_VmContext* ctx, int32 right) {
	/* TODO */
}

/* 9545 printDebugCentre */
GS_PRIVATE GS_INLINE void op_printDebugCentre_9545(gs_VmContext* ctx) {
	/* TODO */
}

/* 9547 printDebugLeft */
GS_PRIVATE GS_INLINE void op_printDebugLeft_9547(gs_VmContext* ctx) {
	/* TODO */
}

/* 9548 printDebugOverhead */
GS_PRIVATE GS_INLINE void op_printDebugOverhead_9548(gs_VmContext* ctx) {
	/* TODO */
}

/* 954A printDebugMumble */
GS_PRIVATE GS_INLINE void op_printDebugMumble_954A(gs_VmContext* ctx) {
	/* TODO */
}

/* 954B printDebugText */
GS_PRIVATE GS_INLINE void op_printDebugText_954B(gs_VmContext* ctx, char* text) {
	/* TODO */
}

/* 95FE printDebugLoadDefault */
GS_PRIVATE GS_INLINE void op_printDebugLoadDefault_95FE(gs_VmContext* ctx) {
	/* TODO */
}

/* 95FF printDebugSaveDefault */
GS_PRIVATE GS_INLINE void op_printDebugSaveDefault_95FF(gs_VmContext* ctx) {
	/* TODO */
}

/* 9641 printSystemAt */
GS_PRIVATE GS_INLINE void op_printSystemAt_9641(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* 9642 printSystemColour */
GS_PRIVATE GS_INLINE void op_printSystemColour_9642(gs_VmContext* ctx, int32 col) {
	/* TODO */
}

/* 9643 printSystemClipped */
GS_PRIVATE GS_INLINE void op_printSystemClipped_9643(gs_VmContext* ctx, int32 right) {
	/* TODO */
}

/* 9645 printSystemCentre */
GS_PRIVATE GS_INLINE void op_printSystemCentre_9645(gs_VmContext* ctx) {
	/* TODO */
}

/* 9647 printSystemLeft */
GS_PRIVATE GS_INLINE void op_printSystemLeft_9647(gs_VmContext* ctx) {
	/* TODO */
}

/* 9648 printSystemOverhead */
GS_PRIVATE GS_INLINE void op_printSystemOverhead_9648(gs_VmContext* ctx) {
	/* TODO */
}

/* 964A printSystemMumble */
GS_PRIVATE GS_INLINE void op_printSystemMumble_964A(gs_VmContext* ctx) {
	/* TODO */
}

/* 964B printSystemText */
GS_PRIVATE GS_INLINE void op_printSystemText_964B(gs_VmContext* ctx, char* text) {
	/* TODO */
}

/* 96FE printSystemLoadDefault */
GS_PRIVATE GS_INLINE void op_printSystemLoadDefault_96FE(gs_VmContext* ctx) {
	/* TODO */
}

/* 96FF printSystemSaveDefault */
GS_PRIVATE GS_INLINE void op_printSystemSaveDefault_96FF(gs_VmContext* ctx) {
	/* TODO */
}

/* 9741 blastTextAt */
GS_PRIVATE GS_INLINE void op_blastTextAt_9741(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* 9742 blastTextColour */
GS_PRIVATE GS_INLINE void op_blastTextColour_9742(gs_VmContext* ctx, int32 col) {
	/* TODO */
}

/* 9743 blastTextClipped */
GS_PRIVATE GS_INLINE void op_blastTextClipped_9743(gs_VmContext* ctx, int32 right) {
	/* TODO */
}

/* 9745 blastTextCentre */
GS_PRIVATE GS_INLINE void op_blastTextCentre_9745(gs_VmContext* ctx) {
	/* TODO */
}

/* 9747 blastTextLeft */
GS_PRIVATE GS_INLINE void op_blastTextLeft_9747(gs_VmContext* ctx) {
	/* TODO */
}

/* 9748 blastTextOverhead */
GS_PRIVATE GS_INLINE void op_blastTextOverhead_9748(gs_VmContext* ctx) {
	/* TODO */
}

/* 974A blastTextMumble */
GS_PRIVATE GS_INLINE void op_blastTextMumble_974A(gs_VmContext* ctx) {
	/* TODO */
}

/* 974B blastTextText */
GS_PRIVATE GS_INLINE void op_blastTextText_974B(gs_VmContext* ctx, char* text) {
	/* TODO */
}

/* 97FE blastTextLoadDefault */
GS_PRIVATE GS_INLINE void op_blastTextLoadDefault_97FE(gs_VmContext* ctx) {
	/* TODO */
}

/* 97FF blastTextSaveDefault */
GS_PRIVATE GS_INLINE void op_blastTextSaveDefault_97FF(gs_VmContext* ctx) {
	/* TODO */
}

/* 98 drawObject */
GS_PRIVATE GS_INLINE void op_drawObject_98(gs_VmContext* ctx, int32 obj, int32 x, int32 y, int32 state) {
	/* TODO */
}

/* 9CDC cursorOn */
GS_PRIVATE GS_INLINE void op_cursorOn_9CDC(gs_VmContext* ctx) {
	/* TODO */
}

/* 9CDD cursorOff */
GS_PRIVATE GS_INLINE void op_cursorOff_9CDD(gs_VmContext* ctx) {
	/* TODO */
}

/* 9CDE cursorSoftOn */
GS_PRIVATE GS_INLINE void op_cursorSoftOn_9CDE(gs_VmContext* ctx) {
	/* TODO */
}

/* 9CDF cursorSoftOff */
GS_PRIVATE GS_INLINE void op_cursorSoftOff_9CDF(gs_VmContext* ctx) {
	/* TODO */
}

/* 9CE0 cursorUserPutOn */
GS_PRIVATE GS_INLINE void op_cursorUserPutOn_9CE0(gs_VmContext* ctx) {
	/* TODO */
}

/* 9CE1 cursorUserPutOff */
GS_PRIVATE GS_INLINE void op_cursorUserPutOff_9CE1(gs_VmContext* ctx) {
	/* TODO */
}

/* 9CE2 cursorUserPutSoftOn */
GS_PRIVATE GS_INLINE void op_cursorUserPutSoftOn_9CE2(gs_VmContext* ctx) {
	/* TODO */
}

/* 9CE3 cursorUserPutSoftOff */
GS_PRIVATE GS_INLINE void op_cursorUserPutSoftOff_9CE3(gs_VmContext* ctx) {
	/* TODO */
}

/* 9CE4 cursorUserCursorImage */
GS_PRIVATE GS_INLINE void op_cursorUserCursorImage_9CE4(gs_VmContext* ctx, int32 idx, int32 obj) {
	/* TODO */
}

/* 9CE5 cursorHotSpot */
GS_PRIVATE GS_INLINE void op_cursorHotSpot_9CE5(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* 9CE6 cursorSetTransparency */
GS_PRIVATE GS_INLINE void op_cursorSetTransparency_9CE6(gs_VmContext* ctx, int32 enabled) {
	/* TODO */
}

/* 9CE7 cursorSetCharSet */
GS_PRIVATE GS_INLINE void op_cursorSetCharSet_9CE7(gs_VmContext* ctx, int32 charsetNum) {
	/* TODO */
}

/* 9CE8 cursorSetColour */
GS_PRIVATE GS_INLINE void op_cursorSetColour_9CE8(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* 9CE9 cursorSetPos */
GS_PRIVATE GS_INLINE void op_cursorSetPos_9CE9(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* 9D loadRoom */
GS_PRIVATE GS_INLINE void op_loadRoom_9D(gs_VmContext* ctx, byte room) {
	/* TODO */
}

/* 9E loadRoomWithEgo */
GS_PRIVATE GS_INLINE void op_loadRoomWithEgo_9E(gs_VmContext* ctx, int32 x, int32 y, int32 room) {
	/* TODO */
}

/* 9F walkActorToObj */
GS_PRIVATE GS_INLINE void op_walkActorToObj_9F(gs_VmContext* ctx, int32 index, int32 obj, int32 dist) {
	/* TODO */
}

/* A0 walkActorTo */
GS_PRIVATE GS_INLINE void op_walkActorTo_A0(gs_VmContext* ctx, int32 index, int32 x, int32 y) {
	/* TODO */
}

/* A1 putActorAtXY */
GS_PRIVATE GS_INLINE void op_putActorAtXY_A1(gs_VmContext* ctx, int32 actorIndex, int32 x, int32 y, int32 room) {
	/* TODO */
}

/* A2 putActorAtObject */
GS_PRIVATE GS_INLINE void op_putActorAtObject_A2(gs_VmContext* ctx, int32 obj) {
	/* TODO */
}

/* A3 faceActor */
GS_PRIVATE GS_INLINE void op_faceActor_A3(gs_VmContext* ctx, int32 index, int32 obj) {
	/* TODO */
}

/* A4 animateActor */
GS_PRIVATE GS_INLINE void op_animateActor_A4(gs_VmContext* ctx, int32 index, int32 anim) {
	/* TODO */
}

/* A5 doSentence */
GS_PRIVATE GS_INLINE void op_doSentence_A5(gs_VmContext* ctx, byte verb, int16 objectA, int16 objectB) {
	/* TODO */
}

/* A6 pickupObject */
GS_PRIVATE GS_INLINE void op_pickupObject_A6(gs_VmContext* ctx, int32 obj) {
	/* TODO */
}

/* A7 setBoxFlags */
GS_PRIVATE GS_INLINE void op_setBoxFlags_A7(gs_VmContext* ctx, int32 argsLength, int32* args, int32 value) {
	/* TODO */
}

/* A8 createBoxMatrix */
GS_PRIVATE GS_INLINE void op_createBoxMatrix_A8(gs_VmContext* ctx) {
	/* TODO */
}

/* A9 wait */
GS_PRIVATE GS_INLINE void op_wait_A9(gs_VmContext* ctx) {
	/* TODO */
}

/* AA3C resourceRoutine3C */
GS_PRIVATE GS_INLINE void op_resourceRoutine3C_AA3C(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA3D loadCostume */
GS_PRIVATE GS_INLINE void op_loadCostume_AA3D(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA3E loadObject */
GS_PRIVATE GS_INLINE void op_loadObject_AA3E(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA3F loadRoom */
GS_PRIVATE GS_INLINE void op_loadRoom_AA3F(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA40 loadScript */
GS_PRIVATE GS_INLINE void op_loadScript_AA40(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA41 loadSound */
GS_PRIVATE GS_INLINE void op_loadSound_AA41(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA42 lockCostume */
GS_PRIVATE GS_INLINE void op_lockCostume_AA42(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA43 lockRoom */
GS_PRIVATE GS_INLINE void op_lockRoom_AA43(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA44 lockScript */
GS_PRIVATE GS_INLINE void op_lockScript_AA44(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA45 lockSound */
GS_PRIVATE GS_INLINE void op_lockSound_AA45(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA46 unlockCostume */
GS_PRIVATE GS_INLINE void op_unlockCostume_AA46(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA47 unlockRoom */
GS_PRIVATE GS_INLINE void op_unlockRoom_AA47(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA48 unlockScript */
GS_PRIVATE GS_INLINE void op_unlockScript_AA48(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA49 unlockSound */
GS_PRIVATE GS_INLINE void op_unlockSound_AA49(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA4A unloadCostume */
GS_PRIVATE GS_INLINE void op_unloadCostume_AA4A(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA4B unloadRoom */
GS_PRIVATE GS_INLINE void op_unloadRoom_AA4B(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA4C unloadScript */
GS_PRIVATE GS_INLINE void op_unloadScript_AA4C(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AA4D unloadSound */
GS_PRIVATE GS_INLINE void op_unloadSound_AA4D(gs_VmContext* ctx, int16 num) {
	/* TODO */
}

/* AB52 setRoomRGB */
GS_PRIVATE GS_INLINE void op_setRoomRGB_AB52(gs_VmContext* ctx, byte r, byte g, byte b, int32 index) {
	/* TODO */
}

/* AB57 fadeRoom */
GS_PRIVATE GS_INLINE void op_fadeRoom_AB57(gs_VmContext* ctx, int32 param) {
	/* TODO */
}

/* AB58 setRoomRGBIntensity */
GS_PRIVATE GS_INLINE void op_setRoomRGBIntensity_AB58(gs_VmContext* ctx, int32 redScale, int32 greenScale, int32 blueScale, int16 startColour, int16 endColour) {
	/* TODO */
}

/* AB59 setRoomRGBTransform */
GS_PRIVATE GS_INLINE void op_setRoomRGBTransform_AB59(gs_VmContext* ctx, int32 resId, int16 start, int16 end, int32 time) {
	/* TODO */
}

/* AB5C setRoomPalette */
GS_PRIVATE GS_INLINE void op_setRoomPalette_AB5C(gs_VmContext* ctx, int16 paletteNum) {
	/* TODO */
}

/* AB5D saveGame */
GS_PRIVATE GS_INLINE void op_saveGame_AB5D(gs_VmContext* ctx) {
	/* TODO */
}

/* AB5E loadGame */
GS_PRIVATE GS_INLINE void op_loadGame_AB5E(gs_VmContext* ctx, byte saveSound) {
	/* TODO */
}

/* AB5F setRoomSaturation */
GS_PRIVATE GS_INLINE void op_setRoomSaturation_AB5F(gs_VmContext* ctx, int32 hueScale, int32 satScale, int32 lightScale, int16 startColour, int16 endColour) {
	/* TODO */
}

/* AC64 setActorCostume */
GS_PRIVATE GS_INLINE void op_setActorCostume_AC64(gs_VmContext* ctx, int16 costumeNum) {
	/* TODO */
}

/* AC65 setActorWalkSpeed */
GS_PRIVATE GS_INLINE void op_setActorWalkSpeed_AC65(gs_VmContext* ctx, int16 x, int16 y) {
	/* TODO */
}

/* AC67 setActorAnimationDefault */
GS_PRIVATE GS_INLINE void op_setActorAnimationDefault_AC67(gs_VmContext* ctx) {
	/* TODO */
}

/* AC68 setActorAnimationInit */
GS_PRIVATE GS_INLINE void op_setActorAnimationInit_AC68(gs_VmContext* ctx, byte frameNum) {
	/* TODO */
}

/* AC69 setActorAnimationTalk */
GS_PRIVATE GS_INLINE void op_setActorAnimationTalk_AC69(gs_VmContext* ctx, byte startFrameNum, byte endFrameNum) {
	/* TODO */
}

/* AC6A setActorAnimationWalk */
GS_PRIVATE GS_INLINE void op_setActorAnimationWalk_AC6A(gs_VmContext* ctx, byte walkFrameNum) {
	/* TODO */
}

/* AC6B setActorAnimationStand */
GS_PRIVATE GS_INLINE void op_setActorAnimationStand_AC6B(gs_VmContext* ctx, byte standFrameNum) {
	/* TODO */
}

/* AC6C setActorAnimationSpeed */
GS_PRIVATE GS_INLINE void op_setActorAnimationSpeed_AC6C(gs_VmContext* ctx, byte animationSpeed) {
	/* TODO */
}

/* AC6D setActorDefault */
GS_PRIVATE GS_INLINE void op_setActorDefault_AC6D(gs_VmContext* ctx) {
	/* TODO */
}

/* AC6E setActorElevation */
GS_PRIVATE GS_INLINE void op_setActorElevation_AC6E(gs_VmContext* ctx, int16 elevation) {
	/* TODO */
}

/* AC6F setActorPalette */
GS_PRIVATE GS_INLINE void op_setActorPalette_AC6F(gs_VmContext* ctx, byte index, int16 value) {
	/* TODO */
}

/* AC70 setActorTalkColour */
GS_PRIVATE GS_INLINE void op_setActorTalkColour_AC70(gs_VmContext* ctx, byte colourIndex) {
	/* TODO */
}

/* AC71 setActorName */
GS_PRIVATE GS_INLINE void op_setActorName_AC71(gs_VmContext* ctx, char* text) {
	/* TODO */
}

/* AC72 setActorWidth */
GS_PRIVATE GS_INLINE void op_setActorWidth_AC72(gs_VmContext* ctx, int16 width) {
	/* TODO */
}

/* AC73 setActorScale */
GS_PRIVATE GS_INLINE void op_setActorScale_AC73(gs_VmContext* ctx, int16 size) {
	/* TODO */
}

/* AC74 setActorNeverZClip */
GS_PRIVATE GS_INLINE void op_setActorNeverZClip_AC74(gs_VmContext* ctx) {
	/* TODO */
}

/* AC75 setActorAlwaysZClip */
GS_PRIVATE GS_INLINE void op_setActorAlwaysZClip_AC75(gs_VmContext* ctx, byte forceClip) {
	/* TODO */
}

/* AC76 setActorIgnoreBoxes */
GS_PRIVATE GS_INLINE void op_setActorIgnoreBoxes_AC76(gs_VmContext* ctx) {
	/* TODO */
}

/* AC77 setActorFollowBoxes */
GS_PRIVATE GS_INLINE void op_setActorFollowBoxes_AC77(gs_VmContext* ctx) {
	/* TODO */
}

/* AC78 setActorSpecialDraw */
GS_PRIVATE GS_INLINE void op_setActorSpecialDraw_AC78(gs_VmContext* ctx) {
	/* TODO */
}

/* AC79 setActorTextOffset */
GS_PRIVATE GS_INLINE void op_setActorTextOffset_AC79(gs_VmContext* ctx, int16 x, int16 y) {
	/* TODO */
}

/* AC7B setActorVar */
GS_PRIVATE GS_INLINE void op_setActorVar_AC7B(gs_VmContext* ctx, int32 name, int32 value) {
	/* TODO */
}

/* AC7C setActorIgnoreTurns */
GS_PRIVATE GS_INLINE void op_setActorIgnoreTurns_AC7C(gs_VmContext* ctx) {
	/* TODO */
}

/* AC7D setActorFollowTurns */
GS_PRIVATE GS_INLINE void op_setActorFollowTurns_AC7D(gs_VmContext* ctx) {
	/* TODO */
}

/* AC7E setActorNew */
GS_PRIVATE GS_INLINE void op_setActorNew_AC7E(gs_VmContext* ctx) {
	/* TODO */
}

/* AC7F setActorDepth */
GS_PRIVATE GS_INLINE void op_setActorDepth_AC7F(gs_VmContext* ctx, int16 depth) {
	/* TODO */
}

/* AC80 setActorStop */
GS_PRIVATE GS_INLINE void op_setActorStop_AC80(gs_VmContext* ctx) {
	/* TODO */
}

/* AC81 setActorDirection */
GS_PRIVATE GS_INLINE void op_setActorDirection_AC81(gs_VmContext* ctx, int16 direction) {
	/* TODO */
}

/* AC82 actorTurn */
GS_PRIVATE GS_INLINE void op_actorTurn_AC82(gs_VmContext* ctx, int16 direction) {
	/* TODO */
}

/* AC83 setActorWalkScript */
GS_PRIVATE GS_INLINE void op_setActorWalkScript_AC83(gs_VmContext* ctx, int16 scriptNum) {
	/* TODO */
}

/* AC84 setActorTalkScript */
GS_PRIVATE GS_INLINE void op_setActorTalkScript_AC84(gs_VmContext* ctx, int16 scriptNum) {
	/* TODO */
}

/* AC85 setActorWalkingFrozen */
GS_PRIVATE GS_INLINE void op_setActorWalkingFrozen_AC85(gs_VmContext* ctx) {
	/* TODO */
}

/* AC86 setActorWalkingResume */
GS_PRIVATE GS_INLINE void op_setActorWalkingResume_AC86(gs_VmContext* ctx) {
	/* TODO */
}

/* AC87 setActorTalkVolume */
GS_PRIVATE GS_INLINE void op_setActorTalkVolume_AC87(gs_VmContext* ctx, int32 volume) {
	/* TODO */
}

/* AC88 setActorTalkFrequency */
GS_PRIVATE GS_INLINE void op_setActorTalkFrequency_AC88(gs_VmContext* ctx, int32 frequency) {
	/* TODO */
}

/* AC89 setActorTalkPan */
GS_PRIVATE GS_INLINE void op_setActorTalkPan_AC89(gs_VmContext* ctx, int32 pan) {
	/* TODO */
}

/* AD32 setCameraPause */
GS_PRIVATE GS_INLINE void op_setCameraPause_AD32(gs_VmContext* ctx) {
	/* TODO */
}

/* AD33 setCameraResume */
GS_PRIVATE GS_INLINE void op_setCameraResume_AD33(gs_VmContext* ctx) {
	/* TODO */
}

/* AE96 initVerb */
GS_PRIVATE GS_INLINE void op_initVerb_AE96(gs_VmContext* ctx, int16 verbNum) {
	/* TODO */
}

/* AE97 newVerb */
GS_PRIVATE GS_INLINE void op_newVerb_AE97(gs_VmContext* ctx, int16 verbNum) {
	/* TODO */
}

/* AE98 deleteVerb */
GS_PRIVATE GS_INLINE void op_deleteVerb_AE98(gs_VmContext* ctx, int16 verbNum) {
	/* TODO */
}

/* AE99 setVerbName */
GS_PRIVATE GS_INLINE void op_setVerbName_AE99(gs_VmContext* ctx, char* name) {
	/* TODO */
}

/* AE9A setVerbXY */
GS_PRIVATE GS_INLINE void op_setVerbXY_AE9A(gs_VmContext* ctx, int16 x, int16 y) {
	/* TODO */
}

/* AE9B setVerbOn */
GS_PRIVATE GS_INLINE void op_setVerbOn_AE9B(gs_VmContext* ctx) {
	/* TODO */
}

/* AE9C setVerbOff */
GS_PRIVATE GS_INLINE void op_setVerbOff_AE9C(gs_VmContext* ctx) {
	/* TODO */
}

/* AE9D setVerbColour */
GS_PRIVATE GS_INLINE void op_setVerbColour_AE9D(gs_VmContext* ctx, byte colourIndex) {
	/* TODO */
}

/* AE9E setVerbHilightColour */
GS_PRIVATE GS_INLINE void op_setVerbHilightColour_AE9E(gs_VmContext* ctx, byte colourIndex) {
	/* TODO */
}

/* AEA0 setVerbDimColour */
GS_PRIVATE GS_INLINE void op_setVerbDimColour_AEA0(gs_VmContext* ctx, byte colourIndex) {
	/* TODO */
}

/* AEA1 setVerbDim */
GS_PRIVATE GS_INLINE void op_setVerbDim_AEA1(gs_VmContext* ctx) {
	/* TODO */
}

/* AEA2 setVerbKey */
GS_PRIVATE GS_INLINE void op_setVerbKey_AEA2(gs_VmContext* ctx, byte keyCode) {
	/* TODO */
}

/* AEA3 setVerbImage */
GS_PRIVATE GS_INLINE void op_setVerbImage_AEA3(gs_VmContext* ctx, int16 objectNum, byte roomNum) {
	/* TODO */
}

/* AEA4 setVerbNameStr */
GS_PRIVATE GS_INLINE void op_setVerbNameStr_AEA4(gs_VmContext* ctx, int32 textAddress) {
	/* TODO */
}

/* AEA5 setVerbCenter */
GS_PRIVATE GS_INLINE void op_setVerbCenter_AEA5(gs_VmContext* ctx) {
	/* TODO */
}

/* AEA6 setVerbCharSet */
GS_PRIVATE GS_INLINE void op_setVerbCharSet_AEA6(gs_VmContext* ctx, byte charSetNum) {
	/* TODO */
}

/* AEA7 setVerbLinesSpacing */
GS_PRIVATE GS_INLINE void op_setVerbLinesSpacing_AEA7(gs_VmContext* ctx, int16 lineSpacing) {
	/* TODO */
}

/* AF startSound */
GS_PRIVATE GS_INLINE void op_startSound_AF(gs_VmContext* ctx, int32 sound) {
	/* TODO */
}

/* B0 startMusic */
GS_PRIVATE GS_INLINE void op_startMusic_B0(gs_VmContext* ctx, int32 sound) {
	/* TODO */
}

/* B1 stopSound */
GS_PRIVATE GS_INLINE void op_stopSound_B1(gs_VmContext* ctx, int32 sound) {
	/* TODO */
}

/* B2 soundKludge */
GS_PRIVATE GS_INLINE void op_soundKludge_B2(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* B39E restartGame */
GS_PRIVATE GS_INLINE void op_restartGame_B39E(gs_VmContext* ctx) {
	/* TODO */
}

/* B39F pauseGame */
GS_PRIVATE GS_INLINE void op_pauseGame_B39F(gs_VmContext* ctx) {
	/* TODO */
}

/* B3A0 quitGame */
GS_PRIVATE GS_INLINE void op_quitGame_B3A0(gs_VmContext* ctx) {
	/* TODO */
}

/* B4 saveRestoreVerbs */
GS_PRIVATE GS_INLINE void op_saveRestoreVerbs_B4(gs_VmContext* ctx, int32 a, int32 b, int32 c) {
	/* TODO */
}

/* B5 setObjectName */
GS_PRIVATE GS_INLINE void op_setObjectName_B5(gs_VmContext* ctx, int32 obj, char* name) {
	/* TODO */
}

/* B6 getDateTime */
GS_PRIVATE GS_INLINE void op_getDateTime_B6(gs_VmContext* ctx) {
	/* TODO */
}

/* B7 drawBox */
GS_PRIVATE GS_INLINE void op_drawBox_B7(gs_VmContext* ctx, int32 x, int32 y, int32 x2, int32 y2, int32 color) {
	/* TODO */
}

/* B9 startVideo */
GS_PRIVATE GS_INLINE void op_startVideo_B9(gs_VmContext* ctx, char* fileName) {
	/* TODO */
}

/* BA0B lockObject */
GS_PRIVATE GS_INLINE void op_lockObject_BA0B(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA0C unlockObject */
GS_PRIVATE GS_INLINE void op_unlockObject_BA0C(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA0D remapCostumePalette */
GS_PRIVATE GS_INLINE void op_remapCostumePalette_BA0D(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA0E remapCostumeInsert */
GS_PRIVATE GS_INLINE void op_remapCostumeInsert_BA0E(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA0F setVideoFrameRate */
GS_PRIVATE GS_INLINE void op_setVideoFrameRate_BA0F(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA14 setBoxScaleSlot */
GS_PRIVATE GS_INLINE void op_setBoxScaleSlot_BA14(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA15 setScaleSlot */
GS_PRIVATE GS_INLINE void op_setScaleSlot_BA15(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA16 setBannerColours */
GS_PRIVATE GS_INLINE void op_setBannerColours_BA16(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA17 setActorChoreLimbFrame */
GS_PRIVATE GS_INLINE void op_setActorChoreLimbFrame_BA17(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA18 clearTextQueue */
GS_PRIVATE GS_INLINE void op_clearTextQueue_BA18(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA19 saveGameReadName */
GS_PRIVATE GS_INLINE void op_saveGameReadName_BA19(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA1A saveGameWrite */
GS_PRIVATE GS_INLINE void op_saveGameWrite_BA1A(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA1B saveGameRead */
GS_PRIVATE GS_INLINE void op_saveGameRead_BA1B(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA1C saveGameScreenshot */
GS_PRIVATE GS_INLINE void op_saveGameScreenshot_BA1C(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA1D setKeyScript */
GS_PRIVATE GS_INLINE void op_setKeyScript_BA1D(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA1E killAllScriptsExceptCurrent */
GS_PRIVATE GS_INLINE void op_killAllScriptsExceptCurrent_BA1E(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA1F stopAllVideo */
GS_PRIVATE GS_INLINE void op_stopAllVideo_BA1F(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA20 writeRegistryValue */
GS_PRIVATE GS_INLINE void op_writeRegistryValue_BA20(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA21 setPaletteIntensity */
GS_PRIVATE GS_INLINE void op_setPaletteIntensity_BA21(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA22 queryQuit */
GS_PRIVATE GS_INLINE void op_queryQuit_BA22(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA6C buildPaletteShadow */
GS_PRIVATE GS_INLINE void op_buildPaletteShadow_BA6C(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA6D setPaletteShadow */
GS_PRIVATE GS_INLINE void op_setPaletteShadow_BA6D(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA6E blastShadowObject */
GS_PRIVATE GS_INLINE void op_blastShadowObject_BA6E(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* BA6F superBlastObject */
GS_PRIVATE GS_INLINE void op_superBlastObject_BA6F(gs_VmContext* ctx, int32 argsLength, int32* args) {
	/* TODO */
}

/* C0 dim2DimArray */
GS_PRIVATE GS_INLINE void op_dim2DimArray_C0(gs_VmContext* ctx, int32 dim2, int32 dim1) {
	/* TODO */
}

/* C6 distObjectPt */
GS_PRIVATE GS_INLINE void op_distObjectPt_C6(gs_VmContext* ctx, int32 a, int32 b, int32 c) {
	/* TODO */
}

/* C8 startScriptQuick2 */
GS_PRIVATE GS_INLINE void op_startScriptQuick2_C8(gs_VmContext* ctx, int32 script, int32 argsLength, int32* args) {
	/* TODO */
}

/* C9 startObjectQuick */
GS_PRIVATE GS_INLINE void op_startObjectQuick_C9(gs_VmContext* ctx, int32 script, byte entryPc, int32 argsLength, int32* args) {
	/* TODO */
}

/* CA pickOneOf */
GS_PRIVATE GS_INLINE void op_pickOneOf_CA(gs_VmContext* ctx, int32 i, int32 argsLength, int32* args) {
	/* TODO */
}

/* CB pickOneOfDefault */
GS_PRIVATE GS_INLINE void op_pickOneOfDefault_CB(gs_VmContext* ctx, int32 i, int32 argsLength, int32* args, int32 def) {
	/* TODO */
}

/* CD isAnyOf */
GS_PRIVATE GS_INLINE void op_isAnyOf_CD(gs_VmContext* ctx, int32 value, int32 argsLength, int32* args) {
	/* TODO */
}

/* CE getRandomNumber */
GS_PRIVATE GS_INLINE void op_getRandomNumber_CE(gs_VmContext* ctx, int32 max) {
	/* TODO */
}

/* CF getRandomNumberRange */
GS_PRIVATE GS_INLINE void op_getRandomNumberRange_CF(gs_VmContext* ctx, int32 min, int32 max) {
	/* TODO */
}

/* D0 ifClassOfIs */
GS_PRIVATE GS_INLINE void op_ifClassOfIs_D0(gs_VmContext* ctx, int32 obj, int32 argsLength, int32* args) {
	/* TODO */
}

/* D1 getState */
GS_PRIVATE GS_INLINE void op_getState_D1(gs_VmContext* ctx, int32 obj) {
	/* TODO */
}

/* D2 getOwner */
GS_PRIVATE GS_INLINE void op_getOwner_D2(gs_VmContext* ctx, int32 obj) {
	/* TODO */
}

/* D3 isScriptRunning */
GS_PRIVATE GS_INLINE void op_isScriptRunning_D3(gs_VmContext* ctx, int32 script) {
	/* TODO */
}

/* D4 shuffle */
GS_PRIVATE GS_INLINE void op_shuffle_D4(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* D5 isSoundRunning */
GS_PRIVATE GS_INLINE void op_isSoundRunning_D5(gs_VmContext* ctx, int32 sound) {
	/* TODO */
}

/* D6 abs */
GS_PRIVATE GS_INLINE void op_abs_D6(gs_VmContext* ctx, int32 value) {
	/* TODO */
}

/* D873 getWalkBoxAt */
GS_PRIVATE GS_INLINE void op_getWalkBoxAt_D873(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D874 isPointInBox */
GS_PRIVATE GS_INLINE void op_isPointInBox_D874(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8CE getRGBSlot */
GS_PRIVATE GS_INLINE void op_getRGBSlot_D8CE(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8D3 getKeyState */
GS_PRIVATE GS_INLINE void op_getKeyState_D8D3(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8D7 getBox */
GS_PRIVATE GS_INLINE void op_getBox_D8D7(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8D8 findBlastObject */
GS_PRIVATE GS_INLINE void op_findBlastObject_D8D8(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8D9 actorHitTest */
GS_PRIVATE GS_INLINE void op_actorHitTest_D8D9(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8DA setLipSyncWidth */
GS_PRIVATE GS_INLINE void op_setLipSyncWidth_D8DA(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8DB setLipSyncHeight */
GS_PRIVATE GS_INLINE void op_setLipSyncHeight_D8DB(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8DC setTalkAnimation */
GS_PRIVATE GS_INLINE void op_setTalkAnimation_D8DC(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8DD getGroupSfxVol */
GS_PRIVATE GS_INLINE void op_getGroupSfxVol_D8DD(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8DE getGroupVoiceVol */
GS_PRIVATE GS_INLINE void op_getGroupVoiceVol_D8DE(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8DF getGroupMusicVol */
GS_PRIVATE GS_INLINE void op_getGroupMusicVol_D8DF(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8E0 readRegistryValue */
GS_PRIVATE GS_INLINE void op_readRegistryValue_D8E0(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8E1 imuseGetMusicPosition */
GS_PRIVATE GS_INLINE void op_imuseGetMusicPosition_D8E1(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8E2 imuseGetMusicLipSyncWidth */
GS_PRIVATE GS_INLINE void op_imuseGetMusicLipSyncWidth_D8E2(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D8E3 imuseGetMusicLipSyncHeight */
GS_PRIVATE GS_INLINE void op_imuseGetMusicLipSyncHeight_D8E3(gs_VmContext* ctx, int32 args) {
	/* TODO */
}

/* D9 isActorInBox */
GS_PRIVATE GS_INLINE void op_isActorInBox_D9(gs_VmContext* ctx, int32 index, int32 box) {
	/* TODO */
}

/* DA getVerbEntrypoint */
GS_PRIVATE GS_INLINE void op_getVerbEntrypoint_DA(gs_VmContext* ctx, int32 verb, int32 entryp) {
	/* TODO */
}

/* DB getActorFromXY */
GS_PRIVATE GS_INLINE void op_getActorFromXY_DB(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* DC findObject */
GS_PRIVATE GS_INLINE void op_findObject_DC(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* DD getVerbFromXY */
GS_PRIVATE GS_INLINE void op_getVerbFromXY_DD(gs_VmContext* ctx, int32 x, int32 y) {
	/* TODO */
}

/* DF findInventory */
GS_PRIVATE GS_INLINE void op_findInventory_DF(gs_VmContext* ctx, int32 owner, int32 index) {
	/* TODO */
}

/* E0 getInventoryCount */
GS_PRIVATE GS_INLINE void op_getInventoryCount_E0(gs_VmContext* ctx, int32 owner) {
	/* TODO */
}

/* E1 getAnimateVariable */
GS_PRIVATE GS_INLINE void op_getAnimateVariable_E1(gs_VmContext* ctx, int32 index, int32 variable) {
	/* TODO */
}

/* E2 getActorRoom */
GS_PRIVATE GS_INLINE void op_getActorRoom_E2(gs_VmContext* ctx, int32 index) {
	/* TODO */
}

/* E3 getActorWalkBox */
GS_PRIVATE GS_INLINE void op_getActorWalkBox_E3(gs_VmContext* ctx, int32 index) {
	/* TODO */
}

/* E4 getActorMoving */
GS_PRIVATE GS_INLINE void op_getActorMoving_E4(gs_VmContext* ctx, int32 index) {
	/* TODO */
}

/* E5 getActorCostume */
GS_PRIVATE GS_INLINE void op_getActorCostume_E5(gs_VmContext* ctx, int32 index) {
	/* TODO */
}

/* E6 getActorScaleX */
GS_PRIVATE GS_INLINE void op_getActorScaleX_E6(gs_VmContext* ctx, int32 index) {
	/* TODO */
}

/* E7 getActorLayer */
GS_PRIVATE GS_INLINE void op_getActorLayer_E7(gs_VmContext* ctx, int32 index) {
	/* TODO */
}

/* E8 getActorElevation */
GS_PRIVATE GS_INLINE void op_getActorElevation_E8(gs_VmContext* ctx, int32 index) {
	/* TODO */
}

/* E9 getActorWidth */
GS_PRIVATE GS_INLINE void op_getActorWidth_E9(gs_VmContext* ctx, int32 index) {
	/* TODO */
}

/* EA getObjectNewDir */
GS_PRIVATE GS_INLINE void op_getObjectNewDir_EA(gs_VmContext* ctx, int32 index) {
	/* TODO */
}

/* EB getObjectX */
GS_PRIVATE GS_INLINE void op_getObjectX_EB(gs_VmContext* ctx, int32 index) {
	/* TODO */
}

/* EC getObjectY */
GS_PRIVATE GS_INLINE void op_getObjectY_EC(gs_VmContext* ctx, int32 index) {
	/* TODO */
}

/* ED getActorChore */
GS_PRIVATE GS_INLINE void op_getActorChore_ED(gs_VmContext* ctx, int16 actorNum) {
	/* TODO */
}

/* EE distObjectObject */
GS_PRIVATE GS_INLINE void op_distObjectObject_EE(gs_VmContext* ctx, int32 left, int32 right) {
	/* TODO */
}

/* EF distObjectPtPt */
GS_PRIVATE GS_INLINE void op_distObjectPtPt_EF(gs_VmContext* ctx, int32 a, int32 b, int32 c, int32 d) {
	/* TODO */
}

/* F0 getObjectImageX */
GS_PRIVATE GS_INLINE void op_getObjectImageX_F0(gs_VmContext* ctx, int16 objectNum) {
	/* TODO */
}

/* F1 getObjectImageY */
GS_PRIVATE GS_INLINE void op_getObjectImageY_F1(gs_VmContext* ctx, int16 objectNum) {
	/* TODO */
}

/* F2 getObjectImageWidth */
GS_PRIVATE GS_INLINE void op_getObjectImageWidth_F2(gs_VmContext* ctx, int16 objectNum) {
	/* TODO */
}

/* F3 getObjectImageHeight */
GS_PRIVATE GS_INLINE void op_getObjectImageHeight_F3(gs_VmContext* ctx, int16 objectNum) {
	/* TODO */
}

/* F6 getStringWidth */
GS_PRIVATE GS_INLINE void op_getStringWidth_F6(gs_VmContext* ctx, char* text, int16 charsetNum) {
	/* TODO */
}

/* F7 getActorZPlane */
GS_PRIVATE GS_INLINE void op_getActorZPlane_F7(gs_VmContext* ctx, int16 actorNum) {
	/* TODO */
}








int gs_vm_decode(gs_VmContext* ctx, byte op1, byte op2) {
	switch(op1) {
		default:
			return 1;
		/* pushByte */
		case 0x00: {
			byte value = readByte();
			op_pushByte_00(ctx, value);
		}
		return 0;
		/* pushWord */
		case 0x01: {
			int32 value = readLong();
			op_pushWord_01(ctx, value);
		}
		return 0;
		/* pushWordVar */
		case 0x02: {
			int32 name = readLong();
			op_pushWordVar_02(ctx, name);
		}
		return 0;
		/* wordArrayRead */
		case 0x03: {
			int32 base = pullStackLong();
			op_wordArrayRead_03(ctx, base);
		}
		return 0;
		/* wordArrayIndexedRead */
		case 0x04: {
			int32 arrayNum = readLong();
			int32 base = pullStackLong();
			int32 index = pullStackLong();
			op_wordArrayIndexedRead_04(ctx, index, base, arrayNum);
		}
		return 0;
		/* dup */
		case 0x05: {
			int32 value = pullStackLong();
			op_dup_05(ctx, value);
		}
		return 0;
		/* pop */
		case 0x06: {
			int32 discard = pullStackLong();
			op_pop_06(ctx, discard);
		}
		return 0;
		/* not */
		case 0x07: {
			int32 value = pullStackLong();
			op_not_07(ctx, value);
		}
		return 0;
		/* eq */
		case 0x08: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_eq_08(ctx, left, right);
		}
		return 0;
		/* neq */
		case 0x09: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_neq_09(ctx, left, right);
		}
		return 0;
		/* gt */
		case 0x0A: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_gt_0A(ctx, left, right);
		}
		return 0;
		/* lt */
		case 0x0B: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_lt_0B(ctx, left, right);
		}
		return 0;
		/* le */
		case 0x0C: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_le_0C(ctx, left, right);
		}
		return 0;
		/* ge */
		case 0x0D: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_ge_0D(ctx, left, right);
		}
		return 0;
		/* add */
		case 0x0E: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_add_0E(ctx, left, right);
		}
		return 0;
		/* sub */
		case 0x0F: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_sub_0F(ctx, left, right);
		}
		return 0;
		/* mul */
		case 0x10: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_mul_10(ctx, left, right);
		}
		return 0;
		/* div */
		case 0x11: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_div_11(ctx, left, right);
		}
		return 0;
		/* land */
		case 0x12: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_land_12(ctx, left, right);
		}
		return 0;
		/* lor */
		case 0x13: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_lor_13(ctx, left, right);
		}
		return 0;
		/* band */
		case 0x14: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_band_14(ctx, left, right);
		}
		return 0;
		/* bor */
		case 0x15: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_bor_15(ctx, left, right);
		}
		return 0;
		/* mod */
		case 0x16: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_mod_16(ctx, left, right);
		}
		return 0;
		/* writeByteVar */
		case 0x42: {
			int32 value = pullStackLong();
			op_writeByteVar_42(ctx, value);
		}
		return 0;
		/* byteArrayWrite */
		case 0x46: {
			int32 value = pullStackLong();
			int32 base = pullStackLong();
			op_byteArrayWrite_46(ctx, base, value);
		}
		return 0;
		/* byteArrayIndexedWrite */
		case 0x4A: {
			int32 value = pullStackLong();
			int32 base = pullStackLong();
			int32 index = pullStackLong();
			op_byteArrayIndexedWrite_4A(ctx, index, base, value);
		}
		return 0;
		/* byteVarInc */
		case 0x4E: {
			op_byteVarInc_4E(ctx);
		}
		return 0;
		/* byteArrayInc */
		case 0x52: {
			int32 base = pullStackLong();
			op_byteArrayInc_52(ctx, base);
		}
		return 0;
		/* byteVarDec */
		case 0x56: {
			op_byteVarDec_56(ctx);
		}
		return 0;
		/* byteArrayDec */
		case 0x5A: {
			int32 base = pullStackLong();
			op_byteArrayDec_5A(ctx, base);
		}
		return 0;
		/* drawObject */
		case 0x61: {
			int32 state = pullStackLong();
			int32 obj = pullStackLong();
			op_drawObject_61(ctx, obj, state);
		}
		return 0;
		/* drawObjectAt */
		case 0x62: {
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			int32 obj = pullStackLong();
			op_drawObjectAt_62(ctx, obj, x, y);
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
			op_drawBlastObject_63(ctx, a, b, c, d, e, argsLength, args);
		}
		return 0;
		/* if */
		case 0x64: {
			int32 offset = readLong();
			int32 condition = pullStackLong();
			op_if_64(ctx, condition, offset);
		}
		return 0;
		/* ifNot */
		case 0x65: {
			int32 offset = readLong();
			int32 condition = pullStackLong();
			op_ifNot_65(ctx, condition, offset);
		}
		return 0;
		/* jump */
		case 0x66: {
			int32 offset = readLong();
			op_jump_66(ctx, offset);
		}
		return 0;
		/* breakHere */
		case 0x67: {
			op_breakHere_67(ctx);
		}
		return 0;
		/* delayFrames */
		case 0x68: {
			op_delayFrames_68(ctx);
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
					op_waitActor_691E(ctx, offset, actorNum);
				}
				return 0;
				/* waitMessage */
				case 0x1F: {
					op_waitMessage_691F(ctx);
				}
				return 0;
				/* waitCamera */
				case 0x20: {
					op_waitCamera_6920(ctx);
				}
				return 0;
				/* waitSentence */
				case 0x21: {
					op_waitSentence_6921(ctx);
				}
				return 0;
				/* waitAnimation */
				case 0x22: {
					op_waitAnimation_6922(ctx);
				}
				return 0;
				/* waitTurn */
				case 0x23: {
					int32 actorNum = pullStackLong();
					int32 offset = readLong();
					op_waitTurn_6923(ctx, offset, actorNum);
				}
				return 0;
		}
		return 1;
		/* delay */
		case 0x6A: {
			int32 delay = pullStackLong();
			op_delay_6A(ctx, delay);
		}
		return 0;
		/* delaySeconds */
		case 0x6B: {
			int32 seconds = pullStackLong();
			op_delaySeconds_6B(ctx, seconds);
		}
		return 0;
		/* delayMinutes */
		case 0x6C: {
			int32 minutes = pullStackLong();
			op_delayMinutes_6C(ctx, minutes);
		}
		return 0;
		/* writeWordVar */
		case 0x6D: {
			int32 value = pullStackLong();
			op_writeWordVar_6D(ctx, value);
		}
		return 0;
		/* wordVarInc */
		case 0x6E: {
			int32 var = readLong();
			op_wordVarInc_6E(ctx, var);
		}
		return 0;
		/* wordVarDec */
		case 0x6F: {
			int32 var = readLong();
			op_wordVarDec_6F(ctx, var);
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
					op_newArrayInt_700A(ctx, arrayNum, dim1);
				}
				return 0;
				/* newArrayString */
				case 0x0B: {
					int32 dim1 = pullStackLong();
					int32 arrayNum = readLong();
					op_newArrayString_700B(ctx, arrayNum, dim1);
				}
				return 0;
				/* deleteArray */
				case 0x0C: {
					int32 arrayNum = readLong();
					op_deleteArray_700C(ctx, arrayNum);
				}
				return 0;
		}
		return 1;
		/* wordArrayWrite */
		case 0x71: {
			int32 value = pullStackLong();
			int32 base = pullStackLong();
			op_wordArrayWrite_71(ctx, base, value);
		}
		return 0;
		/* wordArrayInc */
		case 0x72: {
			int32 base = pullStackLong();
			op_wordArrayInc_72(ctx, base);
		}
		return 0;
		/* wordArrayDec */
		case 0x73: {
			int32 base = pullStackLong();
			op_wordArrayDec_73(ctx, base);
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
					op_newArray2Int_740A(ctx, arrayNum, dim1, dim2);
				}
				return 0;
				/* newArray2String */
				case 0x0B: {
					int32 dim2 = pullStackLong();
					int32 dim1 = pullStackLong();
					int32 arrayNum = readLong();
					op_newArray2String_740B(ctx, arrayNum, dim1, dim2);
				}
				return 0;
				/* deleteArray2 */
				case 0x0C: {
					int32 arrayNum = readLong();
					op_deleteArray2_740C(ctx, arrayNum);
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
			op_wordArrayIndexedWrite_75(ctx, index, base, value, arrayNum);
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
					op_setArrayString_7614(ctx, string, offset, arrayNum);
				}
				return 0;
				/* setArrayList */
				case 0x15: {
					int32 arrayNum = readLong();
					int32 offset = pullStackLong();
					int32 listLength = pullStack();
					int32* list = pullList(listLength, 25);
					op_setArrayList_7615(ctx, listLength, list, offset, arrayNum);
				}
				return 0;
				/* setArray2List */
				case 0x16: {
					int32 arrayNum = readLong();
					int32 offset = pullStackLong();
					int32 listLength = pullStack();
					int32* list = pullList(listLength, 25);
					op_setArray2List_7616(ctx, listLength, list, offset, arrayNum);
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
			op_startScript_79(ctx, flags, script, argsLength, args);
		}
		return 0;
		/* startScriptQuick */
		case 0x7A: {
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			int32 script = pullStackLong();
			op_startScriptQuick_7A(ctx, script, argsLength, args);
		}
		return 0;
		/* stopObjectCode */
		case 0x7B: {
			op_stopObjectCode_7B(ctx);
		}
		return 0;
		/* stopScript */
		case 0x7C: {
			int32 scriptNum = pullStackLong();
			op_stopScript_7C(ctx, scriptNum);
		}
		return 0;
		/* jumpToScript */
		case 0x7D: {
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			int32 scriptNum = pullStackLong();
			int32 flags = pullStackLong();
			op_jumpToScript_7D(ctx, flags, scriptNum, argsLength, args);
		}
		return 0;
		/* dummy */
		case 0x7E: {
			op_dummy_7E(ctx);
		}
		return 0;
		/* startObject */
		case 0x7F: {
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			byte entryp = pullStackByte();
			int32 script = pullStackLong();
			int32 flags = pullStackLong();
			op_startObject_7F(ctx, flags, script, entryp, argsLength, args);
		}
		return 0;
		/* stopObjectScript */
		case 0x80: {
			int16 script = pullStackWord();
			op_stopObjectScript_80(ctx, script);
		}
		return 0;
		/* cutscene */
		case 0x81: {
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			op_cutscene_81(ctx, argsLength, args);
		}
		return 0;
		/* endCutscene */
		case 0x82: {
			op_endCutscene_82(ctx);
		}
		return 0;
		/* freezeUnfreeze */
		case 0x83: {
			int32 script = pullStackLong();
			op_freezeUnfreeze_83(ctx, script);
		}
		return 0;
		/* beginOverride */
		case 0x84: {
			op_beginOverride_84(ctx);
		}
		return 0;
		/* endOverride */
		case 0x85: {
			op_endOverride_85(ctx);
		}
		return 0;
		/* stopSentence */
		case 0x86: {
			op_stopSentence_86(ctx);
		}
		return 0;
		/* setClass */
		case 0x89: {
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			int32 obj = pullStackLong();
			op_setClass_89(ctx, obj, argsLength, args);
		}
		return 0;
		/* setState */
		case 0x8A: {
			int32 state = pullStackLong();
			int32 obj = pullStackLong();
			op_setState_8A(ctx, obj, state);
		}
		return 0;
		/* setOwner */
		case 0x8B: {
			int32 owner = pullStackLong();
			int32 obj = pullStackLong();
			op_setOwner_8B(ctx, obj, owner);
		}
		return 0;
		/* panCameraTo */
		case 0x8C: {
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			op_panCameraTo_8C(ctx, x, y);
		}
		return 0;
		/* actorFollowCamera */
		case 0x8D: {
			int32 index = pullStackLong();
			op_actorFollowCamera_8D(ctx, index);
		}
		return 0;
		/* setCameraAt */
		case 0x8E: {
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			op_setCameraAt_8E(ctx, x, y);
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
					op_printActorAt_8F41(ctx, x, y);
				}
				return 0;
				/* printActorColour */
				case 0x42: {
					int32 col = pullStackLong();
					op_printActorColour_8F42(ctx, col);
				}
				return 0;
				/* printActorClipped */
				case 0x43: {
					int32 right = pullStackLong();
					op_printActorClipped_8F43(ctx, right);
				}
				return 0;
				/* printActorCentre */
				case 0x45: {
					op_printActorCentre_8F45(ctx);
				}
				return 0;
				/* printActorLeft */
				case 0x47: {
					op_printActorLeft_8F47(ctx);
				}
				return 0;
				/* printActorOverhead */
				case 0x48: {
					op_printActorOverhead_8F48(ctx);
				}
				return 0;
				/* printActorMumble */
				case 0x4A: {
					op_printActorMumble_8F4A(ctx);
				}
				return 0;
				/* printActorText */
				case 0x4B: {
					char* text = readText();
					op_printActorText_8F4B(ctx, text);
				}
				return 0;
				/* printActorLoadDefault */
				case 0xFE: {
					int32 actorNum = pullStackLong();
					op_printActorLoadDefault_8FFE(ctx, actorNum);
				}
				return 0;
				/* printActorSaveDefault */
				case 0xFF: {
					op_printActorSaveDefault_8FFF(ctx);
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
					op_printEgoAt_9041(ctx, x, y);
				}
				return 0;
				/* printEgoColour */
				case 0x42: {
					int32 col = pullStackLong();
					op_printEgoColour_9042(ctx, col);
				}
				return 0;
				/* printEgoClipped */
				case 0x43: {
					int32 right = pullStackLong();
					op_printEgoClipped_9043(ctx, right);
				}
				return 0;
				/* printEgoCentre */
				case 0x45: {
					op_printEgoCentre_9045(ctx);
				}
				return 0;
				/* printEgoLeft */
				case 0x47: {
					op_printEgoLeft_9047(ctx);
				}
				return 0;
				/* printEgoOverhead */
				case 0x48: {
					op_printEgoOverhead_9048(ctx);
				}
				return 0;
				/* printEgoMumble */
				case 0x4A: {
					op_printEgoMumble_904A(ctx);
				}
				return 0;
				/* printEgoText */
				case 0x4B: {
					char* text = readText();
					op_printEgoText_904B(ctx, text);
				}
				return 0;
				/* printEgoLoadDefault */
				case 0xFE: {
					int32 actorNum = pullStackLong();
					op_printEgoLoadDefault_90FE(ctx, actorNum);
				}
				return 0;
				/* printEgoSaveDefault */
				case 0xFF: {
					op_printEgoSaveDefault_90FF(ctx);
				}
				return 0;
		}
		return 1;
		/* talkActor */
		case 0x91: {
			int32 actor = pullStackLong();
			char* text = readText();
			op_talkActor_91(ctx, text, actor);
		}
		return 0;
		/* talkEgo */
		case 0x92: {
			char* text = readText();
			op_talkEgo_92(ctx, text);
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
					op_printLineAt_9341(ctx, x, y);
				}
				return 0;
				/* printLineColour */
				case 0x42: {
					int32 col = pullStackLong();
					op_printLineColour_9342(ctx, col);
				}
				return 0;
				/* printLineClipped */
				case 0x43: {
					int32 right = pullStackLong();
					op_printLineClipped_9343(ctx, right);
				}
				return 0;
				/* printLineCentre */
				case 0x45: {
					op_printLineCentre_9345(ctx);
				}
				return 0;
				/* printLineLeft */
				case 0x47: {
					op_printLineLeft_9347(ctx);
				}
				return 0;
				/* printLineOverhead */
				case 0x48: {
					op_printLineOverhead_9348(ctx);
				}
				return 0;
				/* printLineMumble */
				case 0x4A: {
					op_printLineMumble_934A(ctx);
				}
				return 0;
				/* printLineText */
				case 0x4B: {
					char* text = readText();
					op_printLineText_934B(ctx, text);
				}
				return 0;
				/* printLineLoadDefault */
				case 0xFE: {
					op_printLineLoadDefault_93FE(ctx);
				}
				return 0;
				/* printLineSaveDefault */
				case 0xFF: {
					op_printLineSaveDefault_93FF(ctx);
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
					op_printTextAt_9441(ctx, x, y);
				}
				return 0;
				/* printTextColour */
				case 0x42: {
					int32 col = pullStackLong();
					op_printTextColour_9442(ctx, col);
				}
				return 0;
				/* printTextClipped */
				case 0x43: {
					int32 right = pullStackLong();
					op_printTextClipped_9443(ctx, right);
				}
				return 0;
				/* printTextCentre */
				case 0x45: {
					op_printTextCentre_9445(ctx);
				}
				return 0;
				/* printTextLeft */
				case 0x47: {
					op_printTextLeft_9447(ctx);
				}
				return 0;
				/* printTextOverhead */
				case 0x48: {
					op_printTextOverhead_9448(ctx);
				}
				return 0;
				/* printTextMumble */
				case 0x4A: {
					op_printTextMumble_944A(ctx);
				}
				return 0;
				/* printTextText */
				case 0x4B: {
					char* text = readText();
					op_printTextText_944B(ctx, text);
				}
				return 0;
				/* printTextLoadDefault */
				case 0xFE: {
					op_printTextLoadDefault_94FE(ctx);
				}
				return 0;
				/* printTextSaveDefault */
				case 0xFF: {
					op_printTextSaveDefault_94FF(ctx);
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
					op_printDebugAt_9541(ctx, x, y);
				}
				return 0;
				/* printDebugColour */
				case 0x42: {
					int32 col = pullStackLong();
					op_printDebugColour_9542(ctx, col);
				}
				return 0;
				/* printDebugClipped */
				case 0x43: {
					int32 right = pullStackLong();
					op_printDebugClipped_9543(ctx, right);
				}
				return 0;
				/* printDebugCentre */
				case 0x45: {
					op_printDebugCentre_9545(ctx);
				}
				return 0;
				/* printDebugLeft */
				case 0x47: {
					op_printDebugLeft_9547(ctx);
				}
				return 0;
				/* printDebugOverhead */
				case 0x48: {
					op_printDebugOverhead_9548(ctx);
				}
				return 0;
				/* printDebugMumble */
				case 0x4A: {
					op_printDebugMumble_954A(ctx);
				}
				return 0;
				/* printDebugText */
				case 0x4B: {
					char* text = readText();
					op_printDebugText_954B(ctx, text);
				}
				return 0;
				/* printDebugLoadDefault */
				case 0xFE: {
					op_printDebugLoadDefault_95FE(ctx);
				}
				return 0;
				/* printDebugSaveDefault */
				case 0xFF: {
					op_printDebugSaveDefault_95FF(ctx);
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
					op_printSystemAt_9641(ctx, x, y);
				}
				return 0;
				/* printSystemColour */
				case 0x42: {
					int32 col = pullStackLong();
					op_printSystemColour_9642(ctx, col);
				}
				return 0;
				/* printSystemClipped */
				case 0x43: {
					int32 right = pullStackLong();
					op_printSystemClipped_9643(ctx, right);
				}
				return 0;
				/* printSystemCentre */
				case 0x45: {
					op_printSystemCentre_9645(ctx);
				}
				return 0;
				/* printSystemLeft */
				case 0x47: {
					op_printSystemLeft_9647(ctx);
				}
				return 0;
				/* printSystemOverhead */
				case 0x48: {
					op_printSystemOverhead_9648(ctx);
				}
				return 0;
				/* printSystemMumble */
				case 0x4A: {
					op_printSystemMumble_964A(ctx);
				}
				return 0;
				/* printSystemText */
				case 0x4B: {
					char* text = readText();
					op_printSystemText_964B(ctx, text);
				}
				return 0;
				/* printSystemLoadDefault */
				case 0xFE: {
					op_printSystemLoadDefault_96FE(ctx);
				}
				return 0;
				/* printSystemSaveDefault */
				case 0xFF: {
					op_printSystemSaveDefault_96FF(ctx);
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
					op_blastTextAt_9741(ctx, x, y);
				}
				return 0;
				/* blastTextColour */
				case 0x42: {
					int32 col = pullStackLong();
					op_blastTextColour_9742(ctx, col);
				}
				return 0;
				/* blastTextClipped */
				case 0x43: {
					int32 right = pullStackLong();
					op_blastTextClipped_9743(ctx, right);
				}
				return 0;
				/* blastTextCentre */
				case 0x45: {
					op_blastTextCentre_9745(ctx);
				}
				return 0;
				/* blastTextLeft */
				case 0x47: {
					op_blastTextLeft_9747(ctx);
				}
				return 0;
				/* blastTextOverhead */
				case 0x48: {
					op_blastTextOverhead_9748(ctx);
				}
				return 0;
				/* blastTextMumble */
				case 0x4A: {
					op_blastTextMumble_974A(ctx);
				}
				return 0;
				/* blastTextText */
				case 0x4B: {
					char* text = readText();
					op_blastTextText_974B(ctx, text);
				}
				return 0;
				/* blastTextLoadDefault */
				case 0xFE: {
					op_blastTextLoadDefault_97FE(ctx);
				}
				return 0;
				/* blastTextSaveDefault */
				case 0xFF: {
					op_blastTextSaveDefault_97FF(ctx);
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
			op_drawObject_98(ctx, obj, x, y, state);
		}
		return 0;
		case 0x9C: {
			consumeByte();
			switch(op2) {
				default:
					return 1;
				/* cursorOn */
				case 0xDC: {
					op_cursorOn_9CDC(ctx);
				}
				return 0;
				/* cursorOff */
				case 0xDD: {
					op_cursorOff_9CDD(ctx);
				}
				return 0;
				/* cursorSoftOn */
				case 0xDE: {
					op_cursorSoftOn_9CDE(ctx);
				}
				return 0;
				/* cursorSoftOff */
				case 0xDF: {
					op_cursorSoftOff_9CDF(ctx);
				}
				return 0;
				/* cursorUserPutOn */
				case 0xE0: {
					op_cursorUserPutOn_9CE0(ctx);
				}
				return 0;
				/* cursorUserPutOff */
				case 0xE1: {
					op_cursorUserPutOff_9CE1(ctx);
				}
				return 0;
				/* cursorUserPutSoftOn */
				case 0xE2: {
					op_cursorUserPutSoftOn_9CE2(ctx);
				}
				return 0;
				/* cursorUserPutSoftOff */
				case 0xE3: {
					op_cursorUserPutSoftOff_9CE3(ctx);
				}
				return 0;
				/* cursorUserCursorImage */
				case 0xE4: {
					int32 obj = pullStackLong();
					int32 idx = pullStackLong();
					op_cursorUserCursorImage_9CE4(ctx, idx, obj);
				}
				return 0;
				/* cursorHotSpot */
				case 0xE5: {
					int32 y = pullStackLong();
					int32 x = pullStackLong();
					op_cursorHotSpot_9CE5(ctx, x, y);
				}
				return 0;
				/* cursorSetTransparency */
				case 0xE6: {
					int32 enabled = pullStackLong();
					op_cursorSetTransparency_9CE6(ctx, enabled);
				}
				return 0;
				/* cursorSetCharSet */
				case 0xE7: {
					int32 charsetNum = pullStackLong();
					op_cursorSetCharSet_9CE7(ctx, charsetNum);
				}
				return 0;
				/* cursorSetColour */
				case 0xE8: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_cursorSetColour_9CE8(ctx, argsLength, args);
				}
				return 0;
				/* cursorSetPos */
				case 0xE9: {
					int32 y = pullStackLong();
					int32 x = pullStackLong();
					op_cursorSetPos_9CE9(ctx, x, y);
				}
				return 0;
		}
		return 1;
		/* loadRoom */
		case 0x9D: {
			byte room = pullStackByte();
			op_loadRoom_9D(ctx, room);
		}
		return 0;
		/* loadRoomWithEgo */
		case 0x9E: {
			int32 room = pullStackLong();
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			op_loadRoomWithEgo_9E(ctx, x, y, room);
		}
		return 0;
		/* walkActorToObj */
		case 0x9F: {
			int32 dist = pullStackLong();
			int32 obj = pullStackLong();
			int32 index = pullStackLong();
			op_walkActorToObj_9F(ctx, index, obj, dist);
		}
		return 0;
		/* walkActorTo */
		case 0xA0: {
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			int32 index = pullStackLong();
			op_walkActorTo_A0(ctx, index, x, y);
		}
		return 0;
		/* putActorAtXY */
		case 0xA1: {
			int32 room = pullStackLong();
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			int32 actorIndex = pullStackLong();
			op_putActorAtXY_A1(ctx, actorIndex, x, y, room);
		}
		return 0;
		/* putActorAtObject */
		case 0xA2: {
			int32 obj = pullStackLong();
			op_putActorAtObject_A2(ctx, obj);
		}
		return 0;
		/* faceActor */
		case 0xA3: {
			int32 obj = pullStackLong();
			int32 index = pullStackLong();
			op_faceActor_A3(ctx, index, obj);
		}
		return 0;
		/* animateActor */
		case 0xA4: {
			int32 anim = pullStackLong();
			int32 index = pullStackLong();
			op_animateActor_A4(ctx, index, anim);
		}
		return 0;
		/* doSentence */
		case 0xA5: {
			int16 objectB = pullStackWord();
			int16 objectA = pullStackWord();
			byte verb = pullStackByte();
			op_doSentence_A5(ctx, verb, objectA, objectB);
		}
		return 0;
		/* pickupObject */
		case 0xA6: {
			int32 obj = pullStackLong();
			op_pickupObject_A6(ctx, obj);
		}
		return 0;
		/* setBoxFlags */
		case 0xA7: {
			int32 value = pullStackLong();
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			op_setBoxFlags_A7(ctx, argsLength, args, value);
		}
		return 0;
		/* createBoxMatrix */
		case 0xA8: {
			op_createBoxMatrix_A8(ctx);
		}
		return 0;
		/* wait */
		case 0xA9: {
			op_wait_A9(ctx);
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
					op_resourceRoutine3C_AA3C(ctx, num);
				}
				return 0;
				/* loadCostume */
				case 0x3D: {
					int16 num = pullStackWord();
					op_loadCostume_AA3D(ctx, num);
				}
				return 0;
				/* loadObject */
				case 0x3E: {
					int16 num = pullStackWord();
					op_loadObject_AA3E(ctx, num);
				}
				return 0;
				/* loadRoom */
				case 0x3F: {
					int16 num = pullStackWord();
					op_loadRoom_AA3F(ctx, num);
				}
				return 0;
				/* loadScript */
				case 0x40: {
					int16 num = pullStackWord();
					op_loadScript_AA40(ctx, num);
				}
				return 0;
				/* loadSound */
				case 0x41: {
					int16 num = pullStackWord();
					op_loadSound_AA41(ctx, num);
				}
				return 0;
				/* lockCostume */
				case 0x42: {
					int16 num = pullStackWord();
					op_lockCostume_AA42(ctx, num);
				}
				return 0;
				/* lockRoom */
				case 0x43: {
					int16 num = pullStackWord();
					op_lockRoom_AA43(ctx, num);
				}
				return 0;
				/* lockScript */
				case 0x44: {
					int16 num = pullStackWord();
					op_lockScript_AA44(ctx, num);
				}
				return 0;
				/* lockSound */
				case 0x45: {
					int16 num = pullStackWord();
					op_lockSound_AA45(ctx, num);
				}
				return 0;
				/* unlockCostume */
				case 0x46: {
					int16 num = pullStackWord();
					op_unlockCostume_AA46(ctx, num);
				}
				return 0;
				/* unlockRoom */
				case 0x47: {
					int16 num = pullStackWord();
					op_unlockRoom_AA47(ctx, num);
				}
				return 0;
				/* unlockScript */
				case 0x48: {
					int16 num = pullStackWord();
					op_unlockScript_AA48(ctx, num);
				}
				return 0;
				/* unlockSound */
				case 0x49: {
					int16 num = pullStackWord();
					op_unlockSound_AA49(ctx, num);
				}
				return 0;
				/* unloadCostume */
				case 0x4A: {
					int16 num = pullStackWord();
					op_unloadCostume_AA4A(ctx, num);
				}
				return 0;
				/* unloadRoom */
				case 0x4B: {
					int16 num = pullStackWord();
					op_unloadRoom_AA4B(ctx, num);
				}
				return 0;
				/* unloadScript */
				case 0x4C: {
					int16 num = pullStackWord();
					op_unloadScript_AA4C(ctx, num);
				}
				return 0;
				/* unloadSound */
				case 0x4D: {
					int16 num = pullStackWord();
					op_unloadSound_AA4D(ctx, num);
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
					op_setRoomRGB_AB52(ctx, r, g, b, index);
				}
				return 0;
				/* fadeRoom */
				case 0x57: {
					int32 param = pullStackLong();
					op_fadeRoom_AB57(ctx, param);
				}
				return 0;
				/* setRoomRGBIntensity */
				case 0x58: {
					int16 endColour = pullStackWord();
					int16 startColour = pullStackWord();
					int32 blueScale = pullStackLong();
					int32 greenScale = pullStackLong();
					int32 redScale = pullStackLong();
					op_setRoomRGBIntensity_AB58(ctx, redScale, greenScale, blueScale, startColour, endColour);
				}
				return 0;
				/* setRoomRGBTransform */
				case 0x59: {
					int32 time = pullStackLong();
					int16 end = pullStackWord();
					int16 start = pullStackWord();
					int32 resId = pullStackLong();
					op_setRoomRGBTransform_AB59(ctx, resId, start, end, time);
				}
				return 0;
				/* setRoomPalette */
				case 0x5C: {
					int16 paletteNum = pullStackWord();
					op_setRoomPalette_AB5C(ctx, paletteNum);
				}
				return 0;
				/* saveGame */
				case 0x5D: {
					op_saveGame_AB5D(ctx);
				}
				return 0;
				/* loadGame */
				case 0x5E: {
					byte saveSound = pullStackByte();
					op_loadGame_AB5E(ctx, saveSound);
				}
				return 0;
				/* setRoomSaturation */
				case 0x5F: {
					int16 endColour = pullStackWord();
					int16 startColour = pullStackWord();
					int32 lightScale = pullStackLong();
					int32 satScale = pullStackLong();
					int32 hueScale = pullStackLong();
					op_setRoomSaturation_AB5F(ctx, hueScale, satScale, lightScale, startColour, endColour);
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
					op_setActorCostume_AC64(ctx, costumeNum);
				}
				return 0;
				/* setActorWalkSpeed */
				case 0x65: {
					int16 y = pullStackWord();
					int16 x = pullStackWord();
					op_setActorWalkSpeed_AC65(ctx, x, y);
				}
				return 0;
				/* setActorAnimationDefault */
				case 0x67: {
					op_setActorAnimationDefault_AC67(ctx);
				}
				return 0;
				/* setActorAnimationInit */
				case 0x68: {
					byte frameNum = pullStackByte();
					op_setActorAnimationInit_AC68(ctx, frameNum);
				}
				return 0;
				/* setActorAnimationTalk */
				case 0x69: {
					byte endFrameNum = pullStackByte();
					byte startFrameNum = pullStackByte();
					op_setActorAnimationTalk_AC69(ctx, startFrameNum, endFrameNum);
				}
				return 0;
				/* setActorAnimationWalk */
				case 0x6A: {
					byte walkFrameNum = pullStackByte();
					op_setActorAnimationWalk_AC6A(ctx, walkFrameNum);
				}
				return 0;
				/* setActorAnimationStand */
				case 0x6B: {
					byte standFrameNum = pullStackByte();
					op_setActorAnimationStand_AC6B(ctx, standFrameNum);
				}
				return 0;
				/* setActorAnimationSpeed */
				case 0x6C: {
					byte animationSpeed = pullStackByte();
					op_setActorAnimationSpeed_AC6C(ctx, animationSpeed);
				}
				return 0;
				/* setActorDefault */
				case 0x6D: {
					op_setActorDefault_AC6D(ctx);
				}
				return 0;
				/* setActorElevation */
				case 0x6E: {
					int16 elevation = pullStackWord();
					op_setActorElevation_AC6E(ctx, elevation);
				}
				return 0;
				/* setActorPalette */
				case 0x6F: {
					int16 value = pullStackWord();
					byte index = pullStackByte();
					op_setActorPalette_AC6F(ctx, index, value);
				}
				return 0;
				/* setActorTalkColour */
				case 0x70: {
					byte colourIndex = pullStackByte();
					op_setActorTalkColour_AC70(ctx, colourIndex);
				}
				return 0;
				/* setActorName */
				case 0x71: {
					char* text = readText();
					op_setActorName_AC71(ctx, text);
				}
				return 0;
				/* setActorWidth */
				case 0x72: {
					int16 width = pullStackWord();
					op_setActorWidth_AC72(ctx, width);
				}
				return 0;
				/* setActorScale */
				case 0x73: {
					int16 size = pullStackWord();
					op_setActorScale_AC73(ctx, size);
				}
				return 0;
				/* setActorNeverZClip */
				case 0x74: {
					op_setActorNeverZClip_AC74(ctx);
				}
				return 0;
				/* setActorAlwaysZClip */
				case 0x75: {
					byte forceClip = pullStackByte();
					op_setActorAlwaysZClip_AC75(ctx, forceClip);
				}
				return 0;
				/* setActorIgnoreBoxes */
				case 0x76: {
					op_setActorIgnoreBoxes_AC76(ctx);
				}
				return 0;
				/* setActorFollowBoxes */
				case 0x77: {
					op_setActorFollowBoxes_AC77(ctx);
				}
				return 0;
				/* setActorSpecialDraw */
				case 0x78: {
					op_setActorSpecialDraw_AC78(ctx);
				}
				return 0;
				/* setActorTextOffset */
				case 0x79: {
					int16 y = pullStackWord();
					int16 x = pullStackWord();
					op_setActorTextOffset_AC79(ctx, x, y);
				}
				return 0;
				/* setActorVar */
				case 0x7B: {
					int32 value = pullStackLong();
					int32 name = pullStackLong();
					op_setActorVar_AC7B(ctx, name, value);
				}
				return 0;
				/* setActorIgnoreTurns */
				case 0x7C: {
					op_setActorIgnoreTurns_AC7C(ctx);
				}
				return 0;
				/* setActorFollowTurns */
				case 0x7D: {
					op_setActorFollowTurns_AC7D(ctx);
				}
				return 0;
				/* setActorNew */
				case 0x7E: {
					op_setActorNew_AC7E(ctx);
				}
				return 0;
				/* setActorDepth */
				case 0x7F: {
					int16 depth = pullStackWord();
					op_setActorDepth_AC7F(ctx, depth);
				}
				return 0;
				/* setActorStop */
				case 0x80: {
					op_setActorStop_AC80(ctx);
				}
				return 0;
				/* setActorDirection */
				case 0x81: {
					int16 direction = pullStackWord();
					op_setActorDirection_AC81(ctx, direction);
				}
				return 0;
				/* actorTurn */
				case 0x82: {
					int16 direction = pullStackWord();
					op_actorTurn_AC82(ctx, direction);
				}
				return 0;
				/* setActorWalkScript */
				case 0x83: {
					int16 scriptNum = pullStackWord();
					op_setActorWalkScript_AC83(ctx, scriptNum);
				}
				return 0;
				/* setActorTalkScript */
				case 0x84: {
					int16 scriptNum = pullStackWord();
					op_setActorTalkScript_AC84(ctx, scriptNum);
				}
				return 0;
				/* setActorWalkingFrozen */
				case 0x85: {
					op_setActorWalkingFrozen_AC85(ctx);
				}
				return 0;
				/* setActorWalkingResume */
				case 0x86: {
					op_setActorWalkingResume_AC86(ctx);
				}
				return 0;
				/* setActorTalkVolume */
				case 0x87: {
					int32 volume = pullStackLong();
					op_setActorTalkVolume_AC87(ctx, volume);
				}
				return 0;
				/* setActorTalkFrequency */
				case 0x88: {
					int32 frequency = pullStackLong();
					op_setActorTalkFrequency_AC88(ctx, frequency);
				}
				return 0;
				/* setActorTalkPan */
				case 0x89: {
					int32 pan = pullStackLong();
					op_setActorTalkPan_AC89(ctx, pan);
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
					op_setCameraPause_AD32(ctx);
				}
				return 0;
				/* setCameraResume */
				case 0x33: {
					op_setCameraResume_AD33(ctx);
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
					op_initVerb_AE96(ctx, verbNum);
				}
				return 0;
				/* newVerb */
				case 0x97: {
					int16 verbNum = pullStackWord();
					op_newVerb_AE97(ctx, verbNum);
				}
				return 0;
				/* deleteVerb */
				case 0x98: {
					int16 verbNum = pullStackWord();
					op_deleteVerb_AE98(ctx, verbNum);
				}
				return 0;
				/* setVerbName */
				case 0x99: {
					char* name = readText();
					op_setVerbName_AE99(ctx, name);
				}
				return 0;
				/* setVerbXY */
				case 0x9A: {
					int16 y = pullStackWord();
					int16 x = pullStackWord();
					op_setVerbXY_AE9A(ctx, x, y);
				}
				return 0;
				/* setVerbOn */
				case 0x9B: {
					op_setVerbOn_AE9B(ctx);
				}
				return 0;
				/* setVerbOff */
				case 0x9C: {
					op_setVerbOff_AE9C(ctx);
				}
				return 0;
				/* setVerbColour */
				case 0x9D: {
					byte colourIndex = pullStackByte();
					op_setVerbColour_AE9D(ctx, colourIndex);
				}
				return 0;
				/* setVerbHilightColour */
				case 0x9E: {
					byte colourIndex = pullStackByte();
					op_setVerbHilightColour_AE9E(ctx, colourIndex);
				}
				return 0;
				/* setVerbDimColour */
				case 0xA0: {
					byte colourIndex = pullStackByte();
					op_setVerbDimColour_AEA0(ctx, colourIndex);
				}
				return 0;
				/* setVerbDim */
				case 0xA1: {
					op_setVerbDim_AEA1(ctx);
				}
				return 0;
				/* setVerbKey */
				case 0xA2: {
					byte keyCode = pullStackByte();
					op_setVerbKey_AEA2(ctx, keyCode);
				}
				return 0;
				/* setVerbImage */
				case 0xA3: {
					byte roomNum = pullStackByte();
					int16 objectNum = pullStackWord();
					op_setVerbImage_AEA3(ctx, objectNum, roomNum);
				}
				return 0;
				/* setVerbNameStr */
				case 0xA4: {
					int32 textAddress = pullStackLong();
					op_setVerbNameStr_AEA4(ctx, textAddress);
				}
				return 0;
				/* setVerbCenter */
				case 0xA5: {
					op_setVerbCenter_AEA5(ctx);
				}
				return 0;
				/* setVerbCharSet */
				case 0xA6: {
					byte charSetNum = pullStackByte();
					op_setVerbCharSet_AEA6(ctx, charSetNum);
				}
				return 0;
				/* setVerbLinesSpacing */
				case 0xA7: {
					int16 lineSpacing = pullStackWord();
					op_setVerbLinesSpacing_AEA7(ctx, lineSpacing);
				}
				return 0;
		}
		return 1;
		/* startSound */
		case 0xAF: {
			int32 sound = pullStackLong();
			op_startSound_AF(ctx, sound);
		}
		return 0;
		/* startMusic */
		case 0xB0: {
			int32 sound = pullStackLong();
			op_startMusic_B0(ctx, sound);
		}
		return 0;
		/* stopSound */
		case 0xB1: {
			int32 sound = pullStackLong();
			op_stopSound_B1(ctx, sound);
		}
		return 0;
		/* soundKludge */
		case 0xB2: {
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			op_soundKludge_B2(ctx, argsLength, args);
		}
		return 0;
		case 0xB3: {
			consumeByte();
			switch(op2) {
				default:
					return 1;
				/* restartGame */
				case 0x9E: {
					op_restartGame_B39E(ctx);
				}
				return 0;
				/* pauseGame */
				case 0x9F: {
					op_pauseGame_B39F(ctx);
				}
				return 0;
				/* quitGame */
				case 0xA0: {
					op_quitGame_B3A0(ctx);
				}
				return 0;
		}
		return 1;
		/* saveRestoreVerbs */
		case 0xB4: {
			int32 c = pullStackLong();
			int32 b = pullStackLong();
			int32 a = pullStackLong();
			op_saveRestoreVerbs_B4(ctx, a, b, c);
		}
		return 0;
		/* setObjectName */
		case 0xB5: {
			char* name = readText();
			int32 obj = pullStackLong();
			op_setObjectName_B5(ctx, obj, name);
		}
		return 0;
		/* getDateTime */
		case 0xB6: {
			op_getDateTime_B6(ctx);
		}
		return 0;
		/* drawBox */
		case 0xB7: {
			int32 color = pullStackLong();
			int32 y2 = pullStackLong();
			int32 x2 = pullStackLong();
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			op_drawBox_B7(ctx, x, y, x2, y2, color);
		}
		return 0;
		/* startVideo */
		case 0xB9: {
			char* fileName = readText();
			op_startVideo_B9(ctx, fileName);
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
					op_lockObject_BA0B(ctx, argsLength, args);
				}
				return 0;
				/* unlockObject */
				case 0x0C: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_unlockObject_BA0C(ctx, argsLength, args);
				}
				return 0;
				/* remapCostumePalette */
				case 0x0D: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_remapCostumePalette_BA0D(ctx, argsLength, args);
				}
				return 0;
				/* remapCostumeInsert */
				case 0x0E: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_remapCostumeInsert_BA0E(ctx, argsLength, args);
				}
				return 0;
				/* setVideoFrameRate */
				case 0x0F: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_setVideoFrameRate_BA0F(ctx, argsLength, args);
				}
				return 0;
				/* setBoxScaleSlot */
				case 0x14: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_setBoxScaleSlot_BA14(ctx, argsLength, args);
				}
				return 0;
				/* setScaleSlot */
				case 0x15: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_setScaleSlot_BA15(ctx, argsLength, args);
				}
				return 0;
				/* setBannerColours */
				case 0x16: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_setBannerColours_BA16(ctx, argsLength, args);
				}
				return 0;
				/* setActorChoreLimbFrame */
				case 0x17: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_setActorChoreLimbFrame_BA17(ctx, argsLength, args);
				}
				return 0;
				/* clearTextQueue */
				case 0x18: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_clearTextQueue_BA18(ctx, argsLength, args);
				}
				return 0;
				/* saveGameReadName */
				case 0x19: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_saveGameReadName_BA19(ctx, argsLength, args);
				}
				return 0;
				/* saveGameWrite */
				case 0x1A: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_saveGameWrite_BA1A(ctx, argsLength, args);
				}
				return 0;
				/* saveGameRead */
				case 0x1B: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_saveGameRead_BA1B(ctx, argsLength, args);
				}
				return 0;
				/* saveGameScreenshot */
				case 0x1C: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_saveGameScreenshot_BA1C(ctx, argsLength, args);
				}
				return 0;
				/* setKeyScript */
				case 0x1D: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_setKeyScript_BA1D(ctx, argsLength, args);
				}
				return 0;
				/* killAllScriptsExceptCurrent */
				case 0x1E: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_killAllScriptsExceptCurrent_BA1E(ctx, argsLength, args);
				}
				return 0;
				/* stopAllVideo */
				case 0x1F: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_stopAllVideo_BA1F(ctx, argsLength, args);
				}
				return 0;
				/* writeRegistryValue */
				case 0x20: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_writeRegistryValue_BA20(ctx, argsLength, args);
				}
				return 0;
				/* setPaletteIntensity */
				case 0x21: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_setPaletteIntensity_BA21(ctx, argsLength, args);
				}
				return 0;
				/* queryQuit */
				case 0x22: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_queryQuit_BA22(ctx, argsLength, args);
				}
				return 0;
				/* buildPaletteShadow */
				case 0x6C: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_buildPaletteShadow_BA6C(ctx, argsLength, args);
				}
				return 0;
				/* setPaletteShadow */
				case 0x6D: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_setPaletteShadow_BA6D(ctx, argsLength, args);
				}
				return 0;
				/* blastShadowObject */
				case 0x6E: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_blastShadowObject_BA6E(ctx, argsLength, args);
				}
				return 0;
				/* superBlastObject */
				case 0x6F: {
					int32 argsLength = pullStack();
					int32* args = pullList(argsLength, 25);
					op_superBlastObject_BA6F(ctx, argsLength, args);
				}
				return 0;
		}
		return 1;
		/* dim2DimArray */
		case 0xC0: {
			int32 dim1 = pullStackLong();
			int32 dim2 = pullStackLong();
			op_dim2DimArray_C0(ctx, dim2, dim1);
		}
		return 0;
		/* distObjectPt */
		case 0xC6: {
			int32 c = pullStackLong();
			int32 b = pullStackLong();
			int32 a = pullStackLong();
			op_distObjectPt_C6(ctx, a, b, c);
		}
		return 0;
		/* startScriptQuick2 */
		case 0xC8: {
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			int32 script = pullStackLong();
			op_startScriptQuick2_C8(ctx, script, argsLength, args);
		}
		return 0;
		/* startObjectQuick */
		case 0xC9: {
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			byte entryPc = pullStackByte();
			int32 script = pullStackLong();
			op_startObjectQuick_C9(ctx, script, entryPc, argsLength, args);
		}
		return 0;
		/* pickOneOf */
		case 0xCA: {
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			int32 i = pullStackLong();
			op_pickOneOf_CA(ctx, i, argsLength, args);
		}
		return 0;
		/* pickOneOfDefault */
		case 0xCB: {
			int32 def = pullStackLong();
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			int32 i = pullStackLong();
			op_pickOneOfDefault_CB(ctx, i, argsLength, args, def);
		}
		return 0;
		/* isAnyOf */
		case 0xCD: {
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			int32 value = pullStackLong();
			op_isAnyOf_CD(ctx, value, argsLength, args);
		}
		return 0;
		/* getRandomNumber */
		case 0xCE: {
			int32 max = pullStackLong();
			op_getRandomNumber_CE(ctx, max);
		}
		return 0;
		/* getRandomNumberRange */
		case 0xCF: {
			int32 max = pullStackLong();
			int32 min = pullStackLong();
			op_getRandomNumberRange_CF(ctx, min, max);
		}
		return 0;
		/* ifClassOfIs */
		case 0xD0: {
			int32 argsLength = pullStack();
			int32* args = pullList(argsLength, 25);
			int32 obj = pullStackLong();
			op_ifClassOfIs_D0(ctx, obj, argsLength, args);
		}
		return 0;
		/* getState */
		case 0xD1: {
			int32 obj = pullStackLong();
			op_getState_D1(ctx, obj);
		}
		return 0;
		/* getOwner */
		case 0xD2: {
			int32 obj = pullStackLong();
			op_getOwner_D2(ctx, obj);
		}
		return 0;
		/* isScriptRunning */
		case 0xD3: {
			int32 script = pullStackLong();
			op_isScriptRunning_D3(ctx, script);
		}
		return 0;
		/* shuffle */
		case 0xD4: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_shuffle_D4(ctx, left, right);
		}
		return 0;
		/* isSoundRunning */
		case 0xD5: {
			int32 sound = pullStackLong();
			op_isSoundRunning_D5(ctx, sound);
		}
		return 0;
		/* abs */
		case 0xD6: {
			int32 value = pullStackLong();
			op_abs_D6(ctx, value);
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
					op_getWalkBoxAt_D873(ctx, args);
				}
				return 0;
				/* isPointInBox */
				case 0x74: {
					int32 args = pullStackLong();
					op_isPointInBox_D874(ctx, args);
				}
				return 0;
				/* getRGBSlot */
				case 0xCE: {
					int32 args = pullStackLong();
					op_getRGBSlot_D8CE(ctx, args);
				}
				return 0;
				/* getKeyState */
				case 0xD3: {
					int32 args = pullStackLong();
					op_getKeyState_D8D3(ctx, args);
				}
				return 0;
				/* getBox */
				case 0xD7: {
					int32 args = pullStackLong();
					op_getBox_D8D7(ctx, args);
				}
				return 0;
				/* findBlastObject */
				case 0xD8: {
					int32 args = pullStackLong();
					op_findBlastObject_D8D8(ctx, args);
				}
				return 0;
				/* actorHitTest */
				case 0xD9: {
					int32 args = pullStackLong();
					op_actorHitTest_D8D9(ctx, args);
				}
				return 0;
				/* setLipSyncWidth */
				case 0xDA: {
					int32 args = pullStackLong();
					op_setLipSyncWidth_D8DA(ctx, args);
				}
				return 0;
				/* setLipSyncHeight */
				case 0xDB: {
					int32 args = pullStackLong();
					op_setLipSyncHeight_D8DB(ctx, args);
				}
				return 0;
				/* setTalkAnimation */
				case 0xDC: {
					int32 args = pullStackLong();
					op_setTalkAnimation_D8DC(ctx, args);
				}
				return 0;
				/* getGroupSfxVol */
				case 0xDD: {
					int32 args = pullStackLong();
					op_getGroupSfxVol_D8DD(ctx, args);
				}
				return 0;
				/* getGroupVoiceVol */
				case 0xDE: {
					int32 args = pullStackLong();
					op_getGroupVoiceVol_D8DE(ctx, args);
				}
				return 0;
				/* getGroupMusicVol */
				case 0xDF: {
					int32 args = pullStackLong();
					op_getGroupMusicVol_D8DF(ctx, args);
				}
				return 0;
				/* readRegistryValue */
				case 0xE0: {
					int32 args = pullStackLong();
					op_readRegistryValue_D8E0(ctx, args);
				}
				return 0;
				/* imuseGetMusicPosition */
				case 0xE1: {
					int32 args = pullStackLong();
					op_imuseGetMusicPosition_D8E1(ctx, args);
				}
				return 0;
				/* imuseGetMusicLipSyncWidth */
				case 0xE2: {
					int32 args = pullStackLong();
					op_imuseGetMusicLipSyncWidth_D8E2(ctx, args);
				}
				return 0;
				/* imuseGetMusicLipSyncHeight */
				case 0xE3: {
					int32 args = pullStackLong();
					op_imuseGetMusicLipSyncHeight_D8E3(ctx, args);
				}
				return 0;
		}
		return 1;
		/* isActorInBox */
		case 0xD9: {
			int32 box = pullStackLong();
			int32 index = pullStackLong();
			op_isActorInBox_D9(ctx, index, box);
		}
		return 0;
		/* getVerbEntrypoint */
		case 0xDA: {
			int32 entryp = pullStackLong();
			int32 verb = pullStackLong();
			op_getVerbEntrypoint_DA(ctx, verb, entryp);
		}
		return 0;
		/* getActorFromXY */
		case 0xDB: {
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			op_getActorFromXY_DB(ctx, x, y);
		}
		return 0;
		/* findObject */
		case 0xDC: {
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			op_findObject_DC(ctx, x, y);
		}
		return 0;
		/* getVerbFromXY */
		case 0xDD: {
			int32 y = pullStackLong();
			int32 x = pullStackLong();
			op_getVerbFromXY_DD(ctx, x, y);
		}
		return 0;
		/* findInventory */
		case 0xDF: {
			int32 index = pullStackLong();
			int32 owner = pullStackLong();
			op_findInventory_DF(ctx, owner, index);
		}
		return 0;
		/* getInventoryCount */
		case 0xE0: {
			int32 owner = pullStackLong();
			op_getInventoryCount_E0(ctx, owner);
		}
		return 0;
		/* getAnimateVariable */
		case 0xE1: {
			int32 variable = pullStackLong();
			int32 index = pullStackLong();
			op_getAnimateVariable_E1(ctx, index, variable);
		}
		return 0;
		/* getActorRoom */
		case 0xE2: {
			int32 index = pullStackLong();
			op_getActorRoom_E2(ctx, index);
		}
		return 0;
		/* getActorWalkBox */
		case 0xE3: {
			int32 index = pullStackLong();
			op_getActorWalkBox_E3(ctx, index);
		}
		return 0;
		/* getActorMoving */
		case 0xE4: {
			int32 index = pullStackLong();
			op_getActorMoving_E4(ctx, index);
		}
		return 0;
		/* getActorCostume */
		case 0xE5: {
			int32 index = pullStackLong();
			op_getActorCostume_E5(ctx, index);
		}
		return 0;
		/* getActorScaleX */
		case 0xE6: {
			int32 index = pullStackLong();
			op_getActorScaleX_E6(ctx, index);
		}
		return 0;
		/* getActorLayer */
		case 0xE7: {
			int32 index = pullStackLong();
			op_getActorLayer_E7(ctx, index);
		}
		return 0;
		/* getActorElevation */
		case 0xE8: {
			int32 index = pullStackLong();
			op_getActorElevation_E8(ctx, index);
		}
		return 0;
		/* getActorWidth */
		case 0xE9: {
			int32 index = pullStackLong();
			op_getActorWidth_E9(ctx, index);
		}
		return 0;
		/* getObjectNewDir */
		case 0xEA: {
			int32 index = pullStackLong();
			op_getObjectNewDir_EA(ctx, index);
		}
		return 0;
		/* getObjectX */
		case 0xEB: {
			int32 index = pullStackLong();
			op_getObjectX_EB(ctx, index);
		}
		return 0;
		/* getObjectY */
		case 0xEC: {
			int32 index = pullStackLong();
			op_getObjectY_EC(ctx, index);
		}
		return 0;
		/* getActorChore */
		case 0xED: {
			int16 actorNum = pullStackWord();
			op_getActorChore_ED(ctx, actorNum);
		}
		return 0;
		/* distObjectObject */
		case 0xEE: {
			int32 right = pullStackLong();
			int32 left = pullStackLong();
			op_distObjectObject_EE(ctx, left, right);
		}
		return 0;
		/* distObjectPtPt */
		case 0xEF: {
			int32 d = pullStackLong();
			int32 c = pullStackLong();
			int32 b = pullStackLong();
			int32 a = pullStackLong();
			op_distObjectPtPt_EF(ctx, a, b, c, d);
		}
		return 0;
		/* getObjectImageX */
		case 0xF0: {
			int16 objectNum = pullStackWord();
			op_getObjectImageX_F0(ctx, objectNum);
		}
		return 0;
		/* getObjectImageY */
		case 0xF1: {
			int16 objectNum = pullStackWord();
			op_getObjectImageY_F1(ctx, objectNum);
		}
		return 0;
		/* getObjectImageWidth */
		case 0xF2: {
			int16 objectNum = pullStackWord();
			op_getObjectImageWidth_F2(ctx, objectNum);
		}
		return 0;
		/* getObjectImageHeight */
		case 0xF3: {
			int16 objectNum = pullStackWord();
			op_getObjectImageHeight_F3(ctx, objectNum);
		}
		return 0;
		/* getStringWidth */
		case 0xF6: {
			int16 charsetNum = pullStackWord();
			char* text = readText();
			op_getStringWidth_F6(ctx, text, charsetNum);
		}
		return 0;
		/* getActorZPlane */
		case 0xF7: {
			int16 actorNum = pullStackWord();
			op_getActorZPlane_F7(ctx, actorNum);
		}
		return 0;
	};
	return 1;
}
