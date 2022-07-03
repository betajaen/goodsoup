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

#ifndef GS_SCRIPT_H
#define GS_SCRIPT_H

#include "types.h"
#include "buffer.h"
#include "pool.h"

namespace gs
{
#define MAX_SCRIPT_TABLE_ENTRIES 8
	class DiskReader;

	typedef Buffer<byte, uint16> OpcodeData;
	typedef ReadSpan<byte, uint16> OpcodeSpan;

	enum ScriptDataKind {
		SDK_None = 0,
		SDK_RoomGlobalScript = 1,
		SDK_RoomLocalEntrance= 2,
		SDK_RoomLocalExit = 3,
		SDK_RoomLocalScript = 4,
		SDK_RoomVerbScript = 5
	};

	enum ScriptDataFlags {
		SDF_None = 0,
		SDF_Floating = 1
	};

	struct ScriptDataReference;

	struct ScriptData {
		OpcodeData _script;
		uint32 _fileOffset;
		uint16 _parentId;
		uint32 _id;
		uint8 _kind;
		uint8 _diskNum;
		uint8 _users;
		uint8 _flags;
		uint8 _offsetkeys[MAX_SCRIPT_TABLE_ENTRIES];
		uint16 _offsetValues[MAX_SCRIPT_TABLE_ENTRIES];
		uint8 _offsetCount;

		OpcodeSpan getData() const {
			return _script.getReadSpan<uint16>();
		}

		bool getData(uint8 key, OpcodeSpan& out_span) const {

			if (_offsetCount != 0) {
				for (uint8 i = 0; i < _offsetCount; i++) {
					if (_offsetkeys[i] == key) {
						uint16 offset = _offsetValues[i];

						// Size is unknown, but it has to be within the bounds of the script
						out_span = _script.getReadSpan<uint16>(offset, _script.getSize() - offset);
						return true;
					}
				}

				return false;
			}
			else {
				out_span = _script.getReadSpan<uint16>();
				return true;
			}

		}

		void gcGain() {
			if (_users == 255) {
				warn(GS_THIS, "gcGain is called too many times for Script %ld %ld", (uint32) _id, (uint32) _kind);
				return;
			}

			_users++;
		}

		void gcForget() {
			if (_users == 0) {
				warn(GS_THIS, "gcForget called twice for Script %ld %ld", (uint32) _id, (uint32) _kind);
				return;
			}

			_users--;
		}

		void poolRelease();
	};

	struct ScriptDataReference {
	private:
		ScriptData* _script;
	public:

		ScriptDataReference()
			: _script(NULL) {
		}

		~ScriptDataReference() {
			gcForget();
		}

		explicit ScriptDataReference(ScriptData* other)
			: _script(other)
		{
			if (_script) {
				_script->gcGain();
			}
		}
		
		ScriptDataReference(const ScriptDataReference& other)
			: _script(other._script) {
			if (_script != NULL) {
				_script->gcGain();
			}
		}

		ScriptDataReference(ScriptDataReference& other)
			: _script(other._script) {
			if (_script != NULL) {
				_script->gcGain();
			}
		}

		bool isNull() const {
			return _script == NULL;
		}

		void moveInto(ScriptDataReference& other) {
			gcForget();
			_script = other._script;
			other._script = NULL;
		}

		void copyFrom(const ScriptDataReference& other) {
			gcForget();
			_script = other._script;
			if (_script) {
				_script->gcGain();
			}
		}
		
		ScriptDataReference& operator=(ScriptDataReference& other) {
			copyFrom(other);
			return *this;
		}

		ScriptDataReference& operator=(const ScriptDataReference& other) {
			copyFrom(other);
			return *this;
		}

		OpcodeSpan getData() const {
			if (_script != NULL) {
				return _script->getData();
			}
			return OpcodeSpan();
		}

		bool getData(uint8 key, OpcodeSpan& out_span) const {
			if (_script != NULL) {
				return _script->getData(key, out_span);
			}
			return false;
		}

		uint8 getKind() const {
			if (_script == NULL) {
				return SDK_None;
			}
			else {
				return _script->_kind;
			}
		}
		
		bool matchId(uint32 id) const {
			if (_script == NULL) {
				return false;
			}
			else {
				return _script->_id == id;
			}
		}
		
		bool matchId(uint32 id, uint16 parentId) const {
			if (_script == NULL) {
				return false;
			}
			else {
				return _script->_id == id && _script->_parentId == parentId;
			}
		}

		bool matchIdKind(uint32 id, uint8 kind) const {
			if (_script == NULL) {
				return false;
			}
			else {
				return _script->_id == id && _script->_kind == kind;
			}
		}

		bool matchIdKind(uint32 id, uint16 parentId, uint8 kind) const {
			if (_script == NULL) {
				return false;
			}
			else {
				return _script->_id == id && _script->_parentId == parentId && _script->_kind == kind;
			}
		}

		void gcForget() {
			if (_script != NULL) {
				_script->gcForget();
				_script = NULL;
			}
		}


	};

	class ScriptState {
		ArrayPool<ScriptData, uint16> _globals;
		ArrayPool<ScriptData, uint16> _localEntrances;
		ArrayPool<ScriptData, uint16> _localExits;
		ArrayPool<ScriptData, uint16> _locals;
		ArrayPool<ScriptData, uint16> _objectVerbs;

		ScriptData* _newGlobal(uint16 scriptNum);

	public:

		ScriptState();
		~ScriptState();

		void release();

		ScriptDataReference getOrLoadGlobalScript(uint16 scriptNum);

		ScriptDataReference getLocalScript(uint16 roomNum, uint32 localScriptNum);

		ScriptDataReference getEntranceScript(uint16 roomNum);

		ScriptDataReference getExitScript(uint16 roomNum);

		ScriptDataReference getVerbScript(uint16 objectNum);

		ScriptDataReference readLocalScript(uint16 roomNum, uint32 localScriptNum, uint16 scriptLength, DiskReader& reader);

		ScriptDataReference readEntranceScript(uint16 roomNum, uint16 scriptLength, DiskReader& reader);

		ScriptDataReference readExitScript(uint16 roomNum, uint16 scriptLength, DiskReader& reader);

		ScriptDataReference readVerbScript(uint16 objectNum, uint16 verbNum, uint16 scriptLength, DiskReader& reader);

	};

	extern ScriptState* SCRIPTS;

}

#endif