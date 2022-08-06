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

#ifndef GS_TIMER_H
#define GS_TIMER_H

#include "types.h"

namespace gs
{
    class FixedRateTimer {
    private:

        int32 was;
        int32 rate;
        int32 rate2;
    public:

        int32 diff;

        FixedRateTimer();

        void initialize(int32 rate_msec);

        uint8 check();

    };

	class FixedRateTimer2 {
	private:

		int32 was;
		int32 rate;
		int32 rate2;
	public:

		int32 diff;

		FixedRateTimer2();

		void initialize(int32 rate_msec);

		uint8 check(uint32 now);

	};

}



#endif