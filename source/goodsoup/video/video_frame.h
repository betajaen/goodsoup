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
	struct AudioPacket;

	enum SubtitleFlags {
		SF_Center = 1,
		SF_Wrap = 2
	};

	struct SubtitleFrame {
		SubtitleFrame *next;
		uint32 hash;
		uint16 length;
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

	enum ImageFrameFormat {
		IFF_CopyLast = 0,
		IFF_FullFrameRaw = 1,
		IFF_HalfFrameRaw = 2,
		IFF_FullFrameDelta = 3,
		IFF_HalfFrameDelta = 4
	};

	struct ImageFrame {
		ImageFrame* next;
		uint16 left, top;
		uint16 width, height;
		uint16 format;
		uint32 size;
		byte data[GS_BITMAP_SIZE];

		inline byte* getData() {
			return &data[0];
		}

		inline const byte* getData() const {
			return &data[0];
		}
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
		uint8  action;
		uint8  clearFlags;
		uint8  keepSubtitles;
		uint8  reserved;
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

		uint16 getNum() const {
			return _timing.num;
		}

		AudioSampleFrame_S16MSB* addAudio();

		inline bool hasAudio() const {
			return _audio.hasAny();
		}

		ImageFrame* addImage();

		inline bool hasImage() const {
			return _image != NULL;
		}

		void removeImage();

		PaletteFrame* addPalette();

		inline bool hasPalette() const {
			return _palette != NULL;
		}

		SubtitleFrame* addSubtitle();
		void removeSubtitle(SubtitleFrame* frame);
		void removeAllSubtitles();
		void extractSubtitles(SubtitleFrame*& head, SubtitleFrame*& tail);
		void injectSubtitles(SubtitleFrame* head, SubtitleFrame* tail);
		inline bool hasSubtitles() const {
			return _subtitles.hasAny();
		}

		inline bool keepSubtitles() const {
			return _timing.keepSubtitles == 1;
		}

		void applySubtitles(byte* dstFrameBuffer);
		void apply(byte* dstFrameBuffer);
		void queueAudio(AudioStream_S16MSB* audioStream);


		VideoFrameTiming _timing;
		Queue<AudioSampleFrame_S16MSB> _audio;
		Queue<SubtitleFrame> _subtitles;
		ImageFrame* _image;
		PaletteFrame* _palette;
		AudioPacket* _audioPacket;
	};

	VideoFrame* acquireVideoFrame();
	void disposeVideoFrame(VideoFrame* frame);
	void initializeVideoFrameData();
	void disposeVideoFrameData();
	void disposeExtractedSubtitles(SubtitleFrame* head, SubtitleFrame* tail);
	void disposeAudioSampleFrame_S16MSB(AudioSampleFrame_S16MSB* audio);


}

#endif