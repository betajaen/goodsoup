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

#ifndef GS_FUNCTIONS_H
#define GS_FUNCTIONS_H

#include "types.h"

namespace gs
{
	enum GameStateKind {
		GSK_None = 0,
		GSK_Boot = 1,
		GSK_Quit = 2,
		GSK_Room = 3,
		GSK_Video = 4
	};

	extern uint8 GAME_STATE;
	extern int32 GAME_STATE_PARAM;
	extern uint8 NEXT_GAME_STATE;
	extern int32 NEXT_GAME_STATE_PARAM;
	extern bool SCREEN_EVENT_HANDLER_SHOULD_QUIT;

	inline bool hasGameStateChanged() {
		return NEXT_GAME_STATE != GSK_None && NEXT_GAME_STATE != GAME_STATE;
	}

	inline void setNextGameState(uint8 state, int32 param) {

		if (NEXT_GAME_STATE == GSK_Quit)
			return;

		NEXT_GAME_STATE = state;
		NEXT_GAME_STATE_PARAM = param;
	}

	inline bool isQuitting() {
		return NEXT_GAME_STATE == GSK_Quit;
	}

	void startScene(uint16 roomNum);
	
	void setVar(uint32 varName, int32 value);

	int32 getVar(uint32 varName);

	void togglePause();

	void runOSD();

	void screenEventHandler();

	void frameHandler();


}

#endif