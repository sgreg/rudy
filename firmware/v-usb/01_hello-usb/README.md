## RUDY - Example 01: Hello USB

A simple, dummy USB device that does nothing but being recognized as such.

When plugging in, the following information should be visible in the syslog or `dmesg`:

```
[39185.651461] usb 2-3.3: new low-speed USB device number 17 using xhci_hcd
[39185.746374] usb 2-3.3: New USB device found, idVendor=1209, idProduct=b00b, bcdDevice= 1.00
[39185.746379] usb 2-3.3: New USB device strings: Mfr=1, Product=2, SerialNumber=0
[39185.746383] usb 2-3.3: Product: RUDY
[39185.746385] usb 2-3.3: Manufacturer: CrapLab

```

And `lsusb` should have a line like this:

```
Bus 002 Device 017: ID 1209:b00b Generic CrapLab Random Device
```

See how the "`device number`" in the syslog output matches the "`Device`" output in `dmesg`, in this case: 17. And for more verbose output:

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
  iSerial                 0 
  bNumConfigurations      1
  Configuration Descriptor:
...
```

and so on.
