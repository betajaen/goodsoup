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

#include "goodsoup.h"
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

	ResourceManager::ResourceManager(Engine* vm) :
	_vm(vm) {
		
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
		_maxHeapThreshold = 0;
		_minHeapThreshold = 0;
		_expireCounter = 0;

	}

	void ResourceManager::freeResources() {

		int i, j;
		for (i = rtFirst; i <= rtLast; i++) {

			debug("COMI FreeResources (%s, %i)", resTypeFromId(i), i);


			for (j = num[i]; --j >= 0;) {
				if (isResourceLoaded(i, j))
					nukeResource(i, j);
			}
			freeMemThenNull(address[i]);
			freeMemThenNull(flags[i]);
			freeMemThenNull(status[i]);
			freeMemThenNull(roomno[i]);
			freeMemThenNull(roomoffs[i]);

			freeMemThenNull(globsize[i]);
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
			freeMem(ptr);
		}

	}

	bool ResourceManager::canStart() {
		bool hasFile = checkFile("data/COMI.LA0");

		if (hasFile == false) {
			warn("Missing data files!");
		}

		return hasFile;
	}


	void ResourceManager::allocResTypeData(int id_, uint32 tag_, int num_, const char* name_, int mode_) {
		debug("allocResTypeData(%s/%s,%s,%d,%d)", resTypeFromId(id_), name_, tag2str(TO_BE_32(tag_), tagTemp), num_, mode_);
		assert(id_ >= 0 && id_ < (int)(ARRAYSIZE(mode)));

		if (num_ >= 8000)
			error("Too many %ss (%d) in directory", name_, num_);
		

		mode[id_] = mode_;
		num[id_] = num_;
		tags[id_] = tag_;
		name[id_] = name_;
		address[id_] = (byte**)allocMem(num_, sizeof(void*), MEMF_CLEAR);
		flags[id_] = (byte*)allocMem(num_, sizeof(byte), MEMF_CLEAR);
		status[id_] = (byte*)allocMem(num_, sizeof(byte), MEMF_CLEAR);

		if (mode_) {
			roomno[id_] = (byte*)allocMem(num_, sizeof(byte), MEMF_CLEAR);
			roomoffs[id_] = (uint32*)allocMem(num_, sizeof(uint32), MEMF_CLEAR);
		}

	}

}
