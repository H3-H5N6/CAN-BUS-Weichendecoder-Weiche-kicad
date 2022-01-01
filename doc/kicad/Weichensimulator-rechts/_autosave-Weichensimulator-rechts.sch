EESchema Schematic File Version 5
EELAYER 36 0
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
Comment5 ""
Comment6 ""
Comment7 ""
Comment8 ""
Comment9 ""
$EndDescr
Connection ~ 4200 3850
Connection ~ 4300 3950
Connection ~ 4500 2300
Connection ~ 5450 3150
Wire Wire Line
	4100 3850 4200 3850
Wire Wire Line
	4100 3950 4300 3950
Wire Wire Line
	4100 4300 4200 4300
Wire Wire Line
	4100 4400 4300 4400
Wire Wire Line
	4200 3850 4800 3850
Wire Wire Line
	4200 4300 4200 3850
Wire Wire Line
	4300 3950 4800 3950
Wire Wire Line
	4300 4400 4300 3950
Wire Wire Line
	4350 2300 4500 2300
Wire Wire Line
	4350 2600 4350 3550
Wire Wire Line
	4350 3550 5450 3550
Wire Wire Line
	4500 2300 4750 2300
Wire Wire Line
	4750 2600 4750 3450
Wire Wire Line
	4750 3450 5450 3450
Wire Wire Line
	5450 3250 5450 3150
Wire Wire Line
	6750 3150 6950 3150
Wire Wire Line
	6750 3250 6950 3250
Wire Wire Line
	6750 3350 6900 3350
Wire Wire Line
	6750 3450 6850 3450
Wire Wire Line
	6750 3550 6800 3550
Wire Wire Line
	6800 3550 6800 3650
Wire Wire Line
	6800 3650 6950 3650
Wire Wire Line
	6850 3450 6850 3550
Wire Wire Line
	6850 3550 6950 3550
Wire Wire Line
	6900 3350 6900 3450
Wire Wire Line
	6900 3450 6950 3450
$Comp
L power:+5V #PWR0101
U 1 1 6121323E
P 4500 1700
F 0 "#PWR0101" H 4500 1550 50  0001 C CNN
F 1 "+5V" H 4515 1873 50  0000 C CNN
F 2 "" H 4500 1700 50  0001 C CNN
F 3 "" H 4500 1700 50  0001 C CNN
	1    4500 1700
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0103
U 1 1 61264154
P 4800 3850
F 0 "#PWR0103" H 4800 3700 50  0001 C CNN
F 1 "+5V" H 4815 4023 50  0000 C CNN
F 2 "" H 4800 3850 50  0001 C CNN
F 3 "" H 4800 3850 50  0001 C CNN
	1    4800 3850
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0105
U 1 1 61269BBB
P 5450 3150
F 0 "#PWR0105" H 5450 3000 50  0001 C CNN
F 1 "+5V" H 5465 3323 50  0000 C CNN
F 2 "" H 5450 3150 50  0001 C CNN
F 3 "" H 5450 3150 50  0001 C CNN
	1    5450 3150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 61265221
P 4800 3950
F 0 "#PWR0104" H 4800 3700 50  0001 C CNN
F 1 "GND" H 4805 3777 50  0000 C CNN
F 2 "" H 4800 3950 50  0001 C CNN
F 3 "" H 4800 3950 50  0001 C CNN
	1    4800 3950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 6125D20C
P 5450 3350
F 0 "#PWR0102" H 5450 3100 50  0001 C CNN
F 1 "GND" V 5455 3222 50  0000 R CNN
F 2 "" H 5450 3350 50  0001 C CNN
F 3 "" H 5450 3350 50  0001 C CNN
	1    5450 3350
	0    1    1    0   
$EndComp
$Comp
L Mechanical:MountingHole H1
U 1 1 6074DA08
P 6450 1950
F 0 "H1" H 6550 2050 50  0000 L CNN
F 1 "MountingHole" H 6550 1905 50  0001 L CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3" H 6450 1950 50  0001 C CNN
F 3 "~" H 6450 1950 50  0001 C CNN
	1    6450 1950
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J2
U 1 1 61263F3E
P 3900 3850
F 0 "J2" H 4008 4031 50  0000 C CNN
F 1 "Power" H 4000 3650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x02_Pitch2.54mm" H 3900 3850 50  0001 C CNN
F 3 "~" H 3900 3850 50  0001 C CNN
	1    3900 3850
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J3
U 1 1 612729E3
P 3900 4300
F 0 "J3" H 4008 4389 50  0000 C CNN
F 1 "Conn_01x02_Male" H 4008 4390 50  0001 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x02_Pitch2.54mm" H 3900 4300 50  0001 C CNN
F 3 "~" H 3900 4300 50  0001 C CNN
	1    3900 4300
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J1
U 1 1 61262617
P 7150 3250
F 0 "J1" H 7122 3178 50  0000 R CNN
F 1 "Conn_01x02_Male" H 7258 3340 50  0001 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x02_Pitch2.54mm" H 7150 3250 50  0001 C CNN
F 3 "~" H 7150 3250 50  0001 C CNN
	1    7150 3250
	-1   0    0    1   
$EndComp
$Comp
L Device:R R1
U 1 1 61212C6E
P 4500 2150
F 0 "R1" H 4570 2196 50  0000 L CNN
F 1 "100" H 4570 2105 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 4430 2150 50  0001 C CNN
F 3 "~" H 4500 2150 50  0001 C CNN
	1    4500 2150
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male Rü1
U 1 1 60A840A4
P 7150 3550
F 0 "Rü1" H 7122 3528 50  0000 R CNN
F 1 "Conn_01x03_Male" H 7122 3573 50  0001 R CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 7150 3550 50  0001 C CNN
F 3 "~" H 7150 3550 50  0001 C CNN
	1    7150 3550
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D2
U 1 1 61211E8C
P 4350 2450
F 0 "D2" V 4389 2332 50  0000 R CNN
F 1 "LED" V 4298 2332 50  0000 R CNN
F 2 "LEDs:LED_D5.0mm" H 4350 2450 50  0001 C CNN
F 3 "~" H 4350 2450 50  0001 C CNN
	1    4350 2450
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D1
U 1 1 612111BE
P 4500 1850
F 0 "D1" V 4539 1732 50  0000 R CNN
F 1 "LED" V 4448 1732 50  0000 R CNN
F 2 "LEDs:LED_D5.0mm" H 4500 1850 50  0001 C CNN
F 3 "~" H 4500 1850 50  0001 C CNN
	1    4500 1850
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D3
U 1 1 612122F7
P 4750 2450
F 0 "D3" V 4789 2332 50  0000 R CNN
F 1 "LED" V 4698 2332 50  0000 R CNN
F 2 "LEDs:LED_D5.0mm" H 4750 2450 50  0001 C CNN
F 3 "~" H 4750 2450 50  0001 C CNN
	1    4750 2450
	0    -1   -1   0   
$EndComp
$Comp
L HongFa:HFD2_005-S-L2-D K1
U 1 1 6125B40D
P 6750 3150
F 0 "K1" H 7400 3415 50  0000 C CNN
F 1 "HFD2_005-S-L2-D" H 7400 3324 50  0000 C CNN
F 2 "HongFa:HFD2005SL2D" H 7900 3250 50  0001 L CNN
F 3 "http://www.hongfa.com/pro/pdf/HFD2_en.pdf" H 7900 3150 50  0001 L CNN
F 4 "Hongfa Europe GMBH DPDT Non-Latching Relay PCB Mount, 5V dc Coil, 3 A, 3 A Subminiature DIP Relay" H 7900 3050 50  0001 L CNN "Description"
F 5 "10.6" H 7900 2950 50  0001 L CNN "Height"
F 6 "Hongfa" H 7900 2850 50  0001 L CNN "Manufacturer_Name"
F 7 "HFD2/005-S-L2-D" H 7900 2750 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 7900 2650 50  0001 L CNN "Mouser Part Number"
F 9 "" H 7900 2550 50  0001 L CNN "Mouser Price/Stock"
F 10 "HFD2/005-S-L2-D" H 7900 2450 50  0001 L CNN "Arrow Part Number"
F 11 "https://www.arrow.com/en/products/hfd2005-s-l2-d/hongfa-europe-gmbh" H 7900 2350 50  0001 L CNN "Arrow Price/Stock"
	1    6750 3150
	-1   0    0    -1  
$EndComp
$EndSCHEMATC
