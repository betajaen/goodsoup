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

#define GS_FILE_NAME "timer"

#include "types_amiga.h"
#include "timer_amiga.h"
#include "../debug.h"

#include <exec/types.h>
#include <exec/ports.h>
#include <devices/timer.h>
#include <clib/exec_protos.h>
#include <clib/alib_protos.h>

struct Library* TimerBase = NULL;

namespace gs
{
	SystemTimer::SystemTimer() :
		_msgPort(NULL), _req(NULL) {
	}

	SystemTimer::~SystemTimer() {
	}

	bool SystemTimer::open() {

		if (_msgPort) {
			close();
		}

		_msgPort = CreatePort(NULL, 0);
		if (_msgPort == NULL) {
			error(GS_THIS, "Could not open message port");
			return false;
		}

		_req = (struct timerequest*) CreateExtIO(_msgPort, sizeof(struct timerequest));

		if (_req == NULL) {
			DeletePort(_msgPort);
			_msgPort = NULL;
			error(GS_THIS, "Could not create timer request");
			return false;
		}

		if (OpenDevice(TIMERNAME, UNIT_MICROHZ, (struct IORequest*)_req, 0) != 0) {
			DeleteExtIO((struct IORequest*) _req);
			_req = NULL;
			DeletePort(_msgPort);
			_msgPort = NULL;
			return false;
		}

		TimerBase = (struct Library*) _req->tr_node.io_Device;

		return true;

	}

	void SystemTimer::close() {

		if (_req != NULL) {

			AbortIO((struct IORequest*) _req);
			WaitIO((struct IORequest*) _req);

			CloseDevice((struct IORequest*) _req);
			DeleteExtIO((struct IORequest*) _req);
			_req = NULL;
		}

		if (_msgPort != NULL) {
			DeletePort(_msgPort);
			_msgPort = NULL;
		}
		
	}

	uint32 SystemTimer::start(uint32 microSeconds) {

		_req->tr_time.tv_secs = 0;
		_req->tr_time.tv_micro = microSeconds;
		_req->tr_node.io_Command = TR_ADDREQUEST;
		SendIO(&_req->tr_node);

		return 1 << _msgPort->mp_SigBit;
	}
	
	bool SystemTimer::isReady() {
		WaitPort(_msgPort);
		GetMsg(_msgPort);

		return true;
	}
	
	uint32 SystemTimer::getSignalBit() const {
		if (_msgPort != NULL) {
			return 1 << _msgPort->mp_SigBit;
		}
		else {
			return 0;
		}
	}

}
