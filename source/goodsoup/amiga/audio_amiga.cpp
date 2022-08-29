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
#include "timer_amiga.h"

#include <proto/exec.h>
#include <inline/exec.h>
#include <proto/ahi.h>
#include <inline/ahi.h>
#include <proto/dos.h>
#include <inline/dos.h>
#include <dos/dostags.h>


#include "amiga/SDI/SDI_hook.h"

#define GS_AHI_AUDIO_THREAD_NAME "GSAudio"
#define GS_AHI_AUDIO_MAX_SLOTS 1

using namespace gs;

struct AudioSlot {
	gs::AudioPacket* current;
	int8 state;
	uint8 counter;
};

Library* AHIBase = NULL;
struct MsgPort* sAHIPort = NULL;
struct AHIRequest* sAHIRequest = NULL;
struct AHIAudioCtrl* sAHIAudioCtrl = NULL;
gs::Queue<gs::AudioPacket> sQueue;

struct MsgPort* sQueueReadyPort = NULL;
struct Task* sThread = NULL;
AudioSlot sAudioSlots[GS_AHI_AUDIO_MAX_SLOTS];

namespace gs
{
	static bool openAHI();
	static void closeAHI();
	static void releaseAudioPacketFromData(void* data);
	static void freeSlot(uint8 num);
	static bool playFreeSlot(AudioPacket* audioPacket, bool imm);
}

extern "C" void gs_ahi_sound_cb(struct AHIAudioCtrl *actrl, struct AHISoundMessage* msg) {

	const uint8 num = msg->ahism_Channel;

	if (num >= GS_AHI_AUDIO_MAX_SLOTS)
		return;

	AudioSlot* audioSlot = &sAudioSlots[num];

	if (audioSlot->state == 1) {
		audioSlot->counter++;
		if (audioSlot->counter == 2) {
			audioSlot->state = 2;
			AHI_SetSound(num, AHI_NOSOUND, 0, 0, sAHIAudioCtrl, 0);
			// End Play
			// freeSlot(msg->ahism_Channel);
			// AudioPacket *packet = sQueue.peekFront();
			// if (playFreeSlot(packet, false)) {
			// 	sQueue.pullFront();
			// }
		}
	}
}

static int gs_ahi_thread_function(STRPTR args, ULONG argsLength) {

	SystemTimer timer;
	timer.open();
	const ULONG signalBit = timer.getSignalBit();

	ULONG signals;

	while(true) {
		timer.start(10000);

		signals = Wait(SIGBREAKF_CTRL_C | signalBit);

		if (signals & SIGBREAKB_CTRL_C) {
			break;
		}

		if (signals & signalBit) {
			AudioPacket *packet = sQueue.peekFront();
			if (packet != NULL && playFreeSlot(packet, true)) {
				sQueue.pullFront();
			}
		}
	}

	timer.close();

}

extern Hook gs_ahi_sound_fn_hook;


namespace gs {

	static void openThread() {
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
	}

	static void closeThread() {
		if (sThread != NULL) {
			Signal(sThread, SIGBREAKF_CTRL_C);
			Delay(50);
			sThread = NULL;
		}
	}

	static void freeSlot(uint8 num) {
		AudioSlot* audioSlot = &sAudioSlots[num];

		if (audioSlot->state != 0)
			return;

		AHI_UnloadSound(num, sAHIAudioCtrl);
		releaseAudioPacket(audioSlot->current);
		audioSlot->current = NULL;
		audioSlot->state = 0;
	}

	static bool playFreeSlot(AudioPacket* audioPacket, bool imm) {
		for(uint8 num=0; num < GS_AHI_AUDIO_MAX_SLOTS; num++) {
			AudioSlot* audioSlot = &sAudioSlots[num];
			if (audioSlot->state != 1) {
				audioSlot->state = 3;

				if (audioSlot->current != NULL) {
					AHI_UnloadSound(num, sAHIAudioCtrl);
					releaseAudioPacket(audioSlot->current);
					audioSlot->current = NULL;
				}
				audioSlot->current = audioPacket;
				audioSlot->counter = 0;

				ULONG immFlag = imm ? AHISF_IMM : 0;

				struct AHISampleInfo sample;
				sample.ahisi_Address = audioPacket->data;
				sample.ahisi_Length = audioPacket->length_samples;
				sample.ahisi_Type = AHIST_S16S;
				AHI_LoadSound(num, AHIST_SAMPLE, &sample, sAHIAudioCtrl);
				AHI_SetFreq(num, GS_AUDIO_FREQUENCY_HZ, sAHIAudioCtrl, immFlag);
				AHI_SetVol(num, 0x10000, 0x8000, sAHIAudioCtrl, immFlag);
				AHI_SetSound(num, num, 0, 0, sAHIAudioCtrl, immFlag);
				// AHI_SetSound(i, AHI_NOSOUND, 0, 0, sAHIAudioCtrl, 0); // Queue a stop after?
				audioSlot->state = 1;

				return true;

			}
		}

		return false;
	}

	static void addToQueue(AudioPacket* audioPacket) {
		//if (playFreeSlot(audioPacket, true) == false) {
		sQueue.pushBack(audioPacket);
			// Should the timer.device call a function periodically to handle these?
		//}
	}

	static bool openAHI() {

		for(uint8 i=0; i < GS_AHI_AUDIO_MAX_SLOTS; i++) {
			AudioSlot* audioSlot = &sAudioSlots[i];
			audioSlot->current = NULL;
			audioSlot->state = 0;
		}

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


		sAHIAudioCtrl = AHI_AllocAudio(AHIA_AudioID, AHI_DEFAULT_ID,
									   AHIA_MixFreq, GS_AUDIO_FREQUENCY_HZ,
									   AHIA_Channels, 2,
									   AHIA_Sounds, 1,
									   AHIA_SoundFunc, (ULONG) &gs_ahi_sound_fn_hook,
									   TAG_END);

		if (sAHIAudioCtrl == NULL) {
			error(GS_THIS, "Could not create AHI Audio Control");
			abort_quit_stop();
			return false;
		}

		AHI_ControlAudio(sAHIAudioCtrl, AHIC_Play, TRUE, TAG_DONE);

		return true;
	}

	static void closeAHI() {

		if (sAHIAudioCtrl) {
			AHI_FreeAudio(sAHIAudioCtrl);
			sAHIAudioCtrl = NULL;
		}

		if (sAHIRequest != NULL) {
			CloseDevice((struct IORequest *) sAHIRequest);
			DeleteIORequest((struct IORequest *) sAHIRequest);
			sAHIRequest = NULL;
		}

		if (sAHIPort != NULL) {
			DeleteMsgPort(sAHIPort);
			sAHIPort = NULL;
		}


		debug(GS_THIS, "Closed AHI Audio");
	}

	bool openAudio() {
		openThread();
		if (openAHI() == false)
			return false;

		return true;
	}

	void closeAudio() {
		closeAHI();
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
		// 4 bytes prefixes the datapacket which contains a pointer to AudioPacket, the caller
		// only sees the memory after this.
		ULONG* dataPacket = (ULONG*) AllocVec(sizeof(AudioPacket*) + length_bytes, MEMF_CHIP);
		*dataPacket = (ULONG) audioPacket;
		audioPacket->data = (void*) (dataPacket + 1);
		return audioPacket;
	}

	void submitAudioPacket(AudioPacket* audioPacket) {
		addToQueue(audioPacket);
	}

	static void releaseAudioPacketFromData(void* data) {
		if (data) {
			ULONG* dataPacket = ((ULONG*) data) - 1;
			AudioPacket* audioPacket = (AudioPacket*) *dataPacket;
			FreeVec(dataPacket);
			FreeVec(audioPacket);
		}
	}

	void releaseAudioPacket(AudioPacket* audioPacket) {
		if (audioPacket) {
			if (audioPacket->data) {
				ULONG* dataPacket = ((ULONG*) audioPacket->data) - 1;
				FreeVec(dataPacket);
			}
			FreeVec(audioPacket);
		}
	}
}



#if 0

using namespace gs;

#ifndef GS_AHI_DEVICE_MODE
#define GS_AHI_DEVICE_MODE 1
#endif

struct Library* AHIBase = NULL;
static struct MsgPort* sAHIPort = NULL;
static struct AHIRequest* sAHIRequest1 = NULL;
static struct AHIRequest* sAHIRequest2 = NULL;
static Queue<AudioPacket> sQueue;
static Mutex sQueueMutex;

#if GS_AHI_DEVICE_MODE == 1

#define GS_AHI_AUDIO_THREAD_NAME "GSAudio"

struct MsgPort* sQueueReadyPort = NULL;
AudioPacket* sCurrentPacket = NULL;
uint32 sCurrentPos = 0;
uint32 sCurrentRemaining = 0;
struct Task* sThread = NULL;
bool sThreadOpen = false;
uint32 sRead = 0;
byte sReadySignalBit = 0;

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

	sReadySignalBit = AllocSignal(-1L);
	ULONG readySignalFlag = (1 << (ULONG) (sReadySignalBit));
	ULONG ahiFlag = (1 << sAHIPort->mp_SigBit);

	debug_write_str("**** THREAD BEGIN");

	struct AHIRequest* req1 = sAHIRequest1;
	struct AHIRequest* req2 = sAHIRequest2;
	struct AHIRequest* link = NULL;
	bool doWaitIo = false;

	while(true) {

		signals = Wait(SIGBREAKF_CTRL_C | ahiFlag | readySignalFlag);

		if (doWaitIo) {
			doWaitIo = false;
			WaitIO((struct IORequest *) link);
		}

		if (signals & SIGBREAKF_CTRL_C) {
			break;
		}

		if (signals & ahiFlag) {
			CheckIO((struct IORequest*) sAHIRequest1);
		}

		if (signals & readySignalFlag) {

			if (sCurrentPacket) {
				releaseAudioPacket(sCurrentPacket);
				sCurrentPacket = NULL;
			}

			sCurrentPacket = sQueue.pullFront();

			if (sCurrentPacket == NULL) {
				continue;
			}

			sRead--;

			req1->ahir_Std.io_Message.mn_Node.ln_Pri = 0;
			req1->ahir_Std.io_Command  = CMD_WRITE;
			req1->ahir_Std.io_Data     = ((uint8*)sCurrentPacket->data);
			req1->ahir_Std.io_Length   = sCurrentPacket->length_bytes;
			req1->ahir_Std.io_Offset   = 0;
			req1->ahir_Frequency       = GS_AUDIO_FREQUENCY_HZ;
			req1->ahir_Type            = AHIST_S16S;
			req1->ahir_Volume          = 0x10000;          // Full volume
			req1->ahir_Position        = 0x8000;           // Centered
			req1->ahir_Link            = link;
			SendIO((struct IORequest *) req1);

			if (link) {
				doWaitIo = true;
				continue;
			}

			link = req1;
			GS_SWAP(struct AHIRequest*, req1, req2);

			if (sCurrentPacket) {
				releaseAudioPacket(sCurrentPacket);
				sCurrentPacket = NULL;
			}
		}


	}

	debug_write_str("**** THREAD END");

exit_thread:
	FreeSignal(sReadySignalBit);
	sReadySignalBit = 0;
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

		sAHIRequest1 = (struct AHIRequest*) CreateIORequest(sAHIPort, sizeof(struct AHIRequest));

		if (sAHIRequest1 == NULL) {
			error(GS_THIS, "Could not create AHI Request");
			abort_quit_stop();
			return false;
		}

		sAHIRequest1->ahir_Version = 4;

		BYTE isError = OpenDevice(AHINAME, AHI_NO_UNIT, (struct IORequest*) sAHIRequest1, NULL);

		if (isError) {
			error(GS_THIS, "Could not open AHI device");
			abort_quit_stop();
			return false;
		}

		AHIBase = (struct Library*) sAHIRequest1->ahir_Std.io_Device;

		sAHIRequest2 = (struct AHIRequest*) AllocVec(sizeof(struct AHIRequest), MF_Any);
		CopyMem(sAHIRequest1, sAHIRequest2, sizeof(struct AHIRequest));

		return true;
	}

	static void closeAHI() {

		if (sAHIRequest1 != NULL) {
			CloseDevice((struct IORequest*) sAHIRequest1);
			DeleteIORequest((struct IORequest*) sAHIRequest1);
			sAHIRequest1 = NULL;
		}

		if (sAHIPort != NULL) {
			DeleteMsgPort(sAHIPort);
			sAHIPort = NULL;
		}


		debug(GS_THIS, "Closed AHI Audio");

		debug_write_str("sRead = ");
		debug_write_int(sRead);
		debug_write_str("\n");
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
		sQueue.pushBack(audioPacket);
		sRead++;
		if (sThread != NULL && sReadySignalBit != 0) {
			Signal(sThread, (1 << (ULONG) sReadySignalBit));
		}
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

#endif

