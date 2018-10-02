# set debug target to qemu
target remote localhost:1234

# load all symbol table
file kernel/kernel.elf
add-symbol-file loader/loader.elf 0

# default break point
b _start

