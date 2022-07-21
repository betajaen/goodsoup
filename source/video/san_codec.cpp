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

#define GS_FILE_NAME "codec"

#include "san_codec.h"
#include "../screen.h"
#include "../codecs/bomp.h"
#include "../font.h"

namespace gs
{

#define FOBJ_HDR_OP 0
#define FOBJ_HDR_EXTENDED 2
#define FOBJ_HDR_BOMP_LENGTH 12

	static Buffer<char, uint16> _tempText;

	SanCodec::SanCodec(DiskReader reader)
		: _diskReader(reader), _frameNum(0)
	{
		TagPair animTag = _diskReader.readSanTagPair();

#if defined(GS_CHECKED) && GS_CHECKED == 1
		if (animTag.isTag(GS_MAKE_ID('A','N','I','M')) == false) {
			error(GS_THIS, "This is not an ANIM SAN file! Missing ANIM tag got %s", animTag.tagStr());
			abort_quit_stop();
			return;
		}
#endif

		TagPair animHeader = _diskReader.readSanTagPair();

#if defined(GS_CHECKED) && GS_CHECKED == 1
		if (animHeader.isTag(GS_MAKE_ID('A','H','D','R')) == false) {
			error(GS_THIS, "This is not an ANIM SAN file! Missing ANHD tag got %s!", animHeader.tagStr());
			abort_quit_stop();
			return;
		}
#endif

		_diskReader.skip(2);
		_frameCount = _diskReader.readUInt16LE();
		_diskReader.skip(2);
		_readAndApplyPalette();
		_diskReader.seekEndOf(animHeader);
	}

	SanCodec::~SanCodec() {
	}

	void SanCodec::_readAndApplyPalette() {
		_diskReader.readBytes(&_palette.palette[0], 3 * 256);
		screenSetPalette(&_palette);
	}

	void SanCodec::_readAndApplyDeltaPalette(const TagPair& xpal) {

		if (xpal.length == 6) {
			_diskReader.skip(6);

			for(uint16 i=0;i < 768;i++) {
				uint16 s = _palette.palette[i];
				int16 d  = _deltaPalette[i];

				/* TODO: Optimise with a lookup table!
				 		 Otherwise it may be possible with bit-shifts to save on mem.
				 */
				int16 c = ((s * 129 + d) / 128);
				if (c > 255)
					c = 255;
				else if (c < 0)
					c = 0;
				_palette.palette[i] = (uint8) c;
			}
			screenSetPalette(&_palette);
		}
		else {
			_diskReader.skip(4);
			_diskReader.readBytes(&_deltaPalette[0], sizeof(_deltaPalette));
			_diskReader.readBytes(&_palette.palette[0], sizeof(_palette.palette));
			screenSetPalette(&_palette);
		}

	}

	void SanCodec::_readFrameObjectAndApply(const TagPair& fobj) {

		uint8 header[24];

		uint16 type = _diskReader.readUInt16LE();

		if (type != 47) {
			_diskReader.skip(fobj.length - 2);
			return;
		}

		_diskReader.skip(4);	// X,Y
		uint16 w = _diskReader.readUInt16LE();
		uint16 h = _diskReader.readUInt16LE();

		_diskReader.skip(4);	// Unknown

		uint16 seqNum = _diskReader.readUInt16LE();
		_diskReader.readBytes(&header, sizeof(header));

		if (header[FOBJ_HDR_EXTENDED] & 1) {
			_diskReader.skip(32896);
		}

		// debug(GS_THIS, "++ FOBJ %ld (%ld) %ld %ld ", type, (uint32) header[FOBJ_HDR_OP], w, h);

		switch(header[FOBJ_HDR_OP]) {

			case 0: {	// "Key Frame"
				_diskReader.readBytes(&_tempFrame[0], GS_BITMAP_SIZE);
				screenBlitCopy(&_tempFrame[0]);
			}
			break;
			case 5: {	// BOMP Compressed Frame
				uint32 length = READ_LE_UINT32(&header[FOBJ_HDR_BOMP_LENGTH]);

#if defined(GS_CHECKED) && GS_CHECKED == 1
				if (length > GS_BITMAP_SIZE) {
					error(GS_THIS, "BOMP Frame Length to large! %ld", length);
					abort_quit_stop();
					return;
				}
#endif

				_diskReader.readBytes(&_tempBuffer[0], length);
				decodeBomp(&_tempFrame[0], &_tempBuffer[0], length);
				screenBlitCopy(&_tempFrame[0]);

			}
			break;

		}


		_diskReader.seekEndOf(fobj);
	}

	void SanCodec::_readAndApplyText(const TagPair& text) {
		uint16 x = _diskReader.readUInt16LE();
		uint16 y = _diskReader.readUInt16LE();
		uint16 flags = _diskReader.readUInt16LE();
		uint16 x0 = _diskReader.readUInt16LE();
		uint16 y0 = _diskReader.readUInt16LE();
		uint16 right = _diskReader.readUInt16LE();

		_diskReader.skip(4);
		uint16 length = text.length - 16;

		if (_tempText.getSize() < length) {
			_tempText.setSize(8 + length);
		}

		_diskReader.readBytes(_tempText.ptr(0), length);

		drawSubtitles(x, y, _tempText.ptr(0));
	}

	int32 SanCodec::presentFrame() {

		TagPair frme = _diskReader.readSanTagPair();

#if defined(GS_CHECKED) && GS_CHECKED == 1
		if (frme.isTag(GS_MAKE_ID('F','R','M','E')) == false) {
			error(GS_THIS, "This is not an ANIM SAN file! Missing FRME tag got %s!", frme.tagStr());
			abort_quit_stop();
		}
#endif

		while(_diskReader.pos() < frme.end()) {
			TagPair tag = _diskReader.readSanTagPair();

			//debug(GS_THIS, "Frame %ld %s %ld", _frameNum, tag.tagStr(), tag.length);

			if (tag.isTag(GS_MAKE_ID('N','P','A','L'))) {
				_readAndApplyPalette();
				continue;
			}

			if (tag.isTag(GS_MAKE_ID('I','A','C','T'))) {
				_diskReader.skip(tag.length);
				continue;
			}

			if (tag.isTag(GS_MAKE_ID('F','O','B','J'))) {
				_readFrameObjectAndApply(tag);
				continue;
			}

			if (tag.isTag(GS_MAKE_ID('X','P','A','L'))) {
				_readAndApplyDeltaPalette(tag);
				continue;
			}

			if (tag.isTag(GS_MAKE_ID('T','E','X','T'))) {
				_readAndApplyText(tag);
				continue;
			}

			if (tag.isTag(GS_MAKE_ID('S','T','O','R'))) {
				_diskReader.skip(tag.length);
				continue;
			}

			if (tag.isTag(GS_MAKE_ID('F','T','C','H'))) {
				_diskReader.skip(tag.length);
				continue;
			}

			error(GS_THIS, "Unhandled tag %s", tag.tagStr());
			abort_quit_stop();
			_frameNum = _frameCount;
			return -1;
		}

		_frameNum++;

		if (_frameNum == _frameCount) {
			return -1;
		}
		else {
			return 1;
		}
	}
}