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
#include "globals.h"

#define gs_min(X,Y) ((X) < (Y) ? (X) : (Y))

namespace gs
{

	InlineArray<AudioStream_S16MSB*, uint16, MAX_AUDIO_MIXERS> sAudioStreams;
    Queue<AudioStream_S16MSB> sAudioStack;
    bool locked = false;

    AudioStream_S16MSB::AudioStream_S16MSB() {
        next = NULL;
		callback = NULL;
		userData = NULL;
	}

    AudioStream_S16MSB::~AudioStream_S16MSB() {
		AudioSample_S16MSB* sample = NULL;
		while((sample = _queue.pullFront()) != NULL) {

			if (callback) {
				callback(userData, sample->userData, sample->userMessage);
			}

			_samplePool.release(sample);
		}
	}

	AudioSample_S16MSB* AudioStream_S16MSB::allocateSample() {

        AudioSample_S16MSB* sample;

		_sampleLock.lock();
        if (_queueSize > 128) {
            warn(GS_THIS, "Large AudioSample Queue!");
            sample = _queue.pullBack();
        }
        else {
            sample = _samplePool.acquire(GS_COMMENT_FILE_LINE);
        }
		_sampleLock.unlock();

        sample->remaining = 2048;
        sample->pos = 0;
		sample->frame = 0;
        sample->next = NULL;
		sample->userMessage = 0;
		sample->userData = NULL;

        return sample;
	}

	void AudioStream_S16MSB::pushSample(AudioSample_S16MSB *sample) {
        _sampleLock.lock();
        _queueSize++;
		_queue.pushBack(sample);
        //debug(GS_THIS, "Queue Size is greater %ld", _queueSize);
		_sampleLock.unlock();
	}

    void AudioStream_S16MSB::audioCallback_S16MSB(int16* samples, uint32 sampleLength) {

        //debug(GS_THIS, "Samples Begin %ld", sampleLength);

        _sampleLock.lock();

        uint32 pos = 0;
        uint32 remaining = sampleLength;

		_time_msec = _nextTime_msec;

        while(pos < sampleLength && _queue.hasAny()) {
            AudioSample_S16MSB* sample = _queue.peekFront();


            uint32 amountCopied = sample->copyInto(samples + pos, remaining);
            pos += amountCopied;
            remaining -= amountCopied;

            if (sample->isEmpty()) {
				_nextTime_msec += _timePerSample_msec; /* TODO: Account for partial samples */
                _queue.pullFront();

				if (callback) {
					callback(userData, sample->userData, sample->userMessage);
				}

                _samplePool.release_unchecked(sample);
                _queueSize--;
                // debug(GS_THIS, "Queue Size is lesser %ld", _queueSize);
            }

        }

        _sampleLock.unlock();
    }

    uint32 AudioSample_S16MSB::copyInto(int16* buffer, uint32 length) {
        uint32 toCopy = gs_min(length, remaining);
        copyMem(buffer, &data[pos], remaining * sizeof(int16));
        pos += toCopy;
        remaining -= toCopy;
        return toCopy;
    }

    AudioStream_S16MSB* createAudioStream() {
		CHECK_IF_RETURN(sAudioStreams.isFull(), NULL, "Cannot allocate Audio Mixer! None available.");

        AudioStream_S16MSB* audioStream = newObject<AudioStream_S16MSB>(GS_COMMENT_FILE_LINE);
		sAudioStreams.push(audioStream);

		return audioStream;
	}

	void releaseAudioStream(AudioStream_S16MSB* audioStream) {
		CHECK_IF(audioStream == NULL, "Tried to release a null AudioStream");
		uint16 index;

		if (sAudioStreams.indexOf(audioStream, index) == false) {
			error(GS_THIS, "Tried to release a Audio Mixer twice!");
			abort_quit_stop();
			return;
		}

		sAudioStreams.erase(index);
		deleteObject_unchecked(audioStream);
	}

    void pushAudioStream(AudioStream_S16MSB* audioStream) {
        sAudioStack.pushFront(audioStream);
    }

    AudioStream_S16MSB* popAudioStream() {
        return sAudioStack.pullFront();
    }

    void audioCallback_S16MSB(int16* samples, uint32 sampleLength) {

		if (PAUSED) {
			return;
		}

        AudioStream_S16MSB* stream = sAudioStack.peekFront();

        if (stream) {
            stream->audioCallback_S16MSB(samples, sampleLength);
        }
    }

}
