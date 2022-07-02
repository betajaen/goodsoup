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

#ifndef GS_ROOM_H
#define GS_ROOM_H

#include "types.h"
#include "array.h"
#include "buffer.h"
#include "resource_data.h"
#include "span.h"
#include "disk.h"
#include "profile.h"
#include "debug.h"

namespace gs
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
		RSK_LocalScript = 4,
		RSK_VerbScript = 5
	};
	
	class RoomScriptData {
	public:
		
		struct RoomScriptInfo {
			uint32 fileOffset;
			uint32 scriptOffset;
			uint16 length;
			uint16 num;
			uint8  kind;
		};

		RoomScriptData();
		~RoomScriptData();
		
		void close();

		uint8 numScripts;
		Buffer<RoomScriptInfo, uint8> scriptInfo;
		Buffer<byte, uint32> scriptData;
		
		bool getFirstScript(RoomScriptKind kind, ReadSpan<byte, uint16>& out_Script) const ;
		bool getScript(RoomScriptKind kind, uint32 fileOffset, ReadSpan<byte, uint16>& out_Script) const;
		bool getLocalNumberedScript(uint16 num, ReadSpan<byte, uint16>& out_Script) const;
		bool getObjectNumberedScript(uint16 num, ReadSpan<byte, uint16>& out_Script) const;

		bool readFromDisk(DiskReader& reader, const TagPair& lflf, uint16 debug_roomNum);

	};

	class RoomGraphicsData {
		
		uint16 _width, _height;

		uint32 _paletteOffsets[MAX_ROOM_PALETTES];
		Buffer<RoomPaletteData> _palettes;

		FixedArray<RoomColourCycle, MAX_ROOM_COLOUR_CYCLES, uint8> _paletteCycles;

		Buffer<byte, uint32> _backgrounds[16];
		uint8 _numBackgrounds;

	public:

		RoomGraphicsData();
		~RoomGraphicsData();

		void open(uint16 width, uint16 height);
		void close();
		
		bool readFromDisk(DiskReader& reader, const TagPair& lflf, uint16 debug_roomNum);

		uint8 getNumPalettes() {
			return _palettes.getSize();
		}

		RoomPaletteData* getPalette(uint8 index) {
			return _palettes.ptr(index);
		}

		uint8 getNumBackgrounds() const {
			return _numBackgrounds;
		}

		ReadSpan<byte, uint32> getBackground(uint8 idx) const {
			return _backgrounds[idx].getReadSpan<uint32>();
		}

	};
	
	struct RoomObjectData {
		void release();

		uint16 _num;
		uint8 _parent;
		uint8 _parentState;
		uint8 _flags;
		ReadSpan<byte, uint16> _scriptData;
	};

	class RoomData : public ResourceData
	{
		bool _readLFLF(DiskReader& reader, TagPair& lflf);
		bool _readRoomData(DiskReader& reader, const TagPair& lflf, bool readProperties, bool readScripts, bool readGraphics, bool readObjects);
		bool _readProperties(DiskReader& reader, const TagPair& lflf);
		bool _readObjects(DiskReader& reader, const TagPair& lflf);
		bool _readObject(DiskReader& reader, const TagPair& obcdPair, RoomScriptData* scriptData);

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

		uint8 getNumBackgrounds() const {
			if (graphicsData == NULL)
				return 0;

			return graphicsData->getNumBackgrounds();
		}

		ReadSpan<byte, uint32> getBackground(uint8 idx) const {

			if (graphicsData == NULL) {
				error(GS_THIS, "Cannot get background as GraphicsData was not loaded!");
				return ReadSpan<byte, uint32>();
			}

			return graphicsData->getBackground(idx);
		}

		RoomPaletteData* getPalette(uint8 index) const {
			if (graphicsData == NULL) {
				return NULL;
			}

			return graphicsData->getPalette(index);
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

		bool getLocalNumberedScript(uint16 num, ReadSpan<byte, uint16>& out_Script) {
			if (scriptData != NULL) {
				return scriptData->getLocalNumberedScript(num, out_Script);
			}
			warn(GS_THIS, "RoomScriptData was not loaded for %ld", this->getNum());
			return false;
		}

		void close(bool properties = true, bool scripts = true, bool graphics = true);

		RoomScriptData* scriptData;
		RoomGraphicsData* graphicsData;
		Array<RoomObjectData*> objects;

		uint16 width, height, numObjects, numZBuffers;
		
		bool readFromDisk(DiskReader& reader, bool readProperties = true, bool readScripts = true, bool readGraphics = true, bool readObjects = true);
		bool mergeFromDisk(DiskReader& reader, bool readPproperties = true, bool readScripts = true, bool readGraphics = true, bool readObjects = true);

	};

	void startRoom(uint16 roomNum, bool runExitScript = true, bool runEnterScript = true);
	RoomData* getRoom();


}

#endif