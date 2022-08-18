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

#define GS_FILE_NAME "profile"

#include "profile.h"
#include "string.h"

namespace gs
{
	const char* RESOURCE_VIDEO[MAX_VIDEOS] = {
		"BBSAN",
		"CURSERNG",
		"FG010GP",
		"FINALE",
		"KIS030",
		"LAVARIDE",
		"LIFTCRSE",
		"MORESLAW",
		"NEWBOOTS",
		"OPENING",
		"SB010",
		"SB020",
		"SINKSHP",
		"WRECKSAN",
		"ZAP010"
	};


	bool tryGetVideoPath(String& out_String, const char* extension, uint8 videoNum) {
		if (videoNum >= MAX_VIDEOS)
			return false;

		String::format(out_String, "%sRESOURCE/%s.%s", GS_GAME_PATH, RESOURCE_VIDEO[videoNum], extension);
		return true;
	}

}
