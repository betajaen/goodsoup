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

#ifndef GS_AHI_PRIORITY
#define GS_AHI_PRIORITY 10
#endif

#define BUFFER_SIZE (2048 * 2 * sizeof(int16))

#if 0
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

		if (sAHIPort == NULL) {
			error(GS_THIS, "Could not create MessagePort for AHI.");
			abort_quit_stop();
			return false;
		}

		sAHIRequest[0] = (struct AHIRequest*) CreateIORequest(sAHIPort, sizeof(struct AHIRequest));

		if (sAHIRequest[0] == NULL) {
			error(GS_THIS, "Could not create AHI Request 0");
			abort_quit_stop();
			return false;
		}

		sAHIRequest[0]->ahir_Version = 4;

		BYTE result = OpenDevice(AHINAME, AHI_DEFAULT_UNIT, (struct IORequest*) sAHIRequest[0], 0);

		if (result != 0) {
			error(GS_THIS, "Unable to open AHI Device");
			abort_quit_stop();
			return false;
		}

		// Note: Not using memory system, as it is not thread safe.
		sAudioBuffers[0] = (byte*) AllocVec(BUFFER_SIZE, MEMF_PUBLIC | MEMF_CLEAR);

		if (sAudioBuffers[0] == NULL) {
			error(GS_THIS, "Unable to allocate AHI buffer 0");
			abort_quit_stop();
			return false;
		}

		sAudioBuffers[1] = (byte*) AllocVec(BUFFER_SIZE, MEMF_PUBLIC | MEMF_CLEAR);

		if (sAudioBuffers[1] == NULL) {
			error(GS_THIS, "Unable to allocate AHI buffer 1");
			abort_quit_stop();
			return false;
		}

		sAHIRequest[1] = (struct AHIRequest*) AllocVec(sizeof(struct AHIRequest), MEMF_PUBLIC);

		if (sAHIRequest[1] == NULL) {
			error(GS_THIS, "Unable to allocate AHI buffer 1");
			abort_quit_stop();
			return false;
		}

		CopyMem(sAHIRequest[0], sAHIRequest[1], sizeof(struct AHIRequest));

		sAudioWriteBuffer = 0;
		sAHIRequestSent[0] = false;
		sAHIRequestSent[1] = false;
		
		return true;
	}

	static void _closeAHIAudio() {

#if 0

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
#endif

	}

	static void _audioWorker() {

	}

	void audioThread(STRPTR args, ULONG length) {
		LONG priority = 0;
		ULONG signals = 0;

		debug(GS_THIS, "IN AUDIO THREAD");

		uint8 count = 0;

		while(true) {

			while(
					(sAHIRequestSent[sAudioWriteBuffer] == false) ||
					CheckIO((struct IORequest*) sAHIRequest[sAudioWriteBuffer]))
			{
				struct AHIRequest* req = sAHIRequest[sAudioWriteBuffer];

				if (sAHIRequestSent[sAudioWriteBuffer] == true) {
					WaitIO((struct IORequest*) req);
				}

				req->ahir_Std.io_Message.mn_Node.ln_Pri = GS_AHI_PRIORITY;
				req->ahir_Std.io_Command = CMD_WRITE;
				req->ahir_Std.io_Data = sAudioBuffers[sAudioWriteBuffer];
				req->ahir_Std.io_Length = BUFFER_SIZE;
				req->ahir_Std.io_Offset = 0;
				req->ahir_Type = AHIST_S16S;
				req->ahir_Frequency = GS_AUDIO_FREQUENCY_HZ;
				req->ahir_Position = 0x8000;
				req->ahir_Volume = 0x10000;
				req->ahir_Link = (sAHIRequestSent[sAudioWriteBuffer^1]) ? sAHIRequest[sAudioWriteBuffer^1] : NULL;

				// TODO: Can Callback

				SendIO((struct IORequest*) sAHIRequest[sAudioWriteBuffer]);
				sAHIRequestSent[sAudioWriteBuffer] = true;

				sAudioWriteBuffer ^= 1;
			}


			signals = Wait(SIGBREAKF_CTRL_C | (1 << sAHIPort->mp_SigBit));
			if (signals & SIGBREAKF_CTRL_C) {
				break;
			}

		}

		debug(GS_THIS, "LEFT AUDIO THREAD!!!!1");

		_closeAHIAudio();

	}

	bool openAudio() {
#if 1

		if (_openAHIAudio() == false) {
			_closeAHIAudio();
			return false;
		}


		sAudioThread = (struct Task*) CreateNewProcTags(
			NP_Name, (ULONG) "GSAudio",
			NP_Output, (ULONG) Output(),
			NP_Input, (ULONG) Input(),
			NP_CloseOutput, FALSE,
			NP_CloseInput, FALSE,
			NP_StackSize, 65536,
			NP_Entry, (ULONG) &audioThread,
			TAG_DONE
		);

		if (sAudioThread != NULL) {
			SetTaskPri(sAudioThread, GS_AHI_PRIORITY);

			return true;
		}

		return false;
#else
		return true;
#endif

	}


	void closeAudio() {
#if 1
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

#else

struct Library* AHIBase = NULL;

namespace gs
{
	static struct MsgPort* sAHIPort = NULL;
	static struct AHIRequest* sAHIRequest = NULL;
	static struct AHIAudioCtrl* sAHIAudioCtrl = NULL;
	static byte* sAHISampleData = NULL;
	static struct AHISampleInfo sAHISampleInfo;

	bool openAudio() {

		sAHIPort = CreateMsgPort();

		if (sAHIPort == NULL) {
			error(GS_THIS, "Could not create AHI MsgPort");
			abort_quit_stop();
			return false;
		}

		sAHIRequest = (struct AHIRequest*) CreateIORequest(sAHIPort, sizeof(struct AHIRequest));

		if (sAHIRequest == NULL) {
			error(GS_THIS, "Could not create AHI Request");
			abort_quit_stop();
			return false;
		}

		sAHIRequest->ahir_Version = 4;

		BYTE isError = OpenDevice(AHINAME, AHI_NO_UNIT, (struct IORequest*) sAHIRequest, NULL);

		if (isError) {
			error(GS_THIS, "Could not open AHI device");
			abort_quit_stop();
			return false;
		}

		AHIBase = (struct Library*) sAHIRequest->ahir_Std.io_Device;

		sAHIAudioCtrl = AHI_AllocAudio(
				AHIA_AudioID, 0,
				AHIA_MixFreq, GS_AUDIO_FREQUENCY_HZ,
				AHIA_Channels, 1,
				AHIA_Sounds, 1,
				TAG_DONE);

		if (sAHIAudioCtrl == NULL) {
			error(GS_THIS, "Could not Allocate AHI Audio");
			abort_quit_stop();
			return false;
		}

		uint32 gotFrequency;
		AHI_ControlAudio(sAHIAudioCtrl, AHIC_MixFreq_Query, (ULONG) &gotFrequency, TAG_DONE);

		debug(GS_THIS, "Want Frequency = %ld, Got Frequency = %ld", GS_AUDIO_FREQUENCY_HZ, gotFrequency);


		sAHISampleData = (byte*) AllocVec(BUFFER_SIZE, MEMF_CLEAR  | MEMF_PUBLIC);
		sAHISampleInfo.ahisi_Address = (APTR) sAHISampleData;
		sAHISampleInfo.ahisi_Length = 2048;
		sAHISampleInfo.ahisi_Type = AHIST_S16S;

#if 0
		for(uint16 i=0;i < 1024;i+=2) {
			sAHISampleData[i] =   i & 0xFF;	// Noise test.
			sAHISampleData[i+1] = i & 0xFF;	// Noise test.
		}
#endif

		AHI_SetFreq(0, gotFrequency, sAHIAudioCtrl, AHISF_IMM);
		AHI_SetVol(0, 0x10000, 0x8000, sAHIAudioCtrl, AHISF_IMM);

		AHI_LoadSound(0, AHIST_DYNAMICSAMPLE, &sAHISampleInfo, sAHIAudioCtrl);
		AHI_SetSound(0, 0,0,0,  sAHIAudioCtrl, AHISF_IMM);

		AHI_ControlAudio(sAHIAudioCtrl, AHIC_Play, TRUE, TAG_DONE);

		debug(GS_THIS, "Opened AHI Audio");

		return true;
	}

	void closeAudio() {

		if (sAHIAudioCtrl != NULL) {
			AHI_ControlAudio(sAHIAudioCtrl,
							 AHIC_Play, FALSE,
							 TAG_DONE);

			AHI_UnloadSound(0, sAHIAudioCtrl);
			AHI_FreeAudio(sAHIAudioCtrl);
			sAHIAudioCtrl = NULL;
		}

		if (sAHISampleData != NULL) {
			FreeVec(sAHISampleData);
		}

		if (sAHIRequest != NULL) {
			CloseDevice((struct IORequest*) sAHIRequest);
			DeleteIORequest((struct IORequest*) sAHIRequest);
			sAHIRequest = NULL;
		}

		if (sAHIPort != NULL) {
			DeleteMsgPort(sAHIPort);
			sAHIPort = NULL;
		}


		debug(GS_THIS, "Closed AHI Audio");
	}

	void pauseAudio(uint8 isPaused) {

	}


}

#endif

