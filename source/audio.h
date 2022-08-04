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

#ifndef GS_AUDIO_H
#define GS_AUDIO_H

#include "types.h"
#include "pool.h"
#include "memory.h"
#include "queue.h"

namespace gs
{
	struct AudioSample {
		AudioSample() {
			next = NULL;
		}

		AudioSample* next;
		uint32 remaining;
		uint32 pos;
		uint8 data[4096];
	};

	class AudioMixer {

		AllocatedPool<AudioSample, uint8> _samplePool;
		Queue<AudioSample> _queue;

	protected:

		friend AudioMixer* newObject<AudioMixer>();
		friend void deleteObject_unchecked<AudioMixer>(AudioMixer*);

		AudioMixer();
		~AudioMixer();

	public:


		AudioSample* allocateAudioSample();
		void addToQueue(AudioSample* sample);

	};

	void openAudio();
	void closeAudio();

	AudioMixer* createAudioMixer();
	void releaseAudioMixer(AudioMixer* mixer);

	AudioSample* allocateAudioSample();
	void pushAudioSample(AudioSample* sample);


}

#endif
