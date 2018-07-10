.PHONY: all clean

SOURCE:=startup.S kernel.c

all: kernel.bin

clean:
	$(Q)rm -f startup.o
	$(Q)rm -f kernel.o
	$(Q)rm -f kernel.elf
	$(Q)rm -f kernel.bin

kernel.bin: kernel.elf
	$(Q)echo [OBJCOPY] $@
	$(Q)$(OBJCOPY) -O binary $^ $@

kernel.elf: startup.o kernel.o
	$(Q)echo [LD] $@
	$(Q)$(LD) $(LD_OPT) -T kernel.ld -o $@ $^

%.o: %.S
	$(Q)echo [AS] $@
	$(Q)$(AS) $(AS_OPT) -c -o $@ $^

%.o: %.c
	$(Q)echo [CC] $@
	$(Q)$(CC) $(CC_OPT) -c -o $@ $^

