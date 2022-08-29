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

	 bool CostumeState::_seekToCostume(uint16 costumeNum, DiskReader& out_reader, TagPair& out_pair) {
		return false;
	}

	bool CostumeState::_readIntoCostume(DiskReader &reader, const TagPair &parentTag, CostumeData* costume) {
		return false;
	}

	CostumeData* CostumeState::loadFromNum(uint16 num) {

#if 0
		TagPair tag;
		DiskReader reader; //(ReadFile::NullFile, 0);

		if (_seekToCostume(num, reader, tag) == false) {
			return NULL;
		}
#endif
		CostumeData* costume = _pool.acquire();
		costume->_num = num;

#if 0
		if (_readIntoCostume(reader, tag, costume) == false) {
			_pool.release_unchecked(costume);
			return NULL;
		}
#endif

		if (costume != NULL && _reservedLocks.getSize() > 0) {
			for(uint16 i=0;i < _reservedLocks.getSize();i++) {
				uint16 other = _reservedLocks.get_unchecked(i);

				if (other == num) {
					costume->_bResourceLocked = true;
					_reservedLocks.erase(i);
					break;
				}
			}
		}

		_costumes.push(costume);

		return costume;
	}

	CostumeData* CostumeState::loadFromTag(DiskReader& reader, const TagPair& parentTag) {
		CostumeData* costume = _pool.acquire();
		_readIntoCostume(reader, parentTag, costume);

		if (costume != NULL && _reservedLocks.getSize() > 0) {
			for(uint16 i=0;i < _reservedLocks.getSize();i++) {
				uint16 other = _reservedLocks.get_unchecked(i);

				if (other == costume->_num) {
					costume->_bResourceLocked = true;
					_reservedLocks.erase(i);
					break;
				}
			}
		}

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

	void CostumeState::addResourceLock(uint16 num) {
		for(uint16 i=0;i < _reservedLocks.getSize();i++) {
			uint16 other = _reservedLocks.get_unchecked(i);
			if (other == num)
				return;
		}

		_reservedLocks.push(num);
	}

	void CostumeState::removeResourceLock(uint16 num) {
		for(uint16 i=0;i < _reservedLocks.getSize();i++) {
			uint16 other = _reservedLocks.get_unchecked(i);
			if (other == num) {
				_reservedLocks.erase(i);
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
