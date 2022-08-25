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

#include "forward.h"
#include "debug.h"
#include "profile.h"
#include "memory.h"
#include "audio.h"

#include <proto/exec.h>
#include <inline/exec.h>
#include <proto/ahi.h>
#include <inline/ahi.h>
#include <proto/dos.h>
#include <inline/dos.h>
#include <dos/dostags.h>
#include "amiga/SDI/SDI_hook.h"

using namespace gs;

#ifndef GS_AHI_DEVICE_MODE
#define GS_AHI_DEVICE_MODE 1
#endif

struct Library* AHIBase = NULL;
static struct MsgPort* sAHIPort = NULL;
static struct AHIRequest* sAHIRequest = NULL;
static struct AHIAudioCtrl* sAHIAudioCtrl = NULL;
static Queue<AudioPacket> sQueue;

#if GS_AHI_DEVICE_MODE == 1

#define GS_AHI_AUDIO_THREAD_NAME "GSAudio"

static AudioPacket* sCurrentPacket = NULL;
static uint32 sCurrentPos = 0;
static uint32 sCurrentRemaining = 0;
static struct Task* sThread = NULL;
static bool sThreadOpen = false;

namespace gs
{

	static bool openAHI();
	static void closeAHI();

}

static int gs_ahi_thread_function(STRPTR args, ULONG argsLength) {
	ULONG signals;

	sThreadOpen = true;

	if (openAHI() == false) {
		sThreadOpen = false;
		return 1;
	}

	while(true) {
		Delay(10);
		signals = Wait(SIGBREAKF_CTRL_C);

		if (signals & SIGBREAKF_CTRL_C) {
			break;
		}
	}

	closeAHI();
	sThreadOpen = false;
}
#endif

namespace gs
{

	static bool openAHI() {

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
				AHIA_Channels, 2,
				AHIA_Sounds, 2,
		//AHIA_SoundFunc, (ULONG) &gs_ahi_sound_fn_hook,
		//AHIA_PlayerFunc, (ULONG) &gs_ahi_player_fn_hook,
				TAG_DONE);

		if (sAHIAudioCtrl == NULL) {
			error(GS_THIS, "Could not Allocate AHI Audio");
			abort_quit_stop();
			return false;
		}

		uint32 gotFrequency;
		AHI_ControlAudio(sAHIAudioCtrl, AHIC_MixFreq_Query, (ULONG) &gotFrequency, TAG_DONE);

		debug(GS_THIS, "Want Frequency = %ld, Got Frequency = %ld", GS_AUDIO_FREQUENCY_HZ, gotFrequency);

		return true;
	}

	static void closeAHI() {

		if (sAHIAudioCtrl != NULL) {
			AHI_ControlAudio(sAHIAudioCtrl,
							 AHIC_Play, FALSE,
							 TAG_DONE);

			AHI_UnloadSound(0, sAHIAudioCtrl);
			AHI_FreeAudio(sAHIAudioCtrl);
			sAHIAudioCtrl = NULL;
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

	static void openThread() {
#if GS_AHI_DEVICE_MODE == 1
		sThread = (struct Task*) CreateNewProcTags(
				NP_Name, (ULONG) GS_AHI_AUDIO_THREAD_NAME,
				NP_CloseOutput, FALSE,
				NP_CloseInput, FALSE,
				NP_Output, Output(),
				NP_Input, Input(),
				NP_StackSize, 32678,
				NP_Entry, (ULONG) &gs_ahi_thread_function,
				TAG_END
				);
#endif
	}

	static void closeThread() {
#if GS_AHI_DEVICE_MODE == 1
	if (sThread != NULL) {
		Signal(sThread, SIGBREAKF_CTRL_C);
		uint32 counter = 0;
		while(sThreadOpen) {
			Delay(10);
			debug(GS_THIS, "Waiting for Audio Thread to quit... %ld", counter++);
		}
		Delay(50);
		sThread = NULL;
	}
#endif
	}

	bool openAudio() {
		openThread();

		return true;
	}

	void closeAudio() {
		closeThread();
		debug(GS_THIS, "Audio Closed.");
	}

	void pauseAudio(uint8 isPaused) {
	}

	AudioPacket* allocateAudioPacket(uint32 length_bytes) {
		// No AudioPools for now
		AudioPacket* audioPacket = (AudioPacket*) AllocVec(sizeof(AudioPacket), MF_Clear | MF_Any);
		audioPacket->next = NULL;
		audioPacket->length_bytes = length_bytes;
		audioPacket->data = AllocVec(length_bytes, MF_Any);
		return audioPacket;
	}

	void submitAudioPacket(AudioPacket* audioPacket) {
		// TEMP
		releaseAudioPacket(audioPacket);
	}

	void releaseAudioPacket(AudioPacket* audioPacket) {
		if (audioPacket) {
			if (audioPacket->data) {
				FreeVec(audioPacket->data);
			}
			FreeVec(audioPacket);
		}
	}
}


