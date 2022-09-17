PLATFORM = rtg-os3
DEBUG = 0
POBJ =
PDIR = backends/$(PLATFORM)
CFLAGS = -std=c11 -I.
include $(PDIR)/makefile.inc

OBJ =	shared/error.o \
		shared/string.o \
		shared/tag.o\
		shared/file_common.o\
		main.o \
		events/events.o \
		coroutine.o \
		formats/la0.o

all: $(OBJ) $(POBJ)
	$(CC) -o $(PROGRAM) $(OBJ) $(POBJ) $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean .IGNORE:
	rm $(OBJ)
	rm $(POBJ)
	rm $(PROGRAM)
