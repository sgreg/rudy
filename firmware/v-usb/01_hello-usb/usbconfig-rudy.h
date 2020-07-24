#ifndef RUDY_USBCONFIG_H
#define RUDY_USBCONFIG_H


#define RUDY_IMPLEMENT_FN_READ 0
#define RUDY_IMPLEMENT_FN_WRITE 0
#define RUDY_IMPLEMENT_FN_WRITEOUT 0

#define RUDY_VENDOR_ID  0x09, 0x12 // -> 0x1209
#define RUDY_DEVICE_ID  0x0b, 0xb0 // -> 0xb00b

// comment out to not have one
#define RUDY_VENDOR_NAME    'C', 'r', 'a', 'p', 'L', 'a', 'b'
#define RUDY_VENDOR_NAME_LEN 7

// comment out to not have one
#define RUDY_DEVICE_NAME    'R', 'U', 'D', 'Y'
#define RUDY_DEVICE_NAME_LEN 4

// comment out to not have one
//#define RUDY_SERIAL_NUMBER 'N', 'o', 'p', 'e'
//#define RUDY_SERIAL_NUMBER_LEN 4

#define RUDY_DEVICE_CLASS 0xff
#define RUDY_DEVICE_SUBCLASS 0x00

#define RUDY_INTERFACE_CLASS     0
#define RUDY_INTERFACE_SUBCLASS  0
#define RUDY_INTERFACE_PROTOCOL  0

#define RUDY_HAVE_INTRIN_ENDPOINT   0
#define RUDY_HAVE_INTRIN_ENDPOINT3  0
#define RUDY_INTR_POLL_INTERVAL     10

#define RUDY_HID_REPORT_DESCRIPTOR_LENGTH   0

#define RUDY_DESCR_PROPS_DEVICE                  0
#define RUDY_DESCR_PROPS_CONFIGURATION           0
#define RUDY_DESCR_PROPS_STRINGS                 0
#define RUDY_DESCR_PROPS_STRING_0                0
#define RUDY_DESCR_PROPS_STRING_VENDOR           0
#define RUDY_DESCR_PROPS_STRING_PRODUCT          0
#define RUDY_DESCR_PROPS_STRING_SERIAL_NUMBER    0
#define RUDY_DESCR_PROPS_HID                     0
#define RUDY_DESCR_PROPS_HID_REPORT              0
#define RUDY_DESCR_PROPS_UNKNOWN                 0

#endif /* RUDY_USBCONFIG_H */
