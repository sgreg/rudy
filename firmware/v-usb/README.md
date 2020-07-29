# RUDY - V-USB Examples

This is a collection of examples that will turn RUDY into a USB device using the [V-USB library](https://www.obdev.at/products/vusb/index.html).


## List of Examples

- [`01_hello-usb`](01_hello-usb/) a dummy USB device that will simply just show up as such in the system, but doesn't have any actual functionality
- [`02_usb-led`](02_usb-led/) controlling an LED via USB to turn it on, off, or to a specified PWM value, including Python script to communicate with it
- [`03_caesar`](03_caesar/) sending messages from a Python script to the USB device and receiving them back "encrypted" via [Caesar Cipher](https://en.wikipedia.org/wiki/Caesar_cipher)
- [`04_midi`](04_midi/) a USB MIDI device that uses analog-to-ditigal conversion to turn sensor values into MIDI notes

For additional information on the examples themselves, check their individual directories.


## Compiling and Flashing

To compile and flash the examples, please see the general instructions in [the parent directory's README](../). As the build system is designed to keep it as straightforward and consistent as possible between the different examples, they all share the same [common build environment](common/), and therefore building and flashing will be the same for all of them.

If the examples don't have any specific build instructions themselves, it means that there's nothing different about them and the common compiling and flashing instructions apply.

## Running Control Application

Some of the examples come with a host-side control application in form of a Python script, for example the [USB LED Example](02_usb-led). The script themselves require Python3 and the [PyUSB module](https://github.com/pyusb/pyusb) installed. PyUSB can be usually installed via your Linux distribution's package manager, or via `pip install pyusb`.

In order to run the script, the user must have read/write access to the USB device itself, which usually won't be the case out of the box, or else the script will fail to run with something like `ValueError: The device has no langid`. There are two ways to get this working:

1. run the scripts as root via `sudo`
2. add a `udev` rule for the device

While the first option surely is the easy option to make it work, it's recommended to go for the second option.

### Add udev Rule

To add a `udev` rule, a rule file needs to be located in `/etc/udev/rules.d/` with the following content:
```
SUBSYSTEM=="usb", ATTRS{idVendor}=="1209", ATTRS{idProduct}=="b00b", MODE="0666"
```

The rule makes sure that every USB device with a VID/PID combination of 0x1209/0xb00b (i.e. the [official id pair](http://pid.codes/1209/B00B/) for RUDY) will have its permission set to `0666`, i.e. read/write permission for everyone.

The file name itself is usually in a form of `xx-something.rules`, with `xx` being a number to enforce the run order (as the rules are processed in alphabetical order). For RUDY, the file could be called `50-rudy.rules`, and you either use and editor to create the file (needs `sudo` to write in that directory), or `echo` and `tee` it there:
```
$ echo 'SUBSYSTEM=="usb", ATTRS{idVendor}=="1209", ATTRS{idProduct}=="b00b", MODE="0666"' |sudo tee /etc/udev/rules.d/50-rudy.rules
```

Once the file is added to `/etc/udev/rules.d`, reload the rules.
```
$ sudo udevadm control --reload-rules
$ sudo udevadm trigger
```

You should now be able to run the host-side scripts successfully.

