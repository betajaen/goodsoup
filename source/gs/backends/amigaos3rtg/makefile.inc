CC = m68k-amigaos-gcc
PROGRAM = ../../dist/monkey3
DATESTR  = $(shell date +"%-d.%-m.%Y")
CFLAGS += -D__AMIGADATE__="\"$(DATESTR)\""
CFLAGS += -DGS_AMIGA -DGS_DEBUG=$(DEBUG) -DGS_RTG -DGS_ARCH_NAME="\"Amiga RTG\"" -noixemul -fno-exceptions -m68020

PAGADIR = $(PDIR)/../amigaos3aga

POBJ +=  $(PAGADIR)/entry.o\
        $(PAGADIR)/timer.o\
        $(PAGADIR)/loop.o\
        $(PAGADIR)/menu.o\
        $(PAGADIR)/file.o\
        $(PAGADIR)/memory.o\
        $(PDIR)/screen.o
