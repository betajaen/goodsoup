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

#if GS_SAN_CODEC47 >= 1

#define GS_FILE_NAME "san_tables"

#include "../types.h"
#include "../file.h"
#include "../memory.h"

namespace gs
{

	int16 SAN47_MOTION_VECTORS[256] = {
		0,-27521,-27514,-26889,-26227,-25616,-24941,-23063,
		-21734,-21122,-21116,-20509,-20489,-19829,-18576,-18528,
		-17902,-16674,-16022,-16001,-15997,-15367,-15352,-14696,
		-14684,-14092,-13427,-12838,-12800,-12187,-12164,-12156,
		-11537,-10888,-10872,-10862,-10852,-10841,-9612,-9588,
		-8981,-8961,-8959,-8361,-8325,-8315,-8299,-7711,
		-7055,-7048,-7032,-7025,-6402,-6399,-6369,-5783,
		-5771,-5765,-5756,-5749,-5718,-5114,-5096,-4498,
		-4487,-4483,-4481,-4478,-4462,-3883,-3853,-3844,
		-3836,-3832,-3233,-3209,-3202,-3200,-3198,-3195,
		-3187,-2585,-2566,-2563,-2557,-2551,-1939,-1927,
		-1924,-1922,-1921,-1920,-1919,-1918,-1916,-1914,
		-1887,-1294,-1290,-1285,-1283,-1282,-1281,-1280,
		-1279,-1278,-1277,-1275,-1273,-1266,-1261,-1255,
		-1237,-647,-643,-642,-641,-640,-639,-638,
		-637,-630,-5,-3,-2,-1,1,2,
		3,5,7,630,633,637,638,639,
		640,641,642,643,1237,1255,1261,1266,
		1275,1277,1278,1279,1280,1281,1282,1283,
		1285,1287,1290,1294,1887,1914,1916,1918,
		1919,1920,1921,1922,1924,1939,2551,2557,
		2563,2567,2585,3187,3195,3198,3200,3202,
		3205,3209,3233,3832,3836,3844,3853,3883,
		4462,4478,4480,4482,4487,4498,5096,5114,
		5718,5749,5756,5765,5771,5783,6369,6399,
		6402,7025,7032,7048,7055,7711,8299,8315,
		8325,8361,8959,8961,8981,9588,9612,10841,
		10852,10862,10872,10888,11537,12156,12160,12164,
		12187,12838,13427,14092,14684,14696,15352,15367,
		15997,16001,16022,16674,17902,18528,18576,19829,
		20489,20509,21116,21122,21734,23063,24941,25616,
		26227,26889,27514,27521,0,0,0,0
	};

	byte* SAN_TABLE_BIG = NULL;
	byte* SAN_TABLE_SMALL = NULL;
	bool isTablesLoaded = false;

	void initSan47Tables() {
		if (isTablesLoaded == false) {
			isTablesLoaded = true;

			uint32 size;
			SAN_TABLE_BIG = readFileIntoMemory(GS_GAME_PATH "SAN47B.GST", size);
			SAN_TABLE_SMALL = readFileIntoMemory(GS_GAME_PATH "SAN47S.GST", size);
		}
	}

	void releaseSan47Tables() {
		if (isTablesLoaded) {
			isTablesLoaded = false;
			releaseMemoryChecked(SAN_TABLE_SMALL);
			releaseMemoryChecked(SAN_TABLE_BIG);
		}
	}

}
#endif