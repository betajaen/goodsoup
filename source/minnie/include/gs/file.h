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

    class ReadFile;
    class ReadFileChunk;

    namespace readfile {

        bool open(ReadFile& rf, CONST_STRPTR path);

        ReadFileChunk readLaChunk(ReadFile& rf);
        ReadFileChunk readSanChunk(ReadFile& rf);
        ReadFileChunk readGsChunk(ReadFile& rf);

        void skipChunk(ReadFile& rf, ReadFileChunk& chunk);
    }

    class ReadFile final {
    private:
        LONG handle = 0L;
    public:

        friend bool readfile::open(ReadFile& rf, CONST_STRPTR path);

        ReadFile() = default;

        ReadFile(LONG handle_) :
            handle(handle_) {
        }

        ~ReadFile() {
            release();
        }

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

    class ReadFileChunk final {
        private:
            ULONG chunk = 0;
            ULONG start = 0;
            ULONG size = 0;
            ULONG next = 0;
        public:


            ReadFileChunk() = default;

            ReadFileChunk(ULONG chunk_, ULONG start_, ULONG size_, ULONG next_)
                : chunk(chunk_), start(start_), size(size_), next(next_) {
            }

            inline ULONG getChunk() const {
                return chunk;
            }

            inline bool isChunk(ULONG test) const {
                return chunk == test;
            }

            inline bool isEnd() const {
                return chunk == 0;
            }

            inline ULONG getStart() const {
                return start;
            }

            inline ULONG getSize() const {
                return size;
            }

            inline ULONG getNext() const {
                return next;
            }

    };




}

#endif