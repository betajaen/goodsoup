PLATFORM = amiga
PROGRAM = dist/goodsoup
TEST = 1
DATESTR  = $(shell date +"%-d.%-m.%Y")
GAMEPATH = ""

CFLAGS = -Isource -D__AMIGADATE__="\"$(DATESTR)\""

ifeq ($(PLATFORM), amiga)
	OBJ		=	source/amiga/common/entry.o \
				source/amiga/common/start.o \
				source/amiga/common/debug.o \
				source/amiga/common/memory.o\
				source/amiga/common/file.o

	CC		= m68k-amigaos-gcc
	DELETE	= rm
	CFLAGS	+= -Isource/amiga -DGS_AMIGA -DGS_BIG -DGS_PROTECT_MEMORY=1 -DGS_TEST=$(TEST) -DGS_GAME_PATH="\"COMI:\"" -nostartfiles -nostdlib -noixemul -fno-exceptions -fno-rtti -m68020
endif

ifeq ($(PLATFORM), sdl)
	OBJ		=	source/sdl/common/main.o\
				source/sdl/common/memory.o\
				source/sdl/common/debug.o\
				source/sdl/common/file.o

	CC		= gcc
	DELETE	= rm
	CFLAGS	+= -m32 -std=c++98 -Wpedantic -Isource/sdl -DGS_GAME_PATH="\"\"" -DGS_LITTLE -DGS_TEST=$(TEST) -lSDL2 -lstdc++
endif

OBJ +=	source/common/main.o\
		source/common/hash.o\
		source/common/hashmap.o\
		source/common/array.o\
		source/common/keyarray.o\
		source/common/string.o\
		source/common/test.o\
		source/common/test_file.o

# Game Sources
OBJ +=	source/comi/start.o\
		source/comi/context.o\
		source/comi/script.o\
		source/comi/script_data.o\
		source/comi/index.o\
		source/comi/resource.o

all: $(OBJ)
	$(CC) -o $(PROGRAM) $(OBJ) $(CFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean .IGNORE:
	$(DELETE) $(OBJ)
	$(DELETE) $(PROGRAM)
