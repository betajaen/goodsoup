PLATFORM = amigaos3rtg
DEBUG = 0
include $(PLATFORM).make

OBJ = entry.o shared/error.o shared/string.o main.o

all: $(OBJ) $(POBJ)
	$(CC) -o $(PROGRAM) $(OBJ) $(POBJ) $(CFLAGS) -DGS_DEBUG=$(DEBUG)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean .IGNORE:
	rm $(OBJ)
	rm $(POBJ)
	rm $(PROGRAM)
