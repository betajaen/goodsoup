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

namespace common
{


	void test_keyarray() {
		KeyArray<const char*, int32> a;
		
		a.addOnce("test", 1234);
		gs_test(a.get("test") == 1234);
		gs_test(a.size() == 1);
		gs_test(a.exists("test2") == false);
		gs_test(a.exists("test") == true);
		a.remove("test");
		gs_test(a.exists("test") == false);
		gs_test(a.size() == 0);
		
	}
}
