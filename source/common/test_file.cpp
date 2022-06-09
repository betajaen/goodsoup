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

#define GS_FILE_NAME "test/file"

#include "common/file.h"
#include "common/test.h"

namespace test
{
	using namespace common;

	TEST_CASE(file_exists) {

		TEST_EQUAL(true, fileExists("tests/testfile"));
	}

	TEST_CASE(file_open_close) {
		ReadFile file;
		TEST_EQUAL(false, file.isOpen());

		file.open("tests/testfile");
		TEST_EQUAL(true, file.isOpen());

		TEST_EQUAL(8266u, file.length());

		file.close();
		TEST_EQUAL(false, file.isOpen());
	}

	TEST_CASE(file_open_read_close) {
		ReadFile file;
		char tag[5] = {0};

		TEST_EQUAL(false, file.isOpen());

		file.open("tests/testfile");
		TEST_EQUAL(true, file.isOpen());

		TEST_EQUAL(8266u, file.length());

		file.readTag(tag);

		bool isForm = equals("FORM", tag);

		TEST_EQUAL(true, isForm);



		file.close();
		TEST_EQUAL(false, file.isOpen());
	}

	void test_file() {
		TEST_RUN_CASE(file_exists);
		TEST_RUN_CASE(file_open_close);
	}
}
