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

	struct AudioList {

		AudioList() {
			head = NULL;
			tail = NULL;
		}

		~AudioList() {
			head = NULL;
			tail = NULL;
		}

		AudioSample *head, *tail;
		AllocatedPool<AudioSample, uint8> pool;
	};

	AudioList sBuffers[2];
	AudioList* sWrite, *sRead;
	byte sBuffer;
	SDL_atomic_t sBusy;

	void lockBuffers() {
		while (SDL_AtomicCAS(&sBusy, 0, 1) == 0) {
			SDL_Delay(10);
			debug(GS_THIS, "WAIT LOCK");
		}
	}

	void unlockBuffers() {
		while (SDL_AtomicCAS(&sBusy, 1, 0) == 0) {
			SDL_Delay(10);
			debug(GS_THIS, "UNLOCK LOCK");
		}
	}

	void swapBuffers() {
		sBuffer = 1 - sBuffer;
		sWrite = &sBuffers[sBuffer];
		sRead = &sBuffers[1 - sBuffer];
	}

	void audioCallback(void* userdata, uint8* stream, int len)
	{
		SDL_memset(stream, 0, len);

		lockBuffers();
		swapBuffers();
		unlockBuffers();

		AudioList* buffer = sRead;

		uint32 totalLength = 0;
		while(totalLength <= len) {
			AudioSample* sample = buffer->head;
			if (sample == NULL) {
				break;
			}

			uint32 copySize = sample->remaining;
			debug(GS_THIS, "copySize = %ld for %ld", copySize, len);
			if (totalLength + copySize >= len) {
				copySize = (totalLength + copySize) - len;
				debug(GS_THIS, "new copySize = %ld for %ld", copySize, len);
			}

			if (copySize == 0) {
				break;
			}

			copyMem(stream + totalLength, &sample->data[sample->pos], copySize);
			totalLength += copySize;
			sample->remaining -= copySize;
			sample->pos += copySize;

			if (sample->remaining == 0) {
				buffer->head = sample->next;
				sRead->pool.release_unchecked(sample);
				continue;
			}
			else {
				break;
			}
		}

		if (buffer->head == NULL) {
			buffer->tail = NULL;
		}

	}

	void openAudio() {

		sBuffer = 0;
		sWrite = &sBuffers[sBuffer];
		sRead = &sBuffers[1 - sBuffer];

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
		SDL_CloseAudioDevice(sAudioDevice);
		sRead->pool.clear();
		sWrite->pool.clear();
	}

	AudioSample* allocateAudioSample() {
		lockBuffers();
		AudioSample* sample = sWrite->pool.acquire(0xAAAAAAA1);
		unlockBuffers();

		sample->next = NULL;
		sample->remaining = 4096;
		sample->pos = 0;

		return sample;
	}

	void pushAudioSample(AudioSample* sample) {

		lockBuffers();
		if (sWrite->tail == NULL) {
			sWrite->head = sWrite->tail = sample;
		}
		else {
			sWrite->tail->next = sample;
			sWrite->tail = sample;
		}

		unlockBuffers();
	}

}




