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

#define GS_FILE "stack"

#include "shared/forward.h"
#include "shared/error.h"
#include "shared/memory.h"

uint32 sSize, sCapacity;
int32* sData;
int32  sListData[64];

void _growStack() {

}

int32 _popStack_unchecked() {
	sSize--;
	return sData[sSize];
}

void gs_InitializeStack() {
	sCapacity = 256;
	sSize = 0; // ?
	sData = (int32*) gs_Allocate(sCapacity, sizeof(int32), MF_Clear, GS_COMMENT_FILE_LINE);
}

void gs_TeardownStack() {
	gs_Deallocate(sData);
	sCapacity = 0;
	sSize = 0;
}

void gs_ResetStack() {
	sSize = 0;
}

void gs_PushStack(int32 value) {
	if (sSize == sCapacity) {
		_growStack();
	}

	sData[sSize] = value;
	sSize++;
}

int32 gs_PopStack() {
	if (sSize == 0) {
		gs_error_str("Stack underflow.");
		return 0;
	}

	sSize--;
	return sData[sSize];
}

int32* gs_PopList(uint16 maxLength, uint16* out_length) {
	
	uint16 i, size, sizePopped;

	if (maxLength > 64) {
		gs_error_str("Stack list overflow");
		*out_length = 0;
		return NULL;
	}
			
	for (i = 0; i < maxLength; i++) {
		sListData[i] = 0;
	}

	size = gs_PopStack();

	if (size > maxLength || size > 64) {
		gs_error_str("Stack list overflow");
		*out_length = 0;
		return NULL;
	}

	i = size;
	sizePopped = 0;
	while(i-- != 0) {
				
		if (sSize == 0)
			break;

		sListData[i] = _popStack_unchecked();
		sizePopped++;
	}

	if (size != sizePopped) {
		gs_error_str("Stack size is not the same size as amount popped.");
		*out_length = 0;
		return NULL;
	}

	*out_length = sizePopped;
	return &sListData[0];
}
