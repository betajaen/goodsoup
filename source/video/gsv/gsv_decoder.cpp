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

#define GS_FILE_NAME "gsv_decoder"

#include "forward.h"
#include "file.h"
#include "video/video_frame.h"
#include "video/video_api.h"
#include "endian.h"

namespace gs
{
	static TagReadFile* sFile;
	static uint32 sFrameNum;
	static VideoEncoderParams sParams;

	bool gsv_decoder_initialize(TagReadFile* file) {
		sFile = file;

		uint32 tagName = sFile->readUInt32BE();

		// This will fail on encoding/playing on different endian arch.
		sFile->readBytes(&sParams, sizeof(VideoEncoderParams));

		sFrameNum = 0;

		return true;
	}

	void gsv_decoder_teardown() {
	}

	uint8  gsv_decoder_processFrame(VideoFrame* frame) {

		if (sFile->pos() >= sFile->length()) {
			frame->_timing.action = VFNA_Stop;
			return 2;
		}

		byte str[5] = { 0 };
		sFile->readBytes(str, 4);

		if (str[0] == 'S' && str[1] == 'T' && str[2] == 'O' && str[3] == 'P') {
			frame->_timing.action = VFNA_Stop;
			return 2;
		}

		if (!(str[0] == 'F' && str[1] == 'R' && str[2] == 'M' && str[3] == 'E')) {
			frame->_timing.action = VFNA_Stop;
			return 0;
		}

		uint16 numAudio = sFile->readUInt16BE();
		uint16 numSubtitles = sFile->readInt16BE();
		byte imageFormat = sFile->readByte();
		byte hasPalette = sFile->readByte();
/*
		debug(GS_THIS, "Num Audio = %ld, Num Subtitles = %ld, Has Image = %ld, HasPalette = %ld",
			  numAudio,
			  numSubtitles,
			  imageFormat,
			  hasPalette
			  );
*/
		frame->_timing.num = sFile->readUInt16BE();
		frame->_timing.length_msec = sFile->readUInt16BE();
		frame->_timing.action = sFile->readByte();
		frame->_timing.clearFlags = sFile->readByte();
		frame->_timing.keepSubtitles = sFile->readByte();
		frame->_timing.reserved = sFile->readByte();

		while(numAudio--) {
			AudioSampleFrame_S16MSB* audio = frame->addAudio();

			uint32 length = sFile->readUInt32BE();

			sFile->readBytes(&audio->data[0], length);
		}

		while(numSubtitles--) {
			SubtitleFrame* subtitleFrame = frame->addSubtitle();

			subtitleFrame->hash = sFile->readUInt32BE();
			subtitleFrame->length = sFile->readUInt16BE();
			subtitleFrame->flags = sFile->readByte();
			subtitleFrame->font = sFile->readByte();
			subtitleFrame->colour = sFile->readByte();
			subtitleFrame->kind = sFile->readByte();
			subtitleFrame->x = sFile->readInt16LE();
			subtitleFrame->y = sFile->readInt16LE();
			sFile->readBytes(&subtitleFrame->text[0], subtitleFrame->length+1);
		}

		if (imageFormat != IFF_CopyLast) {
			ImageFrame* imageFrame = frame->addImage();

			uint32 size = sFile->readUInt32BE();
			imageFrame->size = size;

			imageFrame->format = imageFormat;

			switch(imageFormat) {
				default:
				case IFF_FullFrameRaw:
				case IFF_FullFrameDelta:
					imageFrame->left = GS_BITMAP_LEFT;
					imageFrame->top = GS_BITMAP_TOP;
					imageFrame->width = GS_BITMAP_PITCH;
					imageFrame->height = GS_BITMAP_ROWS;
				break;
				case IFF_HalfFrameRaw:
				case IFF_HalfFrameDelta:
					imageFrame->left = GS_BITMAP_HALF_LEFT;
					imageFrame->top = GS_BITMAP_HALF_TOP;
					imageFrame->width = GS_BITMAP_HALF_PITCH;
					imageFrame->height = GS_BITMAP_HALF_ROWS;
				break;
			}

			sFile->readBytes(imageFrame->getData(), size);
		}

		if (hasPalette) {
			PaletteFrame* paletteFrame = frame->addPalette();
			sFile->readBytes(&paletteFrame->palette[0], 768);
		}

		sFrameNum = frame->_timing.num;

		return 1;
	}
}

gs::VideoDecoder GSV_DECODER = {
		&gs::gsv_decoder_initialize,
		&gs::gsv_decoder_teardown,
		&gs::gsv_decoder_processFrame
};