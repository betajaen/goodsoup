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

		
		for (uint16 i = 0; i < _localEntrances.getSize(); i++) {
			ScriptData* script = _localEntrances.get_unchecked(i);
			script->poolRelease();
		}

		_localEntrances.clear();
		
		for (uint16 i = 0; i < _localExits.getSize(); i++) {
			ScriptData* script = _localExits.get_unchecked(i);
			script->poolRelease();
		}

		_localExits.clear();
		
		
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

		debug(GS_THIS, "+SCRIPT Room=%ld:%ld Script=%ld:%ld Total = %ld",
			(uint32)script_roomNum, (uint32)room_offset, (uint32) scriptNum, (uint32)script_offset, (uint32)(room_offset + script_offset));

		ScriptData* script = _globals.acquire();
		script->_diskNum = room_diskNum;
		script->_fileOffset = room_offset + script_offset;
		script->_flags = 0;
		script->_kind = SDK_RoomGlobalScript;
		script->_id = scriptNum;
		script->_parentId = script_roomNum;
		script->_users = 0;
		
		DiskReader reader = disk.readSection(script->_fileOffset);

		debug(GS_THIS, "Offset = %ld", script->_fileOffset);

		TagPair tag = reader.readTagPair();

		debug(GS_THIS, "TAG = %s, %ld", tag.tagStr(), tag.length);

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

		return script;
	}
	
	void ScriptData::poolRelease() {
		_script.release();
		_diskNum = 0;
		_fileOffset = 0;
		_flags = 0;
		_kind = SDK_None;
		_id = 0;
		_parentId = 0;
		_users = 0;
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
		return ScriptDataReference();
	}

	ScriptDataReference ScriptState::getEntranceScript(uint16 roomNum) {
		return ScriptDataReference();
	}

	ScriptDataReference ScriptState::getExitScript(uint16 roomNum) {
		return ScriptDataReference();
	}

	ScriptDataReference ScriptState::getVerbScript(uint16 objectNum) {
		return ScriptDataReference();
	}

	ScriptDataReference ScriptState::readLocalScript(uint16 roomNum, uint32 localScriptNum, uint16 scriptLength, DiskReader& reader) {
		return ScriptDataReference();
	}

	ScriptDataReference ScriptState::readEntranceScript(uint16 roomNum, uint16 scriptLength, DiskReader& reader) {
		return ScriptDataReference();
	}

	ScriptDataReference ScriptState::readExitScript(uint16 roomNum, uint16 scriptLength, DiskReader& reader) {
		return ScriptDataReference();
	}

	ScriptDataReference ScriptState::readVerbScript(uint16 objectNum, uint16 verbNum, uint16 scriptLength, DiskReader& reader) {
		return ScriptDataReference();
	}

}
