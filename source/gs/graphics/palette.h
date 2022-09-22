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

#ifndef GS_PALETTE_H
#define GS_PALETTE_H

#include "shared/forward.h"

typedef enum gs_PaletteType {
	PT_Unknown = 0,
	PT_Chunky_256 = 255
} gs_PaletteType;

// Used for fixed non-colour cycling palettes
typedef struct gs_Palette {
	uint16 parent;
	byte parentCObjectType;
	uint8 paletteNum;
	byte paletteType;
	byte reserved;
	byte palette[256 * 3];
} gs_Palette;

gs_Palette* gs_NewPalette();

void gs_DeletePalette(gs_Palette* palette);

void gs_LoadPalette(gs_Palette* pal, struct gs_File* file, gs_TagPair* tagPair);

void gs_SavePalette(struct gs_File* file, gs_Palette* pal);

#endif
