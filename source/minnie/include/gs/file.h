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

#ifndef __GS_FILE_H
#define __GS_FILE_H

#if !defined(__AMIGA__)
#error "Only Amiga supported!"
#endif

#include <exec/types.h>

namespace gs {

    class ReadFile final {
    private:
        LONG handle = 0L;
    public:

        ReadFile() = default;

        ReadFile(LONG handle_) :
            handle(handle_) {
        }

        ~ReadFile() {
            release();
        }

        LONG getHandle() const {
            return handle;
        }
        
        void setHandle(LONG handle);
        void release();

        ReadFile(const ReadFile&) = delete;
        ReadFile& operator=(const ReadFile&) = delete;
        ReadFile(ReadFile&) = delete;
        ReadFile& operator=(ReadFile&) = delete;

        ReadFile(ReadFile&& fh) = default;
        ReadFile& operator=(ReadFile&&) = default;

        ULONG setPosition(ULONG position);
        ULONG getPosition() const;

        ULONG read(APTR buffer, ULONG length_bytes);

        operator bool() const {
            return handle != 0L;
        }
    };




}

#endif