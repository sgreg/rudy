/*
 * RUDY - the Random USB Device
 * USB LED V-USB example - Device side firmware
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
 * Example 02: USB LED
 *      Custom device class to control an LED via host-side application.
 *
 *                                         __  __
 *                                       -|1 \/  |-
 *                                       -|      |-
 *                                       -|      |-
 *                                       -|      |-
 *                                       -|      |-
 *                                       -|      |-
 *                                       -|      |-
 *      .----------------------------GND--|8     |-
 *      |                                -|      |-
 *      |      | /|      _______         -|      |-
 *      '------|( |-----|   R   |----PD5--|11    |-
 *             | \|     '-------'        -|      |-
 *                                       -|      |-
 *                                       -|      |-
 *                                        '------'
 *
 * Connect resistor and LED from PD5 (pin 11) to GND (pin 8)
 *
 * Value for R depends on the supply voltage (3.3V or 5.0V) and the LED itself.
 * If in doubt, somewhere around 120 Ohm should probably do for a first test.
 *
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usbconfig.h"
#include "usbdrv/usbdrv.h"

/* LED commands, need to be in sync with the host side */
#define CMD_LED_ON  0x01
#define CMD_LED_OFF 0x02
#define CMD_LED_PWM 0x03
#define CMD_GET_PWM 0x04

/* LED port / pin definition, expects LED at PD5 */
#define LED_DDR  DDRD
#define LED_PORT PORTD
#define LED_PIN  PORTD5


/** Flag to track whether PWM is currently ongoing or not */
static uint8_t pwm_active;

/**
 * Buffer to store the currently set PWM value as hex string.
 * Buffer size is 2 bytes to store a single byte value as a string.
 */
static uint8_t pwm_value[2];


/**
 * Set the PWM value buffer to the given value.
 *
 * The value is taken as integer and written as string to the pwm_value
 * buffer. Since the value is a single byte, the buffer is two bytes to
 * represent it as hex value. Note that the buffer isn't zero-terminated
 * as the usbFunctionSetup() function will only send 2 bytes anyway.
 *
 * @param value Integer value to store
 */
static void set_pwm_value_string(uint8_t value)
{
    static uint8_t hex[] = "0123456789abcdef";
    pwm_value[0] = hex[(value >> 4) & 0x0f];
    pwm_value[1] = hex[value & 0x0f];
}


/**
 * Setup 8bit timer to Fast PWM mode with the given value.
 *
 * The given value sets the timer0 output compare register,
 * so the LED will be
 *  - on  for the counting duration of 0 .. value
 *  - off for the counting duration of value .. 255
 * or in other words, the higher value, the brighter the LED.
 *
 * @param val Output compare value
 */
void
timer0_init_pwm(uint8_t value)
{
    if (!pwm_active) {
        /*  PWM phase correct (mode 5) */
        TCCR0A = (1 << COM0B1) | (1 << WGM02) | (1 << WGM00);
        /* Prescaler 256 */
        TCCR0B = (1 << CS02);
    }
    /* Set output compare register to new value */
    OCR0B = value;

    /* Set PWM state tracking flag */
    pwm_active = 1;

    /* Store new PWM value in the buffer */
    set_pwm_value_string(value);
}

/**
 * Stop timer0 and implicity turn LED off (if PWM is ongoing).
 */
void
timer0_stop(void)
{
    if (pwm_active) {
        /* Zero output compare value */
        OCR0B = 0;
        /* Normal timer mode, and set PD5 to regular GPIO */
        TCCR0A = 0;
        /* Prescaler 0, i.e clock off */
        TCCR0B = 0;

        /* Clear PWM state tracking flag */
        pwm_active = 0;

        /* Zero PWM value string */
        set_pwm_value_string(0x00);
    }
}


/**
 * V-USB setup callback function.
 *
 * Called from within V-USB when the host requests as setup transaction.
 * As this here acts as a non-standard, vendor-specific USB device class,
 * this is sent for every device control transfer, which is essentially
 * the way the host-side control application actually communicates with
 * the device itself here.
 *
 * For more information, check its documentation in usbdrv.h 
 *
 * @param data Setup data
 */
uchar
usbFunctionSetup(uchar data[8])
{
    /*
     * Cast given raw data to usbRequest_t structure.
     *
     * The struct itself is the main data structure for any communcation
     * between the host and device for a custom class device like this.
     * On the host side, libusb's control transfer messages uses the exact
     * same content that ends up in the usbRequest_t here / is sent back.
     *
     * The struct is defined in common/usbdrv/usbdrv.h and further explained
     * in the V-USB wiki: http://vusb.wikidot.com/driver-api
     *
     * Let's have a quick look to make more sense out of this function here:
     * 
     *  typedef struct usbRequest{
     *      uchar       bmRequestType;
     *      uchar       bRequest;
     *      usbWord_t   wValue;
     *      usbWord_t   wIndex;
     *      usbWord_t   wLength;
     *  }usbRequest_t;
     *
     * bmRequestType - The nature of the request itself, e.g. who communicates
     *                 with whom (host->device or device->host).
     *                 Content is a bit-mask (bitfield), hence the "bm" prefix
     *
     * bRequest      - The request itself, in this case it's whatever we want
     *                 it to be, e.g. CMD_LED_ON.
     *                 Content is a byte value, hence the "b" prefix
     *
     * wValue        - For custom class devices, this doesn't have any fixed
     *                 meaning, and we can abuse it for any sending arbitrary
     *                 data between host and device, e.g. the PWM value in
     *                 the CMD_LED_PWM and CMD_GET_PWM bRequests.
     *                 Content is a 16-bit word value, hence the "w" prefix
     *
     * wIndex        - Same as wValue in case of custom class devices, but
     *                 unused in this example code. It could provide another
     *                 aribtrary 16-bit value if needed.
     *                 Content is a 16-bit word value, hence the "w" prefix
     *
     * wLength       - Length in bytes of additional data if there is a data
     *                 transfer included. When sending data to the device
     *                 and those 32 bit we can utilize via the wValue and
     *                 wIndex parameters aren't enough, or when sending data
     *                 back to the host, that data is transferred separately
     *                 and both sides need to know the size of that data.
     *                 This LED example makes briefly use of that in the
     *                 CMD_GET_PWM request - check below for details. Other
     *                 ways to make use of that are implemented and shown
     *                 in the 03_caesar example code.
     *                 Content is a 16-bit word value, hence the "w" prefix
     */
    usbRequest_t *rq = (void *) data;

    /* Check and handle request type */
    switch (rq->bRequest) {
        case CMD_LED_ON:
            /*
             * Turn LED on.
             *
             * From USB side, there's not much to this, the request has no
             * additional data. Simply toggle the output pin, and stop the
             * PWM timer if necessary.
             */
            timer0_stop();
            LED_PORT |= (1 << LED_PIN);
            break;

        case CMD_LED_OFF:
            /*
             * Turn LED off.
             *
             * Same as the CMD_LED_ON request, nothing further to handle
             * from USB point of view, so just toggle the pin and also stop
             * the PWM timer if necessary.
             */
            timer0_stop();
            LED_PORT &= ~(1 << LED_PIN);
            break;

        case CMD_LED_PWM:
            /*
             * Set LED to given PWM value.
             *
             * PWM value itself is sent in the rq->wValue field.
             * As stated above, the wValue parameter is a 16-bit wide word
             * value, but we only use an 8-bit timer here, so therefore only
             * the lower 8 bits will be used, and everything else is ignored.
             * 
             * Note that we could also use rq->wValue.bytes[0] instead of
             * AND'ing rq->wValue.word with 0xff, but personally, the latter
             * one feels more explicit and obvious than the former, as it
             * doesn't require to consider byte order.
             */
            timer0_init_pwm((rq->wValue.word & 0xff));
            break;

        case CMD_GET_PWM:
            /*
             * Return the current pwm_value string.
             *
             * The request itself will have the wLength value set by the host
             * to tell how big of a buffer it has allocated to receive the
             * data here / how much bytes it will care to receive. If we send
             * less than expected, the host simply receives less without any
             * consequences; if we send more than expected, V-USB itself will
             * limit the size to make sure there won't be any consequences for
             * the host either. The latter will however silently discard data
             * we intended to send, so it's a good idea to check if the sizes
             * will match.
             *
             * To send data back to the host, we have two options:
             *  1) point V-USB's internal usbMsgPtr variable to the location
             *     in RAM (i.e. a regular, non-PROGMEM variable) we want to
             *     send there, and return the size of it in this function
             *
             *  2) use the usbFunctionRead callback (yes, Read, communication
             *     is considered from the host's point of view, and as we
             *     send data back to it, the host is the one reading here)
             *
             * In this example, we use the simpler first option and just point
             * usbMsgPtr to our pwm_value buffer. For more details on the more
             * complex (and thus more powerful / flexibly) second option, have
             * a look at the 03_caesar example.
             */
            if (rq->wLength.word < sizeof(pwm_value)) {
                /*
                 * Length is indeed smaller than our value buffer.
                 * Unfortunately we cannot directly indicate an error here,
                 * so instead, we return 0 here so nothing is actually send
                 * back to the host at all.
                 *
                 * To turn this into proper error handling, the host-side
                 * control application needs to check if the received data
                 * is of length zero or not (../host/ledcontrol.py does so)
                 */
                return 0;
            }

            /* Point usbMsgPtr to our pwm_value buffer and return its size */
            usbMsgPtr = pwm_value;
            return sizeof(pwm_value);
    }

    /* In any other case, including unknown requests, simply return 0 */
    return 0;
}


/*
 * And off we go..
 */
int
main(void)
{
    /* Set up GPIO, set LED pin as output and turn it off */
    LED_DDR = (1 << LED_PIN);
    LED_PORT = 0x00;

    /*
     * By default, shine the LED via PWM at ~25% duty cycle.
     *
     * This achieves three things:
     *  1) instant feedback that everything is set up properly and works
     *  2) lower the risk to kill the LED if current-limiting resistor is
     *     either too low or was omitted altogether
     *  3) indicate in case a way too high current-limiting resistor was
     *     used, as this should ideally have a nice, bright-enough glow.
     */
    timer0_init_pwm(0x3f);

    /* Disconnect and reconnect USB to enforce device re-enumeration */
    usbDeviceDisconnect();
    _delay_ms(200);
    usbDeviceConnect();

    /** Init USB and enable interrupts */
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

