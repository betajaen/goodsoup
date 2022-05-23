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

namespace common
{
	#define HEADER_MAGIC 0x945FAE6A
	#define FOOTER_MAGIC 0xE9394F7F
	
	struct MemHeader
	{
		uint32 _size;
		uint32 _magic;
	};

	struct MemFooter
	{
		uint32 _magic;
		uint32 _size;
	};

	// Memory
	void* allocMem(uint32 count, uint32 size, uint32 flags)
	{
		uint32 totalSize, userSize;
		void* allocatedMem;
		void* userMem;
		MemHeader* header;
		MemFooter* footer;

		userSize = count * size;
		totalSize = sizeof(MemHeader) + sizeof(MemFooter) + userSize;
		
		allocatedMem = SDL_malloc(totalSize);

		verbose("allocMem(%d,%d,%d,%d,%d,%p)", count, size, userSize, totalSize, flags, allocatedMem);

		if (flags & MEMF_CLEAR)
		{
			SDL_memset(allocatedMem, totalSize, 0);
		}

		header = (MemHeader*)allocatedMem;
		header->_size = (count * size);
		header->_magic = HEADER_MAGIC;

		userMem = (void*)(header + 1);

		footer = (MemFooter*)(((byte*)userMem) + userSize);
		footer->_magic = FOOTER_MAGIC;
		footer->_size = (count * size);

		verbose("User=%p", userMem);

		return userMem;
	}

	void freeMem(void* mem)
	{
		if (mem == NULL)
		{
			verbose("freeMem(NULL)!");
			return;
		}

		verbose("freeMem(%p, ?)", mem);

		MemHeader* header = ((MemHeader*)mem)-1;

		if (header->_magic != HEADER_MAGIC)
		{
			error("freeMem(%p) Memory allocation has a corrupted header!");
			return;
		}

		MemFooter* footer = (MemFooter*)(((byte*)mem) + (header->_size));

		if (header->_magic != FOOTER_MAGIC)
		{
			error("freeMem(%p) Memory allocation has a corrupted footer!");
			return;
		}

		if (header->_size != footer->_size)
		{
			error("freeMem(%p) Memory allocation has a corrupted header or footer!");
			return;
		}

		verbose("freeMem(%p, %d)", mem, header->_size);

		SDL_free(header);
	}

	void zeroMem(void* mem, uint32 size)
	{
		verbose("zeroMem(%p,%d)", mem, size);
		SDL_memset(mem, size, 0);
	}

}