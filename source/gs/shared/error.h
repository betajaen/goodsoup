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

#ifndef GS_ERROR_H
#define GS_ERROR_H

#include "shared/forward.h"

GS_IMPORT void gs__error_fmt(const char* source, uint32 line, const char* function, uint16 category, const char* fmt, ...);
GS_IMPORT void gs__error_str(const char* source, uint32 line, const char* function, uint16 category, const char* str);
GS_IMPORT void gs_print_fmt(const char* fmt, ...);
GS_IMPORT void gs_print_str(const char* str);
GS_IMPORT void gs_message_fmt(const char* fmt, ...);
GS_IMPORT void gs_message_str(const char* str);
GS_IMPORT const char* gs_Comment2Str(uint32 comment);

#ifndef GS_FILE
#define GS_FILE __FILE__
#endif

#if !defined(GS_DEBUG)
#define GS_DEBUG 1
#endif

#if GS_DEBUG >= 4
#define gs_verbose_fmt(FMT, ...) gs__error_fmt(GS_FILE, __LINE__, __FUNCTION__, 4, FMT, __VA_ARGS__)
#define gs_verbose_str(STR)      gs__error_str(GS_FILE, __LINE__, __FUNCTION__, 4, STR)
#else
#define gs_verbose_fmt(FMT, ...)
#define gs_verbose_str(STR)
#endif

#if GS_DEBUG >= 3
#define gs_debug_fmt(FMT, ...) gs__error_fmt(GS_FILE, __LINE__, __FUNCTION__, 3, FMT, __VA_ARGS__)
#define gs_debug_str(STR)      gs__error_str(GS_FILE, __LINE__, __FUNCTION__, 3, STR)
#else
#define gs_debug_fmt(FMT, ...)
#define gs_debug_str(STR)
#endif

#if GS_DEBUG >= 2
#define gs_info_fmt(FMT, ...) gs__error_fmt(GS_FILE, __LINE__, __FUNCTION__, 2, FMT, __VA_ARGS__)
#define gs_info_str(STR)      gs__error_str(GS_FILE, __LINE__, __FUNCTION__, 2, STR)
#else
#define gs_info_fmt(FMT, ...)
#define gs_info_str(STR)
#endif

#if GS_DEBUG >= 1
#define gs_warn_fmt(FMT, ...) gs__error_fmt(GS_FILE, __LINE__, __FUNCTION__, 1, FMT, __VA_ARGS__)
#define gs_warn_str(STR)      gs__error_str(GS_FILE, __LINE__, __FUNCTION__, 1, STR)
#else
#define gs_warn_fmt(FMT, ...)
#define gs_warn_str(STR)
#endif

#if GS_DEBUG >= 0
#define gs_error_fmt(FMT, ...) gs__error_fmt(GS_FILE, __LINE__, __FUNCTION__, 0, FMT, __VA_ARGS__)
#define gs_error_str(STR)      gs__error_str(GS_FILE, __LINE__, __FUNCTION__, 0, STR)
#else
#define gs_error_fmt(FMT, ...)
#define gs_error_str(STR)
#endif


#endif
