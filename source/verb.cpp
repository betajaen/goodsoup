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

#define GS_FILE_NAME "verb"

#include "verb.h"


namespace gs
{
	VerbState* VERBS = NULL;

	VerbState::VerbState() {
	}

	VerbState::~VerbState() {
		clear();
	}

	Verb* VerbState::getOrNew(uint16 verbNum) {

		for(uint16 i=0;i < NUM_VERBS;i++) {
			Verb* verb = &_verbs[i];

			if (verb->_num == verbNum) {
				_lastVerbIdx = i;
				return verb;
			}
		}

		for(uint16 i=0;i < NUM_VERBS;i++) {
			Verb* verb = &_verbs[i];
			if (verb->_num == 0) {
				verb->_num = verbNum;
				_lastVerbIdx = i;
				return verb;
			}
		}

		error(GS_THIS, "Number of verbs exceeded!");
		abort_quit_stop();

		return NULL;
	}

	Verb* VerbState::getVerb(uint8 verbNum) {
		for(uint16 i=0;i < NUM_VERBS;i++) {
			Verb* verb = &_verbs[i];

			if (verb->_num == verbNum) {
				_lastVerbIdx = i;
				return verb;
			}
		}

		return NULL;
	}

	void VerbState::clear() {
		for(uint8 i=0;i < NUM_VERBS;i++) {
			Verb* verb = &_verbs[i];
			verb->clear();
		}
		_lastVerbIdx = 0;
	}

	void Verb::clear() {
		_num = 0;
		_mode = 0;
		_lineSpacing = 0;
	}

}
