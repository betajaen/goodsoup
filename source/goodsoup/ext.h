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

#ifndef GS_EXT_H
#define GS_EXT_H

#include "types.h"

namespace gs
{
	template<typename T>
	inline void swap(T& l, T& r) {
		T t = l;
		l = r;
		r = t;
	}

	template<typename T>
	struct defaultValue {
		static T value();
	};

	template<> struct defaultValue<bool> { 
		static inline bool value() { 
			return false; 
		}
	};
	
	template<> struct defaultValue<int8> { 
		static inline int8 value() { 
			return 0;
		}
	};
	
	template<> struct defaultValue<int16> { 
		static inline int16 value() { 
			return 0;
		}
	};
	
	template<> struct defaultValue<int32> { 
		static inline int32 value() { 
			return 0;
		}
	};
	
	template<> struct defaultValue<uint8> { 
		static inline uint8 value() { 
			return 0;
		}
	};
	
	template<> struct defaultValue<uint16> { 
		static inline uint16 value() { 
			return 0;
		}
	};
	
	template<> struct defaultValue<uint32> { 
		static inline uint32 value() { 
			return 0;
		}
	};

	template<typename T>
	struct defaultValue<T*> {
		static inline T* value() {
			return NULL;
		} 
	};

	template<typename T>
	struct defaultValue<T**> {
		static inline T** value() {
			return NULL;
		} 
	};

	class nocopy {
		public:
			nocopy() {}
			~nocopy() {}
		private:
			nocopy(const nocopy&);
			const nocopy& operator=(const nocopy&);
	};

	inline bool equals(const uint8& lhs, const uint8& rhs) {
		return lhs == rhs;
	}

	inline bool equals(const uint16& lhs, const uint16& rhs) {
		return lhs == rhs;
	}

	inline bool equals(const uint32& lhs, const uint32& rhs) {
		return lhs == rhs;
	}

	inline bool equals(const int8& lhs, const int8& rhs) {
		return lhs == rhs;
	}

	inline bool equals(const int16& lhs, const int16& rhs) {
		return lhs == rhs;
	}

	inline bool equals(const int32& lhs, const int32& rhs) {
		return lhs == rhs;
	}

	inline bool equals(const bool& lhs, const bool& rhs) {
		return lhs == rhs;
	}

	inline bool equals(const char* lhs, const char* rhs) {
		if ((lhs == NULL && rhs == NULL) || (lhs == rhs))
			return true;
		while (true) {
			if (*lhs != *rhs)
				return false;

			if (*lhs == '\0')
				return true;

			lhs++;
			rhs++;
		}
	}

}

#define GS_STATIC_ASSERT(COND, MSG) typedef char gs_assert_##MSG[(!!(COND))*2-1]

#endif