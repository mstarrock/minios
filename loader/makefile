.PHONY: all clean

SOURCE:=loader.S

all: loader.bin

clean:
	$(Q)rm -f loader.bin
	$(Q)rm -f loader.o
	$(Q)rm -f loader.elf

loader.bin: loader.elf
	$(Q)$(OBJCOPY) -O binary $^ $@

loader.elf: loader.o
	$(Q)$(LD) $(LD_OPT) -T loader.ld -o $@ $^

%o: %S
	$(Q)$(AS) $(CC_OPT) -c -o $@ $^

