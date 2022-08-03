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

#define GS_FILE_NAME "IACT_Audio"

#include "iact_audio.h"
#include "../disk.h"
#include "../audio.h"

#define DISK_CACHE_SIZE_BYTES (256 * 1024)
#define COMPRESSED_SAMPLE_SIZE_BYTES (2 + 4096)

namespace gs
{

	void applyAudio_S16MSB(byte* src) {
		src += 2;

		AudioSample* sample = allocateAudioSample();
		byte* dst = &sample->data[0];
		byte v;
		byte e1 = *src++;
		byte e2 = e1 / 16;
		e1 &= 0x0F;

		int16 v1 = e1;
		int16 v2 = e2;

		uint16 length = 1023;
		do {
			// Left Channel
			v = *src++;
			if (v == 0x80) {
				*dst++ = *src++;
				*dst++ = *src++;
			}
			else
			{
				int16 m = (int8) v;
				m <<= v2;
				*dst++ = m >> 8;
				*dst++ = (byte) m;
			}
			// Right Channel
			v = *src++;
			if (v == 0x80) {
				*dst++ = *src++;
				*dst++ = *src++;
			}
			else
			{
				int16 m = (int8) v;
				m <<= v1;
				*dst++ = m >> 8;
				*dst++ = (byte) m;
			}
		} while(length--);

		pushAudioSample(sample);
	}


	IACTAudio::IACTAudio() {
		diskCache = (byte*) allocateMemory(1, DISK_CACHE_SIZE_BYTES, MF_Clear);
		compressedSample = (byte*) allocateMemory(1, COMPRESSED_SAMPLE_SIZE_BYTES, MF_Clear);
		pos = 0;
	}

	IACTAudio::~IACTAudio() {
		releaseMemoryChecked(compressedSample);
		releaseMemoryChecked(diskCache);
	}

	bool readIACTAudio(DiskReader& reader, TagPair& tag, IACTAudio& audio, AudioMixer* audioMixer) {
		uint32 dataSize = tag.length - 18;

		if (dataSize > DISK_CACHE_SIZE_BYTES) {
			error(GS_THIS, "IACT data %ld is too large to fit in %ld sized buffer!", dataSize, DISK_CACHE_SIZE_BYTES);
			return false;
		}

		byte* src = audio.diskCache;
		byte* dst = audio.compressedSample;
		uint32 pos = audio.pos;

		reader.seek(tag.dataPos + 18);
		reader.readBytes(src, dataSize);

		while(dataSize > 0) {

			if (pos >= 2) {
				int32 len = READ_BE_UINT16(dst) + 2;
				len -= pos;

				if (len > dataSize) {
					//debug(GS_THIS, ">> %ld", dataSize);
					copyMem(dst + pos, src, dataSize);
					pos += dataSize;
					dataSize = 0;
				}
				else {
					//debug(GS_THIS, ">> %ld", len);
					copyMem(dst + pos, src, len);

					applyAudio_S16MSB(dst);

					dataSize -= len;
					src += len;
					pos = 0;
				}
			}
			else {
				if (dataSize > 1 && pos == 0) {
					dst[0] = *src++;
					pos = 1;
					dataSize--;
				}
				dst[pos] = *src++;
				pos++;
				dataSize--;
			}
		}

		audio.pos = pos;
		return true;
	}

}
