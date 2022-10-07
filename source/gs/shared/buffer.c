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

#define GS_FILE "buffer"

#include "shared/buffer.h"
#include "shared/memory.h"
#include "shared/endian.h"

#define PUT_MAYBE_GROW(TYPE) \
	if (((*pos) + sizeof(TYPE)) >= buffer->capacity)\
	{\
		grow(buffer, (*pos) + sizeof(TYPE));\
	}

GS_PRIVATE void grow(gs_Buffer* buffer, uint32 newCapacity)
{
	if (newCapacity < buffer->capacity) {
		return;
	}

	byte* newData = gs_Allocate(sizeof(byte), newCapacity, MF_Clear, GS_COMMENT_FILE_LINE);
	gs_Memcpy(newData, buffer->data, buffer->capacity);
	gs_Deallocate(buffer->data);

	buffer->data = newData;
	buffer->capacity = newCapacity;
}


GS_EXPORT void gs_AllocateBuffer(gs_Buffer* buffer, uint32 initialCapacity, uint32 comment)
{
	if (initialCapacity == 0) {
		initialCapacity = 64;
	}

	buffer->capacity = initialCapacity;
	buffer->data = gs_Allocate(sizeof(byte), initialCapacity, MF_Clear, comment != 0 ? comment : GS_COMMENT_FILE_LINE);

}

GS_EXPORT void gs_DeallocateBuffer(gs_Buffer* buffer) {
	gs_Deallocate(buffer->data);
	buffer->capacity = 0;
}

GS_EXPORT void gs_PutByte(gs_Buffer* buffer, uint32* pos, byte value)
{
	PUT_MAYBE_GROW(byte)

	*( (byte*) ((buffer->data + *pos))) = value;
}

void gs_PutInt8(gs_Buffer* buffer, uint32* pos, int8 value) {
	
	PUT_MAYBE_GROW(int8)

	*( (byte*) ((buffer->data + *pos))) = value;
}

void gs_PutUInt8(gs_Buffer* buffer, uint32* pos, uint8 value) {
	PUT_MAYBE_GROW(uint8)

	*( (byte*) ((buffer->data + *pos))) = value;
}

void gs_PutInt16_BE(gs_Buffer* buffer, uint32* pos, int16 value) {
	
	PUT_MAYBE_GROW(uint16)

	byte* dst = buffer->data + *pos;
	dst[0] = (value >> 8) & 0xFF;
	dst[1] = value & 0xFF;
}

void gs_PutUInt16_BE(gs_Buffer* buffer, uint32* pos, uint16 value)
{
	PUT_MAYBE_GROW(uint16)

	byte* dst = buffer->data + *pos;
	dst[0] = (value >> 8) & 0xFF;
	dst[1] = value & 0xFF;
}

void gs_PutInt16_LE(gs_Buffer* buffer, uint32* pos, uint16 value)
{
	PUT_MAYBE_GROW(int16)

	byte* dst = buffer->data + *pos;
	dst[0] = value & 0xFF;
	dst[1] = (value >> 8) & 0xFF;
}

void gs_PutUInt16_LE(gs_Buffer* buffer, uint32* pos, uint16 value)
{
	PUT_MAYBE_GROW(uint16)

	byte* dst = buffer->data + *pos;
	dst[0] = value & 0xFF;
	dst[1] = (value >> 8) & 0xFF;
}

void gs_PutInt32_BE(gs_Buffer* buffer, uint32* pos, int32 value)
{
	PUT_MAYBE_GROW(int32)

	byte* dst = buffer->data + *pos;
	dst[0] = (value >> 24) & 0xFF;
	dst[1] = (value >> 16) & 0xFF;
	dst[2] = (value >> 8) & 0xFF;
	dst[3] = value & 0xFF;
}

void gs_PutUInt32_BE(gs_Buffer* buffer, uint32* pos, uint32 value)
{
	PUT_MAYBE_GROW(int32)

	byte* dst = buffer->data + *pos;
	dst[0] = (value >> 24) & 0xFF;
	dst[1] = (value >> 16) & 0xFF;
	dst[2] = (value >> 8) & 0xFF;
	dst[3] = value & 0xFF;
}

void gs_PutInt32_LE(gs_Buffer* buffer, uint32* pos, uint32 value)
{
	PUT_MAYBE_GROW(int32)

	byte* dst = buffer->data + *pos;
	dst[0] = value & 0xFF;
	dst[1] = (value >> 8) & 0xFF;
	dst[2] = (value >> 16) & 0xFF;
	dst[3] = (value >> 24) & 0xFF;
}

void gs_PutUInt32_LE(gs_Buffer* buffer, uint32* pos, uint32 value)
{
	PUT_MAYBE_GROW(uint32)

	byte* dst = buffer->data + *pos;
	dst[0] = value & 0xFF;
	dst[1] = (value >> 8) & 0xFF;
	dst[2] = (value >> 16) & 0xFF;
	dst[3] = (value >> 24) & 0xFF;
}

byte gs_GetByte(gs_Buffer* buffer, uint32* pos)
{
	return (byte) *((byte*) (buffer->data + *pos));
}

int8 gs_GetInt8(gs_Buffer* buffer, uint32* pos)
{
	return (int8) *((byte*) (buffer->data + *pos));
}

uint8 gs_GetUInt8(gs_Buffer* buffer, uint32* pos)
{
	return (uint8) *((byte*) (buffer->data + *pos));
}

int16 gs_GetInt16_BE(gs_Buffer* buffer, uint32* pos)
{
	byte* src = buffer->data + *pos;
	int16 value = src[1];
	value <<= 8;
	value |= src[0];

	return value;
}

uint16 gs_GetUInt16_BE(gs_Buffer* buffer, uint32* pos, uint16 value)
{
	byte* src = buffer->data + *pos;
	uint16 value = src[1];
	value <<= 8;
	value |= src[0];

	return value;
}

int16 gs_GetInt16_LE(gs_Buffer* buffer, uint32* pos, uint16 value)
{
	byte* src = buffer->data + *pos;
	int16 value = src[0];
	value <<= 8;
	value |= src[1];

	return value;
}

uint16 gs_GetUInt16_LE(gs_Buffer* buffer, uint32* pos, uint16 value)
{
	byte* src = buffer->data + *pos;
	uint16 value = src[0];
	value <<= 8;
	value |= src[1];

	return value;
}

int32 gs_GetInt32_BE(gs_Buffer* buffer, uint32* pos, int32 value)
{
	byte* src = buffer->data + *pos;
	uint16 value = src[3];
	value <<= 8;
	value |= src[2];
	value <<= 8;
	value |= src[1];
	value <<= 8;
	value |= src[0];

	return value;
}

uint32 gs_GetUInt32_BE(gs_Buffer* buffer, uint32* pos, uint32 value)
{
	byte* src = buffer->data + *pos;
	uint16 value = src[3];
	value <<= 8;
	value |= src[2];
	value <<= 8;
	value |= src[1];
	value <<= 8;
	value |= src[0];

	return value;
}

int32 gs_GetInt32_LE(gs_Buffer* buffer, uint32* pos, int32 value)
{
	byte* src = buffer->data + *pos;
	uint16 value = src[0];
	value <<= 8;
	value |= src[1];
	value <<= 8;
	value |= src[2];
	value <<= 8;
	value |= src[3];

	return value;
}

uint32 gs_GetUInt32_LE(gs_Buffer* buffer, uint32* pos, uint32 value)
{
	byte* src = buffer->data + *pos;
	uint16 value = src[0];
	value <<= 8;
	value |= src[1];
	value <<= 8;
	value |= src[2];
	value <<= 8;
	value |= src[3];

	return value;
}