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
#include <proto/dos.h>

#include "gs/file.h"

namespace gs {

    void ReadFile::release() {
        if (handle != 0L) {
            Close(handle);
            handle = 0L;
        }
    }

    void ReadFile::setHandle(LONG newHandle) {
        release();
        handle = newHandle;
    }

    FileOffset ReadFile::getPosition() const {
        ULONG rv = 0;

        if (handle == 0L) {
            return FileOffset();
        }

        rv = Seek(handle, OFFSET_CURRENT, 0);
        return FileOffset(rv);
    }

    FileOffset ReadFile::setPosition(FileOffset position) {
        LONG rv;

        if (handle == 0L) {
            return FileOffset();
        }

        Seek(handle, OFFSET_BEGINNING, position);
        rv = Seek(handle, OFFSET_CURRENT, 0L);
        return FileOffset(rv);
    }

    ULONG ReadFile::read(APTR data, ULONG length) {
        if (handle == 0L) {
            return 0;
        }

        LONG rv;

        rv = Read(handle, data, length);

        if (rv < 0) {
            rv = 0;
        }

        return rv;
    }

    namespace readfile {

        bool open(ReadFile& rf, CONST_STRPTR path) {
            rf.release();

            BPTR fh = Open(path, MODE_OLDFILE);

            if (fh == 0L) {
                return false;
            }

            rf.setHandle(fh);
            return true;
        }

    }


    void AppendFile::release() {
        if (handle != 0L) {
            Close(handle);
            handle = 0L;
        }
    }

    void AppendFile::setHandle(LONG newHandle) {
        release();
        handle = newHandle;
    }

     namespace appendfile {

        bool open(AppendFile& af, CONST_STRPTR path) {
            af.release();

            BPTR fh = Open(path, MODE_NEWFILE);

            if (fh == 0L) {
                return false;
            }

            af.setHandle(fh);
            return true;
        }

    }
}

