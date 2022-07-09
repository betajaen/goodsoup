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

#define GS_FILE_NAME "vm_debugger"

#include "vm_debugger.h"
#include "vm.h"

extern const char GOODSOUP_VERSION_STR[];

namespace gs
{

#if defined(GS_VM_DEBUG) && GS_VM_DEBUG==1

    StringAppendFile sDebugFile;
    bool sPaused;

    bool vmDebugStart() {
        debug(GS_THIS, "Opening VMD");

        for(uint16 i=1;i <= 10;i++) {
            String name = String::format("vmd.%lx.log", (uint32) i);
            sDebugFile.open(name.string());

            if (sDebugFile.isOpen()) {
                break;
            }

        }

        if (sDebugFile.isOpen() == false) {
            return false;
        }

        sDebugFile.writeString("REM \"Active\"\n");
        sDebugFile.writeFormat("REM \"version\" \"%s\"\n", &GOODSOUP_VERSION_STR[6]);
        sPaused = false;

        return true;
    }

    void vmDebugStop() {
        sDebugFile.writeString("REM \"Ending\"\n");
        sDebugFile.close();
        debug(GS_THIS, "Closing VMD");
    }

    void vmDebugPause() {
        sPaused = true;
    }

    void vmDebugResume() {
        sPaused = false;
    }

    void vmDebugRemark(const char* comment) {
        if (sPaused == false) {
            sDebugFile.writeFormat("REM \"%s\"\n", comment);
        }
    }

    void vmDebugScript(uint8 context, uint16 scriptNum, uint8 scriptType, uint8 verb, uint32 checkSum) {
        if (sPaused == false) {
            sDebugFile.writeFormat("\n@ %02lx %04lx \"%s\" %02lx %08lx\n", context, scriptNum, ObjectWhereToString(scriptType), verb, checkSum);
        }
    }

    void vmDebugLocals(uint8 count, int32* values) {
        if (sPaused == false) {
            for(uint8 i = 0;i < count;i++) {
                sDebugFile.writeFormat("L %02x %08x\n", i, values[i]);
            }
        }
    }

    void vmDebugStack(uint8 count, int32* values) {
         if (sPaused == false) {
            for(uint8 i = 0;i < count;i++) {
                sDebugFile.writeFormat("S %02x %08x\n", i, values[i]);
            }
        }
    }

    void vmDebugOpcode(uint16 pc, uint8 opcode) {
        if (sPaused == false) {
            sDebugFile.writeFormat("> %04lx %02lx \"%s\"\n", pc, opcode, OpcodeToString(opcode));
        }
    }

    void vmDebugResult(int32 v0) {
        if (sPaused == false) {
            sDebugFile.writeFormat(". %08lx\n", v0);
        }
    }

    void vmDebugResult(int32 v0, int32 v1) {
        if (sPaused == false) {
            sDebugFile.writeFormat(". %08lx %08lx\n", v0, v1);
        }
    }

    void vmDebugResult(int32 v0, int32 v1, int32 v2) {
        if (sPaused == false) {
            sDebugFile.writeFormat(". %08lx %08lx %08lx\n", v0, v1, v2);
        }
    }

    void vmDebugResult(int32 v0, int32 v1, int32 v2, int32 v3) {
        if (sPaused == false) {
            sDebugFile.writeFormat(". %08lx %08lx %08lx %08lx\n", v0, v1, v2, v3);
        }
    }

#endif
}