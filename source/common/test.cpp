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

#define GS_FILE_NAME "test"

#include "common/test.h"
#include "common/debug.h"

#if GS_TEST == 1

static uint32 testsPassed = 0, testsFailed = 0;

namespace common
{
	void handle_test_pass() {
		testsPassed++;
	}

	void handle_test_fail() {
		testsFailed++;
	}
}

namespace test
{
	void test_file();

	void run() {

		using namespace common;

		debug_write_str("Starting Tests\n");

		test_file();

		debug_write_char('\n');
		debug_write_unsigned_int(testsPassed);
		debug_write_str(" passed.");
		debug_write_unsigned_int(testsFailed);
		debug_write_str(" failed.");
		debug_write_char('\n');

	}
}

#endif
