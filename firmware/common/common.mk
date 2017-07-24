#
# RUDY - the Random USB Device
#
# Copyright (C) 2017 Sven Gregori <sven@craplab.fi>
#
# This program is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see http://www.gnu.org/licenses/
#

MCU = atmega328p
F_CPU = 12000000


OBJS += ../common/usbdrv/usbdrv.o ../common/usbdrv/usbdrvasm.o


CC = avr-gcc
OBJCOPY = avr-objcopy
SIZE = avr-size
AVRDUDE = avrdude

CFLAGS += -g -Os -std=gnu99 -I. -I../common/\
-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums \
-Wall -Wextra -Wstrict-prototypes \
-DF_CPU=$(F_CPU) -mmcu=$(MCU) 

ASFLAGS = -Wa,-adhlms=$(<:.c=.lst),-gstabs 
ASFLAGS_ASM = -Wa,-gstabs 
LDFLAGS = -Wl,-Map=$(<:.o=.map),--cref
AVRDUDE_FLAGS = -p $(MCU) -c usbasp


.PRECIOUS : %.elf %.o

all: $(PROGRAM).hex

$(PROGRAM).hex: $(PROGRAM).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@
	@$(SIZE) $^

$(PROGRAM).elf: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

.c.o:
	$(CC) -c $(CFLAGS) $(ASFLAGS) $< -o $@

.S.o:
	$(CC) -c $(CFLAGS) -x assembler-with-cpp $(ASFLAGS_ASM) $< -o $@

burn-fuse:
	# External full swing crystal oscillator, 16K CK / 14 CK + 65ms
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U lfuse:w:0xf7:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m

program:
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U flash:w:$(PROGRAM).hex

clean:
	rm -f $(OBJS)

distclean: clean
	rm -f $(OBJS:.o=.lst)
	rm -f $(OBJS:.o=.map)
	rm -f *.elf
	rm -f *.hex

.PHONY : all clean distclean program

