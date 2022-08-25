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
#include "../containers.h"
#include "../profile.h"
#include "../audio.h"
#include <SDL2/SDL.h>


#define gs_min(X,Y) ((X) < (Y) ? (X) : (Y))


namespace gs
{
	SDL_AudioDeviceID sAudioDevice;

	bool openAudio() {

		SDL_AudioSpec want, have;

		SDL_memset(&want, 0, sizeof(want)); /* or SDL_zero(want) */
		want.freq = GS_AUDIO_FREQUENCY_HZ;
		want.format = AUDIO_S16MSB;
		want.channels = 2;
		want.samples = 1024;
		want.callback =  NULL;

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
				return false;
			}

			if (want.freq != have.freq) {
				error(GS_THIS, "Incompatible requested Audio frequency!");
				abort_quit_stop();
				return false;
			}

			if (want.samples != have.samples) {
				error(GS_THIS, "Incompatible requested Audio samples per second!");
				abort_quit_stop();
				return false;
			}

			break;
		}

		SDL_PauseAudioDevice(sAudioDevice, 0);

		return true;
	}

	void closeAudio() {
		SDL_CloseAudioDevice(sAudioDevice);
	}

	void pauseAudio(uint8 isPaused) {
		SDL_PauseAudioDevice(sAudioDevice, isPaused);
	}

	AudioPacket* allocateAudioPacket(uint32 length_bytes) {
		// No AudioPools for now
		AudioPacket* audioPacket = (AudioPacket*) allocateMemory(1, sizeof(AudioPacket), 0, GS_COMMENT_FILE_LINE);
		audioPacket->next = NULL;
		audioPacket->length_bytes = length_bytes;
		audioPacket->data = allocateMemory(1, length_bytes, 0, GS_COMMENT_FILE_LINE);
		return audioPacket;
	}

	void submitAudioPacket(AudioPacket* audioPacket) {
		SDL_QueueAudio(sAudioDevice, audioPacket->data, audioPacket->length_bytes);
		releaseAudioPacket(audioPacket);
	}

	void releaseAudioPacket(AudioPacket* audioPacket) {
		if (audioPacket) {
			if (audioPacket->data) {
				releaseMemory(audioPacket->data);
			}
			releaseMemory(audioPacket);
		}
	}
}




