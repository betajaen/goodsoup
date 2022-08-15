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

	struct VideoEncoder {
		bool(*initialize)(WriteFile* file);
		void(*teardown)();
		uint8(*processFrame)(VideoFrame* frame);
	};


}

#endif