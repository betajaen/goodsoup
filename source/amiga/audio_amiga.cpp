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

/*
 *  General Design of this Audio Mixer is based off:
 *  https://github.com/mntmn/scummvm-amigaos3/blob/master/backends/mixer/amigaos3/amigaos3-mixer.cpp
 */

#define GS_FILE_NAME "audio"

#include "../types.h"
#include "../debug.h"
#include "../profile.h"
#include "../memory.h"

#include <proto/exec.h>
#include <inline/exec.h>
#include <proto/ahi.h>
#include <inline/ahi.h>
#include <proto/dos.h>
#include <inline/dos.h>
#include <dos/dostags.h>

#define BUFFER_SIZE (2048 * 2 * sizeof(int16))

namespace gs
{
    void audioCallback_S16MSB(int16* samples, uint32 sampleLength);

	static struct MsgPort* sAHIPort = NULL;
	static struct AHIRequest* sAHIRequest[2] = { NULL, NULL };
	static uint8 sAHIRequestSent[2] = { 0, 0 };
	static byte* sAudioBuffers[2] = { NULL, NULL };
	static byte  sAudioWriteBuffer = 0;
	static struct Task* sAudioThread = NULL;

	static bool _openAHIAudio() {
		sAHIPort = (struct MsgPort*) CreateMsgPort();

		CHECK_IF_RETURN(sAHIPort != NULL, false, "Could not create Message Port for AHI");

		sAHIRequest[0] = (struct AHIRequest*) CreateIORequest(sAHIPort, sizeof(struct AHIRequest));

		CHECK_IF_RETURN(sAHIPort != NULL, false, "Could not create AHI Request 0");

		sAHIRequest[0]->ahir_Version = 4;

		BYTE result = OpenDevice(AHINAME, AHI_DEFAULT_UNIT, (struct IORequest*) sAHIRequest[0], 0);

		CHECK_IF_RETURN(result != 0, false, "Unable to open AHI Device");

		// Note: Not using memory system, as it is not thread safe.
		sAudioBuffers[0] = (byte*) AllocVec(BUFFER_SIZE, MF_Public | MF_Clear);
		CHECK_IF_RETURN(sAudioBuffers[0] != NULL, false, "Unable to allocate AHI buffer 0");
		sAudioBuffers[1] = (byte*) AllocVec(BUFFER_SIZE, MF_Public | MF_Clear);
		CHECK_IF_RETURN(sAudioBuffers[1] != NULL, false, "Unable to allocate AHI buffer 1");

		sAHIRequest[1] = (struct AHIRequest*) AllocVec(sizeof(struct AHIRequest), MEMF_PUBLIC);
		CHECK_IF_RETURN(sAudioBuffers[1] != NULL, false, "Unable to allocate AHI Request 1");

		CopyMem(sAHIRequest[0], sAHIRequest[1], sizeof(struct AHIRequest));

		sAudioWriteBuffer = 0;
		sAHIRequestSent[0] = 0;
		sAHIRequestSent[1] = 0;
	}

	static void _closeAHIAudio() {

		uint8 buffer = sAudioWriteBuffer;

		if (sAHIRequest[buffer]) {
			AbortIO((struct IORequest*) sAHIRequest[buffer]);
			WaitIO((struct IORequest*) sAHIRequest[buffer]);
			sAHIRequest[buffer] = NULL;
		}

		buffer = 1 - buffer;

		if (sAHIRequest[buffer]) {
			AbortIO((struct IORequest*) sAHIRequest[buffer]);
			WaitIO((struct IORequest*) sAHIRequest[buffer]);
			sAHIRequest[buffer] = NULL;
		}

		if (sAHIRequest[1]) {
			FreeVec(sAHIRequest[1]);
			sAHIRequest[1] = NULL;
		}

		if (sAHIRequest[0]) {
			CloseDevice((struct IORequest*) sAHIRequest[0]);
			DeleteIORequest(sAHIRequest[0]);
			sAHIRequest[0] = NULL;
		}

		if (sAudioBuffers[1]) {
			FreeVec((APTR) sAudioBuffers[1]);
		}

		if (sAudioBuffers[0]) {
			FreeVec((APTR) sAudioBuffers[0]);
		}

		if (sAHIPort) {
			DeleteMsgPort(sAHIPort);
		}

	}

	static void _audioWorker() {

	}

	void audioThread(STRPTR args, ULONG length) {
		LONG priority = 0;
		ULONG signals = 0;

		if (_openAHIAudio() == false) {
			_closeAHIAudio();
			return;
		}

		while(true) {

			while(
					!sAHIRequest[sAudioWriteBuffer] ||
					CheckIO((struct IORequest*) sAHIRequest[sAudioWriteBuffer]))
			{
				struct AHIRequest* req = sAHIRequest[sAudioWriteBuffer];

				if (sAHIRequestSent[sAudioWriteBuffer] == 1) {
					WaitIO((struct IORequest*) req);
				}


			}
			_audioWorker();

			signals = Wait(SIGBREAKF_CTRL_C | (1 << sAHIPort->mp_SigBit));
			if (signals & SIGBREAKF_CTRL_C) {
				break;
			}

		}

		_closeAHIAudio();

	}

	void openAudio() {
#if 0
		sAudioThread = (struct Task*) CreateNewProcTags(
			NP_Name, (ULONG) "GSAudio",
			NP_CloseOutput, FALSE,
			NP_CloseInput, FALSE,
			NP_StackSize, 24576,
			NP_Entry, (ULONG) &audioThread,
			TAG_DONE
		);

		SetTaskPri(sAudioThread, 0);
#endif
	}


	void closeAudio() {
#if 0
		if (sAudioThread != NULL) {
			Signal(sAudioThread, SIGBREAKF_CTRL_C);
			Delay(10);
			sAudioThread = NULL;
		}
#endif
	}

	void pauseAudio(uint8 isPaused) {

	}
}
