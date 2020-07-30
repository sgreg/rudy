# RUDY - V-USB Example 01: Hello USB

A simple, dummy USB device that does nothing but being recognized as such.

## Set it up

This example won't use any external components, so it requires is to plug the device via USB into your computer. Make sure you have the [jumper set correctly so the device powers up](../../#powering-rudy).

Once plugged in, the following information should be visible in the syslog or `dmesg` output:

```
[39185.651461] usb 2-3.3: new low-speed USB device number 17 using xhci_hcd
[39185.746374] usb 2-3.3: New USB device found, idVendor=1209, idProduct=b00b, bcdDevice= 1.00
[39185.746379] usb 2-3.3: New USB device strings: Mfr=1, Product=2, SerialNumber=0
[39185.746383] usb 2-3.3: Product: RUDY
[39185.746385] usb 2-3.3: Manufacturer: CrapLab
[39185.746386] usb 2-3.3: SerialNumber: Hello USB

```

And `lsusb` should show us a line like this:

```
Bus 002 Device 017: ID 1209:b00b Generic CrapLab Random Device
```

Having the bus (`002`) and device number (`017`, which matches the first `USB device number 17` line in the system log), we can use `lsusb` for some additional, verbose information about that device:

```
$ lsusb -v -s 002:017

Bus 002 Device 017: ID 1209:b00b Generic CrapLab Random Device
Device Descriptor:
  bLength                18
  bDescriptorType         1
  bcdUSB               1.10
  bDeviceClass          255 Vendor Specific Class
  bDeviceSubClass         0 
  bDeviceProtocol         0 
  bMaxPacketSize0         8
  idVendor           0x1209 Generic
  idProduct          0xb00b CrapLab Random Device
  bcdDevice            1.00
  iManufacturer           1 CrapLab
  iProduct                2 RUDY
  iSerial                 3 Hello USB
  bNumConfigurations      1
  Configuration Descriptor:
...
```

There's plenty more output, but this shows the interesting parts that make it clear this is indeed the Hello USB RUDY device. Hooray!

## Using it

This serves really only as a *very* simple Hello-World-ish example, so showing up in the syslog and `lsusb` is all there is to this.
