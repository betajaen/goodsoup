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
#include "../memory.h"

namespace gs
{
#define FOBJ_CODEC2_ENABLED 1
#define FOBJ_HDR_OP 0
#define FOBJ_HDR_SEQ_OP 1
#define FOBJ_HDR_EXTENDED 2
#define FOBJ_HDR_BOMP_LENGTH 12

	static Buffer<char, uint16> _tempText;

#define SWAP_BUFFER(A, B) do { uint8 t = A; A = B; B = t; } while(0);

#if FOBJ_CODEC2_ENABLED == 0

	static void FillLine2x1(byte* dst, byte src) {
		*dst++ = src;
		*dst++ = src;
	}

	static void FillLine4x1(byte* dst, byte src) {
		*dst++ = src;
		*dst++ = src;
		*dst++ = src;
		*dst++ = src;
	}

	static void CopyLine2x1(byte* dst, byte* src) {
		*dst++ = *src++;
		*dst++ = *src++;
	}

	static void CopyLine4x1(byte* dst, byte* src) {
		*dst++ = *src++;
		*dst++ = *src++;
		*dst++ = *src++;
		*dst++ = *src++;
	}

	static void Codec2_Level3(byte* dst, byte*& src, byte* last) {
		uint8 code = *src++;

	}

	static void Codec2_Level2(byte* dst, byte*& src, byte* last) {
		uint8 code = *src++;

	}

	static void Codec2_Level1(byte* dst, byte*& src, byte* last) {
		uint8 code = *src++;

		if (code < 0xF8) {
			uint8 t = 0; /* TODO */
			uint8 s = 8;
			while(s--) {
				CopyLine4x1(dst, dst + t);
				CopyLine4x1(dst + 4, dst + t + 4);
				dst += GS_BITMAP_PITCH;
			}
		}
		else if (code == 0xFF) {
			Codec2_Level2(dst, src, last);
			dst += 4;
			Codec2_Level2(dst, src, last);
			dst += (GS_BITMAP_PITCH * 4) - 4;
			Codec2_Level2(dst, src, last);
			dst += 4;
			Codec2_Level2(dst, src, last);
		}
		else if (code == 0xFE) {
			uint8 t = *src++;
			uint8 s = 8;
			while(s--) {
				FillLine4x1(dst, t);
				FillLine4x1(dst + 4, t);
				dst += GS_BITMAP_PITCH;
			}
		}
		else if (code == 0xFD) {
			src++;
			src++; // TODO
		}
	}

	static void Codec2_Level0(byte* dst, byte* src, byte* last) {
		uint8 bw = 80;
		uint8 bh = 60;
		const uint32 nextLine = 640 * 7;
		do
		{
			uint8 tmp_bw = bw;
			do
			{
				Codec2_Level1(dst, src, last);
				dst += 8;
			} while ((--tmp_bw) != 0);
			dst += nextLine;
		} while ((--bh) != 0);

	}

#endif

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

		_currentBuffer = 0;
		_deltaBuffer[0] = 1;
		_deltaBuffer[1] = 2;
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

	void SanCodec::_copyBuffers(uint8 dst, uint8 src) {
		uint32* dstBuffer = (uint32*) _getBuffer(dst);
		uint32* srcBuffer = (uint32*) _getBuffer(src);

		uint32 count = GS_BITMAP_SIZE / sizeof(uint32);
		while(count--) {
			*dstBuffer++ = *srcBuffer++;
		}
	}

	uint8* SanCodec::_getBuffer(uint8 idx) {
		return &_buffer[idx][0];
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
				uint8* buffer = _getBuffer(_currentBuffer);
				_diskReader.readBytes(buffer, GS_BITMAP_SIZE);
				screenBlitCopy(buffer);
			}
			break;
#if FOBJ_CODEC2_ENABLED == 1
			case 2: {
			}
			break;
#endif
			case 3: {
				// Copies* delta 1 to current.
				_copyBuffers(_currentBuffer, _deltaBuffer[1]);
			}
			break;
			case 4: {
				// Copies delta 0 to current.
				_copyBuffers(_currentBuffer, _deltaBuffer[0]);
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

				uint8* buffer = _getBuffer(_currentBuffer);
				_diskReader.readBytes(&_tempBuffer[0], length);
				decodeBomp(buffer, &_tempBuffer[0], length);
				screenBlitCopy(buffer);
			}
			break;
		}

		if (seqNum == _prevSequenceNum + 1) {
			if (header[FOBJ_HDR_SEQ_OP] == 1) {
				SWAP_BUFFER(_currentBuffer, _deltaBuffer[1]);
			}
			else {
				SWAP_BUFFER(_deltaBuffer[0], _deltaBuffer[1]);
				SWAP_BUFFER(_deltaBuffer[1], _currentBuffer);
			}
		}

		_prevSequenceNum = seqNum;
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
