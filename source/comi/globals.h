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

#ifndef COMI_GLOBALS_H
#define COMI_GLOBALS_H

#include "common/types.h"

namespace comi
{
	class VirtualMachine;
	class Index;
	class VmArrayAllocator;
	class Resources;
	struct VmIntVars;
	struct VmBoolVars;

	extern VirtualMachine* VM;
	extern Index* INDEX;
	extern VmArrayAllocator* ARRAYS;
	extern Resources* RESOURCES;
	extern VmIntVars INTS;
	extern VmBoolVars BOOLS;

	extern bool QUIT_NOW;
}

#endif