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

#ifndef GS_MEMORY_H
#define GS_MEMORY_H

#include "shared/forward.h"

#define MF_Any (0UL)
#define MF_Chip (1UL<<1)
#define MF_Clear (1UL<<16)

GS_IMPORT void* gs_Allocate(uint32 count, uint32 size, uint32 flags, uint32 comment);
GS_IMPORT void gs_Deallocate(void* mem);

#define gs_New(TYPE, COMMENT) (gs_Allocate(1, sizeof(TYPE), MF_Clear, COMMENT))
#define gs_Delete(OBJ) do { if (OBJ) { gs_Deallocate(OBJ); OBJ = NULL; } } while(0)

#define gs_NewCObject(TYPE, COBJECT_TYPE)  (gs_Allocate(1, sizeof(TYPE), MF_Clear, gs_MakeId('C', 'O', 'T', ('A' + COBJECT_TYPE))))
#define gs_DeleteCObject(OBJ) gs_Delete(OBJ)

#endif
