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

#include "../goodsoup.h"
#include "engine.h"
#include "resource.h"
#include "charset.h"
#include "costume.h"
#include "vm.h"
#include "consts.h"
#include "actor.h"

using namespace common;

#define VAR(x) scummVar(x, #x, __FILE__, __LINE__)

namespace comi
{
	Engine* ENGINE = NULL;

	Engine::Engine()
		:	res(),
			vm(),
			_charset(NULL),
			_costumeLoader(NULL),
			_costumeRenderer(NULL),
			_palDirtyMin(0),
			_palDirtyMax(256)
	{
		ENGINE = this;
		_cursor.width = 1;
		_cursor.height = 1;
		_cursor.hotspotX = 0;
		_cursor.hotspotY = 0;
		_cursor.animate = 0;
		_cursor.animateIndex = 0;
		_cursor.state = 0;

		_actors.setSize(NUM_ACTORS);
		_sortedActors.setSize(NUM_ACTORS);

		_verbs.setSize(NUM_VERBS);

		debug("COMI Engine::ctor()");
	}

	Engine::~Engine()
	{
		debug("COMI Engine::dtor()");
		DELETE_OBJECT(_costumeRenderer);
		DELETE_OBJECT(_costumeLoader);
		DELETE_OBJECT(_charset);
		
		_verbs.releaseMem();
		_sortedActors.releaseMem();
		_actors.callDtors();
		_actors.releaseMem();


		res.freeResources();

		debug("COMI Shutdown.");
		ENGINE = NULL;
	}

	bool Engine::canStart()
	{
		debug("COMI Engine::canStart");
		return res.canStart();
	}

	void Engine::init()
	{
		debug("COMI Engine::start()");
		
		_charset = NEW_OBJECT(CharsetRendererNut);
		_costumeLoader = NEW_OBJECT(AkosCostumeLoader);
		_costumeRenderer = NEW_OBJECT(AkosRenderer);

		res.allocResTypeData(rtBuffer, 0, 10, "buffer", 0);
		
		resetScumm();
		sound.reset();
	}

	void Engine::resetScumm()
	{
		uint32 i = 0;
		debug("COMI resetScum()");
		vm.reset();

		initScreens(0, SCREEN_HEIGHT);

		_panManipCounter = 0;
		for (uint32 i = 0; i < 256; i++)
			_roomPalette[i] = i;

		resetPalette();
		setShake(0);
		_cursor.animate = 1;

		// Allocate and Initialize actors
		_sortedActors.zeroMem();
		_actors.zeroMem();
		_actors.callCtors();
		for (i = 0; i < NUM_ACTORS; i++) {
			Actor* actor = _actors.ptr(i);
			actor->_number = i;
			actor->initActor(1);
		}
		
		_verbs.zeroMem();
		_verbs.callCtors();
		
		for (i = 0; i < NUM_VERBS; i++) {
			VerbSlot* verb = _verbs.ptr(i);
			verb->reset();
		}

		VAR(VAR_CAMERA_THRESHOLD_X) = 100;
		VAR(VAR_CAMERA_THRESHOLD_Y) = 70;
		VAR(VAR_CAMERA_ACCEL_X) = 100;
		VAR(VAR_CAMERA_ACCEL_Y) = 100;
		
	}





}
