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

#include "profile.h"
#include "audio.h"
#include "debug.h"
#include "memory.h"

namespace gs
{

	InlineArray<AudioMixer*, uint8, MAX_AUDIO_MIXERS> sAudioMixers;

	AudioMixer::AudioMixer() {

	}

	AudioMixer::~AudioMixer() {
		AudioSample* sample = NULL;
		while((sample = _queue.pull()) != NULL) {
			_samplePool.release(sample);
		}
	}

	AudioSample* AudioMixer::allocateAudioSample() {
		return _samplePool.acquire();
	}

	void AudioMixer::addToQueue(AudioSample* sample) {
		_queue.push(sample);
	}

	AudioMixer* createAudioMixer() {
		CHECK_IF_RETURN(sAudioMixers.isFull(), NULL, "Cannot allocate Audio Mixer! None available.");

		AudioMixer* mixer = newObject<AudioMixer>();
		sAudioMixers.push(mixer);

		return mixer;
	}

	void releaseAudioMixer(AudioMixer* mixer) {
		CHECK_IF(mixer == NULL, "Tried to release a null AudioMixer");
		uint8 index;

		if (sAudioMixers.indexOf(mixer, index) == false) {
			error(GS_THIS, "Tried to release a Audio Mixer twice!");
			abort_quit_stop();
			return;
		}

		sAudioMixers.erase(index);
		deleteObject_unchecked(mixer);
	}

}
