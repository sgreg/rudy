#!/usr/bin/env python3
#
# RUDY - the Random USB Device
# Casear Cipher V-USB example - host side Python script
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
import sys
import usb.core

# Expected USB device information
USB_VID = 0x1209
USB_PID = 0xb00b
USB_SERIAL_NUMBER = "Caesar Cipher"

# USB request types
USB_SEND = 0x40
USB_RECV = 0xC0

# Control commands (make sure these are kept in sync with the device side firmware)
CMD_SEND_TO_DEVICE = 0x10
CMD_RECV_FROM_DEVICE = 0x11


# Try to find a device that matches the expected vendor ID and product ID
dev = usb.core.find(idVendor=USB_VID, idProduct=USB_PID)

# Check that a matching device is connected
if dev is None:
    print('Error: No device found')
    sys.exit(1)

# Make sure it's the expected device based on its serial number data
if dev.serial_number != USB_SERIAL_NUMBER:
    print('Error: expected serial number "{}" but got "{}"'.format(USB_SERIAL_NUMBER, dev.serial_number))
    sys.exit(1)

# Matching device found, we're ready to go - start with some help output
print("""Welcome to the {} Control Application

Available commands:
init <message>  Initialize the device with the given message.
                This sends the message to the device and stores it there.
                Later calls to "cipher <shift"> command will be based on
                this message, so make sure this is called at least once.

cipher <shift>  Retrieve the message previously sent via "init <message>"
                command shifted by the given amount. The shift value can
                be also negative to shift in the other direction.

q | quit        Quit the control application.


Example usage:
> init hello RUDY
Device initialized
> cipher 10
rovvy BENI

""".format(dev.serial_number))

run = True
while run:
    try:
        cmd = input("> ")

        if cmd == "q" or cmd == "quit":
            run = False

        elif cmd == "init":
            # "init" command without parameter, send some help text.
            print('Missing message, use "init <message>", e.g. "init test"')

        elif cmd[:5] == "init " and len(cmd) > 5:
            # "init <message>" command, send message via CMD_SEND_TO_DEVICE request.
            #
            # The message itself is sent in the data_or_wLength parameter, pyusb will handle
            # everything else behind the scenes. wValue and wIndex aren't used in this request.
            #
            # Note that too long messages might require too much handling time on the device
            # side and cause an error due to timeout. See also the device-side main() function.
            # A better way to deal with this is to split up the message and send it chunk by chunk,
            # using one of the wValue or wIndex parameters to tell the device the message offset.
            # Feel free to take this as an exercise.
            #
            message = cmd[5:]
            try:
                dev.ctrl_transfer(USB_SEND, CMD_SEND_TO_DEVICE, 0, 0, message)
                print("Device initialized")
            except usb.core.USBError as e:
                print("Error while sending: {}".format(e))

        elif cmd == "cipher":
            # "cipher" command without parameter, send some help text.
            print('Missing shift value, use "cipher <shift>", e.g. "cipher 10"')

        elif cmd[:7] == "cipher " and len(cmd) > 7:
            # "cipher <shift"> command, request the ciphered message via CMD_RECV_FROM_DEVICE request.
            #
            # The shift value is sent as wValue request parameter, and the maximum amount of bytes
            # to receive as the fifth, data_of_wLength parameter.
            #
            # First, try to convert the given parameter into an integer.
            try:
                shift = int(cmd[7:])
            except ValueError:
                print("Cannot convert '{}' to integer".format(cmd[7:]))
                continue

            # Adjust shift value to be within the alphabet range.
            # Negative values will simply make it shift in the other direction this way.
            shift = shift % 26
            
            # Send the request and read up to 100 bytes back from the device.
            #
            # Similar as in the CMD_SEND_TO_DEVICE request above, a better way to implement
            # this would be to use multiple calls and get the message chunk by chunk.
            try:
                recv = dev.ctrl_transfer(USB_RECV, CMD_RECV_FROM_DEVICE, shift, 0, 200)
                # Convert the raw result into a string and print it.
                recv_string = recv.tostring().decode("ASCII")
                print("Received: {}".format(recv_string))
            except usb.core.USBError as e:
                print("Error while receiving: {}".format(e))

        else:
            print("Unknown command '{}'".format(cmd))

    except (KeyboardInterrupt, EOFError):
        print("")
        run = False

