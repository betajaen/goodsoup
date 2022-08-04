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

#ifndef GS_CODEC_H
#define GS_CODEC_H

#include "../types.h"
#include "../file.h"
#include "../disk.h"
#include "../room.h"	// For RoomPaletteData

#include "iact_timing.h"
#include "iact_audio.h"

#define FOBJ_CODEC2_ENABLED 1
#define MAX_TEXT_PER_FRAME 16

namespace gs
{

	class AudioMixer;

	class SanCodec
	{
		struct TextDrawCall {
			const char*  _text;
			uint32 _hash;
			int16  _x, _y;
			uint8  _center, _wrap, _font, _col;
		};

		DiskReader _diskReader;

		uint16 _frameCount;
		uint16 _frameNum;

		RoomPaletteData _palette;

		int16 _deltaPalette[768];
		uint8 _currentBuffer;
		uint8 _deltaBuffer[2];
		int16 _prevSequenceNum;
		uint8 _tempBuffer[GS_BITMAP_SIZE];
		uint8 _buffer[3][GS_BITMAP_SIZE];
		IACTTiming _timing;
		IACTAudio _audio;
		AudioMixer* _audioMixer;
		uint8 _params[4];
		uint8 _offset1, _offset2;
		TextDrawCall _texts[MAX_TEXT_PER_FRAME];
		uint8 _numTexts;
		uint32 _lastTextHash;
		uint8 _rotationOp;
		bool _hasText, _hasFrame;

		void _copyBuffers(uint8 dst, uint8 src);
		uint8* _getBuffer(uint8 idx);
		void _clearBuffer(uint8 dst, uint8 colour);

		void _readAndApplyPalette();
		void _readAndApplyDeltaPalette(const TagPair& xpal);
		void _readFrameObjectAndApply(const TagPair& fobj);
		void _readAndApplyText(const TagPair& text);

	public:

		SanCodec(DiskReader reader);
		~SanCodec();

		int32 presentFrame();

	};

}

#endif