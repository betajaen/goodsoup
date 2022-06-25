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

#ifndef COMI_CONSTANTS_H
#define COMI_CONSTANTS_H

#include "common/types.h"
#include "common/buffer.h"

using namespace common;

namespace comi
{
	enum  ComiConstants
	{
		MAX_SCRIPT_CONTEXTS = 80,
		NUM_STACK_SCRIPTS = 15,

		// MAXS Constants
		NUM_INT_GLOBALS = 1500,
		NUM_BOOL_GLOBALS = 2048,
		NUM_INT_LOCALS = 26,
		NUM_SCRIPTS = 458,
		NUM_SOUNDS = 789,
		NUM_CHARSETS = 1,
		NUM_COSTUMES = 446,
		NUM_ROOMS = 95,
		NUM_OBJECT_GLOBALS = 1401,
		NUM_OBJECT_LOCALS = 200,
		NUM_NEWNAMES = 100,
		NUM_FLOBJECTS = 128,
		NUM_INVENTORY = 80,
		NUM_ARRAY = 200,
		NUM_VERBS = 50,
		NUM_GLOBAL_SCRIPTS = 2000,
		NUM_AARY = 142,
		NUM_DISKS = 2

	};

	enum ObjectWhere
	{
		OW_Unknown = 0,
		OW_NotFound = 1,
		OW_Inventory = 2,
		OW_Room = 3,
		OW_Global = 4,
		OW_Local = 5,
		OW_FLObject = 6
	};

	enum FixedScriptIds
	{
		FSI_ROOM_ENTRANCE = 10002,
		FSI_ROOM_EXIT = 10001
	};

}

#endif