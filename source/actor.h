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
#include "containers.h"
#include "debug.h"

namespace gs
{

#define MAX_ACTOR_VARS 27

	extern uint8 CURRENT_ACTOR;

	enum ActorMoveFlags {
		AMF_None = 0,
		AMF_NewLeg = 1,
		AMF_InLeg = 2,
		AMF_Turn = 4,
		AMF_LastLeg = 8,
		AMF_Frozen = 0x80
	};

	struct ActorData {

		uint16 _num;
		uint16 _roomNum;
		uint16 _costumeNum;
		int16 _x, _y, _w, _h, _elevation;
		int16 _layer;
		int16 _talkX, _talkY;
		uint8 _walkSpeedX, _walkSpeedY;
		uint8 _talkColour;
		uint8 _bIsVisible;
		uint16 _boxScaleX, _boxScaleY, _scaleX, _scaleY;
		uint8 _charset;
		uint16 _sounds[16];
		uint8 _sound;
		uint16 _facing, _targetFacing;
		uint8 _bIgnoreBoxes;
		uint8 _forceClip;
		uint8 _bIgnoreTurns;
		uint16 _talkFrequency;
		uint8 _talkPan;
		uint8 _talkVolume;
		uint16 _walkScript;
		uint16 _talkScript;
		uint8 _moving;
		uint8 _frame;
		uint16 _costume;
		uint8 _walkBox;
		bool _needRedraw;
		byte _initFrame;
		byte _walkFrame;
		byte _standFrame;
		byte _talkStartFrame;
		byte _talkStopFrame;
		byte _animationSpeed;
		byte _animationProgress;
		uint8 _shadowMode;
		int32 _vars[MAX_ACTOR_VARS];

		void setScale(int16 x, int16 y) {
			if (x != -1) {
				_boxScaleX = x;
			}
			if (y != -1) {
				_boxScaleY = y;
			}
			_needRedraw = true;
		}

		void initialiseDefault();
		void clear();
		void setCostume(uint16 costumeNum);
		void setWalkSpeed(int32 x, int32 y);
		void setAnimationDefault();
		void setAnimationSpeed(uint8 speed);
		void setElevation(int16 elevation);

		void setPalette(uint8 paletteIdx, uint16 paletteNum);

		void setVar(uint8 idx, int32 value);
		int32 getVar(uint8 idx);

		void newDefault();

		void stopMoving();

		void startAnimation(uint8 frame);

		void setDirection(int16 angle);

		void turnToDirection(int16 angle);

		void animate(uint32 animation);
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
