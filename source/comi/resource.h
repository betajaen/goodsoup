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

#ifndef COMI_RESOURCES_H
#define COMI_RESOURCES_H

#include "goodsoup.h"


namespace comi {

	using namespace common;

	class Engine;

	enum ResTypes {
		rtFirst = 1,
		rtRoom = 1,
		rtScript = 2,
		rtCostume = 3,
		rtSound = 4,
		rtInventory = 5,
		rtCharset = 6,
		rtString = 7,
		rtVerb = 8,
		rtActorName = 9,
		rtBuffer = 10,
		rtScaleTable = 11,
		rtTemp = 12,
		rtFlObject = 13,
		rtMatrix = 14,
		rtBox = 15,
		rtObjectName = 16,
		rtRoomScripts = 17,
		rtRoomImage = 18,
		rtImage = 19,
		rtTalkie = 20,
		rtSpoolBuffer = 21,
		rtLast = 21,
		rtNumTypes = 22
	};
	
	const char* resTypeFromId(int id);
	
	enum {
		RF_LOCK = 0x80,
		RF_USAGE = 0x7F,
		RF_USAGE_MAX = RF_USAGE,

		RS_MODIFIED = 0x10
	};

	struct MemBlkHeader {
		uint32 size;
	};

	class ResourceManager {

	public:

		ResourceManager(Engine* vm);
		
		void freeResources();
		bool canStart();
		
		bool isResourceLoaded(int type, int idx) const {
			if (!validateResource("isResourceLoaded", type, idx))
				return false;
			return address[type][idx] != NULL;
		}
		
		bool validateResource(const char* str, int type, int idx) const {
			if (type < rtFirst || type > rtLast || (uint)idx >= (uint)num[type]) {
				error("%s Illegal Glob type %s (%d) num %d", str, resTypeFromId(type), type, idx);
				return false;
			}
			return true;
		}
		
		void nukeResource(int type, int idx);
		
		void allocResTypeData(int id, uint32 tag, int num, const char* name, int mode);

		Engine* _vm;

	public:
		byte mode[rtNumTypes];
		uint16 num[rtNumTypes];
		uint32 tags[rtNumTypes];
		const char* name[rtNumTypes];
		byte** address[rtNumTypes];
	protected:
		byte* flags[rtNumTypes];
		byte* status[rtNumTypes];
	public:
		byte* roomno[rtNumTypes];
		uint32* roomoffs[rtNumTypes];
		uint32* globsize[rtNumTypes];

		uint32 _allocatedSize;
		uint32 _maxHeapThreshold, _minHeapThreshold;
		byte _expireCounter;

	private:

	};
}

#endif