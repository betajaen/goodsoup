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
#include <proto/intuition.h>

namespace gs {

    LONG requester_str(CONST_STRPTR title, CONST_STRPTR text, CONST_STRPTR options) {
        EasyStruct es;
        LONG rv;

        es.es_StructSize = sizeof(EasyStruct);
        es.es_Flags = 0;
        es.es_GadgetFormat = options;
        es.es_TextFormat = text;
        es.es_Title = title;

        rv = EasyRequest(NULL, &es, NULL);

        return rv;
    }

    LONG requester_fmt(CONST_STRPTR title, CONST_STRPTR text, CONST_STRPTR options, ...) {

        EasyStruct es;
        LONG rv;

        es.es_StructSize = sizeof(EasyStruct);
        es.es_Flags = 0;
        es.es_GadgetFormat = options;
        es.es_TextFormat = text;
        es.es_Title = title;


		const char* format_arg = (const char*)(&options + 1);

        rv = EasyRequestArgs(NULL, &es, NULL, (ULONG*) format_arg);

        return rv;
    }

}
