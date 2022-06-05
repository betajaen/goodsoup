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

#define GS_FILE_NAME "keyarray"

#include "keyarray.h"
#include "common/debug.h"
#include "common/test.h"

namespace common
{

	TEST_CASE(keyarray_1) {
		KeyArray<const char*, int32> a;
		
		a.addOnce("test", 1234);
		TEST_EQUAL(1234, a.get("test"));
		TEST_EQUAL(1, a.size());
		TEST_EQUAL(false, a.exists("test2"));
		TEST_EQUAL(true, a.exists("test"));
		a.remove("test");
		TEST_EQUAL(false, a.exists("test"));
		TEST_EQUAL(0, a.size());
	}

	TEST_SUITE(keyarray) {
		TEST_RUN_CASE(keyarray_1);
	}

}
