CC = gcc
PROGRAM = ../../dist/monkey3
DATESTR  = $(shell date +"%-d.%-m.%Y")
CFLAGS += -m32  -D__AMIGADATE__="\"$(DATESTR)\""
CFLAGS += -DGS_CLI_X86 -DGS_DEBUG=$(DEBUG)
POBJ +=  $(PDIR)/entry.o\
        $(PDIR)/mock.o\
        $(PDIR)/file.o\
        $(PDIR)/fs.o\
        $(PDIR)/memory.o