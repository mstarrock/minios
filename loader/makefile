.PHONY: all clean

SOURCE:=loader.S

all: loader.bin

clean:
	$(Q)rm -f loader.o
	$(Q)rm -f loader_c.o
	$(Q)rm -f loader.elf
	$(Q)rm -f loader.bin

loader.bin: loader.elf
	$(Q)echo [OBJCOPY] $@
	$(Q)$(OBJCOPY) -O binary $^ $@

loader.elf: loader.o loader_c.o
	$(Q)echo [LD] $@
	$(Q)$(LD) $(LD_OPT) -T loader.ld -o $@ $^

%.o: %.S
	$(Q)echo [AS] $@
	$(Q)$(AS) $(AS_OPT) -c -o $@ $^

%.o: %.c
	$(Q)echo [CC] $@
	$(Q)$(CC) $(CC_OPT) -c -o $@ $^

