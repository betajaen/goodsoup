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

		if (animTag.isTag(GS_MAKE_ID('A','N','I','M')) == false) {
			error(GS_THIS, "This is not an ANIM SAN file! Missing ANIM tag got %s", animTag.tagStr());
			abort_quit_stop();
			return;
		}

		TagPair animHeader = _diskReader.readSanTagPair();

		if (animHeader.isTag(GS_MAKE_ID('A','H','D','R')) == false) {
			error(GS_THIS, "This is not an ANIM SAN file! Missing ANHD tag got %s!", animHeader.tagStr());
			abort_quit_stop();
			return;
		}

		debug(GS_THIS, "File Pos = %ld, Length = %ld",  _diskReader.pos(), animHeader.length);

		_diskReader.skip(2);
		_frameCount = _diskReader.readUInt16LE();
		_diskReader.skip(2);

		_readAndApplyPalette();

		_diskReader.seekEndOf(animHeader);

		debug(GS_THIS, "Opened Codec %ld Frames", _frameCount);
	}

	Codec::~Codec() {
	}

	void Codec::_readAndApplyPalette() {
		_diskReader.readBytes(&_palette.palette[0], 3 * 256);
		screenSetPalette(&_palette);
	}

	int32 Codec::presentFrame() {

		TagPair frme = _diskReader.readSanTagPair();

		if (frme.isTag(GS_MAKE_ID('F','R','M','E')) == false) {
			error(GS_THIS, "This is not an ANIM SAN file! Missing FRME tag got %s!", frme.tagStr());
			abort_quit_stop();
		}

		debug(GS_THIS, "File Position = %ld, Length = %ld", frme.dataPos, frme.length);


		_diskReader.seekEndOf(frme);
		_frameNum++;

		if (_frameNum == _frameCount) {
			return -1;
		}
		else {
			return 1;
		}
	}
}
