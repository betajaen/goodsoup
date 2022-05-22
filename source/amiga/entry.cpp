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

#include <proto/exec.h>
#include <proto/dos.h>

#define DOS_LIB_NAME   "dos.library"
#define DOS_LIB_VERS   33L
#define INT_LIB_NAME   "intuition.library"
#define INT_LIB_VERS   33L
#define GFX_LIB_NAME   "graphics.library"
#define GFX_LIB_VERS   33L

struct ExecBase* SysBase = NULL;
struct DosLibrary* DOSBase = NULL;
struct IntuitionBase* IntuitionBase = NULL;
struct GfxBase* GfxBase = NULL;

extern int common_main();
extern void exit();
extern void __initlibraries();
extern void __exitlibraries();

__entrypoint void __startup(void)
{
	SysBase = (*((struct ExecBase**)4));
	__initlibraries();
	common_main();
	__exitlibraries();
}

void __exit(int rc)
{
	__exitlibraries();
	Exit(rc);
}

void __initlibraries()
{
	DOSBase = (struct DosLibrary*)OpenLibrary(DOS_LIB_NAME, DOS_LIB_VERS);
	GfxBase = (struct GfxBase*)OpenLibrary(GFX_LIB_NAME, GFX_LIB_VERS);
	IntuitionBase = (struct IntuitionBase*)OpenLibrary(INT_LIB_NAME, INT_LIB_VERS);
}

void __exitlibraries()
{
	if (IntuitionBase)
	{
		CloseLibrary((struct Library*)IntuitionBase);
		IntuitionBase = NULL;
	}

	if (GfxBase)
	{
		CloseLibrary((struct Library*)GfxBase);
		GfxBase = NULL;
	}

	if (DOSBase)
	{
		CloseLibrary((struct Library*)DOSBase);
		DOSBase = NULL;
	}
}
