# Summary

This is a collection of baremetal projects for various Raspberry Pi models.

# JtagBoot

The JtagBoot projects builds an image that, when copied onto the SD card, will
cause the RPI to configure some of the GPIO for JTAG usage. That in turn enables
another RPI to act as a JTAG server and can, using OpenOCD, connect to the booted
target RPI and load new images without removing the SD card. It also enables
the same server RPI to use GDB to debug the Target RPI.

# Setup

## Toolchain

The code is compiled using the crosstools-ng cross compiler toolchain. To set it
up on Debian Stretch:

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

To build the debugger as well:

    ct-ng menuconfig

...

Now build a toolchain for arm-unknown-eabi with gdb support:

    cd
    mkdir staging
    cd staging
    ct-ng arm-unknown-eabi
    ct-ng menuconfig

and enable GDB in "Debug facilities". Then:

    ct-ng build

The last step will take a while. When done, the new compilers can be found in ~/x-tools/arm-unknown-eabi/bin.

