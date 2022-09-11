CC = m68k-amigaos-gcc
PROGRAM = ../../dist/monkey3
DATESTR  = $(shell date +"%-d.%-m.%Y")
CFLAGS = -I. -D__AMIGADATE__="\"$(DATESTR)\""
CFLAGS += -DGS_AMIGA -DGS_BIG -DGS_DEBUG=$(DEBUG) -DGS_AGA -DGS_ARCH_NAME="\"Amiga AGA\"" -noixemul -fno-exceptions -m68020
POBJ =  $(PDIR)/entry.o \
        $(PDIR)/screen.o \
        $(PDIR)/timer.o\
        $(PDIR)/loop.o\
        $(PDIR)/menu.o\
        $(PDIR)/file.o\
        $(PDIR)/memory.o