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

#ifndef GS_VIDEO_CONVERTER_H
#define GS_VIDEO_CONVERTER_H

#include "forward.h"
#include "containers.h"

namespace gs
{

	class VideoDecoder;
	class VideoEncoder;
	class VideoFrame;

	class VideoConverter {
	private:

		VideoDecoder* _videoDecoder;
		VideoEncoder* _videoEncoder;
		TagReadFile* _srcFile;
		WriteFile* _dstFile;
		byte* _frameBuffer;
		byte* _lastFrame;
		byte* _compressionFrame;
		bool _halfFrameSize;
		bool _subtitleCompression;
		bool _bakeSubtitles;
		uint16 _videoNum;
		Array<uint32> _lastSubtitles;

		void compressFrame(VideoFrame* frame);
		void reduceFrameSizeToHalf(VideoFrame* frame);
		void bakeSubtitles(VideoFrame* frame);

	public:

		VideoConverter();
		~VideoConverter();

		bool initialize(uint8 videoNum, bool halfFrameSize, bool subtitleCompression);
		void run();

	};

	int convertVideo(uint8 num, bool halfSize, bool subtitleCompression);

}

#endif