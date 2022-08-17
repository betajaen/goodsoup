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

#define GS_FILE_NAME "font"

#include "font.h"
#include "debug.h"
#include "disk.h"
#include "file.h"
#include "screen.h"
#include "codecs/nut.h"
#include "profile.h"
#include "hash.h"

#define GS_TEXT_SAFE_PITCH (GS_BITMAP_PITCH - 40)

namespace gs
{
	Font* FONT[5] = { NULL} ;

	static byte glyphBytes[64*64] = { 0 };

	static void _clearGlyphBytes(uint8 col) {
		const uint32 colour = col << 24 | col << 16 | col << 8 | col;
		uint32* g = (uint32*) &glyphBytes[0];
		uint32 len = sizeof(glyphBytes) / sizeof(uint32);
		while(len--) {
			*g++ = colour;
		}
	}

	static void _grabGlyph(byte* src, uint32 stride, uint32 x, uint32 y, uint32 w, uint32 h) {
		/* TODO: Optimise */

		byte* dst = &glyphBytes[0];
		byte* s = src + x + (y * stride);

		while(h--) {
			byte* nextSrc = s + stride;

			uint16 l = w;

			while(l--) {
				*dst++ = *s++;
			}

			s = nextSrc;
		}
	}

	static void saveFontRLEFile(const Font& font, uint8 id, uint32 dataSize) {
		WriteFile file;
		String path = String::format(GS_GAME_PATH "FONT%ld.GSF", id);
		file.open(path.string());

		if (file.isOpen() == false) {
			error(GS_THIS, "Cannot open font file to save to!");
			abort_quit_stop();
			return;
		}

		file.writeUInt16BE(font._numChars);
		file.writeBytes(&font._chars[0], sizeof(RLEImage64) * font._numChars);
		file.writeUInt16BE(dataSize);
		file.writeBytes(font._data.ptr(0), dataSize);
		file.close();
	}

	static bool loadFontRLEFile(Font& font, uint8 id) {
		ReadFile file;
		String path = String::format(GS_GAME_PATH "FONT%ld.GSF", id);
		file.open(path.string(), false);

		if (file.isOpen() == false) {
			return false;
		}

		font._numChars = file.readUInt16BE();
		file.readBytes(&font._chars[0], sizeof(RLEImage64) * font._numChars);
#if GS_BIG
		uint16 dataSize = file.readUInt16BE();
#else
		uint16 dataSize = file.readUInt16LE();
#endif
		font._data.setSize(dataSize);
		file.readBytes(font._data.ptr(0), dataSize);
		file.close();

		return true;
	}

	static uint32 _parseNutFont(Font& font, DiskReader reader);

	Font::Font(uint8 id) {

		// if (loadFontRLEFile(*this, id)) {
		// 	return;
		// }

		if (convertNutFontToRleFont(id) == false) {
			return;
		}

		if (loadFontRLEFile(*this, id)) {
			return;
		}


	}

	Font::~Font() {
		_numChars = 0;
		_data.release();
	}


	void Font::drawText(uint32 x, uint32 y, const char* text) {

		uint8 colours[2] = {
				0,
				16
		};


		while(true) {
			char ch = *text;
			text++;
			if (ch == 0)
				return;

			if (x > GS_BITMAP_PITCH || y > GS_BITMAP_ROWS)
				return;

			RLEImage64& fontImg = _chars[ch];


			_clearGlyphBytes(5);
			// screenGrab(x,y, fontImg._width, fontImg._height, &glyphBytes[0]);
			drawRLEImage64(0,0,fontImg, _data.ptr(0), &glyphBytes[0], 32, colours);
			screenBlitBitmap(x,y, fontImg._width, fontImg._height, &glyphBytes[0]);

			x += fontImg._width;
		}
	}

	inline uint8 readNum(const char*& text) {
		uint8 num = 0;
		uint8 count = 3;
		while(count--) {
			char ch = *text;
			if (ch < '0' || ch > '9')
				return num;
			num *= 10;
			num += ch - '0';
			text++;
		}
		return num;
	}

	int16 Font::calculateFontWidth(const char* text) {
#if defined(GS_CHECKED) && GS_CHECKED == 1
		if (text == NULL)
			return 0;
#endif

		int16 width = 0;
		while(*text != 0) {
			RLEImage64& fontImg = _chars[*text];
			width += fontImg._width;
			text++;
		}

		return width;
	}

	const char* parseFormattedDialogue(const char* text, uint32& out_translationHash, uint8& out_fontNum, uint8& out_Colour) {
#if defined(GS_CHECKED) && GS_CHECKED == 1
		if (text == NULL)
			return NULL;
#endif

		if (*text == '\0')
			return text;

		if (*text == '/') {
			HashBuilder hb;
			text++;

			while(*text != '\0' && *text != '/') {
				hb.feed(*text);
				text++;
			}

			out_translationHash = hb.hash;

			if (*text == '\0')
				return text;

			text++;
		}


		for(uint8 i=0;i < 2;i++) {

			if (*text == '^') {
				text++;
#if defined(GS_CHECKED) && GS_CHECKED == 1
				if (*text == '\0')
					return text;
#endif
				if (*text == 'f') {
					text++;
					out_fontNum = readNum(text);
#if defined(GS_CHECKED) && GS_CHECKED == 1
					if (*text == '\0')
						return text;
#endif
				}

				else if (*text == 'c') {
					text++;
					out_Colour = readNum(text);
#if defined(GS_CHECKED) && GS_CHECKED == 1
					if (*text == '\0')
						return text;
#endif
				}
			}
		}

		return text;
	}

	inline bool isSpace(char ch) {
		return ch > 0 && ch <= 32;
	}

	inline uint8 readNum(char *&text) {
		uint8 num = 0;
		uint8 count = 3;
		while (count--) {
			char ch = *text;
			if (ch < '0' || ch > '9')
				return num;
			num *= 10;
			num += ch - '0';
			text++;
		}
		return num;
	}

	bool parseFormattedDialogue2(const char* text, char* out_text, uint32 &out_translationHash, uint8 &out_fontNum, uint8 &out_Colour, uint8 &out_kind, uint16& out_Length) {

		CHECK_IF_RETURN(text == NULL, false, "Text is NULL");

		out_Length = 0;

		// Empty text
		if (*text == '\0') {
			return false;
		}

		// Read in the translation marker, this is turned into a hash so the dialogue can be identified
		// and used with caching later.
		// This is usually in the form of, and always starts at the beginning of the string
		// 		/xyx_123/

		if (*text == '/') {
			HashBuilder hb;
			text++;

			out_kind = SK_Spoken;

			// Determine Dialogue kind
			//	Seen in the forms of (in upper and lower-case)
			//		/ec_xxx/			Credits
			//		/ec__xxx/			Credits
			//		/ds_xxx/			Exposition
			//		/ds__xxx/			Exposition
			if (text[2] == '_') {
				if (text[0] == 'd' || text[0] == 'D') {
					if (text[1] == 's' || text[1] == 'S') {
						out_kind = SK_Exposition;
					}
				}
				else if (text[0] == 'e' || text[0] == 'E') {
					if (text[1] == 'c' || text[1] == 'C') {
						out_kind = SK_Credit;
					}
				}
			}

			while(*text != '\0' && *text != '/') {
				hb.feed(*text);
				text++;
			}

			out_translationHash = hb.hash;

			text++;
		}

		// Just the translation tag
		if (*text == '\0' || *text == '\r')
			return false;

		// Read in Font and Colour Codes these are in the form of
		// ^fxx			-- Font typeface x (decimal)
		// ^c0xxx		-- Colour of xx (decimal)
		// These can be in any order, or none at all.
		for(uint8 i=0;i < 2;i++) {

			if (*text == '^') {
				text++;
#if defined(GS_CHECKED) && GS_CHECKED == 1
				if (*text == '\0')
					return false;
#endif
				if (*text == 'f') {
					text++;
					out_fontNum = readNum(text);
#if defined(GS_CHECKED) && GS_CHECKED == 1
					if (*text == '\0')
						return false;
#endif
				}

				else if (*text == 'c') {
					text++;
					out_Colour = readNum(text);
#if defined(GS_CHECKED) && GS_CHECKED == 1
					if (*text == '\0')
						return false;
#endif
				}
			}
		}

		// There are cases of dialogue with just a translation marker and a control code
		// We should return false in that case.

		// Just the translation tag
		if (*text == '\0' || *text == '\r')
			return false;

		bool lastWasNl = false;
		bool lastWasSpace = false;

		// String Copy the rest of the text.
		while(*text != 0) {
			// Skip all non-space white-space and control characters. This is partly to remove unwanted
			// characters but to apply trimming as well (a bit lower down)
			if (*text <= 32) {
				if (*text == '\n') {
					lastWasNl = true;
				}
				if (*text == ' ') {
					lastWasSpace = true;
				}
				text++;
				continue;
			}

			// If there was a newline \r\n (usually), add it back in but in LF format. This handles right-trimming
			// of \r\n in SMUSH dialogue sequences
			if (lastWasNl) {
				lastWasNl = false;
				*out_text = '\n';
				out_text++;
				out_Length++;
			}

			// If there was a " ", add it back in. This handles left and right trimming.
			if (lastWasSpace) {
				lastWasSpace = false;
				*out_text = ' ';
				out_text++;
				out_Length++;
			}

			// Copy a Normal character over
			*out_text++ = *text++;
			out_Length++;
		}

		// Dont forget the null!
		*out_text = '\0';

		return true;
	}

	void drawSubtitles(uint32 x, uint32 y, const char* text, bool center) {
		/* REMOVED */
	}

#define MAX_LINES 16

	static int16 linesX[MAX_LINES];
	static int16 linesY[MAX_LINES];
	static uint8  linesLengths[MAX_LINES];
	static uint16 linesWidth[MAX_LINES];
	static const char* linesText[MAX_LINES];
	static uint8  numLines = 0;
	static Font*  lineFont;
	static uint8  lineColour[2];

	static void prepareLines(uint8 fontNum, int16 x, int16 y, const char* text, bool wrap, bool centre) {

		CHECK_IF(fontNum >= MAX_FONTS, "Out of range for font");
		lineFont = FONT[fontNum];

		if (wrap == false) {
			numLines = 1;
			linesX[0] = 0;
			linesY[0] = y;
			linesLengths[0] = 0xFF;
			linesText[0] = text;
			uint8 length = 0;

			int16 width = 0;
			int16 height = lineFont->_chars['M']._height;

			for(uint8 i=0;i < 255;i++) {

				char ch = text[i];

				if (ch == 0)
					break;

				length++;
				RLEImage64 &fontImg = lineFont->_chars[ch];
				width += fontImg._width;
			}

			linesWidth[0] = width;
			linesLengths[0] = length;

			linesX[0] = centre ? (x - width / 2) : x;

			int16 x0 = x;
			int16 y0 = y;
			int16 x1 = width;
			int16 y1 = y + height;

			bool inBounds = (x0 >= 0 && x0 < GS_BITMAP_PITCH && y0 > 0 && y1 < GS_BITMAP_ROWS);

			if (inBounds == false) {
				numLines = 0;
			}
		}
		else {
			numLines = 0;
			const char* begin = text;
			const char* space = begin;
			const char* it = begin;

			int16 width = 0;
			int16 lineHeight = lineFont->_chars['M']._height;
			uint8 length = 0;
			uint8 spaceLength = 0;
			int16 y0 = y;
			int16 y1 = y + lineHeight;
			bool trim = false;


			while(true) {
				char ch = *it;

				if (ch == 0) {
					linesX[numLines] = x;
					linesY[numLines] = y;
					linesLengths[numLines] = 0xFF;
					linesText[numLines] = begin;
					linesWidth[numLines] = width;
					y += lineHeight;
					y1 += lineHeight;
					numLines++;
					break;
				}

				// do trim on new lines
				if (trim && ch == ' ') {
					length = 0;
					it++;
					begin = it;
					continue;
				}

				trim = false;
				length++;

				if (ch < 32) {
					it++;
					continue;
				}

				if (ch == ' ') {
					// does the space come after a . or , if so we should use that.
					if (length > 1 && (it[-1] == '.' || it[-1] == ',')) {
						space = it-1;
						spaceLength = length;
					}
					else {
						space = it;
						spaceLength = length;
					}

				}

				RLEImage64 &fontImg = lineFont->_chars[ch];
				width += fontImg._width;

				if (width > GS_TEXT_SAFE_PITCH) {
					linesX[numLines] = x;
					linesY[numLines] = y;
					linesLengths[numLines] = spaceLength;
					linesText[numLines] = begin;
					linesWidth[numLines] = width;
					y += lineHeight;
					y1 += lineHeight;
					length = 0;
					width = 0;
					numLines++;
					it = space+1;
					begin = space+1;
					trim = true;
					continue;
				}

				it++;
			}

			// Center? - Center to screen
			if (centre) {

				// Temp. 
				if (x <= GS_BITMAP_PITCH / 2) {
					x = GS_BITMAP_PITCH / 2;
				}

				for(uint8 i=0;i < numLines;i++) {
					linesX[i] = x - linesWidth[i] / 2;
				}
			}

			// Shift up.
			if (y1 > GS_BITMAP_ROWS) {
				int16 diff = y1 - GS_BITMAP_ROWS;
				for (uint8 i = 0; i < numLines; i++) {
					linesY[i] -= diff;
				}
			}


		}

		//debug(GS_THIS, "F%ld W%ld C%ld L%d", fontNum , wrap, centre, numLines);

		//for(uint8 i=0;i < numLines;i++) {
		//	debug(GS_THIS, "L%ld X%ld Y%ld \"%s\"", i, linesX[i], linesY[i], linesText[i]);
		//}

	}

	static void _drawSubtitlesImpl(byte* background) {

		for(uint8 i=0;i < numLines;i++) {
			uint16 x = linesX[i];
			uint16 y = linesY[i];
			uint8 length = linesLengths[i];
			const char* str = linesText[i];

			/* TODO: Grab background for entire line */

			for(uint8 j=0;j < length;j++) {
				char ch = str[j];
				if (ch == 0)
					break;

				if (ch < 32)
					continue;

				RLEImage64& fontImg = lineFont->_chars[ch];
				int16 r = x + fontImg._width;
				int16 b = y + fontImg._height;

				bool inBounds = (x >=0 && r < GS_BITMAP_PITCH && y >= 0 && b < GS_BITMAP_ROWS);

				if (inBounds == false) {
					break;
				}

				/* TODO: just draw RLE image at x,y on image */

				_grabGlyph(background, GS_BITMAP_PITCH, x, y, fontImg._width, fontImg._height);
				drawRLEImage64(0, 0, fontImg, lineFont->_data.ptr(0), &glyphBytes[0], fontImg._width, lineColour);
				screenBlitBitmap(x, y, fontImg._width, fontImg._height, &glyphBytes[0]);

				x += fontImg._width;
			}

			/* TODO: Copy entire text onto image as is */

		}	}

	void drawSubtitlesFromAgain(byte* background) {
		_drawSubtitlesImpl(background);
	}

	void drawSubtitlesFrom(byte* background, int16 x, int16 y, const char* text, bool center, bool wrap, uint8 fontNum, uint8 colourNum) {

		prepareLines(fontNum, x, y, text, wrap, center);

		lineColour[0] = 0xFF;
		lineColour[1] = 0x00;

		_drawSubtitlesImpl(background);
	}


	static void _drawSubtitlesImplTo(byte* dstFrameBuffer) {

		for(uint8 i=0;i < numLines;i++) {
			uint16 x = linesX[i];
			uint16 y = linesY[i];
			uint8 length = linesLengths[i];
			const char* str = linesText[i];

			/* TODO: Grab background for entire line */

			for(uint8 j=0;j < length;j++) {
				char ch = str[j];
				if (ch == 0)
					break;

				if (ch < 32)
					continue;

				RLEImage64& fontImg = lineFont->_chars[ch];
				int16 r = x + fontImg._width;
				int16 b = y + fontImg._height;

				bool inBounds = (x >=0 && r < GS_BITMAP_PITCH && y >= 0 && b < GS_BITMAP_ROWS);

				if (inBounds == false) {
					break;
				}

				drawRLEImage64(x, y, fontImg, lineFont->_data.ptr(0), dstFrameBuffer, GS_BITMAP_PITCH, lineColour);

				x += fontImg._width;
			}

			/* TODO: Copy entire text onto image as is */

		}	}

	void drawSubtitlesToAgain(byte* dstFrameBuffer) {
		_drawSubtitlesImplTo(dstFrameBuffer);
	}

	void drawSubtitlesTo(byte* dstFrameBuffer, int16 x, int16 y, const char* text, bool center, bool wrap, uint8 fontNum, uint8 colourNum) {

		prepareLines(fontNum, x, y, text, wrap, center);

		lineColour[0] = 0xFF;
		lineColour[1] = 0x00;

		_drawSubtitlesImplTo(dstFrameBuffer);
	}

	static uint32 lastPrintedId = 0;

	void printDialogue(const char* text, uint32 id, uint8 kind) {
		if (lastPrintedId == id)
			return;

		lastPrintedId = id;

		if (kind == SK_Spoken) {
			debug_write_hex(id);
			debug_write_char('>');
			debug_write_str(text);
			debug_write_char('\n');
		}
		else if (kind == SK_Exposition) {
			debug_write_hex(id);
			debug_write_char(':');
			debug_write_str(text);
			debug_write_char('\n');
		}
	}

}
