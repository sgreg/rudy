## RUDY - Example 01: Hello USB

A simple, dummy USB device that does nothing but being recognized as such.

When plugging in, the following information should be visible in the syslog or `dmesg`:

```
[629862.042354] usb 3-1.1: new low-speed USB device number 92 using xhci_hcd
[629862.135285] usb 3-1.1: New USB device found, idVendor=16c0, idProduct=05dc
[629862.135289] usb 3-1.1: New USB device strings: Mfr=1, Product=2, SerialNumber=0
[629862.135291] usb 3-1.1: Product: RUDY
[629862.135293] usb 3-1.1: Manufacturer: CrapLab

```

And `lsusb` should have a line like this:

```
Bus 003 Device 092: ID 16c0:05dc Van Ooijen Technische Informatica shared ID for use with libusb
```

See how the "`device number`" in the syslog output matches the "`Device`" output in `dmesg`, in this case: 92. And for more verbose output:

```
$ lsusb -v -s 003:092

Bus 003 Device 092: ID 16c0:05dc Van Ooijen Technische Informatica shared ID for use with libusb
Device Descriptor:
  bLength                18
  bDescriptorType         1
  bcdUSB               1.10
  bDeviceClass          255 Vendor Specific Class
  bDeviceSubClass         0 
  bDeviceProtocol         0 
  bMaxPacketSize0         8
  idVendor           0x16c0 Van Ooijen Technische Informatica
  idProduct          0x05dc shared ID for use with libusb
  bcdDevice            1.00
  iManufacturer           1 CrapLab
  iProduct                2 RUDY
  iSerial                 0 
  bNumConfigurations      1
  Configuration Descriptor:
...
```

and so on.
