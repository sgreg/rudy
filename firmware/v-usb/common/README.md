# RUDY - Common Files for V-USB Examples

All V-USB examples have common parts for both the source code and the build environment that are collected here. This keeps the examples themselves short and focused on the part they're actually implementing, and makes extending / adding new examples easier.

- `common.mk` the main Makefile, setting up all the `make` targets, the general compiler settings as well as AVRDUDE flags, and is included in each project-specific `Makefile`.
- `usbdrv/` contains the [V-USB library](https://www.obdev.at/products/vusb/index.html) source code as-is, and is based on the vusb-20121206 release
- `usbconfig.h` the main V-USB configuration file, set up to correspond with RUDY's pin configuration, and defining most other values as `RUDY_` prefixed constants that each example source can define as required
- `usbconfig-rudy.h` a default implementation of those `RUDY_` prefixed, project-specific values in case a project itself doesn't define its own header file for that. This primarily serves as a sample template and causes a warning if it's included, as it's recommended that an example will have its own version of this.

