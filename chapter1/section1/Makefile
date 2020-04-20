TARGET = casm-c-sample.bin

CC = gcc
LD = ld
CFLAGS += -O0 -march=i386 -m32 -nostdlib -fno-asynchronous-unwind-tables -g -fno-stack-protector -fno-pie
LDFLAGS += -m elf_i386 --entry=func --oformat=binary

.PHONY: all
all : $(TARGET)
	hexdump -v -e'/1 "%02x "' $(TARGET)

%.bin : %.o
	$(LD) $(LDFLAGS) -o $@ $<

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean :
	rm -f $(TARGET)
