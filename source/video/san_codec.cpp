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
#include "../endian.h"
#include "../audio.h"
#include "../globals.h"

namespace gs
{


#if GS_SAN_CODEC47 >= 1
	extern int16 SAN47_MOTION_VECTORS[256];
	extern byte* SAN_TABLE_BIG;
	extern byte* SAN_TABLE_SMALL;

	void initSan47Tables();
	void releaseSan47Tables();
#endif

#if GS_SAN_CODEC47 == 1
	void san_codec47_decode_basic(byte* dst, byte* src, byte* offset1, byte* offset2, byte* params);
#endif

#if GS_SAN_CODEC47 == 2
	void san_codec47_decode_opt(byte* dst, byte* src, byte* offset1, byte* offset2, byte* params);
#endif

#define FOBJ_HDR_OP 0
#define FOBJ_HDR_ROTATION_OP 1
#define FOBJ_HDR_EXTENDED 2
#define FOBJ_HDR_BOMP_LENGTH 12
#define FOBJ_HDR_PARAMS 6

	char  _textData[1024];
	uint16 _textLength = 0;

#define SWAP_BUFFER(A, B) do { uint8 t = A; A = B; B = t; } while(0)

	SanCodec::SanCodec(DiskReader reader)
		: _diskReader(reader), _frameNum(0)
	{

#if GS_MUTE_AUDIO == 0
		_audioStream = createAudioStream();
		_audioStream->_rateFactor = 10;
        pushAudioStream(_audioStream);
#endif

		TagPair animTag = _diskReader.readSanTagPair();

#if GS_SAN_CODEC47 >= 1
		initSan47Tables();
#else
#endif

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

		uint16 version = _diskReader.readUInt16LE();

		if (version != 2) {
			error(GS_THIS, "Unsupported SMUSH File version %ls expected 2", version);
			abort_quit_stop();
			return;
		}

		_frameCount = _diskReader.readUInt16LE();
		_diskReader.skip(2);
		_readAndApplyPalette();

		uint32 frameRate = _diskReader.readUInt32LE();
		_diskReader.skip(4);
		uint32 audioRate = _diskReader.readUInt32LE();
        _waitTimeUSec = 1000000 / frameRate;
        _timer.initialize(_waitTimeUSec);

		_diskReader.seekEndOf(animHeader);

		_currentBuffer = 2;
		_deltaBuffer[0] = 0;
		_deltaBuffer[1] = 1;
		_prevSequenceNum = -1;
		_numTexts = 0;
		_textLength = 0;
		_lastTextHash = 0;
	}

	SanCodec::~SanCodec() {

#if GS_MUTE_AUDIO == 0
        AudioStream_S16MSB* oldMixer = popAudioStream();
        CHECK_IF(oldMixer != _audioStream, "Additional AudioStream was pushed during video playback!");
		releaseAudioStream(_audioStream);
		_audioStream = NULL;
#endif
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
			for(uint16 i=0;i < 768;i++) {
				_deltaPalette[i] = _diskReader.readUInt16LE();
			}
			_diskReader.readBytes(&_palette.palette[0], sizeof(_palette.palette));
			screenSetPalette(&_palette);
		}

	}

	void SanCodec::_readAndApplyText(const TagPair& text) {

		if (_numTexts == MAX_TEXT_PER_FRAME) {
			uint16 length = text.length;
			_diskReader.skip(length);
			return;
		}

		TextDrawCall& call = _texts[_numTexts];
		_numTexts++;

		call._x = _diskReader.readInt16LE();
		call._y  = _diskReader.readUInt16LE();
		uint16 flags = _diskReader.readUInt16LE();
		uint16 x0 = _diskReader.readUInt16LE();
		uint16 y0 = _diskReader.readUInt16LE();
		uint16 right = _diskReader.readUInt16LE();

		_diskReader.skip(4);
		uint16 length = text.length - 16;


#if defined(GS_CHECKED) && GS_CHECKED == 1
		if (_textLength + length >= sizeof(_textData)) {
			warn(GS_THIS, "Out of dialogue text space!");
			_numTexts--;
			_diskReader.skip(length);
			return;
		}
#endif

		_diskReader.readBytes(&_textData[_textLength], length);
		call._text = parseFormattedDialogue((const char*) &_textData[_textLength], call._hash, call._font, call._col);

		call._center = flags == 13 || flags == 9 || flags == 1;
		call._wrap = flags == 13;

		_textLength += length;

		_hasText = true;
	}

	void SanCodec::_copyBuffers(uint8 dst, uint8 src) {
		uint32* dstBuffer = (uint32*) _getBuffer(dst);
		uint32* srcBuffer = (uint32*) _getBuffer(src);

		uint32 count = GS_BITMAP_SIZE / sizeof(uint32);
		while(count--) {
			*dstBuffer++ = *srcBuffer++;
		}
	}

	void SanCodec::_clearBuffer(uint8 dst, uint8 colour) {
		uint32* dstBuffer = (uint32*) _getBuffer(dst);
		uint32 colour32 = colour | colour << 8 | colour << 16 | colour << 24;

		uint32 count = GS_BITMAP_SIZE / sizeof(uint32);
		while(count--) {
			*dstBuffer++ = colour32;
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

		uint16 seqNum = _diskReader.readUInt16LE();		// -2
		_diskReader.readBytes(&header, sizeof(header));	// 0
		if (header[FOBJ_HDR_EXTENDED] & 1) {
			_diskReader.skip(0x8080);
		}

		_offset1 = _deltaBuffer[1];
		_offset2 = _deltaBuffer[0];

		if (seqNum == 0) {
			_prevSequenceNum = -1;

			_clearBuffer(_deltaBuffer[0], header[10]);
			_clearBuffer(_deltaBuffer[1], header[11]);
		}

		switch(header[FOBJ_HDR_OP]) {

			case 0: {	// "Key Frame"
				uint8* buffer = _getBuffer(_currentBuffer);
				_diskReader.readBytes(buffer, GS_BITMAP_SIZE);
				_hasFrame = true;
			}
			break;
#if GS_SAN_CODEC47 >= 1
			case 2: {
				if (seqNum == _prevSequenceNum + 1) {

					_params[0] = header[FOBJ_HDR_PARAMS + 0];	// F8
					_params[1] = header[FOBJ_HDR_PARAMS + 1];	// F9
					_params[2] = header[FOBJ_HDR_PARAMS + 2];   // FA
					_params[3] = header[FOBJ_HDR_PARAMS + 3];   // FB

					uint32 dataLength = fobj.end() - _diskReader.pos();
					byte* src = &_tempBuffer[0];
					_diskReader.readBytes(src, dataLength);
					uint8 *buffer = _getBuffer(_currentBuffer);

#if GS_SAN_CODEC47 == 1
					san_codec47_decode_basic(buffer, src, _getBuffer(_deltaBuffer[1]), _getBuffer(_deltaBuffer[0]), _params);
#endif
#if GS_SAN_CODEC47 == 2
					san_codec47_decode_opt(buffer, src, _getBuffer(_deltaBuffer[1]), _getBuffer(_deltaBuffer[0]), _params);
#endif

					_hasFrame = true;
				}
			}
			break;
			case 3: {
				// Copies* delta 1 to current.
				_copyBuffers(_currentBuffer, _deltaBuffer[1]);
				_hasFrame = false;
			}
			break;
			case 4: {
				// Copies delta 0 to current.
				_copyBuffers(_currentBuffer, _deltaBuffer[0]);
				_hasFrame = false;
			}
			break;
#endif
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
				_hasFrame = true;
			}
			break;
		}

		if (seqNum == _prevSequenceNum + 1) {
			_rotationOp = header[FOBJ_HDR_ROTATION_OP];
		}

		_prevSequenceNum = seqNum;
		_diskReader.seekEndOf(fobj);
	}


	int32 SanCodec::presentFrame() {

#if GS_MUTE_AUDIO == 1

        uint32 shouldPresent = _timer.check();

        if (shouldPresent == 0) {
            return 1;
        }

        /* TODO: Skipping Frames when shouldPresent is 2 */
#else
		/* TODO: This is a dumb way. Used with testing the new audio stream system */
		if (_audioStream->getQueueSize() >= 4) {
			return 1;
		}

#endif

        debug(GS_THIS, "New Video Frame");


		TagPair frme = _diskReader.readSanTagPair();

#if defined(GS_CHECKED) && GS_CHECKED == 1
		if (frme.isTag(GS_MAKE_ID('F','R','M','E')) == false) {
			error(GS_THIS, "This is not an ANIM SAN file! Missing FRME tag got %s!", frme.tagStr());
			abort_quit_stop();
		}
#endif

		_hasFrame = false;

		while(_diskReader.pos() < frme.end()) {
			TagPair tag = _diskReader.readSanTagPair();

			if (tag.isTag(GS_MAKE_ID('N','P','A','L'))) {
				_readAndApplyPalette();
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

			if (tag.isTag(GS_MAKE_ID('I','A','C','T'))) {

				TagPair iact;
				iact.dataPos = tag.dataPos;

				_diskReader.skip(-4);
				iact.length = _diskReader.readUInt32BE();

				readIACTTiming(_diskReader, iact, _timing);

#if GS_MUTE_AUDIO == 0
				readIACTAudio(_diskReader, iact, _audio, _audioStream, _timing.currentFrame);
#endif

				_diskReader.seekEndOf(tag);
				continue;
			}
/*
			if (tag.isTag(GS_MAKE_ID('S','T','O','R'))) {
				_diskReader.skip(tag.length);
				continue;
			}

			if (tag.isTag(GS_MAKE_ID('F','T','C','H'))) {
				_diskReader.skip(tag.length);
				continue;
			}
*/

			_diskReader.skip(tag.length);
		}


		if (_hasFrame == true) {
			uint8 *buffer = _getBuffer(_currentBuffer);
			screenBlitCopy(buffer);
		}

		if (_hasText) {
			_hasText = false;

			if (_numTexts == 1 && _texts[0]._hash == _lastTextHash) {
				drawSubtitlesFromAgain(_getBuffer(_currentBuffer));
			}
			else {

				for(uint8 i=0;i < _numTexts;i++) {
					TextDrawCall& call = _texts[i];
					drawSubtitlesFrom(_getBuffer(_currentBuffer), call._x, call._y, call._text , call._center, call._wrap, call._font, call._col);
				}

				if (_numTexts == 1) {
					_lastTextHash = _texts[0]._hash;
				}
			}

			_numTexts = 0;
			_textLength = 0;
		}

		if (_rotationOp != 0) {
			if (_rotationOp == 2) {
				SWAP_BUFFER(_deltaBuffer[0], _deltaBuffer[1]);
			}
			SWAP_BUFFER(_currentBuffer, _deltaBuffer[1]);
			_rotationOp = 0;
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
