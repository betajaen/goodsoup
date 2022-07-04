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

	void ActorData::initialiseDefault() {
		_elevation = 0;
		_w = 24;
		_talkColour = 15;
		_talkX = 0;
		_talkY = 0;
		_boxScaleX = 0xFF;
		_boxScaleY = 0xFF;
		_scaleX = 0xFF;
		_scaleY = 0xFF;
		_charset = 0;
		for(uint8 i=0; i < 16;i++) {
			_sounds[i] = 0;
		}
		_sound = 0;
		_facing = 0;
		_targetFacing = 0;
		/* TODO: Stop Actor Moving (Script) */
		/* TODO: Set Actor Walk Speed */
		_bIgnoreBoxes = false;
		_forceClip = 100;
		_bIgnoreTurns = false;
		_talkFrequency = 256;
		_talkPan = 64;
		_talkVolume = 127;
		/* TODO: Reset Frames */
		_walkScript = 0;
		_talkScript = 0;
		/* TODO: Class Data */
	}

	void ActorData::clear() {
		_x = 0;
		_y = 0;
		_w = 0;
		_h = 0;
		_roomNum = 0;
		_bIsVisible = false;
		_elevation = 0;
		_talkColour = 0;
		_talkX = 0;
		_talkY = 0;
		_boxScaleX = 0;
		_boxScaleY = 0;
		_scaleX = 0;
		_scaleY = 0;
		_charset = 0;
		for(uint8 i=0; i < 16;i++) {
			_sounds[i] = 0;
		}
		_sound = 0;
		_facing = 0;
		_targetFacing = 0;
		_bIgnoreBoxes = false;
		_forceClip = 0;
		_bIgnoreTurns = false;
		_talkFrequency = 0;
		_talkPan = 0;
		_talkVolume = 0;
		_walkScript = 0;
		_talkScript = 0;
	}

}
