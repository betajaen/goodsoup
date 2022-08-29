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

#define GS_FILE_NAME "dialogue"

#include "dialogue.h"
#include "containers.h"

namespace gs
{
#define MAX_DIALOGUE_CACHE_SIZE 24

	LinkedListPool<Dialogue> sDialoguePool;
	LinkedListPool<DialogueDrawOperation> sDialogueDrawOperationPool;
	LinkedListPool<DialogueDrawRegion> sDialogueDrawRegionsPool;

	// Cache of previously deleted Dialogues so they can be reused, to avoid expensive recalculations of the same text
	Queue<Dialogue> sDialogueCache;
	uint16 sDialogueCacheSize;


}
