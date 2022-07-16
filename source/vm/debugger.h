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

#ifndef GS_VM_DEBUGGER_H
#define GS_VM_DEBUGGER_H

#include "types.h"
#include "file.h"
#include "debug.h"

namespace gs
{

#if defined(GS_VM_DEBUG) && GS_VM_DEBUG==1

    bool vmDebugStart();
    void vmDebugStop();
    void vmDebugPause();
    void vmDebugResume();

    void vmDebugRemark(const char* comment);
    void vmDebugScript(uint8 context, uint16 scriptNum, uint8 scriptType, uint8 verb, uint32 checkSum);
    void vmDebugLocals(uint8 count, int32* values);
    void vmDebugStack(uint8 count, int32* values);
    void vmDebugOpcode(uint16 pc, uint8 opcode);
    void vmDebugResult(int32 v0);
    void vmDebugResult(int32 v0, int32 v1);
    void vmDebugResult(int32 v0, int32 v1, int32 v2);
    void vmDebugResult(int32 v0, int32 v1, int32 v2, int32 v3);
    void vmDebugResult(int32 v0, int32 v1, int32 v2, int32 v3, int32 v4);

#else

    inline bool vmDebugStart() { return true; }
    inline void vmDebugStop() {}
    inline void vmDebugRemark(const char* comment) {}
    inline void vmDebugScript(uint8 context, uint16 scriptNum, uint8 scriptType, uint8 verb, uint32 checkSum) {}
    inline void vmDebugLocals(uint8 count, int32* values) {}
    inline void vmDebugStack(uint8 count, int32* values) {}
    inline void vmDebugOpcode(uint16 pc, uint8 opcode) {}
    inline void vmDebugResult(int32 v0) {}
    inline void vmDebugResult(int32 v0, int32 v1) {}
    inline void vmDebugResult(int32 v0, int32 v1, int32 v2) {}
    inline void vmDebugResult(int32 v0, int32 v1, int32 v2, int32 v3) {}
	inline void vmDebugResult(int32 v0, int32 v1, int32 v2, int32 v3, int32 v4) {}
#endif
}

#endif
