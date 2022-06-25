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

#include "common/types.h"
#include "common/memory.h"

#include "debug.h"
#include "globals.h"
#include "vm.h"
#include "vm_array.h"
#include "vm_vars.h"
#include "index.h"
#include "resource.h"

using namespace common;

extern const char GOODSOUP_VERSION_STR[];

namespace comi
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

	int main() {
		info(COMI_THIS, "%s\n", &GOODSOUP_VERSION_STR[6]);

		QUIT_NOW = false;
		ARRAYS = newObject<VmArrayAllocator>();
		INDEX = newObject<Index>();
		
		INTS = newObject<VmIntVars>();
		BOOLS = newObject<VmBoolVars>();
		LOCALS = newObject<VmLocalVars>();

		if (INDEX->readFromFile(GS_GAME_PATH "COMI.LA0") == false) {
			cleanup();
			return 1;
		}

		RESOURCES = newObject<Resources>();
		RESOURCES->open();

		VM = newObject<VirtualMachine>();
		VM->reset();
		VM->runScript(1, false, false);

		while (QUIT_NOW == false) {
			debug(COMI_THIS, "** FRAME");
			VM->runAllScripts();
		}

		cleanup();

		return 0;
	}

}

namespace common
{
	void abort_quit_stop() {
		using namespace comi;

		comi::QUIT_NOW = true;

		if (VM) {
			VM->abort();
		}
	}
}