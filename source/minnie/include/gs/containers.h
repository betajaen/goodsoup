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

#ifndef __GS_CONTAINERS_H
#define __GS_CONTAINERS_H

#if !defined(__AMIGA__)
#error "Only Amiga supported!"
#endif

#include <exec/types.h>

namespace gs {

    enum class AllocationType {
        Chip,
        Fast,
        Any = Fast
    };

    template<typename T, AllocationType AT>
    class Buffer final {
    private:
        T* data = nullptr;
        ULONG length = 0;
        bool owned = false;
    public:

        Buffer() = default;

        Buffer(T* data_, ULONG length_, bool owned_) {
            this->data = data_;
            this->length = length_;
            this->owned = owned_;
        }

        ~Buffer() {
            release();
        }

        void release();

        Buffer(const Buffer&) = delete;
        Buffer& operator=(const Buffer&) = delete;
        Buffer(Buffer&) = delete;
        Buffer& operator=(Buffer&) = delete;

        Buffer(Buffer&& fh) = default;
        Buffer& operator=(Buffer&&) = default;

        T* getData() {
            return data;
        }

        const T* getData() const {
            return data;
        }

        operator bool() const {
            return data != nullptr;
        }
    };
}

#endif