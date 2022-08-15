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

#define GS_FILE_NAME "gsv_encoder"

#include "forward.h"
#include "file.h"
#include "video/video_frame.h"
#include "video/video_api.h"

namespace gs
{
	static WriteFile* sFile;

	bool gsv_encoder_initialize(WriteFile* file) {
		sFile = file;
		sFile->writeTag("GSV ");
		return true;
	}

	void gsv_encoder_teardown() {
		sFile->writeTag("STOP");
	}

	uint8  gsv_encoder_processFrame(VideoFrame* frame) {

		/* TODO */

		return 0;
	}
}

gs::VideoEncoder GSV_ENCODER = {
		&gs::gsv_encoder_initialize,
		&gs::gsv_encoder_teardown,
		&gs::gsv_encoder_processFrame
};