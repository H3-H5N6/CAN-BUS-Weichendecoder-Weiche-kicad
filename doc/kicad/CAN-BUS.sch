EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	8350 3000 8100 3000
Wire Wire Line
	8350 3100 8100 3100
Wire Wire Line
	8100 3200 8350 3200
Wire Wire Line
	8350 3300 8100 3300
Wire Wire Line
	8100 3400 8350 3400
Wire Wire Line
	8350 3500 8100 3500
Wire Wire Line
	8350 3600 8100 3600
Wire Wire Line
	8350 3700 8100 3700
$Comp
L Transistor_Array:ULN2803A U5
U 1 1 6041A47D
P 8750 3200
F 0 "U5" H 8750 3767 50  0000 C CNN
F 1 "ULN2803A" H 8750 3676 50  0000 C CNN
F 2 "Package_DIP:DIP-18_W7.62mm" H 8800 2550 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/uln2803a.pdf" H 8850 3000 50  0001 C CNN
	1    8750 3200
	1    0    0    -1  
$EndComp
$Comp
L Interface_Expansion:PCF8574 U2
U 1 1 60418056
P 7600 3400
F 0 "U2" H 7300 4050 50  0000 C CNN
F 1 "PCF8574" H 7600 3600 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 7600 3400 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/PCF8574_PCF8574A.pdf" H 7600 3400 50  0001 C CNN
	1    7600 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 1450 8350 1450
Wire Wire Line
	8350 1350 8100 1350
$Comp
L Interface_Expansion:PCF8574 U1
U 1 1 604173C8
P 7600 1750
F 0 "U1" H 7300 2400 50  0000 C CNN
F 1 "PCF8574" H 7600 2000 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 7600 1750 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/PCF8574_PCF8574A.pdf" H 7600 1750 50  0001 C CNN
	1    7600 1750
	1    0    0    -1  
$EndComp
$Comp
L Transistor_Array:ULN2803A U4
U 1 1 60418EE2
P 8750 1550
F 0 "U4" H 8750 2117 50  0000 C CNN
F 1 "ULN2803A" H 8750 2026 50  0000 C CNN
F 2 "Package_DIP:DIP-18_W7.62mm" H 8800 900 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/uln2803a.pdf" H 8850 1350 50  0001 C CNN
	1    8750 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 1550 8350 1550
Wire Wire Line
	8100 1650 8350 1650
Wire Wire Line
	8350 1750 8100 1750
Wire Wire Line
	8100 1850 8350 1850
Wire Wire Line
	8100 1950 8350 1950
Wire Wire Line
	8100 2050 8350 2050
$Comp
L MCU_Module:Arduino_Nano_v3.x A1
U 1 1 60416171
P 4950 2350
F 0 "A1" H 4750 1300 50  0000 C CNN
F 1 "Arduino_Nano" H 5000 2700 50  0000 C CNN
F 2 "Modules:Arduino_Nano" H 4950 2350 50  0001 C CIN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 4950 2350 50  0001 C CNN
	1    4950 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 1350 6750 1350
Wire Wire Line
	6750 1350 6750 2850
Wire Wire Line
	7100 1450 6850 1450
Wire Wire Line
	6850 1450 6850 2750
Wire Wire Line
	6850 2750 5450 2750
$Comp
L power:GND #PWR0101
U 1 1 604883CE
P 7600 2450
F 0 "#PWR0101" H 7600 2200 50  0001 C CNN
F 1 "GND" H 7700 2450 50  0000 C CNN
F 2 "" H 7600 2450 50  0001 C CNN
F 3 "" H 7600 2450 50  0001 C CNN
	1    7600 2450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 60488B69
P 7600 4100
F 0 "#PWR0102" H 7600 3850 50  0001 C CNN
F 1 "GND" H 7605 3927 50  0000 C CNN
F 2 "" H 7600 4100 50  0001 C CNN
F 3 "" H 7600 4100 50  0001 C CNN
	1    7600 4100
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0103
U 1 1 60489399
P 7600 1050
F 0 "#PWR0103" H 7600 900 50  0001 C CNN
F 1 "+5V" H 7800 1050 50  0000 C CNN
F 2 "" H 7600 1050 50  0001 C CNN
F 3 "" H 7600 1050 50  0001 C CNN
	1    7600 1050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0104
U 1 1 6048A0D6
P 7600 2700
F 0 "#PWR0104" H 7600 2550 50  0001 C CNN
F 1 "+5V" H 7700 2700 50  0000 C CNN
F 2 "" H 7600 2700 50  0001 C CNN
F 3 "" H 7600 2700 50  0001 C CNN
	1    7600 2700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 604AE05B
P 8750 2250
F 0 "#PWR0105" H 8750 2000 50  0001 C CNN
F 1 "GND" H 8755 2077 50  0000 C CNN
F 2 "" H 8750 2250 50  0001 C CNN
F 3 "" H 8750 2250 50  0001 C CNN
	1    8750 2250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 604AE7F2
P 8750 3900
F 0 "#PWR0106" H 8750 3650 50  0001 C CNN
F 1 "GND" H 8755 3727 50  0000 C CNN
F 2 "" H 8750 3900 50  0001 C CNN
F 3 "" H 8750 3900 50  0001 C CNN
	1    8750 3900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 604AF486
P 7100 1850
F 0 "#PWR0107" H 7100 1600 50  0001 C CNN
F 1 "GND" H 7105 1677 50  0000 C CNN
F 2 "" H 7100 1850 50  0001 C CNN
F 3 "" H 7100 1850 50  0001 C CNN
	1    7100 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 1650 7100 1750
Wire Wire Line
	7100 1750 7100 1850
Connection ~ 7100 1750
Connection ~ 7100 1850
Wire Wire Line
	6850 2750 6850 3100
Wire Wire Line
	6850 3100 7100 3100
Connection ~ 6850 2750
Wire Wire Line
	7100 3000 6750 3000
Connection ~ 6750 2850
Wire Wire Line
	8350 4950 8100 4950
Wire Wire Line
	8350 5050 8100 5050
Wire Wire Line
	8100 5150 8350 5150
Wire Wire Line
	8350 5250 8100 5250
Wire Wire Line
	8100 5350 8350 5350
Wire Wire Line
	8350 5450 8100 5450
Wire Wire Line
	8350 5550 8100 5550
Wire Wire Line
	8350 5650 8100 5650
$Comp
L Transistor_Array:ULN2803A U6
U 1 1 60572018
P 8750 5150
F 0 "U6" H 8750 5717 50  0000 C CNN
F 1 "ULN2803A" H 8750 5626 50  0000 C CNN
F 2 "Package_DIP:DIP-18_W7.62mm" H 8800 4500 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/uln2803a.pdf" H 8850 4950 50  0001 C CNN
	1    8750 5150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 60572024
P 7600 6050
F 0 "#PWR0108" H 7600 5800 50  0001 C CNN
F 1 "GND" H 7605 5877 50  0000 C CNN
F 2 "" H 7600 6050 50  0001 C CNN
F 3 "" H 7600 6050 50  0001 C CNN
	1    7600 6050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0109
U 1 1 6057202A
P 7600 4650
F 0 "#PWR0109" H 7600 4500 50  0001 C CNN
F 1 "+5V" H 7615 4823 50  0000 C CNN
F 2 "" H 7600 4650 50  0001 C CNN
F 3 "" H 7600 4650 50  0001 C CNN
	1    7600 4650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 60572030
P 8750 5850
F 0 "#PWR0110" H 8750 5600 50  0001 C CNN
F 1 "GND" H 8755 5677 50  0000 C CNN
F 2 "" H 8750 5850 50  0001 C CNN
F 3 "" H 8750 5850 50  0001 C CNN
	1    8750 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 4950 6750 4950
Wire Wire Line
	6750 3000 6750 2850
Connection ~ 6850 3100
Connection ~ 6750 3000
Wire Wire Line
	6750 3000 6750 4950
Wire Wire Line
	6850 3100 6850 5050
$Comp
L Transistor_Array:ULN2803A U7
U 1 1 605E2384
P 4850 5550
F 0 "U7" H 4850 6117 50  0000 C CNN
F 1 "ULN2803A" H 4850 6026 50  0000 C CNN
F 2 "Package_DIP:DIP-18_W7.62mm" H 4900 4900 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/uln2803a.pdf" H 4950 5350 50  0001 C CNN
	1    4850 5550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 605E2390
P 4850 6250
F 0 "#PWR0111" H 4850 6000 50  0001 C CNN
F 1 "GND" H 4855 6077 50  0000 C CNN
F 2 "" H 4850 6250 50  0001 C CNN
F 3 "" H 4850 6250 50  0001 C CNN
	1    4850 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 2150 3300 2150
Wire Wire Line
	3300 2150 3300 5350
Wire Wire Line
	3300 5350 4450 5350
Wire Wire Line
	4450 2250 3400 2250
Wire Wire Line
	3400 2250 3400 5450
Wire Wire Line
	3400 5450 4450 5450
Wire Wire Line
	4450 2350 3500 2350
Wire Wire Line
	3500 2350 3500 5550
Wire Wire Line
	3500 5550 4450 5550
Wire Wire Line
	4450 2450 3600 2450
Wire Wire Line
	3600 2450 3600 5650
Wire Wire Line
	3600 5650 4450 5650
Wire Wire Line
	4450 2550 3700 2550
Wire Wire Line
	3700 2550 3700 5750
Wire Wire Line
	3700 5750 4450 5750
Wire Wire Line
	4450 2650 3800 2650
Wire Wire Line
	3800 2650 3800 5850
Wire Wire Line
	3800 5850 4450 5850
Wire Wire Line
	5450 2350 6300 2350
Wire Wire Line
	6300 2350 6300 4000
Wire Wire Line
	6300 4000 3900 4000
Wire Wire Line
	3900 4000 3900 5950
Wire Wire Line
	3900 5950 4450 5950
Wire Wire Line
	5450 2450 6200 2450
Wire Wire Line
	6200 2450 6200 3900
Wire Wire Line
	6200 3900 4000 3900
Wire Wire Line
	4000 3900 4000 6050
Wire Wire Line
	4000 6050 4450 6050
Wire Wire Line
	5450 2550 6100 2550
Wire Wire Line
	6100 2550 6100 3800
Wire Wire Line
	6100 3800 4150 3800
$Comp
L Transistor_Array:ULN2803A U8
U 1 1 606E8064
P 4900 7050
F 0 "U8" H 4900 7617 50  0000 C CNN
F 1 "ULN2803A" H 4900 7526 50  0000 C CNN
F 2 "Package_DIP:DIP-18_W7.62mm" H 4950 6400 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/uln2803a.pdf" H 5000 6850 50  0001 C CNN
	1    4900 7050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 3800 4150 6850
Wire Wire Line
	4150 6850 4500 6850
Wire Wire Line
	5450 2650 6000 2650
Wire Wire Line
	6000 2650 6000 3700
Wire Wire Line
	6000 3700 4250 3700
Wire Wire Line
	4250 3700 4250 6950
Wire Wire Line
	4250 6950 4500 6950
$Comp
L power:GND #PWR0112
U 1 1 60710646
P 7100 3300
F 0 "#PWR0112" H 7100 3050 50  0001 C CNN
F 1 "GND" V 7105 3172 50  0000 R CNN
F 2 "" H 7100 3300 50  0001 C CNN
F 3 "" H 7100 3300 50  0001 C CNN
	1    7100 3300
	0    1    1    0   
$EndComp
Wire Wire Line
	7100 3400 7100 3300
Connection ~ 7100 3300
$Comp
L power:+5V #PWR0113
U 1 1 6073429C
P 7100 3500
F 0 "#PWR0113" H 7100 3350 50  0001 C CNN
F 1 "+5V" V 7115 3628 50  0000 L CNN
F 2 "" H 7100 3500 50  0001 C CNN
F 3 "" H 7100 3500 50  0001 C CNN
	1    7100 3500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6850 5050 7100 5050
$Comp
L Interface_Expansion:PCF8574 U3
U 1 1 6057201E
P 7600 5350
F 0 "U3" H 7250 6050 50  0000 C CNN
F 1 "PCF8574" H 7600 6140 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 7600 5350 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/PCF8574_PCF8574A.pdf" H 7600 5350 50  0001 C CNN
	1    7600 5350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 6075D602
P 7100 5250
F 0 "#PWR0114" H 7100 5000 50  0001 C CNN
F 1 "GND" V 7105 5122 50  0000 R CNN
F 2 "" H 7100 5250 50  0001 C CNN
F 3 "" H 7100 5250 50  0001 C CNN
	1    7100 5250
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 607677E0
P 7100 5450
F 0 "#PWR0115" H 7100 5200 50  0001 C CNN
F 1 "GND" V 7105 5322 50  0000 R CNN
F 2 "" H 7100 5450 50  0001 C CNN
F 3 "" H 7100 5450 50  0001 C CNN
	1    7100 5450
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR0116
U 1 1 6077B3AB
P 7100 5350
F 0 "#PWR0116" H 7100 5200 50  0001 C CNN
F 1 "+5V" V 7115 5478 50  0000 L CNN
F 2 "" H 7100 5350 50  0001 C CNN
F 3 "" H 7100 5350 50  0001 C CNN
	1    7100 5350
	0    -1   -1   0   
$EndComp
$Comp
L Jumper:Jumper_2_Open JP1
U 1 1 607843B2
P 5950 5100
F 0 "JP1" V 5950 5198 50  0000 L CNN
F 1 "JP1" V 5995 5198 50  0001 L CNN
F 2 "Connectors:GS2" H 5950 5100 50  0001 C CNN
F 3 "~" H 5950 5100 50  0001 C CNN
	1    5950 5100
	0    1    1    0   
$EndComp
Wire Wire Line
	5450 2850 6750 2850
$Comp
L Jumper:Jumper_2_Open JP2
U 1 1 607F9644
P 5700 5100
F 0 "JP2" V 5700 5198 50  0000 L CNN
F 1 "JP2" V 5745 5198 50  0001 L CNN
F 2 "Connectors:GS2" H 5700 5100 50  0001 C CNN
F 3 "~" H 5700 5100 50  0001 C CNN
	1    5700 5100
	0    1    1    0   
$EndComp
$Comp
L HFD2_005-S-L2-D:HFD2_005-S-L2-D K1
U 1 1 6081F7E1
P 9600 5800
F 0 "K1" H 10250 6065 50  0000 C CNN
F 1 "HFD2_005-S-L2-D" H 10250 5974 50  0000 C CNN
F 2 "HFD2_005-S-L2-D:HFD2005SL2D" H 10750 5900 50  0001 L CNN
F 3 "http://www.hongfa.com/pro/pdf/HFD2_en.pdf" H 10750 5800 50  0001 L CNN
F 4 "Hongfa Europe GMBH DPDT Non-Latching Relay PCB Mount, 5V dc Coil, 3 A, 3 A Subminiature DIP Relay" H 10750 5700 50  0001 L CNN "Description"
F 5 "10.6" H 10750 5600 50  0001 L CNN "Height"
F 6 "Hongfa" H 10750 5500 50  0001 L CNN "Manufacturer_Name"
F 7 "HFD2/005-S-L2-D" H 10750 5400 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 10750 5300 50  0001 L CNN "Mouser Part Number"
F 9 "" H 10750 5200 50  0001 L CNN "Mouser Price/Stock"
F 10 "HFD2/005-S-L2-D" H 10750 5100 50  0001 L CNN "Arrow Part Number"
F 11 "https://www.arrow.com/en/products/hfd2005-s-l2-d/hongfa-europe-gmbh" H 10750 5000 50  0001 L CNN "Arrow Price/Stock"
	1    9600 5800
	1    0    0    -1  
$EndComp
NoConn ~ 9150 1250
NoConn ~ 7100 2150
NoConn ~ 7100 5750
NoConn ~ 9150 4850
NoConn ~ 7100 3800
NoConn ~ 9150 2900
NoConn ~ 5450 2150
NoConn ~ 4850 1350
NoConn ~ 5050 1350
$Comp
L power:+5V #PWR0117
U 1 1 60879456
P 5150 1350
F 0 "#PWR0117" H 5150 1200 50  0001 C CNN
F 1 "+5V" H 5165 1523 50  0000 C CNN
F 2 "" H 5150 1350 50  0001 C CNN
F 3 "" H 5150 1350 50  0001 C CNN
	1    5150 1350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0118
U 1 1 6087B245
P 4950 3350
F 0 "#PWR0118" H 4950 3100 50  0001 C CNN
F 1 "GND" H 4955 3177 50  0000 C CNN
F 2 "" H 4950 3350 50  0001 C CNN
F 3 "" H 4950 3350 50  0001 C CNN
	1    4950 3350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0119
U 1 1 6087C0E3
P 5050 3350
F 0 "#PWR0119" H 5050 3100 50  0001 C CNN
F 1 "GND" H 5140 3178 50  0000 C CNN
F 2 "" H 5050 3350 50  0001 C CNN
F 3 "" H 5050 3350 50  0001 C CNN
	1    5050 3350
	1    0    0    -1  
$EndComp
NoConn ~ 4450 1750
NoConn ~ 4450 1850
NoConn ~ 4450 2050
NoConn ~ 1000 1850
$Comp
L Device:R R2
U 1 1 608B92B2
P 5850 4450
F 0 "R2" H 5920 4496 50  0000 L CNN
F 1 "10K" H 5920 4405 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 5780 4450 50  0001 C CNN
F 3 "~" H 5850 4450 50  0001 C CNN
	1    5850 4450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 608BA830
P 5700 4750
F 0 "R1" H 5770 4796 50  0000 L CNN
F 1 "22k" H 5770 4705 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 5630 4750 50  0001 C CNN
F 3 "~" H 5700 4750 50  0001 C CNN
	1    5700 4750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 608BB067
P 5950 4750
F 0 "R3" H 6020 4796 50  0000 L CNN
F 1 "4,7k" H 6020 4705 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 5880 4750 50  0001 C CNN
F 3 "~" H 5950 4750 50  0001 C CNN
	1    5950 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 4600 5850 4600
Wire Wire Line
	5850 4600 5950 4600
Connection ~ 5850 4600
$Comp
L Jumper:Jumper_2_Open JP3
U 1 1 608EACDA
P 6200 5100
F 0 "JP3" V 6200 5198 50  0000 L CNN
F 1 "JP3" V 6245 5198 50  0001 L CNN
F 2 "Connectors:GS2" H 6200 5100 50  0001 C CNN
F 3 "~" H 6200 5100 50  0001 C CNN
	1    6200 5100
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR0120
U 1 1 608EBB6A
P 5850 4300
F 0 "#PWR0120" H 5850 4150 50  0001 C CNN
F 1 "+5V" H 5865 4473 50  0000 C CNN
F 2 "" H 5850 4300 50  0001 C CNN
F 3 "" H 5850 4300 50  0001 C CNN
	1    5850 4300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0121
U 1 1 608EC64A
P 5700 5300
F 0 "#PWR0121" H 5700 5050 50  0001 C CNN
F 1 "GND" H 5705 5127 50  0000 C CNN
F 2 "" H 5700 5300 50  0001 C CNN
F 3 "" H 5700 5300 50  0001 C CNN
	1    5700 5300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0122
U 1 1 608ED27B
P 5950 5300
F 0 "#PWR0122" H 5950 5050 50  0001 C CNN
F 1 "GND" H 5955 5127 50  0000 C CNN
F 2 "" H 5950 5300 50  0001 C CNN
F 3 "" H 5950 5300 50  0001 C CNN
	1    5950 5300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0123
U 1 1 608ED8C0
P 6200 5300
F 0 "#PWR0123" H 6200 5050 50  0001 C CNN
F 1 "GND" H 6205 5127 50  0000 C CNN
F 2 "" H 6200 5300 50  0001 C CNN
F 3 "" H 6200 5300 50  0001 C CNN
	1    6200 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 4900 6200 4600
Wire Wire Line
	6200 4600 5950 4600
Connection ~ 5950 4600
Wire Wire Line
	5550 4600 5550 2950
Wire Wire Line
	5450 2950 5550 2950
Connection ~ 5700 4600
Wire Wire Line
	5700 4600 5550 4600
Wire Wire Line
	2350 1950 2350 2650
Wire Wire Line
	2350 2650 2150 2650
Wire Wire Line
	2150 2750 2600 3050
Wire Wire Line
	2150 3050 2600 2750
Wire Wire Line
	2350 1950 4450 1950
Wire Wire Line
	2600 2750 4450 2750
Wire Wire Line
	2600 3050 4450 3050
Wire Wire Line
	2150 2950 4450 2950
Wire Wire Line
	2150 2850 4450 2850
$Comp
L power:+5V #PWR?
U 1 1 6060A93E
P 2150 3250
F 0 "#PWR?" H 2150 3100 50  0001 C CNN
F 1 "+5V" H 2165 3423 50  0000 C CNN
F 2 "" H 2150 3250 50  0001 C CNN
F 3 "" H 2150 3250 50  0001 C CNN
	1    2150 3250
	-1   0    0    1   
$EndComp
$Comp
L CAN_BUS_MODULE_TJA1050_COPY:CAN_BUS_MODULE_TJA1050 U?
U 1 1 60580973
P 1450 2850
F 0 "U?" H 1400 2175 50  0000 C CNN
F 1 "CAN_BUS_MODULE_TJA1050" H 1400 2084 50  0000 C CNN
F 2 "" H 1450 2850 50  0001 C CNN
F 3 "" H 1450 2850 50  0001 C CNN
	1    1450 2850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6058B6A1
P 2150 3150
F 0 "#PWR?" H 2150 2900 50  0001 C CNN
F 1 "GND" V 2155 3022 50  0000 R CNN
F 2 "" H 2150 3150 50  0001 C CNN
F 3 "" H 2150 3150 50  0001 C CNN
	1    2150 3150
	0    -1   -1   0   
$EndComp
$EndSCHEMATC
