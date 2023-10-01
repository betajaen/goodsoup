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

#ifndef __GS_FEATURES_H
#define __GS_FEATURES_H

#if !defined(__AMIGA__)
#error "Only Amiga supported!"
#endif

#include <exec/types.h>

namespace gs {

    namespace features {

        enum class Animation : ULONG {
            None      = 0x0,
            Animated  = 0x1,
            KeyFrames = 0x2,

            Default    = Animated,
            kBitOffset = 0,
            kBitSize   = 2,
            kBitNext   = kBitOffset + kBitSize,
        };

        enum class Subtitles : ULONG {
            None      = 0x0,
            Overlay   = 0x1,
            Baked     = 0x2,

            Default    = Overlay,
            kBitOffset = static_cast<ULONG>(Animation::kBitNext),
            kBitSize   = 2,
            kBitNext   = kBitOffset + kBitSize
        };

        enum class Picture : ULONG  {
            Chunky = 0x0,
            Planar = 0x1,

            Default    = Chunky,
            kBitOffset = static_cast<ULONG>(Subtitles::kBitNext),
            kBitSize   = 1,
            kBitNext   = kBitOffset + kBitSize
        };

        enum class AudioFlags : ULONG  {
            Speech        = 0x1,
            SoundEffects  = 0x2,
            Music         = 0x4,

            None       = 0,
            Default    = Speech | SoundEffects | Music,
            kBitOffset = static_cast<ULONG>(Picture::kBitNext),
            kBitSize   = 3,
            kBitNext   = kBitOffset + kBitSize
        };

        enum class Endian : ULONG  {
            Big         = 0x0,
            Little      = 0x1,

            Default    = Big,
            kBitOffset = static_cast<ULONG>(AudioFlags::kBitNext),
            kBitSize   = 1,
            kBitNext   = kBitOffset + kBitSize
        };


        enum class Arrays : ULONG  {
            False      = 0x0,
            True       = 0x1,

            Default    = True,
            kBitOffset = static_cast<ULONG>(Endian::kBitNext),
            kBitSize   = 1,
            kBitNext   = kBitOffset + kBitSize
        };

        enum class Scripts : ULONG  {
            False      = 0x0,
            True       = 0x1,

            Default    = True,
            kBitOffset = static_cast<ULONG>(Arrays::kBitNext),
            kBitSize   = 1,
            kBitNext   = kBitOffset + kBitSize
        };

        enum class Objects : ULONG  {
            False      = 0x0,
            True       = 0x1,

            Default    = True,
            kBitOffset = static_cast<ULONG>(Scripts::kBitNext),
            kBitSize   = 1,
            kBitNext   = kBitOffset + kBitSize
        };

        enum class Actors : ULONG  {
            False      = 0x0,
            True       = 0x1,

            Default    = True,
            kBitOffset = static_cast<ULONG>(Objects::kBitNext),
            kBitSize   = 1,
            kBitNext   = kBitOffset + kBitSize
        };

        enum class Rooms : ULONG  {
            False      = 0x0,
            True       = 0x1,

            Default    = True,
            kBitOffset = static_cast<ULONG>(Actors::kBitNext),
            kBitSize   = 1,
            kBitNext   = kBitOffset + kBitSize
        };

        static_assert(static_cast<ULONG>(Rooms::kBitNext) < 32, "To many features!");
    }


}

#endif