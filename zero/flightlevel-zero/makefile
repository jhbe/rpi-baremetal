ABI=arm-unknown-eabihf
TOOLCHAIN=/home/johan/x-tools/$(ABI)/bin/$(ABI)

CC  = $(TOOLCHAIN)-gcc
GCC = $(TOOLCHAIN)-gcc
GXX = $(TOOLCHAIN)-g++
LD  = $(TOOLCHAIN)-ld
OC  = $(TOOLCHAIN)-objcopy
OD  = $(TOOLCHAIN)-objdump
NM  = $(TOOLCHAIN)-nm

CFLAGS = -ffreestanding -g -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s  -Wl,--build-id=none -Wl,-T,armelf_rpi.x

HDRS= led.h   ../../b-plus/common-b-plus/systemtimer.h ../../b-plus/common-b-plus/delay.h ../../b-plus/common-b-plus/gpio.h                                     ../../b-plus/common-b-plus/uart.h ../../b-plus/common-b-plus/aux.h ../../b-plus/common-b-plus/i2c.h mpu6050.h
SRCS= led.cpp ../../b-plus/common-b-plus/systemtimer.c ../../b-plus/common-b-plus/delay.c ../../b-plus/common-b-plus/gpio.c ../../b-plus/common-b-plus/cstubs.c ../../b-plus/common-b-plus/uart.c ../../b-plus/common-b-plus/aux.c ../../b-plus/common-b-plus/i2c.c mpu6050.c flightlevel.cpp ../common-zero/eightthousand.s 
DEPS= $(SRCS) $(HDRS) armelf_rpi.x makefile

all: flightlevel.elf kernel.img flightlevel.txt flightlevel.list flightlevel.hex

flightlevel.elf: $(DEPS)
	$(GXX) $(CFLAGS) -o $@ $(SRCS)

kernel.img: flightlevel.elf
	$(OC) $^ -O binary $@

flightlevel.hex: flightlevel.elf
	$(OC) $^ -O ihex $@

flightlevel.list: flightlevel.elf
	$(OD) -D $^ >$@

flightlevel.txt: flightlevel.elf
	$(NM) $^ >$@

clean:
	rm -rf *.o flightlevel.elf kernel.img flightlevel.txt flightlevel.list flightlevel.hex
