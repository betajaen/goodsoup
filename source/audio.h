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

#include "forward.h"
#include "containers.h"
#include "memory.h"
#include "mutex.h"

namespace gs {

	enum AudioFormat {
		AF_S16MSB = 0
	};

	struct AudioSample_S16MSB {
		AudioSample_S16MSB() {
			next = NULL;
			remaining = 0;
			pos = 0;
			frame = 0;
			data = NULL;
			userMessage = 0;
			userData = NULL;
		}

		uint32 copyInto(int16* buffer, uint32 length);

		bool isEmpty() {
			return remaining == 0;
		}

		AudioSample_S16MSB *next;
		uint16 remaining;
		uint16 pos;
		uint16 frame;
		int16* data;
		uint16 userMessage;
		void*  userData;
	};

	typedef void (*AudioSample_S16MSB_Callback)(void* user, void* userData, uint16 userMessage);

	class AudioStream_S16MSB {

		AllocatedPool<AudioSample_S16MSB, uint8> _samplePool;
		Queue<AudioSample_S16MSB> _queue;
		uint16 _queueSize;
		Mutex _sampleLock;

	protected:

		friend AudioStream_S16MSB *newObject<AudioStream_S16MSB>(uint32);

		friend void deleteObject_unchecked<AudioStream_S16MSB>(AudioStream_S16MSB *);

		AudioStream_S16MSB();

		~AudioStream_S16MSB();

	public:
		AudioStream_S16MSB *next;
		uint32 _time_msec;
		uint32 _nextTime_msec;
		uint32 _timePerSample_msec;
		AudioSample_S16MSB_Callback  callback;
		void* userData;

		AudioSample_S16MSB *allocateSample();

		void pushSample(AudioSample_S16MSB *sample);

		void audioCallback_S16MSB(int16 *samples, uint32 sampleLength);

		uint16 getQueueSize() const {
			return _queueSize;
		}

	};

	void openAudio();

	void closeAudio();

	AudioStream_S16MSB *createAudioStream();

	void releaseAudioStream(AudioStream_S16MSB *audioStream);

	void pushAudioStream(AudioStream_S16MSB *audioStream);

	AudioStream_S16MSB *popAudioStream();

}

#endif
