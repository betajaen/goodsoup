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

#define GS_FILE_NAME "memory"

#include "common/memory.h"
#include "common/debug.h"

#include <stdio.h>	// for checkMem

#define HEADER_MAGIC 0x945FAE6A
#define FOOTER_MAGIC 0xE9394F7F

namespace common
{

	struct MemHeader
	{
		uint32 _allocationId;
		uint32 _flags;
		uint32 _totalSize;
		uint32 _magic;
	};

	struct MemFooter
	{
		uint32 _magic;
		uint32 _allocationId;
	};

	static uint32 sMemAllocatedUser;
	static uint32 sMemAllocatedTotal;


	// Memory


	static uint32 memSize(void* mem)
	{
		if (mem == NULL)
		{
			return 0;
		}

		byte* allocatedMem = ((byte*)mem) - sizeof(MemHeader);

		MemHeader* header = (MemHeader*)allocatedMem;

		if (header->_magic != HEADER_MAGIC)
		{
			return 0;
		}

		return header->_totalSize - sizeof(MemHeader) - sizeof(MemFooter);
	}

	static MemHeader* getHeader(void* allocation) {
		byte* allocatedMem = ((byte*)allocation) - sizeof(MemHeader);
		return (MemHeader*)allocatedMem;
	}

	static MemFooter* getFooter(MemHeader* header) {
		return (MemFooter*)(((byte*)header) + header->_totalSize - sizeof(MemFooter));
	}

	static void checkAllocation(MemHeader* header, MemFooter* footer, const char* from) {
		if (header->_magic != HEADER_MAGIC)
		{
			error(GS_THIS, "(%s, %p, %x, %x, %d, %d) Memory allocation has a corrupted header!", 
				from, header, header->_magic, header->_allocationId, header->_totalSize, header->_flags);
			return;
		}

		if (footer->_magic != FOOTER_MAGIC)
		{
			error(GS_THIS, "(%s, %p) Memory allocation has a corrupted footer!", from, footer);
			return;
		}

		if (header->_allocationId != footer->_allocationId)
		{
			error(GS_THIS, "(%s, %p, %p) Memory allocation has a corrupted header or footer!", from, header, footer);
			return;
		}
	}

	static void* allocateMemoryInternal(uint32 itemCount, uint32 itemSize, int flags) {
		static uint32 sNextAllocationId = 0xBB2F0507;

		uint32 allocationSize, userSize;
		byte* allocatedMem;
		void* userMem;
		MemHeader* header;
		MemFooter* footer;
		uint32 allocationId;

		allocationId = sNextAllocationId += 1;

		userSize = itemCount * itemSize;
		allocationSize = sizeof(MemHeader) + sizeof(MemFooter) + userSize;

		allocatedMem = (byte*)SDL_malloc(allocationSize);

		if (flags & MEMF_CLEAR)
		{
			SDL_memset(allocatedMem, 0, allocationSize);
		}


		header = (MemHeader*)allocatedMem;
		header->_flags = flags;
		header->_allocationId = allocationId;
		header->_totalSize = allocationSize;
		header->_magic = HEADER_MAGIC;

		userMem = (void*)(allocatedMem + sizeof(MemHeader));

		footer = (MemFooter*)(allocatedMem + sizeof(MemHeader) + userSize);
		footer->_magic = FOOTER_MAGIC;
		footer->_allocationId = allocationId;

		sMemAllocatedTotal += allocationSize;
		sMemAllocatedUser += userSize;

		return userMem;
	}


	void* allocateMemory(uint32 itemCount, uint32 itemSize, int flags) {
		
		void* allocatedMem;

		allocatedMem = allocateMemoryInternal(itemCount, itemSize, flags);

		verbose(GS_THIS, "(%p,%d,%d)", allocatedMem, itemCount, itemSize, flags);

		return allocatedMem;
	}


	void* reallocateMemory(void* allocation, uint32 itemCount, uint32 itemSize) {


		if (allocation == NULL)
		{
			warn(GS_THIS, "(0, 0) - reallocating a null pointer. Is this intentional? Calling allocateMemory.");
			return allocateMemory(itemCount, itemSize, MEMF_CLEAR);
		}

		MemHeader* header = getHeader(allocation);
		MemFooter* footer = getFooter(header);
		checkAllocation(header, footer, __FUNCTION__);

		uint32 oldUserSize = header->_totalSize - sizeof(MemHeader) - sizeof(MemFooter);
		uint32 newUserSize = itemCount * itemSize;

		// Exactly the same. Dont reallocate.
		if (oldUserSize == newUserSize) {
			warn(GS_THIS, "(%p,%d,%d) - reallocating a pointer to the same size. Is this intentional?", allocation, oldUserSize, newUserSize);
			return allocation;
		}

		void* newAllocation = allocateMemoryInternal(itemCount, itemSize, MEMF_CLEAR);

		if (newUserSize > oldUserSize) {
			// grow
			SDL_memcpy(newAllocation, allocation, oldUserSize);
		}
		else {
			// shrink
			SDL_memcpy(newAllocation, allocation, newUserSize);
		}

		MemHeader* newHeader = getHeader(allocation);
		MemFooter* newFooter = getFooter(header);

		checkAllocation(newHeader, newFooter, __FUNCTION__);


		sMemAllocatedTotal -= header->_totalSize;
		sMemAllocatedUser -= (header->_totalSize - sizeof(MemHeader) - sizeof(MemFooter));


		SDL_free(header);

		verbose(GS_THIS, "(%p,%d,%d)", allocation, newAllocation, oldUserSize, newUserSize);

		return newAllocation;

	}

	void releaseMemory(void* mem)
	{
		if (mem == NULL)
		{
			verbose(GS_THIS, "(0, 0) - Freeing a null pointer. Is this intentional?");
			return;
		}

		MemHeader* header = getHeader(mem);
		MemFooter* footer = getFooter(header);

		checkAllocation(header, footer, __FUNCTION__);

		verbose(GS_THIS, "(%p, %d, 0x%x) released", mem, header->_totalSize, header->_flags);

		sMemAllocatedTotal -= header->_totalSize;
		sMemAllocatedUser -= (header->_totalSize - sizeof(MemHeader) - sizeof(MemFooter));

		SDL_free(header);
	}

	void clearMemory(void* mem, uint32 size)
	{
		if (mem == NULL)
		{
			error(GS_THIS, "(NULL, ?, ?) Tried to clear a NULL pointer");
			return;
		}
		uint32 maxSize = memSize(mem);

		if (maxSize == 0) {
			error(GS_THIS, "(%p, %d, %d) Tried to clear a corrupted/supported pointer!", mem, size, maxSize);
			return;
		}

		if (size > maxSize) {
			error(GS_THIS, "(%p, %d, %d) Caught out of bounds write!", mem, size, maxSize);
			return;
		}

		SDL_memset(mem, size, 0);
	}

	void clearMemoryNonAllocated(void* mem, uint32 size) {
		if (mem == NULL)
		{
			error(GS_THIS, "(NULL, ?) Tried to clear a NULL pointer");
			return;
		}

		SDL_memset(mem, size, 0);
	}

	void checkMem() {
		printf("D checkMem(%d, %d)\n", sMemAllocatedUser, sMemAllocatedTotal);
	}
}