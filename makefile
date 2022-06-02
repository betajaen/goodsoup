PLATFORM = sdl
PROGRAM = goodsoup
DATESTR  = $(shell date +"%-d.%-m.%Y")

CFLAGS = -Isource -D__AMIGADATE__="\"$(DATESTR)\""

ifeq ($(PLATFORM), amiga)
	OBJ		=	source/amiga/common/entry.o \
				source/amiga/common/start.o
	CC		= m68k-amigaos-gcc
	DELETE	= rm
	CFLAGS	+= -Isource/amiga -DGS_AMIGA -DGS_BIG -nostartfiles -nostdlib -noixemul -fno-exceptions -fno-rtti
endif

ifeq ($(PLATFORM), sdl)
	OBJ		=	source/sdl/common/main.o\
				source/sdl/common/memory.o\
				source/sdl/common/debug.o\
				source/sdl/common/file.o
	CC		= gcc
	DELETE	= rm
	CFLAGS	+= -std=c++98 -Isource/sdl -DGS_LITTLE -lSDL2 -lstdc++
endif

OBJ +=	source/common/hash.o\
		source/common/hashmap.o\
		source/common/array.o\
		source/common/keyarray.o\
		source/common/string.o

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
