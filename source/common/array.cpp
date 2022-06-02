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

#define GS_FILE_NAME "array"

#include "array.h"

namespace common
{
	void test_array() {
		Array<int32> a;
		a.push(1);
		a.push(2);
		a.push(3);
		a.push(4);
		a.push(5);
		a.push(6);
		a.push(7);
		a.push(8);
		a.push(9);
		a.push(10);
		a.push(11);
		a.push(12);
		a.push(13);
		a.push(14);
		a.pop();
		a.erase(3);

		FixedArray<int32, 8> b;
		b[2] = 3;
		b[10] = -3;
	}
}
