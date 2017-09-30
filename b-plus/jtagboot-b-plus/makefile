#!/bin/make -f

ABI=arm-unknown-eabi
TOOLCHAIN=/home/johan/x-tools/$(ABI)/bin/$(ABI)

CC = $(TOOLCHAIN)-gcc
OC = $(TOOLCHAIN)-objcopy
OD = $(TOOLCHAIN)-objdump
NM = $(TOOLCHAIN)-nm

CFLAGS = -march=armv6zk -nostdlib -nostartfiles -ffreestanding -Wl,-T,rpi.x -Wl,--build-id=none

HDRS=                                      ../common-b-plus/gpio.h 
SRCS=  ../common-b-plus/start.s jtagboot.c ../common-b-plus/gpio.c

all: kernel.img jtagboot.hex jtagboot.list jtagboot.txt

jtagboot.elf: $(HDRS) $(SRCS) rpi.x makefile
	$(CC) $(CFLAGS) -o $@ $(SRCS)

kernel.img: jtagboot.elf
	$(OC) $^ -O binary $@
	
jtagboot.hex: jtagboot.elf
	$(OC) $^ -O ihex $@

jtagboot.list: jtagboot.elf
	$(OD) -D $^ >$@

jtagboot.txt: jtagboot.elf
	$(NM) $^ >$@

clean:
	rm -rf *.o kernel.*
