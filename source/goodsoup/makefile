PLATFORM = amiga
PROGRAM = ../../dist/monkey3
TEST = 0
DEBUG_LEVEL = 2
DATESTR  = $(shell date +"%-d.%-m.%Y")
GAME_PATH = "COMI:"
IGNORE_NO_FEATURE = 1
ONE_FRAME = 0
VM_DEBUG = 0
CHECKED = 1
FRAME_DELAY=1
DEMO_MODE=0
SAN_CODEC47=1
MUTE_AUDIO=0

CFLAGS = -I. -D__AMIGADATE__="\"$(DATESTR)\""

ifeq ($(PLATFORM), amiga)
	OBJ		=	amiga/entry.o \
				amiga/start.o \
				amiga/debug.o \
				amiga/string_format.o\
				amiga/screen.o\
				amiga/timer.o\
				amiga/cursor.o\
				amiga/audio_amiga.o\
				amiga/audio_hook.o

	CC		= m68k-amigaos-gcc
	DELETE	= rm
	CFLAGS	+= -Iamiga -DGS_AMIGA -DGS_BIG -noixemul -fno-exceptions -fno-rtti -fno-threadsafe-statics -m68020
ifeq ($(RELEASE), 1)
	CFLAGS	+= -O2 -fno-builtin -DGS_RELEASE=1 -DGS_DEBUG_LEVEL=4 -DGS_PROTECT_MEMORY=0 -s
else
	CFLAGS	+= -O0 -DGS_RELEASE=0 -DGS_DEBUG_LEVEL=$(DEBUG_LEVEL) -DGS_PROTECT_MEMORY=1
endif
endif

ifeq ($(PLATFORM), sdl)
	OBJ		=	sdl/main.o\
				sdl/debug.o\
				sdl/string_format.o\
				sdl/screen.o\
				sdl/audio_sdl.o

	CC		= gcc
	DELETE	= rm
	CFLAGS	+= -m32 -std=c++98 -Wpedantic -Isdl -DGS_SDL -DGS_LITTLE -lSDL2 -lstdc++
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

OBJ +=	hash.o\
		string.o\
		file.o\
		memory.o

# Game Sources
OBJ +=	main_game.o\
		profile.o\
		vm/vm.o\
		vm/context.o\
		vm/stack.o\
		vm/array.o\
		vm/opcodes.o\
		vm/opcodes_names.o\
		vm/vars.o\
		vm/debugger.o\
		script.o\
		room.o\
		room_scripts.o\
		room_graphics.o\
		room_objects.o\
		index.o\
		resource.o\
		disk.o\
		utils.o\
		osd.o\
		screen.o\
		object.o\
		object_functions.o\
		verb.o\
		actor.o\
		table.o\
		image.o\
		costume.o\
		video/video.o\
		video/video_frame.o\
		video/video_converter.o\
		video/san/codec.o\
		video/san/iact_timing.o\
		video/san/iact_audio.o\
		video/san/tables.o\
		video/san/fobj_47.o\
		video/san/fobj_47_ulong.o\
		video/smush/smush_decoder.o\
		video/smush/smush_codec47_opt_none.o\
		video/smush/smush_codec47_opt_ulong.o\
		video/smush/smush_tables.o\
		video/gsv/gsv_decoder.o\
		video/gsv/gsv_encoder.o\
		draw.o\
		codecs/la0.o\
		codecs/gsi.o\
		codecs/bomp.o\
		codecs/nut.o\
		codecs/rle.o\
		codecs/image.o\
		font.o\
		audio.o\
		timer.o\
		mutex.o

all: $(OBJ)
	$(CC) -o $(PROGRAM) $(OBJ) $(CFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean .IGNORE:
	$(DELETE) *.o
	$(DELETE) vm/*.o
	$(DELETE) video/*.o
	$(DELETE) video/san/*.o
	$(DELETE) video/smush/*.o
	$(DELETE) video/gsv/*.o
	$(DELETE) codecs/*.o
	$(DELETE) sdl/*.o
	$(DELETE) amiga/*.o
	$(DELETE) $(PROGRAM)
