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
#include "../file.h"

namespace gs
{
	LinkedListPool<VideoFrame> sVideoFrames;
	LinkedListPool<SubtitleFrame> sSubtitles;
	LinkedListPool<AudioSampleFrame_S16MSB> sAudioSamples;
	LinkedListPool<PaletteFrame> sPalettes;
	LinkedListPool<ImageFrame> sImages;

	void disposeVideoFrameData() {
		sVideoFrames.clear();
		sSubtitles.clear();
		sAudioSamples.clear();
		sPalettes.clear();
		sImages.clear();
	}

	VideoFrame* acquireVideoFrame() {
		return sVideoFrames.acquire(GS_COMMENT_FILE_LINE);
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
		_timing.num = 0;
		_timing.length_msec = 0;

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

	SubtitleFrame* VideoFrame::addSubtitle() {
		SubtitleFrame* subtitle = sSubtitles.acquire(GS_COMMENT_FILE_LINE);
		_subtitles.pushBack(subtitle);
		return subtitle;
	}

	void VideoFrame::removeSubtitle(SubtitleFrame* frame) {
		_subtitles.pull(frame);
		sSubtitles.release_unchecked(frame);
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


	void VideoFrame::apply(AudioStream_S16MSB* audioStream) {

	}

	void VideoFrame::save(WriteFile& file) {
		uint32 len = 0;

		len += 2 + 2;	// timing.num, timing.length_msec;

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
			file.writeBytes(&_image->_video[0], GS_BITMAP_SIZE);
		}

		// Palette
		if (_palette != NULL) {
			file.writeBytes(&_palette->_palette, 256 * 3);
		}

	}


}
