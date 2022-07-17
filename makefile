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

CFLAGS = -Isource -D__AMIGADATE__="\"$(DATESTR)\""

ifeq ($(PLATFORM), amiga)
	OBJ		=	source/amiga/entry.o \
				source/amiga/start.o \
				source/amiga/debug.o \
				source/amiga/memory.o\
				source/amiga/file.o\
				source/amiga/string_format.o\
				source/amiga/screen.o\
				source/amiga/timer.o\
				source/amiga/cursor.o

	CC		= m68k-amigaos-gcc
	DELETE	= rm
	CFLAGS	+= -Isource/amiga -DGS_AMIGA -DGS_BIG -noixemul -fno-exceptions -fno-rtti -fno-threadsafe-statics -m68020
ifeq ($(RELEASE), 1)
	CFLAGS	+= -O2 -fno-builtin -DGS_RELEASE -DGS_DEBUG_LEVEL=4 -DGS_PROTECT_MEMORY=0 -s
else
	CFLAGS	+= -O0 -DGS_DEBUG -DGS_DEBUG_LEVEL=$(DEBUG_LEVEL) -DGS_PROTECT_MEMORY=1
endif
endif

ifeq ($(PLATFORM), sdl)
	OBJ		=	source/sdl/main.o\
				source/sdl/memory.o\
				source/sdl/debug.o\
				source/sdl/file.o\
				source/sdl/string_format.o\
				source/sdl/screen.o

	CC		= gcc
	DELETE	= rm
	CFLAGS	+= -m32 -std=c++98 -Wpedantic -Isource/sdl -DGS_SDL -DGS_LITTLE -lSDL2 -lstdc++
ifeq ($(RELEASE), 1)
	CFLAGS	+= -O3 -DGS_RELEASE -DGS_DEBUG_LEVEL=4 -DGS_PROTECT_MEMORY=0 -s
else
	CFLAGS	+= -O0 -g -DGS_DEBUG -DGS_DEBUG_LEVEL=$(DEBUG_LEVEL) -DGS_PROTECT_MEMORY=1
endif
endif

CFLAGS += -DGS_GAME_PATH="\"$(GAME_PATH)\""
CFLAGS += -DGS_TEST=$(TEST)
CFLAGS += -DGS_VM_DEBUG=$(VM_DEBUG)
CFLAGS += -DGS_ONE_FRAME=$(ONE_FRAME)
CFLAGS += -DGS_CHECKED=$(CHECKED)
CFLAGS += -DGS_FRAME_DELAY=$(FRAME_DELAY)

ifeq ($(IGNORE_NO_FEATURE), 1)
CFLAGS += -DGS_IGNORE_NO_FEATURE
endif

OBJ +=	source/hash.o\
		source/hashmap.o\
		source/array.o\
		source/keyarray.o\
		source/string.o\
		source/test.o\
		source/test_file.o

# Game Sources
OBJ +=	source/main_game.o\
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
		source/video/codec.o\
		source/draw.o\
		source/codecs.o

all: $(OBJ)
	$(CC) -o $(PROGRAM) $(OBJ) $(CFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean .IGNORE:
	$(DELETE) source/*.o
	$(DELETE) source/vm/*.o
	$(DELETE) source/video/*.o
	$(DELETE) source/sdl/*.o
	$(DELETE) source/amiga/*.o
	$(DELETE) dist/monkey3
