#!/usr/bin/env python3
#
# RUDY - the Random USB Device
# USB LED V-USB example - host side Python script
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
USB_SERIAL_NUMBER = "LED Example"

# USB request types
USB_SEND = 0x40
USB_RECV = 0xC0

# LED control commands (make sure these are kept in sync with the device side firmware)
CMD_LED_ON  = 0x01
CMD_LED_OFF = 0x02
CMD_LED_PWM = 0x03
CMD_GET_PWM = 0x04


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

# Matching device found, we're ready to go - start with some help ouptut
print("""Welcome to {}

Available commands:
on              turn LED on
off             turn LED off
pwm             read the current PWM value
pwm <value>     set LED to given PWM value
                value can be either decimal [0..255] or hexadecimal [0x00..0xff]
q | quit        quit

""".format(dev.serial_number))

run = True
while run:
    try:
        cmd = input("> ")

        if cmd == "q" or cmd == "quit":
            run = False

        elif cmd == "on":
            # "on" command, write SEND reqest with CMD_LED_ON and no additional data
            #
            # The third and fourth parameter (wValue and wIndex) are zero here and could be
            # therefore omitted. In other cases we could send two 16bit values to the device
            # here, so for completeness, the parameters are included here.
            dev.ctrl_transfer(USB_SEND, CMD_LED_ON, 0, 0)

        elif cmd == "off":
            # "off" command, write SEND reqest with CMD_LED_OFF and no additional data
            #
            # This time, the third and fourth parmater (wValue and wIndex) are omitted,
            # just to demonstrate both options. 
            dev.ctrl_transfer(USB_SEND, CMD_LED_OFF)

        elif cmd == "pwm":
            # "pwm" command, read PWM value with CMD_GET_PWM
            #
            # Since a value is read back from the device here, things are slighty different:
            #   - the request type needs to be USB_RECV instead of USB_SEND
            #   - a fifth parameter is needed to define how many bytes to read
            #   - the returned data is an array object containg raw bytes
            #
            # The returned data needs to be converted to a string to make use of it,
            # and in this case, it's the hexadecimal value (without 0x prefix) of the
            # current PWM value, therefore we need to read 2 bytes (as the PWM value
            # itself is one byte, which requires two characters to represent as string)
            #

            # Read 2 bytes via CMD_GET_PWM command
            pwm_value = dev.ctrl_transfer(USB_RECV, CMD_GET_PWM, 0, 0, 2)
            # Alternatively, we could call:
            #   pwm_value = dev.ctrl_transfer(USB_RECV, CMD_GET_PWM, data_or_wLength=2)
            # and again omit the unused wValue and wIndex parameters
            #
            # Note that the size parameter (2 bytes here) is the *maximum* number of bytes
            # that is attempted to be received here. If less data is sent by the device,
            # simply less data is received; if more data is sent, the rest of it is ignored.

            # Convert received data to string
            pwm_value_string = pwm_value.tostring().decode('ASCII')

            # Convert string to integer value - if possible.
            # If conversion fails, chances are nothing was received from the device side.
            # Reason for that could a too small receive buffer size (see ../device/main.c)
            try:
                int_value = int(pwm_value_string, 16);
                # Display the current PWM value both in hexadecimal and decimal
                print("Current PWM value: 0x{} ({})".format(pwm_value_string, int_value))
            except ValueError:
                print('Failed to retrieve PWM value, received "{}"'.format(pwm_value_string))


        elif cmd[:4] == "pwm " and len(cmd) > 4:
            # "pwm <value>" command, write SEND request with CMD_LED_PWM and a given value
            #
            # The given value itself can be either decimal or hexadecimal, and is sent using
            # the third wValue paramter. Note that the "w" prefix denotes that the variable
            # is of "word sized value", which in this case means 16-bit. However, the device
            # uses an 8-bit timer, so only the lower byte of the value is actually used, and
            # the device-side code will simply ignore the higher byte.
            #
            # e.g. a value of 666 (0x029a) will simply result in a value of 154 (0x009a)
            # 

            # First, parse the given value string to an integer.
            #
            # Extract the value from the cmd string, and check if it starts with "0x",
            # in which case the value string is treated as a hexadecimal value.
            # Otherwise, it's treated as a regular decimal value.
            value = cmd[4:].lower()
            base = 10
            if value[:2] == "0x":
                base = 16
            try:
                dev.ctrl_transfer(USB_SEND, CMD_LED_PWM, int(value, base), 0)
            except ValueError:
                print("Cannot convert '{}' to integer".format(value))

        else:
            print("Unknown command '{}'".format(cmd))

    except (KeyboardInterrupt, EOFError):
        print("")
        run = False

