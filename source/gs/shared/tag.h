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

typedef struct gs_TagPair {
	uint32 tag;
	uint32 start;
	uint32 end;
} gs_TagPair;

GS_IMPORT const char* gs_Tag2Str(uint32 tag);

#define gs_TagPair2Str(TAG_PAIR_PTR) (gs_Tag2Str((TAG_PAIR_PTR)->tag))


#define gs_IsTagPair(TAGPAIR_PTR, A, B, C, D) (((TAGPAIR_PTR)->tag) == (gs_MakeId(A,B,C,D)))

#define gs_TagPairDataLength(TAGPAIR_PTR)  ((((TAGPAIR_PTR)->end) - ((TAGPAIR_PTR)->start)) - 8)


#endif
