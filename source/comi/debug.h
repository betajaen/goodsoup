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

#ifndef COMI_DEBUG_H
#define COMI_DEBUG_H

#include "common/debug.h"

#ifndef GS_FILE_NAME
#define GS_FILE_NAME __FILE__
#endif

#define comi_verbose(FMT, ...) ::common::verbose("COMI %-12s %3i %-24s " FMT,GS_FILE_NAME,__LINE__,__FUNCTION__,##__VA_ARGS__)
#define comi_debug(FMT, ...)   ::common::debug("COMI %-12s %3i %-24s " FMT,GS_FILE_NAME,__LINE__,__FUNCTION__,##__VA_ARGS__)
#define comi_info(FMT, ...)    ::common::info("COMI %-12s %3i %-24s " FMT,GS_FILE_NAME,__LINE__,__FUNCTION__,##__VA_ARGS__)
#define comi_warn(FMT, ...)    ::common::warn("COMI %-12s %3i %-24s " FMT,GS_FILE_NAME,__LINE__,__FUNCTION__,##__VA_ARGS__)
#define comi_error(FMT, ...)   ::common::error("COMI %-12s %3i %-24s " FMT,GS_FILE_NAME,__LINE__,__FUNCTION__,##__VA_ARGS__)

#endif