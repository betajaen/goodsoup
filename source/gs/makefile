PLATFORM = amigaos3rtg
DEBUG = 0
PDIR = backends/$(PLATFORM)

include $(PDIR)/makefile.inc

OBJ = shared/error.o shared/string.o main.o events/events.o

all: $(OBJ) $(POBJ)
	$(CC) -o $(PROGRAM) $(OBJ) $(POBJ) $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean .IGNORE:
	rm $(OBJ)
	rm $(POBJ)
	rm $(PROGRAM)
