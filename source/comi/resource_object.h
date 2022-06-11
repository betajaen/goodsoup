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

#ifndef COMI_RESOURCE_OBJECT_H
#define COMI_RESOURCE_OBJECT_H

#include "common/types.h"

namespace comi
{

	class ResourceObject {
	protected:
		uint16  _num;
		uint8   _users;
		uint8   _kind;
		uint8   _flags;
		uint8   _disk;
	public:

		uint16 getNum() const {
			return _num;
		}

		uint16 getResourceUsers() const {
			return _users;
		}

		uint8 getResourceKind() const {
			return _kind;
		}

		uint8 getResourceFlags() const {
			return _flags;
		}

		uint8 getResourceDisk() const {
			return _disk;
		}

		void increaseUse() {
			_users++;
		}

		void decreaseUse() {
			if (_users) {
				_users--;
			}
		}
	};


}

#endif