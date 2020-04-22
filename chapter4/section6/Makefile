TARGET = pbr.bin
ASM = nasm
QEMU = qemu-system-x86_64

.PHONY: all clean
all : $(TARGET)
	$(QEMU) $<

%.bin : %.asm
	nasm $< -o $@

clean :
	rm -f $(TARGET)
