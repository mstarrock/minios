.PHONY: all loader kernel clean run

Q:=@
DBG?=0

CROSS_TOOL:=arm-none-eabi-
AS:=$(CROSS_TOOL)as
CC:=$(CROSS_TOOL)gcc
LD:=$(CROSS_TOOL)ld
OBJCOPY:=$(CROSS_TOOL)objcopy
GDB:=$(CROSS_TOOL)gdb

CC_OPT:= -g -mcpu=cortex-a9 -mlittle-endian -fno-builtin
AS_OPT:= -g -mcpu=cortex-a9 -mlittle-endian
LD_OPT:= -nostdlib -nodefaultlibs -nobuildin

ifeq ($(DBG),1)
QEMU_DBG_OPT:=-s -S
endif

export

all: loader kernel
	$(Q)echo [GEN] sys.img
	$(Q)cp loader/loader.bin ./sys.img
	$(Q)truncate -s 4K ./sys.img
	$(Q)cat kernel/kernel.bin >> sys.img

loader:
	$(Q)make -C loader

kernel:
	$(Q)make -C kernel

clean:
	$(Q)make -C loader/ clean
	$(Q)make -C kernel/ clean
	$(Q)rm -f ./sys.img

run: clean all
	$(Q)echo
	$(Q)echo "start runing qemu"
	$(Q)echo "NOTE: use ctrl+a x to exit"
	$(Q)if [ $(DBG) -eq 1 ]; then echo "debug option specified, connect localhost:1234 with gdb"; fi
	$(Q)QEMU_AUDIO_DRV=none qemu-system-arm -nographic -m 64M -M vexpress-a9 $(QEMU_DBG_OPT) -bios sys.img

dbg:
	$(Q)if [ -f init.gdb ];then $(GDB) --command=init.gdb; else $(GDB); fi

