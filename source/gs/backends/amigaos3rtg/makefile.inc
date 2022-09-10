CC = m68k-amigaos-gcc
PROGRAM = ../../dist/monkey3
DATESTR  = $(shell date +"%-d.%-m.%Y")
CFLAGS = -I. -D__AMIGADATE__="\"$(DATESTR)\""
CFLAGS += -DGS_AMIGA -DGS_BIG -DGS_DEBUG=$(DEBUG) -DGS_RTG -DGS_ARCH_NAME="\"Amiga RTG\"" -noixemul -fno-exceptions -m68020

PAGADIR = $(PDIR)/../amigaos3aga

POBJ =  $(PAGADIR)/entry.o\
        $(PAGADIR)/timer.o\
        $(PDIR)/screen.o