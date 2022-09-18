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

#ifndef GS_FORWARD_H
#define GS_FORWARD_H

_Static_assert(sizeof(void*) == 4, "Goodsoup can only be compiled on a 32-bit architecture.");

// typedef char __32BIT_ARCH_ONLY__[(!!(sizeof(void*) == 4))*2-1];

#if defined(GS_AGA_OS3)

#define GS_OS3_ARCH
#define GS_BIG
#define GS_AGA
#define GS_PATH_DIR "COMI:"

#define GS_ARCH_NAME "AGA OS3"

#elif defined(GS_RTG_OS3)

#define GS_OS3_ARCH
#define GS_BIG
#define GS_RTG
#define GS_PATH_DIR "COMI:"

#define GS_ARCH_NAME "RTG OS3"

#elif defined(GS_CLI_OS3)

#define GS_OS3_ARCH
#define GS_BIG
#define GS_CLI
#define GS_PATH_DIR "COMI:"

#define GS_ARCH_NAME "CLI OS3"

#elif defined(GS_CLI_X86)

#define GS_CSTD_ARCH
#define GS_LITTLE
#define GS_CLI
#define GS_PATH_DIR "./"

#define GS_ARCH_NAME "CLI X86"

#else

#error "GS_AGA_OS3, GS_RTG_OS3, GS_CLI_OS3 or GS_CLI_X86 was not defined in defines. Please fix appropriate makefile."

#endif


#if defined(GS_OS3_ARCH)

#include <exec/types.h>
#include "shared/sdi/SDI_stdarg.h"

typedef UBYTE	uint8;
typedef BYTE	int8;
typedef UBYTE	byte;
typedef UWORD	uint16;
typedef WORD	int16;
typedef ULONG	uint32;
typedef LONG	int32;
typedef uint16	gs_bool;
typedef ULONG	gs_absptr;
typedef ULONG   gs_tag;

#define GS_VARARG_LIST(ARGS) VA_LIST ARGS
#define GS_VARARG_BEGIN(ARGS, FMT) VA_START(ARGS, FMT)
#define GS_VARARG_END(ARGS) VA_END(ARGS)
#define GS_VARARG_ARG(ARGS, TYPE) ((TYPE) ARGS)

#elif defined(GS_CSTD_ARCH)

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

typedef uint8_t		uint8;
typedef int8_t		int8;
typedef uint8_t		byte;
typedef uint16_t	uint16;
typedef int16_t		int16;
typedef uint32_t	uint32;
typedef int32_t		int32;
typedef uint16		gs_bool;
typedef uint32		gs_absptr;
typedef uint32      gs_tag;

#define GS_VARARG_LIST(ARGS) va_list ARGS
#define GS_VARARG_BEGIN(ARGS, FMT) va_start(ARGS, FMT)
#define GS_VARARG_END(ARGS) va_end(ARGS)
#define GS_VARARG_ARG(ARGS, TYPE) ((TYPE) ARGS)

#else
#error "Unknown Arch!"
#endif


#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE  1
#endif

#define GS_PRIVATE static
#define GS_IMPORT  extern
#define GS_EXPORT  /* extern */

typedef int32(*gs_callback)(void* user, int32 param);

#define GS__CONCAT(a, b) a##b
#define GS_CONCAT(a, b) GS__CONCAT(a, b)
#define GS_CONCAT2(a, b) GS_CONCAT(a, GS_CONCAT(_, b))

#define _GS_STR_IMPL(X) #X
#define GS_STR(X) _GS_STR_IMPL(X)
#define GS_COMMENT_FILE_LINE	(uint32) (__FILE__ ":" GS_STR(__LINE__))
#define GS_COMMENT_FILE_LINE_NOTE(NOTE)	(uint32) (__FILE__ ":" GS_STR(__LINE__) " " NOTE)

#define GS_SWAP(T, A, B) do { T t = A; A = B; B = t; } while(0)

#endif
