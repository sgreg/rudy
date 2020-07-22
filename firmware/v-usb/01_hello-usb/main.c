/*
 * RUDY - the Random USB Device
 * Hello USB V-USB example
 *
 * Copyright (C) 2020 Sven Gregori <sven@craplab.fi>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
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

