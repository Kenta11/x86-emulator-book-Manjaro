TARGET = px86
PROGRAM = test.bin
OBJS = main.o emulator_function.o instruction.o modrm.o

CC = gcc
LD = ld
ASM = nasm
CFLAGS += -O2 -Wall -Wextra

.PHONY: all run
all : $(TARGET)

run : $(TARGET) $(PROGRAM)
	./$(TARGET) $(PROGRAM)

$(PROGRAM) : crt0.o test.o
	$(LD) -m elf_i386 --entry=start --oformat=binary -Ttext 0x7c00 -o $@ $^

test.o : test.c
	$(CC) -O0 -march=i386 -m32 -nostdlib -fno-asynchronous-unwind-tables -g -fno-stack-protector -fno-pie -c -o $@ $<

crt0.o : crt0.asm
	$(ASM) -f elf $<

%.o : %.c
	$(CC) $(CFLAGS) -c $<

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

clean :
	rm -f $(TARGET) $(PROGRAM) $(OBJS) test.o crt0.o
