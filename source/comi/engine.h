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

#include "goodsoup.h"
#include "resource.h"


namespace comi {

	class ResourceManager;
	class CharsetRendererNut;
	class AkosRenderer;
	class AkosCostumeLoader;

	class Engine {

	public:

		Engine();
		~Engine();

		bool canStart();
		void start();

		ResourceManager res;

	private:

		CharsetRendererNut* _charset;
		AkosRenderer* _costumeRenderer;
		AkosCostumeLoader* _costumeLoader;
	};
}

#endif