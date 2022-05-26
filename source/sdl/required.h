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

#ifndef GOODSOUP_SDL_REQUIRED_H
#define GOODSOUP_SDL_REQUIRED_H

#include <SDL2/SDL.h>
#include <new>

#define assert(X) SDL_assert(X)

#define ARRAYSIZE(X) SDL_arraysize(X)

#define MEMF_ANY     (0UL)
#define MEMF_PUBLIC  (1UL<<0)
#define MEMF_CHIP    (1UL<<1)
#define MEMF_CLEAR   (1UL<<16)
#define MEMF_CPP_NEW (1UL << 24)

namespace common
{
	typedef Uint8   byte;
	typedef Uint8   uint8;
	typedef Uint16  uint16;
	typedef Uint32  uint32;
	typedef Sint8   int8;
	typedef Sint16  int16;
	typedef Sint32  int32;

	// Debugging

	void verbose(const char* fmt, ...);
	void debug(const char* fmt, ...);
	void info(const char* fmt, ...);
	void warn(const char* fmt, ...);
	void error(const char* fmt, ...);

	// Memory

	void* allocMem(uint32 count, uint32 size, int flags);
	void freeMem(void* mem);
	void clearMem(void* mem, uint32 size);
	void checkMem();


	template<typename T>
	T* newObject() {
		void* mem = ::common::allocMem(1, (common::uint32)sizeof(T), MEMF_CLEAR | MEMF_CPP_NEW);
		new(mem) T();
		return (T*)mem;
	}

	template<typename T, typename TA0>
	T* newObject(TA0 a0) {
		void* mem = ::common::allocMem(1, (common::uint32)sizeof(T), MEMF_CLEAR | MEMF_CPP_NEW);
		new(mem) T(a0);
		return (T*)mem;
	}

	template<typename T, typename TA0, typename TA1>
	T* newObject(TA0 a0, TA1 a1) {
		void* mem = ::common::allocMem(1, (common::uint32)sizeof(T), MEMF_CLEAR | MEMF_CPP_NEW);
		new(mem) T(a0, a1);
		return (T*)mem;
	}

	template<typename T, typename TA0, typename TA1, typename TA2>
	T* newObject(TA0 a0, TA1 a1, TA2 a2) {
		void* mem = ::common::allocMem(1, (common::uint32)sizeof(T), MEMF_CLEAR | MEMF_CPP_NEW);
		new(mem) T(a0, a1, a2);
		return (T*)mem;
	}

	template<typename T, typename TA0, typename TA1, typename TA2, typename TA3>
	T* newObject(TA0 a0, TA1 a1, TA2 a2, TA3 a3) {
		void* mem = ::common::allocMem(1, (common::uint32)sizeof(T), MEMF_CLEAR | MEMF_CPP_NEW);
		new(mem) T(a0, a1, a2, a3);
		return (T*)mem;
	}

	template<typename T>
	void deleteObject(T*& object) {
		if (object != NULL) {
			object->~T();
			::common::freeMem(object);
			object = NULL;
		}
	}

	template<typename T>
	void freeMemThenNull(T*& mem)
	{
		if (mem)
		{
			freeMem(mem);
			mem = NULL;
		}
	}

	// File

	enum SeekOffset
	{
		FOS_Begin = RW_SEEK_SET,
		FOS_Current = RW_SEEK_CUR,
		FOS_End = RW_SEEK_END
	};

	typedef SDL_RWops* CFile;

	CFile openFileRead(const char* path);
	CFile openFileWrite(const char* path);
	void closeFile(CFile file);
	bool checkFile(const char* path);
	bool isFileOpen(CFile file);
	void writeFile(CFile file, const void* data, uint32 length);
	void readFile(CFile file, void* data, uint32 length);
	int32 seekFile(CFile file, int32 seek, int32 seekOffset);
	int32 tellFile(CFile file);

	inline uint32 SWAP_BYTES_32(uint32 a) {
		return ((a >> 24) & 0x000000FF) |
			((a >> 8) & 0x0000FF00) |
			((a << 8) & 0x00FF0000) |
			((a << 24) & 0xFF000000);
	}
	
	inline uint16 SWAP_BYTES_16(uint16 a) {
		return ((a >> 8) & 0x00FF) + ((a << 8) & 0xFF00);
	}

	const char* tag2str(uint32 tag, char* str);

}

#define TO_LE_32(a) ((uint32)(a))
#define TO_LE_16(a) ((uint16)(a))

#define TO_BE_32(a) (::common::SWAP_BYTES_32(a))
#define TO_BE_16(a) (::common::SWAP_BYTES_16(a))

#define NEW_OBJECT(T, ...) ::common::newObject<T>(__VA_ARGS__)
#define DELETE_OBJECT(OBJ) ::common::deleteObject(OBJ)
#define NEW_MEMORY(COUNT, SIZE, FLAGS) ::common::allocMem(COUNT, SIZE, FLAGS)
#define DELETE_MEMORY(MEM) ::common::freeMemThenNull(MEM)


#endif
