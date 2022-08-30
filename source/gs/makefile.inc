OBJ = main.o


all: $(OBJ)
	$(CC) -o $(PROGRAM) $(OBJ) $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean .IGNORE:
	$(DELETE) *.o
	$(DELETE) $(PROGRAM)
