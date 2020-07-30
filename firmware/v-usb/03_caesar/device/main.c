/*
 * RUDY - the Random USB Device
 * Casear Cipher V-USB example - Device side firmware
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
 * Example 03: Caesar Cipher
 *      Custom device class to send chunks of data (text) to and receive
 *      it back in Caesar Cipher "encrypted". (the quotes are purposely
 *      used within this example as the Caesar Cipher should never be seen
 *      as an actual, real-world encryption mechanism).
 *
 *      See https://en.wikipedia.org/wiki/Caesar_cipher for more information
 *      on the Caesar Cipher itself.
 *
 *      See also the 02_usb-led example code for additional V-USB related
 *      information (which is partially duplicated here)
 *
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include "usbconfig.h"
#include "usbdrv/usbdrv.h"

/*
 * LED commands, need to be in sync with the host side.
 * As direction can be a bit confusing when using "read" and "write" in the
 * device code, as it's considered from the host's point of view, "send to"
 * and "receive from" terminology is used here in hopes to make it more clear.
 */
/**
 * Request command to send data from the host to the device.
 * This will include the message that is stored on the device then and later
 * returned via CMD_RECV_FROM_DEVICE request in "encrypted" form.
 */
#define CMD_SEND_TO_DEVICE 0x10
/**
 * Request command to send data from the device back to the host.
 * This is expected to include the "encrypted" message that was initially
 * sent via CMD_SEND_TO_DEVICE request.
 */
#define CMD_RECV_FROM_DEVICE 0x11


/** Maximum number of bytes we will store on the device */
#define BUFFER_SIZE 256

/** Buffer to store the message received via CMD_SEND_TO_DEVICE request */
static char buffer[BUFFER_SIZE];
/** Size of the message itself in the buffer */
static uint8_t buffer_len;

/**
 * Amount of places to shift / "encrypt" the message when returning it via
 * CMD_RECV_FROM_DEVICE command. The value itself is received as part of
 * the CMD_SEND_TO_DEVICE request.
 */
static uint8_t shift;

/** Number of bytes to expect from the CMD_SEND_TO_DEVICE request */
static uint16_t recv_cnt;
/** Bytes received during the CMD_SEND_TO_DEVICE request's data transfer */
static uint16_t recv_len;

/** Number of bytes the host accepts during a CMD_RECV_FROM_DEVICE request */
static uint16_t repl_cnt;
/* Bytes sent during the CMD_RECV_FROM_DEVICE request's data transfer */
static uint16_t repl_len;


/**
 * Shift a single given character and return it.
 *
 * Implementing the Caesar Cipher on a per-character base here.
 * If the given character is either lower-case a-z, or upper-case A-Z,
 * the shifted value is returned accordingly. If the given character is
 * not a letter (number, special character, or non-printable character),
 * it is not relevant to the "encryption" and returned as-is.
 *
 * @param in Character to shift
 * @return Character shifted according to the set shift value
 */
char
shift_character(char in)
{
    if (in >= 'a' && in <= 'z') {
        /* lower-case letter, shift within lower-case space */
        if (in + shift <= 'z') {
            return in + shift;
        } else {
            return in - 26 + shift;
        }
    } else if (in >= 'A' && in <= 'Z') {
        /* upper-case letter, shift within upper-case space */
        if (in + shift <= 'Z') {
            return in + shift;
        } else {
            return in + shift - 26;
        }
    } else {
        /* Not a letter, return input as-is */
        return in;
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
 * For more information, check its documentation in usbdrv.h and the code
 * in the ../02_usb-led/device/ example.
 *
 * @param data Setup data
 */
uchar
usbFunctionSetup(uchar data[8])
{
    /*
     * Cast given raw data to usbRequest_t structure.
     *
     * The struct itself is *the* main data structure for any communication
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
     *                 it to be, e.g. CMD_SEND_TO_DEVICE.
     *                 Content is a byte value, hence the "b" prefix
     *
     * wValue        - For custom class devices, this doesn't have any fixed
     *                 meaning, and we can abuse it for any sending arbitrary
     *                 data between host and device, e.g. the cipher rotation
     *                 value in the CMD_RECV_FROM_DEVICE request.
     *                 Content is a 16-bit word value, hence the "w" prefix
     *
     * wIndex        - Same as wValue in case of custom class devices, but
     *                 unused in this example code. It could provide another
     *                 arbitrary 16-bit value if needed.
     *                 Content is a 16-bit word value, hence the "w" prefix
     *
     * wLength       - Length in bytes of an additional data transfer.
     *                 As we're sending messages between host and the device
     *                 in this example, the 32 bit provided by wValue and
     *                 wIndex won't be enough, and the data is sent after
     *                 the setup message. Check further below for more of
     *                 the details on the data transfer code itself.
     *                 Content is a 16-bit word value, hence the "w" prefix
     */
    usbRequest_t *rq = (void *) data;

    /* Check and handle request type */
    switch (rq->bRequest) {
        case CMD_SEND_TO_DEVICE:
            /*
             * Request to send data to the device.
             * This includes the message to later receive back "encrypted".
             *
             * First make sure the request type's direction is actually
             * set as a "host to device" request.
             */
            if ((rq->bmRequestType & USBRQ_DIR_MASK) == USBRQ_DIR_HOST_TO_DEVICE) {
                /*
                 * It is. In that case, we are expecting to receive additional
                 * data from the host, i.e. the mentioned message we will
                 * store for later.
                 *
                 * The length of the message the host will send is given in the
                 * requests's wLength parameter. We'll need this value to know
                 * when we have received all the data, so let's store it.
                 */
                recv_len = rq->wLength.word;

                /*
                 * As we're receiving a new message, we'll zero the buffer and
                 * delete any possible old message, and set our receive counter
                 * to zero as well.
                 */
                memset(buffer, 0, BUFFER_SIZE);
                recv_cnt = 0;

                /*
                 * From the setup request point of view, we're done, but we
                 * return special USB_NO_MSG value, which will indicate to
                 * V-USB that additional data should be transferred.
                 *
                 * This will lead to V-USB calling the usbFunctionWrite()
                 * callback, which is implemented a bit further down, and
                 * has some further information about what's happening.
                 */
                return USB_NO_MSG;
            } /* else: do nothing, use default return at the end. */
            break;

        case CMD_RECV_FROM_DEVICE:
            /*
             * Request to receive data from the device.
             * This expects to send the earlier received message back in its
             * "encrypted" form. The amount of shifts to perform here is also
             * added as part of the request.
             *
             * But let's make also sure that that the request type's direction
             * is actually set as a "device to host" request.
             */
            if ((rq->bmRequestType & USBRQ_DIR_MASK) == USBRQ_DIR_DEVICE_TO_HOST) {
                /*
                 * It is. In that case, the host is expecting to receive the
                 * initially sent message back in its "encrypted" form, and
                 * provides the number of bytes it'll be ready to receive in
                 * the request's wLength parameter.
                 *
                 * We'll store that number for later, and while doing so adjust
                 * it to match the actual number of bytes we have actually in
                 * the buffer we'll send.
                 */
                repl_len = rq->wLength.word;
                if (repl_len > buffer_len) {
                    repl_len = buffer_len;
                }
                /*
                 * The host also sends the actual value to shift the message
                 * by, using the request's wValue parameter, so we'll store
                 * that one as well.
                 *
                 * Note that there is no check or adjustments performed here,
                 * so if the value is outside the alphabet's range, funky
                 * things will happen. The host-side control script is set
                 * up to sanitize and adjust this value at this point.
                 */
                shift = rq->wValue.word & 0xff;

                /*
                 * Clear the receive counter and indicate to V-USB to start
                 * the data transfer by returning again the special value
                 * USB_NO_MSG here.
                 *
                 * Similar to the previous request, this will cause V-USB to
                 * call the usbFunctionWrite() callback, which is again
                 * implemented a bit further down and has some extra details.
                 */
                repl_cnt = 0;
                return USB_NO_MSG;
            } /* else: do nothing, use default return at the end. */
            break;
    }

    /* In any other case, including unknown requests, simply return 0 */
    return 0;
}


/**
 * V-USB write callback function
 *
 * To make use of this function, RUDY_IMPLEMENT_FN_WRITE needs to be defined
 * in usbconfig-rudy.h (which in turn defines USB_CFG_IMPLEMENT_FN_WRITE in
 * ../common/usbconfig.h), or the other around, in order to successfully
 * define RUDY_IMPLEMENT_FN_WRITE, this callback function here must exist.
 *
 * Note that the read/write terminology is considered from the host's point
 * of view, not the device's, which can be a bit confusing when writing code
 * for the device itself. So a "write" means actually "write *to* the device"
 * as that is what the host will actually do here. As a result, the
 * usbFunctionWrite() callback is called when the device is technically
 * *reading* data from the host. To avoid too much confusion with this,
 * let's just say we're *receiving* data here.
 *
 * The received data is provided in the address the given data parameter is
 * pointing to. Note that the data transfer happens in little 8 byte chunks,
 * so the len parameter refers to only that chunk size in a specific call.
 * The full expected length of data was transferred in the request itself, and
 * was therefore stored locally in the recv_cnt variable.
 *
 * The callback should return 1 if there is more data expected to be sent,
 * and 0 if all the data was received.
 *
 *
 * @param data Pointer where to received data sent from the host is stored
 * @param len Number of bytes received in this single chunk
 * @return 1 if the host should send more data, 0 of all data was received
 */
uchar
usbFunctionWrite(uchar *data, uchar len)
{
    uint8_t i;

    /*
     * Loop through the received data chunk - either the entire chunk,
     * or only the last few bytes - and store it in the buffer.
     */
    for (i = 0; recv_cnt < recv_len && i < len; i++, recv_cnt++) {
        buffer[recv_cnt] = data[i];
    }

    /*
     * Adjust buffer_len so later CMD_RECV_FROM_DEVICE requests
     * will know how much data there is to send.
     */
    buffer_len += len;

    /* Return 1 if there's more data expected, 0 if we're done */
    return (recv_cnt == recv_len);
}


/**
 * V-USB read callback function.
 *
 * To make use of this function, RUDY_IMPLEMENT_FN_READ needs to be defined
 * in usbconfig-rudy.h (which in turn defines USB_CFG_IMPLEMENT_FN_READ in
 * ../common/usbconfig.h), or the other around, in order to successfully
 * define RUDY_IMPLEMENT_FN_READ, this callback function here must exist.
 *
 * Again, the read/write terminology is considered from the host's point of
 * view, so the host is "reading data from the device" here, and as a result,
 * the usbFunctionRead() callback is called when the device itself is
 * technically *writing* - or simply *sending* data here.
 *
 * Sending data is done by placing it in the buffer pointed to by the given
 * data parameter. The transfer itself is done in max 8 byte chunks, so only
 * 8 bytes at a time will be handled in here. Therefore the len parameter
 * refers to the current chunk length, not the entire message length.
 *
 * The message length itself was received in the request's wLength parameter,
 * and had therefore be stored locally (in the repl_len variable).
 *
 * The callback should returns the amount of bytes to send here, so most of
 * the time it simply returns len itself. However, if the expected chunk size
 * is bigger than what's actually left to send, we will only send those
 * remaining bytes and have to return a value less than len. V-USB will take
 * the "less data sent than you asked for" as indication that the transfer
 * itself is done now.
 *
 *
 * @param data Pointer where to store the data to that is read back by the host
 * @param len Number of bytes to send in this chunk
 * @return Number of bytes actually sent, if < len, transfer is considered done
 */
uchar
usbFunctionRead(uchar *data, uchar len)
{
    uint8_t i;

    /*
     * Check if we send the whole chunk, or if these are the last bytes
     * remaining, and adjust len value accordingly.
     */
    if (len > repl_len - repl_cnt) {
        len = repl_len - repl_cnt;
    }

    /*
     * Send the actual data.
     * The Caesar Cipher part is handled right here, one character at a time.
     */
    for (i = 0; i < len; i++) {
        *data++ = shift_character(buffer[repl_cnt++]);
    }

    /* Return the (possibly adjusted) number of bytes we sent */
    return len;
}


/*
 * And off we go..
 */
int
main(void)
{
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
         * or else the USB connection times out and is dropped. In previous
         * examples, there wasn't much going on, so we could easily delay
         * a couple tens of milliseconds here. Doing so here will slow down
         * the data transfer significantly, as the data transfer itself is
         * triggered within the usbPoll() call.
         *
         * Considering that each transfer consists of only 8 bytes of data,
         * longer messages are easily flirting with a timeout if we use the
         * same 30ms as in the previous examples. However, delaying not at
         * all seem to cause some timing issue that result in (silently)
         * interrupted transfers / missing data chunks. This might need a
         * bit of tweaking, luck, and eventually some actual improvement.
         * For now, we'll start with 5ms delay.
         */
        usbPoll();
        _delay_ms(5);
    }

    return 0;
}

