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
#include "resource.h"

using namespace common;

#ifndef CHECK_HEAP
#define CHECK_HEAP
#endif

namespace comi
{

	static char tagTemp[5];

	const char* resTypeFromId(int id) {
		
		switch (id) {
		case rtRoom:
			return "Room";
		case rtScript:
			return "Script";
		case rtCostume:
			return "Costume";
		case rtSound:
			return "Sound";
		case rtInventory:
			return "Inventory";
		case rtCharset:
			return "Charset";
		case rtString:
			return "String";
		case rtVerb:
			return "Verb";
		case rtActorName:
			return "ActorName";
		case rtBuffer:
			return "Buffer";
		case rtScaleTable:
			return "ScaleTable";
		case rtTemp:
			return "Temp";
		case rtFlObject:
			return "FlObject";
		case rtMatrix:
			return "Matrix";
		case rtBox:
			return "Box";
		case rtObjectName:
			return "ObjectName";
		case rtRoomScripts:
			return "RoomScripts";
		case rtRoomImage:
			return "RoomImage";
		case rtImage:
			return "Image";
		case rtTalkie:
			return "Talkie";
		case rtSpoolBuffer:
			return "SpoolBuffer";
		case rtNumTypes:
			return "NumTypes";
		default:
			return "Unknown";
		}
	}

	ResourceManager::ResourceManager()
	{
		
		int i;
		for (i = rtFirst; i <= rtLast; i++) {
			mode[i] = 0;
			num[i] = 0;
			tags[i] = 0;
			name[i] = NULL;
			address[i] = NULL;
			flags[i] = NULL;
			status[i] = NULL;
			roomno[i] = NULL;
			roomoffs[i] = NULL;
			globsize[i] = NULL;
		}

		_allocatedSize = 0;
		_maxHeapThreshold = 6 * 1024 * 1024;
		_minHeapThreshold = 400000;
		_expireCounter = 0;

	}

	void ResourceManager::freeResources() {

		uint32 type, idx;

		for (type = rtFirst; type <= rtLast; type++) {
			idx = num[type];

			debug("COMI ResourceManager::freeResources/1(%s, %i, %i)", resTypeFromId(type), type, idx);

			if (idx > 0) {
				idx--;
				while (idx) {

					void* ptr = address[type][idx];

					if (isResourceLoaded(type, idx)) {
						debug("COMI ResourceManager::freeResources/2(%i, %i, %p)", type, idx, ptr);


						nukeResource(type, idx);
					}

					idx--;
				}
			}

			freeMemThenNull(address[type]);
			freeMemThenNull(flags[type]);
			freeMemThenNull(status[type]);
			freeMemThenNull(roomno[type]);
			freeMemThenNull(roomoffs[type]);

			freeMemThenNull(globsize[type]);
		}
	}

	void ResourceManager::nukeResource(int type, int idx) {

		byte* ptr;

		CHECK_HEAP
			if (!address[type])
				return;

		assert(idx >= 0 && idx < num[type]);

		ptr = address[type][idx];
		if (ptr != NULL) {
			debug("COMI nukeResource(%s,%d,%p)", resTypeFromId(type), idx, ptr);
			address[type][idx] = 0;
			flags[type][idx] = 0;
			status[type][idx] &= ~RS_MODIFIED;
			_allocatedSize -= ((MemBlkHeader*)ptr)->size;

			debug("COMI nukeResource(%i,%i,%p)", type, idx, ptr);
			DELETE_MEMORY(ptr);
		}

	}

	bool ResourceManager::canStart() {
		bool hasFile = checkFile("data/COMI.LA0");

		if (hasFile == false) {
			warn("Missing data files!");
		}

		return hasFile;
	}


	void ResourceManager::allocResTypeData(int type, uint32 tag_, int num_, const char* name_, int mode_) {
		debug("allocResTypeData(%s/%s,%s,%d,%d)", resTypeFromId(type), name_, tag2str(TO_BE_32(tag_), tagTemp), num_, mode_);
		assert(type >= 0 && type < (int)(ARRAYSIZE(mode)));

		if (num_ >= 8000)
			error("Too many %ss (%d) in directory", name_, num_);
		

		mode[type] = mode_;
		num[type] = num_;
		tags[type] = tag_;
		name[type] = name_;
		address[type] = (byte**) NEW_MEMORY(num_, sizeof(void*), MEMF_CLEAR);
		flags[type] = (byte*)NEW_MEMORY(num_, sizeof(byte), MEMF_CLEAR);
		status[type] = (byte*)NEW_MEMORY(num_, sizeof(byte), MEMF_CLEAR);

		if (mode_) {
			roomno[type] = (byte*)NEW_MEMORY(num_, sizeof(byte), MEMF_CLEAR);
			roomoffs[type] = (uint32*)NEW_MEMORY(num_, sizeof(uint32), MEMF_CLEAR);
		}

	}

}
