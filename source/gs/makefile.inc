OBJ = entry.o main.o


all: $(OBJ) $(POBJ)
	$(CC) -o $(PROGRAM) $(OBJ) $(POBJ) $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean .IGNORE:
	rm $(OBJ)
	rm $(POBJ)
	rm $(PROGRAM)
