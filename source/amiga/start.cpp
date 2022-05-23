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

#include "goodsoup.h"

#include <proto/exec.h>
#include <proto/dos.h>

int common_main()
{
	return common::start();
}

extern void __exit(int);

static const uint32 PUTCHARPROCFN = 0x16c04e75;
static char PUTCHARBUF[1024] = { 0 };

typedef VOID(*PUTCHARPROC)();

void debug(const char* fmt, ...)
{
	const char* arg = (const char*)(&fmt + 1);
	RawDoFmt(fmt, (APTR)arg, (PUTCHARPROC)&PUTCHARPROCFN, &PUTCHARBUF[0]);
	PutStr("D ");
	PutStr(PUTCHARBUF);
	PutStr("\n");
}

void warn(const char* fmt, ...)
{
	const char* arg = (const char*)(&fmt + 1);
	RawDoFmt(fmt, (APTR)arg, (PUTCHARPROC)&PUTCHARPROCFN, &PUTCHARBUF[0]);
	PutStr("W ");
	PutStr(PUTCHARBUF);
	PutStr("\n");
}

void error(const char* fmt, ...)
{
	const char* arg = (const char*)(&fmt + 1);
	RawDoFmt(fmt, (APTR)arg, (PUTCHARPROC)&PUTCHARPROCFN, &PUTCHARBUF[0]);
	PutStr("!! Error !!\n");
	PutStr(PUTCHARBUF);
	PutStr("\n");
}


void __assert_impl(const char* file, int line)
{
	debug("Assertion!\nFile: %s:%iWarning: Resources were NOT released.\n", file, line);
	__exit(1);
}

namespace platform
{
	bool preinit()
	{
		return false;
	}

	bool init()
	{
		return false;
	}

	bool teardown()
	{
		PutStr("Bye.\n");
		return false;
	}

	void wait(uint32 ms)
	{
	}
}
