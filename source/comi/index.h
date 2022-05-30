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

#ifndef COMI_INDEX_H
#define COMI_INDEX_H

#include "common/types.h"
#include "common/buffer.h"
#include "common/file.h"

#include "resource.h"
#include "constants.h"

using namespace common;

namespace comi
{
	class Index;

	extern Index* INDEX;

	class Index
	{
	public:

		Index();
		~Index();

		bool readFromFile(const char* path);

		bool loadScript(uint16 id, Buffer<byte>& data);

	private:

		struct ArraySpec
		{
			uint16 num, a, b;
		};

		char						_roomNames[NUM_ROOMS + 1][10];
		ResourceList<NUM_ROOMS>		_roomsResources;
		ResourceList<NUM_ROOMS>		_roomsScriptsResources;
		ResourceList<NUM_SCRIPTS>	_scriptsResources;
		ResourceList<NUM_SOUNDS>	_soundsResources;
		ResourceList<NUM_COSTUMES>	_costumesResources;
		ResourceList<NUM_CHARSETS>	_charsetResources;
		ObjectTable					_objectTable;
		ArraySpec					_arraySpec[NUM_AARY];

	};
}

#endif