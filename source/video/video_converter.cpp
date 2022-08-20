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

#define GS_FILE_NAME "video_converter"

#include "video_converter.h"
#include "video_api.h"
#include "video_frame.h"
#include "memory.h"
#include "profile.h"
#include "file.h"
#include "audio.h"
#include "string.h"
#include "font.h"

extern gs::VideoDecoder SMUSH_DECODER;
extern gs::VideoEncoder GSV_ENCODER;
extern gs::VideoDecoder GSV_DECODER;

namespace gs
{
	// Declared in video/smush/smush_tables.cpp
	void smush_tables_initialize();
	void smush_tables_teardown();

	VideoConverter::VideoConverter() {
		_srcFile = NULL;
		_dstFile = NULL;
		_frameBuffer = NULL;
		_lastFrame = NULL;
		_compressionFrame = NULL;
		initializeVideoFrameData();
		smush_tables_initialize();
	}

	VideoConverter::~VideoConverter() {
		disposeVideoFrameData();
		deleteObject(_dstFile);
		deleteObject(_srcFile);
		releaseMemory(_compressionFrame);
		releaseMemory(_lastFrame);
		releaseMemory(_frameBuffer);
		smush_tables_teardown();
	}

	bool VideoConverter::initialize(uint8 videoNum, bool halfFrameSize, bool subtitleCompression) {

		deleteObject(_dstFile);
		deleteObject(_srcFile);
		releaseMemory(_compressionFrame);
		releaseMemory(_lastFrame);
		releaseMemory(_frameBuffer);

		_videoNum = videoNum;
		_halfFrameSize = halfFrameSize;
		_subtitleCompression = subtitleCompression;
		_bakeSubtitles = true;
		_frameBuffer = (byte*) allocateMemory(1, GS_BITMAP_SIZE, MF_Clear, GS_COMMENT_FILE_LINE);
		_lastFrame = (byte*) allocateMemory(1, GS_BITMAP_SIZE, MF_Clear, GS_COMMENT_FILE_LINE);
		_compressionFrame = (byte*) allocateMemory(1, GS_BITMAP_SIZE + (GS_BITMAP_ROWS * sizeof(uint32)), MF_Clear, GS_COMMENT_FILE_LINE);

		_srcFile = newObject<TagReadFile>(GS_COMMENT_FILE_LINE);
		CHECK_IF_RETURN(_srcFile == NULL, false, "Could not allocate src Video File!");

		String srcPath;

		if (tryGetVideoPath(srcPath, "SAN", videoNum) == false) {
			error(GS_THIS, "Could not find Video File!");
			abort_quit_stop();
			deleteObject(_srcFile);
			return false;
		}

		_srcFile->open(srcPath.string());

		if (_srcFile->isOpen() == false) {
			error(GS_THIS, "Could not open Video File!");
			abort_quit_stop();
			deleteObject(_srcFile);
			return false;
		}

		_videoDecoder = &SMUSH_DECODER;

		if (_videoDecoder->initialize(_srcFile) == false) {
			error(GS_THIS, "Could not read Video File!");
			abort_quit_stop();
			deleteObject(_srcFile);
			_videoDecoder = NULL;
			return false;
		}

		_dstFile = newObject<WriteFile>(GS_COMMENT_FILE_LINE);
		CHECK_IF_RETURN(_dstFile == NULL, false, "Could not allocate Video dst File!");

		String dstPath;
		CHECK_IF_RETURN(tryGetVideoPath(dstPath, "GSV", videoNum) == false, false, "Could not create Destination Video Path");

		_dstFile->open(dstPath.string());

		if (_dstFile->isOpen() == false) {
			error(GS_THIS, "Could not open destination Video File!");
			abort_quit_stop();
			deleteObject(_dstFile);
			return false;
		}

		_videoEncoder = &GSV_ENCODER;

		VideoEncoderParams encoderParams;
		encoderParams.left_px = _halfFrameSize ? GS_BITMAP_HALF_LEFT : GS_BITMAP_LEFT;
		encoderParams.top_px = _halfFrameSize ? GS_BITMAP_HALF_TOP : GS_BITMAP_TOP;
		encoderParams.width_px = _halfFrameSize ? GS_BITMAP_HALF_PITCH : GS_BITMAP_PITCH;
		encoderParams.height_px = _halfFrameSize ? GS_BITMAP_HALF_ROWS : GS_BITMAP_ROWS;
		encoderParams.audioFormat = AF_S16MSB;
		encoderParams.audioFrequency_hz = 22050;
		encoderParams.audioSampleRate_bytes = (1024 * 2 * sizeof(int16));

		if (_videoEncoder->initialize(_dstFile, encoderParams) == false) {
			error(GS_THIS, "Could not open destination Video File!");
			abort_quit_stop();
			deleteObject(_srcFile);
			_videoEncoder = NULL;
			return false;
		}


		debug_write_str("Converting ");
		debug_write_str(srcPath.string());
		debug_write_str(" to ");
		debug_write_str(dstPath.string());
		debug_write_char('\n');

		return true;
	}

	void VideoConverter::run() {

		VideoFrame* frame = acquireVideoFrame();

		debug_write_str("Processing Frames\n");
		uint16 counter = 0;
		uint8 tens = 0;

		uint32 lastDialogue = 0;
		uint32 lastImageNum = 0;
		while(true) {
			bool isKeyFrame = false;
			bool shouldHalfSize = false;

			frame->recycle();
			_videoDecoder->processFrame(frame);

			isKeyFrame = false;


			// If there is a palette change, its a keyframe
			if (frame->_palette != NULL) {
				isKeyFrame = true;
			}


			frame->_timing.clearFlags = 0;

			/* Half size */
			if (_halfFrameSize && frame->_image != NULL ) {
				shouldHalfSize = true;

				// OPENING.SAN/GSV  Credits
				if (_videoNum == 9 && frame->getNum() >= 1722 && frame->getNum() <= 3057) {
					shouldHalfSize = false;

					if (frame->getNum() >= 3038) { // A few frames off.
						frame->_timing.clearFlags = 1;
					}
				}
			}

			if (_halfFrameSize == false && _bakeSubtitles) {
				bakeSubtitles(frame);
				isKeyFrame = false;
			}
			else {
				if (_subtitleCompression) {

					if (frame->_subtitles.hasAny()) {
						uint32 newCount = 0;
						bool identical = true;

						SubtitleFrame *subtitleFrame = frame->_subtitles.peekFront();

						while (subtitleFrame != NULL) {
							if (_lastSubtitles.contains(subtitleFrame->hash) == false) {
								identical = false;
								break;
							}
							newCount++;
							subtitleFrame = subtitleFrame->next;
						}

						if (newCount != _lastSubtitles.getSize()) {
							identical = false;
						}

						// New/Different Subtitles
						if (identical == false) {
							_lastSubtitles.clear();
							subtitleFrame = frame->_subtitles.peekFront();
							while (subtitleFrame != NULL) {
								_lastSubtitles.push(subtitleFrame->hash);
								subtitleFrame = subtitleFrame->next;
							}

							if (shouldHalfSize) {
								frame->_timing.clearFlags = 1;
							}

							frame->_timing.keepSubtitles = 1;
							isKeyFrame = true;

							subtitleFrame = frame->_subtitles.peekFront();
							while (subtitleFrame != NULL) {
								subtitleFrame = subtitleFrame->next;
							}

						} else {
							// Same as last frame
							frame->removeAllSubtitles();
							frame->_timing.keepSubtitles = 1;
						}

					} else {
						// End of Subtitles (Empty)
						if (_lastSubtitles.getSize() != 0) {
							if (shouldHalfSize) {
								frame->_timing.clearFlags = 1;
							}
							_lastSubtitles.clear();
							frame->_timing.keepSubtitles = 0;
							isKeyFrame = true;
						}
					}

				}
			}

			if (shouldHalfSize) {
				reduceFrameSizeToHalf(frame);
			}
			else {

				// Compress if there was a good frame.
				if (frame->hasImage()) {
					if (isKeyFrame == false) {
						compressFrame(frame);
					} else {
						// A keyframe, either way we should copy the source frame over to last
						copyMemQuick((uint32 *) _lastFrame, (uint32 *) frame->_image->getData(), GS_BITMAP_SIZE);
					}
				}
			}


			if (frame->_image != NULL) {
				lastImageNum = frame->getNum();
			}

			_videoEncoder->processFrame(frame);

			if (frame->_timing.action == VFNA_Stop) {
				break;
			}

			counter++;
			tens++;

			if (tens == 10) {
				tens = 0;
				debug_write_int(counter);
				debug_write_char('\n');
			}
		}

		disposeVideoFrame(frame);

		debug_write_str("Completed.\n");
		_videoEncoder->teardown();
		_videoDecoder->teardown();
	}

	void VideoConverter::reduceFrameSizeToHalf(VideoFrame* frame) {
		ImageFrame* image = frame->_image;

		uint8* dst = image->getData();
		uint8* src = image->getData();

		uint16 y = GS_BITMAP_HALF_ROWS;
		while(y--) {
			uint16 x = GS_BITMAP_HALF_PITCH;

			while(x--) {
				*dst++ = *src++;
				src++;
			}

			src += GS_BITMAP_PITCH;
		}

		image->width = GS_BITMAP_HALF_PITCH;
		image->height = GS_BITMAP_HALF_ROWS;
		image->left = GS_BITMAP_LEFT;
		image->top = GS_BITMAP_TOP;
		image->size = GS_BITMAP_HALF_SIZE;
		image->format = IFF_HalfFrameRaw;

	}

	void VideoConverter::compressFrame(VideoFrame* frame) {
		uint32 compressionSize = 0;
		// Initialize
		uint32* dst = (uint32*) _compressionFrame;
		const uint32* src = (uint32*) frame->_image->getData();
		const uint32* last = (uint32*) _lastFrame;

		// Compress

		// 0. Each line
		uint16 y = GS_BITMAP_ROWS; // 480
		while(y--) {

			uint8 x = 32;	// 32 bits per ULONG/segment, 640/32=20px per bit/segment, 20px/4bytes = 5 ulongs
			uint32 mask = 0;

			// 1. Detect changes for this line from previous frame in 20px segments.
			//    Each segment must match exactly.
			//    Each segment change is encoded as a bit into mask.
			while(x--) {
				mask >>= 1;
				uint32 different = 0;

				different |= *src++ ^ *last++;	// if (src != last) { different = 1 (ish); }
				different |= *src++ ^ *last++;
				different |= *src++ ^ *last++;
				different |= *src++ ^ *last++;
				different |= *src++ ^ *last++;

				if (different != 0) {
					mask |= 0x80000000;			// Written MSB first, then bit-shift right in next iteration, so its in the correct order.
				}

			}

			// 2. Write change mask, and then for each mask those segments in right-to-left bit order
			*dst++ = mask;
			src -= 160;		// 5 * 32
			x = 32;

			while(x--) {
				uint32 different = (mask & 1);
				mask >>= 1;

				if (different == 1) {
					*dst++ = *src++;
					*dst++ = *src++;
					*dst++ = *src++;
					*dst++ = *src++;
					*dst++ = *src++;
				}
				else {
					src += 5;
				}
			}
		}

		// Finalize
		compressionSize = (dst - ((uint32*) _compressionFrame)) * sizeof(uint32);
		dst = (uint32*) _compressionFrame;

		// No changes - So remove the image, and do not copy source to last.
		if (compressionSize == (GS_BITMAP_ROWS * sizeof(uint32))) {
			frame->removeImage();
			return;
		}

		// Copy source frame over to last
		copyMemQuick((uint32*) _lastFrame, (uint32*) frame->_image->getData(), GS_BITMAP_SIZE);

		if (compressionSize < GS_BITMAP_SIZE) {
			copyMemQuick((uint32*) frame->_image->getData(), dst, compressionSize);
			frame->_image->format = IFF_FullFrameDelta;
			frame->_image->size = compressionSize;
		}

	}

	void VideoConverter::bakeSubtitles(gs::VideoFrame *frame) {

		if (frame->hasSubtitles() == false)
			return;

		if (frame->_image == NULL) {
			ImageFrame* image = frame->addImage();

			copyMemQuick((uint32*) image->getData(), (uint32*) _lastFrame, GS_BITMAP_SIZE);
			image->size = GS_BITMAP_SIZE;
			image->format = IFF_FullFrameRaw;
		}

		SubtitleFrame* subtitle = frame->_subtitles.peekFront();
		while(subtitle != NULL) {

			drawSubtitlesTo(frame->_image->getData(),
							subtitle->x,
							subtitle->y,
							subtitle->getString(),
							subtitle->flags & SF_Center,
							subtitle->flags & SF_Wrap,
							subtitle->font,
							subtitle->colour);


			subtitle = subtitle->next;
		}

		frame->removeAllSubtitles();
	}


	int convertVideo(uint8 videoNum, bool halfSize, bool subtitleCompression) {

		if (FONT[0] == NULL) {
			FONT[0] = newObject<Font>(0, GS_COMMENT_FILE_LINE);
			FONT[1] = newObject<Font>(1, GS_COMMENT_FILE_LINE);
			FONT[2] = newObject<Font>(2, GS_COMMENT_FILE_LINE);
			FONT[3] = newObject<Font>(3, GS_COMMENT_FILE_LINE);
			FONT[4] = newObject<Font>(4, GS_COMMENT_FILE_LINE);
		}

		VideoConverter* converter = newObject<VideoConverter>(GS_COMMENT_FILE_LINE);
		if (converter->initialize(videoNum, halfSize, subtitleCompression) == false) {
			deleteObject(converter);
			return 1;
		}

		converter->run();
		deleteObject(converter);
		return 0;
	}

}
