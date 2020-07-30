/*
 * RUDY - the Random USB Device
 * Blinky bare metal example
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
 * Example 01: Blinky
 *      The classic hardware equivalent of Hello World: blink an LED
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
#include <util/delay.h>

/* LED port / pin definition, expects LED at PD5 */
#define LED_DDR  DDRD
#define LED_PORT PORTD
#define LED_PIN  PORTD5

/* Number of milliseconds to wait between toggling the LED on and off */
#define BLINK_DELAY_MS 500

int
main(void)
{
    /*
     * Declare a local variable that will remember the current state of the
     * LED (1 for on, 0 for off), and initialize it to 1 as the LED will be
     * on by default (see below).
     */
    uint8_t toggled = 1;

    /*
     * Set the selected LED pin's data direction as output by writing a 1 to
     * the associated place in the Data Direction Register. As the LED is
     * connected to PD5, that means the fifth bit in DDRD needs to be set.
     *
     * We have two ways to set a specific bit to one:
     *  1. hard-code the value, in this case 0x20
     *  2. shift a 1 to that place, in this case (1 << 5)
     *
     * For the compiler, it's all the same, as those are both constants that
     * can be figured out during compile time, so it's mostly a matter of
     * taste which option to choose. The first option makes it faster to set
     * multiple values at once (as in "it requires less code to write"):
     *      0x86   vs    ((1 << 7) | (1 << 2) | (1 << 1))
     * while the second option makes it more clear which bits are actually
     * set, and keep later changes a bit more flexible. It also encourages
     * to use variables / constants and avoid magic numbers that way, so
     * we'll go for the second option here.
     *
     * Without using the defined constants, we could write
     *      DDRD = (1 << 5);
     * to set the data direction of pin 5 in port D (i.e. PD5) as output,
     * here, but we'll just go ahead and use the constants instead.
     */
    LED_DDR = (1 << LED_PIN);

    /*
     * Set the selected pin's output to ON (i.e. turn the LED on) by writing
     * a 1 to the associated Port Data Register - again, the same way as above
     * by shifting a 1 to the associated (5th) bit. Without using the defined
     * constants here, this could be also written directly as
     *      PORTD = (1 << 5);
     * to set the output value of pin 5 in port D to 1.
     *
     * Alternatively, instead of writing 1, we could write the "toggled"
     * value here to keep both in sync:
     *      LED_PORT = (toggled << LED_PIN);
     *
     * Note that if LED_DDR / DDRD above wasn't set to make this an output,
     * PD5 would remain an input, and the writing to LED_PORT / PORTD here
     * would result in setting up the input's pull-up registers.
     *
     * For all the details, check chapter 13 "I/O Ports" in the ATmega328's
     * data sheet.
     */
    LED_PORT = (1 << LED_PIN);

    /* Loop forever */
    while (1) {
        if (toggled) {
            /*
             * LED is currently on, so we turn it off now.
             *
             * Turning the LED off essentially means to write a 0 to the
             * LED_PORT's Data Register. In this case, we'd have write that
             * to the 5th bit in that register, as that's the one associated
             * with the LED. In this specific case, where the LED is the only
             * additional component connected to the micrcontroller, we could
             * just write zero to the entire register - but that's not a good
             * way to deal with this, as it affects values that are none of
             * our concern here.
             *
             * Instead, we'll explicitly set only the 5th bit here, and we do
             * so by reading the register's current value, and writing it back
             * by AND'ing it with a bit mask that has our fifth bit set to 0.
             * 
             * Bit pos.     7 6 5 4 3 2 1 0
             * PORTD value  x x 1 x x x x x
             * Bit mask     1 1 0 1 1 1 1 1
             * ------------------------------
             * AND'ed       x x 0 x x x x x
             *
             * Since we don't want to change other values than our own, we
             * leave them as they are, whether they are 0 or 1, it doesn't
             * matter to us - and using the AND operation, it will keep the
             * ones as ones (1 & 1 == 1) and the zeros as zeros (0 & 1 = 0).
             *
             * To get the bit mask itself, we use the same shift we used to
             * turn the LED on in the beginning, and invert it using the
             * tilde (~) operator:
             *
             * Bit              7 6 5 4 3 2 1 0
             *  (1 << LED_PIN)  0 0 1 0 0 0 0 0
             * ~(1 << LED_PIN)  1 1 0 1 1 1 1 1
             *
             * So putting it all togheter:
             *      PORTD = PORTD & (1 << 5);
             * Or rather using our defined constants:
             *      LED_PORT = LED_PORT & ~(1 << LED_PIN)
             * Or simply shorter:
             */
            LED_PORT &= ~(1 << LED_PIN);

        } else {
            /*
             * LED is currently off, so let's turn it on.
             *
             * The principle here is a combination of the initial setting of
             * the register value, and the extensive explanation of how to
             * turn it off above.
             *
             * Again, instead of just setting the register as we did in the
             * beginning (which was okay there as we simply initialized it,
             * and in case there were other components involved, we had the
             * same with them right away in that moment), we *only* want to
             * set the register value associated with LED itself.
             *
             * So we take again the bit mask via (1 << LED_PIN), but do an
             * OR operation this time to set the specific bit to 1:
             *
             * Bit pos.     7 6 5 4 3 2 1 0
             * PORTD value  x x 0 x x x x x
             * Bit mask     0 0 1 0 0 0 0 0
             * ------------------------------
             * OR'ed        x x 1 x x x x x
             *
             * This will leave again all other values in PORTD alone since
             * an OR operation with zero leaves zeroes as zeroes (0 | 0 == 0)
             * and ones as ones (0 | 1 == 1).
             */
            LED_PORT |= (1 << LED_PIN);
        }

        /*
         * Invert the value of "toggled".
         *
         * Since C doesn't have a dedicated boolean data type, any integer
         * that's 0 is considered as "false", and any other value will be
         * considered as "true". Since we only need 0 and 1 to keep track
         * of the LED's state, negating the value here will essentially
         * turn a true to false and a false to true.
         *
         * Alternatively, we could set "toggled" explicitly to 0 and 1
         * respectively in the if clause above.
         */
        toggled = !toggled;

        /* Delay for the specified milliseconds to get a blinking going */
        _delay_ms(BLINK_DELAY_MS);
    }

    return 0;
}

