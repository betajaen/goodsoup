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

#define GS_FILE_NAME "comi/context"

#include "common/memory.h"
#include "common/debug.h"
#include "common/file.h"
#include "context.h"

using namespace common;

extern const char GOODSOUP_VERSION_STR[];

namespace comi
{
	Context::Context() {
	}

	Context::~Context() {
	}

	void Context::initialize() {
	}

	bool Context::canRun() {
		return fileExists("data/COMI.LA0");
	}

	void Context::run() {
		vm.reset();
	}
}
