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

#ifndef COMMON_EXT_H
#define COMMON_EXT_H

#include "common/types.h"

namespace common
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

}

#endif