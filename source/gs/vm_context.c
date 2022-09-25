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

#define GS_FILE "coroutine"

#include "shared/forward.h"
#include "shared/error.h"
#include "vm_context.h"

#define T gs_VmContext
#define LIST_NAME ContextList
#include "shared/list.h"

ContextList sVmContexts = { NULL, NULL };

gs_VmContext* gs_ContextStack[1 + GS_VM_CONTEXT_STACK_SIZE] = { NULL };
