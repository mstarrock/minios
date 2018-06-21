# minios
bare metal OS implementation for ARM

## Running the tests
Execute "run" recipe by make will invoke qemu to start testing your code.

If you need gdb for debugging then specify DBG=1 option to "run" recipe, and qemu will halt the execution and wait for gdb connection from localhost:1234.
