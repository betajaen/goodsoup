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

#ifndef GS_VIDEO_API_H
#define GS_VIDEO_API_H

namespace gs
{

	class DiskReader;
	class TagReadFile;
	class VideoFrame;
	class WriteFile;

	struct VideoApi {
		void(*initialize)(DiskReader reader);
		void(*teardown)();
		int(*processFrame)();
	};

	struct VideoDecoder {
		bool(*initialize)(TagReadFile* file);
		void(*teardown)();
		uint8(*processFrame)(VideoFrame* frame);
	};


	struct VideoEncoderParams {
		// Left position of a video frame in pixels (i.e. 0)
		uint16 left_px;
		// Top position of a video frame in pixels (i.e. 0)
		uint16 top_px;
		// Width of a video frame in pixels (i.e. 640)
		uint16 width_px;
		// Height of a video frame in pixels (i.e. 480)
		uint16 height_px;
		// Reserved
		uint8  reserved;
		// Audio Format (i.e. AF_S16MSB, see AudioFormat in audio.h)
		uint8  audioFormat;
		// Audio Frequency in Hertz (i.e. 22050 Hz)
		uint16 audioFrequency_hz;
		// Audio Sample Rate in Bytes (i.e. 4096)
		uint16 audioSampleRate_bytes;
	};


	struct VideoEncoder {
		bool(*initialize)(WriteFile* file, const VideoEncoderParams& params);
		void(*teardown)();
		uint8(*processFrame)(VideoFrame* frame);
	};


}

#endif