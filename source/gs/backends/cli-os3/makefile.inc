CC = m68k-amigaos-gcc
PROGRAM = ../../dist/monkey3
DATESTR  = $(shell date +"%-d.%-m.%Y")
CFLAGS += -D__AMIGADATE__="\"$(DATESTR)\""
CFLAGS += -DGS_CLI_OS3 -DGS_DEBUG=$(DEBUG) -noixemul -fno-exceptions -m68020

PAGADIR = $(PDIR)/../aga-os3

POBJ +=  $(PAGADIR)/entry.o\
        $(PAGADIR)/file.o\
        $(PAGADIR)/memory.o\
        $(PAGADIR)/fs.o\
        $(PDIR)/mock.o
