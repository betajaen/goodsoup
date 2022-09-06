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

#define GS_FILE "events"

#include "shared/forward.h"
#include "shared/error.h"

#if defined(GS_AMIGA)

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/intuition.h>

extern struct Screen* gs_Screen;
extern struct ScreenBuffer* gs_ScreenBuffer;
extern struct Window* gs_Window;
extern struct RastPort gs_RastPort;

void gs_Listen() {

	gs_debug_str("Starting to listen.");

	Delay(100);
}

#endif
