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

#ifndef GS_CONFIG_H
#define GS_CONFIG_H

//  -----------------------------------------------------------------
//	You should override these parameters via the makefile script
//  -----------------------------------------------------------------


#ifndef GS_RELEASE
// GS_RELEASE
// Disable all debugging features
// Options:
//	0 - Debug Mode
//	1 - Release Mode
// Option:  RELEASE=0/1
// Default: 0
#define GS_RELEASE 0
#endif

#ifndef GS_CHECKED
// GS_CHECKED
// Check all parameters and extern data before using it. Anything that is abnormal
// is reported, and the game should stop.
// Options:
//	0 - Don't check
//	1 - Check
// Option: CHECKED=0/1
// Default: 1
#define GS_CHECKED 1
#endif


#ifndef GS_MUTE_AUDIO
// GS_MUTE_AUDIO
// Disable Audio processing and playback
// Options:
//	0 - Enable Audio Processing
//	1 - Disable Audio Processing
// Option: MUTE_AUDID=0/1
// Default: 0
#define GS_MUTE_AUDIO 0
#endif





//  -----------------------------------------------------------------
//	Private. Please do not touch.
//  -----------------------------------------------------------------

// GS_AMIGA
// Game is for the Commodore Amiga
// Option: PLATFORM=amiga
#ifndef GS_AMIGA
#if defined(AMIGA) || defined(_AMIGA_) || defined(__AMIGA__)
#define GS_AMIGA
#endif
#endif


// GS_SDL
// Game is for Linux based upon SDL2
// Option: PLATFORM=sdl
#ifndef GS_SDL
#if defined(__linux__)
#define GS_SDL
#endif
#endif


#endif
