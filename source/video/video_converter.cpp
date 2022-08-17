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
#include "memory.h"
#include "profile.h"

namespace gs
{

	VideoConverter::VideoConverter() {
		_lastFrame = NULL;
		_newFrame = NULL;
	}

	VideoConverter::~VideoConverter() {
		releaseMemory(_lastFrame);
		releaseMemory(_newFrame);
	}

	void VideoConverter::initialize(bool frameDifference, bool halfScale) {
		_doFrameDifference = frameDifference;
		_doHalfScale = halfScale;

		_lastFrame = (byte*) allocateMemory(1, GS_BITMAP_SIZE, MF_Clear, GS_COMMENT_FILE_LINE);
		_newFrame = (byte*) allocateMemory(1, GS_BITMAP_SIZE, MF_Clear, GS_COMMENT_FILE_LINE);

	}

	void VideoConverter::convert(byte* dstFrameBuffer, byte* newFrameData) {
		GS_SWAP(byte*, _lastFrame, _newFrame);
		copyMemQuick((uint32*) _newFrame, (uint32*) newFrameData, GS_BITMAP_SIZE);

		if (_doHalfScale) {
			uint8 y = 240;
			byte* src = _newFrame;
			byte* dst = dstFrameBuffer;


			while(y--) {

				uint16 x = 320;
				while(x--) {

					*dst++ = *src++;
					src++;
				}

				src+=640;

			}

		}

		if (_doFrameDifference) {

			uint32* prev = (uint32*) _lastFrame;
			uint32* now = (uint32*) _newFrame;
			uint32* dst = (uint32*) dstFrameBuffer;


			uint16 y = 480;
			while(y--) {

				uint8 b = 16;

				while(b--) {
					uint8 k = 10;
					uint8 same = 1;

					while(k--) {
						if (*prev++ == *now++) {
							continue;
						}

						same = 0;
					}

					if (same) {
						k = 10;
						while (k--) {
							dst++;
						}
					}
					else {
						k = 10;
						while (k--) {
							*dst++ = 0xFFffFFff;
						}
					}

				}




			}

		}
	}


}
