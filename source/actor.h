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

#ifndef GS_ACTOR_H
#define GS_ACTOR_H

#include "types.h"
#include "memory.h"
#include "profile.h"
#include "array.h"
#include "debug.h"

namespace gs
{

	extern uint8 CURRENT_ACTOR;

	struct ActorData {

		uint16 _num;
		uint16 _roomNum;
		int16 _x, _y, _w, _h;
		bool _bIsVisible;

		void clear();
	};


	class ActorState {
		FixedArray<ActorData, NUM_ACTORS, uint8> _actors;

	public:

		ActorState();
		~ActorState();

		void clear();

		ActorData* getActor() {
			return getActor(CURRENT_ACTOR);
		}

		ActorData* getActor(uint8 actorNum)  {
			if (actorNum == 0) {
				warn(GS_THIS, "getActor is 0");
				return NULL;
			}
			if (actorNum >= NUM_ACTORS) {
				warn(GS_THIS, "getActor %ld is out of bounds!", actorNum);
				return NULL;
			}

			return &_actors[actorNum];
		}

		bool  putActorAtXY(uint8 actorNum, uint16 roomNum, int16 x, int16 y);

	};

	extern ActorState* ACTORS;

}


#endif
