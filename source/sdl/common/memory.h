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

#ifndef COMMON_MEMORY_H
#define COMMON_MEMORY_H

#include "types.h"

namespace common
{

	enum MemoryFlags
	{
		MEMF_ANY     = (0UL),
		MEMF_PUBLIC  = (1UL<<0),
		MEMF_CHIP    = (1UL<<1),
		MEMF_CLEAR   = (1UL<<16),
		MEMF_CPP_NEW = (1UL << 24)
	};

	void* allocateMemory(uint32 itemCount, uint32 itemSize, int flags);

	void releaseMemory(void* allocation);

	template<typename T>
	inline void releaseMemoryChecked(T*& allocation)
	{
		if (allocation) {
			releaseMemory(allocation);
			allocation = NULL;
		}
	}

	void clearMemory(void* allocation, uint32 size);

	void clearMemoryNonAllocated(void* allocation, uint32 size);

	template<typename T>
	T* newObject() {
		void* mem = allocateMemory(1, (uint32)sizeof(T), MEMF_CLEAR | MEMF_CPP_NEW);
		new(mem) T();
		return (T*)mem;
	}

	template<typename T, typename TA0>
	T* newObject(TA0 a0) {
		void* mem = allocateMemory(1, (uint32)sizeof(T), MEMF_CLEAR | MEMF_CPP_NEW);
		new(mem) T(a0);
		return (T*)mem;
	}

	template<typename T, typename TA0, typename TA1>
	T* newObject(TA0 a0, TA1 a1) {
		void* mem = allocateMemory(1, (uint32)sizeof(T), MEMF_CLEAR | MEMF_CPP_NEW);
		new(mem) T(a0, a1);
		return (T*)mem;
	}

	template<typename T, typename TA0, typename TA1, typename TA2>
	T* newObject(TA0 a0, TA1 a1, TA2 a2) {
		void* mem = allocateMemory(1, (uint32)sizeof(T), MEMF_CLEAR | MEMF_CPP_NEW);
		new(mem) T(a0, a1, a2);
		return (T*)mem;
	}

	template<typename T, typename TA0, typename TA1, typename TA2, typename TA3>
	T* newObject(TA0 a0, TA1 a1, TA2 a2, TA3 a3) {
		void* mem = allocateMemory(1, (uint32)sizeof(T), MEMF_CLEAR | MEMF_CPP_NEW);
		new(mem) T(a0, a1, a2, a3);
		return (T*)mem;
	}


	template<typename T>
	void deleteObject(T* object) {
		object->~T();
		::common::releaseMemory(object);
	}

	template<typename T>
	void deleteObjectChecked(T*& object) {
		if (object != NULL) {
			object->~T();
			::common::releaseMemory(object);
			object = NULL;
		}
	}

}

#define NEW_OBJECT(T, ...) ::common::newObject<T>(__VA_ARGS__)
#define DELETE_OBJECT(OBJ) ::common::deleteObjectChecked(OBJ)
#define NEW_MEMORY(COUNT, SIZE, FLAGS) ::common::allocateMemory(COUNT, SIZE, FLAGS)
#define DELETE_MEMORY(ALLOCATION) ::common::releaseMemoryChecked(ALLOCATION);

#define ARRAYSIZE(X) SDL_arraysize(X)

#endif
