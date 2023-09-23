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

#ifndef __GS_BUFFER_IMPL_H
#define __GS_BUFFER_IMPL_H

#include "gs/containers.h"

namespace gs {

    namespace internal { namespace memory {
        APTR __AllocateInternal(ULONG byteSize, AllocationType allocationType, bool clear);
        APTR __ReallocateInternal(APTR data, ULONG byteSize, AllocationType allocationType, bool copy);
        void __ReleaseInternal(APTR data, ULONG byteSize, AllocationType allocationType);
    }}

    template <typename T, AllocationType AT>
    inline void Buffer<T, AT>::release()
    {
        if (data != nullptr) {
            if (owned) {
                ::gs::internal::memory::__ReleaseInternal(data, length * sizeof(T), AT);
            }
            data = nullptr;
            length = 0UL;
            owned = false;
        }
    }

    namespace buffer {

        template<typename T, AllocationType AT>
        inline Buffer<T, AT> acquire(T* data, ULONG length) {
            return Buffer<T, AT>(data, length, false);
        }

        template<typename T, AllocationType AT = AllocationType::Any>
        inline Buffer<T, AT> allocate(ULONG length) {
            APTR mem = internal::memory::__AllocateInternal(length * sizeof(T), AT, true);
            return Buffer<T, AT>(static_cast<T*>(mem), length, true);
        }

    }

}
#endif