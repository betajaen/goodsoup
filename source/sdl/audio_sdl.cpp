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
#include "../buffer.h"
#include "../profile.h"
#include "../pool.h"
#include "../audio.h"
#include <SDL2/SDL.h>



namespace gs
{
	SDL_AudioDeviceID sAudioDevice;

	AllocatedPool<AudioSample, uint8> sPool;
	AudioSample* sHeadSample = NULL;
	AudioSample* sTailSample = NULL;
	bool lock = false;


	void audioCallback(void* userdata, uint8* stream, int len)
	{
		uint32 totalLength = 0;
		while(totalLength <= len) {
			lock = true;
			AudioSample* sample = sHeadSample;
			if (sample == NULL) {
				break;
			}

			sHeadSample = sample->next;

			copyMem(stream + totalLength, &sample->data[0], 4096);
			totalLength += 4096;

			sample->next = NULL;
			sPool.release_unchecked(sample);
		}

		if (sHeadSample == NULL) {
			sTailSample = NULL;
		}
		lock = false;
	}

	void openAudio() {

		return;

		sHeadSample = NULL;
		sTailSample = NULL;

		SDL_AudioSpec want, have;

		SDL_memset(&want, 0, sizeof(want)); /* or SDL_zero(want) */
		want.freq = GS_AUDIO_FREQUENCY_HZ;
		want.format = AUDIO_S16MSB;
		want.channels = 2;
		want.samples = GS_AUDIO_SAMPLES_SIZE;
		want.callback =  &audioCallback;

		int count = SDL_GetNumAudioDevices(0);
		for(int i=0;i < count;i++) {
			const char* name = SDL_GetAudioDeviceName(i, 0);

			info(GS_THIS, "Want Audio Device %s for %ldHz Format=%lx Channels=%ld Samples=%ld", name, want.freq, want.format, want.channels, want.samples);

			// sAudioDevice = SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_ANY_CHANGE);
			sAudioDevice = SDL_OpenAudioDevice(
					name,
					0,
					&want,
					&have,
					0);

			if (want.format != have.format) {
				error(GS_THIS, "Incompatible requested Audio format!");
				abort_quit_stop();
				return;
			}

			if (want.freq != have.freq) {
				error(GS_THIS, "Incompatible requested Audio frequency!");
				abort_quit_stop();
				return;
			}

			if (want.samples != have.samples) {
				error(GS_THIS, "Incompatible requested Audio samples per second!");
				abort_quit_stop();
				return;
			}

			break;
		}

		SDL_PauseAudioDevice(sAudioDevice, 0);
	}

	void closeAudio() {

		return;

		SDL_CloseAudioDevice(sAudioDevice);
		sPool.clear();
		sHeadSample = NULL;
		sTailSample = NULL;
	}

	AudioSample* allocateAudioSample() {

		if (lock) {
			while(true) ;
		}

		return sPool.acquire();
	}

	void pushAudioSample(AudioSample* sample) {

		if (lock) {
			while(true) ;
		}

		if (sTailSample == NULL) {
			sHeadSample = sTailSample = sample;
		}
		else {
			sTailSample->next = sample;
			sTailSample = sample;
		}
	}

}




