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

#ifndef TEST_H
#define TEST_H

#include "common/types.h"
#include "common/debug.h"

namespace common
{

    template<typename TA, typename TB>
    void handle_test_fail(const char* file, uint32 line, const char* testName, const TA& a, const TB& b, const char* aName, const char* bName, const char* operatorType) {
        debug_write_char('\n');
        debug_write_str(file);
        debug_write_char('(');
        debug_write_unsigned_int(line);
        debug_write_char(',');
        debug_write_str(testName);
        debug_write_str(") FAILED!\n\t");
        
        debug_write_str(aName);
        debug_write_char(' ');
        debug_write_str(operatorType);
        debug_write_char(' ');
        debug_write_str(bName);
        debug_write_char('\n');
        
        debug_write_str("with expansion:\n\t");
        
        debugWriter<TA>::printable(a);
        debug_write_char(' ');
        debug_write_str(operatorType);
        debug_write_char(' ');
        debugWriter<TB>::printable(b);
        
        debug_write_str("\n\n"); 
    }

    void handle_test_good() {
        debug_write_char('.');
        
    }
}

#define TEST_EQUAL(EXPECTED, RESULT) \
    if (!(EXPECTED == RESULT)) {\
        ::common::handle_test_fail(__FILE__, __LINE__, __FUNCTION__, EXPECTED, RESULT, #EXPECTED, #RESULT, "==");\
        return;\
    }

#endif
