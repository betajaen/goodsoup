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

	Font::Font(uint8 id) {

		ReadFile file;

		String path = String::format(GS_GAME_PATH "RESOURCE/FONT%ld.NUT", id);
		file.open(path.string());


		if (file.isOpen() == false) {
			error(GS_THIS, "Cannot open font file!");
			abort_quit_stop();
			return;
		}

		_readNutFont(DiskReader(file));
	}

	Font::~Font() {
		_data.release();
	}

	void Font::_readNutFont(DiskReader reader) {

		Buffer<uint8, uint16> _tempCharBuffer;

		TagPair animTag = reader.readSanTagPair();

#if defined(GS_CHECKED) && GS_CHECKED == 1
		if (animTag.isTag(GS_MAKE_ID('A','N','I','M')) == false) {
			error(GS_THIS, "This is not an NUT file! Missing ANIM tag got %s", animTag.tagStr());
			abort_quit_stop();
			return;
		}
#endif

		TagPair animHeader = reader.readSanTagPair();

#if defined(GS_CHECKED) && GS_CHECKED == 1
		if (animHeader.isTag(GS_MAKE_ID('A','H','D','R')) == false) {
			error(GS_THIS, "This is not an NUT file! Missing ANHD tag got %s!", animHeader.tagStr());
			abort_quit_stop();
			return;
		}
#endif

		reader.skip(2);
		_numChars = reader.readUInt16LE();

		if (_numChars > 256) {
			error(GS_THIS, "NUT file has too many characters %ld", _numChars);
			abort_quit_stop();
			return;
		}

		reader.seekEndOf(animHeader);


		uint32 dataSize = 0;
		uint32 tempDataSize = 0;

		// Calculate data size.
		uint32 largestWidth = 0, largestHeight = 0;

		for(uint16 i=0;i < _numChars;i++) {

			TagPair frme = reader.readSanTagPair();

#if defined(GS_CHECKED) && GS_CHECKED == 1
			if (frme.isTag(GS_MAKE_ID('F','R','M','E')) == false) {
				error(GS_THIS, "This is not an NUT file! Missing FRME tag got %s!", frme.tagStr());
				abort_quit_stop();
				return;
			}
#endif

			TagPair fobj = reader.readSanTagPair();

#if defined(GS_CHECKED) && GS_CHECKED == 1
			if (fobj.isTag(GS_MAKE_ID('F','O','B','J')) == false) {
				error(GS_THIS, "This is not an NUT file! Missing FOBJ tag got %s!", fobj.tagStr());
				abort_quit_stop();
				return;
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

			_chars[i]._rle._width = width;
			_chars[i]._rle._height = height;
			_chars[i]._rle._offsets[0] = 0;
			_chars[i]._rle._offsets[1] = 0;
			_chars[i]._size = width * height;

			dataSize += _chars[i]._size;
			reader.seekEndOf(fobj);
		}


		_tempCharBuffer.setSize(tempDataSize, MF_Clear);

		uint32 dstOffset = 0;
		_data.setSize(dataSize, MF_Clear);

		Buffer<byte, uint16> _tempGlyphBuffer;
		_tempGlyphBuffer.setSize(largestWidth * largestHeight);


		reader.seekEndOf(animHeader);

		for(uint16 i=0;i < _numChars-10;i++) {
			TagPair frme = reader.readSanTagPair();
			TagPair fobj = reader.readSanTagPair();

			FontChar& fontChar = _chars[i];
			reader.readBytes(_tempCharBuffer.ptr(0), fobj.length);

			if (_tempCharBuffer.get_unchecked(0) == 44) {

				byte* src = _tempCharBuffer.ptr(14);
				uint32 originalDstOffset = dstOffset;
				dstOffset += decodeNutFrame44ToRLE2(src, _data.ptr(dstOffset), _tempGlyphBuffer.ptr(0), fontChar._rle);

				for(uint16 i=0;i < _tempGlyphBuffer.getSize();i++) {
					_tempGlyphBuffer.set_unchecked(i, 0);
				}

				for(uint8 i=0;i < 2;i++) {
					fontChar._rle._offsets[i] += originalDstOffset;
				}
			}

		}

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

		debug(GS_THIS, "%s", text);

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

		debug(GS_THIS, "Font Number = %ld, Colour = %ld", (uint32) out_fontNum, (uint32) out_Colour);

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
