CXX=/opt/amiga/bin/m68k-amigaos-gcc
CXXFLAGS=-Iinclude -std=c++11 -Wall  -noixemul -fno-exceptions -fno-rtti -fno-threadsafe-statics -m68020
LDFLAGS=-noixemul -noixemul -fno-exceptions -fno-rtti -fno-threadsafe-statics

OBJS = entry.o \
       main.o \
       memory.o \
       requester.o \
	   chunk.o \
       file.o

PROGRAM = ../../install/Install/monkey3

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(PROGRAM) $(LDFLAGS)
	cp $(PROGRAM) ../../tests/COMI/monkey3

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
	--hard_drive_1=../../install \
	--hard_drive_1_label="Monkey3 Install" \
	--hard_drive_2=../../tests/MONKEY3_1 \
	--hard_drive_2_label=MONKEY3_1 \
	--hard_drive_3=../../tests/MONKEY3_2 \
	--hard_drive_3_label=MONKEY3_2 \
	--hard_drive_4=../../tests/Work \
	--hard_drive_4_label=Work \
	--floppy_drive_volume=0 \
	--floppy_drive_volume_empty=0