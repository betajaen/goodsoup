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
 *
 *
 * openTimer, closeTimer, startTimer is based off the AmigaMapPing code
 * which is distributed under the GNU General Public License version 3.
 * Which can be read here.
 * 
 * https://bitbucket.org/tygre/amigamapping/src/master/GPL%20v3
 * 
 * AmigaMapPing can be found here:
 * 
 * https://bitbucket.org/tygre/amigamapping/src/master/
 * 
 */

#ifndef GS_TIMER_AMIGA_H
#define GS_TIMER_AMIGA_H

#include "types_amiga.h"

struct MsgPort;
struct Device;
struct timerequest;

namespace gs
{
	class SystemTimer {
		
		struct MsgPort* _msgPort;
		struct timerequest* _req;
		uint32 _signalBit;

	public:

		SystemTimer();
		~SystemTimer();

		bool open();
		void close();
		uint32 start(uint32 microSeconds);
		bool isReady();

		uint32 getSignalBit() const;

	};

}

#endif
