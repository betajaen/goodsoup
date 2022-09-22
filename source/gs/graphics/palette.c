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

#define GS_FILE "palette"

#include "shared/forward.h"
#include "shared/file.h"
#include "shared/memory.h"
#include "shared/tag.h"

#include "graphics/palette.h"


gs_Palette* gs_NewPalette() {
	gs_Palette* palette = gs_NewCObject(gs_Palette, COT_Palette);
}

void gs_DeletePalette(gs_Palette* palette) {
	gs_DeleteCObject(palette);
}

void gs_LoadPalette(gs_Palette* palette, struct gs_File* file, gs_TagPair* tagPair) {

	palette->parent = gs_ReadUInt16_Native(file);
	palette->parentCObjectType = gs_ReadByte(file);
	palette->paletteType = gs_ReadByte(file);
	
	gs_ReadBytes(file, &palette->palette[0], (3 * 256));	
}

void gs_SavePalette(struct gs_File* file, gs_Palette* palette) {
	
	gs_WriteTagPairKnownSize(file,
		GS_TAG_GSC_PALETTE,
		GS_TAG_BYTE_SIZE * 2 +
		sizeof(uint16) + sizeof(byte) * 2 + (3 * 256)
	);

	gs_WriteTagPairKnownSize(file,
		GS_TAG_GSD_INFO,
		sizeof(uint16) + sizeof(byte) * 2
	);	
	gs_WriteUInt16_Native(file, palette->parent);
	gs_WriteByte(file, palette->parentCObjectType);
	gs_WriteByte(file, palette->paletteType);

	
	gs_WriteTagPairKnownSize(file,
		GS_TAG_GSD_DATA,
		(3 * 256)
	);
	gs_WriteBytes(file, &palette->palette[0], (3 * 256));

}