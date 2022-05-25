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

#ifndef COMI_VM_H
#define COMI_VM_H

#include "../goodsoup.h"
#include "../array.h"
#include "resource.h"
#include "consts.h"

namespace comi {

	class Engine;

	class Vm {

	public:
		
		struct ScriptSlot {
			uint32 offs;
			int32 delay;
			uint16 number;
			uint16 delayFrameCount;
			bool freezeResistant, recursive;
			bool didexec;
			byte status;
			byte where;
			byte freezeCount;
			byte cutsceneOverride;
			byte cycle;

			void reset() {
				/* TODO */
			}
		};

		struct NestedScript {
			uint16 number;
			uint8 where;
			uint8 slot;

			void reset() {
				/* TODO */
			}
		};

		struct VmState
		{
			uint32 cutScenePtr[5];
			byte cutSceneScript[5];
			int16 cutSceneData[5];
			int16 cutSceneScriptIndex;
			byte cutSceneStackPointer;
			ScriptSlot slot[NUM_SCRIPT_SLOT];
			int32 localvar[NUM_SCRIPT_SLOT][26];

			NestedScript nest[15];
			byte numNestedScripts;

			void reset() {
				numNestedScripts = 0;
				cutSceneStackPointer = 0;

				for (uint32 i = 0; i < 5; i++) {
					cutScenePtr[i] = 0;
					cutSceneData[i] = 0;
					cutSceneScript[i] = 0;
				}

				for (uint32 i = 0; i < NUM_SCRIPT_SLOT; i++) {
					slot[i].reset();

					for (uint32 j = 0; j < 26; j++) {
						localvar[i][j] = 0;
					}
				}

				for (uint32 i = 0; i < 15; i++) {
					nest[i].reset();
				}
			}
		};

		Vm();
		~Vm();

		Array<int32> vars;
		VmState state;

		void reset() { /* TODO */ }
		void executeOpcode(byte i) { /* TODO */ }

		inline void set(uint32 name, int32 value) {
			vars.set(name, value);
		}

		inline int32 get(uint32 name) const {
			return vars.get(name);
		}

	private:


	};
}

#endif