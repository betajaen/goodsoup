CXX=/opt/amiga/bin/m68k-amigaos-gcc
CXXFLAGS=-I. -std=c++11 -Wall  -noixemul -fno-exceptions -fno-rtti -fno-threadsafe-statics -m68020
LDFLAGS=-noixemul -noixemul -fno-exceptions -fno-rtti -fno-threadsafe-statics

OBJS = entry.o \
       main.o

PROGRAM = ../../dist/monkey3

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(PROGRAM) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(PROGRAM)

test:
	fs-uae \
	--model=A1200 \
	--cpu=68030 \
	--zorro_iii_memory=16384 \
	--kickstart_file=../../tests/kickstart.rom \
	--hard_drive_0=../../tests/dh0.hdf \
	--hard_drive_1=../../dist \
	--hard_drive_1_label=COMI \
	--floppy_drive_volume=0 \
	--floppy_drive_volume_empty=0