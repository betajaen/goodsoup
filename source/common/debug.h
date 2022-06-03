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

#ifndef DEBUG_H
#define DEBUG_H

#include "common/types.h"

namespace common
{
    enum DebugCategory
    {
        DC_Test = 0,
        DC_Verbose = 1,
        DC_Debug  = 2,
        DC_Informational = 3,
        DC_Warning = 4,
        DC_Error = 5
    };

#ifndef GS_FILE_NAME
    #define GS_FILE_NAME __FILE__
#endif

    #define GS_THIS "GS  ", GS_FILE_NAME, __FUNCTION__, __LINE__

    void debug_write(DebugCategory category, const char* module, const char* file, const char* function, uint32 line, const char* message);
    void debug_writef(DebugCategory category, const char* module, const char* file, const char* function, uint32 line, const char* format, ...);
    void debug_stop(const char* message);

    inline void verbose(const char* module, const char* file, const char* function, uint32 line, const char* message) {
        debug_write(DC_Verbose, module, file, function, line, message);
    }

    template<typename T0>
    inline void verbose(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0) {
        debug_writef(DC_Verbose, module, file, function, line, format, a0);
    }

    template<typename T0, typename T1>
    inline void verbose(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1) {
        debug_writef(DC_Verbose, module, file, function, line, format, a0, a1);
    }

    template<typename T0, typename T1, typename T2>
    inline void verbose(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2) {
        debug_writef(DC_Verbose, module, file, function, line, format, a0, a1, a2);
    }

    template<typename T0, typename T1, typename T2, typename T3>
    inline void verbose(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2, const T3& a3) {
        debug_writef(DC_Verbose, module, file, function, line, format, a0, a1, a2, a3);
    }

    template<typename T0, typename T1, typename T2, typename T3, typename T4>
    inline void verbose(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2, const T3& a3, const T4& a4) {
        debug_writef(DC_Verbose, module, file, function, line, format, a0, a1, a2, a3, a4);
    }

    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
    inline void verbose(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2, const T3& a3, const T4& a4, const T5& a5) {
        debug_writef(DC_Verbose, module, file, function, line, format, a0, a1, a2, a3, a4, a5);
    }

    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    inline void verbose(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2, const T3& a3, const T4& a4, const T5& a5, const T6& a6) {
        debug_writef(DC_Verbose, module, file, function, line, format, a0, a1, a2, a3, a4, a5, a6);
    }

    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    inline void verbose(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2, const T3& a3, const T4& a4, const T5& a5, const T6& a6, const T7& a7) {
        debug_writef(DC_Verbose, module, file, function, line, format, a0, a1, a2, a3, a4, a5, a6, a7);
    }



    inline void debug(const char* module, const char* file, const char* function, uint32 line, const char* message) {
        debug_write(DC_Debug, module, file, function, line, message);
    }

    template<typename T0>
    inline void debug(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0) {
        debug_writef(DC_Debug, module, file, function, line, format, a0);
    }

    template<typename T0, typename T1>
    inline void debug(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1) {
        debug_writef(DC_Debug, module, file, function, line, format, a0, a1);
    }

    template<typename T0, typename T1, typename T2>
    inline void debug(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2) {
        debug_writef(DC_Debug, module, file, function, line, format, a0, a1, a2);
    }

    template<typename T0, typename T1, typename T2, typename T3>
    inline void debug(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2, const T3& a3) {
        debug_writef(DC_Debug, module, file, function, line, format, a0, a1, a2, a3);
    }

    template<typename T0, typename T1, typename T2, typename T3, typename T4>
    inline void debug(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2, const T3& a3, const T4& a4) {
        debug_writef(DC_Debug, module, file, function, line, format, a0, a1, a2, a3, a4);
    }

    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
    inline void debug(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2, const T3& a3, const T4& a4, const T5& a5) {
        debug_writef(DC_Debug, module, file, function, line, format, a0, a1, a2, a3, a4, a5);
    }

    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    inline void debug(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2, const T3& a3, const T4& a4, const T5& a5, const T6& a6) {
        debug_writef(DC_Debug, module, file, function, line, format, a0, a1, a2, a3, a4, a5, a6);
    }

    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    inline void debug(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2, const T3& a3, const T4& a4, const T5& a5, const T6& a6, const T7& a7) {
        debug_writef(DC_Debug, module, file, function, line, format, a0, a1, a2, a3, a4, a5, a6, a7);
    }


    inline void info(const char* module, const char* file, const char* function, uint32 line, const char* message) {
        debug_write(DC_Informational, module, file, function, line, message);
    }

    template<typename T0>
    inline void info(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0) {
        debug_writef(DC_Informational, module, file, function, line, format, a0);
    }

    template<typename T0, typename T1>
    inline void info(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1) {
        debug_writef(DC_Informational, module, file, function, line, format, a0, a1);
    }

    template<typename T0, typename T1, typename T2>
    inline void info(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2) {
        debug_writef(DC_Informational, module, file, function, line, format, a0, a1, a2);
    }

    template<typename T0, typename T1, typename T2, typename T3>
    inline void info(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2, const T3& a3) {
        debug_writef(DC_Informational, module, file, function, line, format, a0, a1, a2, a3);
    }

    template<typename T0, typename T1, typename T2, typename T3, typename T4>
    inline void info(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2, const T3& a3, const T4& a4) {
        debug_writef(DC_Informational, module, file, function, line, format, a0, a1, a2, a3, a4);
    }

    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
    inline void info(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2, const T3& a3, const T4& a4, const T5& a5) {
        debug_writef(DC_Informational, module, file, function, line, format, a0, a1, a2, a3, a4, a5);
    }

    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    inline void info(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2, const T3& a3, const T4& a4, const T5& a5, const T6& a6) {
        debug_writef(DC_Informational, module, file, function, line, format, a0, a1, a2, a3, a4, a5, a6);
    }

    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    inline void info(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2, const T3& a3, const T4& a4, const T5& a5, const T6& a6, const T7& a7) {
        debug_writef(DC_Informational, module, file, function, line, format, a0, a1, a2, a3, a4, a5, a6, a7);
    }



    inline void warn(const char* module, const char* file, const char* function, uint32 line, const char* message) {
        debug_write(DC_Warning, module, file, function, line, message);
    }

    template<typename T0>
    inline void warn(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0) {
        debug_writef(DC_Warning, module, file, function, line, format, a0);
    }

    template<typename T0, typename T1>
    inline void warn(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1) {
        debug_writef(DC_Warning, module, file, function, line, format, a0, a1);
    }

    template<typename T0, typename T1, typename T2>
    inline void warn(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2) {
        debug_writef(DC_Warning, module, file, function, line, format, a0, a1, a2);
    }

    template<typename T0, typename T1, typename T2, typename T3>
    inline void warn(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2, const T3& a3) {
        debug_writef(DC_Warning, module, file, function, line, format, a0, a1, a2, a3);
    }

    template<typename T0, typename T1, typename T2, typename T3, typename T4>
    inline void warn(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2, const T3& a3, const T4& a4) {
        debug_writef(DC_Warning, module, file, function, line, format, a0, a1, a2, a3, a4);
    }

    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
    inline void warn(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2, const T3& a3, const T4& a4, const T5& a5) {
        debug_writef(DC_Warning, module, file, function, line, format, a0, a1, a2, a3, a4, a5);
    }

    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    inline void warn(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2, const T3& a3, const T4& a4, const T5& a5, const T6& a6) {
        debug_writef(DC_Warning, module, file, function, line, format, a0, a1, a2, a3, a4, a5, a6);
    }

    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    inline void warn(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2, const T3& a3, const T4& a4, const T5& a5, const T6& a6, const T7& a7) {
        debug_writef(DC_Warning, module, file, function, line, format, a0, a1, a2, a3, a4, a5, a6, a7);
    }



    inline void error(const char* module, const char* file, const char* function, uint32 line, const char* message) {
        debug_write(DC_Error, module, file, function, line, message);
    }

    template<typename T0>
    inline void error(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0) {
        debug_writef(DC_Error, module, file, function, line, format, a0);
    }

    template<typename T0, typename T1>
    inline void error(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1) {
        debug_writef(DC_Error, module, file, function, line, format, a0, a1);
    }

    template<typename T0, typename T1, typename T2>
    inline void error(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2) {
        debug_writef(DC_Error, module, file, function, line, format, a0, a1, a2);
    }

    template<typename T0, typename T1, typename T2, typename T3>
    inline void error(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2, const T3& a3) {
        debug_writef(DC_Error, module, file, function, line, format, a0, a1, a2, a3);
    }

    template<typename T0, typename T1, typename T2, typename T3, typename T4>
    inline void error(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2, const T3& a3, const T4& a4) {
        debug_writef(DC_Error, module, file, function, line, format, a0, a1, a2, a3, a4);
    }

    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
    inline void error(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2, const T3& a3, const T4& a4, const T5& a5) {
        debug_writef(DC_Error, module, file, function, line, format, a0, a1, a2, a3, a4, a5);
    }

    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    inline void error(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2, const T3& a3, const T4& a4, const T5& a5, const T6& a6) {
        debug_writef(DC_Error, module, file, function, line, format, a0, a1, a2, a3, a4, a5, a6);
    }

    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    inline void error(const char* module, const char* file, const char* function, uint32 line, const char* format, const T0& a0, const T1& a1, const T2& a2, const T3& a3, const T4& a4, const T5& a5, const T6& a6, const T7& a7) {
        debug_writef(DC_Error, module, file, function, line, format, a0, a1, a2, a3, a4, a5, a6, a7);
    }

    inline void test(bool cond, const char* message = NULL)
    {
        if (cond == false) {
            debug_stop(message);
        }
    } 

}

#endif
