ABI=arm-unknown-eabi
TOOLCHAIN=/home/johan/x-tools/$(ABI)/bin/$(ABI)

CC  = $(TOOLCHAIN)-gcc
GCC = $(TOOLCHAIN)-gcc
GXX = $(TOOLCHAIN)-g++
LD  = $(TOOLCHAIN)-ld
OC  = $(TOOLCHAIN)-objcopy
OD  = $(TOOLCHAIN)-objdump
NM  = $(TOOLCHAIN)-nm

CFLAGS = -ffreestanding -g -mfpu=vfp -mfloat-abi=soft -march=armv6zk -mtune=arm1176jzf-s  -Wl,--build-id=none -Wl,-T,armelf_rpi.x

HDRS= led.h   ../../b-plus/common-b-plus/systemtimer.h ../../b-plus/common-b-plus/delay.h ../../b-plus/common-b-plus/gpio.h                                     ../../b-plus/common-b-plus/uart.h ../../b-plus/common-b-plus/aux.h
SRCS= led.cpp ../../b-plus/common-b-plus/systemtimer.c ../../b-plus/common-b-plus/delay.c ../../b-plus/common-b-plus/gpio.c ../../b-plus/common-b-plus/cstubs.c ../../b-plus/common-b-plus/uart.c ../../b-plus/common-b-plus/aux.c ledblink.cpp ../../b-plus/common-b-plus/eightthousand.s 
DEPS= $(SRCS) $(HDRS) armelf_rpi.x makefile

all: ledblink.elf kernel.img ledblink.txt ledblink.list ledblink.hex

ledblink.elf: $(DEPS)
	$(GXX) $(CFLAGS) -o $@ $(SRCS)

kernel.img: ledblink.elf
	$(OC) $^ -O binary $@

ledblink.hex: ledblink.elf
	$(OC) $^ -O ihex $@

ledblink.list: ledblink.elf
	$(OD) -D $^ >$@

ledblink.txt: ledblink.elf
	$(NM) $^ >$@

clean:
	rm -rf *.o ledblink.elf kernel.img ledblink.txt ledblink.list ledblink.hex
