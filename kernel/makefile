.PHONY: all clean

SOURCE:=$(wildcard *.S) $(wildcard *.c)
OBJECT:=$(patsubst %.S,%.o,$(patsubst %.c,%.o,$(SOURCE)))

all: kernel.bin

clean:
	$(Q)rm -f $(OBJECT)
	$(Q)rm -f kernel.elf
	$(Q)rm -f kernel.bin

kernel.bin: kernel.elf
	$(Q)echo [OBJCOPY] $@
	$(Q)$(OBJCOPY) -O binary $^ $@

kernel.elf: $(OBJECT)
	$(Q)echo [LD] $@
	$(Q)$(LD) $(LD_OPT) -T kernel.ld -o $@ $^

%.o: %.S
	$(Q)echo [AS] $@
	$(Q)$(CC) $(AS_OPT) -c -o $@ $^

%.o: %.c
	$(Q)echo [CC] $@
	$(Q)$(CC) $(CC_OPT) -c -o $@ $^

