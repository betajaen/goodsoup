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

#ifndef GS_BUFFER_H
#define GS_BUFFER_H

#include "shared/forward.h"

typedef struct gs_Buffer {
	byte* data;
	uint32 capacity;
} gs_Buffer;

void gs_AllocateBuffer(gs_Buffer* buffer, uint32 initialCapacity, uint32 comment);
void gs_DeallocateBuffer(gs_Buffer* buffer);

void gs_PutByte(gs_Buffer* buffer, uint32* pos, byte value);
void gs_PutInt8(gs_Buffer* buffer, uint32* pos, int8 value);
void gs_PutUInt8(gs_Buffer* buffer, uint32* pos, uint8 value);
void gs_PutInt16_BE(gs_Buffer* buffer, uint32* pos, int16 value);
void gs_PutUInt16_BE(gs_Buffer* buffer, uint32* pos, uint16 value);
void gs_PutInt16_LE(gs_Buffer* buffer, uint32* pos, uint16 value);
void gs_PutUInt16_LE(gs_Buffer* buffer, uint32* pos, uint16 value);
void gs_PutInt32_BE(gs_Buffer* buffer, uint32* pos, int32 value);
void gs_PutUInt32_BE(gs_Buffer* buffer, uint32* pos, uint32 value);
void gs_PutInt32_LE(gs_Buffer* buffer, uint32* pos, uint32 value);
void gs_PutUInt32_LE(gs_Buffer* buffer, uint32* pos, uint32 value);


#define gs_AddByte(BUFFER, POS, VALUE) do { gs_PutByte(BUFFER, POS, VALUE); POS += sizeof(byte); } while(0)
#define gs_AddInt8(BUFFER, POS, VALUE) do { gs_PutInt8(BUFFER, POS, VALUE); POS += sizeof(int8); } while(0)
#define gs_AddUInt8(BUFFER, POS, VALUE) do { gs_PutUInt8(BUFFER, POS, VALUE); POS += sizeof(uint8); } while(0)
#define gs_AddInt16_LE(BUFFER, POS, VALUE) do { gs_PutInt16_LE(BUFFER, POS, VALUE); POS += sizeof(int16); } while(0)
#define gs_AddUInt16_LE(BUFFER, POS, VALUE) do { gs_PutUInt16_LE(BUFFER, POS, VALUE); POS += sizeof(uint16); } while(0)
#define gs_AddInt16_BE(BUFFER, POS, VALUE) do { gs_PutInt16_BE(BUFFER, POS, VALUE); POS += sizeof(int16); } while(0)
#define gs_AddUInt16_BE(BUFFER, POS, VALUE) do { gs_PutUInt16_BE(BUFFER, POS, VALUE); POS += sizeof(uint16); } while(0)
#define gs_AddInt32_LE(BUFFER, POS, VALUE) do { gs_PutInt32_LE(BUFFER, POS, VALUE); POS += sizeof(int32); } while(0)
#define gs_AddUInt32_LE(BUFFER, POS, VALUE) do { gs_PutUInt32_LE(BUFFER, POS, VALUE); POS += sizeof(uint32); } while(0)
#define gs_AddInt32_BE(BUFFER, POS, VALUE) do { gs_PutInt32_BE(BUFFER, POS, VALUE); POS += sizeof(int32); } while(0)
#define gs_AddUInt32_BE(BUFFER, POS, VALUE) do { gs_PutUInt32_BE(BUFFER, POS, VALUE); POS += sizeof(uint32); } while(0)


byte gs_GetByte(gs_Buffer* buffer, uint32* pos);
int8 gs_GetInt8(gs_Buffer* buffer, uint32* pos);
uint8 gs_GetUInt8(gs_Buffer* buffer, uint32* pos);
int16 gs_GetInt16_BE(gs_Buffer* buffer, uint32* pos);
uint16 gs_GetUInt16_BE(gs_Buffer* buffer, uint32* pos);
int16 gs_GetInt16_LE(gs_Buffer* buffer, uint32* pos);
uint16 gs_GetUInt16_LE(gs_Buffer* buffer, uint32* pos);
int32 gs_GetInt32_BE(gs_Buffer* buffer, uint32* pos);
uint32 gs_GetUInt32_BE(gs_Buffer* buffer, uint32* pos);
int32 gs_GetInt32_LE(gs_Buffer* buffer, uint32* pos);
uint32 gs_GetUInt32_LE(gs_Buffer* buffer, uint32* pos);


#endif
