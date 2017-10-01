# LedBlink-B-Plus

The purpose of this LED-blinking (GPIO 16, greenA ACT LED on a Zero) application is to illustrate
how to use the arm-unknown-eabi toolchain, standard libraries (newlib) and C++ classes.
In particular, it does NOT use -nostdlib, -nodefaultfiles or -nostartfiles.

Instead, it uses a slightly tweeked copy of the standard armelf.x linker script file. An
additional section called "eight" (for eight thousand, or the RPI start address 0x8000)
was inserted BEFORE the original .init section:

      .init           :
      {
        *(.eight)
        KEEP (*(SORT_NONE(.init)))
      }
    
The purpose is to be able to insert code first in the text section. This code will end up
address 0x8000 and all we need to do that the linker script doesn't already do, is to call
_start (file eightthousand.s):

    .section .eight
    .global _eightstart
    _eightstart:
    	bl _start

All we need is to include the eightthousand.s file and the armelf_rpi.x (through
the makefile) when we build.

Two changes to the linker script (armelf_rpi.x)) with respect to the stack were
also necessary. First the stack size was increased. Rather than starting at
0x80000 it now starts at 0x180000. Some 20k of stack seems to have been used by
the time we reach main(), so more was needed.

The second change was the addition of the \_\_stack linker script variable (note the double
underscores). This enables the .Lstack symbol to be initialised properly and not merely use a
default value (of 0x80000). See /home/johan/cross/.build/src/newlib-2.2.0/libgloss/arm/crt0.S.
