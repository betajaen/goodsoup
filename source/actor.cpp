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

#define GS_FILE_NAME "actor"

#include "actor.h"

namespace gs
{
	ActorState* ACTORS = NULL;
	uint8 CURRENT_ACTOR = 0;

	ActorState::ActorState() {
		for(uint8 i=0;i < NUM_ACTORS;i++) {
			ActorData& actor = _actors[i];
			actor._num = i;
		}
	}

	ActorState::~ActorState() {
		clear();
	}

	void ActorState::clear() {
		for(uint8 i=0;i < NUM_ACTORS;i++) {
			ActorData& actor = _actors[i];
			actor.clear();
		}
	}

	bool  ActorState::putActorAtXY(uint8 actorNum, uint16 roomNum, int16 x, int16 y) {
		ActorData* actor = getActor(actorNum);
		if (actor == NULL) {
			return false;
		}

		actor->_x = x;
		actor->_y = y;
		// Cases of 0xFF or 0x7FFF which means current room.
		if (roomNum < NUM_ROOMS) {
			actor->_roomNum = roomNum;
		}
		return true;
	}

	void ActorData::clear() {
		_x = 0;
		_y = 0;
		_w = 0;
		_h = 0;
		_roomNum = 0;
		_bIsVisible = false;
	}

}
