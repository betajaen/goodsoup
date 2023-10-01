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

#include "gs/file.h"
#include "gs/chunk.h"

namespace gs {

    bool Chunk::operator==(const ULONG four_cc) {
        return chunk == four_cc;
    }

    namespace chunk {

        Chunk readLaChunk(ReadFile& rf) {
            return Chunk(); // TODO
        }

        Chunk readSanChunk(ReadFile& rf) {
            return Chunk(); // TODO
        }

        Chunk readGsChunk(ReadFile& rf) {
            return Chunk(); // TODO
        }

        void skipChunk(ReadFile& rf, Chunk& chunk) {
            rf.setPosition(FileOffset(chunk.next));
        }

    }
}

