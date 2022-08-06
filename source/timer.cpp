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

#define GS_FILE_NAME "timer"

#include "timer.h"

namespace gs
{
    int32 getMSec();

    FixedRateTimer::FixedRateTimer() {
        was = 0;
        rate = 0;
        rate2 = 0;
    }

    void FixedRateTimer::initialize(int rate_msec) {
        was = getMSec();
        rate = rate_msec;
        rate2 = rate+rate;
    }

    uint8 FixedRateTimer::check() {
        int32 now = getMSec();
        int32 delta = now - was;

        this->was += -delta;
        this->diff = delta;

        if (delta >= rate) {
            was = now;

            if (delta >= rate2)
                return 2;

            return 1;
        }
        else {
            return 0;
        }

    }



	FixedRateTimer2::FixedRateTimer2() {
		was = 0;
		rate = 0;
		rate2 = 0;
	}

	void FixedRateTimer2::initialize(int rate_msec) {
		was = 0;
		rate = rate_msec;
		rate2 = rate+rate;
	}

	uint8 FixedRateTimer2::check(uint32 now) {
		int32 delta = now - was;

		this->was += -delta;
		this->diff = delta;

		if (delta >= rate) {
			was = now;

			if (delta >= rate2)
				return 2;

			return 1;
		}
		else {
			return 0;
		}

	}

}