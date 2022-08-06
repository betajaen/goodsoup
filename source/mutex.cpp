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

#define GS_FILE_NAME "mutex"

#include "types.h"
#include "mutex.h"

#if defined(GS_AMIGA)
#include <exec/types.h>
#include <exec/semaphores.h>
#include <proto/exec.h>
#else
#include <SDL2/SDL.h>
#endif

namespace gs
{

	Mutex::Mutex() {
#if defined(GS_AMIGA)
	SignalSemaphore *sem = (SignalSemaphore*) AllocVec(sizeof (SignalSemaphore), MEMF_PUBLIC);

	if (sem) {
		InitSemaphore(sem);
    }

	_object = sem;
#endif

#if defined(GS_SDL)
	_object = SDL_CreateMutex();
#endif
	}

	Mutex::~Mutex() {
#if defined(GS_AMIGA)
		FreeMem((APTR) _object, sizeof(SignalSemaphore));
		_object = NULL;
#endif

#if defined(GS_SDL)
		SDL_DestroyMutex((SDL_mutex*) _object);
		_object = NULL;
#endif
	}

	void Mutex::lock() {
#if defined(GS_AMIGA)
		ObtainSemaphore((SignalSemaphore*) _object);
#endif

#if defined(GS_SDL)
		SDL_LockMutex((SDL_mutex*) _object);
#endif
	}

	void Mutex::unlock() {
#if defined(GS_AMIGA)
		ReleaseSemaphore((SignalSemaphore*) _object);
#endif

#if defined(GS_SDL)
		SDL_UnlockMutex((SDL_mutex*) _object);
#endif
	}

}
