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

#ifndef __GS_CAPABILITIES_IMPL_H
#define __GS_CAPABILITIES_IMPL_H

#if !defined(__AMIGA__)
#error "Only Amiga supported!"
#endif

#include <exec/types.h>
#include "gs/features.h"

namespace gs {

    namespace features {


        template<typename TEnum>
        ULONG encode(const TEnum enumValue, ULONG existingValue) {
            return (static_cast<ULONG>(enumValue) << static_cast<ULONG>(TEnum::kBitOffset)) | existingValue;
        }

        template<typename TEnum>
        TEnum decode(ULONG enumValue) {
            return static_cast<TEnum>((static_cast<ULONG>(enumValue) >> static_cast<ULONG>(TEnum::kBitOffset)) & ((1 << static_cast<ULONG>(TEnum::kBitSize)) - 1));
        }

        template<typename TEnum>
        bool decode(ULONG enumValue, TEnum wantedValue) {
            return decode<TEnum>(enumValue) == wantedValue;
        }

    }



}

#endif