.PHONY: all loader kernel clean run

Q:=@
DBG?=0

CROSS_TOOL:=arm-none-eabi-
AS:=$(CROSS_TOOL)as
CC:=$(CROSS_TOOL)gcc
LD:=$(CROSS_TOOL)ld
OBJCOPY:=$(CROSS_TOOL)objcopy
GDB:=$(CROSS_TOOL)gdb

CC_OPT:= -g -mcpu=cortex-a9 -mlittle-endian
LD_OPT:= -nostdlib -nodefaultlibs

ifeq ($(DBG),1)
QEMU_DBG_OPT:=-s -S
endif

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
	$(Q)if [ $(DBG) -eq 1 ]; then echo "debug option specified, connect localhost:1234 with gdb"; fi
	$(Q)qemu-system-arm -nographic -m 64M -M vexpress-a9 $(QEMU_DBG_OPT) -bios loader/loader.bin

