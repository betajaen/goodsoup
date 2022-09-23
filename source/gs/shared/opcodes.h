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

#ifndef GS_OPCODES_H
#define GS_OPCODES_H

typedef enum gs_Opcodes {
	OP_00 = 0x00,
	OP_pushWord = 0x01,
	OP_pushWordVar = 0x02,
	OP_wordArrayRead = 0x03,
	OP_wordArrayIndexedRead = 0x04,
	OP_dup = 0x05,
	OP_pop = 0x06,
	OP_not = 0x07,
	OP_eq = 0x08,
	OP_neq = 0x09,
	OP_gt = 0x0a,
	OP_lt = 0x0b,
	OP_le = 0x0c,
	OP_ge = 0x0d,
	OP_add = 0x0e,
	OP_sub = 0x0f,
	OP_mul = 0x10,
	OP_div = 0x11,
	OP_land = 0x12,
	OP_lor = 0x13,
	OP_band = 0x14,
	OP_bor = 0x15,
	OP_mod = 0x16,
	OP_17 = 0x17,
	OP_18 = 0x18,
	OP_19 = 0x19,
	OP_1a = 0x1a,
	OP_1b = 0x1b,
	OP_1c = 0x1c,
	OP_1d = 0x1d,
	OP_1e = 0x1e,
	OP_1f = 0x1f,
	OP_20 = 0x20,
	OP_21 = 0x21,
	OP_22 = 0x22,
	OP_23 = 0x23,
	OP_24 = 0x24,
	OP_25 = 0x25,
	OP_26 = 0x26,
	OP_27 = 0x27,
	OP_28 = 0x28,
	OP_29 = 0x29,
	OP_2a = 0x2a,
	OP_2b = 0x2b,
	OP_2c = 0x2c,
	OP_2d = 0x2d,
	OP_2e = 0x2e,
	OP_2f = 0x2f,
	OP_30 = 0x30,
	OP_31 = 0x31,
	OP_32 = 0x32,
	OP_33 = 0x33,
	OP_34 = 0x34,
	OP_35 = 0x35,
	OP_36 = 0x36,
	OP_37 = 0x37,
	OP_38 = 0x38,
	OP_39 = 0x39,
	OP_3a = 0x3a,
	OP_3b = 0x3b,
	OP_3c = 0x3c,
	OP_3d = 0x3d,
	OP_3e = 0x3e,
	OP_3f = 0x3f,
	OP_40 = 0x40,
	OP_41 = 0x41,
	OP_42 = 0x42,
	OP_43 = 0x43,
	OP_44 = 0x44,
	OP_45 = 0x45,
	OP_46 = 0x46,
	OP_47 = 0x47,
	OP_48 = 0x48,
	OP_49 = 0x49,
	OP_4a = 0x4a,
	OP_4b = 0x4b,
	OP_4c = 0x4c,
	OP_4d = 0x4d,
	OP_4e = 0x4e,
	OP_4f = 0x4f,
	OP_50 = 0x50,
	OP_51 = 0x51,
	OP_52 = 0x52,
	OP_53 = 0x53,
	OP_54 = 0x54,
	OP_55 = 0x55,
	OP_56 = 0x56,
	OP_57 = 0x57,
	OP_58 = 0x58,
	OP_59 = 0x59,
	OP_5a = 0x5a,
	OP_5b = 0x5b,
	OP_5c = 0x5c,
	OP_5d = 0x5d,
	OP_5e = 0x5e,
	OP_5f = 0x5f,
	OP_60 = 0x60,
	OP_61 = 0x61,
	OP_62 = 0x62,
	OP_63 = 0x63,
	OP_if = 0x64,
	OP_ifNot = 0x65,
	OP_jump = 0x66,
	OP_breakHere = 0x67,
	OP_delayFrames = 0x68,
	OP_wait = 0x69,
	OP_delay = 0x6a,
	OP_delaySeconds = 0x6b,
	OP_delayMinutes = 0x6c,
	OP_writeWordVar = 0x6d,
	OP_wordVarInc = 0x6e,
	OP_wordVarDec = 0x6f,
	OP_dimArray = 0x70,
	OP_wordArrayWrite = 0x71,
	OP_wordArrayInc = 0x72,
	OP_wordArrayDec = 0x73,
	OP_dim2dimArray = 0x74,
	OP_wordArrayIndexedWrite = 0x75,
	OP_arrayOps = 0x76,
	OP_77 = 0x77,
	OP_78 = 0x78,
	OP_startScript = 0x79,
	OP_startScriptQuick = 0x7a,
	OP_stopObjectCode = 0x7b,
	OP_stopScript = 0x7c,
	OP_jumpToScript = 0x7d,
	OP_dummy = 0x7e,
	OP_startObject = 0x7f,
	OP_stopObjectScript = 0x80,
	OP_cutscene = 0x81,
	OP_endCutscene = 0x82,
	OP_freezeUnfreeze = 0x83,
	OP_beginOverride = 0x84,
	OP_endOverride = 0x85,
	OP_stopSentence = 0x86,
	OP_87 = 0x87,
	OP_88 = 0x88,
	OP_setClass = 0x89,
	OP_setState = 0x8a,
	OP_setOwner = 0x8b,
	OP_panCameraTo = 0x8c,
	OP_actorFollowCamera = 0x8d,
	OP_setCameraAt = 0x8e,
	OP_printActor = 0x8f,
	OP_printEgo = 0x90,
	OP_talkActor = 0x91,
	OP_talkEgo = 0x92,
	OP_printLine = 0x93,
	OP_printText = 0x94,
	OP_printDebug = 0x95,
	OP_printSystem = 0x96,
	OP_blastText = 0x97,
	OP_drawObject = 0x98,
	OP_99 = 0x99,
	OP_9a = 0x9a,
	OP_9b = 0x9b,
	OP_cursorCommand = 0x9c,
	OP_loadRoom = 0x9d,
	OP_loadRoomWithEgo = 0x9e,
	OP_walkActorToObj = 0x9f,
	OP_walkActorTo = 0xa0,
	OP_putActorAtXY = 0xa1,
	OP_putActorAtObject = 0xa2,
	OP_faceActor = 0xa3,
	OP_animateActor = 0xa4,
	OP_doSentence = 0xa5,
	OP_pickupObject = 0xa6,
	OP_setBoxFlags = 0xa7,
	OP_createBoxMatrix = 0xa8,
	OP_a9 = 0xa9,
	OP_resourceRoutines = 0xaa,
	OP_roomOps = 0xab,
	OP_actorOps = 0xac,
	OP_cameraOps = 0xad,
	OP_verbOps = 0xae,
	OP_startSound = 0xaf,
	OP_startMusic = 0xb0,
	OP_stopSound = 0xb1,
	OP_soundKludge = 0xb2,
	OP_systemOps = 0xb3,
	OP_saveRestoreVerbs = 0xb4,
	OP_setObjectName = 0xb5,
	OP_getDateTime = 0xb6,
	OP_drawBox = 0xb7,
	OP_b8 = 0xb8,
	OP_startVideo = 0xb9,
	OP_kernelSetFunctions = 0xba,
	OP_bb = 0xbb,
	OP_bc = 0xbc,
	OP_bd = 0xbd,
	OP_be = 0xbe,
	OP_bf = 0xbf,
	OP_c0 = 0xc0,
	OP_c1 = 0xc1,
	OP_c2 = 0xc2,
	OP_c3 = 0xc3,
	OP_c4 = 0xc4,
	OP_c5 = 0xc5,
	OP_c6 = 0xc6,
	OP_c7 = 0xc7,
	OP_startScriptQuick2 = 0xc8,
	OP_startObjectQuick = 0xc9,
	OP_pickOneOf = 0xca,
	OP_pickOneOfDefault = 0xcb,
	OP_cc = 0xcc,
	OP_isAnyOf = 0xcd,
	OP_getRandomNumber = 0xce,
	OP_getRandomNumberRange = 0xcf,
	OP_ifClassOfIs = 0xd0,
	OP_getState = 0xd1,
	OP_getOwner = 0xd2,
	OP_isScriptRunning = 0xd3,
	OP_d4 = 0xd4,
	OP_isSoundRunning = 0xd5,
	OP_abs = 0xd6,
	OP_d7 = 0xd7,
	OP_kernelGetFunctions = 0xd8,
	OP_isActorInBox = 0xd9,
	OP_getVerbEntrypoint = 0xda,
	OP_getActorFromXY = 0xdb,
	OP_findObjectFromXY = 0xdc,
	OP_getVerbFromXY = 0xdd,
	OP_de = 0xde,
	OP_findInventory = 0xdf,
	OP_getInventoryCount = 0xe0,
	OP_getAnimateVariable = 0xe1,
	OP_getActorRoom = 0xe2,
	OP_getActorWalkBox = 0xe3,
	OP_getActorMoving = 0xe4,
	OP_getActorCostume = 0xe5,
	OP_getActorScaleX = 0xe6,
	OP_getActorLayer = 0xe7,
	OP_getActorElevation = 0xe8,
	OP_getActorWidth = 0xe9,
	OP_getObjectNewDir = 0xea,
	OP_getObjectX = 0xeb,
	OP_getObjectY = 0xec,
	OP_getActorChore = 0xed,
	OP_distObjectObject = 0xee,
	OP_distPtPt = 0xef,
	OP_getObjectImageX = 0xf0,
	OP_getObjectImageY = 0xf1,
	OP_getObjectImageWidth = 0xf2,
	OP_getObjectImageHeight = 0xf3,
	OP_f4 = 0xf4,
	OP_f5 = 0xf5,
	OP_getStringWidth = 0xf6,
	OP_getActorZPlane = 0xf7,
	OP_f8 = 0xf8,
	OP_f9 = 0xf9,
	OP_fa = 0xfa,
	OP_fb = 0xfb,
	OP_fc = 0xfc,
	OP_fd = 0xfd,
	OP_fe = 0xfe,
	OP_ff = 0xff
} gs_Opcodes;

typedef enum gs_SystemOps {
	SystemOps_Restart = 158,
	SystemOps_Pause = 159,
	SystemOps_Quit = 160,
	SystemOps_AbortQuitStop = 161,
	SystemOps_Noop = 162
} gs_SystemOps;
	
typedef enum gs_ActorOp {
	ActorOp_SetCostume = 0x64,
	ActorOp_SetWalkSpeed = 0x65,
	ActorOp_SetAnimationDefault = 0x67,
	ActorOp_InitAnimation = 0x68,
	ActorOp_SetAnimationTalk = 0x69,
	ActorOp_SetAnimationWalk = 0x6A,
	ActorOp_SetAnimationStand = 0x6B,
	ActorOp_SetAnimationSpeed = 0x6C,
	ActorOp_Default = 0x6D,
	ActorOp_SetElevation = 0x6E,
	ActorOp_SetPalette = 0x6F,
	ActorOp_SetTalkColour = 0x70,
	ActorOp_SetActorName = 0x71,
	ActorOp_SetActorWidth = 0x72,
	ActorOp_SetActorScale = 0x73,
	ActorOp_SetNeverZClip = 0x74,
	ActorOP_SetAlwaysZClip = 0x75,
	ActorOp_SetIgnoreBoxes = 0x76,
	ActorOp_SetFollowBoxes = 0x77,
	ActorOp_SetSpecialDraw = 0x78,
	ActorOp_SetTextOffset = 0x79,
	ActorOp_Init = 0x7A,
	ActorOp_SetActorVariable = 0x7B,
	ActorOp_SetIgnoreTurnsOn = 0x7C,
	ActorOp_SetIgnoreTurnsOff= 0x7D,
	ActorOp_ActorNew = 0x7E,
	ActorOp_SetActorZ = 0x7F,
	ActorOp_ActorStop = 0x80,
	ActorOp_SetAngle = 0x81,
	ActorOp_TurnAngle = 0x82,
	ActorOp_SetWalkScript = 0x83,
	ActorOp_SetTalkScript = 0x84,
	ActorOp_WalkPause = 0x85,
	ActorOp_WalkResume = 0x86,
	ActorOp_SetTalkVolume = 0x87,
	ActorOp_SetTalkFrequency = 0x88,
	ActorOp_SetActorPan = 0x89
} gs_ActorOp;

typedef enum gs_ArrayOp
{
	ArrayOps_AssignString = 0x14,
	ArrayOps_AssignScummVarList = 0x15,
	ArrayOps_Assign2DimList = 0x16
} gs_ArrayOp;
	
typedef enum gs_CursorCommandOp {
	CursorCommandOp_CursorOn = 0xDC,
	CursorCommandOp_CursorOff = 0xDD,
	CursorCommandOp_SoftCursorOn = 0xDE,
	CursorCommandOp_SoftCursorOff = 0xDF,
	CursorCommandOp_UserPutOn = 0xE0,
	CursorCommandOp_UserPutOff = 0xE1,
	CursorCommandOp_SoftUserPutOn = 0xE2,
	CursorCommandOp_SoftUserPutOff = 0xE3,
	CursorCommandOp_CursorImage = 0xE4,
	CursorCommandOp_HotSpot = 0xE5,
	CursorCommandOp_Transparency = 0xE6,
	CursorCommandOp_CharsetSet = 0xE7,
	CursorCommandOp_CharsetColour = 0xE8,
	CursorCommandOp_CursorPut = 0xE9
} gs_CursorCommandOp;

typedef enum gs_DimArrayOp {
	DimArrayOp_NewInt = 0xA,
	DimArrayOp_NewString = 0xB,
	DimArrayOp_Delete = 0xC
} gs_DimArrayOp;

typedef enum Dim2DimOp {
	Dim2DimOp_Int = 0xA,
	Dim2DimOp_String = 0xB,
	Dim2DimOp_Delete = 0xC
} gs_Dim2DimOp;

typedef enum gs_KernelSetOp {
	KernelSetOp_LockObject = 0xB,
	KernelSetOp_UnlockObject = 0xC,
	KernelSetOp_RemapCostume = 0xD,
	KernelSetOp_RemapCostumeInert = 0xE,
	KernelSetOp_Unused_0xF = 0xF,
	KernelSetOp_SetBoxScaleSlot = 0x14,
	KernelSetOp_SetScaleSlot = 0x15,
	KernelSetOp_SetBannerColours = 0x16,
	KernelSetOp_SetActorChoreLimbFrame = 0x17,
	KernelSetOp_ClearTextQueue = 0x18,
	KernelSetOp_Unused_0x1A = 0x1A,
	KernelSetOp_Unused_0x1B = 0x1B,
	KernelSetOp_Unused_0x1C = 0x1C,
	KernelSetOp_Unused_0x1D = 0x1D,
	KernelSetOp_KillAllScriptsExceptCurrent = 0x1E,
	KernelSetOp_StopAllVideo = 0x1F,
	KernelSetOp_WriteRegistryValue = 0x20,
	KernelSetOp_QueryQuit = 0x22,
	KernelSetOp_BuildShadowPalette = 0x6C,
	KernelSetOp_SetShadowPalette = 0x6D,
	KernelSetOp_BlastShadowObject = 0x76,
	KernelSetOp_SuperBlastObject = 0x77
} gs_KernelSetOp;

typedef enum gs_KernelGetOp {
	KernelGetOp_GetRGBSlot = 0xCE,
	KernelGetOp_GetKeyState = 0xD3,
	KernelGetOp_CheckXYInBoxBounds = 0xD7,
	KernelGetOp_FindBlastObject = 0xD8,
	KernelGetOp_TestActorHit = 0xD9,
	KernelGetOp_GetLipSyncWidth = 0xDA,
	KernelGetOp_GetLipSyncHeight = 0xDB,
	KernelGetOp_GetTalkAnimation = 0xDC,
	KernelGetOp_GetGroupSfxVolume = 0xDD,
	KernelGetOp_GetGroupVoiceVolume = 0xDE,
	KernelGetOp_GetGroupMusicVolume = 0xDF,
	KernelGetOp_ReadRegistryValue = 0xE0,
	KernelGetOp_ImGetMusicPosition = 0xE1,
	KernelGetOp_MusicLipGetSyncWidth = 0xE2,
	KernelGetOp_MusicLipGetSyncHeight = 0xE3,
	KernelGetOp_GetWalkBoxAt = 0x73,
	KernelGetOp_IsPointInBox = 0x74
} gs_KernelGetOp;

typedef enum gs_ParseStringOp {
    ParseStringOp_Load = 0xC8,
    ParseStringOp_Save = 0xC9,
    ParseStringOp_SetPos = 0xCA,
    ParseStringOp_SetColour = 0xCB,
    ParseStringOp_SetCenter = 0xCC,
    ParseStringOp_SetCharset = 0xCD,
    ParseStringOp_SetLeft = 0xCE,
    ParseStringOp_SetOverhead = 0xCF,
    ParseStringOp_SetMumble = 0xD0,
    ParseStringOp_PrintString = 0xD1,
    ParseStringOp_SetWrap = 0xD2
} gs_ParseStringOp ;

typedef enum gs_RoomOp {
	RoomOp_SetColour = 0x52,
	RoomOp_FadePalette = 0x57,
	RoomOp_DarkenPalette = 0x58,
	RoomOp_PaletteManipulate = 0x59,
	RoomOp_SetPalette = 0x5C,
	RoomOp_SaveGame = 0x5D,
	RoomOp_LoadGame = 0x5E,
	RoomOp_DesaturatePalette = 0x5F
} gs_RoomOp;


typedef enum gs_ResourceRoutineOp {
	ResourceRoutineOp_Dummy = 0x3C,
	ResourceRoutineOp_LoadCostume = 0x3D,
	ResourceRoutineOp_LoadObject = 0x3E,
	ResourceRoutineOp_LoadRoom = 0x3F,
	ResourceRoutineOp_LoadScript = 0x40,
	ResourceRoutineOp_LoadSound = 0x41,
	ResourceRoutineOp_LockCostume = 0x42,
	ResourceRoutineOp_LockRoom = 0x43,
	ResourceRoutineOp_LockScript = 0x44,
	ResourceRoutineOp_LockSound = 0x45,
	ResourceRoutineOp_UnlockCostume = 0x46,
	ResourceRoutineOp_UnlockRoom = 0x47,
	ResourceRoutineOp_UnlockScript = 0x48,
	ResourceRoutineOp_UnlockSound = 0x49,
	ResourceRoutineOp_SetResourceCounterCostume = 0x4A,
	ResourceRoutineOp_SetResourceCounterRoom = 0x4B,
	ResourceRoutineOp_SetResourceCounterScript = 0x4C,
	ResourceRoutineOp_SetResourceCounterSound = 0x4D
} gs_ResourceRoutineOp;

typedef enum gs_VerbOp {
	VerbOp_GetOrNew = 0x96,
	VerbOp_New = 0x97,
	VerbOp_Delete = 0x98,
	VerbOp_SetName = 0x99,
	VerbOp_SetPosition = 0x9A,
	VerbOp_Enable = 0x9B,
	VerbOp_Disable = 0x9C,
	VerbOp_SetColour = 0x9D,
	VerbOp_SetHilightColour = 0x9E,
	VerbOp_SetDimmedColour = 0xA0,
	VerbOp_Dim = 0xA1,
	VerbOp_SetKey = 0xA2,
	VerbOp_SetImage = 0xA3,
	VerbOp_SetNameString = 0xA4,
	VerbOp_Centre = 0xA5,
	VerbOp_SetCharSet = 0xA6,
	VerbOp_SetLineSpacing = 0xA7
} gs_VerbOp;

typedef enum gs_WaitOp {
	WaitOp_WaitActor = 0x1E,
	WaitOp_WaitMessage = 0x1F,
	WaitOp_WaitCamera = 0x20,
	WaitOp_WaitSentence = 0x21,
	WaitOp_WaitAnimation = 0x22,
	WaitOp_WaitTurn = 0x23
} gs_WaitOp;

#endif
