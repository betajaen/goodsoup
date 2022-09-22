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

#define GS_FILE "image"

#include "shared/forward.h"
#include "shared/file.h"
#include "shared/memory.h"
#include "shared/tag.h"

#include "graphics/image.h"
#include "graphics/palette.h"

gs_Image* gs_NewImage() {
	gs_Image* image = gs_NewCObject(gs_Image, COT_Image);

	return image;
}

void gs_DeleteImage(gs_Image* image) {

	if (image->imageData) {
		gs_DeallocateImageData(image);
	}

	gs_DeleteCObject(image);
}

gs_bool gs_AllocateImageData(gs_Image* image) {
	if (image->imageData != NULL) {
		return TRUE;
	}

	uint32 size = image->width_px * image->height_px;

	if (image->imageData == 0) {
		return FALSE;
	}

	switch (image->imageFormat) {
		default:
			return FALSE;
		case IF_Chunky_256: {
			image->imageDataLength_bytes = size * sizeof(byte);
			image->imageData = gs_Allocate(1, image->imageDataLength_bytes, MF_Clear, GS_COMMENT_FILE_LINE);
		}
		return TRUE;
	}

	return FALSE;
}

void gs_DeallocateImageData(gs_Image* image) {
	if (image->imageData == NULL) {
		return;
	}

	switch (image->imageFormat) {
		default:
			return;
		case IF_Chunky_256: {
			gs_Deallocate(image->imageData);

			image->imageData = NULL;
			image->imageDataLength_bytes = 0;
		}
		return;
	}

	return;
}


void gs_LoadImage(gs_Image* image, struct gs_File* file, gs_TagPair* tagPair) {

	image->num = gs_ReadUInt16_Native(file);
	image->parent = gs_ReadUInt16_Native(file);
	image->parentCObjectType = gs_ReadUInt8(file);
	image->imageFormat = gs_ReadUInt8(file);
	image->width_px = gs_ReadUInt16_Native(file);
	image->height_px = gs_ReadUInt16_Native(file);
	
	if (gs_AllocateImageData(image)) {
		gs_ReadBytes(file, image->imageData, image->imageDataLength_bytes);
	}
	
}

void gs_SaveImage(struct gs_File* file, gs_Image* image) {
	gs_TagPair imgTag, infoTag, dataTag;
	gs_WriteTagPairStart(file, &imgTag, GS_TAG_GSC_IMAGE);

	gs_WriteTagPairStart(file, &infoTag, GS_TAG_GSD_INFO);

	gs_WriteUInt16_Native(file, image->num);
	gs_WriteUInt16_Native(file, image->parent);
	gs_WriteByte(file, image->parentCObjectType);
	gs_WriteByte(file, image->imageFormat);
	gs_WriteUInt16_Native(file, image->width_px);
	gs_WriteUInt16_Native(file, image->height_px);

	gs_WriteTagPairEnd(file, &infoTag);

	if (image->palette) {
		gs_SavePalette(file, image->palette);
	}

	if (image->imageData && image->imageDataLength_bytes) {

		gs_WriteTagPairKnownSize(file, GS_TAG_GSD_DATA, image->imageDataLength_bytes);
		gs_WriteBytes(file, image->imageData, image->imageDataLength_bytes);
	}

	gs_WriteTagPairEnd(file, &imgTag);
}