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
		file.writeBytes(&font._chars[0], sizeof(FontChar) * font._numChars);
		file.writeUInt32BE(dataSize);
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
		file.readBytes(&font._chars[0], sizeof(FontChar) * font._numChars);
		uint32 dataSize = file.readUInt32BE();
		font._data.setSize(dataSize);
		file.readBytes(font._data.ptr(0), dataSize);
		file.close();

		return true;
	}

	static uint32 _parseNutFont(Font& font, DiskReader reader);

	static uint32 loadFontNUTFile(Font& font, uint8 id) {
		ReadFile file;

		String path = String::format(GS_GAME_PATH "RESOURCE/FONT%ld.NUT", id);
		file.open(path.string());


		if (file.isOpen() == false) {
			error(GS_THIS, "Cannot open font file!");
			abort_quit_stop();
			return 0;
		}

		return _parseNutFont(font, DiskReader(file));
	}

	static uint32 _parseNutFont(Font& font, DiskReader reader) {

		Buffer<uint8, uint16> _tempCharBuffer;

		TagPair animTag = reader.readSanTagPair();

#if defined(GS_CHECKED) && GS_CHECKED == 1
		if (animTag.isTag(GS_MAKE_ID('A','N','I','M')) == false) {
			error(GS_THIS, "This is not an NUT file! Missing ANIM tag got %s", animTag.tagStr());
			abort_quit_stop();
			return 0;
		}
#endif

		TagPair animHeader = reader.readSanTagPair();

#if defined(GS_CHECKED) && GS_CHECKED == 1
		if (animHeader.isTag(GS_MAKE_ID('A','H','D','R')) == false) {
			error(GS_THIS, "This is not an NUT file! Missing ANHD tag got %s!", animHeader.tagStr());
			abort_quit_stop();
			return 0;
		}
#endif

		reader.skip(2);
		font._numChars = reader.readUInt16LE();

		if (font._numChars > 256) {
			error(GS_THIS, "NUT file has too many characters %ld", font._numChars);
			abort_quit_stop();
			return 0;
		}

		reader.seekEndOf(animHeader);


		uint32 dataSize = 0;
		uint32 tempDataSize = 0;

		// Calculate data size.
		uint32 largestWidth = 0, largestHeight = 0;

		for(uint16 i=0;i < font._numChars;i++) {

			TagPair frme = reader.readSanTagPair();

#if defined(GS_CHECKED) && GS_CHECKED == 1
			if (frme.isTag(GS_MAKE_ID('F','R','M','E')) == false) {
				error(GS_THIS, "This is not an NUT file! Missing FRME tag got %s!", frme.tagStr());
				abort_quit_stop();
				return 0;
			}
#endif

			TagPair fobj = reader.readSanTagPair();

#if defined(GS_CHECKED) && GS_CHECKED == 1
			if (fobj.isTag(GS_MAKE_ID('F','O','B','J')) == false) {
				error(GS_THIS, "This is not an NUT file! Missing FOBJ tag got %s!", fobj.tagStr());
				abort_quit_stop();
				return 0;
			}
#endif

			uint32 imgSize = fobj.length;
			reader.skip(6);
			uint16 width = reader.readUInt16LE();	// 8-10
			uint16 height = reader.readUInt16LE();	// 11-12

			if (imgSize > tempDataSize) {
				tempDataSize = imgSize;
			}

			if (largestWidth < width) {
				largestWidth = width;
			}

			if (largestHeight < height) {
				largestHeight = height;
			}

			font._chars[i]._rle._width = width;
			font._chars[i]._rle._height = height;
			font._chars[i]._rle._offsets[0] = 0;
			font._chars[i]._rle._offsets[1] = 0;
			font._chars[i]._size = width * height;

			dataSize += font._chars[i]._size;
			reader.seekEndOf(fobj);
		}


		_tempCharBuffer.setSize(tempDataSize, MF_Clear);	// Estimated

		uint32 dstOffset = 0;
		font._data.setSize(dataSize, MF_Clear);

		Buffer<byte, uint16> _tempGlyphBuffer;
		_tempGlyphBuffer.setSize(largestWidth * largestHeight);

		reader.seekEndOf(animHeader);

		uint32 actualDataSize = 0;

		for(uint16 i=0;i < font._numChars-10;i++) {
			TagPair frme = reader.readSanTagPair();
			TagPair fobj = reader.readSanTagPair();

			FontChar& fontChar = font._chars[i];
			reader.readBytes(_tempCharBuffer.ptr(0), fobj.length);

			if (_tempCharBuffer.get_unchecked(0) == 44) {

				byte* src = _tempCharBuffer.ptr(14);
				uint32 originalDstOffset = dstOffset;
				dstOffset += decodeNutFrame44ToRLE2(src, font._data.ptr(dstOffset), _tempGlyphBuffer.ptr(0), fontChar._rle);

				// Clear image
				for(uint16 i=0;i < _tempGlyphBuffer.getSize();i++) {
					_tempGlyphBuffer.set_unchecked(i, 0);
				}

				// Append offsets to font char
				for(uint8 i=0;i < 2;i++) {
					fontChar._rle._offsets[i] += originalDstOffset;
				}

				actualDataSize = fontChar._rle._offsets[1];
			}
		}

		return actualDataSize;
	}


	Font::Font(uint8 id) {

		if (loadFontRLEFile(*this, id)) {
			return;
		}

		uint32 dataSize = loadFontNUTFile(*this, id);

		if (dataSize != 0) {
			saveFontRLEFile(*this, id, dataSize);
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

			FontChar& fontChar = _chars[ch];

			_clearGlyphBytes(5);
			// screenGrab(x,y, fontChar._rle._width, fontChar._rle._height, &glyphBytes[0]);
			drawRLEImage2(0,0,fontChar._rle, _data.ptr(0), &glyphBytes[0], 32, colours);
			screenBlitBitmap(x,y, fontChar._rle._width, fontChar._rle._height, &glyphBytes[0]);

			x += fontChar._rle._width;
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
	}

	int16 Font::calculateFontWidth(const char* text) {
#if defined(GS_CHECKED) && GS_CHECKED == 1
		if (text == NULL)
			return 0;
#endif

		int16 width = 0;
		while(*text != 0) {
			FontChar& fontChar = _chars[*text];
			width += fontChar._rle._width;
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

	void drawSubtitles(uint32 x, uint32 y, const char* text, bool center) {
		/* REMOVED */
	}

	void drawSubtitlesFrom(byte* background, int16 x, int16 y, const char* text, bool center, uint8 fontNum, uint8 colourNum) {

		if (fontNum >= MAX_FONTS) {
			warn(GS_THIS, "Cannot display dialogue %s with given font num %ld", text, (uint32) fontNum);
			return;
		}

		Font* font = FONT[fontNum];
		int16 originalX = x;

		uint8 colours[2] = {
				colourNum,
				0x00
		};

		uint32 width = 0;
		if (center) {
			width = font->calculateFontWidth(text);
		}

		originalX -= width;

		while(true) {

			char ch = *text;
			text++;

			if (ch == 0)
				return;

			if (ch >= font->_numChars)
				continue;

			FontChar& fontChar = font->_chars[ch];

			if (ch < 32) {
				if (ch == '\r') {
					y += fontChar._rle._height;
				}
				else if (ch == '\n') {
					x = originalX;
				}
				continue;
			}

			int16 r = x + fontChar._rle._width;
			int16 b = y + fontChar._rle._height;
			bool inBounds = (x >=0 && r < GS_BITMAP_PITCH && y > 0 && b < GS_BITMAP_ROWS);

			if (inBounds) {
				_grabGlyph(background, GS_BITMAP_PITCH, x, y, fontChar._rle._width, fontChar._rle._height);
				drawRLEImage2(0, 0, fontChar._rle, font->_data.ptr(0), &glyphBytes[0], 32, colours);
				screenBlitBitmap(x, y, fontChar._rle._width, fontChar._rle._height, &glyphBytes[0]);
			}

			x += fontChar._rle._width;

		}


	}
}
