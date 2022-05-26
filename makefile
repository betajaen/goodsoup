PLATFORM = sdl
PROGRAM = goodsoup
DATESTR  = $(shell date +"%-d.%-m.%Y")

CFLAGS = -ISource -D__AMIGADATE__="\"$(DATESTR)\""

ifeq ($(PLATFORM), amiga)
	OBJ		= source/amiga/entry.o source/amiga/start.o
	CC		= m68k-amigaos-gcc
	DELETE	= rm
	CFLAGS	+= -DGS_AMIGA -nostartfiles -nostdlib -noixemul -fno-exceptions -fno-rtti
endif

ifeq ($(PLATFORM), sdl)
	OBJ		=	source/sdl/common.o source/sdl/memory.o source/sdl/gfx.o source/sdl/file.o
	CC		= gcc
	DELETE	= rm
	CFLAGS	+= -lSDL2 -lstdc++
endif

# Common Sources
OBJ += source/main.o

# Engine Sources
OBJ +=	source/comi/engine.o \
		source/comi/resource.o \
		source/comi/charset.o \
		source/comi/costume.o \
		source/comi/vm.o \
		source/comi/actor.o \
		source/comi/sound.o \
		source/comi/graphics.o 

all: $(OBJ)
	$(CC) -o $(PROGRAM) $(OBJ) $(CFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean .IGNORE:
	$(DELETE) $(OBJ)
	$(DELETE) $(PROGRAM)
