# RUDY - Arduino Examples

Some very brief list of examples to use RUDY within the Arduino ecosytem.

Being a generic ATmega328 development board, RUDY naturally supports to run Arduino code as it doesn't differ much from an Arduino Uno from the compiler's point of view. The main difference, apart from not being an actual Arduino board, is a lower clock frequency (12MHz instead of 16MHz), which will affect anything that uses timers and other internal clocks (delays, UART, SPI, hardware timers, etc). To make things easier, [RUDY can be supported as 3rd part board package](https://github.com/sgreg/craplab-arduino).

Keep in mind that Arduino support is more of a side effect than the primary goal, and RUDY has no Arduino bootloader installed, so an external programmer is required and the sketch needs to be uploaded via the "Upload Using Programmer" option.


## List of Examples

- [`01_blinky`](01_blinky/) the classic blinking LED Hello World example (requires external LED)


## Limitations

### No Bootloader
As mentioned, RUDY has no Arduino bootloader installed, nor USB set up in a way that adding it could be easily achieved. It's probaby still possible - somewhat, maybe? - but there are no intentions to make that happen at this point. So in order to upload a sketch, you'll need an external programmer that's set up accordingly in the Arduino, and the "Upload Using Programmer" option has to be chosen instead of the normal "Upload" one.

### No Controllable On-Board LED
While RUDY does have LEDs, they are meant as power indicator, and are not connected to any of the ATmega328's pins<sup>[1]</sup>. So in order to run the [Blinky example](01_blinky/) (or any other simple LED blinking code), an external LED is needed.

<sup>[1]</sup> I thought about that option but decided against it, as the LEDs' primary purpose is to indicate that the board is actually powered on (and by that to avoid chasing ghosts in the code in case the jumpers were simply mixed up)

### Some Pins Shouldn't Be Used

Since RUDY has the V-USB circuitry wired to the ATmega328 - after all, USB development was the primary motivation for this board - those pins shouldn't be used for any other purpose, even if V-USB itself isn't used.

The pins in question have a circle placed around them on the board, which are:

| ATmega pin | Arduino pin | Usage     |
|    :---:   |    :---:    |   ----    |
|      4     |      2      | USB D+    |
|      5     |      3      | USB D-    |
|      6     |      4      | USB Reset |
|      9     |      -      | external crystal oscillator |
|     10     |      -      | external crystal oscillator |


## Pinout

Again, RUDY uses the same microncontroller as the Arduino Uno, so the pinout from Arduino's point of view is identical

```
                                   _______
                              .---|       |---.
                              | [ ]       [ ] |
                              |   |       |   |
                              |   |       |   |
                              | [ ]_|||||_[ ] |
                              |               |
                              |3V3 o  o  o 5V0|
                              |   ___   ___   |
                   Reset ---- |o-| 1 \_/ 28|-o| ---- A5
                  (RX) 0 ---- |o-| 2     27|-o| ---- A4
                  (TX) 1 ---- |o-| 3     26|-o| ---- A3
                       x ---- |o-| 4     25|-o| ---- A2
                       x ---- |o-| 5     24|-o| ---- A1
                       x ---- |o-| 6     23|-o| ---- A0
                     VCC ---- |o-| 7     22|-o| ---- GND
                     GND ---- |o-| 8     21|-o| ---- AREF
                 Crystal ---- |o-| 9     20|-o| ---- AVCC
                 Crystal ---- |o-|10     19|-o| ---- 13
                 (PWM) 5 ---- |o-|11     18|-o| ---- 12
                 (PWM) 6 ---- |o-|12     17|-o| ---- 11 (PWM)
                       7 ---- |o-|13     16|-o| ---- 10 (PWM)
                       8 ---- |o-|14     15|-o| ----  9 (PWM)
                              |  '---------'  |
                              | _________     |
                              |/         \  o |
                              |\_________/  o |
                              | ____     ____ |
                              ||    '---'    ||
                              ||   o  o  o   ||
                              ||   o  o  o   ||
                              ||_____________||
                              '---------------'
```
