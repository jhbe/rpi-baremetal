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

HDRS= led.h   ../common-b-plus/systemtimer.h ../common-b-plus/delay.h ../common-b-plus/gpio.h ../common-b-plus/cstubs.c ../common-b-plus/uart.c ../common-b-plus/aux.c
SRCS= led.cpp ../common-b-plus/systemtimer.c ../common-b-plus/delay.c ../common-b-plus/gpio.c ../common-b-plus/cstubs.c ../common-b-plus/uart.c ../common-b-plus/aux.c ledblink.cpp ../common-b-plus/eightthousand.s 
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
