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

#ifndef GS_TAG_H
#define GS_TAG_H

#include "shared/forward.h"

#define GS_TAG_BYTE_SIZE 8

#define GS_TAG_LA_ROOM_FILE gs_MakeId('L', 'F', 'L', 'F')

#define GS_TAG_GS_FILE_MAGIC_BE "GSBE"
#define GS_TAG_GS_FILE_MAGIC_LE "GSLE"

// Structured Data that can be represented in a C struct
#define GS_TAG_GSD_INFO gs_MakeId('I', 'N', 'F', 'O')

// Unstructured Data (i.e. raw bytes)
#define GS_TAG_GSD_DATA gs_MakeId('D', 'A', 'T', 'A')

// Room Container
#define GS_TAG_GSC_ROOM gs_MakeId('R', 'O', 'O', 'M')

// Background Container
#define GS_TAG_GSC_ROOM_BACKGROUND gs_MakeId('B', 'G', 'N', 'D')

// Image Container
#define GS_TAG_GSC_IMAGE gs_MakeId('I', 'M', 'G', ' ')

// Palette Container
#define GS_TAG_GSC_PALETTE gs_MakeId('P', 'A', 'L', ' ')

// Script Container
#define GS_TAG_GSC_SCRIPT gs_MakeId('S', 'C', 'R', 'P')

GS_IMPORT const char* gs_Tag2Str(uint32 tag);

GS_IMPORT const char* gs_TagPair2Str(gs_TagPair* tag);


#define gs_IsTagPair(TAGPAIR_PTR, A, B, C, D) (((TAGPAIR_PTR)->tag) == (gs_MakeId(A,B,C,D)))

#define gs_TagPairDataLength(TAGPAIR_PTR)  ((((TAGPAIR_PTR)->end) - ((TAGPAIR_PTR)->start)) - 8)


#endif
