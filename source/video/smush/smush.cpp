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
	static bool smush_initialize(TagReadFile* file) {
		return true;
	}

	static void smush_teardown() {

	}

	static bool smush_processFrame(VideoFrame* frame) {
		return true;
	}

}

gs::VideoCodec SMUSH_VIDEO_CODEC = {
		&gs::smush_initialize,
		&gs::smush_teardown,
		&gs::smush_processFrame
};