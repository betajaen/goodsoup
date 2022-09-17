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

#ifndef GS_STRING_H
#define GS_STRING_H

#include "shared/forward.h"

GS_IMPORT uint32 gs_format(char* buf, uint32 bufLength, const char* fmt, ...);
GS_IMPORT uint32 gs_format_vargs(char* buf, uint32 bufLength, const char* fmt, void* args);
GS_IMPORT uint32 gs_format_length(const char* fmt, ...);
GS_IMPORT uint32 gs_format_length_vargs(const char* fmt, void* args);
GS_IMPORT uint32 gs_hash_str(const char* str);

#define gs_hash_init(HASH) uint32 HASH;
#define gs_hash_feed(HASH, BYTE)	do { HASH = ((HASH << 5) + HASH) + BYTE; } while(0)

#endif
