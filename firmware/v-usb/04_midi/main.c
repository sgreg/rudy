/*
 * RUDY - the Random USB Device
 * USB MIDI V-USB example
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
 */
 /*
 * Example 03: MIDI device
 *
 *      This is a combination of USB MIDI and Analog to Digital Conversion.
 *      An arbitrary sensor can be hooked up to an ADC channel, and the device
 *      will periodically send MIDI notes depending on the sensor values read
 *      by the ADC. Take for example a photoresistor (LDR, light sensor), and
 *      the brighter the light, the higher (or lower) the note.
 *
 *      The USB MIDI setup part is taken directly from the 4chord MIDI project,
 *      see https://github.com/sgreg/4chord-midi for more information on that.
 *
 *      Note that while the ADC part should work well enough, it's not the most
 *      ideal setup for a real world sensor reading setup. For more information
 *      on how to improve Analog to Digital conversions, check out Microchip's
 *      application note AN2538 (formerly known as AVR126 when it was still
 *      Atmel) titled "ADC of megaAVR in Single-Ended Mode".
 *
 *
 * Example hardware setup:
 *
 *       .-----------------------------.
 *       |                             |
 *       |           __  __          .---.
 *       |         -|1 \/  |-        |   |  Variable resistor as sensor
 *       |         -|      |-        | R |  e.g. LDR, force sensor, NTC
 *       |         -|      |-        | 1 |  (or simply a potentiometer)
 *       |         -|      |-        |___|
 *       |         -|      |-          |
 *       |         -|    23|--ADC0-----+
 *       '-----VCC--|7     |-          |
 *       .-----GND--|8     |-        .---.
 *       |         -|      |-        |   |  Matching resistor to complete
 *       |         -|      |-        | R    the voltage divider to get a
 *       |         -|      |-        | 2 |  good sensor value range
 *       |         -|      |-        |___|
 *       |         -|      |-          |
 *       |         -|      |-          |
 *       |          '------'           |
 *       |                             |
 *       '-----------------------------'
 *
 *
 * An alternative option is to use a standalone sensor that directly outputs
 * their analog voltage value instead of having variable resistance that
 * requires the voltage divider setup - for example the ADXL335 accelerometer
 * or an LM35 temperature sensor.
 *
 */
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <usbdrv/usbdrv.h>
#include "usbconfig.h"


/** ADC Channel (and ADCx pin) the sensor is connected to */
#define ADC_CHANNEL 0

/** Number of samples multiplier, will result in 2^ADC_SAMPLES_MUL samples */
#define ADC_SAMPLES_MUL 2
/** Number of samples to take the average ADC value from */
#define ADC_SAMPLES (1 << ADC_SAMPLES_MUL)


/*
 * USB MIDI device and configuration descriptor setup
 * For more details, refer to the Universal Serial Bus Device Class Definition
 * for MIDI Devices Release 1.0 document found at
 * https://usb.org/sites/default/files/midi10.pdf
 *
 * The descriptor definition is based and taken from the example found in
 * the above mentioned document, Appendix B.1. and was adjusted to provide
 * one interface (MIDI IN Jack) with one bulk endpoint.
 */

/*
 * USB MIDI adapter device descriptor.
 * Based on the USB device class definition example found in Appendix B.1
 */
const uint8_t usb_midi_device_descriptor[] PROGMEM = {
    0x12,                   /* [1] size of this descriptor in bytes (18)    */
    USBDESCR_DEVICE,        /* [1] descriptor type (DEVICE)                 */
    0x10, 0x01,             /* [2] supported USB version (1.10)             */
    0x00,                   /* [1] device class, defined at interface level */
    0x00,                   /* [1] subclass, unused                         */
    0x00,                   /* [1] protocol, unused                         */
    0x08,                   /* [1] max packet size in bytes (8)             */
    USB_CFG_VENDOR_ID,      /* [2] vendor ID (see usbconfig.h)              */
    USB_CFG_DEVICE_ID,      /* [2] device ID (see usbconfig.)               */
    USB_CFG_DEVICE_VERSION, /* [2] device release version (see usbconfig.h) */
    0x01,                   /* [1] manufacturer string index (1)            */
    0x02,                   /* [1] product string index (2)                 */
    0x00,                   /* [1] serial number string index, unused       */
    0x01,                   /* [1] number of configurations (1)             */
};

/*
 * USB MIDI configuration adapter descriptor.
 * Based on the USB device class definition example found in Appendix B.2-B.6
 */
const uint8_t usb_midi_config_descriptor[] PROGMEM = {
/* B.2   Configuration Descriptor */
    0x09,               /* [1] size of this descriptor in bytes (9)         */
    USBDESCR_CONFIG,    /* [1] descriptor type (CONFIGURATION)              */
    0x3f, 0x00,         /* [2] total length of descriptor in bytes (63)     */
    0x02,               /* [1] number of interfaces (2)                     */
    0x01,               /* [1] ID of this configuration (1)                 */
    0x00,               /* [1] configuration, unused                        */
    USBATTR_BUSPOWER,   /* [1] attributes                                   */
    0x32,               /* [1] max USB power in 2mA units (50 == 100mA)     */

/* B.3   AudioControl Interface Descriptor */
/* B.3.1 Standard AudioControl Interface Descriptor                         */
    0x09,               /* [1] size of this descriptor in bytes (9)         */
    USBDESCR_INTERFACE, /* [1] descriptor type (INTERFACE)                  */
    0x00,               /* [1] index of this interface (0)                  */
    0x00,               /* [1] index of this setting (0)                    */
    0x00,               /* [1] number of endpoints to follow (0)            */
    0x01,               /* [1] interface class (AUDIO)                      */
    0x01,               /* [1] interface sublass (AUDIO_CONTROL)            */
    0x00,               /* [1] interface protocol, unused                   */
    0x00,               /* [1] interface, unused                            */

/* B.3.2 Class-specific AudioControl Interface Descriptor */
    0x09,               /* [1] size of this descriptor in bytes (9)         */
    0x24,               /* [1] descriptor type (CS_INTERFACE)               */
    0x01,               /* [1] header subtype                               */
    0x00, 0x01,         /* [2] revision of class specification (1.0)        */
    0x09, 0x00,         /* [2] total size of class spec descriptor (9)      */
    0x01,               /* [1] number of streaming interfaces (1)           */
    0x01,               /* [1] MIDIStreaming iface 1 belongs to this iface  */

/* B.4   MIDIStreaming (MS) Interface Descriptors */
/* B.4.1 Standard MIDIStreaming Interface Descriptor */
    0x09,               /* [1] size of this descriptor in bytes (9)         */
    USBDESCR_INTERFACE, /* [1] descriptor type (INTERFACE)                  */
    0x01,               /* [1] index of this interface (1)                  */
    0x00,               /* [1] index of this alternate setting (0)          */
    0x01,               /* [1] number of endpoints to follow (1)            */
    0x01,               /* [1] interface class (AUDIO)                      */
    0x03,               /* [1] interface sublass (MIDSTREAMING)             */
    0x00,               /* [1] interface protocol, unused                   */
    0x00,               /* [1] interface, unused                            */

/* B.4.2 Class-specific MIDIStreaming Interface Descriptor */
    0x07,               /* [1] size of this descriptor in bytes (7)         */
    0x24,               /* [1] descriptor type (CS_INTERFACE)               */
    0x01,               /* [1] header subtype                               */
    0x00, 0x01,         /* [2] revision of class specification (1.0)        */
    0x41, 0x00,         /* [2] total size of class spec descriptor (65)     */

/* B.4.3 MIDI IN Jack Descriptor Embedded */
    0x06,               /* [1] size of this descriptor in bytes (6)         */
    0x24,               /* [1] descriptor type (CS_INTERFACE)               */
    0x02,               /* [1] header subtype (MIDI_IN_JACK)                */
    0x01,               /* [1] jack type (EMBEDDED)                         */
    0x01,               /* [1] jack ID (1)                                  */
    0x00,               /* [1] unused */

/* B.6   Bulk IN Endpoint Descriptors */
/* B.6.1 Standard Bulk IN Endpoint Descriptor */
    0x09,               /* [1] size of this descriptor in bytes (9)         */
    USBDESCR_ENDPOINT,  /* [1] descriptor type (ENDPOINT)                   */
    0x81,               /* [1] endpoint address (IN 1)                      */
    0x03,               /* [1] attribute (interrupt endpoint)               */
    0x08, 0x00,         /* [2] max packet size (8)                          */
    0x0a,               /* [1] interval in ms (10)                          */
    0x00,               /* [1] refresh                                      */
    0x00,               /* [1] sync address                                 */

/* B.6.2 Class-specific MS Bulk IN Endpoint Descriptor */
    0x05,               /* [1] size of this descriptor in bytes (5)         */
    0x25,               /* [1] descriptor type (CS_ENDPOINT)                */
    0x01,               /* [1] descriptor subtype (MS_GENERAL)              */
    0x01,               /* [1] number of embedded MIDI OUT jacks (1)        */
    0x01,               /* [1] id of the embedded MIDI OUT jack (1)         */
};


/**
 * V-USB descriptor setup callback function
 */
uint8_t
usbFunctionDescriptor(usbRequest_t * request)
{
    if (request->wValue.bytes[1] == USBDESCR_DEVICE) {
        usbMsgPtr = (uint8_t *) usb_midi_device_descriptor;
        return sizeof(usb_midi_device_descriptor);

    } else {    /* must be config descriptor */
        usbMsgPtr = (uint8_t *) usb_midi_config_descriptor;
        return sizeof(usb_midi_config_descriptor);
    }
}

/**
 * V-USB setup callback function.
 *
 * There's nothing to be done here as RUDY acts as a standard USB MIDI device.
 * However, V-USB code itself references this function, so the linker won't
 * be happy if it doesn't exist, so here we are.
 */
uint8_t
usbFunctionSetup(uint8_t *data __attribute__((unused)))
{
    return 0;
}


/**
 * Generic USB MIDI message send function.
 * USB MIDI messages are always 4 byte long (padding unused bytes with zero).
 *
 * See also chapter 4 in the Universal Serial Bus Device Class Definition
 * for MIDI Devices Release 1.0 document found at
 * https://usb.org/sites/default/files/midi10.pdf
 *
 * For more information on MIDI messages, refer to Summary of MIDI Messages,
 * found at https://www.midi.org/specifications/item/table-1-summary-of-midi-message
 *
 * @param byte0 USB cable number and code index number
 * @param byte1 MIDI message status byte
 * @param byte2 MIDI message data byte 0
 * @param byte3 MIDI message data byte 1
 */
void
usb_send_midi_message(uint8_t byte0, uint8_t byte1, uint8_t byte2, uint8_t byte3)
{
    static uint8_t midi_buf[4];
    uint8_t retries = 10;

    while (--retries) {
        if (usbInterruptIsReady()) {
            midi_buf[0] = byte0;
            midi_buf[1] = byte1;
            midi_buf[2] = byte2;
            midi_buf[3] = byte3;
            usbSetInterrupt(midi_buf, 4);
            return;
        }
        _delay_ms(2);
    }
}

/**
 * Send a MIDI "Note On" message for the given note over USB.
 *
 * @param note MIDI note key number
 */
#define midi_msg_note_on(note) usb_send_midi_message(0x09, 0x90, note, 0x7f)

/**
 * Send a MIDI "Note Off" message for the given note over USB.
 *
 * @param note MIDI note key number
 */
#define midi_msg_note_off(note) usb_send_midi_message(0x08, 0x80, note, 0x7f)


/**
 * Initialize the Analog to Digital Converter.
 */
void
adc_init(void)
{
    ADCSRA = 0x00; /* disable ADC */

    /* Set reference voltage to "AVcc with external capacitor at AREF pin" */
    ADMUX = (0 << REFS1) | (1 << REFS0)
    /* Also set data left adjusted, this way we can skip ADCL and filter out the LSB */
          | (1 << ADLAR)
    /* And set the channel our sensor is connected to */
          | ADC_CHANNEL;

    /* Enable ADC */
    ADCSRA = (1 << ADEN)
    /* Set ADC clock prescaler to 64 for 12MHz/64 == 187.5kHz sample frequency */
           | (1 << ADPS2)
           | (1 << ADPS1);

    /* Set ADC to free-running mode. This could be triggered by a timer */
    ADCSRB = 0;

    /* Disable digital pin on ADC channel (if it has a corresponding one) */
    if (ADC_CHANNEL <= 5) {
        DIDR0 = (1 << ADC_CHANNEL);
    }
}

/**
 * Read a series of values from the ADC and return its average value.
 *
 * This is a very simple way to smoothen out the values a bit.
 * Instead of taking and relying on a single sample, multiple values
 * are read from the ADC channel, added up, and in the end divided
 * by that same number of samples to get the average value.
 *
 * This is seriously simple, as in "there are better ways to do this",
 * for examples using a moving average. But to keep the focus in this
 * example on setting up a sample USB MIDI device, this will do fine.
 *
 * Note that this only cares for the top 8 bits of the ADC value and
 * fully ignores the lower two bits (only reads from ADCH and skips
 * reading ADCL) as we're anyway mapping the value to a limited range
 * of MIDI notes later on.
 *
 * @return average value of ADC_SAMPLES samples
 */
uint8_t
adc_read(void)
{
    uint8_t i;
    uint16_t sum = 0;

    /*
     * Start collecting multiple samples.
     * The first sample will be discarded, so adding an extra loop round.
     */
    for (i = 0; i < ADC_SAMPLES + 1; i++) {
        /* Trigger a single conversion */
        ADCSRA |= (1 << ADSC);

        /* Wait for conversion done */
        while (ADCSRA & (1 << ADSC)) {
            /* do nothing */
        }

        /* Discard the first sample as it might be garbage. Just in case.. */
        if (i == 0) {
            continue;
        }

        /* Read sample and add it up */
        sum += ADCH;
    }

    /* All samples are taken, return the average value of them */
    return (sum >> ADC_SAMPLES_MUL) & 0xff;
}


/*
 * Let's get going..
 */
int
main(void)
{
    /* Raw ADC value. Contains the 8 most significant bits */
    uint8_t adcval = 0;

    /*
     * Currently played note value. This is derived from the ADC value and
     * the actual note that's sent as MIDI message. Needs to be kept around
     * to make sure the same value that was sent in the previous "Note On"
     * MIDI message is the same that's sent in the "Note Off" message.
     */
    uint8_t note = 0;

    /* Keep track if note is currently played or stopped */
    uint8_t note_on = 0;

    /* Delay counter, see below */
    uint8_t delay_count = 0;


    /* Force device re-enumeration */
    usbDeviceDisconnect();
    _delay_ms(300);
    usbDeviceConnect();

    /* Set up ADC and USB */
    adc_init();
    usbInit();

    /* Enable interrupts and off we go */
    sei();

    while (1) {
        /*
         * usbPoll() needs to be called periodically (at least every 50ms),
         * or else the USB connection times out and is dropped. So avoid
         * long _delay_*() calls, and rather split them up with a counter.
         */
        usbPoll();

        /*
         * Do the actual playing.
         * Notes are played around every second, with ~700ms actively played,
         * and ~300ms pause between the notes. As mentioned above, usbPoll()
         * needs to be called latest every 50ms, so this requires a counter
         * to stay within that limit.
         *
         * For simplicity, each loop is 10ms delayed.
         */
        if (note_on) {
            /* Note is currently played, check if it's time to stop */
            if (++delay_count == 70) {
                /* Yes - reset delay counter, and stop the playing */
                delay_count = 0;
                midi_msg_note_off(note);
                note_on = 0;
            }
        } else {
            /* Note is not yet played, check if it's time to start */
            if (++delay_count == 30) {
                /* Yes - reset delay counter and read the current ADC value */
                delay_count = 0;
                adcval = adc_read();

                /*
                 * We retrieved the 8 highest bits of the analog-to-digital
                 * conversion from adc_read(), so we have values in the range
                 * of [0, 255]. As there are 127 MIDI notes, we could simply
                 * divide the ADC value by 2 and play it. However, the lowest
                 * and highest notes didn't feel very pleasant to listen to,
                 * so it seems like a good idea to limit the range of actual
                 * available notes a bit.
                 *
                 * If we ignore the bottom 2 bits of the ADC value, we'll end
                 * up with a 6-bit value, giving us 64 possible notes, which
                 * seems like a decent enough range for a simple MIDI device
                 * like this. Now we only need to add an offset to shift it
                 * more into the center range of the notes spectrum.
                 *
                 * After some soul searching, I've decided on the number 28,
                 * as it puts natural notes on both ends of the spectrum.
                 * This way we'll end up with an available MIDI notes range
                 * of [28, 91], which translates to E1...G6.
                 */
                note = ((adcval >> 2) & 0x3f) + 28;

                /* Start playing the note */
                midi_msg_note_on(note);
                note_on = 1;
            }
        }

        /* Delay a little while */
        _delay_ms(10);
    }

    return 0;
}

