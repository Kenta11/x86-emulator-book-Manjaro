TARGET = boots
OBJS = main.o assemble.o fat.o

CC = gcc

.PHONY: all clean
all : $(TARGET)

$(TARGET) : $(OBJS)
	gcc $^ -o $@

%.o : %.c
	gcc -c -O2 -Wall -Wextra -o $@ $<

clean :
	rm -f $(TARGET) *.o
