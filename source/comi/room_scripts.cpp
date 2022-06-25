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

#define GS_FILE_NAME "room_scripts"

#include "room.h"
#include "disk.h"
#include "debug.h"

using namespace common;

namespace comi
{
	RoomScriptData::RoomScriptData() {
		numScripts = 0;
	}

	RoomScriptData::~RoomScriptData() {
		close();
	}

	void RoomScriptData::close() {
		numScripts = 0;
		scriptInfo.release();
		scriptData.release();
	}
	
	bool RoomScriptData::readFromDisk(DiskReader& reader, const TagPair& lflf, uint16 debug_roomNum) {
		
		reader.seek(lflf);

		// Discover number of scripts and total length in bytes
		numScripts = 0;
		uint32 scriptTotalLength = 0;

		while (reader.pos() < lflf.end()) {
			TagPair pair = reader.readTagPair();

			if (pair.isTag(GS_MAKE_ID('R','M','S','C'))) {
				while(reader.pos() < pair.end()) {
					TagPair roomPair = reader.readTagPair();

					if (roomPair.isTag(
						GS_MAKE_ID('E','N','C','D'),
						GS_MAKE_ID('E','X','C','D'),
						GS_MAKE_ID('L','S','C','R')
					)) {
						numScripts++;
						scriptTotalLength += roomPair.length;
					}
			
					reader.skip(roomPair);
				}

				continue;
			}

			if (pair.isTag(GS_MAKE_ID('S','C','R','P'))) {
				numScripts++;
				scriptTotalLength += pair.length;
				
				reader.skip(pair);
				continue;
			}

			reader.skip(pair);
		}

		if (numScripts > MAX_ROOM_SCRIPTS) {
			error(COMI_THIS, "Maximum Number (%ld) of supported scripts (%ld) for this Room (%ld) has been exceeded!", (uint32) MAX_ROOM_SCRIPTS, (uint32) numScripts, (uint32) debug_roomNum);
			return false;
		}

		// Read Script Info and opcodes into info and data.
		scriptInfo.setSize(numScripts, 0);
		scriptData.setSize(scriptTotalLength, 0);
		uint8 scriptIdx = 0;
		uint32 scriptOffset = 0;

		reader.seek(lflf);

		while (reader.pos() < lflf.end()) {
			TagPair pair = reader.readTagPair();

			if (pair.isTag(GS_MAKE_ID('R','M','S','C'))) {
				while(reader.pos() < pair.end()) {
					TagPair roomPair = reader.readTagPair();

					if (roomPair.isTag(
						GS_MAKE_ID('E','N','C','D'),
						GS_MAKE_ID('E','X','C','D'),
						GS_MAKE_ID('L','S','C','R')
					)) {
						RoomScriptInfo& info = scriptInfo.get_unchecked(scriptIdx);
						info.fileOffset = reader.pos();
						info.length = roomPair.length;
						info.scriptOffset = scriptOffset;
						
						if (roomPair.isTag(GS_MAKE_ID('E', 'N', 'C', 'D'))) {
							info.kind = RSK_Entrance;
							info.num = 0xFFFF;
						}
						else if (roomPair.isTag(GS_MAKE_ID('E', 'X', 'C', 'D'))) {
							info.kind = RSK_Exit;
							info.num = 0xFFFF;
						}
						else {

							info.length -= sizeof(uint32);
							info.kind = RSK_LocalScript;
							info.num = reader.readUInt32LE();
						}

						ReadWriteSpan<byte, uint16> span = scriptData.getReadWriteSpan<uint16>(scriptOffset, info.length);
						reader.readBytes(span);

						debug(COMI_THIS, "%s %ld %ld %ld %ld", roomPair.tagStr(), (uint32) scriptIdx, (uint32) (info.num), (uint32) scriptOffset, (uint32) roomPair.length);

						scriptIdx++;
						scriptOffset += info.length;

						continue;
					}
			
					reader.skip(roomPair);
				}

				continue;
			}

			if (pair.isTag(GS_MAKE_ID('S','C','R','P'))) {
				
				RoomScriptInfo& info = scriptInfo.get_unchecked(scriptIdx);
				info.fileOffset = reader.pos();
				info.length = pair.length;
				info.scriptOffset = scriptOffset;
				info.num = 0xFFFF;
				info.kind = RSK_Script;

				ReadWriteSpan<byte, uint16> span = scriptData.getReadWriteSpan<uint16>(scriptOffset, pair.length);
				reader.readBytes(span);
				
				debug(COMI_THIS, "%s %ld %ld", pair.tagStr(), (uint32) scriptIdx, (uint32) scriptOffset, (uint32) pair.length);

				scriptIdx++;
				scriptOffset += pair.length;

				continue;
			}
			reader.skip(pair);
		}

		return true;
	}
	
	bool RoomScriptData::getFirstScript(RoomScriptKind kind, ReadSpan<byte, uint16>& out_Script) const {
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

	bool RoomScriptData::getScript(RoomScriptKind kind, uint32 fileOffset, ReadSpan<byte, uint16>& out_Script) const {
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

	bool RoomScriptData::getLocalNumberedScript(uint16 num, ReadSpan<byte, uint16>& out_Script) const {
		for (uint8 i = 0; i < numScripts; i++) {
			const RoomScriptInfo& info = scriptInfo.get_unchecked(i);
			if (info.kind == RSK_LocalScript && info.num == num) {
				out_Script = scriptData.getReadSpan(info.scriptOffset, info.length);
				return true;
			}
		}

		error(COMI_THIS, "Could not find room script number %ld in Room!", (uint32) num);
		abort_quit_stop();

		return false;
	}
}
