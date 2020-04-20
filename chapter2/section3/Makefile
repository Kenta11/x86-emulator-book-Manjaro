TARGET = px86
PROGRAM = helloworld.bin
OBJS = main.o

CC = gcc
CFLAGS += -O2 -Wall -Wextra

.PHONY: all run
all : $(TARGET)

run : $(TARGET) $(PROGRAM)
	./$(TARGET) $(PROGRAM)

%.bin : %.asm
	nasm -f bin -o $@ $<


$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) $(OBJS) $(PROGRAM)
