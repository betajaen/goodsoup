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

#ifndef GS_FONT_H
#define GS_FONT_H

#include "forward.h"
#include "containers.h"
#include "disk.h"
#include "codecs/rle.h"

namespace gs
{

	class Font
	{
	public:

		uint16               _numChars;
		Buffer<byte, uint16> _data;
		RLEImage64 	 		 _chars[256];

		Font(uint8 id);
		~Font();

		void drawText(uint32 x, uint32 y, const char* text);
		int16 calculateFontWidth(const char* text);
	};

	enum SubtitleKind
	{
		// Spoken Dialogue
		// An actor or subject on the screen is talking
		// "Lost at sea for days now. I have no crew or navigational instruments."
		SK_Spoken = 0,
		// Exposition Text
		// Text on the screen is describing an place, event or idea that isnt obvious to the player
		// "Monkey Island"
		SK_Exposition = 1,
		// Credit
		// Text on the screen of a name, or entity that contributed to the game
		SK_Credit = 2
	};

	extern Font* FONT[5];

	const char* parseFormattedDialogue(const char* text, uint32& out_translationHash, uint8& out_fontNum, uint8& out_Colour);
	bool parseFormattedDialogue2(const char* text, char* out_text, uint32 &out_translationHash, uint8 &out_fontNum, uint8 &out_Colour);

	void drawSubtitles(uint32 x, uint32 y, const char* text, bool center = false);
	void drawSubtitlesFrom(byte* background, int16 x, int16 y, const char* text, bool center, bool wrap, uint8 fontNum, uint8 colourNum);
	void drawSubtitlesFromAgain(byte* background);

	void printDialogue(const char* text, uint32 id, uint8 kind);
}

#endif