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
#include <SDL2/SDL.h>

namespace gs
{
	struct AudioBuffer {

		AudioBuffer() {
			data = NULL;
			length = 0;
			capacity = 0;
		}

		byte* data;
		uint32 length;
		uint32 capacity;
	};

	AudioBuffer sAudioBuffers[2];
	uint8 sWriteBuffer;

	SDL_AudioDeviceID sAudioDevice;

	AudioBuffer* swapAudioBuffers() {
		AudioBuffer* read = &sAudioBuffers[sWriteBuffer];

		sWriteBuffer = 1 - sWriteBuffer;
		AudioBuffer* write = &sAudioBuffers[sWriteBuffer];
		write->length = 0;

		return read;
	}

	void audioCallback(void* userdata, uint8* stream, int len)
	{
		//debug(GS_THIS, "Callback");

		AudioBuffer*  read = swapAudioBuffers();

		uint32 maxCopy = SDL_min(read->length, len);

		//printf("MaxCopy = %ld  Read=%ld,  Want=%ld", maxCopy, read->length, len);

		copyMem(stream, read->data, maxCopy);
		read->length = 0;

	}

	void openAudio() {

		SDL_AudioSpec want, have;

		SDL_memset(&want, 0, sizeof(want)); /* or SDL_zero(want) */
		want.freq = GS_AUDIO_FREQUENCY_HZ;
		want.format = AUDIO_S16MSB;
		want.channels = 2;
		want.samples = GS_AUDIO_SAMPLES_PER_SECOND;
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

			if (sAudioDevice > 0) {
				info(GS_THIS, "Got Audio Device %lx for %ldHz Format=%lx Channels=%ld Samples=%ld", sAudioDevice, have.freq, have.format, have.channels, have.samples);
			}

			break;
		}



		uint32 capacity = have.size;

		info(GS_THIS, "Audio Buffer Size = %ld", capacity);

		sWriteBuffer = 0;
		sAudioBuffers[0].length = 0;
		sAudioBuffers[0].capacity = capacity;
		sAudioBuffers[0].data = (byte*) allocateMemory(1, capacity, MF_Clear);
		sAudioBuffers[1].length = 0;
		sAudioBuffers[1].capacity = capacity;
		sAudioBuffers[1].data = (byte*) allocateMemory(1, capacity, MF_Clear);

		SDL_PauseAudioDevice(sAudioDevice, 0);
	}

	void closeAudio() {
		SDL_CloseAudioDevice(sAudioDevice);

		releaseMemory(sAudioBuffers[1].data);
		releaseMemory(sAudioBuffers[0].data);
	}

	void audioPush16(const void* data, uint32 length) {
		AudioBuffer* write = &sAudioBuffers[sWriteBuffer];

		if ((write->length + length) <= write->capacity) {
			copyMem(write->data + write->length, (void*) data, length);
			write->length += length;
		}
	}

}




