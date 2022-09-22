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

#define GS_FILE "tag"

#include "shared/forward.h"
#include "shared/tag.h"


GS_EXPORT const char* gs_Tag2Str(uint32 tag) {
	static char str[5] = { 0 };

#if defined(GS_BIG)
	str[0] = (char)(tag >> 24);
	str[1] = (char)(tag >> 16);
	str[2] = (char)(tag >> 8);
	str[3] = (char)tag;
#else
	str[0] = (char)tag;
	str[1] = (char)(tag >> 8);
	str[2] = (char)(tag >> 16);
	str[3] = (char)(tag >> 24);
#endif
	str[4] = '\0';
	return str;
}

GS_EXPORT const char* gs_TagPair2Str(gs_TagPair* tagPair) {
	static char str[5] = { 0 };

#if defined(GS_BIG)
	str[0] = (char)(tagPair->tag >> 24);
	str[1] = (char)(tagPair->tag >> 16);
	str[2] = (char)(tagPair->tag >> 8);
	str[3] = (char)tagPair->tag;
#else
	str[0] = (char)tagPair->tag;
	str[1] = (char)(tagPair->tag >> 8);
	str[2] = (char)(tagPair->tag >> 16);
	str[3] = (char)(tagPair->tag >> 24);
#endif
	str[4] = '\0';
	return str;
}
