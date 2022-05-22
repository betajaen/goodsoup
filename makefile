PLATFORM = amiga
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
	OBJ		=	source/sdl/start.o source/sdl/gfx.o
	CC		= gcc
	DELETE	= rm
	CFLAGS	+= -lSDL2
endif

OBJ += source/main.o

all: $(OBJ)
	$(CC) -o $(PROGRAM) $(OBJ) $(CFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean .IGNORE:
	$(DELETE) $(OBJ)
	$(DELETE) $(PROGRAM)
