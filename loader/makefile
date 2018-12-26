.PHONY: all clean

SOURCE:=$(wildcard *.S) $(wildcard *.c)
OBJECT:=$(patsubst %.S,%.o,$(patsubst %.c,%.o,$(SOURCE)))

all: loader.bin

clean:
	$(Q)rm -f $(OBJECT)
	$(Q)rm -f loader.elf
	$(Q)rm -f loader.bin
	$(Q)rm -f loader.ld

loader.bin: loader.elf
	$(Q)echo [OBJCOPY] $@
	$(Q)$(OBJCOPY) -O binary $^ $@

loader.elf: loader.ld $(OBJECT)
	$(Q)echo [LD] $@
	$(Q)$(LD) $(LD_OPT) -T loader.ld -o $@ $(OBJECT)

%.o: %.S
	$(Q)echo [AS] $@
	$(Q)$(AS) $(CFLAGS) $(AS_OPT) -c -o $@ $^

%.o: %.c
	$(Q)echo [CC] $@
	$(Q)$(CC) $(CC_OPT) $(CFLAGS) -c -o $@ $^

%.ld: %.lds
	$(Q)echo [CPP] $@
	$(Q)$(CPP) $(CFLAGS) -E -x c $^ | grep -v '^#' > $@

.INTERMEDIATE: loader.ld
