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

#define GS_FILE_NAME "video_frame"

#include "video_frame.h"
#include "memory.h"
#include "file.h"
#include "font.h"
#include "screen.h"
#include "audio.h"

namespace gs
{
	class VideoFramePool
	{
	public:


		VideoFramePool() {
		}

		~VideoFramePool() {
			videoFrames.clear();
			subtitles.clear();
			audioSamples.clear();
			palettes.clear();
			images.clear();
		}

		LinkedListPool<VideoFrame> videoFrames;
		LinkedListPool<SubtitleFrame> subtitles;
		LinkedListPool<AudioSampleFrame_S16MSB> audioSamples;
		LinkedListPool<PaletteFrame> palettes;
		LinkedListPool<ImageFrame> images;
	};

	static VideoFramePool* sVideoFramePool = NULL;

	void initializeVideoFrameData() {
		if (sVideoFramePool == NULL) {
			sVideoFramePool = newObject<VideoFramePool>(GS_COMMENT_FILE_LINE_NOTE("VideoFramePool"));
		}
	}

	void disposeVideoFrameData() {
		deleteObject(sVideoFramePool);
	}

	VideoFrame* acquireVideoFrame() {
		return sVideoFramePool->videoFrames.acquire(GS_COMMENT_FILE_LINE_NOTE("Video Frame"));
	}

	void disposeVideoFrame(VideoFrame* frame) {
		CHECK_IF(frame == NULL, "Null VideoFrame Given.");
		CHECK_IF(sVideoFramePool == NULL, "sVideoFramePool is NULL.");

		frame->recycle();
		sVideoFramePool->videoFrames.release_unchecked(frame);
	}

	void disposeExtractedSubtitles(SubtitleFrame* head, SubtitleFrame* tail) {
		Queue<SubtitleFrame> queue;
		queue.replace(head, tail);

		while(true) {
			SubtitleFrame* subtitle = queue.pullFront();
			if (subtitle == NULL)
				break;
			sVideoFramePool->subtitles.release_unchecked(subtitle);
		}

	}

	VideoFrame::VideoFrame() {
		_image = NULL;
		_palette = NULL;
		_audioPacket = NULL;
	}

	VideoFrame::~VideoFrame() {
		recycle();
	}

	void VideoFrame::recycle() {
		_timing.num = 0;
		_timing.length_msec = 0;

		while(true) {
			AudioSampleFrame_S16MSB* sample = _audio.pullFront();
			if (sample == NULL)
				break;
			sVideoFramePool->audioSamples.release_unchecked(sample);
		}

		while(true) {
			SubtitleFrame* subtitle = _subtitles.pullFront();
			if (subtitle == NULL)
				break;
			sVideoFramePool->subtitles.release_unchecked(subtitle);
		}

		if (_image != NULL) {
			sVideoFramePool->images.release_unchecked(_image);
			_image = NULL;
		}

		if (_palette != NULL) {
			sVideoFramePool->palettes.release(_palette);
			_palette = NULL;
		}

		if (_audioPacket) {
			// Was unused
			releaseAudioPacket(_audioPacket);
			_audioPacket = NULL;
		}

	}

	SubtitleFrame* VideoFrame::addSubtitle() {
		SubtitleFrame* subtitle = sVideoFramePool->subtitles.acquire(GS_COMMENT_FILE_LINE_NOTE("SubtitleFrame"));
		_subtitles.pushBack(subtitle);
		return subtitle;
	}

	void VideoFrame::removeSubtitle(SubtitleFrame* frame) {
		_subtitles.pull(frame);
		sVideoFramePool->subtitles.release_unchecked(frame);
	}

	void VideoFrame::removeAllSubtitles() {
		SubtitleFrame* subtitleFrame = _subtitles.pullFront();
		while(subtitleFrame != NULL) {
			sVideoFramePool->subtitles.release_unchecked(subtitleFrame);
			subtitleFrame = _subtitles.pullFront();
		}
	}

	void VideoFrame::extractSubtitles(SubtitleFrame*& head, SubtitleFrame*& tail) {
		head = _subtitles.peekFront();
		tail = _subtitles.peekBack();
		_subtitles.clear();
	}

	void VideoFrame::injectSubtitles(gs::SubtitleFrame *head, gs::SubtitleFrame *tail) {

		if (hasSubtitles()) {
			disposeExtractedSubtitles(_subtitles.peekFront(), _subtitles.peekBack());
		}

		_subtitles.replace(head, tail);
	}

	AudioSampleFrame_S16MSB* VideoFrame::addAudio() {
		AudioSampleFrame_S16MSB* audioSample = sVideoFramePool->audioSamples.acquire(GS_COMMENT_FILE_LINE_NOTE("AudioSampleFrame_S16MSB"));
		_audio.pushBack(audioSample);
		return audioSample;
	}

	ImageFrame* VideoFrame::addImage() {
		if (_image == NULL) {
			_image = sVideoFramePool->images.acquire(GS_COMMENT_FILE_LINE_NOTE("ImageFrame"));
		}

		return _image;
	}

	void VideoFrame::removeImage() {
		if (_image != NULL) {
			sVideoFramePool->images.release_unchecked(_image);
			_image = NULL;
		}
	}

	PaletteFrame* VideoFrame::addPalette() {
		if (_palette == NULL) {
			_palette = sVideoFramePool->palettes.acquire(GS_COMMENT_FILE_LINE_NOTE("PaletteFrame"));
		}

		return _palette;
	}


	void VideoFrame::applySubtitles(byte* dstFrameBuffer) {

		static uint32 lastHash = 0;

		SubtitleFrame* subtitle = _subtitles.peekFront();

		if (_subtitles.hasOne()) {
			if (lastHash == subtitle->hash) {
				drawSubtitlesToAgain(dstFrameBuffer);
			}
			else {
				drawSubtitlesTo(dstFrameBuffer,
								  subtitle->x,
								  subtitle->y,
								  subtitle->getString(),
								  subtitle->flags & SF_Center,
								  subtitle->flags & SF_Wrap,
								  subtitle->font,
								  subtitle->colour);
			}

			lastHash = subtitle->hash;
			return;
		}

		while(subtitle != NULL) {
			printDialogue(subtitle->getString(), subtitle->hash, subtitle->kind);

			drawSubtitlesTo(dstFrameBuffer,
							  subtitle->x,
							  subtitle->y,
							  subtitle->getString(),
							  subtitle->flags & SF_Center,
							  subtitle->flags & SF_Wrap,
							  subtitle->font,
							  subtitle->colour);

			subtitle = subtitle->next;
		}
	}

	void VideoFrame::apply(byte* dstFrameBuffer) {

		if (_palette != NULL) {
			screenSetPaletteFromArray(&_palette->palette[0]);
		}

		if (_timing.clearFlags == 1) {
			uint32 length = GS_BITMAP_SIZE / sizeof(uint32);
			uint32* dst = (uint32*) dstFrameBuffer;
			while(length--) {
				*dst++ = 0x0;
			}
		}

		if (_image != NULL) {

			switch(_image->format) {

				case IFF_CopyLast:
					break;
				case IFF_FullFrameRaw: {
					copyMemQuick((uint32 *) dstFrameBuffer, (uint32*) _image->getData(), GS_BITMAP_SIZE);
				}
				break;
				case IFF_HalfFrameRaw: {
					uint32* src = (uint32*) _image->getData();
					uint32* dst = (uint32*) dstFrameBuffer;
					dst += (GS_BITMAP_HALF_LEFT + GS_BITMAP_HALF_TOP * GS_BITMAP_PITCH) / sizeof(uint32);
					uint32 y = GS_BITMAP_HALF_ROWS;
					const uint32 srcStride = GS_BITMAP_HALF_PITCH / sizeof(uint32);
					const uint32 dstStride = GS_BITMAP_PITCH / sizeof(uint32);

					while(y--) {
						copyMemQuick(dst, src, GS_BITMAP_HALF_PITCH);
						src += srcStride;
						dst += dstStride;
					}
				}
				break;
				case IFF_FullFrameDelta: {
					uint32* dst = (uint32*) dstFrameBuffer;
					uint32* src = (uint32*) _image->getData();

					uint16 y = GS_BITMAP_ROWS;
					while(y--) {
						uint32 mask = *src++;

						for(uint8 i=0;i < 32;i++) {
							uint32 isDifferent = mask & 1;
							mask >>= 1;

							if (isDifferent == 1) {
#if 1
								*dst++ = *src++;
								*dst++ = *src++;
								*dst++ = *src++;
								*dst++ = *src++;
								*dst++ = *src++;
#else
								*dst++ ^= *src++;
								*dst++ ^= *src++;
								*dst++ ^= *src++;
								*dst++ ^= *src++;
								*dst++ ^= *src++;
#endif
							}
							else {
								dst += 5;
							}
						}
					}

				}
				break;
				case IFF_HalfFrameDelta: {

				}
				break;

			}

		}

		if (_subtitles.hasAny()) {
			applySubtitles(dstFrameBuffer);
		}

	}

	void disposeAudioSampleFrame_S16MSB(AudioSampleFrame_S16MSB* audio) {
		sVideoFramePool->audioSamples.release_unchecked(audio);
	}

	void VideoFrame::queueAudio(AudioStream_S16MSB *audioStream) {

		if (_audioPacket != NULL) {
			submitAudioPacket(_audioPacket);
			_audioPacket = NULL;
		}

		AudioSampleFrame_S16MSB* sampleFrame = _audio.pullFront();

		while(sampleFrame != NULL) {
        /*
			AudioSample_S16MSB *sample = audioStream->allocateSample();

			sample->userMessage = getNum();
			sample->userData = sampleFrame;
			sample->data = &sampleFrame->data[0];
			sample->pos = 0;
			sample->remaining = 2048;
			audioStream->pushSample(sample);
        */
			sampleFrame = _audio.pullFront();
		}

	}


}
