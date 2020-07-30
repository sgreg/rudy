# RUDY - Common Files for Bare Metal Examples

All Bare Metal examples share common parts for the build environment that are collected here. This keeps the examples themselves short and focused on the part they're actually implementing, and makes extending / adding new examples easier.

At this point, `common.mk` is the only file here, and serves as main Makefile that sets up all the `make` targets, the general compiler settings as well as  AVRDUDE flag, and is included in each sproject-specific `Makefile`.


