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

#ifndef GS_VIDEO_FRAME_HH
#define GS_VIDEO_FRAME_HH

#include "../forward.h"
#include "../containers.h"
#include "../profile.h"

namespace gs
{

	class AudioStream_S16MSB;
	class WriteFile;

	enum SubtitleFlags {
		SF_Center = 1,
		SF_Wrap = 2
	};

	struct SubtitleFrame {
		SubtitleFrame *next;
		uint32 hash;
		uint8 length;
		uint8 flags;
		uint8 font;
		uint8 colour;
		uint8 kind;		// See SubtitleKind
		int16 x, y;
		char text[480];

		inline const char* getString() const {
			return &text[0];
		}

		inline char* getString() {
			return &text[0];
		}

	};

	struct AudioSampleFrame_S16MSB {
		AudioSampleFrame_S16MSB *next;
		int16 data[2048];

		inline int16* getData() {
			return &data[0];
		}

		inline const int16* getData() const {
			return &data[0];
		}

		inline byte* getBytes() {
			return (byte*) &data[0];
		}

		inline const byte* getBytes() const {
			return (byte*) &data[0];
		}
	};

	struct ImageFrame {
		ImageFrame* next;
		uint8 frame[GS_BITMAP_SIZE];
	};

	struct PaletteFrame {
		PaletteFrame* next;
		uint8 palette[256 * 3];
	};

	enum VideoFrameNextAction {
		VFNA_Next = 0,
		VFNA_Stop = 1
	};

	struct VideoFrameTiming {
		uint16 num;
		uint16 length_msec;
		uint16 action;
	};

	enum VideoFrameFeature {
		VFF_None = 0,
		VFF_Timing = 1,
		VFF_Audio = 2,
		VFF_Subtitles = 4,
		VFF_Image = 8,
		VFF_Palette = 16
	};

	class VideoFrame {

	public:

		VideoFrame();
		~VideoFrame();

		void recycle();

		VideoFrame *next;

		SubtitleFrame* addSubtitle();
		AudioSampleFrame_S16MSB* addAudio();
		ImageFrame* addImage();
		PaletteFrame* addPalette();
		void removeSubtitle(SubtitleFrame* frame);

		void applySubtitles(byte* dstFrameBuffer);
		void apply(byte* dstFrameBuffer, AudioStream_S16MSB* audioStream);
		void save(WriteFile& file);

		VideoFrameTiming _timing;
		Queue<AudioSampleFrame_S16MSB> _audio;
		Queue<SubtitleFrame> _subtitles;
		ImageFrame* _image;
		PaletteFrame* _palette;
	};

	VideoFrame* acquireVideoFrame();
	void disposeVideoFrame(VideoFrame* frame);
	void disposeVideoFrameData();

}

#endif