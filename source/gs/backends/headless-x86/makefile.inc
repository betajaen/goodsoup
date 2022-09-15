CC = gcc
PROGRAM = ../../dist/monkey3
DATESTR  = $(shell date +"%-d.%-m.%Y")
CFLAGS += -m32  -D__AMIGADATE__="\"$(DATESTR)\""
CFLAGS += -DGS_HEADLESS_X86 -DGS_DEBUG=$(DEBUG) -DGS_ARCH_NAME="\"Headless X86\""
POBJ +=  $(PDIR)/entry.o\
        $(PDIR)/mock.o\
        $(PDIR)/file.o\
        $(PDIR)/memory.o