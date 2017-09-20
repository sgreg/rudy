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
LIBS:rudy-usbasp-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "RUDY USBasp Adapter Board"
Date "2017-09-21"
Rev "A"
Comp "Sven Gregori <sven@craplab.fi>"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_02X03 J3
U 1 1 599B7A8E
P 6850 3950
F 0 "J3" H 6850 4150 50  0000 C CNN
F 1 "ISP 6pin" H 6850 3750 50  0000 C CNN
F 2 "Connect:IDC_Header_Straight_6pins" H 6850 2750 50  0001 C CNN
F 3 "" H 6850 2750 50  0001 C CNN
	1    6850 3950
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X05 J4
U 1 1 599B7ACF
P 8600 3950
F 0 "J4" H 8600 4250 50  0000 C CNN
F 1 "ISP 10pin" H 8600 3650 50  0000 C CNN
F 2 "Connect:IDC_Header_Straight_10pins" H 8600 2750 50  0001 C CNN
F 3 "" H 8600 2750 50  0001 C CNN
	1    8600 3950
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X14 J1
U 1 1 599B7C42
P 3050 3900
F 0 "J1" H 3050 4650 50  0000 C CNN
F 1 "CONN_01X14" V 3150 3900 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x14_Pitch2.54mm" H 3050 3900 50  0001 C CNN
F 3 "" H 3050 3900 50  0001 C CNN
	1    3050 3900
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X14 J2
U 1 1 599B7CFE
P 3750 3900
F 0 "J2" H 3750 4650 50  0000 C CNN
F 1 "CONN_01X14" V 3850 3900 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x14_Pitch2.54mm" H 3750 3900 50  0001 C CNN
F 3 "" H 3750 3900 50  0001 C CNN
	1    3750 3900
	-1   0    0    1   
$EndComp
$Comp
L R R1
U 1 1 599B7D56
P 4600 2600
F 0 "R1" V 4680 2600 50  0000 C CNN
F 1 "1k" V 4600 2600 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 4530 2600 50  0001 C CNN
F 3 "" H 4600 2600 50  0001 C CNN
	1    4600 2600
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 599B7DA6
P 4900 2600
F 0 "R2" V 4980 2600 50  0000 C CNN
F 1 "1k" V 4900 2600 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 4830 2600 50  0001 C CNN
F 3 "" H 4900 2600 50  0001 C CNN
	1    4900 2600
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 599B7DD4
P 4600 3050
F 0 "D1" H 4600 3150 50  0000 C CNN
F 1 "LED" H 4600 2950 50  0000 C CNN
F 2 "LEDs:LED_0805" H 4600 3050 50  0001 C CNN
F 3 "" H 4600 3050 50  0001 C CNN
	1    4600 3050
	0    -1   -1   0   
$EndComp
$Comp
L LED D2
U 1 1 599B7E7C
P 4900 3050
F 0 "D2" H 4900 3150 50  0000 C CNN
F 1 "LED" H 4900 2950 50  0000 C CNN
F 2 "LEDs:LED_0805" H 4900 3050 50  0001 C CNN
F 3 "" H 4900 3050 50  0001 C CNN
	1    4900 3050
	0    -1   -1   0   
$EndComp
NoConn ~ 2850 3250
NoConn ~ 2850 3350
NoConn ~ 2850 3450
NoConn ~ 2850 3550
NoConn ~ 2850 3650
NoConn ~ 2850 3750
NoConn ~ 2850 4050
NoConn ~ 2850 4150
NoConn ~ 2850 4250
NoConn ~ 2850 4350
NoConn ~ 2850 4450
NoConn ~ 2850 4550
Wire Wire Line
	2600 3850 2850 3850
Wire Wire Line
	2600 3000 2600 4900
Wire Wire Line
	2600 4900 4250 4900
Wire Wire Line
	4250 4900 4250 4050
Wire Wire Line
	4250 4050 3950 4050
Wire Wire Line
	2850 3950 2450 3950
Wire Wire Line
	2450 3950 2450 5700
Wire Wire Line
	2450 5050 4400 5050
Wire Wire Line
	4400 5050 4400 3850
Wire Wire Line
	4400 3850 3950 3850
NoConn ~ 3950 3250
NoConn ~ 3950 3350
NoConn ~ 3950 3450
NoConn ~ 3950 3550
NoConn ~ 3950 3950
Wire Wire Line
	3950 3650 4600 3650
Wire Wire Line
	4600 3650 4600 3200
Wire Wire Line
	4600 2900 4600 2750
Wire Wire Line
	3950 3750 4900 3750
Wire Wire Line
	4900 3750 4900 3200
Wire Wire Line
	4900 2900 4900 2750
$Comp
L VCC #PWR01
U 1 1 599B840C
P 4600 2250
F 0 "#PWR01" H 4600 2100 50  0001 C CNN
F 1 "VCC" H 4600 2400 50  0000 C CNN
F 2 "" H 4600 2250 50  0001 C CNN
F 3 "" H 4600 2250 50  0001 C CNN
	1    4600 2250
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR02
U 1 1 599B844B
P 4900 2250
F 0 "#PWR02" H 4900 2100 50  0001 C CNN
F 1 "VCC" H 4900 2400 50  0000 C CNN
F 2 "" H 4900 2250 50  0001 C CNN
F 3 "" H 4900 2250 50  0001 C CNN
	1    4900 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 2250 4900 2450
Wire Wire Line
	4600 2250 4600 2450
$Comp
L VCC #PWR03
U 1 1 599B84C3
P 2600 3000
F 0 "#PWR03" H 2600 2850 50  0001 C CNN
F 1 "VCC" H 2600 3150 50  0000 C CNN
F 2 "" H 2600 3000 50  0001 C CNN
F 3 "" H 2600 3000 50  0001 C CNN
	1    2600 3000
	1    0    0    -1  
$EndComp
Connection ~ 2600 3850
$Comp
L GND #PWR04
U 1 1 599B8527
P 2450 5700
F 0 "#PWR04" H 2450 5450 50  0001 C CNN
F 1 "GND" H 2450 5550 50  0000 C CNN
F 2 "" H 2450 5700 50  0001 C CNN
F 3 "" H 2450 5700 50  0001 C CNN
	1    2450 5700
	1    0    0    -1  
$EndComp
Text Label 4750 4350 0    60   ~ 0
MOSI
Text Label 4750 4250 0    60   ~ 0
MISO
Text Label 4750 4150 0    60   ~ 0
SCK
Text Label 4750 4450 0    60   ~ 0
RESET
NoConn ~ 3950 4550
Wire Wire Line
	3950 4150 4750 4150
Wire Wire Line
	3950 4250 4750 4250
Wire Wire Line
	3950 4350 4750 4350
Wire Wire Line
	3950 4450 4750 4450
$Comp
L VCC #PWR05
U 1 1 599B88B5
P 7350 3600
F 0 "#PWR05" H 7350 3450 50  0001 C CNN
F 1 "VCC" H 7350 3750 50  0000 C CNN
F 2 "" H 7350 3600 50  0001 C CNN
F 3 "" H 7350 3600 50  0001 C CNN
	1    7350 3600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 599B88FC
P 7350 4300
F 0 "#PWR06" H 7350 4050 50  0001 C CNN
F 1 "GND" H 7350 4150 50  0000 C CNN
F 2 "" H 7350 4300 50  0001 C CNN
F 3 "" H 7350 4300 50  0001 C CNN
	1    7350 4300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 599B894C
P 9100 4300
F 0 "#PWR07" H 9100 4050 50  0001 C CNN
F 1 "GND" H 9100 4150 50  0000 C CNN
F 2 "" H 9100 4300 50  0001 C CNN
F 3 "" H 9100 4300 50  0001 C CNN
	1    9100 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8850 4150 9100 4150
Wire Wire Line
	9100 4050 9100 4300
Wire Wire Line
	8850 4050 9100 4050
Connection ~ 9100 4150
NoConn ~ 8850 3950
NoConn ~ 8850 3850
Wire Wire Line
	7100 4050 7350 4050
Wire Wire Line
	7350 4050 7350 4300
$Comp
L VCC #PWR08
U 1 1 599B8A1D
P 9100 3600
F 0 "#PWR08" H 9100 3450 50  0001 C CNN
F 1 "VCC" H 9100 3750 50  0000 C CNN
F 2 "" H 9100 3600 50  0001 C CNN
F 3 "" H 9100 3600 50  0001 C CNN
	1    9100 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8850 3750 9100 3750
Wire Wire Line
	9100 3750 9100 3600
Wire Wire Line
	7100 3850 7350 3850
Wire Wire Line
	7350 3850 7350 3600
Text Label 7350 3950 0    60   ~ 0
MOSI
Wire Wire Line
	7350 3950 7100 3950
Text Label 6350 3850 2    60   ~ 0
MISO
Wire Wire Line
	6350 3850 6600 3850
Text Label 6350 3950 2    60   ~ 0
SCK
Text Label 6350 4050 2    60   ~ 0
RESET
Wire Wire Line
	6350 3950 6600 3950
Wire Wire Line
	6350 4050 6600 4050
Text Label 8100 3750 2    60   ~ 0
MOSI
Wire Wire Line
	8350 3750 8100 3750
NoConn ~ 8350 3850
Text Label 8100 3950 2    60   ~ 0
RESET
Text Label 8100 4050 2    60   ~ 0
SCK
Text Label 8100 4150 2    60   ~ 0
MISO
Wire Wire Line
	8100 3950 8350 3950
Wire Wire Line
	8100 4050 8350 4050
Wire Wire Line
	8100 4150 8350 4150
Connection ~ 2450 5050
$Comp
L PWR_FLAG #FLG09
U 1 1 599B966F
P 2300 3000
F 0 "#FLG09" H 2300 3075 50  0001 C CNN
F 1 "PWR_FLAG" H 2300 3150 50  0000 C CNN
F 2 "" H 2300 3000 50  0001 C CNN
F 3 "" H 2300 3000 50  0001 C CNN
	1    2300 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 3000 2300 3250
Wire Wire Line
	2300 3250 2600 3250
Connection ~ 2600 3250
$Comp
L PWR_FLAG #FLG010
U 1 1 599B9746
P 2100 5700
F 0 "#FLG010" H 2100 5775 50  0001 C CNN
F 1 "PWR_FLAG" H 2100 5850 50  0000 C CNN
F 2 "" H 2100 5700 50  0001 C CNN
F 3 "" H 2100 5700 50  0001 C CNN
	1    2100 5700
	-1   0    0    1   
$EndComp
Wire Wire Line
	2100 5700 2100 5400
Wire Wire Line
	2100 5400 2450 5400
Connection ~ 2450 5400
$EndSCHEMATC
