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

#include "gs/types.h"
#include "gs/containers.h"
#include "gs/buffer_impl.h"
#include "gs/requester.h"

#include <proto/dos.h>

extern int gs_game(int param);
extern int gs_convert(ULONG what, ULONG capabilities);
extern int gs_player(ULONG what, ULONG capabilities);
extern int gs_viewer(ULONG what, ULONG capabilities);

int gs_main(ULONG param, ULONG param2) {

    int rv = 0;

    Printf("Params are %ld %ld\n", param, param2);

    if (param < 2001) {
        rv = gs_game(param);
    }
    else if (param < 2100) {
        rv = gs_convert(param - 2001, param2);
    }
    else if (param < 2200) {
        rv = gs_player(param - 2100, param2);
    }
    else if (param < 3000) {
        rv = gs_viewer(param - 2200, param2);
    }
    else {
        rv = kReturnError;
    }

    //gs::Buffer<ULONG> parts;
    //parts.release();
    //auto buf = gs::buffer::allocate<ULONG, gs::AllocationType::Chip>(128*1024);
    //gs::requester_fmt("Hello", "Test %ld %ld %s %lx", "OK", (ULONG) 1234UL, (ULONG) 56789UL, "Hello", buf.getData());
    return rv;
}