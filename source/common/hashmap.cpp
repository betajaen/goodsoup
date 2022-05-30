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

#define GS_FILE_NAME "hashmap"

#include "hashmap.h"

namespace common
{
	static int _to_lower(int ch)
	{
		if (ch >= 'A' && ch <= 'Z')
			return ch + 32;
		else
			return ch;
	}

	uint32 hashString(const char* str)
	{
		uint hash = 0;
		byte c;

		hash = 0;
		while ((c = *str++))
			hash = (hash * 31 + c);

		return hash;
	}

	uint32 hashStringLower(const char* str)
	{
		uint hash = 0;
		byte c;

		hash = 0;
		while ((c = *str++))
			hash = (hash * 31 + _to_lower(*str));

		return hash;
	}

	static const uint32 primes[] = {
		53ul,         97ul,         193ul,       389ul,       769ul,
		1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
		49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
		1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
		50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
		1610612741ul, 3221225473ul, 4294967291ul
	};

	uint32 nextTableSize(uint32 x) {
		int i = 0;
		while (x >= primes[i])
			i++;
		return primes[i];
	}
}
