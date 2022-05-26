PLATFORM = sdl
PROGRAM = goodsoup
DATESTR  = $(shell date +"%-d.%-m.%Y")

CFLAGS = -Isource -D__AMIGADATE__="\"$(DATESTR)\""

ifeq ($(PLATFORM), amiga)
	OBJ		=	source/backends/amiga/common/entry.o \
				source/backends/amiga/common/start.o
	CC		= m68k-amigaos-gcc
	DELETE	= rm
	CFLAGS	+= -Isource/backends/amiga -DGS_AMIGA -DGS_BIG -nostartfiles -nostdlib -noixemul -fno-exceptions -fno-rtti
endif

ifeq ($(PLATFORM), sdl)
	OBJ		=	source/backends/sdl/common/main.o\
				source/backends/sdl/common/memory.o\
				source/backends/sdl/common/debug.o\
				source/backends/sdl/common/file.o
	CC		= gcc
	DELETE	= rm
	CFLAGS	+= -Isource/backends/sdl -DGS_LITTLE -lSDL2 -lstdc++
endif

# Game Sources
OBJ +=	source/comi/start.o\
		source/comi/engine.o\
		source/comi/resource.o\
		source/comi/charset.o\
		source/comi/costume.o\
		source/comi/vm.o\
		source/comi/actor.o\
		source/comi/sound.o\
		source/comi/graphics.o

all: $(OBJ)
	$(CC) -o $(PROGRAM) $(OBJ) $(CFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean .IGNORE:
	$(DELETE) $(OBJ)
	$(DELETE) $(PROGRAM)
