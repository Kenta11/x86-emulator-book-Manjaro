TARGET = px86
PROGRAM = subroutine32.bin
OBJS = main.o emulator_function.o instruction.o modrm.o io.o bios.o

CC = gcc
ASM = nasm
CFLAGS += -O2 -Wall -Wextra

.PHONY: all run clean
all : $(TARGET) $(PROGRAM)

run : $(TARGET) $(PROGRAM)
	./$(TARGET) -q $(PROGRAM)

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

%.bin : %.asm
	$(ASM) -f bin -o $@ $<

clean :
	rm -f $(TARGET) $(PROGRAM) $(OBJS)
