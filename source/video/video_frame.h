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

#include "../types.h"
#include "../list.h"
#include "../profile.h"
#include "../pool.h"

namespace gs
{

	class AudioStream_S16MSB;
	class WriteFile;

	struct SubtitleFrame {
		SubtitleFrame *next;
		uint8 length;
		uint8 flags;
		uint8 font;
		uint8 colour;
		int16 x, y;
		char text[256];
	};

	struct AudioSampleFrame_S16MSB {
		AudioSampleFrame_S16MSB *next;
		int16 data[2048];
	};

	struct ImageFrame {
		ImageFrame* next;
		uint8 _video[GS_BITMAP_SIZE];
	};

	struct PaletteFrame {
		PaletteFrame* next;
		uint8 _palette[256 * 3];
	};


	struct VideoFrameTiming {
		uint16 num;
		uint16 length_msec;
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

		void addToQueue();

		void apply(AudioStream_S16MSB* audioStream);
		void save(WriteFile& file);

		VideoFrameTiming _timing;
		Queue<AudioSampleFrame_S16MSB> _audio;
		Queue<SubtitleFrame> _subtitles;
		ImageFrame* _image;
		PaletteFrame* _palette;
	};

	VideoFrame* acquireVideoFrame();
	void disposeVideoFrame(VideoFrame* frame);

}

#endif