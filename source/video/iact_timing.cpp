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

#define GS_FILE_NAME "IACT_Timing"

#include "iact_timing.h"
#include "../disk.h"

namespace gs
{

	bool readIACTTiming(DiskReader& reader, TagPair& tag, IACTTiming& timing) {
		uint16 code = reader.readUInt16LE();
		uint16 flags = reader.readUInt16LE();

		if (code != 8 && flags != 46)
			return false;

		reader.skip(6);

		timing.currentFrame = reader.readUInt16LE();
		timing.totalFrames = reader.readUInt16LE();

		debug(GS_THIS, "Frame %ld of %ld", timing.currentFrame, timing.totalFrames);

		return true;
	}

}
