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

#ifndef GS_TYPES_H
#define GS_TYPES_H

#include "config.h"

#ifdef GS_AMIGA
#include "amiga/types_amiga.h"
#else
#include "sdl/types_sdl.h"
#endif


#if defined(GS_CHECKED) && GS_CHECKED == 1


	#define CHECK_IF(COND, MSG) \
		do { \
			if (COND) {\
				error(GS_THIS, MSG);\
				abort_quit_stop();\
				return;\
			}\
		} while(0)

	#define CHECK_IF_1(COND, MSG, A1) \
		do { \
			if (COND) {\
				error(GS_THIS, MSG, A1);\
				abort_quit_stop();\
				return;\
			}\
		} while(0)

	#define CHECK_IF_2(COND, MSG, A1, A2) \
		do { \
			if (COND) {\
				error(GS_THIS, MSG, A1, A2);\
				abort_quit_stop();\
				return;\
			}\
		} while(0)

	#define CHECK_IF_3(COND, MSG, A1, A2, A3) \
		do { \
			if (COND) {\
				error(GS_THIS, MSG, A1, A2, A3);\
				abort_quit_stop();\
				return;\
			}\
		} while(0)

	#define CHECK_IF_4(COND, MSG, A1, A2, A3, A4) \
		do { \
			if (COND) {\
				error(GS_THIS, MSG, A1, A2, A3, A4);\
				abort_quit_stop();\
				return;\
			}\
		} while(0)

	#define CHECK_IF_RETURN(COND, RETURN, MSG) \
		do { \
			if (COND) {\
				error(GS_THIS, MSG);\
				abort_quit_stop();\
				return RETURN;\
			}\
		} while(0)

	#define CHECK_IF_RETURN_1(COND, RETURN, MSG, A1) \
		do { \
			if (COND) {\
				error(GS_THIS, MSG, A1);\
				abort_quit_stop();\
				return RETURN;\
			}\
		} while(0)

	#define CHECK_IF_RETURN_2(COND, RETURN, MSG, A1, A2) \
		do { \
			if (COND) {\
				error(GS_THIS, MSG, A1, A2);\
				abort_quit_stop();\
				return RETURN;\
			}\
		} while(0)

	#define CHECK_IF_RETURN_3(COND, RETURN, MSG, A1, A2, A3) \
		do { \
			if (COND) {\
				error(GS_THIS, MSG, A1, A2, A3);\
				abort_quit_stop();\
				return RETURN;\
			}\
		} while(0)

	#define CHECK_IF_RETURN_4(COND, RETURN, MSG, A1, A2, A3, A4) \
		do { \
			if (COND) {\
				error(GS_THIS, MSG, A1, A2, A3, A4);\
				abort_quit_stop();\
				return RETURN;\
			}\
		} while(0)
#else
	#define CHECK_IF(COND, MSG)
	#define CHECK_IF_1(COND, MSG, A1)
	#define CHECK_IF_2(COND, MSG, A1, A2)
	#define CHECK_IF_3(COND, MSG, A1, A2, A3)
	#define CHECK_IF_4(COND, MSG, A1, A2, A3, A4)
	#define CHECK_IF_RETURN(COND, RETURN, MSG)
	#define CHECK_IF_RETURN_1(COND, RETURN, MSG, A1)
	#define CHECK_IF_RETURN_2(COND, RETURN, MSG, A1, A2)
	#define CHECK_IF_RETURN_3(COND, RETURN, MSG, A1, A2, A3)
	#define CHECK_IF_RETURN_4(COND, RETURN, MSG, A1, A2, A3, A4)
#endif


#endif