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

using namespace common;

namespace comi
{
	Engine::Engine()
		:	res(this),
			_charset(NULL),
			_costumeLoader(NULL),
			_costumeRenderer(NULL)
	{
	}

	Engine::~Engine()
	{
		deleteThenNull(_costumeRenderer);
		deleteThenNull(_costumeLoader);
		deleteThenNull(_charset);

		res.freeResources();

		debug("COMI Shutdown.");
	}

	bool Engine::canStart()
	{
		debug("COMI Checking prerequisites.");
		return res.canStart();
	}

	void Engine::start()
	{
		debug("COMI Starting engine.");
		_charset = new CharsetRendererNut(this);
		_costumeLoader = new AkosCostumeLoader(this);
		_costumeRenderer = new AkosRenderer(this);

		res.allocResTypeData(rtBuffer, 0, 10, "buffer", 0);
	}


}
