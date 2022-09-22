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

#ifndef GS_IMAGE_H
#define GS_IMAGE_H

#include "shared/forward.h"

typedef enum gs_ImageFormat {
	IF_Unknown = 0,
	IF_Chunky_256 = 1
} gs_ImageFormat;

// Used for non-animated graphics, usually room backdrops, etc.
typedef struct gs_Image {
	struct gs_Image* next, *prev;
	uint16 num;
	uint16 parent;
	uint8  parentCObjectType;
	uint8  imageFormat;
	uint16 width_px;
	uint16 height_px;
	struct gs_Palette* palette;
	uint32 imageDataLength_bytes;
	byte*  imageData;
} gs_Image;

gs_Image* gs_AllocateImage();

gs_Image* gs_NewImage();

void gs_DeleteImage(gs_Image* image);

gs_bool gs_AllocateImageData(gs_Image* image);

void gs_DeallocateImageData(gs_Image* image);

void gs_LoadImage(gs_Image* image, struct gs_File* file, gs_TagPair* tagPair);

void gs_SaveImage(struct gs_File* file, gs_Image* image);

#endif
