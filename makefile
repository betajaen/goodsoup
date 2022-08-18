PLATFORM = amiga
PROGRAM = dist/monkey3
TEST = 0
DEBUG_LEVEL = 2
DATESTR  = $(shell date +"%-d.%-m.%Y")
GAME_PATH = "COMI:"
IGNORE_NO_FEATURE = 0
ONE_FRAME = 0
VM_DEBUG = 0
CHECKED = 1
FRAME_DELAY=1
DEMO_MODE=0
SAN_CODEC47=1
MUTE_AUDIO=0

CFLAGS = -Isource -D__AMIGADATE__="\"$(DATESTR)\""

ifeq ($(PLATFORM), amiga)
	OBJ		=	source/amiga/entry.o \
				source/amiga/start.o \
				source/amiga/debug.o \
				source/amiga/string_format.o\
				source/amiga/screen.o\
				source/amiga/timer.o\
				source/amiga/cursor.o\
				source/amiga/audio_amiga.o

	CC		= m68k-amigaos-gcc
	DELETE	= rm
	CFLAGS	+= -Isource/amiga -DGS_AMIGA -DGS_BIG -noixemul -fno-exceptions -fno-rtti -fno-threadsafe-statics -m68020
ifeq ($(RELEASE), 1)
	CFLAGS	+= -O2 -fno-builtin -DGS_RELEASE=1 -DGS_DEBUG_LEVEL=4 -DGS_PROTECT_MEMORY=0 -s
else
	CFLAGS	+= -O0 -DGS_RELEASE=0 -DGS_DEBUG_LEVEL=$(DEBUG_LEVEL) -DGS_PROTECT_MEMORY=1
endif
endif

ifeq ($(PLATFORM), sdl)
	OBJ		=	source/sdl/main.o\
				source/sdl/debug.o\
				source/sdl/string_format.o\
				source/sdl/screen.o\
				source/sdl/audio_sdl.o

	CC		= gcc
	DELETE	= rm
	CFLAGS	+= -m32 -std=c++98 -Wpedantic -Isource/sdl -DGS_SDL -DGS_LITTLE -lSDL2 -lstdc++
ifeq ($(RELEASE), 1)
	CFLAGS	+= -O3 -DGS_RELEASE=1 -DGS_DEBUG_LEVEL=4 -DGS_PROTECT_MEMORY=0 -s
else
	CFLAGS	+= -O0 -g -DGS_RELEASE=0 -DGS_DEBUG_LEVEL=$(DEBUG_LEVEL) -DGS_PROTECT_MEMORY=1
endif
endif

CFLAGS += -DGS_GAME_PATH="\"$(GAME_PATH)\""
CFLAGS += -DGS_TEST=$(TEST)
CFLAGS += -DGS_VM_DEBUG=$(VM_DEBUG)
CFLAGS += -DGS_ONE_FRAME=$(ONE_FRAME)
CFLAGS += -DGS_CHECKED=$(CHECKED)
CFLAGS += -DGS_FRAME_DELAY=$(FRAME_DELAY)
CFLAGS += -DGS_SAN_CODEC47=$(SAN_CODEC47)
CFLAGS += -DGS_MUTE_AUDIO=$(MUTE_AUDIO)

ifeq ($(IGNORE_NO_FEATURE), 1)
CFLAGS += -DGS_IGNORE_NO_FEATURE
endif

CFLAGS += -DGS_DEMO_MODE=$(DEMO_MODE)

OBJ +=	source/hash.o\
		source/string.o\
		source/file.o\
		source/memory.o

# Game Sources
OBJ +=	source/main_game.o\
		source/profile.o\
		source/vm/vm.o\
		source/vm/context.o\
		source/vm/stack.o\
		source/vm/array.o\
		source/vm/opcodes.o\
		source/vm/opcodes_names.o\
		source/vm/vars.o\
		source/vm/debugger.o\
		source/script.o\
		source/room.o\
		source/room_scripts.o\
		source/room_graphics.o\
		source/room_objects.o\
		source/index.o\
		source/resource.o\
		source/disk.o\
		source/utils.o\
		source/osd.o\
		source/screen.o\
		source/object.o\
		source/object_functions.o\
		source/verb.o\
		source/actor.o\
		source/table.o\
		source/image.o\
		source/costume.o\
		source/video/video.o\
		source/video/video_frame.o\
		source/video/video_converter.o\
		source/video/san/codec.o\
		source/video/san/iact_timing.o\
		source/video/san/iact_audio.o\
		source/video/san/tables.o\
		source/video/san/fobj_47.o\
		source/video/san/fobj_47_ulong.o\
		source/video/smush/smush_decoder.o\
		source/video/smush/smush_codec47_opt_none.o\
		source/video/smush/smush_codec47_opt_ulong.o\
		source/video/smush/smush_tables.o\
		source/video/gsv/gsv_decoder.o\
		source/video/gsv/gsv_encoder.o\
		source/draw.o\
		source/codecs/bomp.o\
		source/codecs/nut.o\
		source/codecs/rle.o\
		source/font.o\
		source/audio.o\
		source/timer.o\
		source/mutex.o

all: $(OBJ)
	$(CC) -o $(PROGRAM) $(OBJ) $(CFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean .IGNORE:
	$(DELETE) source/*.o
	$(DELETE) source/vm/*.o
	$(DELETE) source/video/*.o
	$(DELETE) source/video/san/*.o
	$(DELETE) source/video/smush/*.o
	$(DELETE) source/codecs/*.o
	$(DELETE) source/sdl/*.o
	$(DELETE) source/amiga/*.o
	$(DELETE) dist/monkey3
