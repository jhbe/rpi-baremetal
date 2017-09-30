# Summary

This is a collection of (NetBeans 8.2) baremetal projects for various Raspberry
Pi models.

The *JtagBoot* projects builds an image that, when copied onto the SD card, will
cause the RPI to configure some of the GPIO for JTAG usage. That in turn enables
another RPI to act as a JTAG server and can, using OpenOCD, connect to the booted
target RPI and load new images without removing the SD card. It also enables
the same server RPI to use GDB to debug the Target RPI. See the README.md in the
JtagBoot folders for details.

The *LebBlink* project illustrates the use of C++ classes and standard libraries (newlib);
it does NOT use -nostdlib, -nodefaultfiles nor -nostartfiles.

# Terminology

Three computers are required:

- The Debian based development PC. Not a Raspberry Pi.

- The *Server RPI* runs Debian and will have OpenOCD installed on it. It is connected 
through five P1 header wires to...

- The *Target* RPI. This is the baremetal RPI. It will boot of an SD card with just
enough to run the JtagBoot program once.

# Setup

## Toolchain

The code is compiled using the crosstools-ng cross compiler toolchain on the Development
PC. To set it up on Debian Stretch with gdb support:

    sudo apt-get install gperf bison flex gawk libtool libtool-bin texinfo libncurses5-dev help2man automake gcc g++ subversion python-dev
    wget http://crosstool-ng.org/download/crosstool-ng/crosstool-ng-1.23.0.tar.bz2
    tar -xjf crosstool-ng-1.23.0.tar.bz2
    cd crosstool-ng-1.23.0/
    sudo mkdir ~/cross
    ./configure --prefix=~/cross
    make
    sudo make install
    sudo cp ct-ng.comp /etc/bash_completion.d/

Add to ~/.bashrc and restart the terminal to get the new path: 

    export PATH=~/cross/bin:$PATH

Build a toolchain for arm-unknown-eabi with gdb support:

    cd
    mkdir staging
    cd staging
    ct-ng arm-unknown-eabi
    ct-ng menuconfig

and enable GDB in "Debug facilities". Then:

    ct-ng build

The last step will take a while. When done, the new compilers can be found in
~/x-tools/arm-unknown-eabi/bin.

## OpenOCD

Install OpenOCD on the Server RPI:

    wget http://sourceforge.net/projects/openocd/files/openocd/0.10.0/openocd-0.10.0.tar.bz2
    tar -xf openocd-0.10.0.tar.bz2
    cd openocd-0.10.0
    sudo apt-get install texinfo texlive git autoconf libtool make pkg-config libusb-1.0-0 libusb-1.0-0-dev telnet
    ./configure --enable-bcm2835gpio --enable-sysfsgpio
    make
    sudo make install

Connect the Server and Target RPIs. The numbers below are PI header numbers (not GPIO numbers).

| Signal | Server | Target | Alt | Notes |
|--------|--------|--------|-----|-------|
| GND    | 6      | 6      |     |       |
| TCK    | 23     | 33     |  5  |       |
| TMS    | 22     | 32     |  5  |       |
| TDI    | 19     | 37     |  4  |       |
| TDO    | 21     | 29     |  5  |       | 
| TRST   | (26)   | (15)   |  4  | Not required. Internal pull-up de-asserts. *But note that GPIO 22 cannot be used for anything else!* |

The JtagBoot program sets up the Alt-mode for there pins on the Target RPI.

Add a file /usr/local/share/openocd/scripts/target/rpi.cfg:

    adapter_khz 1000
    adapter_nsrst_delay 400
    reset_config trst_only
    
    if { [info exists CHIPNAME] } {
     set _CHIPNAME $CHIPNAME
    } else {
     set _CHIPNAME rspi
    }
    
    if { [info exists CPU_TAPID] } {
     set _CPU_TAPID $CPU_TAPID
    } else {
     set _CPU_TAPID 0x07b7617f
    }
    
    jtag newtap $_CHIPNAME arm -irlen 5 -expected-id $_CPU_TAPID
    set _TARGETNAME $_CHIPNAME.arm
    target create $_TARGETNAME arm11 -chain-position $_TARGETNAME
    rspi.arm configure -event gdb-attach { halt }

Different PIs have different configuration needs:

    # Raspi2 and Raspi3 peripheral_base address
    bcm2835gpio_peripheral_base 0x3F000000
    
    # Raspi1 peripheral_base address
    bcm2835gpio_peripheral_base 0x20000000
    
    # Raspi3 BCM2837 (1200Mhz): 
    bcm2835gpio_speed_coeffs 194938 48
    
    # Raspi2 BCM2836 (900Mhz):
    bcm2835gpio_speed_coeffs 146203 36
    
    # Raspi1 BCM2835: (700Mhz)
    bcm2835gpio_speed_coeffs 113714 28

## Jtag Boot

- Build the JtagBoot project for the correct RPI.
- Copy the kernel.img, bootcode.bin and start.elf to an SD card.
- Boot the Target RPI of that SD card.

The Target RPI is now ready to act as a JTAG device. To connect to it, on the
Server RPI:

    cd openocd-0.10.0/
    sudo openocd -f interface/sysfsgpio-raspberrypi.cfg -f target/rpi.cfg

## GDB

Create a .gdbinit in ~ on the Development PC:

    set auto-load safe-path /

Create a .gdbinit in the project working directory if it is not already there on the Development PC:

    target remote 192.168.0.11:3333
    set remotetimeout 10

# Running 

- Copy the just-built kernel.img from the Development PC to the Target RPI:

    scp kernel.img pi@192.168.0.11:/home/pi

Connect to the OpenOCD from the Development PC and transfer it to the Target RPI:

    telnet 192.168.0.11 3333
    halt
    load_image ../kernel.img 0x8000 bin
    resume

# Debugging

Run GDB on the Development PC. Provide the .elf file that was built for the project:

    ~/x-tools/armv6-rpi-linux-gnueabi/bin/armv6-rpi-linux-gnueabi-gdb -tui blah.elf

Commands:

    step        (s)
    next        (n)
    continue    (c)
    finish      (fin)  runs until the end of the current function
    load
    print       (p)
    display
    
    break main
    break main.c:34
    
    info br
    delete <br>
