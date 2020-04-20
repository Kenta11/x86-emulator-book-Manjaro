TARGET = evil.o

CC = gcc
CFLAGS += -O0 -g -march=i386 -m32 -nostdlib -fno-asynchronous-unwind-tables -g -fno-stack-protector -fno-pie

.PHONY: all
all : $(TARGET)
	objdump -d -S -M intel $(TARGET)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean :
	rm -f $(TARGET)
