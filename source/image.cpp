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

#define GS_FILE_NAME "image"

#include "image.h"
#include "memory.h"

namespace gs
{
	ImageState* IMAGES = NULL;


	ImageState::ImageState() {

	}

	ImageState::~ImageState() {
		clear();
	}

	ImageData* ImageState::create(uint16 num) {
		ImageData* image = _pool.acquire();
		image->_num = num;
		_images.push(image);
		return image;
	}

	void ImageState::clear() {
		for(uint16 i=0;i < _images.getSize();i++) {
			ImageData* image = _images.get_unchecked(i);
			image->reset();
			_pool.release_unchecked(image);
		}
	}

	ImageData* ImageState::findFromNum(uint16 num) {
		for(uint16 i=0;i < _images.getSize();i++) {
			ImageData* image = _images.get_unchecked(i);
			if (image->_num == num) {
				return image;
			}
		}

		return NULL;
	}

	void ImageState::destroy(uint16 num) {
		for(uint16 i=0;i < _images.getSize();i++) {
			ImageData* image = _images.get_unchecked(i);
			if (image->_num == num) {
				_images.erase(i);
				_pool.release_unchecked(image);
			}
		}
	}

	void ImageData::reset() {
		if (_bitmap != NULL) {
			releaseBitmap();
		}

		_num = 0;
		_parentNum = 0;
		_width = 0;
		_height = 0;
		_format = 0;
		_bitmap = NULL;
		_diskNum = 0;
		_flags = 0;
		_fileOffset = 0;
	}

	void ImageData::allocateBitmap() {
		if (_bitmap) {
			releaseMemory(_bitmap);
		}

		_size = _width * _height;
		_bitmap = (byte*) allocateMemory(1, _size, 0, GS_COMMENT_FILE_LINE);
	}

	void ImageData::releaseBitmap() {
		if (_bitmap) {
			releaseMemory(_bitmap);
			_bitmap = NULL;
		}
	}

	void ImageData::clear(uint8 colour) {
		for(uint32 i=0;i < _size;i++) {
			_bitmap[i] = colour;
		}
	}

}
