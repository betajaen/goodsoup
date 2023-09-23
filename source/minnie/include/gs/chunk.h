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

#ifndef __GS_CHUNK_H
#define __GS_CHUNK_H

#if !defined(__AMIGA__)
#error "Only Amiga supported!"
#endif

#include <exec/types.h>

namespace gs {

    class Chunk final {
        
        public:

            const ULONG chunk = 0;
            const ULONG start = 0;
            const ULONG size = 0;
            const ULONG next = 0;

            Chunk() = default;

            Chunk(ULONG chunk_, ULONG start_, ULONG size_, ULONG next_)
                : chunk(chunk_), start(start_), size(size_), next(next_) {
            }

            bool operator==(const ULONG four_cc);

            operator bool() const {
                return chunk != 0UL;
            }

    };


}

#endif