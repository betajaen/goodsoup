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

#define GS_FILE_NAME "script"

#include "script.h"
#include "resource.h"

#include "index.h"
#include "disk.h"
#include "debug.h"
#include "profile.h"

namespace gs
{

	ScriptState* SCRIPTS = NULL;

	ScriptState::ScriptState() {

	}

	ScriptState::~ScriptState() {

	}

	void ScriptState::release() {

		for (uint16 i = 0; i < _globals.getSize(); i++) {
			ScriptData* script = _globals.get_unchecked(i);
			script->poolRelease();
		}

		_globals.clear();

		for (uint16 i = 0; i < _locals.getSize(); i++) {
			ScriptData* script = _locals.get_unchecked(i);
			script->poolRelease();
		}
		
		_locals.clear();
		
		for (uint16 i = 0; i < _objectVerbs.getSize(); i++) {
			ScriptData* script = _objectVerbs.get_unchecked(i);
			script->poolRelease();
		}

		_objectVerbs.clear();
	}

	ScriptData* ScriptState::_newGlobal(uint16 scriptNum) {

		uint8 script_roomNum;
		uint32 script_offset;

		if (INDEX->getScript(scriptNum, script_roomNum, script_offset) == false) {
			return NULL;
		}

		uint8 room_diskNum;
		uint32 room_resOffset;

		if (INDEX->getRoom(script_roomNum, room_diskNum, room_resOffset) == false) {
			return NULL;
		}

		uint32 room_offset;
		Disk& disk = RESOURCES->_getDisk(room_diskNum);
		disk.getRoomOffset(script_roomNum, room_offset);

		ScriptData* script = _globals.acquire();
		script->_fileOffset = room_offset + script_offset;
		script->_flags = 0;
		script->_kind = SDK_Global;
		script->_id = scriptNum;
		script->_parentId = script_roomNum;
		script->_users = 0;
		
		DiskReader reader = disk.readSection(script->_fileOffset);

		TagPair tag = reader.readTagPair();

		if (tag.isTag(GS_MAKE_ID('S', 'C', 'R', 'P')) == false) {
			error(GS_THIS, "No Script Header found for Global Script %ld", (uint32) script->_id);
			_globals.release(script);
			abort_quit_stop();
			return NULL;
		}

		if (tag.length > 65535) {
			error(GS_THIS, "No Script Length (%ld) is to large for for Global Script %ld", tag.length, (uint32) script->_id);
			_globals.release(script);
			abort_quit_stop();
			return NULL;
		}

		if (tag.length == 0) {
			error(GS_THIS, "No Script Length is 0 for for Global Script %ld", (uint32) script->_id);
			_globals.release(script);
			abort_quit_stop();
			return NULL;
		}

		reader.readBytes(script->_script, (uint16) tag.length);

		debug(GS_THIS, "+SCRP %ld, %ld", (uint32) script->_id, (uint32) tag.length);

		return script;
	}
	
	void ScriptData::poolRelease() {
		_script.release();
		_fileOffset = 0;
		_flags = 0;
		_kind = SDK_None;
		_id = 0;
		_parentId = 0;
		_users = 0;
		_numOffsets = 0;
	}

	ScriptDataReference ScriptState::getOrLoadGlobalScript(uint16 scriptNum) {
		
		ScriptData* script;

		for (uint16 i = 0; i < _globals.getSize(); i++) {
			script = _globals.get_unchecked(i);
			if (script->_id == scriptNum) {
				return ScriptDataReference(script);
			}
		}

		script = _newGlobal(scriptNum);

		return ScriptDataReference(script);
	}

	ScriptDataReference ScriptState::getLocalScript(uint16 roomNum, uint32 localScriptNum) {

		for(uint16 i=0;i < _locals.getSize();i++) {
			ScriptData* data = _locals.get_unchecked(i);
			if (data->_parentId == roomNum && data->_id == localScriptNum) {
				return ScriptDataReference(data);
			}
		}

		return ScriptDataReference();
	}

	ScriptDataReference ScriptState::readLocalScript(uint16 roomNum, const TagPair& tag, DiskReader& reader) {

		ScriptData* script = _locals.acquire();
		script->_id = 0;
		script->_parentId = roomNum;
		script->_fileOffset = tag.dataPos;
		script->_kind = SDK_Local;

		uint16 length = tag.length;

		if (tag.isTag(GS_MAKE_ID('L','S', 'C', 'R'))) {
			// Not an EXCD or ENCD, its a LSCR, so the first four bytes is the ID (which always starts at 2000)
			script->_id = reader.readUInt32LE();
			length -= sizeof(uint32);
		}
		else if (tag.isTag(GS_MAKE_ID('E','N', 'C', 'D'))) {
			script->_id = HSN_RoomEntrance;
		}
		else if (tag.isTag(GS_MAKE_ID('E','X', 'C', 'D'))) {
			script->_id = HSN_RoomExit;
		}
		else {
			error(GS_THIS, "Unknown Local Script type %s", tag.tagStr());
			abort_quit_stop();
			return ScriptDataReference();
		}

		reader.readBytes(script->_script, length);

		debug(GS_THIS, "+ %s %ld", tag.tagStr(), length);

		return ScriptDataReference(script);
	}

	bool ScriptState::readObjectVerbScript(uint16 objectNum, const TagPair& tag, DiskReader& reader) {

		if (tag.isTag(GS_MAKE_ID('V','E', 'R', 'B')) == false) {
			error(GS_THIS, "Unexpected tag %ls expected VERB", tag.tagStr());
			abort_quit_stop();
			return false;
		}

		ScriptData* script = _objectVerbs.acquire();
		script->_id = objectNum;
		script->_parentId = 0;
		script->_fileOffset = tag.dataPos;
		script->_kind = SDK_Verb;

		uint16 length = tag.length;

		while(true) {
			byte verbKey = reader.readByte();
			length -= sizeof(byte);

			if (verbKey == 0)
				break;

			uint16 verbOffset = reader.readUInt16LE();
			length -= sizeof(uint16);

			script->_offsetkeys[script->_numOffsets] = verbKey;
			script->_offsetValues[script->_numOffsets] = verbOffset;
			script->_numOffsets++;
		}

		reader.readBytes(script->_script, length);

		debug(GS_THIS, "+VERB %ld %ld %ld", (uint32) objectNum, (uint32) length, (uint32) script->_numOffsets);

		return true;
	}

}
