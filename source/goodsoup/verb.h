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
		uint16 _num;
		uint8  _mode;
		int32  _lineSpacing;

		void clear();
	};

	class VerbState {
		Verb _verbs[NUM_VERBS];
		uint8 _lastVerbIdx;

	public:
		VerbState();
		~VerbState();

		void clear();

		void dumpVerbs();

		Verb* getOrNew(uint16 num);

		Verb* getLastVerbUsed() {
			return &_verbs[_lastVerbIdx];
		}

		Verb* getVerb(uint8 verbNum);

		Verb* findVerbAtXY(int16 x, int16 y);

	};

	extern VerbState* VERBS;


}

#endif