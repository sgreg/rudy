# RUDY - the Random USB Device

RUDY is a test and play-around device for USB development, using the [Objecvtive Development V-USB library](https://www.obdev.at/products/vusb/index.html). The hardware is built as a breadboard-friendly prototyping board around the AVR ATmega328 microcontroller and its other family members (ATmega48/88/168) and any other controller that is pin-compatbile enough.

## Roadmap and TODO

* create hardware
    * ~~create schematic~~
    * ~~create PCB design~~
    * ~~order PCB from OSH Park~~
    * solder first prototype
* write firmware examples
    * MIDI example (see also [4chord MIDI](https://github.com/sgreg/4chord-midi))
    * simple HID example
    * custom class example
    * bootloader
* write matching software side examples
    * libusb test code in C
    * communication tool in Python
    * communication tool for Android

