# RUDY - V-USB Example 03: Caesar Cipher

A USB implementation of the [Caesar Cipher](https://en.wikipedia.org/wiki/Caesar_cipher), which "encrypts" a message by shifting letters a certain amount of positions. A message is sent to the device and stored there, and can later be requested back in "encrypted" form. Note that the quotes are purposely used here, while technically it could be considered as an encryption mechanism, the Caesar Cipher isn't really of much use for actual encryption. It's good for a USB communication / data transfer example though.

This example is split into a [`device/`](device/) directory that has the firmware for RUDY, and a [`host/`](host/) directory that has the host-side control software in form of a Python script.

## Set it up

No other components are used in this example.


## Build and flash it

The general instruction in the [parent directory's README](../). apply here, but the firmware itself is found in the [`device/`](device/) directory, so the `make` commands need to be run from within that directory instead of the example's main directory.


## Use it

If everything went well and the hardware is set up correctly, once the device is plugged in, the following information should be visible in the syslog or `dmesg`:

```
[252898.876553] usb 2-3.4: new low-speed USB device number 65 using xhci_hcd
[252899.185018] usb 2-3.4: New USB device found, idVendor=1209, idProduct=b00b, bcdDevice= 1.00
[252899.185022] usb 2-3.4: New USB device strings: Mfr=1, Product=2, SerialNumber=3
[252899.185025] usb 2-3.4: Product: RUDY
[252899.185027] usb 2-3.4: Manufacturer: CrapLab
[252899.185030] usb 2-3.4: SerialNumber: Caesar Cipher
```

### Python control script

The Python control script requires Python3 and the [PyUSB module](https://github.com/pyusb/pyusb) installed. PyUSB can be usually installed via your Linux distribution's package manager, or via `pip install pyusb`.

If you have both available, you should be able to run the [`caesarcontrol.py`](host/caesarcontrol.py) script located in the [`host`](host/) directory.

```
[03_caesar/]$ cd host/
[03_caesar/host/]$ ./caesarcontrol.py 
Welcome to the Caesar Cipher Control Application

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


>
```

If the script says "`Error: No device found`", make sure you have flashed RUDY with the correct example firmware, the device is [powered correctly](../../#powering-rudy), and it shows up in the syslog or `lsusb` output.

