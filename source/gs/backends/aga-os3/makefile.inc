CC = m68k-amigaos-gcc
PROGRAM = ../../dist/monkey3
DATESTR  = $(shell date +"%-d.%-m.%Y")
CFLAGS += -D__AMIGADATE__="\"$(DATESTR)\""
CFLAGS += -DGS_AGA_OS3 -DGS_DEBUG=$(DEBUG) -noixemul -fno-exceptions -m68020
POBJ +=  $(PDIR)/entry.o \
        $(PDIR)/screen.o \
        $(PDIR)/timer.o\
        $(PDIR)/loop.o\
        $(PDIR)/menu.o\
        $(PDIR)/file.o\
        $(PDIR)/memory.o