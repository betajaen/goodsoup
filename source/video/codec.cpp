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

#include "codec.h"
#include "../screen.h"

namespace gs
{

	Codec::Codec(DiskReader reader)
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

	Codec::~Codec() {
	}

	void Codec::_readAndApplyPalette() {
		_diskReader.readBytes(&_palette.palette[0], 3 * 256);
		screenSetPalette(&_palette);
	}

	void Codec::_readFrameObjectAndApply(const TagPair& fobj) {
		uint16 type = _diskReader.readUInt16LE();

		if (type != 47) {
			_diskReader.skip(fobj.length - 2);
			return;
		}

		uint16 x = _diskReader.readUInt16LE();
		uint16 y = _diskReader.readUInt16LE();
		uint16 w = _diskReader.readUInt16LE();
		uint16 h = _diskReader.readUInt16LE();

		_diskReader.skip(4);


		_diskReader.skip(2);	// 0,1
		uint8 op = _diskReader.readByte(); // 2
		_diskReader.skip(1); // 3
		uint8 extraHeader = _diskReader.readByte(); // 4

		uint32 offset = 21;

		if (extraHeader & 1) {
			offset += 32896;
		}

		_diskReader.skip(offset);

		debug(GS_THIS, "++ FOBJ %ld (%ld) %ld %ld %ld %ld ", type, (uint32) op, x, y, w, h);

		// "Keyframes" - just copy over as-is.
		if (op == 0 && w == GS_SCREEN_WIDTH && h == GS_SCREEN_HEIGHT) {
			_diskReader.readBytes(&_tempFrame[0], GS_BITMAP_SIZE);
			screenBlitCopy(&_tempFrame[0]);
		}

		_diskReader.seekEndOf(fobj);
	}

	int32 Codec::presentFrame() {

		TagPair frme = _diskReader.readSanTagPair();

#if defined(GS_CHECKED) && GS_CHECKED == 1
		if (frme.isTag(GS_MAKE_ID('F','R','M','E')) == false) {
			error(GS_THIS, "This is not an ANIM SAN file! Missing FRME tag got %s!", frme.tagStr());
			abort_quit_stop();
		}
#endif

		while(_diskReader.pos() < frme.end()) {
			TagPair tag = _diskReader.readSanTagPair();

			debug(GS_THIS, "Frame %ld %s %ld", _frameNum, tag.tagStr(), tag.length);

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
				_diskReader.skip(tag.length);
				continue;
			}

			if (tag.isTag(GS_MAKE_ID('T','E','X','T'))) {
				_diskReader.skip(tag.length);
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