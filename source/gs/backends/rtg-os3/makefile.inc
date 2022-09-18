CC = m68k-amigaos-gcc
PROGRAM = ../../dist/monkey3
DATESTR  = $(shell date +"%-d.%-m.%Y")
CFLAGS += -D__AMIGADATE__="\"$(DATESTR)\""
CFLAGS += -DGS_RTG_OS3 -DGS_DEBUG=$(DEBUG) -noixemul -fno-exceptions -m68020

PAGADIR = $(PDIR)/../aga-os3

POBJ +=  $(PAGADIR)/entry.o\
        $(PAGADIR)/timer.o\
        $(PAGADIR)/loop.o\
        $(PAGADIR)/menu.o\
        $(PAGADIR)/file.o\
        $(PAGADIR)/fs.o\
        $(PAGADIR)/memory.o\
        $(PDIR)/screen.o
