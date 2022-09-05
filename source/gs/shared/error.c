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

#include "shared/error.h"

// shared/error.c
extern int gs_StartedFromCli;

void gs__error_fmt(const char* source, uint32 line, const char* function, uint16 category, const char* fmt, ...) {

	if (category == 0 && gs_StartedFromCli == 0) {

	}
	else {

	}
}

void gs__error_str(const char* source, uint32 line, const char* function, uint16 category, const char* str) {


	if (category == 0 && gs_StartedFromCli == 0) {

	}
	else {

	}

}

void gs_print_fmt(const char* fmt, ...) {

}

void gs_print_str(const char* str) {

}

void gs_message_fmt(const char* fmt, ...) {

}

void gs_message_str(const char* str) {

}