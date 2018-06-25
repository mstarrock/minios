# minios
bare metal OS implementation for ARM

## Running the tests
Execute "run" recipe by make will invoke qemu to start testing your code.

If you need gdb for debugging then specify DBG=1 option to "run" recipe, and qemu will halt the execution and wait for gdb connection from localhost:1234.

## Reference
* Documents
  * [ARM CoreTile Express A9×4 Technical Reference Manual](http://infocenter.arm.com/help/topic/com.arm.doc.dui0448i/DUI0448I_v2p_ca9_trm.pdf)
  * [ARM Motherboard Express µATX Technical Reference Manual](http://infocenter.arm.com/help/topic/com.arm.doc.dui0447j/DUI0447J_v2m_p1_trm.pdf)
  * [PrimeCell UART (PL011) Technical Reference Manual](http://infocenter.arm.com/help/topic/com.arm.doc.ddi0183g/DDI0183G_uart_pl011_r1p5_trm.pdf)
