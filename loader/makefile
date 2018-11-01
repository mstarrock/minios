.PHONY: all clean

SOURCE:=$(wildcard *.S) $(wildcard *.c)
OBJECT:=$(patsubst %.S,%.o,$(patsubst %.c,%.o,$(SOURCE)))

all: loader.bin

clean:
	$(Q)rm -f $(OBJECT)
	$(Q)rm -f loader.elf
	$(Q)rm -f loader.bin

loader.bin: loader.elf
	$(Q)echo [OBJCOPY] $@
	$(Q)$(OBJCOPY) -O binary $^ $@

loader.elf: $(OBJECT)
	$(Q)echo [LD] $@
	$(Q)$(LD) $(LD_OPT) -T loader.ld -o $@ $^

%.o: %.S
	$(Q)echo [AS] $@
	$(Q)$(AS) $(AS_OPT) -c -o $@ $^

%.o: %.c
	$(Q)echo [CC] $@
	$(Q)$(CC) $(CC_OPT) -c -o $@ $^

