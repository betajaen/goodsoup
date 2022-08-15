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

#define GS_FILE_NAME "gsv_decoder"

#include "forward.h"
#include "file.h"
#include "video/video_frame.h"
#include "video/video_api.h"

namespace gs
{
	static TagReadFile* sFile;

	bool gsv_decoder_initialize(TagReadFile* file) {
		sFile = file;
		return true;
	}

	void gsv_decoder_teardown() {
	}

	uint8  gsv_decoder_processFrame(VideoFrame* frame) {

		/* TODO */

		return 0;
	}
}

gs::VideoDecoder GSV_DECODER = {
		&gs::gsv_decoder_initialize,
		&gs::gsv_decoder_teardown,
		&gs::gsv_decoder_processFrame
};