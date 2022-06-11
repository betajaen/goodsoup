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
#include <proto/intuition.h>

#include <dos/dos.h>
#include <workbench/workbench.h>
#include <inline/exec.h>
#include <inline/dos.h>

int __nocommandline = 1;
int __initlibraries = 0;

struct DosLibrary* DOSBase = NULL;
struct IntuitionBase* IntuitionBase = NULL;
struct GfxBase* GfxBase = NULL;
extern struct WBStartup* _WBenchMsg;

extern int amiga_main();

int main(void) {


	if ((DOSBase = (struct DosLibrary*)OpenLibrary("dos.library", 33)) == NULL)
	{
		return RETURN_FAIL;
	}

	if ((IntuitionBase = (struct IntuitionBase*)OpenLibrary("intuition.library", 33)) == NULL)
	{
		CloseLibrary((struct Library*)DOSBase);
		return RETURN_FAIL;
	}

	if ((GfxBase = (struct GfxBase*)OpenLibrary("graphics.library", 33)) == NULL)
	{
		CloseLibrary((struct Library*)IntuitionBase);
		CloseLibrary((struct Library*)DOSBase);
		return RETURN_FAIL;
	}

	amiga_main();

	if (_WBenchMsg) {
		EasyStruct str;
		str.es_StructSize = sizeof(EasyStruct);
		str.es_Flags = 0;
		str.es_GadgetFormat = (UBYTE*)"OK";
		str.es_TextFormat = (UBYTE*)"Thanks for playing!";
		str.es_Title = (UBYTE*)"Goodsoup";

		EasyRequest(NULL, &str, NULL);
	}
	else {
		PutStr("Thanks for playing!\n");
	}

	CloseLibrary((struct Library*)GfxBase);
	CloseLibrary((struct Library*)IntuitionBase);
	CloseLibrary((struct Library*)DOSBase);

	return RETURN_OK;
}
