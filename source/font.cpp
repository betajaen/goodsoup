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

			dataSize += width * height;

			_chars[i]._width = width;
			_chars[i]._height = height;

			reader.seekEndOf(fobj);
		}


		_tempCharBuffer.setSize(tempDataSize, MF_Clear);

		uint32 dstOffset = 0;
		_data.setSize(dataSize, 0);

		reader.seekEndOf(animHeader);

		for(uint16 i=0;i < _numChars;i++) {
			TagPair frme = reader.readSanTagPair();
			TagPair fobj = reader.readSanTagPair();

			FontChar& fontChar = _chars[i];
			reader.readBytes(_tempCharBuffer.ptr(0), fobj.length);

			//debug(GS_THIS, "%ld Codec=%ld Width=%ld Height=%ld", i, _tempCharBuffer.get_unchecked(0), fontChar._width, fontChar._height);

			if (_tempCharBuffer.get_unchecked(0) == 44) {

				fontChar._offset = dstOffset;

				byte* dst = _data.ptr(dstOffset);
				byte* src = _tempCharBuffer.ptr(22);
				uint32 srcLength = fobj.length - 22;

				for(uint16 y=0;y < fontChar._height;y++) {

					byte* x = dst;
					byte* nextSrc = src + 2 + READ_LE_UINT16(src);
					src+=2;

					debug(GS_THIS, "Width = %ld, Y = %ld", fontChar._width, y);

					int16 len = fontChar._width;

					do {

						int16 transparentLength = READ_LE_UINT16(src);
						src += 2;
						x += transparentLength;
						len -= transparentLength;

						if (transparentLength <= 0)
							break;


						int16 matteLength = READ_LE_UINT16(src) + 1;
						src += 2;
						len -= matteLength;

						if (len < 0) {
							matteLength += len;
						}

						src += matteLength;
						while(matteLength--) {
							*x++ = 50;	// Colour.
						}



					} while(len > 0);

					x = dst + fontChar._width;
					src = nextSrc;
				}

				dstOffset = (dst - _data.ptr(0));
			}

		}

	}

	void Font::drawText(uint32 x, uint32 y, const char* text) {
		while(true) {
			char ch = *text;
			text++;
			if (ch == 0)
				return;

			FontChar& fontChar = _chars[ch];
			byte* fontData = _data.ptr(fontChar._offset);

			screenBlitBitmap(x, y, fontChar._width, fontChar._height, fontData);

			x += fontChar._width;
		}
	}


}
