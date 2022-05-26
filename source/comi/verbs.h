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

#ifndef COMI_VERBS_H
#define COMI_VERBS_H

#include "common/types.h"
#include "common/rect.h"
#include "consts.h"

using namespace common;

namespace comi {

	enum {
		kTextVerbType = 0,
		kImageVerbType = 1
	};

	struct VerbSlot {
		Rect curRect;
		Rect oldRect;
		uint16 verbid;
		uint8 color, hicolor, dimcolor, bkcolor, type;
		uint8 charset_nr, curmode;
		uint16 saveid;
		uint8 key;
		bool center;
		uint8 prep;
		uint16 imgindex;

		inline void reset()
		{
			verbid = 0;
			curRect.right = SCREEN_WIDTH - 1;
			oldRect.left = -1;
			type = 0;
			color = 2;
			hicolor = 0;
			charset_nr = 1;
			curmode = 0;
			saveid = 0;
			center = 0;
			key = 0;
		}
	};
}

#endif