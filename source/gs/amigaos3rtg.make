CC = m68k-amigaos-gcc
PROGRAM = ../../dist/monkey3
DATESTR  = $(shell date +"%-d.%-m.%Y")
CFLAGS = -I. -D__AMIGADATE__="\"$(DATESTR)\""
CFLAGS += -DGS_AMIGA -DGS_BIG -DGS_DEBUG=$(DEBUG) -noixemul -fno-exceptions -m68020
POBJ = graphics/rtg.o events/timer.o
