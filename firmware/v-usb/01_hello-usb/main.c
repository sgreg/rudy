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
 *      ..that's really it.
 *
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usbconfig.h"
#include "usbdrv/usbdrv.h"

/**
 * V-USB setup callback function.
 *
 * Called from within V-USB itself to handle a SETUP packet.
 * This device here doesn't do anything, so neither will this function here,
 * but V-USB references it either way, so it needs to exist.
 */
uchar
usbFunctionSetup(uchar data[8] __attribute__((unused)))
{
    /* do nothing */
    return 0;
}

/*
 * Let's get going..
 */
int
main(void)
{
    /* Disconnect and reconnect USB to enforce device re-enumeration */
    usbDeviceDisconnect();
    _delay_ms(300);
    usbDeviceConnect();

    /* Set up USB and enable interrupts */
    usbInit();
    sei();

    /* Loop forever */
    while (1) {
        /*
         * usbPoll() needs to be called periodically (at least every 50ms),
         * or else the USB connection times out and is dropped. But nothing
         * else is going on in here, so we can easily delay a little while.
         */
        usbPoll();
        _delay_ms(30);
    }

    return 0;
}

