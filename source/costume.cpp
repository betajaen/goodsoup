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

#define GS_FILE_NAME "costume"

#include "costume.h"
#include "memory.h"

namespace gs
{
	CostumeState* COSTUMES = NULL;


	CostumeState::CostumeState() {

	}

	CostumeState::~CostumeState() {
		clear();
	}

	CostumeData* CostumeState::create(uint16 num) {
		CostumeData* costume = _pool.acquire();
		costume->_num = num;
		_costumes.push(costume);
		return costume;
	}

	void CostumeState::clear() {
		for(uint16 i=0;i < _costumes.getSize();i++) {
			CostumeData* costume = _costumes.get_unchecked(i);
			costume->reset();
			_pool.release_unchecked(costume);
		}
	}

	CostumeData* CostumeState::findFromNum(uint16 num) {
		for(uint16 i=0;i < _costumes.getSize();i++) {
			CostumeData* costume = _costumes.get_unchecked(i);
			if (costume->_num == num) {
				return costume;
			}
		}

		return NULL;
	}

	void CostumeState::destroy(uint16 num) {
		for(uint16 i=0;i < _costumes.getSize();i++) {
			CostumeData* costume = _costumes.get_unchecked(i);
			if (costume->_num == num) {
				_costumes.erase(i);
				_pool.release_unchecked(costume);
			}
		}
	}

	void CostumeData::reset() {
		_num = 0;
		_parentNum = 0;
		_diskNum = 0;
		_fileOffset = 0;
	}

}
