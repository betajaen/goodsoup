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
#include "vm.h"
#include "vm_array.h"
#include "vm_vars.h"
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
#include "vm_debugger.h"

extern const char GOODSOUP_VERSION_STR[] = "$VER: goodsoup 0.5 (" __AMIGADATE__ ")";

#if GS_TEST == 1
namespace test
{
	int run();
}
#endif

namespace gs
{

	bool QUIT_NOW = false;
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

	void cleanup() {
		deleteObject(ACTORS);
		deleteObject(VERBS);
		deleteObject(SCRIPTS);
		deleteObject(OBJECTS);
		deleteObject(VM);
		deleteObject(INTS);
		deleteObject(BOOLS);
		deleteObject(LOCALS);
		deleteObject(ARRAYS);
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

		debug_write_str(GOODSOUP_VERSION_STR);
		debug_write_char('\n');

#if GS_TEST == 1
		return test::run();
#else


		info(GS_THIS, "%s\n", &GOODSOUP_VERSION_STR[6]);

		QUIT_NOW = false;

		if (openScreen() == false) {
			error(GS_THIS, "Could not open screen!");
			cleanup();
			return 1;
		}

		ARRAYS = newObject<VmArrayAllocator>();
		INDEX = newObject<Index>();
		
		INTS = newObject<VmIntVars>();
		BOOLS = newObject<VmBoolVars>();
		LOCALS = newObject<VmLocalVars>();
		OBJECTS = newObject<ObjectState>();
		SCRIPTS = newObject<ScriptState>();
		VERBS = newObject<VerbState>();
		ACTORS = newObject<ActorState>();

		if (INDEX->readFromFile(GS_GAME_PATH GS_INDEX_FILENAME) == false) {
			cleanup();
			return 1;
		}

		RESOURCES = newObject<Resources>();
		RESOURCES->open();

		VM = newObject<VirtualMachine>();
		VM->reset();
        vmDebugRemark("Boot");
        vmDebugPause();
		VM->runScript(1, false, false);
        vmDebugResume();
        vmDebugRemark("Loop");

		info(GS_THIS, "=========Starting Main Loop===========");
        PAUSED=1;
		screenLoop();

		cleanup();
		closeScreen();

		return 0;
#endif
	}

	uint8 col = 0;

	bool DEBUG_STOP_AFTER_FRAMES = false;
	int32 DEBUG_STOP_AFTER_FRAMES_COUNT = 0;
	int test = 0;

	void runFrame() {

#if defined(GS_VM_DEBUG) && GS_VM_DEBUG==1
        vmDebugRemark("frame");
#endif

		if (DEBUG_STOP_AFTER_FRAMES) {
			DEBUG_STOP_AFTER_FRAMES_COUNT--;
			if (DEBUG_STOP_AFTER_FRAMES_COUNT <= 0) {
				QUIT_NOW = true;
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

		drawBox(col++, 10, 10, 10, 10);

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

}

namespace gs
{
	void abort_quit_stop() {
		using namespace gs;

		gs::QUIT_NOW = true;

		if (VM) {
			VM->abort();
		}
	}
}