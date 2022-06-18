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

#define GS_FILE_NAME "utils"

#include "utils.h"

namespace comi
{
	static uint32 _rand = 0xC81198ab;

	uint32 getRandom(uint32 max) {
		_rand = 0xDEADBF03 * (_rand + 1);
		_rand = (_rand >> 13) | (_rand << 19);
		return _rand % (max + 1);
	}

	uint32 getRandomRange(uint32 min, uint32 max) {
		return getRandom(max - min) + min;
	}

}



