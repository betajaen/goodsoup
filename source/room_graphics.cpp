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

#define GS_FILE_NAME "room_graphics"

#include "room.h"
#include "disk.h"
#include "debug.h"

namespace gs
{
	RoomGraphicsData::RoomGraphicsData() {
		_width = 0;
		_height = 0;
		_numBackgrounds = 0;
	}

	RoomGraphicsData::~RoomGraphicsData() {
		close();
	}

	void RoomGraphicsData::open(uint16 width, uint16 height) {
		_width = width;
		_height =height;
		_numBackgrounds = 0;
	}

	void RoomGraphicsData::close() {
		_width = 0;
		_height = 0;
		if (_numBackgrounds) {
			for (uint8 i = 0; i < _numBackgrounds; i++) {
				Buffer<byte, uint32>& image = _backgrounds[i];
				image.release();
			}
			_numBackgrounds = 0;
		}
	}

	static bool readInsideSMAP(DiskReader& reader, TagPair& tag, FixedArray<uint32, 16, uint8>& chunks, uint8& chunksCount) {
		
		while (reader.pos() < tag.end()) {
			TagPair innerTag = reader.readTagPair();
			
			if (innerTag.isTag(GS_MAKE_ID('Z', 'P', 'L', 'N'))) {
				
				TagPair offsTag;
						
				// OFFS - Offsets.
				if (reader.readAndCompareTag(GS_MAKE_ID('O', 'F', 'F', 'S'), offsTag) == false) {
					error(GS_THIS, "Expected OFFS tag after PALS tag! Got %s", offsTag.tagStr());
					return false;
				}

				if (readInsideSMAP(reader, offsTag, chunks, chunksCount) == false)
					return false;

				continue;
			}
			else if (innerTag.isTag(GS_MAKE_ID('Z', 'P', 'L', 'N'))) {
				chunks[chunksCount++] = innerTag.dataPos;

				reader.skip(innerTag);
			}

			error(GS_THIS, "Unsupported tag %s from", innerTag.tagStr(), tag.tagStr());

			reader.skip(innerTag);
		}

		return true;
	}
	
	bool RoomGraphicsData::readFromDisk(DiskReader& reader, const TagPair& lflf, uint16 debug_roomNum) {
		
		reader.seek(lflf);

		while (reader.pos() < lflf.end()) {

			TagPair roomPair = reader.readTagPair();

			if (roomPair.isTag(GS_MAKE_ID('R', 'O', 'O', 'M'))) {

				while (reader.pos() < roomPair.end()) {

					TagPair tag = reader.readTagPair();
					
					if (tag.isTag(GS_MAKE_ID('P', 'A', 'L', 'S'))) {

						TagPair wrapTag;
						
						if (reader.readAndCompareTag(GS_MAKE_ID('W', 'R', 'A', 'P'), wrapTag) == false) {
							error(GS_THIS, "Expected WRAP tag after PALS tag! Got %s", wrapTag.tagStr());
							abort_quit_stop();
							return false;
						}

						TagPair offsTag;
						
						// OFFS - Offsets.
						if (reader.readAndCompareTag(GS_MAKE_ID('O', 'F', 'F', 'S'), offsTag) == false) {
							error(GS_THIS, "Expected OFFS tag after PALS tag! Got %s", offsTag.tagStr());
							return false;
						}

						uint8 _numPalettes = (uint8) (offsTag.length / sizeof(uint32));

						if (_numPalettes > MAX_ROOM_PALETTES) {
							error(GS_THIS, "Number of Room palettes exceeded!");
							return false;
						}

						for (uint8 i = 0; i < _numPalettes; i++) {
							_paletteOffsets[i] = reader.readUInt32BE();
							debug(GS_THIS, "OFFS(%ld, %ld)", (uint32) 1+ i, (uint32) _numPalettes);
						}
						

						// APAL - Palette(s) data
						TagPair apalTag;
						
						if (reader.readAndCompareTag(GS_MAKE_ID('A', 'P', 'A', 'L'), apalTag) == false) {
							error(GS_THIS, "Expected APAL tag after OFFS tag! Got %s", offsTag.tagStr());
							return false;
						}

						uint32 expectedLen = ((uint32) _numPalettes) * 256 * 3;

						if (apalTag.length != expectedLen) {
							error(GS_THIS, "Expected APAL (%ld) tag length unexpected (%ld)!", expectedLen, apalTag.length);
							abort_quit_stop();
							return false;
						}


						_palettes.setSize(_numPalettes, 0);

						for (uint8 i = 0; i < _numPalettes; i++) {
							RoomPaletteData& paletteData = _palettes.get_unchecked(i);

							reader.readBytes(&paletteData.palette[0], 256 * 3);
							
							debug(GS_THIS, "APAL(%ld, %ld)", (uint32) 1 + i, (uint32) _numPalettes);
						}
						

						continue;
					}

					
					if (tag.isTag(GS_MAKE_ID('C', 'Y', 'C', 'L'))) {

						while (true) {

							uint8 index = reader.readByte();

							if (index == 0)
								break;

							RoomColourCycle& cycle = _paletteCycles[index - 1];
							cycle.counter = 0;
							cycle.delay = 16384 / reader.readUInt16BE();
							cycle.flags = reader.readUInt16BE();
							cycle.start = reader.readByte();
							cycle.end = reader.readByte();

							debug(GS_THIS, "CYCL(%ld)", (uint32) (index - 1));
						}

						continue;

					}
					
					if (tag.isTag(GS_MAKE_ID('I', 'M', 'A', 'G'))) {

						TagPair wrapTag;
						
						if (reader.readAndCompareTag(GS_MAKE_ID('W', 'R', 'A', 'P'), wrapTag) == false) {
							error(GS_THIS, "Expected WRAP tag after IMAG tag! Got %s", wrapTag.tagStr());
							abort_quit_stop();
							return false;
						}

						TagPair offsTag;
						
						// OFFS - Offsets.
						if (reader.readAndCompareTag(GS_MAKE_ID('O', 'F', 'F', 'S'), offsTag) == false) {
							error(GS_THIS, "Expected OFFS tag after IMAG tag! Got %s", offsTag.tagStr());
							return false;
						}

						reader.skip(offsTag);
						
						TagPair smapTag;
						
						// SMAP - Screen? Map.
						if (reader.readAndCompareTag(GS_MAKE_ID('S', 'M', 'A', 'P'), smapTag) == false) {
							error(GS_THIS, "Expected SMAP tag after OFFS tag! Got %s", smapTag.tagStr());
							return false;
						}

						debug(GS_THIS, "In SMAP tag %ld!!", smapTag.length);

						FixedArray<uint32, 16, uint8> chunks;
						uint8 chunksCount = 0;

						readInsideSMAP(reader, smapTag, chunks, chunksCount);


						debug(GS_THIS, "Passed. Num chunks = %ld", (uint32) chunksCount);

						if (chunksCount == 0) {
							_numBackgrounds = 1;
							Buffer<byte, uint32>& background = _backgrounds[0];
						
							uint32 backgroundSize = smapTag.length;

							debug(GS_THIS, "Reading background of size %ld", backgroundSize);
						
						
							background.setSize(backgroundSize, 0);
							ReadWriteSpan<byte, uint32> backgroundData = background.getReadWriteSpan<uint32>();
							
							uint32 tempPos = reader.pos();
							reader.seek(smapTag);
							reader.readBytes(backgroundData);
							reader.seek(tempPos);
						}


						continue;

					}
					
					reader.skip(tag);
				}

				break;
			}


			reader.skip(roomPair);
		}


		return true;
	}

}
