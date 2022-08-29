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

#ifndef GS_VM_CONTEXT_H
#define GS_VM_CONTEXT_H

#include "forward.h"
#include "debug.h"
#include "profile.h"
#include "script.h"
#include "stack.h"

namespace gs
{

	enum ObjectWhere
	{
		OW_Unknown = 0,
		OW_NotFound = 1,
		OW_Inventory = 2,
		OW_Room = 3,
		OW_Global = 4,
		OW_Local = 5,
		OW_FLObject = 6,
		OW_ObjectVerb = 7
	};

	enum ScriptContextState
	{
		SCS_Dead = 0,
		SCS_Paused = 1,
		SCS_Running = 2,
		SCS_Frozen = 0x80
	};

	struct VmContext
	{
		void _reset();

		inline void _markDead() {
			_scriptNum = 0;
			_scriptWhere = OW_NotFound;
			_state = SCS_Dead;
		}

		inline bool _isFrozen() const {
			return _freezeCount > 0;
		}

		inline bool _isDead() const {
			return _state == 0;
		}

		inline void _freeze() {
			_freezeCount++;
			if (_freezeCount) {
				_state |= SCS_Frozen;
			}
		}

		inline void _unfreeze() {
			if (_freezeCount) {
				_freezeCount--;
				if (_freezeCount == 0) {
					_state &= ~SCS_Frozen;
				}
			}
		}

		inline void _unfreezeAll() {
			_freezeCount = 0;
			_state &= ~SCS_Frozen;
		}

		bool _getScriptData();
		void _forgetScriptData();

		void run();
		void _step();

		byte _readByte();
		int32  _readWord();
		uint32  _readUnsignedWord();
		int32  _readSignedWord();
		void _readString();
		void _readStringLength(uint16& from, uint16& length);
		void _decodeParseString(uint8 m, uint8 n);
		void _readBytesForArray();
		void _actorSay(uint16 actorNum, uint16 length, uint16 offset);

		void clearLocals();
		void copyIntoLocals(int32* values, uint8 numValues);

		void setVar(uint32 name, int32 value);

		int32 getVar(uint32 name);

		int32 getLocal_unchecked(uint8 varName) const {
			return _locals[varName];
		}

		void setLocal_unchecked(uint8 varName, int32 value) {
			_locals[varName] = value;
		}

		uint16 _scriptNum;
		uint8  _verb;
		uint8  _indexNum;
		uint32 _pc;
		int32  _delay;
		uint16 _delayFrameCount;
		uint8  _scriptWhere;
		uint8  _state;
		uint8  _freezeCount;
		uint8  _bFreezeResistant;
		uint8  _bRecursive;
		uint8  _bIsExecuted;
		uint8  _cutsceneOverride;
		uint8  _bHasScript;
		OpcodeSpan 			_script;
		ScriptDataReference _scriptReference;
		int32 _locals[NUM_INT_LOCALS];
		static StringBuilder<uint16> sStringTemp;

	};

	class VmContextAllocator {
		VmContext _contexts[MAX_SCRIPT_CONTEXTS + 1];
	public:

		VmContextAllocator();
		~VmContextAllocator();

		void clear();

		VmContext& acquire();

		VmContext& get(uint8 contextIdx, bool& out_hasContext) {
			if (contextIdx >= MAX_SCRIPT_CONTEXTS) {
				out_hasContext = false;
				return _contexts[MAX_SCRIPT_CONTEXTS];
			}
			out_hasContext = true;
			return _contexts[contextIdx];
		}

		VmContext& get_unchecked(uint8 contextIdx) {
			return _contexts[contextIdx];
		}

	};

}

#endif
