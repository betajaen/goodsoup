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
#include "../memory.h"

namespace gs
{
	LinkedListPool<VideoFrame> sVideoFrames;
	LinkedListPool<SubtitleFrame> sSubtitles;
	LinkedListPool<AudioSampleFrame_S16MSB> sAudioSamples;
	LinkedListPool<PaletteFrame> sPalettes;
	LinkedListPool<ImageFrame> sImages;

	Queue<VideoFrame> sQueue;

	VideoFrame* acquireVideoFrame() {
		return sVideoFrames.acquire();
	}

	void disposeVideoFrame(VideoFrame* frame) {
		CHECK_IF(frame == NULL, "Null VideoFrame Given.");

		frame->recycle();
		sVideoFrames.release_unchecked(frame);
	}

	VideoFrame::VideoFrame() {
		_image = NULL;
		_palette = NULL;
	}

	VideoFrame::~VideoFrame() {
		recycle();
	}

	void VideoFrame::recycle() {
		_frameNum = 0;
		_frameLength = 0;

		while(true) {
			AudioSampleFrame_S16MSB* audio = _audio.pullFront();
			if (audio == NULL)
				break;
			sAudioSamples.release_unchecked(audio);
		}

		while(true) {
			SubtitleFrame* subtitle = _subtitles.pullFront();
			if (subtitle == NULL)
				break;
			sSubtitles.release_unchecked(subtitle);
		}

		if (_image != NULL) {
			sImages.release_unchecked(_image);
			_image = NULL;
		}

		if (_palette != NULL) {
			sPalettes.release(_palette);
			_palette = NULL;
		}

	}

	void VideoFrame::addToQueue() {
		sQueue.pushFront(this);
	}

	SubtitleFrame* VideoFrame::addSubtitle() {
		SubtitleFrame* subtitle = sSubtitles.acquire(GS_COMMENT_FILE_LINE);
		_subtitles.pushBack(subtitle);
		return subtitle;
	}

	AudioSampleFrame_S16MSB* VideoFrame::addAudio() {
		AudioSampleFrame_S16MSB* audioSample = sAudioSamples.acquire(GS_COMMENT_FILE_LINE);
		_audio.pushBack(audioSample);
		return audioSample;
	}

	ImageFrame* VideoFrame::addImage() {
		if (_image == NULL) {
			_image = sImages.acquire(GS_COMMENT_FILE_LINE);
		}

		return _image;
	}

	PaletteFrame* VideoFrame::addPalette() {
		if (_palette == NULL) {
			_palette = sPalettes.acquire(GS_COMMENT_FILE_LINE);
		}

		return _palette;
	}

}
