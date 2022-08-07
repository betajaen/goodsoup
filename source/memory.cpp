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

#include "memory.h"
#include "debug.h"

#if defined(GS_AMIGA)
#include <proto/exec.h>
#endif

#if defined(GS_SDL)
#include <SDL2/SDL.h>
#endif

#include "list.h"

namespace gs
{
    struct CheckedMemoryHeader;

	List<CheckedMemoryHeader> sCheckedAllocations;
	uint32 sMemoryAllocated = 0;

	struct TrackedMemoryHeader
	{
		uint32 allocationSize;
	} __attribute__ ((packed));

	struct CheckedMemoryHeader
	{
		uint32 allocationSize;
		uint32 comment;
		CheckedMemoryHeader* next, *prev;
		uint32 _guard_begin;
	} __attribute__ ((packed));

	struct CheckedMemoryFooter
	{
		uint32 _guard_end;
	} __attribute__ ((packed));

	static CheckedMemoryHeader* _getCheckedMemoryHeader(void* allocation) {
		return ( (CheckedMemoryHeader*) allocation) - 1;
	}

	static TrackedMemoryHeader* _getTrackedMemoryHeader(void* allocation) {
		return ( (TrackedMemoryHeader*) allocation) - 1;
	}

    static bool _commentIsTag(const char* tagName) {
        if (tagName[0] < 'A')
            return false;
        if (tagName[0] > 'Z')
            return false;
        if (tagName[1] < 'A')
            return false;
        if (tagName[1] > 'Z')
            return false;
        if (tagName[2] < 'A')
            return false;
        if (tagName[2] > 'Z')
            return false;
        if (tagName[3] < 'A')
            return false;
        if (tagName[3] > 'Z')
            return false;
        return true;
    }

    static void _writeComment(uint32 comment) {

        if (comment == 0) {
            debug_write_str("No Comment");
            return;
        }

        char tagStr[5] = {0};
        *((uint32*) &tagStr[0]) = comment;

        if (_commentIsTag(tagStr)) {
            debug_write_str(&tagStr[0]);
        }
        else
        {
            const char* str = (const char*) comment;
            bool isString = true;
            for(uint32 i=0;i < 100;i++) {
                char ch = str[i];
                if ((ch > 1 && ch < 32) || ch > 127) {
                    isString = false;
                    break;
                }
                if (ch == 0) {
                    break;
                }
            }

            if (isString) {
                debug_write_str(str);
            }
            else {
                debug_write_str("No Comment");
            }
        }


    }

	void _writeTrackedAllocation(TrackedMemoryHeader* header) {
        debug_write_str("- Address: ");
        debug_write_hex((uint32) header);
        debug_write_str("\n- Size: ");
        debug_write_int(header->allocationSize);
        debug_write_str("\n- User Address: ");
        debug_write_hex((uint32) (header+1));
        debug_write_str("\n- User Size: ");
        debug_write_int(header->allocationSize - sizeof(TrackedMemoryHeader));
	}

	void _writeCheckedAllocation(CheckedMemoryHeader* header) {
#if 1
		CheckedMemoryFooter* footer = (CheckedMemoryFooter*) ((byte*)header + header->allocationSize - sizeof(CheckedMemoryFooter));

		debug_write_int(header->allocationSize);
		debug_write_char('b');
		debug_write_char(' ');
		debug_write_char('@');
        debug_write_hex((uint32) header);
		debug_write_char('/');
		debug_write_hex((uint32) (header+1));
		debug_write_char(' ');

		if ((header->_guard_begin ^ header->allocationSize) != (uint32) header) {
			debug_write_str(" CORRUPTION");
		}

		if (header->_guard_begin != footer->_guard_end) {
			debug_write_str(" OVERWRITE!");
		}

		debug_write_char(' ');
		_writeComment(header->comment);

		debug_write_char('\n');
#else
        debug_write_str("- Address: ");
        debug_write_hex((uint32) header);
        debug_write_str("\n- Size: ");
        debug_write_int(header->allocationSize);
        debug_write_str("\n- User Address: ");
        debug_write_hex((uint32) (header+1));
        debug_write_str("\n- User Size: ");
        debug_write_int(header->allocationSize - sizeof(CheckedMemoryHeader) - sizeof(CheckedMemoryFooter));
        debug_write_str("\n- User Comment: ");
        _writeComment(header->comment);
        debug_write_str("\n- Header Guard: ");
        debug_write_hex(header->_guard_begin);
        CheckedMemoryFooter* footer = (CheckedMemoryFooter*) ((byte*)header + header->allocationSize - sizeof(CheckedMemoryFooter));
        debug_write_str("\n- Footer Guard: ");
        debug_write_hex(footer->_guard_end);
        debug_write_str("\n- Corrupted Header: ");
        debug_write_bool((header->_guard_begin ^ header->allocationSize) != (uint32) header);
        debug_write_str("\n- Memory Overwrite: ");
        debug_write_bool(header->_guard_begin != footer->_guard_end);
        debug_write_str("\n");
#endif
	}

	static bool _confirmCheckedMemoryHeader(CheckedMemoryHeader* header) {

		// Check Header Guard
		if ((header->_guard_begin ^ header->allocationSize) != (uint32) header) {
			error(GS_THIS, "Caught Corrupted Allocation Header");
            _writeCheckedAllocation(header);
			abort_quit_stop();
			return false;
		}

		// Check Footer Guard
		CheckedMemoryFooter* footer = (CheckedMemoryFooter*) ((byte*)header + header->allocationSize - sizeof(CheckedMemoryFooter));

		if (header->_guard_begin != footer->_guard_end) {
			error(GS_THIS, "Caught Memory Overflow!");
			_writeCheckedAllocation(header);
			abort_quit_stop();
			return false;
		}

		return true;
	}


	static void* _allocateMemory_checked(uint32 userSize, int flags, uint32 comment) {
		CheckedMemoryHeader* header;
		CheckedMemoryFooter* footer;
		byte* allocatedMemory;
		uint32 allocationSize;

		allocationSize = userSize + sizeof(CheckedMemoryHeader) + sizeof(CheckedMemoryFooter);

#if defined(GS_AMIGA)
		allocatedMemory = (byte*) AllocMem(allocationSize, flags);
#endif

#if defined(GS_SDL)
		allocatedMemory = (byte*) SDL_malloc(allocationSize);

		if (flags & MF_Clear)
		{
			SDL_memset(allocatedMemory, 0, allocationSize);
		}

#endif

		if (allocatedMemory == NULL) {
			return NULL;
		}

		header = (CheckedMemoryHeader*) allocatedMemory;
		header->allocationSize = allocationSize;
		header->comment = comment;
		header->_guard_begin = ((uint32) header) ^ header->allocationSize;

		footer = (CheckedMemoryFooter*) (allocatedMemory + sizeof(CheckedMemoryHeader) + userSize);
		footer->_guard_end = header->_guard_begin;

		sCheckedAllocations.pushBack(header);

		sMemoryAllocated += allocationSize;

		return (void*)(header + 1);
	}

	static void* _allocateMemory_unchecked(uint32 userSize, int flags) {
		TrackedMemoryHeader* header;
		byte* allocatedMemory;
		uint32 allocationSize = userSize + sizeof(TrackedMemoryHeader);

#if defined(GS_AMIGA)
		allocatedMemory = (byte*) AllocMem(allocationSize, flags);
#endif

#if defined(GS_SDL)
		allocatedMemory = (byte*) SDL_malloc(allocationSize);


		if (flags & MF_Clear)
		{
			SDL_memset(allocatedMemory, 0, allocationSize);
		}

#endif

		sMemoryAllocated += allocationSize;

		header = (TrackedMemoryHeader*) allocatedMemory;
		header->allocationSize = allocationSize;

		return (void*)(allocatedMemory + sizeof(TrackedMemoryHeader));
	}

	static void _releaseMemory_checked(void* allocation) {
		CheckedMemoryHeader* header = _getCheckedMemoryHeader(allocation);

		if (_confirmCheckedMemoryHeader(header)) {

			sCheckedAllocations.pull(header);

			sMemoryAllocated -= header->allocationSize;
#if defined(GS_AMIGA)
			FreeMem(header, header->allocationSize);
#endif

#if defined(GS_SDL)
			SDL_free(header);
#endif

		}

	}

	static void _releaseMemory_unchecked(void* allocation) {
		TrackedMemoryHeader* header = _getTrackedMemoryHeader(allocation);

		sMemoryAllocated -= header->allocationSize;

#if defined(GS_AMIGA)
		FreeMem(header, header->allocationSize);
#endif

#if defined(GS_SDL)
		SDL_free(header);
#endif

	}

	static void _reallocateMemory_impl(void* dst, const void* src, uint32 dstSize, uint32 srcSize) {

		if (dstSize > srcSize) {
			// grow
#if defined(GS_AMIGA)
			CopyMem((APTR) src, dst, srcSize);
#endif

#if defined(GS_SDL)
			SDL_memcpy(dst, src, srcSize);
#endif
		}
		else {
			// shrink
#if defined(GS_AMIGA)
			CopyMem((APTR) src, dst, dstSize);
#endif

#if defined(GS_SDL)
			SDL_memcpy(dst, src, dstSize);
#endif
		}

	}

	static void* _reallocateMemory_checked(void* allocation, uint32 itemCount, uint32 itemSize) {

		CheckedMemoryHeader* oldHeader = _getCheckedMemoryHeader(allocation);
		CheckedMemoryHeader* newHeader;
		CheckedMemoryFooter* newFooter;
		byte* allocatedMemory;

		if (_confirmCheckedMemoryHeader(oldHeader) == false) {
			return NULL;
		}

		uint32 newUserSize = itemCount * itemSize;
		uint32 newAllocationSize = sizeof(CheckedMemoryHeader) + sizeof(CheckedMemoryFooter) + newUserSize;

#if defined(GS_AMIGA)
		allocatedMemory = (byte*) AllocMem(newAllocationSize, MEMF_CLEAR);
#endif

#if defined(GS_SDL)
		allocatedMemory = (byte*) SDL_malloc(newAllocationSize);

		SDL_memset(allocatedMemory, 0, newAllocationSize);
#endif

		/* TODO: Only clear on grow, and only clear non-written parts */

		sMemoryAllocated += newAllocationSize;

		newHeader = (CheckedMemoryHeader*)  allocatedMemory;
		newHeader->allocationSize = newAllocationSize;
		newHeader->comment = oldHeader->comment;
		newHeader->_guard_begin = ((uint32) newHeader) ^ newHeader->allocationSize;

		newFooter = (CheckedMemoryFooter*) (allocatedMemory + sizeof(CheckedMemoryHeader) + newUserSize);
		newFooter->_guard_end = newHeader->_guard_begin;

		_reallocateMemory_impl( (void*) (newHeader + 1),  allocation, newUserSize, oldHeader->allocationSize - sizeof(CheckedMemoryHeader) - sizeof(CheckedMemoryFooter) );

		if (_confirmCheckedMemoryHeader(newHeader) == false) {
			return NULL;
		}

		sCheckedAllocations.pull(oldHeader);

		sMemoryAllocated -= oldHeader->allocationSize;
#if defined(GS_AMIGA)
		FreeMem(oldHeader, oldHeader->allocationSize);
#endif

#if defined(GS_SDL)
		SDL_free(oldHeader);
#endif

		sCheckedAllocations.pushBack(newHeader);

		return ((void*) (newHeader + 1));
	}

	static void* _reallocateMemory_unchecked(void* allocation, uint32 itemCount, uint32 itemSize) {

		TrackedMemoryHeader* oldHeader = _getTrackedMemoryHeader(allocation);
		TrackedMemoryHeader* newHeader;
		byte* allocatedMemory;


		uint32 newUserSize = itemCount * itemSize;
		uint32 newAllocationSize = sizeof(TrackedMemoryHeader) + newUserSize;


#if defined(GS_AMIGA)
		allocatedMemory = (byte*) AllocMem(newAllocationSize, MEMF_CLEAR);
#endif

#if defined(GS_SDL)
		allocatedMemory = (byte*) SDL_malloc(newAllocationSize);
		SDL_memset(allocatedMemory, 0, newAllocationSize);
#endif

		/* TODO: Only clear on grow, and only clear non-written parts */

		sMemoryAllocated += newAllocationSize;

		newHeader = (TrackedMemoryHeader*)  allocatedMemory;
		newHeader->allocationSize = newAllocationSize;

		_reallocateMemory_impl( (void*) (newHeader + 1),  allocation, newUserSize, oldHeader->allocationSize - sizeof(TrackedMemoryHeader) );

		sMemoryAllocated -= oldHeader->allocationSize;
#if defined(GS_AMIGA)
		FreeMem(oldHeader, oldHeader->allocationSize);
#endif

#if defined(GS_SDL)
		SDL_free(oldHeader);
#endif

		return ((void*) (newHeader + 1));
	}



	void* allocateMemory(uint32 itemCount, uint32 itemSize, int flags, uint32 comment) {

		if (itemCount == 0 || itemSize == 0)
			return NULL;

		uint32 userSize = (itemCount == 1) ? (itemSize) : (itemCount * itemSize);

#if GS_CHECKED == 1
		return _allocateMemory_checked(userSize, flags, comment);
#else
		return _allocateMemory_unchecked(userSize, flags);
#endif
	}

	void releaseMemory(void* allocation) {
		if (allocation != NULL) {

#if GS_CHECKED == 1
			_releaseMemory_checked(allocation);
#else
			_releaseMemory_unchecked(allocation);
#endif

		}
	}


	void* reallocateMemory(void* allocation, uint32 itemCount, uint32 itemSize) {

		// Mimics allocateMemory
		if (allocation == NULL) {
			if (itemCount > 0 && itemSize > 0) {
				return allocateMemory(itemCount, itemSize, MF_Clear, 0);
			}
			else {
				return NULL;
			}
		}

		// Mimics releaseMemory
		if (allocation != NULL && (itemCount == 0 || itemSize == 0)) {
			releaseMemory(allocation);
			return NULL;
		}

#if GS_CHECKED == 1
		return _reallocateMemory_checked(allocation, itemCount, itemSize);
#else
		return _reallocateMemory_unchecked(allocation, itemCount, itemSize);
#endif

	}

	uint32 memSize(void* mem) {

		if (mem == NULL)
			return 0;

#if GS_CHECKED == 1
		CheckedMemoryHeader* header = _getCheckedMemoryHeader(mem);

		if (_confirmCheckedMemoryHeader(header)) {
			return header->allocationSize - sizeof(CheckedMemoryHeader) - sizeof(CheckedMemoryFooter);
		}
		else {
			return 0;
		}

#else
		TrackedMemoryHeader* header = _getTrackedMemoryHeader(mem);
		return header->allocationSize - sizeof(TrackedMemoryHeader);
#endif
	}

	void copyMem(void* dst, void* src, uint32 size) {
#if defined(GS_AMIGA)
		CopyMem(src, dst, size);
#endif

#if defined(GS_SDL)
		SDL_memcpy(dst, src, size);
#endif

	}

	static void _clearMemory(void* mem, uint32 size) {

		/* TODO: Speed improvements */

		byte* p = (byte*) mem;
		while(size--) {
			*p++ = 0;
		}

	}

	void clearMemory(void* mem, uint32 size)
	{
		if (mem == NULL)
		{
			error(GS_THIS, "Attempted to clear a NULL pointer");
			abort_quit_stop();
			return;
		}

#if GS_CHECKED == 1
		uint32 maxSize = memSize(mem);

		if (maxSize == 0) {
			return;
		}

		if (size > maxSize) {
			error(GS_THIS, "Caught buffer overflow!");
			_writeCheckedAllocation(_getCheckedMemoryHeader(mem));
			abort_quit_stop();
			return;
		}
#endif

		_clearMemory(mem, size);

	}

	void clearMemoryNonAllocated(void* mem, uint32 size) {
		if (mem == NULL)
		{
			error(GS_THIS, "(NULL, ?) Tried to clear a NULL pointer");
			return;
		}

		_clearMemory(mem, size);
	}

	void checkMem() {

		debug_write_str("Allocated Memory: ");
		debug_write_int(sMemoryAllocated);
		debug_write_str("\n");

#if GS_CHECKED == 1
		CheckedMemoryHeader* allocation = sCheckedAllocations.peekFront();

		while(allocation != NULL) {
			_writeCheckedAllocation(allocation);
			allocation = allocation->next;
		}
#endif

	}

	uint32 getHeapSize() {
		return 0;
	}

}
