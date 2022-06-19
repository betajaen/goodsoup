PLATFORM = amiga
PROGRAM = dist/monkey3
TEST = 0
DEBUG_LEVEL = 2
DATESTR  = $(shell date +"%-d.%-m.%Y")
GAME_PATH = "COMI:"

CFLAGS = -Isource -D__AMIGADATE__="\"$(DATESTR)\""

ifeq ($(PLATFORM), amiga)
	OBJ		=	source/amiga/common/entry.o \
				source/amiga/common/start.o \
				source/amiga/common/debug.o \
				source/amiga/common/memory.o\
				source/amiga/common/file.o\
				source/amiga/common/string.o

	CC		= m68k-amigaos-gcc
	DELETE	= rm
	CFLAGS	+= -Isource/amiga -DGS_AMIGA -DGS_BIG -noixemul -fno-exceptions -fno-rtti -m68020
ifeq ($(RELEASE), 1)
	CFLAGS	+= -O2 -fno-builtin -DGS_RELEASE -DGS_DEBUG_LEVEL=4 -DGS_PROTECT_MEMORY=0
else
	CFLAGS	+= -O0 -DGS_DEBUG -DGS_DEBUG_LEVEL=$(DEBUG_LEVEL) -DGS_PROTECT_MEMORY=1
endif
endif

ifeq ($(PLATFORM), sdl)
	OBJ		=	source/sdl/common/main.o\
				source/sdl/common/memory.o\
				source/sdl/common/debug.o\
				source/sdl/common/file.o\
				source/sdl/common/string.o

	CC		= gcc
	DELETE	= rm
	CFLAGS	+= -m32 -std=c++98 -Wpedantic -Isource/sdl -DGS_LITTLE -DGS_DEBUG_LEVEL=$(DEBUG_LEVEL) -lSDL2 -lstdc++
ifeq ($(RELEASE), 1)
	CFLAGS	+= -O3 -DGS_RELEASE -DGS_DEBUG_LEVEL=4 -DGS_PROTECT_MEMORY=0
else
	CFLAGS	+= -O0 -DGS_DEBUG -DGS_DEBUG_LEVEL=$(DEBUG_LEVEL) -DGS_PROTECT_MEMORY=1
endif
endif

CFLAGS += -DGS_GAME_PATH="\"$(GAME_PATH)\""
CFLAGS += -DGS_TEST=$(TEST)

OBJ +=	source/common/main.o\
		source/common/hash.o\
		source/common/hashmap.o\
		source/common/array.o\
		source/common/keyarray.o\
		source/common/string.o\
		source/common/test.o\
		source/common/test_file.o

# Game Sources
OBJ +=	source/comi/main.o\
		source/comi/vm.o\
		source/comi/vm_array.o\
		source/comi/vm_opcodes.o\
		source/comi/vm_vars.o\
		source/comi/script.o\
		source/comi/room.o\
		source/comi/index.o\
		source/comi/resource.o\
		source/comi/disk.o\
		source/comi/utils.o

all: $(OBJ)
	$(CC) -o $(PROGRAM) $(OBJ) $(CFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean .IGNORE:
	$(DELETE) $(OBJ)
	$(DELETE) $(PROGRAM)
