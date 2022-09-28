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

#include "shared/forward.h"
#include "shared/error.h"

#include <stdlib.h>
#include <string.h>

#ifndef GS_CHECK_MEMORY
#define GS_CHECK_MEMORY 0
#endif

#if GS_CHECK_MEMORY == 1

#define UNALLOCATED_MAGIC 0xDEADDEAD

typedef struct CheckedMemHeader
{
	uint32 length;		// Length
	uint32 comment;		// Comment; which can be a FourCC, or a string pointer.
	uint32 magic;		// Is the XOR of the pointer and the length.
} Header  __attribute__ ((packed));

typedef struct CheckedMemFooter
{
	uint32 magic;		// Is the XOR of the pointer and the length.
} Footer  __attribute__ ((packed));


// Checks the allocation and returns the CheckedMemAllocation associated with it.
// In the case of a null pointer or buffer overflow/underflow, it will return a null. An error will be raised.
GS_PRIVATE CheckedMemHeader* GetHeaderAndCheckAllocation(void* allocation)
{
	if (allocation == NULL) {
		return NULL;
	}

	CheckedMemHeader* header = ((CheckedMemHeader*) allocation)[-1];

	if (header->magic != ( ((uint32) header->length) ^ header->magic)) {
		const char* headerComment = GetHeaderComment(header);
		if (header->magic == UNALLOCATED_MAGIC) {
			// Double Free!
			gs_error_fmt("Double Free Caught from %s", headerComment);
		}
		else {
			// Buffer underflow
			gs_error_fmt("Allocated memory underflow for possibly %s", headerComment);
		}
		return NULL;
	}

	CheckedMemFooter* footer = (CheckedMemFooter*) ( ( ( (byte*) allocation) + sizeof(CheckedMemoryHeader) + userSize) );

	if (footer->magic != header->magic) {
		const char* headerComment = GetHeaderComment(header);
		gs_error_fmt("Allocated memory overflow for %s", headerComment);
		return NULL;
	}

	return header;
}

GS_EXPORT void* gs_Allocate(uint32 count, uint32 size, uint32 flags, const char* comment) {

	if (count == 0) {
		count = 1;
	}

	uint32 userSize = count * size;
	uint32 allocSize = sizeof(CheckedMemHeader) + userSize + sizeof(CheckedMemFooter);

	void* allocation = malloc(allocSize);
	
	if (flags & (1UL << 16)) {
		memset(allocation, 0, allocSize);
	}

	CheckedMemHeader* header = (CheckedMemHeader*) allocation;
	header->length = userSize;
	header->comment = comment;
	header->magic = ((uint32) header) ^ userSize;

	CheckedMemFooter* footer = (CheckedMemFooter*) ( ( ( (byte*) allocation) + sizeof(CheckedMemoryHeader) + userSize) );
	footer->magic = header->magic;

	return (void*) (header + 1);
}

GS_EXPORT void gs_Deallocate(void* mem) {

	CheckedMemHeader* header = GetHeaderAndCheckAllocation(mem);

	if (header == NULL) {
		return;
	}

	// Mark magic as unallocated, but do not reset comment or length.
	// These can be used to determine a double free later.
	header->magic = UNALLOCATED_MAGIC;

	free(header);
}

#else

GS_EXPORT void* gs_Allocate(uint32 count, uint32 size, uint32 flags, const char* comment) {

	if (count == 0) {
		count = 1;
	}

	uint32 userSize = count * size;

	void* mem = malloc(userSize);

	if (flags & (1UL << 16)) {
		memset(mem, 0, userSize);
	}

	return mem;
}

GS_EXPORT void gs_Deallocate(void* mem) {
	if (mem != NULL) {
		free(mem);
	}
}

#endif

