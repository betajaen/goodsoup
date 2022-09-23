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

#ifndef GS_OS3_ARCH
#error "GS_OS3_ARCH must be defined to compile this file."
#endif

#include "shared/error.h"
#include <proto/dos.h>


GS_IMPORT gs_bool gs_DrawerExists(const char* path) {
	

	BPTR lock = Lock(path, ACCESS_READ);

	UnLock(lock);

	return lock != 0;
}

GS_IMPORT gs_bool gs_CreateDrawer(const char* path) {
	
	BPTR lock;

	gs_debug_fmt("Create Drawer %s", path);

	lock = Lock(path, ACCESS_READ);

	if (lock) {
		UnLock(lock);

		return TRUE;
	}

	lock = CreateDir(path);

	if (lock != 0) {
		UnLock(lock);
	}
	
	return lock != 0;
}
