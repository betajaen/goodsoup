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

#ifndef GS_TEST_H
#define GS_TEST_H

#include "types.h"
#include "debug.h"
#include "ext.h"

namespace gs
{

#if GS_TEST == 1
	void handle_test_fail_write_header(const char* file, uint32 line, const char* testName);

	void handle_test_fail_write_aopb_string(const char* left, const char* right, const char* operatorType);

	template<typename TA, typename TB>
	void handle_test_fail_write_aopb_value(const TA& a, const TB& b, const char* operatorType) {
		debugWriter<TA>::printable(a);
		debug_write_char(' ');
		debug_write_str(operatorType);
		debug_write_char(' ');
		debugWriter<TB>::printable(b);
	}

	template<typename TA, typename TB>
	void handle_test_fail(const char* file, uint32 line, const char* testName, const TA& a, const TB& b, const char* aName, const char* bName, const char* operatorType) {        
		handle_test_fail_write_header(file, line, testName);
		handle_test_fail_write_aopb_string(aName, bName, operatorType);
		debug_write_char('\n');
		debug_write_str("with expansion:\n\t");
		handle_test_fail_write_aopb_value(a, b, operatorType);
		debug_write_str("\n\n"); 
	}

	void handle_leak_measure(uint32& m);
	void handle_test_heap_then_memory_offset(const char* file, int32 line, const char* testName, uint32 marker, int32 bytes);
	void handle_test_pass();
	void handle_test_fail();
	void handle_test_equal_str(const char* expected, const char* result);
#endif
}

#if GS_TEST == 1

#define TEST_EQUAL(EXPECTED, RESULT) do {\
	if (equals(EXPECTED, RESULT)) {\
		::gs::handle_test_pass();\
	} else {\
		::gs::handle_test_fail(__FILE__, __LINE__, __FUNCTION__, EXPECTED, RESULT, #EXPECTED, #RESULT, "==");\
		::gs::handle_test_fail();\
		return;\
	} } while(0)


#define TEST_MEMORY(MARKER, EXPECTED) \
	::gs::handle_test_heap_then_memory_offset(\
		__FILE__, __LINE__, __FUNCTION__, test_marker_##MARKER, EXPECTED) 


#define TEST_MEMORY_MEASURE(MARKER) \
	uint32 test_marker_##MARKER;\
	::gs::handle_leak_measure(test_marker_##MARKER)

#else

#define TEST_EQUAL(EXPECTED, RESULT)
#define TEST_MEMORY(MARKER, EXPECTED)
#define TEST_MEMORY_MEASURE(MARKER)

#endif


#define TEST_CASE(NAME) void testcase_##NAME()
#define TEST_SUITE(NAME) void test_##NAME()
#define TEST_RUN_CASE(NAME) testcase_##NAME()

#endif
