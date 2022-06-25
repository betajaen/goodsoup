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

#include <proto/exec.h>
#include <proto/dos.h>

#include "../memory.h"
#include "../debug.h"


namespace gs
{

#define HEADER_MAGIC 0x945FAE6A

#if GS_PROTECT_MEMORY == 1
#define FOOTER_MAGIC 0xE9394F7F
#endif

	struct MemHeader
	{
#if GS_PROTECT_MEMORY == 1
		uint32 _magic;
#endif
		uint32 _totalSize;
	};

#if GS_PROTECT_MEMORY == 1
	struct MemFooter
	{
		uint32 _magic;
	};
#endif

	static uint32 sMemAllocatedUser;
	static uint32 sMemAllocatedTotal;
	static uint32 sMemAllocatedHighest;

	// Memory

	static uint32 memSize(void* mem)
	{
		if (mem == NULL)
		{
			return 0;
		}

		byte* allocatedMem = ((byte*)mem) - sizeof(MemHeader);

		MemHeader* header = (MemHeader*)allocatedMem;
#if GS_PROTECT_MEMORY == 1
		if (header->_magic != HEADER_MAGIC)
		{
			return 0;
		}
#endif


#if GS_PROTECT_MEMORY == 1
		return header->_totalSize - sizeof(MemHeader) - sizeof(MemFooter);
#else
		return header->_totalSize - sizeof(MemHeader);
#endif
	}

	static MemHeader* getHeader(void* allocation) {
		byte* allocatedMem = ((byte*)allocation) - sizeof(MemHeader);
		return (MemHeader*)allocatedMem;
	}

#if GS_PROTECT_MEMORY == 1
	static MemFooter* getFooter(MemHeader* header) {
		return (MemFooter*)(((byte*)header) + header->_totalSize - sizeof(MemFooter));
	}
#endif

#if GS_PROTECT_MEMORY == 1
	static void checkAllocation(MemHeader* header, MemFooter* footer, const char* from) {
		if (header->_magic != HEADER_MAGIC)
		{
			error(GS_THIS, "(%s, %p, %x, %d) Memory allocation has a corrupted header!",
				from, header, header->_magic, header->_totalSize);
			return;
		}

		if (footer->_magic != FOOTER_MAGIC)
		{
			error(GS_THIS, "(%s, %p) Memory allocation has a corrupted footer!", from, footer);
			return;
		}
	}
#endif

	static void* allocateMemoryInternal(uint32 itemCount, uint32 itemSize, int flags) {

		uint32 allocationSize, userSize;
		byte* allocatedMem;
		void* userMem;
		MemHeader* header;

#if GS_PROTECT_MEMORY == 1
		MemFooter* footer;
#endif

		userSize = itemCount * itemSize;

#if GS_PROTECT_MEMORY == 1
		allocationSize = sizeof(MemHeader) + sizeof(MemFooter) + userSize;
#else
		allocationSize = sizeof(MemHeader) + userSize;
#endif

		allocatedMem = (byte*) AllocMem(allocationSize, flags);

		header = (MemHeader*)allocatedMem;
		header->_totalSize = allocationSize;
#if GS_PROTECT_MEMORY == 1
		header->_magic = HEADER_MAGIC;
#endif

		userMem = (void*)(allocatedMem + sizeof(MemHeader));

#if GS_PROTECT_MEMORY == 1
		footer = (MemFooter*)(allocatedMem + sizeof(MemHeader) + userSize);
		footer->_magic = FOOTER_MAGIC;
#endif
		sMemAllocatedTotal += allocationSize;
		sMemAllocatedUser += userSize;

		if (sMemAllocatedTotal > sMemAllocatedHighest) {
			sMemAllocatedHighest = sMemAllocatedTotal;
		}

		return userMem;
	}


	void* allocateMemory(uint32 itemCount, uint32 itemSize, int flags) {

		void* allocatedMem;

		allocatedMem = allocateMemoryInternal(itemCount, itemSize, flags);
#if GS_TEST==3
		verbose(GS_THIS, "(%p,%d,%d,%d)", allocatedMem, itemCount, itemSize, flags);
#endif
		return allocatedMem;
	}


	void* reallocateMemory(void* allocation, uint32 itemCount, uint32 itemSize) {


		if (allocation == NULL)
		{
			warn(GS_THIS, "(0, 0) - reallocating a null pointer. Is this intentional? Calling allocateMemory.");
			return allocateMemory(itemCount, itemSize, MF_Clear);
		}

		MemHeader* header = getHeader(allocation);

#if GS_PROTECT_MEMORY == 1
		MemFooter* footer = getFooter(header);
		checkAllocation(header, footer, __FUNCTION__);
#endif

#if GS_PROTECT_MEMORY == 1
		uint32 oldUserSize = header->_totalSize - sizeof(MemHeader) - sizeof(MemFooter);
#else
		uint32 oldUserSize = header->_totalSize - sizeof(MemHeader);
#endif
		uint32 newUserSize = itemCount * itemSize;

		// Exactly the same. Dont reallocate.
		if (oldUserSize == newUserSize) {
			warn(GS_THIS, "(%p,%d,%d) - reallocating a pointer to the same size. Is this intentional?", allocation, oldUserSize, newUserSize);
			return allocation;
		}

		void* newAllocation = allocateMemoryInternal(itemCount, itemSize, MF_Clear);

		if (newUserSize > oldUserSize) {
			// grow
			CopyMem(allocation, newAllocation, oldUserSize);
		}
		else {
			// shrink
			CopyMem(allocation, newAllocation, newUserSize);
		}

#if GS_PROTECT_MEMORY == 1
		MemHeader* newHeader = getHeader(allocation);
		MemFooter* newFooter = getFooter(header);
		checkAllocation(newHeader, newFooter, __FUNCTION__);
#endif


		sMemAllocatedTotal -= header->_totalSize;

#if GS_PROTECT_MEMORY == 1
		sMemAllocatedUser -= (header->_totalSize - sizeof(MemHeader) - sizeof(MemFooter));
#else
		sMemAllocatedUser -= (header->_totalSize - sizeof(MemHeader));
#endif

		FreeMem(header, header->_totalSize);
#if GS_TEST==3
		verbose(GS_THIS, "(%p,%d,%d)", allocation, newAllocation, oldUserSize, newUserSize);
#endif
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
#if GS_PROTECT_MEMORY == 1
		MemFooter* footer = getFooter(header);

		checkAllocation(header, footer, __FUNCTION__);
#endif
#if GS_TEST==3
		verbose(GS_THIS, "(%p, %d) released", mem, header->_totalSize);
#endif
		sMemAllocatedTotal -= header->_totalSize;
#if GS_PROTECT_MEMORY == 1
		sMemAllocatedUser -= (header->_totalSize - sizeof(MemHeader) - sizeof(MemFooter));
#else
		sMemAllocatedUser -= (header->_totalSize - sizeof(MemHeader));
#endif

		FreeMem(header, header->_totalSize);
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

		/* TODO This will be slow. Have cases for when size is %2 or %4 and clear by shorts or ints */
		byte* bytes = (byte*)mem;
		for (uint32 i = 0; i < size; i++) {
			bytes[i] = 0;
		}
	}

	void clearMemoryNonAllocated(void* mem, uint32 size) {
		if (mem == NULL)
		{
			error(GS_THIS, "(NULL, ?) Tried to clear a NULL pointer");
			return;
		}

		byte* bytes = (byte*)mem;
		for (uint32 i = 0; i < size; i++) {
			bytes[i] = 0;
		}
	}


	uint32 getHeapSize() {
		return sMemAllocatedUser;
	}

	void checkMem() {
		debug_write_str("Memory Stats:\nAllocation/Overhead = ");
		debug_write_unsigned_int(sMemAllocatedUser >> 10);
		debug_write_str(" / ");
		debug_write_unsigned_int((sMemAllocatedTotal - sMemAllocatedUser) >> 10);
		debug_write_str(" KiB\n");
		
		if (sMemAllocatedTotal > 0) {
			debug_write_str(" ** Leaks Detected!\n");
		}

		debug_write_str("Highest = ");
		debug_write_unsigned_int(sMemAllocatedHighest >> 10);
		debug_write_str(" KiB\n");
	}
}