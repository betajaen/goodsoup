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

namespace gs
{
	Font* FONT0 = NULL;

	Font::Font(uint8 id) {

		ReadFile file;
		file.open(GS_GAME_PATH "RESOURCE/FONT1.NUT");

		if (file.isOpen() == false) {
			error(GS_THIS, "Cannot open font file!");
			abort_quit_stop();
			return;
		}

		_readNutFont(DiskReader(file), true);
	}

	Font::~Font() {
		_data.release();
	}

	void Font::_readNutFont(DiskReader reader, bool isRLE2) {
		if (isRLE2) {
			_readNutRLE2(reader);
		}
		else {
			_readNut44(reader);
		}
	}

	void Font::_readNut44(DiskReader reader) {


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
		uint16 _numChars = reader.readUInt16LE();

		if (_numChars > 256) {
			error(GS_THIS, "NUT file has too many characters %ld", _numChars);
			abort_quit_stop();
			return;
		}

		reader.seekEndOf(animHeader);


		uint32 dataSize = 0;
		uint32 tempDataSize = 0;

		// Calculate data size.

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

			_chars[i]._rle._width = width;
			_chars[i]._rle._height = height;
			_chars[i]._size = width * height;
			_chars[i]._offset = 0;

			dataSize += _chars[i]._size;
			reader.seekEndOf(fobj);
		}


		_tempCharBuffer.setSize(tempDataSize, MF_Clear);

		uint32 dstOffset = 0;
		_data.setSize(dataSize, MF_Clear);

		for(uint32 i=0;i < _data.getSize();i++) {
			_data.set_unchecked(i, 30);
		}

		reader.seekEndOf(animHeader);

		for(uint16 i=0;i < _numChars-10;i++) {
			TagPair frme = reader.readSanTagPair();
			TagPair fobj = reader.readSanTagPair();

			FontChar& fontChar = _chars[i];
			reader.readBytes(_tempCharBuffer.ptr(0), fobj.length);

			if (_tempCharBuffer.get_unchecked(0) == 44) {
				fontChar._offset = dstOffset;
				byte* src = _tempCharBuffer.ptr(14);
				decodeNutFrame44ToBitmap(src, _data.ptr(dstOffset), fontChar._rle._width, fontChar._rle._height);
			}

			dstOffset += fontChar._size;

		}

	}

	void Font::_readNutRLE2(DiskReader reader) {

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
		uint16 _numChars = reader.readUInt16LE();

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
			_chars[i]._size = width * height;
			_chars[i]._offset = 0;

			dataSize += _chars[i]._size;
			reader.seekEndOf(fobj);
		}


		_tempCharBuffer.setSize(tempDataSize, MF_Clear);

		uint32 dstOffset = 0;
		_data.setSize(dataSize);

		Buffer<byte, uint16> _tempGlyphBuffer;
		_tempGlyphBuffer.setSize(largestWidth * largestHeight);


		reader.seekEndOf(animHeader);

		for(uint16 i=0;i < _numChars-10;i++) {
			TagPair frme = reader.readSanTagPair();
			TagPair fobj = reader.readSanTagPair();

			FontChar& fontChar = _chars[i];
			reader.readBytes(_tempCharBuffer.ptr(0), fobj.length);

			if (_tempCharBuffer.get_unchecked(0) == 44) {
				fontChar._offset = dstOffset;
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

		abort_quit_stop();
	}

	void Font::drawText(uint32 x, uint32 y, const char* text) {
		while(true) {
			char ch = *text;
			text++;
			if (ch == 0)
				return;

			if (x > GS_BITMAP_PITCH || y > GS_BITMAP_ROWS)
				return;

			FontChar& fontChar = _chars[ch];

			if (fontChar._offset != 0) {
				byte *fontData = _data.ptr(fontChar._offset);
				screenBlitBitmap(x, y, fontChar._rle._width, fontChar._rle._height, fontData);
			}
			else {
				/* TODO */
			}

			x += fontChar._rle._width;
		}
	}

	void drawSubtitles(uint32 x, uint32 y, const char* text) {
		Font* font = FONT0;
		bool skipSlash = false;
		while(true) {

			if (x > GS_BITMAP_PITCH || y > GS_BITMAP_ROWS)
				return;

			char ch = *text;
			text++;

			if (ch == 0)
				return;

			if (ch == '/') {

				text++;

				while(true) {
					char ch = *text;
					text++;

					if (ch == 0)
						return;

					if (ch == '/') {
						break;
					}
				}

				continue;
			}

			if (ch == '^') {
				ch = *text;
				if (ch == 'f') {
					text += 3;
				}
				else if (ch == 'c') {
					text += 4 ;
				}
				continue;
			}

			FontChar& fontChar = font->_chars[ch];

			if (fontChar._offset != 0) {
				byte* fontData = font->_data.ptr(fontChar._offset);
				screenBlitBitmap(x, y, fontChar._rle._width, fontChar._rle._height, fontData);
			}
			else {

			}
			x += fontChar._rle._width;

		}

	}

}
