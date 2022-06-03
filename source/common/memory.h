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

#ifndef MEMORY_H
#define MEMORY_H

#include "common/types.h"

namespace common
{
    
	enum MemoryFlags
	{
		MEMF_ANY     = (0UL),
		MEMF_PUBLIC  = (1UL<<0),
		MEMF_CHIP    = (1UL<<1),
		MEMF_CLEAR   = (1UL<<16),
		MEMF_HINT_NEW = (1UL << 24),
		MEMF_HINT_STRING = (1UL << 25)
	};

	void* allocateMemory(uint32 itemCount, uint32 itemSize, int flags);

	void releaseMemory(void* allocation);

	void* reallocateMemory(void* allocation, uint32 itemCount, uint32 itemSize);

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
		void* mem = allocateMemory(1, sizeof(T), MEMF_CLEAR | MEMF_HINT_NEW);
		return new(mem) T();
	}

	template<typename T, typename T0>
	T* newObject(const T0& a0) {
		void* mem = allocateMemory(1, sizeof(T), MEMF_CLEAR | MEMF_HINT_NEW);
		return new(mem) T(a0);
	}

	template<typename T, typename T0, typename T1>
	T* newObject(const T0& a0, const T1& a1) {
		void* mem = allocateMemory(1, sizeof(T), MEMF_CLEAR | MEMF_HINT_NEW);
		return new(mem) T(a0, a1);
	}

	template<typename T, typename T0, typename T1, typename T2>
	T* newObject(const T0& a0, const T1& a1, const T2& a2) {
		void* mem = allocateMemory(1, sizeof(T), MEMF_CLEAR | MEMF_HINT_NEW);
		return new(mem) T(a0, a1, a2);
	}

	template<typename T, typename T0, typename T1, typename T2, typename T3>
	T* newObject(const T0& a0, const T1& a1, const T2& a2, const T3& a3) {
		void* mem = allocateMemory(1, sizeof(T), MEMF_CLEAR | MEMF_HINT_NEW);
		return new(mem) T(a0, a1, a2, a3);
	}

	template<typename T>
	void deleteObject_unchecked(T* object) {
		object->~T();
		releaseMemory(object);
	}

	template<typename T>
	void deleteObject(T*& object) {
		if (object != NULL) {
			object->~T();
			::common::releaseMemory(object);
			object = NULL;
		}
	}

}

#define GS_ArraySize(array)    (sizeof(x)/sizeof(x[0]))

#endif
