# RUDY - V-USB Examples

This is a collection of examples that will turn RUDY into a USB device using the [V-USB library](https://www.obdev.at/products/vusb/index.html).


## List of Examples

- [`01_hello-usb`](01_hello-usb/) a dummy USB device that will simply just show up as such in the system, but doesn't have any actual funcionality
- [`02_usb-led`](02_usb-led/) controlling an LED via USB to turn it on, off, or to a specified PWM value, including Python script to communicate with it

For additional information on the examples themselves, check their individual directories.


## Compiling and Flashing

To compile and flash the examples, please see the general instructions in [the parent directory's README](../). As the build system is designed to keep it as straightforward and consistent as possible between the different examples, they all share the same [common build environment](common/), and therefore building and flashing will be the same for all of them.

If the examples don't have any specific build instructions themselves, it means that there's nothing different about them and the common compiling and flashing instructions apply.

