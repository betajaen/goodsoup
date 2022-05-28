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

#define GS_FILE_NAME "common/memory"

#include "memory.h"
#include "debug.h"

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
	void* allocateMemory(uint32 itemCount, uint32 itemSize, int flags) {
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

		gs_verbose("(%d,%d,%d,%d,%d,%p)", itemCount, itemSize, userSize, allocationSize, flags, allocatedMem);

		return (void*)userMem;
	}

	void releaseMemory(void* mem)
	{
		if (mem == NULL)
		{
			gs_verbose("(0, 0) - Freeing a null pointer. Is this intentional?");
			return;
		}

		byte* allocatedMem = ((byte*)mem) - sizeof(MemHeader);

		MemHeader* header = (MemHeader*)allocatedMem;

		if (header->_magic != HEADER_MAGIC)
		{
			gs_error("(%p) Memory allocation has a corrupted header!");
			return;
		}

		MemFooter* footer = (MemFooter*)(allocatedMem + header->_totalSize - sizeof(MemFooter));

		if (footer->_magic != FOOTER_MAGIC)
		{
			gs_error("(%p) Memory allocation has a corrupted footer!");
			return;
		}

		if (header->_allocationId != footer->_allocationId)
		{
			gs_error("(%p) Memory allocation has a corrupted header or footer!");
			return;
		}

		gs_verbose("(%p, %d, 0x%x) released", mem, header->_totalSize, header->_flags);

		sMemAllocatedTotal -= header->_totalSize;
		sMemAllocatedUser -= (header->_totalSize - sizeof(MemHeader) - sizeof(MemFooter));

		SDL_free(header);
	}

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

	void clearMemory(void* mem, uint32 size)
	{
		if (mem == NULL)
		{
			error("(NULL, ?, ?) Tried to clear a NULL pointer");
			return;
		}
		uint32 maxSize = memSize(mem);

		if (maxSize == 0) {
			error("(%p, %d, %d) Tried to clear a corrupted/supported pointer!", mem, size, maxSize);
			return;
		}

		if (size > maxSize) {
			error("(%p, %d, %d) Caught out of bounds write!", mem, size, maxSize);
			return;
		}

		SDL_memset(mem, size, 0);
	}

	void checkMem() {
		printf("D checkMem(%d, %d)\n", sMemAllocatedUser, sMemAllocatedTotal);
	}
}