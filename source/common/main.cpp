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

#define GS_FILE_NAME "common/main"

#include "common/types.h"
#include "common/debug.h"

extern const char GOODSOUP_VERSION_STR[] = "$VER: goodsoup 0.1 (" __AMIGADATE__ ")";

namespace common
{
	void checkMem();
}

#if GS_TEST == 1
namespace test
{
	int run();
}
#endif

namespace comi
{
	int start();
}

namespace common
{

	int common_main()
	{
		int rc = 0;

		debug_write_str(GOODSOUP_VERSION_STR);
		debug_write_char('\n');

#if GS_TEST == 1
		rc = test::run();
#else
		rc = comi::start();
#endif

		common::checkMem();
		return rc;
	}
}