.PHONY: all clean

SOURCE:=$(wildcard *.S) $(wildcard *.c)
OBJECT:=$(patsubst %.S,%.o,$(patsubst %.c,%.o,$(SOURCE)))

all: kernel.bin

clean:
	$(Q)rm -f $(OBJECT)
	$(Q)rm -f kernel.elf
	$(Q)rm -f kernel.bin
	$(Q)rm -f kernel.ld

kernel.bin: kernel.elf
	$(Q)echo [OBJCOPY] $@
	$(Q)$(OBJCOPY) -O binary $^ $@

kernel.elf: kernel.ld $(OBJECT)
	$(Q)echo [LD] $@
	$(Q)$(LD) $(LD_OPT) -T kernel.ld -o $@ $(OBJECT)

%.o: %.S
	$(Q)echo [AS] $@
	$(Q)$(CC) $(AS_OPT) $(CFLAGS) -c -o $@ $^

%.o: %.c
	$(Q)echo [CC] $@
	$(Q)$(CC) $(CC_OPT) $(CFLAGS) -c -o $@ $^

%.ld: %.lds
	$(Q)echo [CPP] $@
	$(Q)$(CPP) $(CFLAGS) -E -x c $^ | grep -v '^#' > $@

.INTERMEDIATE: kernel.ld
