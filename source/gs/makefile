PLATFORM = rtg-os3
DEBUG = 0
POBJ =
PDIR = backends/$(PLATFORM)
CFLAGS = -std=c11 -I.
CFLAGS += -g -O0

include $(PDIR)/makefile.inc


#ifneq ($(DEBUG), 0)
#	CFLAGS += -g -O0
#else
#	CFLAGS += -s -O2
#endif


OBJ =	shared/error.o \
		shared/string.o \
		shared/tag.o\
		shared/file_common.o\
		shared/buffer.o\
		graphics/image.o\
		graphics/palette.o\
		main.o \
		events/events.o \
		vm_context.o \
		vm_stack.o\
		vm_script_gs8.o\
		vm_script_la8.o\
		room.o \
		script.o \
		script_la8.o \
		script_gs8.o \
		formats/la0.o\
		formats/lflf.o\
		formats/scrp.o

all: $(OBJ) $(POBJ)
	$(CC)  $(CFLAGS) $(OBJ) $(POBJ) -o $(PROGRAM)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean .IGNORE:
	rm $(OBJ)
	rm $(POBJ)
	rm $(PROGRAM)
