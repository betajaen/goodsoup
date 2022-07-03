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

#ifndef GS_VERB_H
#define GS_VERB_H

#include "types.h"
#include "profile.h"
#include "debug.h"

namespace gs
{

	struct Verb {
		uint16 placeholder;

		void clear();
	};

	class VerbState {
		Verb _verbs[NUM_VERBS];
	public:
		VerbState();
		~VerbState();

		void clear();

		Verb* getVerb(uint8 idx)  {
			if (idx >= NUM_VERBS) {
				error(GS_THIS, "Verb idx %ld is out of bounds!", idx);
				abort_quit_stop();
				return NULL;
			}

			return &_verbs[idx];
		}

		const Verb* getVerb(uint8 idx) const {
			if (idx >= NUM_VERBS) {
				error(GS_THIS, "Verb idx %ld is out of bounds!", idx);
				abort_quit_stop();
				return NULL;
			}

			return &_verbs[idx];
		}

	};

	extern VerbState* VERBS;


}

#endif