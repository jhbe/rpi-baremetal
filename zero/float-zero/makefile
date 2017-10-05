ABI=arm-unknown-eabihf
TOOLCHAIN=/home/johan/x-tools/$(ABI)/bin/$(ABI)

CC  = $(TOOLCHAIN)-gcc
GCC = $(TOOLCHAIN)-gcc
GXX = $(TOOLCHAIN)-g++
LD  = $(TOOLCHAIN)-ld
OC  = $(TOOLCHAIN)-objcopy
OD  = $(TOOLCHAIN)-objdump
NM  = $(TOOLCHAIN)-nm

CFLAGS = -ffreestanding -g -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s  -Wl,--build-id=none -Wl,-T,armhf_rpi.x

HDRS=                                     ../../b-plus/common-b-plus/uart.h ../../b-plus/common-b-plus/gpio.h ../../b-plus/common-b-plus/aux.h
SRCS= ../../b-plus/common-b-plus/cstubs.c ../../b-plus/common-b-plus/uart.c ../../b-plus/common-b-plus/gpio.c ../../b-plus/common-b-plus/aux.c float.cpp eightthousand.s 
DEPS= $(SRCS) $(HDRS) armhf_rpi.x makefile

all: float.elf kernel.img float.txt float.list float.hex

float.elf: $(DEPS)
	$(GXX) $(CFLAGS) -o $@ $(SRCS)

kernel.img: float.elf
	$(OC) $^ -O binary $@

float.hex: float.elf
	$(OC) $^ -O ihex $@

float.list: float.elf
	$(OD) -D $^ >$@

float.txt: float.elf
	$(NM) $^ >$@

clean:
	rm -rf *.o float.elf kernel.img float.txt float.list float.hex
