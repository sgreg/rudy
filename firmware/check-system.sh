#!/bin/bash
#
# RUDY - the Random USB Device
# Check System script to verify if the required tools are installed
#
# Copyright (C) 2020 Sven Gregori <sven@craplab.fi>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

#
# Tries to find all required executables and if it does, tries to compile
# a little dummy file to verify compilation itself really works.
#
# If required executables aren't found, and the Linux distribution used is
# either Debian based (e.g. Debian, Ubuntu, Linux Mint) or Red Hat based
# (e.g. Red Hat, Fedora, CentOS), the script will offer to install the
# missing packages right away. For other distribution (or MacOS / Cygwin),
# the script just says what's missing instead.
#
# Usage:
#   ./check-system.sh
#

# We might need to know what Linux distribution we're running on later,
# since Debian based ones use different package names than e.g. Red Hat
# based ditros. So let's check /etc/*release files for hints on that.
if grep -qEi 'debian|buntu|mint' /etc/*release 2>/dev/null ; then
    DISTRO="Debian"
elif grep -qEi 'fedora|redhat|centos' /etc/*release 2>/dev/null ; then
    DISTRO="Red Hat"
else
    DISTRO="Other"
fi

# Check if required tools exist..
echo -n "Checking if tools are available... "
# ..which we can assume they do if the system finds their executable's path
MAKE="$(which make 2>/dev/null)"
GCC="$(which avr-gcc 2>/dev/null)"
BINUTILS="$(which avr-objcopy 2>/dev/null)"
AVRDUDE="$(which avrdude 2>/dev/null)"

# Let's get through those results one by one and chain
# the missing package names together if necessary
missing=""

# Check if make executable was found
if [ -z "$MAKE" ] ; then
    # Nope, add it to the list of missing packages
    missing+="make "
fi

# Check if avr-gcc executable was found
if [ -z "$GCC" ] ; then
    # Nope.
    # Check if this is a Debian based distro to get the package name right
    if [ "$DISTRO" == "Debian" ] ; then
        missing+="gcc-avr "
    else
        missing+="avr-gcc "
    fi

    # If avr-gcc is missing, then avr-libc most certainly is as well
    missing+="avr-libc "
fi

# Repeat for binutils..
if [ -z "$BINUTILS" ] ; then
    if [ "$DISTRO" == "Debian" ] ; then
        missing+="binutils-avr "
    else
        missing+="avr-binutils "
    fi
fi

# ..and AVRDUDE
if [ -z "$AVRDUDE" ] ; then
    missing+="avrdude"
fi

# Check if there are missing packages
if [ -z "$missing" ] ; then
    # No, all good.
    echo "yes"
else
    # Yes, packages are missing.
    echo "no"
    echo ""
    echo "Required tools are missing, using the examples won't be possible."

    # If this is a Debian or Red Hat based distribution, offer to isntall
    # the packages right away via apt-get / dnf
    if [ "$DISTRO" == "Debian" ] ; then
        package_manager="apt-get"
    elif [ "$DISTRO" == "Red Hat" ] ; then
        package_manager="dnf"
    fi

    # ..assuming the package manager exists, which it probably should?
    if [ -n "$package_manager" ] && [ -n "$(which $package_manager 2>/dev/null)" ] ; then
        echo "You seem to run a $DISTRO based distribution, would you like to run"
        echo "    sudo $package_manager install $missing"
        read -p "right away? [Y/n] " choice

        # Check if answer was "y" (or nothing, which defaults to "y")
        if [ -z "$choice" ] || [[ ${choice,,} == "y" ]] ; then
            # Yep, let's get going then and exit the script for now.
            if sudo $package_manager install $missing ; then
                echo ""
                echo "Packages installed, run the script again to verify that all is good now."
                exit 0
            else
                echo ""
                echo "Running $package_manager failed, aborting."
            fi
        fi
        echo ""
    fi

    # If we're still here, something went wrong, installation offering was
    # rejected, or it's a Linux distribution where users will anyway make
    # their own decisions about how to install things.
    echo "Make sure to install the following tools: $missing"
    echo ""
    exit 1
fi

# Executables are available, that's a good start, but things could still fail.
# To make sure it really all works, and also the AVR implementation of libc
# (which includes all the header files) is available, the best way is to just
# create a little dummy C file and trying to compile it.
# If compilation succeeds, we can be pretty sure the examples will work.
echo -n "Trying to compile a dummy file... "
# Use temporary directory (somewhere in /tmp/tmp.XXXXXXXX)
builddir="$(mktemp -d)"

# Create dummy source file, which basically just sets up two GPIO ports using
# constants defined in the controller-specific io.h header file. If they are
# found, compilation will succeed meaning avr-libc is installed and we're all
# good to go. If compilation fails, avr-libc is most likely missing.
cat > $builddir/main.c << EOF
#include <avr/io.h>

int main(void)
{
    PORTD = (1 << PD5);
    DDRB = (1 << DDD3);
    while (1);
}
EOF

# Compile it and store the output in case things fail
out=$(avr-gcc -Os -std=gnu99 -mmcu=atmega328p $builddir/main.c -o $builddir/success 2>&1)

# Check if the output file exists
if [ -e $builddir/success ] ; then
    # It does - hooray. All good then.
    success=1
    echo "success"
else
    # It doesn't. Show compiler error.
    success=0
    echo "failed"
    echo ""
    echo "Cannot compile dummy file, compiler says:"
    echo "$out"
    echo ""
fi

# Remove the temporary build directory
rm -rf $builddir

# Give some final opinion and exit depending on the success state.
if [ $success -eq 1 ] ; then
    echo ""
    echo "All seems well and you're ready to go!"
    exit 0
else
    echo "Sorry, you won't be able to compile the examples."
    echo "Make sure you have the avr-libc package installed"
    echo ""
    exit 1
fi

