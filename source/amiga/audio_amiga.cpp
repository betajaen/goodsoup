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

#define GS_FILE_NAME "audio"

#include "../types.h"
#include "../debug.h"
#include "../profile.h"

#include <proto/exec.h>
#include <proto/ahi.h>
#include <devices/ahi.h>

namespace gs
{
    void audioCallback_S16MSB(int16* samples, uint32 sampleLength);

	struct MsgPort* sAHIPort = NULL;
	struct AHIRequest *sAHIRequest = NULL;
	BYTE sAHIDevice = 0;

	void openAudio() {
		if (AHImp=CreateMsgPort()) {
			if (AHio = (struct AHIRequest *) CreateIORequest(AHImp, sizeof(struct AHIRequest))) {
				AHio->ahir_Version = 4;
				AHIDevice = OpenDevice(AHINAME, 0, (struct IORequest *) AHio, NULL);
				debug(GS_THIS, "Audio Opened");
			}
		}
	}

	void closeAudio() {

		if (!AHIDevice) {
			CloseDevice((struct IORequest *) AHio);
		}

		DeleteIORequest((struct IORequest *)AHio);
		//DeleteIORequest((struct IORequest *)AHIio2);
		DeleteMsgPort(AHImp);

		debug(GS_THIS, "Audio closed.");
	}

	void audioPush16(const void* data, uint32 length) {
	}
}
