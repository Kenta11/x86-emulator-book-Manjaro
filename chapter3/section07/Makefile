TARGET = px86
PROGRAM_CALL = call-test.bin
PROGRAM_LEAVE = leave-test.bin
PROGRAM_LEAVE2 = leave2-test.bin
PROGRAM = $(PROGRAM_CALL) $(PROGRAM_LEAVE) $(PROGRAM_LEAVE2)
OBJS = main.o emulator_function.o instruction.o modrm.o

CC = gcc
LD = ld
ASM = nasm
CFLAGS += -O2 -Wall -Wextra

.PHONY: all run-call-test run-crt run-crt2
all : $(TARGET)

run-call-test : $(TARGET) $(PROGRAM_CALL)
	./$(TARGET) $(PROGRAM_CALL)

run-crt : $(TARGET) $(PROGRAM_LEAVE)
	./$(TARGET) $(PROGRAM_LEAVE)

run-crt2 : $(TARGET) $(PROGRAM_LEAVE2)
	./$(TARGET) $(PROGRAM_LEAVE2)

$(PROGRAM_LEAVE) : crt0.o leave-test.o
	$(LD) -m elf_i386 --entry=start --oformat=binary -Ttext 0x7c00 -o $@ $^

leave-test.o : leave-test.c
	$(CC) -O0 -march=i386 -m32 -nostdlib -fno-asynchronous-unwind-tables -g -fno-stack-protector -fno-pie -c -o $@ $<

$(PROGRAM_LEAVE2) : crt0.o leave2-test.o
	$(LD) -m elf_i386 --entry=start --oformat=binary -Ttext 0x7c00 -o $@ $^

leave2-test.o : leave2-test.c
	$(CC) -O0 -march=i386 -m32 -nostdlib -fno-asynchronous-unwind-tables -g -fno-stack-protector -fno-pie -c -o $@ $<

crt0.o : crt0.asm
	$(ASM) -f elf $<

%.bin : %.asm
	$(ASM) -f bin -o $@ $<

%.o : %.c
	$(CC) $(CFLAGS) -c $<

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

clean :
	rm -f $(TARGET) $(PROGRAM) $(OBJS) leave-test.o leave2-test.o crt0.o
