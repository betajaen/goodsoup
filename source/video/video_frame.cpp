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

	VideoFrame::VideoFrame() {
		_image = NULL;
		_palette = NULL;
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

	void VideoFrame::apply(byte* dstFrameBuffer, AudioStream_S16MSB* audioStream) {

		if (_palette != NULL) {
			screenSetPaletteFromArray(&_palette->palette[0]);
		}

		if (_image != NULL) {
			copyMemQuick((uint32*) dstFrameBuffer, (uint32*) &_image->frame[0], GS_BITMAP_SIZE);
		}

		if (_subtitles.hasAny()) {
			applySubtitles(dstFrameBuffer);
		}

	}

	void VideoFrame::save(WriteFile& file) {
		uint32 len = 0;

		len += 2 + 2 + 2;	// timing.num, timing.length_msec, timing.action;

		uint16 flags = VFF_Timing;
		uint16 numAudio = 0;
		uint16 numSubtitles = 0;

		if (_image != NULL) {
			len += GS_BITMAP_SIZE;
			flags |= VFF_Image;
		}

		if (_palette != NULL) {
			len += 3 * 256;
			flags |= VFF_Palette;
		}

		AudioSampleFrame_S16MSB* audioSample = _audio.peekFront();
		if (audioSample != NULL) {
			flags |= VFF_Audio;
			while (audioSample != NULL) {
				len += sizeof(AudioSampleFrame_S16MSB);
				audioSample = audioSample->next;
				numAudio++;
			}
		}

		SubtitleFrame* subtitle = _subtitles.peekFront();
		if (subtitle != NULL) {
			flags |= VFF_Subtitles;
			while (subtitle != NULL) {
				len += sizeof(SubtitleFrame);
				subtitle = subtitle->next;
				numSubtitles++;
			}
		}


		// FOURCC header and length
		file.writeTag("VFRM");
		file.writeUInt32BE(len);

		// VFRM Header
		file.writeUInt16BE(flags);
		file.writeUInt16BE(numAudio);
		file.writeUInt16BE(numSubtitles);

		// Timing
		file.writeUInt16BE(_timing.num);
		file.writeUInt16BE(_timing.length_msec);
		file.writeUInt16BE(_timing.action);

		// Audio
		audioSample = _audio.peekFront();
		if (audioSample != NULL) {
			while (audioSample != NULL) {
				file.writeBytes(audioSample->data, sizeof(2048 * sizeof(int16)));
				audioSample = audioSample->next;
			}
		}

		// Subtitles
		subtitle = _subtitles.peekFront();
		if (subtitle != NULL) {
			while (subtitle != NULL) {
				file.writeBytes(subtitle, sizeof(SubtitleFrame));
				subtitle = subtitle->next;
			}
		}

		// Image
		if (_image != NULL) {
			file.writeBytes(&_image->frame[0], GS_BITMAP_SIZE);
		}

		// Palette
		if (_palette != NULL) {
			file.writeBytes(&_palette->palette, 256 * 3);
		}

	}


}
