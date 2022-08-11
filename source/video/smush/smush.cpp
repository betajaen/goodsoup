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

#define GS_FILE_NAME "smush"

#include "forward.h"
#include "containers.h"
#include "video/video_frame.h"
#include "video/video_api.h"

namespace gs
{
	TagReadFile* sFile;
	byte* sPalette;
	byte* sFrames[3];
	byte  sCurrentFrameBuffer;
	byte  sDeltaFrameBuffers[2];
	char* sSubtitleText;
	byte* sCompressedAudioSample;

	static bool smush_initialize(TagReadFile* file) {
		sFile = file;
		sPalette = (byte*) allocateMemory(256, 3 * sizeof(byte), MF_Clear, GS_COMMENT_FILE_LINE);
		byte* videoFrames = (byte*) allocateMemory(3, GS_BITMAP_SIZE, MF_Clear, GS_COMMENT_FILE_LINE);
		sFrames[0] = videoFrames;
		sFrames[1] = videoFrames + GS_BITMAP_SIZE;
		sFrames[2] = videoFrames + GS_BITMAP_SIZE + GS_BITMAP_SIZE;
		sSubtitleText = (char*) allocateMemory(256, sizeof(char), MF_Clear, GS_COMMENT_FILE_LINE);
		sCompressedAudioSample = (byte*) allocateMemory(4096 + 2, sizeof(byte), MF_Clear, GS_COMMENT_FILE_LINE);

		sCurrentFrameBuffer = 3;
		sDeltaFrameBuffers[0] = 0;
		sDeltaFrameBuffers[1] = 1;

		return true;
	}

	static void smush_teardown() {
		releaseMemoryChecked(sCompressedAudioSample);
		releaseMemoryChecked(sSubtitleText);
		releaseMemoryChecked(sFrames[0]);
		sFrames[1] = NULL;
		sFrames[2] = NULL;
		releaseMemoryChecked(sPalette);
	}

	static uint8 smush_processFrame(VideoFrame* frame) {
		return 2;
	}

}

gs::VideoCodec SMUSH_VIDEO_CODEC = {
		&gs::smush_initialize,
		&gs::smush_teardown,
		&gs::smush_processFrame
};