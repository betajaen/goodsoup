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

	static inline char upper(char m) {
		if (m < 'a' || m > 'z')
			return m;
		m = m - 'a' + 'A';
		return m;
	}

	bool tryGetVideoId(uint8& out_videoNum, const char* string) {
		// Known forms come in as "opening.san"

		for(uint8 i=0;i < MAX_VIDEOS;i++) {
			const char* test = string;
			const char* orig = RESOURCE_VIDEO[i];
			bool foundIt = true;

			while(true) {
				char o = *orig, t = upper(*test);

				debug(GS_THIS, "%c %c", o, t);

				// Original ends with a null char, whilst test ends with a period.
				if (o == 0 || t == '.') {
					break; // Found it.
				}

				if (o != t) {
					foundIt = false;
					break;
				}

				orig++;
				test++;
			}

			if (foundIt == false)
				continue;

			out_videoNum = i;
			return true;

		}

		return false;
	}

	bool tryGetVideoPath(String& out_String, const char* extension, uint8 videoNum) {
		if (videoNum >= MAX_VIDEOS)
			return false;

		String::format(out_String, "%sRESOURCE/%s.%s", GS_GAME_PATH, RESOURCE_VIDEO[videoNum], extension);
		return true;
	}

}
