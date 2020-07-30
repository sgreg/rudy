# RUDY - V-USB Example 05: HID Mouse

This is the HID Mouse example taken straight from the [V-USB example](https://github.com/obdev/v-usb/tree/master/examples/hid-mouse) and adjusted to match for RUDY. All it does is act as a Mouse that moves around in circles.

The only real adjustment here is in the [`usbconfig-rudy.h`](usbconfig-rudy.h) values to match the ones set for the V-USB example. The code itself, written by Christian Starkjohann, is left as-is.

When plugged in, something along the following information should be visible in the syslog or `dmesg`:

```
186709.076775] usb 2-3.4: new low-speed USB device number 98 using xhci_hcd
[186709.171360] usb 2-3.4: New USB device found, idVendor=1209, idProduct=b00b, bcdDevice= 1.00
[186709.171366] usb 2-3.4: New USB device strings: Mfr=1, Product=2, SerialNumber=0
[186709.171369] usb 2-3.4: Product: RUDY
[186709.171372] usb 2-3.4: Manufacturer: CrapLab
[186709.184325] input: CrapLab RUDY as /devices/pci0000:00/0000:00:14.0/usb2/2-3/2-3.4/2-3.4:1.0/0003:1209:B00B.0003/input/input62
[186709.184642] hid-generic 0003:1209:B00B.0003: input,hidraw0: USB HID v1.01 Mouse [CrapLab RUDY] on usb-0000:00:14.0-3.4/input0
```

See the [V-USB repository](https://github.com/obdev/v-usb/tree/master/examples/hid-mouse) for more information.

