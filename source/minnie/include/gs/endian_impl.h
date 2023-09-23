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

#ifndef __GS_ENDIAN_H
#define __GS_ENDIAN_H

#if !defined(__AMIGA__)
#error "Only Amiga supported!"
#endif

#include <exec/types.h>

namespace gs {

    namespace endian {

        template<typename T>
        inline ULONG swap_2(T value) {
            UBYTE* src = reinterpret_cast<UBYTE*>(&value);
            UBYTE  dst[2];
            dst[0] = src[1];
            dst[1] = src[0];
            return *(reinterpret_cast<T*>(&dst));
        }
        
        template<typename T>
        inline ULONG swap_4(T value) {
            UBYTE* src = reinterpret_cast<UBYTE*>(&value);
            UBYTE  dst[4];
            dst[0] = src[3];
            dst[1] = src[2];
            dst[2] = src[1];
            dst[3] = src[0];
            return *(reinterpret_cast<T*>(&dst));
        }

    }

    inline UWORD to_be16(const UWORD& v) {
        return v;
    };

    inline ULONG to_be32(const ULONG& v) {
        return v;
    };

    inline WORD to_be16(const WORD& v) {
        return v;
    };

    inline LONG to_be32(const LONG& v) {
        return v;
    };

    inline UWORD to_le16(const UWORD& v) {
        return endian::swap_2<UWORD>(v);
    };
    
    inline ULONG to_le32(const ULONG& v) {
        return endian::swap_4<ULONG>(v);
    };

    inline WORD to_le16(const WORD& v) {
        return endian::swap_2<WORD>(v);
    };

    inline LONG to_le32(const LONG& v) {
        return endian::swap_4<LONG>(v);
    };

    inline UWORD from_be16(const UWORD& v) {
        return v;
    };

    inline ULONG from_be32(const ULONG& v) {
        return v;
    };

    inline WORD from_be16(const WORD& v) {
        return v;
    };

    inline LONG from_be32(const LONG& v) {
        return v;
    };

    inline UWORD from_le16(const UWORD& v) {
        return endian::swap_2<UWORD>(v);
    };

    inline ULONG from_le32(const ULONG& v) {
        return endian::swap_4<ULONG>(v);
    };
    
    inline WORD from_le16(const WORD& v) {
        return endian::swap_2<WORD>(v);
    };

    inline LONG from_le32(const LONG& v) {
        return endian::swap_4<LONG>(v);
    };

}

#endif