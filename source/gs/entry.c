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

#if defined(GS_AMIGA)

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/intuition.h>

#include <dos/dos.h>
#include <workbench/workbench.h>
#include <inline/exec.h>
#include <inline/dos.h>

#define MIN_STACK_SIZE 65536U

int __nocommandline = 1;
int __initlibraries = 0;
extern char * __commandline;
struct DosLibrary* DOSBase = NULL;
struct IntuitionBase* IntuitionBase = NULL;
extern struct WBStartup* _WBenchMsg;
int gs_StartedFromCli = 0;

static ULONG string_to_int(STRPTR str);
// main.c
extern int gs_Main(int param);


int main(void) {

	int param;

	if ((DOSBase = (struct DosLibrary*)OpenLibrary("dos.library", 33)) == NULL) {
		return RETURN_FAIL;
	}

	struct Task* thisTask = FindTask(NULL);
	ULONG currentStack=(ULONG) thisTask->tc_SPUpper-(ULONG)thisTask->tc_SPLower;

	if (currentStack < MIN_STACK_SIZE) {

		if (_WBenchMsg) {
			if ((IntuitionBase = (struct IntuitionBase*)OpenLibrary("intuition.library", 33)) != NULL) {
				struct EasyStruct str;
				str.es_StructSize = sizeof(struct EasyStruct);
				str.es_Flags = 0;
				str.es_GadgetFormat = (UBYTE*)"OK";
				str.es_TextFormat = (UBYTE*)"Not enough stack space!\n\n%ld bytes given.\n\nPlease increase it to at least %ld bytes\nin the Workbench Information Window.";
				str.es_Title = (UBYTE*)"Goodsoup";

				EasyRequest(NULL, &str, NULL, currentStack, MIN_STACK_SIZE);
				CloseLibrary((struct Library*)IntuitionBase);
			}
		}
		else {
			Printf("Not enough stack space!\n\n%ld bytes given.\n\nPlease run the command \"stack %lu\" before running this program from the CLI.\n", currentStack, MIN_STACK_SIZE);
		}

		CloseLibrary((struct Library*)DOSBase);

		return RETURN_FAIL;
	}

	if ((IntuitionBase = (struct IntuitionBase*)OpenLibrary("intuition.library", 33)) == NULL) {
		CloseLibrary((struct Library*)DOSBase);
		return RETURN_FAIL;
	}


	param = 0;

	if (_WBenchMsg == NULL && __commandline != NULL) {
		param = string_to_int(__commandline);
		gs_StartedFromCli = TRUE;
	}
	else {
		gs_StartedFromCli = FALSE;
	}

	gs_Main(param);

	if (_WBenchMsg) {
		struct EasyStruct str;
		str.es_StructSize = sizeof(struct EasyStruct);
		str.es_Flags = 0;
		str.es_GadgetFormat = (UBYTE*)"OK";
		str.es_TextFormat = (UBYTE*)"Thanks for playing!";
		str.es_Title = (UBYTE*)"Goodsoup";

		EasyRequest(NULL, &str, NULL);
	}
	else {
		PutStr("Thanks for playing!\n");
	}

	CloseLibrary((struct Library*)IntuitionBase);
	CloseLibrary((struct Library*)DOSBase);

	return RETURN_OK;
}

static ULONG string_to_int(STRPTR str) {
	ULONG num = 0;
	while(*str != 0) {
		if (*str < '0' || *str > '9')
			break;

		num *= 10UL;
		num += *str - '0';

		str++;
	}

	return num;
}

#endif
