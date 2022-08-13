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

#ifndef GS_DIALOGUE_H
#define GS_DIALOGUE_H

#include "forward.h"
#include "profile.h"

namespace gs
{

#define DIALOGUE_DRAW_REGION_LENGTH 40

	class DialogueDrawRegion;
	class DialogueDrawLine;

	enum DialogueKind
	{
		// Spoken Dialogue
		// An actor or subject on the screen is talking
		// "Lost at sea for days now. I have no crew or navigational instruments."
		DK_Spoken = 0,
		// Exposition Text
		// Text on the screen is describing an place, event or idea that isnt obvious to the player
		// "Monkey Island"
		DK_Exposition = 1,
		// Credit
		// Text on the screen of a name, or entity that contributed to the game
		DK_Credit = 2
	};

	enum DialogueFormatting
	{
		DF_Center = 1,
		DF_Wrap = 2
	};

	class Dialogue {
	public:

		Dialogue() {
			next = NULL;
			drawOp = NULL;
		}

		~Dialogue();

		void draw(byte* dstFrameBuffer);

		Dialogue* next;
		DialogueDrawOperation* drawOp;
		uint32 hash;
		uint8  font;
		uint8  flags;
		uint8  colour;
		char text[MAX_DIALOGUE_LENGTH];
	};

	class DialogueDrawRegion
	{
	public:
		DialogueDrawRegion() {
			next = NULL;
		}

		DialogueDrawRegion* next;

		uint16 left, top, right, bottom;
		uint16 startX, startY;
		byte   length;
		byte   characters[DIALOGUE_DRAW_REGION_LENGTH];
	};

	class DialogueDrawOperation
	{
	public:
		DialogueDrawOperation() {
			next = NULL;
			region = NULL;
		}

		~DialogueDrawOperation();

		DialogueDrawOperation* next;
		DialogueDrawRegion* region;
	};

	Dialogue* GetOrCreateDialogueFromText(const char* text);
	Dialogue* GetOrCreateDialogueFromHash(uint32 hash);
	void ReleaseDialogue(Dialogue* dialogue);

	void DesignDialogueDrawOp(Dialogue* dialogue);

}

#endif