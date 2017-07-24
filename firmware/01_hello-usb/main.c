/*
 * RUDY - the Random USB Device
 *
 * Copyright (C) 2017 Sven Gregori <sven@craplab.fi>
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see http://www.gnu.org/licenses/
 *
 *
 *
 * Example 01: Hello USB
 *      Do nothing but being a dummy USB device.
 *      Once plugged in, the device should show up in the syslog and lsusb
 *
 */
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usbconfig.h"
#include "usbdrv/usbdrv.h"

/**
 * V-USB setup callback function.
 */
uchar
usbFunctionSetup(uchar data[8] __attribute__((unused)))
{
    /* do nothing */
    return 0;
}

/**
 * V-USB read callback function
 */
uchar
usbFunctionRead(uchar *data, uchar len)
{
    /* zero the buffer and return len to indicate read was completed */
    memset(data, 0x00, len);
    return len;
}

/**
 * V-USB write callback function
 */
uchar
usbFunctionWrite(uchar *data __attribute__((unused)),
        uchar len __attribute__((unused)))
{
    /* ignore data and return 1 to indicate write was completed */
    return 1;
}


int
main(void)
{
    usbDeviceDisconnect();
    _delay_ms(300);
    usbDeviceConnect();
    usbInit();

    sei();

    while (1) {
        usbPoll();
    }

    return 0;
}

