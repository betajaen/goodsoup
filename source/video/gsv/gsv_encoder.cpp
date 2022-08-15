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

#define GSV_HEADER "GSV1"

namespace gs
{

	static WriteFile* sFile;

	/*
 		General Format of a GSV video file

 			"GSV1"	- 4	- File Header and Version
 			0		- 4	- Offset from beginning to the string table
 			...		- sizeof(VideoEncoderParams) - Video Encoding Params
 			FRME	- 4
			0		- 2 - numAudioSamples
			0		- 2 - numSubtitles
			0		- 1	- hasImageChange
			0		- 1	- hasPaletteChange
			...		- n - 0+ AudioSampleFrame_S16MSB
			...		- n - 0+ SubtitleFrame
			...		- 0 or 307200 - Image Data
			..		- 0 or 768 - Palette Data
			FRME
			...
			FRME
			...
			FRME
 			...
 			STOP
 			STBL
 			StringTable	- n	- Contents of String table (FUTURE)
 			<eof>
 	*/

	bool gsv_encoder_initialize(WriteFile* file, const VideoEncoderParams& params) {
		sFile = file;
		sFile->writeTag(GSV_HEADER);
		sFile->writeUInt32BE(0);	// /* TODO: Will point to the string table in the file */
		sFile->writeBytes(&params, sizeof(VideoEncoderParams));
		return true;
	}

	void gsv_encoder_teardown() {
		sFile->writeTag("STOP");
		/* TODO: STBL - String table */
	}

	uint8  gsv_encoder_processFrame(VideoFrame* frame) {
		sFile->writeTag("FRME");


		return 0;
	}
}

gs::VideoEncoder GSV_ENCODER = {
		&gs::gsv_encoder_initialize,
		&gs::gsv_encoder_teardown,
		&gs::gsv_encoder_processFrame
};