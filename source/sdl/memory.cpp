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

#include "required.h"
#include <stdio.h>	// for checkMem

namespace common
{
	#define HEADER_MAGIC 0x945FAE6A
	#define FOOTER_MAGIC 0xE9394F7F
	
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
	void* allocMem(uint32 itemCount, uint32 itemSize, int flags) {
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
		
		allocatedMem = (byte*) SDL_malloc(allocationSize);

		verbose("allocMem(%d,%d,%d,%d,%d,%p)", itemCount, itemSize, userSize, allocationSize, flags, allocatedMem);

		if (flags & MEMF_CLEAR)
		{
			SDL_memset(allocatedMem, 0, allocationSize);
		}


		header = (MemHeader*)allocatedMem;
		header->_flags = flags;
		header->_allocationId = allocationId;
		header->_totalSize = allocationSize;
		header->_magic = HEADER_MAGIC;

		userMem = (void*) (allocatedMem + sizeof(MemHeader));

		footer = (MemFooter*)(allocatedMem + sizeof(MemHeader) + userSize);
		footer->_magic = FOOTER_MAGIC;
		footer->_allocationId = allocationId;

		verbose("allocMem(return,%p)", userMem);

		sMemAllocatedTotal += allocationSize;
		sMemAllocatedUser += userSize;

		return (void*) userMem;
	}

	void freeMem(void* mem)
	{
		if (mem == NULL)
		{
			verbose("freeMem(0, 0)");
			return;
		}

		byte* allocatedMem = ((byte*) mem) - sizeof(MemHeader);

		MemHeader* header = (MemHeader*)allocatedMem;

		if (header->_magic != HEADER_MAGIC)
		{
			error("freeMem(%p) Memory allocation has a corrupted header!");
			return;
		}

		MemFooter* footer = (MemFooter*) (allocatedMem + header->_totalSize - sizeof(MemFooter));

		if (footer->_magic != FOOTER_MAGIC)
		{
			error("freeMem(%p) Memory allocation has a corrupted footer!");
			return;
		}

		if (header->_allocationId != footer->_allocationId)
		{
			error("freeMem(%p) Memory allocation has a corrupted header or footer!");
			return;
		}

		verbose("freeMem(%p, %d, 0x%x)", mem, header->_totalSize, header->_flags);

		sMemAllocatedTotal -= header->_totalSize;
		sMemAllocatedUser -= (header->_totalSize - sizeof(MemHeader) - sizeof(MemFooter));

		SDL_free(header);
	}

	void zeroMem(void* mem, uint32 size)
	{
		verbose("zeroMem(%p,%d)", mem, size);
		SDL_memset(mem, size, 0);
	}

	void checkMem() {
		printf("D checkMem(%d, %d)\n", sMemAllocatedUser, sMemAllocatedTotal);
	}
}