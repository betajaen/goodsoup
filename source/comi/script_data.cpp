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

#define GS_FILE_NAME "comi/script_data"

#include "script_data.h"
#include "debug.h"

using namespace common;

namespace comi
{
	ScriptData::ScriptData() {
		comi_debug(".");
	}

	ScriptData::~ScriptData() {
		comi_debug(".");
	}

	uint32 ScriptData::ReadWord() {
		/* TODO */
		return 0;
	}

	int32  ScriptData::ReadWordSigned() {
		/* TODO */
		return 0;
	}


}
