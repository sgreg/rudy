EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:rudy-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "RUDY - the Random USB Device"
Date "2017-08-10"
Rev "A"
Comp "Sven Gregori <sven@craplab.fi>"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ATMEGA328-P IC1
U 1 1 56DA1270
P 7250 3000
F 0 "IC1" H 6500 4250 50  0000 L BNN
F 1 "ATMEGA328-P" H 7650 1600 50  0000 L BNN
F 2 "Housings_DIP:DIP-28_W7.62mm" H 7250 3000 50  0000 C CIN
F 3 "" H 7250 3000 50  0000 C CNN
	1    7250 3000
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X14 P2
U 1 1 56DA12E7
P 9850 3050
F 0 "P2" H 9850 3800 50  0000 C CNN
F 1 "CONN2" V 9950 3050 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x14_Pitch2.54mm" H 9850 3050 50  0001 C CNN
F 3 "" H 9850 3050 50  0000 C CNN
	1    9850 3050
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X14 P1
U 1 1 56DA143A
P 9500 3050
F 0 "P1" H 9500 3800 50  0000 C CNN
F 1 "CONN1" V 9600 3050 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x14_Pitch2.54mm" H 9500 3050 50  0001 C CNN
F 3 "" H 9500 3050 50  0000 C CNN
	1    9500 3050
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 56DA16B2
P 5900 3150
F 0 "C1" H 5925 3250 50  0000 L CNN
F 1 "100n" H 5925 3050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 5938 3000 50  0001 C CNN
F 3 "" H 5900 3150 50  0000 C CNN
	1    5900 3150
	1    0    0    -1  
$EndComp
Text Label 8250 1900 0    60   ~ 0
PB0
Text Label 8250 2000 0    60   ~ 0
PB1
Text Label 8250 2100 0    60   ~ 0
PB2
Text Label 8250 2200 0    60   ~ 0
PB3
Text Label 8250 2300 0    60   ~ 0
PB4
Text Label 8250 2400 0    60   ~ 0
PB5
Text Label 8250 2500 0    60   ~ 0
PB6
Text Label 8250 2600 0    60   ~ 0
PB7
Text Label 8250 2750 0    60   ~ 0
PC0
Text Label 8250 2850 0    60   ~ 0
PC1
Text Label 8250 2950 0    60   ~ 0
PC2
Text Label 8250 3050 0    60   ~ 0
PC3
Text Label 8250 3150 0    60   ~ 0
PC4
Text Label 8250 3250 0    60   ~ 0
PC5
Text Label 8250 3500 0    60   ~ 0
PD0
Text Label 8250 3600 0    60   ~ 0
PD1
Text Label 8250 3350 0    60   ~ 0
#RESET
Text Label 8250 3700 0    60   ~ 0
PD2
Text Label 8250 3800 0    60   ~ 0
PD3
Text Label 8250 3900 0    60   ~ 0
PD4
Text Label 8250 4000 0    60   ~ 0
PD5
Text Label 8250 4100 0    60   ~ 0
PD6
Text Label 8250 4200 0    60   ~ 0
PD7
Text Label 6350 1900 2    60   ~ 0
VCC
Text Label 6350 2200 2    60   ~ 0
AVCC
Text Label 6350 2500 2    60   ~ 0
AREF
Text Label 6350 4100 2    60   ~ 0
GND
Text Label 6350 4200 2    60   ~ 0
GND
$Comp
L PWR_FLAG #FLG01
U 1 1 56DA1A41
P 6350 1900
F 0 "#FLG01" H 6350 1995 50  0001 C CNN
F 1 "PWR_FLAG" H 6350 2080 50  0000 C CNN
F 2 "" H 6350 1900 50  0000 C CNN
F 3 "" H 6350 1900 50  0000 C CNN
	1    6350 1900
	-1   0    0    1   
$EndComp
Text Label 9300 2400 2    60   ~ 0
#RESET
Text Label 9300 2500 2    60   ~ 0
PD0
Text Label 9300 2600 2    60   ~ 0
PD1
Text Label 9300 2700 2    60   ~ 0
PD2
Text Label 9300 2800 2    60   ~ 0
PD3
Text Label 9300 2900 2    60   ~ 0
PD4
Text Label 9300 3000 2    60   ~ 0
VCC
Text Label 9300 3100 2    60   ~ 0
GND
Text Label 9300 3200 2    60   ~ 0
PB6
Text Label 9300 3300 2    60   ~ 0
PB7
Text Label 9300 3400 2    60   ~ 0
PD5
Text Label 9300 3500 2    60   ~ 0
PD6
Text Label 9300 3600 2    60   ~ 0
PD7
Text Label 9300 3700 2    60   ~ 0
PB0
Text Label 10050 3700 0    60   ~ 0
PB1
Text Label 10050 3600 0    60   ~ 0
PB2
Text Label 10050 3500 0    60   ~ 0
PB3
Text Label 10050 3400 0    60   ~ 0
PB4
Text Label 10050 3300 0    60   ~ 0
PB5
Text Label 10050 3200 0    60   ~ 0
AVCC
Text Label 10050 3100 0    60   ~ 0
AREF
Text Label 10050 3000 0    60   ~ 0
GND
Text Label 10050 2900 0    60   ~ 0
PC0
Text Label 10050 2800 0    60   ~ 0
PC1
Text Label 10050 2700 0    60   ~ 0
PC2
Text Label 10050 2600 0    60   ~ 0
PC3
Text Label 10050 2500 0    60   ~ 0
PC4
Text Label 10050 2400 0    60   ~ 0
PC5
$Comp
L PWR_FLAG #FLG02
U 1 1 56DA230A
P 6350 2200
F 0 "#FLG02" H 6350 2295 50  0001 C CNN
F 1 "PWR_FLAG" H 6350 2380 50  0000 C CNN
F 2 "" H 6350 2200 50  0000 C CNN
F 3 "" H 6350 2200 50  0000 C CNN
	1    6350 2200
	-1   0    0    1   
$EndComp
$Comp
L USB_B P4
U 1 1 59695E35
P 1100 1550
F 0 "P4" H 1300 1350 50  0000 C CNN
F 1 "USB_B" H 1050 1750 50  0000 C CNN
F 2 "Connect:USB_Mini-B" V 1050 1450 50  0001 C CNN
F 3 "" V 1050 1450 50  0000 C CNN
	1    1100 1550
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 59695F92
P 1750 3950
F 0 "R4" V 1830 3950 50  0000 C CNN
F 1 "1M" V 1750 3950 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 1680 3950 50  0001 C CNN
F 3 "" H 1750 3950 50  0000 C CNN
	1    1750 3950
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 59695FED
P 3150 3350
F 0 "R2" V 3230 3350 50  0000 C CNN
F 1 "68R" V 3150 3350 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 3080 3350 50  0001 C CNN
F 3 "" H 3150 3350 50  0000 C CNN
	1    3150 3350
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 59696022
P 3150 3550
F 0 "R3" V 3230 3550 50  0000 C CNN
F 1 "1k5" V 3150 3550 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 3080 3550 50  0001 C CNN
F 3 "" H 3150 3550 50  0000 C CNN
	1    3150 3550
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 5969606A
P 3150 3150
F 0 "R1" V 3230 3150 50  0000 C CNN
F 1 "68R" V 3150 3150 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 3080 3150 50  0001 C CNN
F 3 "" H 3150 3150 50  0000 C CNN
	1    3150 3150
	0    1    1    0   
$EndComp
$Comp
L GND #PWR03
U 1 1 596975E8
P 1750 5200
F 0 "#PWR03" H 1750 4950 50  0001 C CNN
F 1 "GND" H 1750 5050 50  0000 C CNN
F 2 "" H 1750 5200 50  0000 C CNN
F 3 "" H 1750 5200 50  0000 C CNN
	1    1750 5200
	1    0    0    -1  
$EndComp
$Comp
L CP C2
U 1 1 59697689
P 2700 1950
F 0 "C2" H 2725 2050 50  0000 L CNN
F 1 "10u" H 2725 1850 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:CP_Tantalum_Case-A_EIA-3216-18_Reflow" H 2738 1800 50  0001 C CNN
F 3 "" H 2700 1950 50  0000 C CNN
	1    2700 1950
	1    0    0    -1  
$EndComp
$Comp
L CP C3
U 1 1 596976FA
P 4000 1950
F 0 "C3" H 4025 2050 50  0000 L CNN
F 1 "10u" H 4025 1850 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:CP_Tantalum_Case-A_EIA-3216-18_Reflow" H 4038 1800 50  0001 C CNN
F 3 "" H 4000 1950 50  0000 C CNN
	1    4000 1950
	1    0    0    -1  
$EndComp
$Comp
L LD1117S33TR U1
U 1 1 59697888
P 3400 1400
F 0 "U1" H 3400 1650 50  0000 C CNN
F 1 "LD1117S33TR" H 3400 1600 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-223" H 3400 1500 50  0000 C CNN
F 3 "" H 3400 1400 50  0000 C CNN
	1    3400 1400
	1    0    0    -1  
$EndComp
$Comp
L Crystal Y1
U 1 1 59729C28
P 3050 5950
F 0 "Y1" H 3050 6100 50  0000 C CNN
F 1 "Crystal" H 3050 5800 50  0000 C CNN
F 2 "Crystals:Crystal_HC49-U_Vertical" H 3050 5950 50  0001 C CNN
F 3 "" H 3050 5950 50  0000 C CNN
	1    3050 5950
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 59729D6D
P 2600 6350
F 0 "C4" H 2625 6450 50  0000 L CNN
F 1 "22p" H 2625 6250 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 2638 6200 50  0001 C CNN
F 3 "" H 2600 6350 50  0000 C CNN
	1    2600 6350
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 59729E30
P 3500 6350
F 0 "C5" H 3525 6450 50  0000 L CNN
F 1 "22p" H 3525 6250 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 3538 6200 50  0001 C CNN
F 3 "" H 3500 6350 50  0000 C CNN
	1    3500 6350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 5972A2AC
P 3400 2600
F 0 "#PWR04" H 3400 2350 50  0001 C CNN
F 1 "GND" H 3400 2450 50  0000 C CNN
F 2 "" H 3400 2600 50  0000 C CNN
F 3 "" H 3400 2600 50  0000 C CNN
	1    3400 2600
	1    0    0    -1  
$EndComp
$Comp
L JUMPER3 JP1
U 1 1 5972A6C3
P 4300 1000
F 0 "JP1" H 4350 900 50  0000 L CNN
F 1 "JUMPER3" H 4300 1100 50  0000 C BNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 4300 1000 50  0001 C CNN
F 3 "" H 4300 1000 50  0000 C CNN
	1    4300 1000
	0    -1   -1   0   
$EndComp
Text Label 4750 1000 0    60   ~ 0
VCC
$Comp
L ZENER D1
U 1 1 5972B2E0
P 2400 4250
F 0 "D1" H 2400 4350 50  0000 C CNN
F 1 "3V6" H 2400 4150 50  0000 C CNN
F 2 "Diodes_SMD:D_MiniMELF" H 2400 4250 50  0001 C CNN
F 3 "" H 2400 4250 50  0000 C CNN
	1    2400 4250
	0    1    1    0   
$EndComp
$Comp
L ZENER D2
U 1 1 5972B3B7
P 2700 4250
F 0 "D2" H 2700 4350 50  0000 C CNN
F 1 "3V6" H 2700 4150 50  0000 C CNN
F 2 "Diodes_SMD:D_MiniMELF" H 2700 4250 50  0001 C CNN
F 3 "" H 2700 4250 50  0000 C CNN
	1    2700 4250
	0    1    1    0   
$EndComp
Text Label 3650 3350 0    60   ~ 0
USB_D+
Text Label 3650 3150 0    60   ~ 0
USB_D-
Text Label 3650 3550 0    60   ~ 0
USB_RESET
$Comp
L GND #PWR05
U 1 1 5972C24B
P 3100 6700
F 0 "#PWR05" H 3100 6450 50  0001 C CNN
F 1 "GND" H 3100 6550 50  0000 C CNN
F 2 "" H 3100 6700 50  0000 C CNN
F 3 "" H 3100 6700 50  0000 C CNN
	1    3100 6700
	1    0    0    -1  
$EndComp
Text Label 2100 5950 2    60   ~ 0
XTAL1
Text Label 3950 5950 0    60   ~ 0
XTAL2
Wire Wire Line
	6350 4200 6350 4100
Wire Wire Line
	3400 1650 3400 2600
Wire Wire Line
	1400 1350 3000 1350
Wire Wire Line
	2700 2100 2700 2350
Wire Wire Line
	2700 2350 3400 2350
Connection ~ 3400 2350
Wire Wire Line
	3400 2400 4000 2400
Wire Wire Line
	4000 2400 4000 2100
Connection ~ 3400 2400
Wire Wire Line
	4000 1800 4000 1350
Wire Wire Line
	3800 1350 4300 1350
Wire Wire Line
	4300 1350 4300 1250
Connection ~ 4000 1350
Wire Wire Line
	4400 1000 4750 1000
Wire Wire Line
	2700 1800 2700 1350
Connection ~ 2700 1350
Wire Wire Line
	4300 750  1950 750 
Wire Wire Line
	1950 750  1950 1350
Connection ~ 1950 1350
Wire Wire Line
	1400 1650 1750 1650
Wire Wire Line
	1750 1650 1750 3800
Wire Wire Line
	1400 1550 1950 1550
Wire Wire Line
	1950 1550 1950 3550
Connection ~ 1950 3150
Connection ~ 1750 3350
Wire Wire Line
	1750 4100 1750 5200
Wire Wire Line
	2400 4050 2400 3150
Connection ~ 2400 3150
Wire Wire Line
	2700 4050 2700 3350
Connection ~ 2700 3350
Wire Wire Line
	2400 4450 2400 4600
Wire Wire Line
	2400 4600 1750 4600
Connection ~ 1750 4600
Wire Wire Line
	2700 4450 2700 4900
Wire Wire Line
	2700 4900 1750 4900
Connection ~ 1750 4900
Wire Wire Line
	2600 6500 2600 6600
Wire Wire Line
	2600 6600 3500 6600
Wire Wire Line
	3500 6600 3500 6500
Wire Wire Line
	3100 6700 3100 6600
Connection ~ 3100 6600
Wire Wire Line
	2100 5950 2900 5950
Wire Wire Line
	2600 5950 2600 6200
Wire Wire Line
	3200 5950 3950 5950
Wire Wire Line
	3500 5950 3500 6200
Connection ~ 2600 5950
Connection ~ 3500 5950
Wire Wire Line
	6550 5400 7350 5400
Wire Wire Line
	6550 5300 7350 5300
Wire Wire Line
	6550 5200 7350 5200
Wire Wire Line
	6550 5500 7350 5500
Wire Wire Line
	6550 5600 7350 5600
Text Label 6550 5200 2    60   ~ 0
XTAL1
Text Label 6550 5300 2    60   ~ 0
XTAL2
Text Label 6550 5400 2    60   ~ 0
USB_D+
Text Label 6550 5500 2    60   ~ 0
USB_D-
Text Label 6550 5600 2    60   ~ 0
USB_RESET
Text Label 7350 5200 0    60   ~ 0
PB6
Text Label 7350 5300 0    60   ~ 0
PB7
Text Label 7350 5400 0    60   ~ 0
PD2
Text Label 7350 5500 0    60   ~ 0
PD3
Text Label 7350 5600 0    60   ~ 0
PD4
$Comp
L JUMPER JP2
U 1 1 59734F16
P 9800 4650
F 0 "JP2" H 9800 4800 50  0000 C CNN
F 1 "JUMPER" H 9800 4570 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 9800 4650 50  0001 C CNN
F 3 "" H 9800 4650 50  0000 C CNN
	1    9800 4650
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X03 P3
U 1 1 597350D9
P 9900 5250
F 0 "P3" H 9900 5450 50  0000 C CNN
F 1 "SERPROG" H 9900 5050 50  0000 C CNN
F 2 "Connect:IDC_Header_Straight_6pins" H 9900 4050 50  0001 C CNN
F 3 "" H 9900 4050 50  0000 C CNN
	1    9900 5250
	1    0    0    -1  
$EndComp
Text Label 9650 5150 2    60   ~ 0
SPI_MISO
Text Label 9650 5250 2    60   ~ 0
SPI_SCK
Text Label 9650 5350 2    60   ~ 0
#RESET
Text Label 10150 5250 0    60   ~ 0
SPI_MOSI
Text Label 10150 5350 0    60   ~ 0
GND
Wire Wire Line
	6550 5700 7350 5700
Wire Wire Line
	6550 5800 7350 5800
Wire Wire Line
	6550 5900 7350 5900
Text Label 6550 5700 2    60   ~ 0
SPI_MISO
Text Label 6550 5900 2    60   ~ 0
SPI_SCK
Text Label 6550 5800 2    60   ~ 0
SPI_MOSI
Text Label 7350 5900 0    60   ~ 0
PB5
Text Label 7350 5700 0    60   ~ 0
PB4
Text Label 7350 5800 0    60   ~ 0
PB3
Wire Wire Line
	10150 5150 10400 5150
Wire Wire Line
	10400 5150 10400 4650
Wire Wire Line
	10400 4650 10100 4650
Wire Wire Line
	9500 4650 9150 4650
Text Label 9150 4650 2    60   ~ 0
VCC
Wire Wire Line
	6350 1900 5900 1900
Wire Wire Line
	5900 1900 5900 3000
Wire Wire Line
	5900 3300 5900 4200
Wire Wire Line
	5900 4200 6350 4200
Connection ~ 6350 4200
Text Notes 1300 7350 0    60   ~ 0
Crystal and capacitor values depend on supply voltage.\nIf voltage regulator is omitted and whole system operates on 5V, crystal could be 16MHz.\nIf 3.3V voltage regulator is used, 16MHz is out of the ATmega's spec and may or may not\noperate stable. With 3.3V supply voltage, 13.3MHz is the limit of safe operating space, so\n12MHz or 12.8MHz might be the safest choice.
Text Notes 4200 1750 0    60   ~ 0
U1 and C3 can be omitted, and\nand JP1 shorted, if there is no\nneed for 3.3V supply voltage.
Text Notes 3000 4400 0    60   ~ 0
D1 and D2 can be omitted if there is no\nneed for 5V supply voltage, and 3.3V\nregulator is always used. JP1 could be\nshorted accordingly then.
Wire Wire Line
	3300 3150 3650 3150
Wire Wire Line
	3300 3350 3650 3350
Wire Wire Line
	1750 3350 3000 3350
Wire Wire Line
	1950 3150 3000 3150
Wire Wire Line
	3300 3550 3650 3550
Wire Wire Line
	1950 3550 3000 3550
$Comp
L GND #PWR06
U 1 1 598BB025
P 1000 2200
F 0 "#PWR06" H 1000 1950 50  0001 C CNN
F 1 "GND" H 1000 2050 50  0000 C CNN
F 2 "" H 1000 2200 50  0000 C CNN
F 3 "" H 1000 2200 50  0000 C CNN
	1    1000 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 1950 1000 2200
Wire Wire Line
	1100 1950 1100 2050
Wire Wire Line
	1100 2050 1000 2050
Connection ~ 1000 2050
$EndSCHEMATC
