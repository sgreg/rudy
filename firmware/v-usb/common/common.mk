#
# RUDY - the Random USB Device
# Common Makefile definitions for V-USB examples
#
# Copyright (C) 2020 Sven Gregori <sven@craplab.fi>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

MCU = atmega328p
F_CPU = 12000000


# location to common files (i.e. the directory this common.mk file
# here is located) relative to the example project source files.
# If not defined in the project's Makefile, fall back to ../common
COMMON ?= ../common

USBDRV_SRC = $(COMMON)/usbdrv/usbdrv.c
USBDRV = usbdrv.o
USBDRVASM_SRC = $(COMMON)/usbdrv/usbdrvasm.S
USBDRVASM = usbdrvasm.o

USBCONFIG = usbconfig-rudy.h

ifeq (,$(wildcard $(USBCONFIG)))
USBCONFIG = $(COMMON)/usbconfig-rudy.h
endif

BUILD_OBJS = $(OBJS) $(USBDRV) $(USBDRVASM)


CC = avr-gcc
OBJCOPY = avr-objcopy
SIZE = avr-size
AVRDUDE = avrdude

INCLUDES = -I. -I$(COMMON)

CFLAGS += -g -Os -std=gnu99 $(INCLUDES)\
-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums \
-Wall -Wextra -Wstrict-prototypes \
-DF_CPU=$(F_CPU) -mmcu=$(MCU) 

ASFLAGS = -Wa,-adhlms=$(<:.c=.lst),-gstabs 
ASFLAGS_ASM = -Wa,-gstabs 
LDFLAGS = -Wl,-Map=$(PROGRAM).map,--cref

# Include programmer.mk relative to $(COMMON) to make sure paths are
# correct in case there are subdirectories (i.e. the reason $(COMMON)
# exists in the first place)
include $(COMMON)/../../programmer.mk
AVRDUDE_FLAGS = -p $(MCU) $(AVRDUDE_PROGRAMMER)


.PRECIOUS : %.elf %.o

all: $(PROGRAM).hex

$(PROGRAM).hex: $(PROGRAM).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@
	@$(SIZE) $^

$(PROGRAM).elf: $(BUILD_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

.c.o: $(USBCONFIG)
	$(CC) -c $(CFLAGS) $(ASFLAGS) $< -o $@

.S.o:
	$(CC) -c $(CFLAGS) -x assembler-with-cpp $(ASFLAGS_ASM) $< -o $@

$(USBDRV): $(USBDRV_SRC) $(USBCONFIG)
	$(CC) -c $(CFLAGS) $< -o $@

$(USBDRVASM): $(USBDRVASM_SRC) $(USBCONFIG)
	$(CC) -c $(CFLAGS) -x assembler-with-cpp $(ASFLAGS_ASM) $< -o $@

burn-fuse:
	# External full swing crystal oscillator, 16K CK / 14 CK + 65ms
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U lfuse:w:0xf7:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m

program:
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U flash:w:$(PROGRAM).hex

clean:
	rm -f $(BUILD_OBJS)
	rm -f $(OBJS:.o=.lst)

distclean: clean
	rm -f $(PROGRAM).elf $(PROGRAM).hex $(PROGRAM).map

.PHONY : all clean distclean program

