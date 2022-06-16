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

#define GS_FILE_NAME "debug"

#include "common/debug.h"
#include "common/memory.h"

#include <proto/exec.h>
#include <proto/dos.h>

namespace common
{
	typedef VOID(*PUTCHARPROC)();

	static const uint32 PutChar = 0x16c04e75;
	static const uint32 LenChar = 0x52934e75;
	static char BufChar[1024] = { 0 };
	
	static const char HEX_CHAR[16] = {
		'0',
		'1',
		'2',
		'3',
		'4',
		'5',
		'6',
		'7',
		'8',
		'9',
		'A',
		'B',
		'C',
		'D',
		'E',
		'F',
	};

	static inline void gs_printf(const char* fmt, ...) {
		const char* arg = (const char*)(&fmt + 1);
		RawDoFmt((CONST_STRPTR) fmt, (APTR) arg, (PUTCHARPROC)&PutChar, &BufChar[0]);
		PutStr(BufChar);
	}

	static inline void gs_print(const char* text) {
		PutStr((CONST_STRPTR)text);
	}

	static inline void exit(int rc) {
		/* TODO */
	}

	void debug_write(DebugCategory category, const char* module, const char* file, const char* function, uint32 line, const char* message) {
		switch (category) {
			default:
			case DC_Test: gs_print("T "); break;
			case DC_Verbose: gs_print("V "); break;
			case DC_Debug: gs_print("D "); break;
			case DC_Informational: gs_print("I "); break;
			case DC_Warning: gs_print("W "); break;
			case DC_Error: gs_print("\n!! ERROR !!\n\nE "); break;
		}

		gs_print(module);
		gs_printf("\t%-10s\t%-10s\t%ld\t", file, function, line);

		gs_print(message);

		gs_print("\n");

		if (category == DC_Error) {
			gs_print("\n");
		}
	}

	void debug_writef(DebugCategory category, const char* module, const char* file, const char* function, uint32 line, const char* format, ...) {

		switch (category) {
			default:
			case DC_Test: gs_print("T "); break;
			case DC_Verbose: gs_print("V "); break;
			case DC_Debug: gs_print("D "); break;
			case DC_Informational: gs_print("I "); break;
			case DC_Warning: gs_print("W "); break;
			case DC_Error: gs_print("\n!! ERROR !!\n\nE "); break;
		}


		gs_print(module);
		gs_printf("\t%-10s\t%s\t%ld\t", file, function, line);

		/* TODO */
		// va_start(ap, format);
		// vfprintf(stdout, format, ap);
		// va_end(ap);

		const char* format_arg = (const char*)(&format + 1);
		RawDoFmt((CONST_STRPTR) format, (APTR)format_arg, (PUTCHARPROC)&PutChar, &BufChar[0]);
		gs_print(BufChar);

		gs_print("\n");

		if (category == DC_Error) {
			gs_print("\n");
		}

	}

	void debug_stop(const char* file, uint32 line, const char* message) {
		gs_printf("%s:%lu\n", file, line);
		if (message) {
			gs_print(message);
		}
		Exit(0);
	}

	void debug_write_test_fail_location(const char* file, uint32 line, const char* test_name) {
		// Printf("%s failed\n:\n\t%s:%lu\n", test_name, file, line);
	}

	void debug_write_str(const char* str_value) {
		FPuts(Output(), str_value);
	}

	void debug_write_byte(byte byte_value) {

		char str_temp[3];
		str_temp[0] = HEX_CHAR[((byte_value >> 4) & 0xF)];
		str_temp[1] = HEX_CHAR[(byte_value & 0xF)];
		str_temp[2] = 0;
		
		FPuts(Output(), str_temp);

		//Printf("%02x", byte_value);
	}

	void debug_write_char(char char_value) {
		FPutC(Output(), char_value);
	}

	void debug_write_unsigned_int(uint32 uint32_value) {
		Printf("%lu", uint32_value);
	}

	void debug_write_int(int32 int32_value) {
		Printf("%ld", int32_value);
	}
	
	void debug_write_hex(uint32 hex_value) {
		Printf("%lx", hex_value);
	}

	void debug_write_str_int(const char* str, int32 int32_value) {
		Printf("%s:%ld", (ULONG) str, int32_value);
	}

	void debug_write_bool(bool bool_value) {
		if (bool_value)
			FPuts(Output(), "true");
		else
			FPuts(Output(), "false");
	}

	void debug_write_pointer(const void* ptr) {
		Printf("0x%lx", (uint32) ptr);
	}

	void handle_leak_measure(uint32& m) {
		m = getHeapSize();
	}

	void handle_test_fail_write_header(const char* file, uint32 line, const char* testName) {
		debug_write_char('\n');
		debug_write_str(file);
		debug_write_char('(');
		debug_write_unsigned_int(line);
		debug_write_char(',');
		debug_write_str(testName);
		debug_write_str(") FAILED!\n");
	}

	void handle_test_fail_write_aopb_string(const char* left, const char* right, const char* operatorType) {
		debug_write_str(left);
		debug_write_char(' ');
		debug_write_str(operatorType);
		debug_write_char(' ');
		debug_write_str(right);
		debug_write_char('\n');
	}

	void handle_test_heap_then_memory_offset(const char* file, int32 line, const char* testName, uint32 marker, int32 bytes) {

		int32 difference = getHeapSize() - marker;

		if (difference != bytes) {
			handle_test_fail_write_header(file, line, testName);

			debug_write_str("Heap size is unexpected.\n");

			debug_write_str("\tExpected: ");
			debug_write_int(bytes);
			debug_write_str(" bytes\n");

			debug_write_str("\tActually: ");
			debug_write_int(difference);
			debug_write_str(" bytes\n");

			debug_write_str("\n");
		}

	}

}
