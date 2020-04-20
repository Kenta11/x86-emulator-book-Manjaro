TARGET = px86
PROGRAM = modrm-test.bin
OBJS = main.o emulator_function.o instruction.o modrm.o

CC = gcc
ASM = nasm
CFLAGS += -O2 -Wall -Wextra

.PHONY: all run
all : $(TARGET)

run : $(TARGET) $(PROGRAM)
	./$(TARGET) $(PROGRAM)

%.bin : %.asm
	$(ASM) -f bin -o $@ $<

%.o : %.c
	$(CC) $(CFLAGS) -c $<

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

clean :
	rm -f $(TARGET) $(PROGRAM) $(OBJS)
