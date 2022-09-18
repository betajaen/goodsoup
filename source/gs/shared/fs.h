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

#ifndef GS_FS_H
#define GS_FS_H

#include "shared/forward.h"

/**
 * Checks to see if a drawer exists
 * 
 * @param path Path to the drawer
 * @return if the drawer exists or not
 */
GS_IMPORT gs_bool gs_DrawerExists(const char* path);

/**
 * Checks to see if a drawer exists
 * 
 * @param path Path to the drawer
 * @return if the directory exists or not
 */
GS_IMPORT gs_bool gs_CreateDrawer(const char* path);

#endif
