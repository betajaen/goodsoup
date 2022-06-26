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

extern const char GOODSOUP_VERSION_STR[] = "$VER: goodsoup 0.3 (" __AMIGADATE__ ")";

#if GS_TEST == 1
namespace test
{
	int run();
}
#endif

namespace gs
{

	bool QUIT_NOW = false;
	int32 SENTENCE_NUM = 0;

	void cleanup() {
		deleteObject(VM);
		deleteObject(INTS);
		deleteObject(BOOLS);
		deleteObject(LOCALS);
		deleteObject(ARRAYS);
		deleteObject(INDEX);
		deleteObject(RESOURCES);
	}

	int main(int param) {
		
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

		if (INDEX->readFromFile(GS_GAME_PATH GS_INDEX_FILENAME) == false) {
			cleanup();
			return 1;
		}

		RESOURCES = newObject<Resources>();
		RESOURCES->open();

		VM = newObject<VirtualMachine>();
		VM->reset();
		VM->runScript(1, false, false);

		while (QUIT_NOW == false) {
			debug(GS_THIS, "** FRAME");
			VM->runAllScripts();
		}

		cleanup();
		closeScreen();

		return 0;
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