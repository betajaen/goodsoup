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

#ifndef COMI_ENGINE_H
#define COMI_ENGINE_H

#include "../goodsoup.h"
#include "resource.h"
#include "vm.h"

namespace comi {

	class Engine;
	class ResourceManager;
	class CharsetRendererNut;
	class AkosRenderer;
	class AkosCostumeLoader;
	class Actor;
	class Vm;

	extern Engine* ENGINE;

	class Engine {

	public:

		friend class Vm;

		Engine();
		~Engine();

		bool canStart();
		void start();

		ResourceManager res;
		Vm vm;

	private:

		struct {
			int hotspotX, hotspotY, width, height;
			byte animate, animateIndex;
			int8 state;
		} _cursor;

		void setupScummVars();
		void setupOpcodes();

		void resetScumm();

		void initScreens(int b, int h) { /* TODO */ }

		void setShake(int mode) { /* TODO */ }

		inline void resetPalette()
		{
			setDirtyColours(0, 255);
		}

		inline void setDirtyColours(uint16 min, uint16 max)
		{
			if (min < _palDirtyMin)
				_palDirtyMin = min;
			if (max > _palDirtyMax)
				_palDirtyMax = max;
		}

		CharsetRendererNut* _charset;
		AkosRenderer* _costumeRenderer;
		AkosCostumeLoader* _costumeLoader;

		uint32 _tempMusic;
		uint16 _panManipCounter;
		byte   _roomPalette[256];
		uint16 _palDirtyMin, _palDirtyMax;


	};
}

#endif