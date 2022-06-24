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

#ifndef COMI_ROOM_H
#define COMI_ROOM_H

#include "common/types.h"
#include "common/array.h"
#include "common/buffer.h"
#include "resource_data.h"
#include "common/span.h"
#include "disk.h"

using namespace common;

namespace comi
{

#define MAX_ROOM_PALETTES 8
#define MAX_ROOM_SCRIPTS 24
#define MAX_ROOM_COLOUR_CYCLES 8

	class DiskReader;

	struct RoomColourCycle
	{
		uint16 delay;
		uint16 counter;
		uint16 flags;
		uint8  start;
		uint8 end;
	};

	struct RoomPaletteData {
		uint8 palette[3 * 256];
	};

	enum RoomScriptKind {
		RSK_Entrance= 1,	// Entrance Script
		RSK_Exit = 2,	// Exit Script
		RSK_Script = 3,	// Room Script
		RSK_LocalScript = 4
	};
	
	class RoomScriptData {
	public:
		
		struct RoomScriptInfo {
			uint32 fileOffset;
			uint32 scriptOffset;
			uint16 length;
			uint8  num;
			uint8  kind;
		};

		RoomScriptData();
		~RoomScriptData();
		
		void close();

		uint8 numScripts;
		Buffer<RoomScriptInfo, uint8> scriptInfo;
		Buffer<byte, uint32> scriptData;
		
		bool getFirstScript(RoomScriptKind kind, ReadSpan<byte, uint16>& out_Script) const {
			if (scriptData.getSize() > 0) {
				for (uint8 i = 0; i < numScripts; i++) {
					const RoomScriptInfo& info = scriptInfo.get_unchecked(i);
					if (info.kind == kind) {
						out_Script = scriptData.getReadSpan(info.scriptOffset, info.length);
						return true;
					}
				}
			}
			return false;
		}

		bool getScript(RoomScriptKind kind, uint32 fileOffset, ReadSpan<byte, uint16>& out_Script) {
			if (numScripts > 0) {
				for (uint8 i = 0; i < numScripts; i++) {
					const RoomScriptInfo& info = scriptInfo.get_unchecked(i);
					if (info.kind == kind && info.fileOffset == fileOffset) {
						out_Script = scriptData.getReadSpan(info.scriptOffset, info.length);
						return true;
					}
				}
			}
			return false;
		}

		bool readFromDisk(DiskReader& reader, const TagPair& lflf, uint16 debug_roomNum);

	};

	class RoomGraphicsData {
		
		uint16 _width, _height;

		uint32 _paletteOffsets[MAX_ROOM_PALETTES];
		Buffer<RoomPaletteData> _palettes;

		FixedArray<RoomColourCycle, MAX_ROOM_COLOUR_CYCLES, uint8> _paletteCycles;

	public:

		RoomGraphicsData();
		~RoomGraphicsData();

		void open(uint16 width, uint16 height);
		void close();
		
		bool readFromDisk(DiskReader& reader, const TagPair& lflf, uint16 debug_roomNum);

		uint8 getNumPalettes() {
			return _palettes.getSize();
		}

		RoomPaletteData& getPalette(uint8 index) {
			return _palettes.get(index);
		}

	};

	class RoomData : public ResourceData
	{
		bool _readLFLF(DiskReader& reader, TagPair& lflf);
		bool _readRoomData(DiskReader& reader, const TagPair& lflf, bool readProperties, bool readScripts, bool graphics);
		bool _readProperties(DiskReader& reader, const TagPair& lflf);

	public:

		RoomData(uint16 num, uint8 disk, uint8 flags);
		~RoomData();

		bool hasProperties() const {
			return width != 0 && height != 0;
		}

		bool hasScriptData() const {
			return scriptData != NULL;
		}

		bool hasGraphicsData() const {
			return graphicsData != NULL;
		}

		bool getFirstScript(RoomScriptKind kind, ReadSpan<byte, uint16>& out_Script) const {
			if (scriptData != NULL) {
				return scriptData->getFirstScript(kind, out_Script);
			}
			return false;
		}

		bool getScript(RoomScriptKind kind, uint32 fileOffset, ReadSpan<byte, uint16>& out_Script) {
			if (scriptData != NULL) {
				return scriptData->getScript(kind, fileOffset, out_Script);
			}
			return false;
		}

		void close(bool properties = true, bool scripts = true, bool graphics = true);

		RoomScriptData* scriptData;
		RoomGraphicsData* graphicsData;

		uint16 width, height, numObjects, numZBuffers;
		
		bool readFromDisk(DiskReader& reader, bool readProperties = true, bool readScripts = true, bool readGraphics = true);
		bool mergeFromDisk(DiskReader& reader, bool readPproperties = true, bool readScripts = true, bool readGraphics = true);

	};

	void startRoom(uint16 roomNum, bool runExitScript = true, bool runEnterScript = true);
	RoomData* getRoom();


}

#endif