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

#include "forward.h"
#include "containers.h"
#include "disk.h"

namespace gs
{
	struct ImageData {
		uint16 _num;
		uint16 _parentNum;
		uint16 _width, _height;
		uint32 _size;
		uint16 _format;
		uint32 _fileOffset;
		uint8  _diskNum;
		uint8  _flags;
		byte*  _bitmap;

		void allocateBitmap();
		void releaseBitmap();
		void clear(uint8 colour);

		void reset();
	};

	class ImageState {

		AllocatedPool<ImageData, uint16> _pool;

		Array<ImageData*> _images;

		public:

			ImageState();
			~ImageState();

			void clear();

			ImageData* findFromNum(uint16 num);

			ImageData* create(uint16 num);
			void destroy(uint16 num);

	};

	extern ImageState* IMAGES;

}

#endif
