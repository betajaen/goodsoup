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

#define GS_FILE_NAME "main"

#include "types.h"
#include "memory.h"

#include "debug.h"
#include "globals.h"
#include "vm/vm.h"
#include "vm/array.h"
#include "vm/vars.h"
#include "vm/debugger.h"
#include "video/video.h"
#include "index.h"
#include "resource.h"
#include "profile.h"
#include "screen.h"
#include "functions.h"
#include "object.h"
#include "script.h"
#include "verb.h"
#include "actor.h"
#include "input.h"
#include "table.h"
#include "image.h"
#include "costume.h"
#include "draw.h"

extern const char GOODSOUP_VERSION_STR[] = "$VER: goodsoup 0.5 (" __AMIGADATE__ ")";

#if GS_TEST == 1
namespace test
{
	int run();
}
#endif

namespace gs
{

	uint8 NEXT_GAME_STATE = GSK_None;
	int32 GAME_STATE_PARAM = 0;
	uint8 GAME_STATE = GSK_None;
	int32 NEXT_GAME_STATE_PARAM = 0;
	bool SCREEN_EVENT_HANDLER_SHOULD_QUIT = false;
	bool PAUSED = false;
	int32 SENTENCE_NUM = 0;
	bool SHOW_OSD = true;
	uint32 FRAME_NUM = 0;
	int32 MOUSE_X;
	int32 MOUSE_Y;
	int32 MOUSE_LMB_EVENT;
	int32 MOUSE_RMB_EVENT;
	int32 MOUSE_LMB_STATE;
	int32 MOUSE_RMB_STATE;
	uint8 KEY_EVENT;
	bool FAST_MODE;

	void cleanup() {
		closeTables();
		deleteObject(VIDEO);
		deleteObject(COSTUMES);
		deleteObject(IMAGES);
		deleteObject(ACTORS);
		deleteObject(VERBS);
		deleteObject(SCRIPTS);
		deleteObject(ARRAYS);
		deleteObject(OBJECTS);
		deleteObject(VM);
		deleteObject(INTS);
		deleteObject(BOOLS);
		deleteObject(INDEX);
		deleteObject(RESOURCES);
        vmDebugStop();
	}

	int main(int param) {

        if (vmDebugStart() == false) {
            error(GS_THIS, "Cannot Start VMD Debugger!");
            cleanup();
            return 1;
        }

#if GS_FRAME_DELAY == 1
		FAST_MODE = 0;
#else
		FAST_MODE = 1;
#endif
		debug_write_str(GOODSOUP_VERSION_STR);
		debug_write_char('\n');

#if GS_TEST == 1
		return test::run();
#else

		info(GS_THIS, "%s\n", &GOODSOUP_VERSION_STR[6]);

		if (openScreen() == false) {
			error(GS_THIS, "Could not open screen!");
			cleanup();
			return 1;
		}

		ARRAYS = newObject<VmArrayAllocator>();
		INDEX = newObject<Index>();
		
		INTS = newObject<VmIntVars>();
		BOOLS = newObject<VmBoolVars>();
		OBJECTS = newObject<ObjectState>();
		SCRIPTS = newObject<ScriptState>();
		VERBS = newObject<VerbState>();
		ACTORS = newObject<ActorState>();
		IMAGES = newObject<ImageState>();
		COSTUMES = newObject<CostumeState>();
		VIDEO = newObject<VideoContext>();

		if (INDEX->readFromFile(GS_GAME_PATH GS_INDEX_FILENAME) == false) {
			cleanup();
			return 1;
		}

		if (openTables() == false) {
			cleanup();
			return 1;
		}

		RESOURCES = newObject<Resources>();
		RESOURCES->open();
		VM = newObject<VirtualMachine>();
		VM->reset();

		NEXT_GAME_STATE = GSK_Boot;
		NEXT_GAME_STATE_PARAM = 1;
		GAME_STATE = GSK_None;
		SCREEN_EVENT_HANDLER_SHOULD_QUIT = false;

		screenEventHandler();

		cleanup();
		closeScreen();

		return 0;
#endif
	}

	uint8 col = 0;

	bool DEBUG_STOP_AFTER_FRAMES = false;
	int32 DEBUG_STOP_AFTER_FRAMES_COUNT = 0;
	int test = 0;

	void roomFrameHandler(bool fullRedraw) {

#if defined(GS_VM_DEBUG) && GS_VM_DEBUG==1
        vmDebugRemark("frame");
#endif

		if (DEBUG_STOP_AFTER_FRAMES) {
			DEBUG_STOP_AFTER_FRAMES_COUNT--;
			if (DEBUG_STOP_AFTER_FRAMES_COUNT <= 0) {
				setNextGameState(GSK_Quit, 0);
				return;
			}
		}

		FRAME_NUM++;

		if (MOUSE_LMB_EVENT == 1) {
			MOUSE_LMB_STATE = 1;
			MOUSE_LMB_EVENT = 0;

			INTS->leftbtnDown = 1;

		}
		else if (MOUSE_LMB_EVENT == -1) {
			MOUSE_LMB_STATE = 0;
			MOUSE_LMB_EVENT = 0;

			INTS->leftbtnDown = 0;
		}
		else {
			INTS->leftbtnDown = 0;
		}

		if (KEY_EVENT == KE_DebugDumpStack) {
			VM->dumpStack();
		}
		else if (KEY_EVENT == KE_DebugDumpVerbs) {
			VERBS->dumpVerbs();
		}

		KEY_EVENT = 0;

		INTS->mouseX = MOUSE_X;
		INTS->mouseY = MOUSE_Y;
		INTS->virtMouseX = MOUSE_X;
		INTS->virtMouseY = MOUSE_Y;
		INTS->leftbtnHold = MOUSE_LMB_STATE;

		screenDrawBox(col++, 10, 10, 10, 10);

		DRAW_FLAGS = 0;

		VM->processScriptDelays(1);

#if defined(GS_VM_DEBUG) && GS_VM_DEBUG==1
        vmDebugRemark("scripts");
#endif
		VM->runAllScripts();

#if defined(GS_VM_DEBUG) && GS_VM_DEBUG==1
        vmDebugRemark("input");
#endif

		if (INTS->leftbtnDown == 1 && INTS->room == 87 && test == 0) {
			test = 1;
			VM->runInputScript(2005, 2, 0, 1);
		}


		if (SHOW_OSD) {
			runOSD();
		}
		
#if defined(GS_ONE_FRAME) && GS_ONE_FRAME == 1
		warn(GS_THIS, "One Frame Only");
		QUIT_NOW = true;
#endif
	}

	void videoFrameHander(bool start, int32 videoId) {

		if (start) {
			VIDEO->loadVideo(videoId);
		}
		else {
			VIDEO->playVideoFrame();

			if (VIDEO->getVideoStateKind() == VSK_Stopped) {
				VIDEO->unloadVideo();
				setNextGameState(GSK_Room, 0);
			}
		}

	}

	void frameHandler() {

		bool newState = false;

		if (NEXT_GAME_STATE != GSK_None) {
			GAME_STATE = NEXT_GAME_STATE;
			GAME_STATE_PARAM = NEXT_GAME_STATE_PARAM;
			NEXT_GAME_STATE = 0;
			NEXT_GAME_STATE_PARAM = 0;
			newState = true;
		}

		switch(GAME_STATE) {
			case GSK_Boot: {
#if defined(GS_VM_DEBUG) && GS_VM_DEBUG==1
				vmDebugRemark("Boot");
#endif
				VM->runScript(GAME_STATE_PARAM, false, false);

				NEXT_GAME_STATE = GSK_Room;
				NEXT_GAME_STATE_PARAM = 0;
			}
			break;
			case GSK_Room: {
#if defined(GS_VM_DEBUG) && GS_VM_DEBUG == 1
				if (newState) {
					vmDebugRemark("First Frame");
				}
				else {
					vmDebugRemark("Frame");
				}
#endif

				roomFrameHandler(newState);
			}
			break;
			case GSK_Video: {
				FAST_MODE = 0;
				videoFrameHander(newState, GAME_STATE_PARAM);
			}
			break;
			case GSK_Quit: {
				if (newState) {
					SCREEN_EVENT_HANDLER_SHOULD_QUIT = true;
				}
			}
			break;
		}

	}

}

namespace gs
{
	void abort_quit_stop() {
		using namespace gs;

		setNextGameState(GSK_Quit, 0);

		if (VM) {
			VM->abort();
		}
	}
}