.PHONY: all loader kernel clean run

Q:=@

CROSS_TOOL:=arm-none-eabi-
AS:=$(CROSS_TOOL)as
CC:=$(CROSS_TOOL)gcc
LD:=$(CROSS_TOOL)ld
OBJCOPY:=$(CROSS_TOOL)objcopy
GDB:=$(CROSS_TOOL)gdb

CC_OPT:= -g -mcpu=cortex-a9 -march=arm -mlittle-endian
LD_OPT:= -nostdlib -nodefaultlibs

export

all: loader

loader:
	$(Q)make -C loader

clean:
	$(Q)make -C loader/ clean

run: clean all
	$(Q)echo
	$(Q)echo "start runing qemu"
	$(Q)echo "NOTE: use ctrl+a x to exit"
	$(Q)qemu-system-arm -nographic -m 64M -M vexpress-a9 -s -S -bios loader/loader.bin

