/*
 * RUDY - the Random USB Device
 * Blinky Arduino example
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
 *      Note that RUDY has no on-board LED, so an external LED is required
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
 *      '------|( |-----|   R   |-----D5--|11    |-
 *             | \|     '-------'        -|      |-
 *                                       -|      |-
 *                                       -|      |-
 *                                        '------'
 *
 * Connect resistor and LED from digital pin 5 (pin 11) to GND (pin 8)
 *
 * Value for R depends on the supply voltage (3.3V or 5.0V) and the LED itself.
 * If in doubt, somewhere around 120 Ohm should probably do for a first test.
 *
 */

/* The Arduino pin the LED is connected to, here: digital pin 5 */
#define LED_PIN 5

/* Number of milliseconds to wait between toggling the LED on and off */
#define BLINK_DELAY_MS 500


/* Setup, set LED_PIN as output */
void setup(void) {
    pinMode(LED_PIN, OUTPUT);
}

/* Loop, toggle LED_PIN ever BLINK_DELAY_MS milliseconds */
void loop(void) {
    digitalWrite(LED_PIN, HIGH);
    delay(BLINK_DELAY_MS);
    digitalWrite(LED_PIN, LOW);
    delay(BLINK_DELAY_MS);
}

