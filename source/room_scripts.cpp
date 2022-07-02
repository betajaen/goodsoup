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

namespace gs
{
	RoomScriptData::RoomScriptData() {
	}

	RoomScriptData::~RoomScriptData() {
		close();
	}

	void RoomScriptData::close() {

		for (uint16 i = 0; i < _scripts.size(); i++) {
			NewScriptDataReference& script = _scripts.get_unchecked(i);
			script.gcForget();
		}

		_scripts.clear();
	}
	
	bool RoomScriptData::readFromDisk(DiskReader& reader, const TagPair& lflf, uint16 roomNum) {
		

		// Read Script Info and opcodes into info and data.
		reader.seek(lflf);

		while (reader.pos() < lflf.end()) {
			TagPair pair = reader.readTagPair();

			if (pair.isTag(GS_MAKE_ID('R','M','S','C'))) {
				while(reader.pos() < pair.end()) {
					TagPair roomPair = reader.readTagPair();

					if (roomPair.isTag(GS_MAKE_ID('E', 'N', 'C', 'D'))) {
						NewScriptDataReference script =  SCRIPTS->readEntranceScript(roomNum, roomPair.length, reader);
						_scripts.push(script);
						continue;
					}
					else if (roomPair.isTag(GS_MAKE_ID('E', 'X', 'C', 'D'))) {
						NewScriptDataReference script =  SCRIPTS->readExitScript(roomNum, roomPair.length, reader);
						_scripts.push(script);
						continue;
					}
					else if (roomPair.isTag(GS_MAKE_ID('L', 'S', 'C', 'R'))) {
						uint32 num = reader.readUInt32LE();

						NewScriptDataReference script =  SCRIPTS->readLocalScript(roomNum, num, roomPair.length - sizeof(uint32), reader);
						_scripts.push(script);
						continue;
					}

					reader.skip(roomPair);
				}
				

				continue;
			}

			reader.skip(pair);
		}

		return true;
	}
	
	bool RoomScriptData::getFirstScript(uint8 kind, NewScriptDataReference& out_Script) const {
		if (_scripts.size() > 0) {
			for (uint8 i = 0; i < _scripts.size(); i++) {
				const NewScriptDataReference& script = _scripts.get_unchecked(i);
				if (script.getKind() == kind) {
					out_Script.copyFrom(script);
					return true;
				}
			}
		}
		return false;
	}
	
	bool RoomScriptData::hasFirstScript(uint8 kind) const {
		if (_scripts.size() > 0) {
			for (uint8 i = 0; i < _scripts.size(); i++) {
				const NewScriptDataReference& script = _scripts.get_unchecked(i);
				if (script.getKind() == kind) {
					return true;
				}
			}
		}
		return false;
	}

	bool RoomScriptData::getLocalNumberedScript(uint32 num, NewScriptDataReference& out_Script) const {
		
		if (_scripts.size() > 0) {
			for (uint8 i = 0; i < _scripts.size(); i++) {
				const NewScriptDataReference& script = _scripts.get_unchecked(i);
				if (script.matchIdKind(num, SDK_RoomLocalScript)) {
					out_Script.copyFrom(script);
					return true;
				}
			}
		}

		error(GS_THIS, "Could not find room script number %ld in Room!", (uint32) num);
		abort_quit_stop();

		return false;
	}
	
}
