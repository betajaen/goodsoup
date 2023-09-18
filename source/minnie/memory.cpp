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

#include <proto/exec.h>

#include "gs/containers.h"
#include "gs/requester.h"

namespace gs {

    namespace internal { namespace memory {
        APTR __AllocateInternal(ULONG byteSize, AllocationType allocationType, bool clear) {
            ULONG requirements = 0UL;

            if (allocationType == AllocationType::Chip) {
                requirements |= MEMF_CHIP;
            }
            else if (allocationType == AllocationType::Fast) {
                requirements |= MEMF_FAST;
            }

            if (clear) {
                requirements |= MEMF_CLEAR;
            }

            APTR mem = AllocVec(byteSize, requirements);
            if (mem == nullptr) {
                requester_fmt("Goodsoup - Error", "Out of memory!\n\nCould not allocate %ld bytes for %s memory.", "OK", byteSize, allocationType == AllocationType::Chip ? "Chip" : "Fast");
            }
            return mem;
        }

        APTR __ReallocateInternal(APTR data, ULONG byteSize, AllocationType allocationType, bool copy) {
            return nullptr; // TODO.
        }

        void __ReleaseInternal(APTR data, ULONG byteSize, AllocationType allocationType) {
            if (data) {
                FreeVec(data);
            }
        }

    }}
}
