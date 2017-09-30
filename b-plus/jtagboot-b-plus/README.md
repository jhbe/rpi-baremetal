# Summary

This tiny program sets the JTAG GPIO (TCK, TMS, TDI, TDO, TRST) to ALT4, thus making them
available on the RPI 40 pin connector on a RPI B+. A pull-up resistor is attached to TRST,
so it can be left unattached if not used.

The generated kernel.img, along with start.elf and bootcode.bin, should go on the first
partition on the SD card. That partition must be FAT32. Once the RPI has booted of it, the
real application can be loaded using OpenOCD.

The Host is the RPI acting as the debugger (OpenOCD). The Target is the bare metal RPI.
The numbers below are PI header pins, NOT GPIO numbers:

    Host             Target
    =======================
      6 ----  GND ----  6
     23 ----  TCK ---- 22
     22 ----  TMS ---- 13
     19 ----  TDI ---- 37
     21 ----  TDO ---- 18

# Notes

The order of the source files in the Makefile matters; the start.s must be first
or else the stack pointer won't be initialized.
