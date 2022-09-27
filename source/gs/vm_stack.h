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

#ifndef GS_VM_STACK_H
#define GS_VM_STACK_H

#include "shared/forward.h"

void gs_InitializeStack();
void gs_TeardownStack();
void gs_ResetStack();
void gs_PushStack(int32 value);
int32 gs_PopStack();
int32* gs_PopList(uint16 maxLength, uint16* out_length);

#endif
