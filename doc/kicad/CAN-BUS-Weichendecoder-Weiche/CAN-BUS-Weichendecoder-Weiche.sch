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
Connection ~ 7050 2250
Wire Wire Line
	4750 1550 3600 1550
Wire Wire Line
	4750 1650 3700 1650
Wire Wire Line
	4750 1850 3900 1850
Wire Wire Line
	4750 2050 4100 2050
Wire Wire Line
	5750 1750 6250 1750
Wire Wire Line
	6250 1750 6250 3300
Wire Wire Line
	5750 1850 6150 1850
Wire Wire Line
	6150 1850 6150 3200
Wire Wire Line
	6150 3200 4250 3200
Wire Wire Line
	5750 1950 6050 1950
Wire Wire Line
	6050 1950 6050 3100
Wire Wire Line
	6050 3100 4450 3100
Wire Wire Line
	5750 2050 5950 2050
Wire Wire Line
	5950 2050 5950 3000
Wire Wire Line
	5950 3000 4550 3000
Wire Wire Line
	5750 2250 7050 2250
NoConn ~ 5750 1550
NoConn ~ 5150 750 
NoConn ~ 5350 750 
$Comp
L power:+5V #PWR01012
U 1 1 60879456
P 5450 750
F 0 "#PWR01012" H 5450 600 50  0001 C CNN
F 1 "+5V" H 5465 923 50  0000 C CNN
F 2 "" H 5450 750 50  0001 C CNN
F 3 "" H 5450 750 50  0001 C CNN
	1    5450 750 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01011
U 1 1 6087C0E3
P 5350 2750
F 0 "#PWR01011" H 5350 2500 50  0001 C CNN
F 1 "GND" H 5440 2578 50  0000 C CNN
F 2 "" H 5350 2750 50  0001 C CNN
F 3 "" H 5350 2750 50  0001 C CNN
	1    5350 2750
	1    0    0    -1  
$EndComp
NoConn ~ 4750 1150
NoConn ~ 4750 1250
Wire Wire Line
	2950 2850 3450 2550
$Comp
L power:+5V #PWR01004
U 1 1 6060A93E
P 2900 3050
F 0 "#PWR01004" H 2900 2900 50  0001 C CNN
F 1 "+5V" H 2915 3223 50  0000 C CNN
F 2 "" H 2900 3050 50  0001 C CNN
F 3 "" H 2900 3050 50  0001 C CNN
	1    2900 3050
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR01003
U 1 1 6058B6A1
P 2900 2950
F 0 "#PWR01003" H 2900 2700 50  0001 C CNN
F 1 "GND" V 2905 2822 50  0000 R CNN
F 2 "" H 2900 2950 50  0001 C CNN
F 3 "" H 2900 2950 50  0001 C CNN
	1    2900 2950
	0    -1   -1   0   
$EndComp
$Comp
L CAN-BUS-MODULE-TJA1050:CAN-BUS_MODULE_TJA1050 Shield1001
U 1 1 60585225
P 2200 2650
F 0 "Shield1001" H 2150 1975 50  0001 C CNN
F 1 "CAN-BUS_MODULE_TJA1050" H 2200 1950 50  0000 C CNN
F 2 "CAN-BUS-MODULE:MCP2515_CAN_MODULE_BY0-10" H 2200 2650 50  0001 C CIN
F 3 "" H 2200 2650 50  0001 C CNN
	1    2200 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 2450 3500 2450
$Comp
L Jumper:Jumper_2_Open JP2
U 1 1 607843B2
P 6400 850
F 0 "JP2" V 6400 948 50  0000 L CNN
F 1 "Prog2" V 6445 948 50  0001 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 6400 850 50  0001 C CNN
F 3 "~" H 6400 850 50  0001 C CNN
	1    6400 850 
	0    -1   -1   0   
$EndComp
$Comp
L Jumper:Jumper_2_Open JP3
U 1 1 607F9644
P 6650 850
F 0 "JP3" V 6650 948 50  0000 L CNN
F 1 "Prog3" V 6695 948 50  0001 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 6650 850 50  0001 C CNN
F 3 "~" H 6650 850 50  0001 C CNN
	1    6650 850 
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R6
U 1 1 608B92B2
P 6500 1500
F 0 "R6" H 6570 1546 50  0000 L CNN
F 1 "10K" H 6570 1455 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6430 1500 50  0001 C CNN
F 3 "~" H 6500 1500 50  0001 C CNN
	1    6500 1500
	-1   0    0    1   
$EndComp
$Comp
L Device:R R5
U 1 1 608BA830
P 6650 1200
F 0 "R5" H 6720 1246 50  0000 L CNN
F 1 "22k" H 6720 1155 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6580 1200 50  0001 C CNN
F 3 "~" H 6650 1200 50  0001 C CNN
	1    6650 1200
	-1   0    0    1   
$EndComp
$Comp
L Device:R R4
U 1 1 608BB067
P 6400 1200
F 0 "R4" H 6470 1246 50  0000 L CNN
F 1 "4,7k" H 6470 1155 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6330 1200 50  0001 C CNN
F 3 "~" H 6400 1200 50  0001 C CNN
	1    6400 1200
	-1   0    0    1   
$EndComp
Wire Wire Line
	6650 1350 6500 1350
Wire Wire Line
	6500 1350 6400 1350
Connection ~ 6500 1350
$Comp
L Jumper:Jumper_2_Open JP1
U 1 1 608EACDA
P 6150 850
F 0 "JP1" V 6150 948 50  0000 L CNN
F 1 "Prog 1" V 6050 900 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 6150 850 50  0001 C CNN
F 3 "~" H 6150 850 50  0001 C CNN
	1    6150 850 
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR01017
U 1 1 608EBB6A
P 6500 1650
F 0 "#PWR01017" H 6500 1500 50  0001 C CNN
F 1 "+5V" H 6515 1823 50  0000 C CNN
F 2 "" H 6500 1650 50  0001 C CNN
F 3 "" H 6500 1650 50  0001 C CNN
	1    6500 1650
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR01019
U 1 1 608EC64A
P 6650 650
F 0 "#PWR01019" H 6650 400 50  0001 C CNN
F 1 "GND" H 6655 477 50  0000 C CNN
F 2 "" H 6650 650 50  0001 C CNN
F 3 "" H 6650 650 50  0001 C CNN
	1    6650 650 
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR01016
U 1 1 608ED27B
P 6400 650
F 0 "#PWR01016" H 6400 400 50  0001 C CNN
F 1 "GND" H 6405 477 50  0000 C CNN
F 2 "" H 6400 650 50  0001 C CNN
F 3 "" H 6400 650 50  0001 C CNN
	1    6400 650 
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR01013
U 1 1 608ED8C0
P 6150 650
F 0 "#PWR01013" H 6150 400 50  0001 C CNN
F 1 "GND" H 6155 477 50  0000 C CNN
F 2 "" H 6150 650 50  0001 C CNN
F 3 "" H 6150 650 50  0001 C CNN
	1    6150 650 
	-1   0    0    1   
$EndComp
Wire Wire Line
	6150 1050 6150 1350
Wire Wire Line
	6150 1350 6400 1350
Connection ~ 6400 1350
Connection ~ 6650 1350
Wire Wire Line
	6650 1350 6800 1350
Wire Wire Line
	6800 1350 6800 2350
Wire Wire Line
	5750 2350 6800 2350
$Comp
L Device:R R8
U 1 1 608DF9C2
P 7150 900
F 0 "R8" H 7000 950 50  0000 L CNN
F 1 "4k7" H 6950 850 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7080 900 50  0001 C CNN
F 3 "~" H 7150 900 50  0001 C CNN
	1    7150 900 
	-1   0    0    1   
$EndComp
$Comp
L Device:R R7
U 1 1 608DEDAC
P 7050 900
F 0 "R7" H 7100 950 50  0000 L CNN
F 1 "4k7" H 7100 850 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6980 900 50  0001 C CNN
F 3 "~" H 7050 900 50  0001 C CNN
	1    7050 900 
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR01020
U 1 1 60931B13
P 7050 750
F 0 "#PWR01020" H 7050 600 50  0001 C CNN
F 1 "+5V" H 7065 923 50  0001 C CNN
F 2 "" H 7050 750 50  0001 C CNN
F 3 "" H 7050 750 50  0001 C CNN
	1    7050 750 
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR01021
U 1 1 60932977
P 7150 750
F 0 "#PWR01021" H 7150 600 50  0001 C CNN
F 1 "+5V" H 7165 923 50  0001 C CNN
F 2 "" H 7150 750 50  0001 C CNN
F 3 "" H 7150 750 50  0001 C CNN
	1    7150 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 2850 2900 2850
$Comp
L ASSMANN_WSW:A-20042-LP_FS CAN-Bus
U 1 1 60B7A5DF
P 1700 5150
F 0 "CAN-Bus" V 1350 4900 50  0000 C CNN
F 1 "J22" H 1757 5726 50  0001 C CNN
F 2 "ASSMANN_WSW:A20042LPFS" V 1700 5175 50  0001 C CNN
F 3 "~" V 1700 5175 50  0001 C CNN
	1    1700 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 4650 2350 4650
Wire Wire Line
	2350 5700 2150 5700
Wire Wire Line
	2150 4550 2400 4550
Wire Wire Line
	2400 4550 2400 5600
Wire Wire Line
	2400 5600 2150 5600
Wire Wire Line
	2150 4450 2450 4450
Wire Wire Line
	2450 5500 2150 5500
Wire Wire Line
	2150 4350 2500 4350
Wire Wire Line
	2500 4350 2500 5400
Wire Wire Line
	2500 5400 2150 5400
Wire Wire Line
	2150 4250 2550 4250
Wire Wire Line
	2550 4250 2550 5300
Wire Wire Line
	2550 5300 2150 5300
Wire Wire Line
	2150 4150 2600 4150
Wire Wire Line
	2600 4150 2600 5200
Wire Wire Line
	2600 5200 2150 5200
Wire Wire Line
	2650 4050 2650 5100
Wire Wire Line
	2650 5100 2150 5100
Wire Wire Line
	2700 3950 2700 5000
Wire Wire Line
	2700 5000 2150 5000
Wire Wire Line
	1400 2850 1150 2850
Wire Wire Line
	1150 2850 1150 3550
Wire Wire Line
	1400 2750 1100 2750
Wire Wire Line
	1100 2750 1100 3600
Wire Wire Line
	4750 1750 3800 1750
$Comp
L Isolator:6N136 U1001
U 1 1 615246FE
P 2200 1200
F 0 "U1001" H 2200 1625 50  0000 C CNN
F 1 "6N136" H 2200 1534 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 2000 900 50  0001 L CIN
F 3 "https://optoelectronics.liteon.com/upload/download/DS70-2008-0032/6N135-L%206N136-L%20series.pdf" H 2200 1200 50  0001 L CNN
	1    2200 1200
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4004 D1
U 1 1 61525ABE
P 1700 1150
F 0 "D1" V 1654 1230 50  0000 L CNN
F 1 "1N4004" V 1745 1230 50  0000 L CNN
F 2 "Diodes_THT:D_DO-15_P10.16mm_Horizontal" H 1700 975 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 1700 1150 50  0001 C CNN
	1    1700 1150
	0    1    1    0   
$EndComp
$Comp
L Device:R R1
U 1 1 6154F62A
P 1450 1000
F 0 "R1" V 1243 1000 50  0000 C CNN
F 1 "1k5" V 1334 1000 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 1380 1000 50  0001 C CNN
F 3 "~" H 1450 1000 50  0001 C CNN
	1    1450 1000
	0    1    1    0   
$EndComp
Wire Wire Line
	1600 1000 1700 1000
Wire Wire Line
	1700 1000 1900 1000
Wire Wire Line
	1900 1000 1900 1100
Connection ~ 1700 1000
Wire Wire Line
	1300 1300 1700 1300
Wire Wire Line
	1900 1300 1700 1300
Connection ~ 1700 1300
$Comp
L power:GND #PWR01001
U 1 1 61634386
P 2500 1450
F 0 "#PWR01001" H 2500 1200 50  0001 C CNN
F 1 "GND" H 2505 1277 50  0000 C CNN
F 2 "" H 2500 1450 50  0001 C CNN
F 3 "" H 2500 1450 50  0001 C CNN
	1    2500 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 1400 2500 1450
Wire Wire Line
	2500 1300 3100 1300
Wire Wire Line
	3100 1350 4750 1350
$Comp
L power:+5V #PWR01002
U 1 1 61660705
P 2700 750
F 0 "#PWR01002" H 2700 600 50  0001 C CNN
F 1 "+5V" H 2715 923 50  0000 C CNN
F 2 "" H 2700 750 50  0001 C CNN
F 3 "" H 2700 750 50  0001 C CNN
	1    2700 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 1000 2700 1000
Wire Wire Line
	2700 1000 2700 750 
$Comp
L MCU_Module:Arduino_Nano_v3.x U1
U 1 1 60416171
P 5250 1750
F 0 "U1" H 5050 700 50  0000 C CNN
F 1 "Arduino_Nano" H 5300 2100 50  0000 C CNN
F 2 "Modules:Arduino_Nano" H 5250 1750 50  0001 C CIN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 5250 1750 50  0001 C CNN
	1    5250 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 1200 3100 1300
$Comp
L power:+5V #PWR01007
U 1 1 616A6118
P 3100 750
F 0 "#PWR01007" H 3100 600 50  0001 C CNN
F 1 "+5V" H 3115 923 50  0000 C CNN
F 2 "" H 3100 750 50  0001 C CNN
F 3 "" H 3100 750 50  0001 C CNN
	1    3100 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 750  3100 900 
Text Notes 1800 550  0    50   ~ 0
DCC-Interface
Wire Wire Line
	1300 1100 1300 1000
Wire Wire Line
	1300 1200 1300 1300
Wire Wire Line
	2450 7350 2450 7300
Wire Wire Line
	2850 7000 2900 7000
Wire Wire Line
	2900 7000 2900 6800
$Comp
L power:+12V #PWR01046
U 1 1 6178B55D
P 2900 6450
F 0 "#PWR01046" H 2900 6300 50  0001 C CNN
F 1 "+12V" H 3050 6500 50  0000 C CNN
F 2 "" H 2900 6450 50  0001 C CNN
F 3 "" H 2900 6450 50  0001 C CNN
	1    2900 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 6350 3150 6300
$Comp
L power:GND #PWR01045
U 1 1 61F06718
P 2850 7350
F 0 "#PWR01045" H 2850 7100 50  0001 C CNN
F 1 "GND" H 2855 7177 50  0000 C CNN
F 2 "" H 2850 7350 50  0001 C CNN
F 3 "" H 2850 7350 50  0001 C CNN
	1    2850 7350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 7350 2450 7350
Connection ~ 3100 1300
$Comp
L Device:R R2
U 1 1 6168E6E9
P 3100 1050
F 0 "R2" H 3170 1096 50  0000 L CNN
F 1 "10K" H 3170 1005 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 3030 1050 50  0001 C CNN
F 3 "~" H 3100 1050 50  0001 C CNN
	1    3100 1050
	1    0    0    -1  
$EndComp
Connection ~ 1300 1300
$Comp
L Wago:2604-1102 J31
U 1 1 6163DC25
P 750 7100
F 0 "J31" H 592 6713 60  0000 C CNN
F 1 "12V DC" H 592 6819 60  0000 C CNN
F 2 "CONN_2604-1102_4_WAG" H 750 7040 60  0001 C CNN
F 3 "" H 750 7100 60  0000 C CNN
	1    750  7100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1150 6900 1150 7000
Connection ~ 1150 7000
Wire Wire Line
	1150 7200 1150 7100
Connection ~ 1150 7100
Wire Wire Line
	1950 2100 1950 2250
Wire Wire Line
	1950 2250 2200 2250
Wire Wire Line
	2550 2250 2550 2100
$Comp
L Device:Jumper JP11
U 1 1 61A202D7
P 2250 2100
F 0 "JP11" H 2250 2300 50  0001 C CNN
F 1 "CAN-Term" H 2250 2250 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 2250 2100 50  0001 C CNN
F 3 "~" H 2250 2100 50  0001 C CNN
	1    2250 2100
	1    0    0    -1  
$EndComp
Connection ~ 7150 2150
Wire Wire Line
	7150 2150 5750 2150
Wire Wire Line
	2950 2550 2900 2550
Wire Wire Line
	2950 2550 3450 2850
Wire Wire Line
	3100 1300 3100 1350
Wire Wire Line
	6300 7550 6200 7550
$Comp
L Device:R_Network05 R10
U 1 1 615C2884
P 6000 7350
F 0 "R10" V 5700 7350 50  0000 C CNN
F 1 "1k" V 5600 7350 50  0000 C CNN
F 2 "Resistors_THT:R_Array_SIP6" V 6375 7350 50  0001 C CNN
F 3 "http://www.vishay.com/docs/31509/csc.pdf" H 6000 7350 50  0001 C CNN
	1    6000 7350
	0    1    -1   0   
$EndComp
$Comp
L Wago:250-1404 J5
U 1 1 616E29D2
P 7150 6000
F 0 "J5" H 7678 5850 60  0000 L CNN
F 1 "250-1404" H 7678 5850 60  0001 L CNN
F 2 "Wago:250-1404" H 7678 5744 60  0001 L CNN
F 3 "" H 7150 6000 60  0001 C CNN
	1    7150 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 6000 6150 6000
Wire Wire Line
	7150 6300 6250 6300
Wire Wire Line
	4450 7450 4600 7450
Wire Wire Line
	4300 7350 4600 7350
Wire Wire Line
	4200 7250 4600 7250
Wire Wire Line
	4100 7150 4600 7150
Wire Wire Line
	3900 6950 4600 6950
Wire Wire Line
	3800 6850 4600 6850
Wire Wire Line
	3700 6750 4600 6750
Wire Wire Line
	3600 6650 4600 6650
Connection ~ 6300 7000
$Comp
L power:GND #PWR01018
U 1 1 619BA8AC
P 6300 7000
F 0 "#PWR01018" H 6300 6750 50  0001 C CNN
F 1 "GND" H 6305 6827 50  0000 C CNN
F 2 "" H 6300 7000 50  0001 C CNN
F 3 "" H 6300 7000 50  0001 C CNN
	1    6300 7000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6300 7000 6300 7550
Wire Wire Line
	6300 6650 6300 7000
Wire Wire Line
	6200 6650 6300 6650
Wire Wire Line
	5700 7550 5800 7550
Wire Wire Line
	5700 7450 5800 7450
Wire Wire Line
	5700 7350 5800 7350
Wire Wire Line
	5700 7250 5800 7250
Wire Wire Line
	5700 7150 5800 7150
Wire Wire Line
	5700 7050 5800 7050
Wire Wire Line
	5700 6950 5800 6950
Wire Wire Line
	5700 6850 5800 6850
Wire Wire Line
	5700 6750 5800 6750
Wire Wire Line
	5700 6650 5800 6650
$Comp
L Device:R_Network05 R9
U 1 1 615C1448
P 6000 6850
F 0 "R9" V 5583 6850 50  0000 C CNN
F 1 "1k" V 5674 6850 50  0000 C CNN
F 2 "Resistors_THT:R_Array_SIP6" V 6375 6850 50  0001 C CNN
F 3 "http://www.vishay.com/docs/31509/csc.pdf" H 6000 6850 50  0001 C CNN
	1    6000 6850
	0    1    1    0   
$EndComp
$Comp
L Kingbright-LED:DC-10SGWA DS1001
U 1 1 615BB0E4
P 4600 6650
F 0 "DS1001" H 5150 6915 50  0000 C CNN
F 1 "DC-10SGWA" H 5150 6824 50  0000 C CNN
F 2 "Kingbright-LED:DIPS750W80P254L2540H825Q20N" H 5550 6750 50  0001 L CNN
F 3 "http://uk.rs-online.com/web/p/products/2473090" H 5550 6650 50  0001 L CNN
F 4 "Kingbright DC-10SGWA Light Bar LED Display, Green 21 mcd" H 5550 6550 50  0001 L CNN "Description"
F 5 "8.25" H 5550 6450 50  0001 L CNN "Height"
F 6 "Kingbright" H 5550 6350 50  0001 L CNN "Manufacturer_Name"
F 7 "DC-10SGWA" H 5550 6250 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "N/A" H 5550 6150 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.com/Search/Refine.aspx?Keyword=N%2FA" H 5550 6050 50  0001 L CNN "Mouser Price/Stock"
F 10 "" H 5550 5950 50  0001 L CNN "Arrow Part Number"
F 11 "" H 5550 5850 50  0001 L CNN "Arrow Price/Stock"
	1    4600 6650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 7050 4600 7050
Wire Wire Line
	4750 1950 4000 1950
Wire Wire Line
	4000 1950 4000 4100
Connection ~ 4000 4100
Wire Wire Line
	4000 4100 4000 7050
Wire Wire Line
	4550 3000 4550 5300
Wire Wire Line
	4450 3100 4450 5200
Connection ~ 4450 5200
Wire Wire Line
	4450 5200 4450 7450
Wire Wire Line
	3900 1850 3900 4200
Connection ~ 3900 4200
Wire Wire Line
	3900 4200 3900 6950
Wire Wire Line
	3800 1750 3800 4300
Connection ~ 3800 4300
Wire Wire Line
	3800 4300 3800 6850
Wire Wire Line
	3700 1650 3700 4400
Connection ~ 3700 4400
Wire Wire Line
	3700 4400 3700 6750
Wire Wire Line
	3600 1550 3600 4500
Connection ~ 3600 4500
Wire Wire Line
	3600 4500 3600 6650
Wire Wire Line
	4100 2050 4100 4000
Connection ~ 4100 4000
Wire Wire Line
	4100 4000 4100 7150
Wire Wire Line
	4250 3200 4250 3900
Connection ~ 4250 3900
Wire Wire Line
	4250 3900 4200 7250
Wire Wire Line
	4550 5300 4650 5300
Wire Wire Line
	5450 5100 5550 5100
Wire Wire Line
	4450 5200 4650 5200
$Comp
L Transistor_Array:ULN2803A U3
U 1 1 606E8064
P 5050 5400
F 0 "U3" H 5050 5967 50  0000 C CNN
F 1 "ULN2803A" H 5050 5876 50  0000 C CNN
F 2 "Package_DIP:DIP-18_W7.62mm" H 5100 4750 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/uln2803a.pdf" H 5150 5200 50  0001 C CNN
	1    5050 5400
	1    0    0    -1  
$EndComp
Connection ~ 6250 5700
Wire Wire Line
	6250 5700 6250 6300
Connection ~ 6150 5400
Wire Wire Line
	6150 5400 6150 6000
Wire Wire Line
	5600 4500 5600 5600
Wire Wire Line
	5650 4400 5650 5500
Wire Wire Line
	5850 4200 5850 4600
Connection ~ 6250 4800
Wire Wire Line
	6250 4800 6250 4950
Connection ~ 6150 4500
Wire Wire Line
	6150 4500 6150 5000
Connection ~ 6250 4300
Wire Wire Line
	6250 4300 6250 4800
Wire Wire Line
	7150 5700 6250 5700
Wire Wire Line
	7150 5400 6150 5400
$Comp
L Wago:250-1404 J4
U 1 1 616E1E7E
P 7150 5400
F 0 "J4" H 7678 5250 60  0000 L CNN
F 1 "250-1404" H 7678 5250 60  0001 L CNN
F 2 "Wago:250-1404" H 7678 5144 60  0001 L CNN
F 3 "" H 7150 5400 60  0001 C CNN
	1    7150 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 4800 7100 4800
Wire Wire Line
	7100 4500 6150 4500
$Comp
L Wago:250-1404 J3
U 1 1 616E033D
P 7100 4500
F 0 "J3" H 7628 4350 60  0000 L CNN
F 1 "250-1404" H 7628 4350 60  0001 L CNN
F 2 "Wago:250-1404" H 7628 4244 60  0001 L CNN
F 3 "" H 7100 4500 60  0001 C CNN
	1    7100 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 3300 4350 3300
$Comp
L power:+12V #PWR01014
U 1 1 60761D5B
P 6150 3500
F 0 "#PWR01014" H 6150 3350 50  0001 C CNN
F 1 "+12V" H 6165 3673 50  0000 C CNN
F 2 "" H 6150 3500 50  0001 C CNN
F 3 "" H 6150 3500 50  0001 C CNN
	1    6150 3500
	1    0    0    -1  
$EndComp
Connection ~ 6150 3500
$Comp
L Device:Jumper JP4
U 1 1 607A8A8B
P 5850 3500
F 0 "JP4" H 5850 3650 50  0000 C CNN
F 1 "Jumper" H 5850 3673 50  0001 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 5850 3500 50  0001 C CNN
F 3 "~" H 5850 3500 50  0001 C CNN
	1    5850 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 3800 4300 7350
Connection ~ 4350 3800
Wire Wire Line
	4350 3300 4350 3800
Wire Wire Line
	5550 5100 5550 3700
Wire Wire Line
	3600 4500 4650 4500
Wire Wire Line
	3700 4400 4650 4400
Wire Wire Line
	3800 4300 4650 4300
Wire Wire Line
	3900 4200 4650 4200
Wire Wire Line
	4000 4100 4650 4100
Wire Wire Line
	4100 4000 4650 4000
Wire Wire Line
	4250 3900 4650 3900
Wire Wire Line
	5450 4000 6050 4000
Wire Wire Line
	5450 4200 5850 4200
Wire Wire Line
	5450 4300 5750 4300
Wire Wire Line
	5450 4400 5650 4400
Wire Wire Line
	5450 4500 5600 4500
Wire Wire Line
	4350 3800 4650 3800
$Comp
L Transistor_Array:ULN2803A U2
U 1 1 605E2384
P 5050 4000
F 0 "U2" H 5050 4567 50  0000 C CNN
F 1 "ULN2803A" H 5050 4476 50  0000 C CNN
F 2 "Package_DIP:DIP-18_W7.62mm" H 5100 3350 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/uln2803a.pdf" H 5150 3800 50  0001 C CNN
	1    5050 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 4100 5950 4100
Wire Wire Line
	5750 4300 5750 4700
Wire Wire Line
	5450 5200 5550 5200
Wire Wire Line
	5450 5300 5500 5300
Wire Wire Line
	5950 4100 5950 4200
Wire Wire Line
	6050 4000 6050 4100
Wire Wire Line
	6150 4000 6150 3500
Wire Wire Line
	6150 4000 6150 4500
Connection ~ 6150 4000
Wire Wire Line
	5950 4200 6700 4200
$Comp
L Wago:250-1404 J2
U 1 1 616186ED
P 7100 4000
F 0 "J2" H 7628 3850 60  0000 L CNN
F 1 "250-1404" H 7628 3850 60  0001 L CNN
F 2 "Wago:250-1404" H 7628 3744 60  0001 L CNN
F 3 "" H 7100 4000 60  0001 C CNN
	1    7100 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 3800 6250 4300
Wire Wire Line
	7100 3800 6250 3800
Wire Wire Line
	7100 3500 6150 3500
$Comp
L Wago:250-1404 J1
U 1 1 62056259
P 7100 3500
F 0 "J1" H 7628 3403 60  0000 L CNN
F 1 "250-1404" H 7628 3297 60  0001 L CNN
F 2 "Wago:250-1404" H 7500 3240 60  0001 C CNN
F 3 "" H 7100 3500 60  0001 C CNN
	1    7100 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 2850 4650 2450
Wire Wire Line
	4650 2450 4750 2450
Wire Wire Line
	3450 2850 4650 2850
Wire Wire Line
	4550 2750 4550 2350
Wire Wire Line
	4550 2350 4750 2350
Wire Wire Line
	2900 2750 4550 2750
Wire Wire Line
	4450 2650 4450 2250
Wire Wire Line
	4450 2250 4750 2250
Wire Wire Line
	2900 2650 4450 2650
Wire Wire Line
	4350 2550 4350 2150
Wire Wire Line
	4350 2150 4750 2150
Wire Wire Line
	3450 2550 4350 2550
Wire Wire Line
	4550 7550 4600 7550
Wire Wire Line
	4550 7550 4550 5300
Connection ~ 4550 5300
$Comp
L ASSMANN_WSW:A-20042-LP_FS CAN-Bus
U 1 1 64B4E74A
P 1700 4100
F 0 "CAN-Bus" V 1350 3850 50  0000 C CNN
F 1 "J22" H 1757 4676 50  0000 C CNN
F 2 "ASSMANN_WSW:A20042LPFS" V 1700 4125 50  0001 C CNN
F 3 "~" V 1700 4125 50  0001 C CNN
	1    1700 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 4050 2650 4050
Wire Wire Line
	2350 4650 2350 5700
Wire Wire Line
	2450 4450 2450 5500
Wire Wire Line
	1100 3600 2650 3600
Connection ~ 2650 4050
Wire Wire Line
	2150 3950 2700 3950
Wire Wire Line
	1150 3550 2700 3550
Connection ~ 2700 3950
Wire Wire Line
	2850 4350 2500 4350
Connection ~ 2500 4350
Wire Wire Line
	2850 4450 2450 4450
Connection ~ 2450 4450
$Comp
L power:GND #PWR0101
U 1 1 64C41938
P 2850 4450
F 0 "#PWR0101" H 2850 4200 50  0001 C CNN
F 1 "GND" H 2855 4277 50  0000 C CNN
F 2 "" H 2850 4450 50  0001 C CNN
F 3 "" H 2850 4450 50  0001 C CNN
	1    2850 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 4350 2850 4450
Connection ~ 2850 4450
$Comp
L Jumper:Jumper_2_Open JP41
U 1 1 64C66E53
P 1300 1700
F 0 "JP41" V 1300 1550 50  0000 L CNN
F 1 "DCC B" V 1400 1400 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 1300 1700 50  0001 C CNN
F 3 "~" H 1300 1700 50  0001 C CNN
	1    1300 1700
	0    1    1    0   
$EndComp
$Comp
L Jumper:Jumper_2_Open JP42
U 1 1 64C690BF
P 1500 1700
F 0 "JP42" V 1500 1850 50  0000 L CNN
F 1 "DCC A" V 1600 1800 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 1500 1700 50  0001 C CNN
F 3 "~" H 1500 1700 50  0001 C CNN
	1    1500 1700
	0    1    1    0   
$EndComp
Wire Wire Line
	1300 1100 1500 1100
Wire Wire Line
	1500 1100 1500 1500
Wire Wire Line
	2400 4550 2400 3700
Wire Wire Line
	2400 3700 950  3700
Wire Wire Line
	950  3700 950  2150
Wire Wire Line
	950  2150 1500 2150
Wire Wire Line
	1500 2150 1500 1900
Connection ~ 2400 4550
Wire Wire Line
	2350 4650 2350 3750
Wire Wire Line
	2350 3750 900  3750
Wire Wire Line
	900  3750 900  2100
Wire Wire Line
	900  2100 1300 2100
Wire Wire Line
	1300 2100 1300 1900
Connection ~ 2350 4650
$Comp
L Device:Jumper JP23
U 1 1 6177E616
P 3100 4150
F 0 "JP23" H 3100 4350 50  0000 C CNN
F 1 "12V CAN" H 3100 4050 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 3100 4150 50  0001 C CNN
F 3 "~" H 3100 4150 50  0001 C CNN
	1    3100 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 4150 2800 4150
Connection ~ 2600 4150
Wire Wire Line
	2650 3600 2650 4050
Wire Wire Line
	2700 3550 2700 3950
$Comp
L power:+5V #PWR01044
U 1 1 6176DD9A
P 2900 6800
F 0 "#PWR01044" H 2900 6650 50  0001 C CNN
F 1 "+5V" H 3000 6900 50  0000 C CNN
F 2 "" H 2900 6800 50  0001 C CNN
F 3 "" H 2900 6800 50  0001 C CNN
	1    2900 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 1500 1300 1300
$Comp
L Wago:2604-1102 J41
U 1 1 615D8C87
P 900 1100
F 0 "J41" H 742 713 60  0000 C CNN
F 1 "2604-1102" H 742 819 60  0000 C CNN
F 2 "CONN_2604-1102_4_WAG" H 900 1040 60  0001 C CNN
F 3 "" H 900 1100 60  0000 C CNN
	1    900  1100
	-1   0    0    1   
$EndComp
Connection ~ 1300 1000
Connection ~ 1300 1100
$Comp
L Regulator_Switching:TSR_1-24120 U10
U 1 1 61513CB9
P 2450 7100
F 0 "U10" H 2450 7467 50  0000 C CNN
F 1 "TSR_1-2450" H 2450 7376 50  0000 C CNN
F 2 "Converters_DCDC_ACDC:DCDC-Conv_TRACO_TSR-1" H 2450 6950 50  0001 L CIN
F 3 "http://www.tracopower.com/products/tsr1.pdf" H 2450 7100 50  0001 C CNN
	1    2450 7100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 7000 1450 7000
Wire Wire Line
	1150 7100 1400 7100
Wire Wire Line
	1400 7100 1400 7350
Connection ~ 2450 7350
Wire Wire Line
	2900 6450 2900 6550
Wire Wire Line
	2900 6550 1450 6550
Wire Wire Line
	1450 6550 1450 7000
Connection ~ 1450 7000
Wire Wire Line
	1450 7000 1500 7000
$Comp
L power:GND1 #PWR0103
U 1 1 61BF3914
P 2200 7350
F 0 "#PWR0103" H 2200 7100 50  0001 C CNN
F 1 "GND1" H 2205 7177 50  0000 C CNN
F 2 "" H 2200 7350 50  0001 C CNN
F 3 "" H 2200 7350 50  0001 C CNN
	1    2200 7350
	1    0    0    -1  
$EndComp
Connection ~ 2200 7350
Wire Wire Line
	2200 7350 2450 7350
Wire Wire Line
	1400 7350 2200 7350
$Comp
L power:GND1 #PWR0104
U 1 1 61C3B5F7
P 6250 6300
F 0 "#PWR0104" H 6250 6050 50  0001 C CNN
F 1 "GND1" H 6255 6127 50  0000 C CNN
F 2 "" H 6250 6300 50  0001 C CNN
F 3 "" H 6250 6300 50  0001 C CNN
	1    6250 6300
	1    0    0    -1  
$EndComp
Connection ~ 6250 6300
$Comp
L power:GND1 #PWR0105
U 1 1 61C5F996
P 5050 6100
F 0 "#PWR0105" H 5050 5850 50  0001 C CNN
F 1 "GND1" H 5055 5927 50  0000 C CNN
F 2 "" H 5050 6100 50  0001 C CNN
F 3 "" H 5050 6100 50  0001 C CNN
	1    5050 6100
	1    0    0    -1  
$EndComp
$Comp
L power:GND1 #PWR0106
U 1 1 61C83CCE
P 5050 4700
F 0 "#PWR0106" H 5050 4450 50  0001 C CNN
F 1 "GND1" H 5055 4527 50  0000 C CNN
F 2 "" H 5050 4700 50  0001 C CNN
F 3 "" H 5050 4700 50  0001 C CNN
	1    5050 4700
	1    0    0    -1  
$EndComp
$Comp
L pspice:DIODE D1001
U 1 1 61C8566F
P 1700 7000
F 0 "D1001" H 1700 7265 50  0000 C CNN
F 1 "DIODE" H 1700 7174 50  0000 C CNN
F 2 "Diodes_THT:D_DO-15_P10.16mm_Horizontal" H 1700 7000 50  0001 C CNN
F 3 "~" H 1700 7000 50  0001 C CNN
	1    1700 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 7000 1950 7000
Wire Wire Line
	3400 4150 3500 4150
Wire Wire Line
	3500 4150 3500 6250
Wire Wire Line
	3500 6250 1950 6250
Wire Wire Line
	1950 6250 1950 7000
Connection ~ 1950 7000
Wire Wire Line
	1950 7000 2050 7000
$Comp
L Device:R R20
U 1 1 61D15312
P 3050 7000
F 0 "R20" V 2850 7000 50  0000 C CNN
F 1 "470" V 2934 7000 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 2980 7000 50  0001 C CNN
F 3 "~" H 3050 7000 50  0001 C CNN
	1    3050 7000
	0    1    1    0   
$EndComp
$Comp
L Device:LED D1002
U 1 1 61D16967
P 3450 7200
F 0 "D1002" V 3489 7082 50  0000 R CNN
F 1 "LED" V 3398 7082 50  0000 R CNN
F 2 "LEDs:LED_D3.0mm" H 3450 7200 50  0001 C CNN
F 3 "~" H 3450 7200 50  0001 C CNN
	1    3450 7200
	0    -1   -1   0   
$EndComp
Connection ~ 2900 7000
Wire Wire Line
	3200 7000 3450 7000
Wire Wire Line
	3450 7000 3450 7050
Wire Wire Line
	3450 7350 2850 7350
Connection ~ 2850 7350
Wire Wire Line
	2300 2250 2550 2250
Wire Wire Line
	7150 1050 7150 2150
Wire Wire Line
	7050 1050 7050 2250
$Comp
L Connector:Conn_01x04_Male J1001
U 1 1 61903BAF
P 8750 2350
F 0 "J1001" H 8722 2232 50  0001 R CNN
F 1 "I²C" V 8650 2350 50  0000 R CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 8750 2350 50  0001 C CNN
F 3 "~" H 8750 2350 50  0001 C CNN
	1    8750 2350
	-1   0    0    1   
$EndComp
Wire Wire Line
	7050 2250 8550 2250
$Comp
L power:+5V #PWR0102
U 1 1 61974505
P 7750 2600
F 0 "#PWR0102" H 7750 2450 50  0001 C CNN
F 1 "+5V" H 7765 2773 50  0000 C CNN
F 2 "" H 7750 2600 50  0001 C CNN
F 3 "" H 7750 2600 50  0001 C CNN
	1    7750 2600
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 61999477
P 8000 2600
F 0 "#PWR0107" H 8000 2350 50  0001 C CNN
F 1 "GND" H 8005 2427 50  0000 C CNN
F 2 "" H 8000 2600 50  0001 C CNN
F 3 "" H 8000 2600 50  0001 C CNN
	1    8000 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 2450 8000 2450
Wire Wire Line
	8000 2450 8000 2600
Wire Wire Line
	8550 2350 7750 2350
Wire Wire Line
	7750 2350 7750 2600
Wire Wire Line
	3500 1450 3500 2450
Wire Wire Line
	3500 1450 4750 1450
NoConn ~ 5250 2750
Wire Wire Line
	7150 2150 8550 2150
Wire Wire Line
	5500 5300 5500 6200
Wire Wire Line
	5500 6200 6700 6200
Wire Wire Line
	5550 5200 5550 6100
Wire Wire Line
	6500 3000 8100 3000
Wire Wire Line
	8100 3000 8100 3550
Wire Wire Line
	8100 3550 8500 3550
Wire Wire Line
	5800 3700 6500 3700
Wire Wire Line
	6550 3050 8050 3050
Wire Wire Line
	8050 3050 8050 3650
Wire Wire Line
	8050 3650 8500 3650
$Comp
L Connector:Conn_01x16_Male J1002
U 1 1 61B3C7FA
P 8700 4250
F 0 "J1002" H 8672 4224 50  0000 R CNN
F 1 "Conn_01x16_Male" H 8672 4133 50  0000 R CNN
F 2 "Connectors:he10-16d" H 8700 4250 50  0001 C CNN
F 3 "~" H 8700 4250 50  0001 C CNN
	1    8700 4250
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6700 3200 7900 3200
Wire Wire Line
	7900 3200 7900 3750
Wire Wire Line
	7900 3750 8500 3750
Wire Wire Line
	6750 3250 7850 3250
Wire Wire Line
	7850 3250 7850 3850
Wire Wire Line
	7850 3850 8500 3850
Wire Wire Line
	7100 4300 6250 4300
Wire Wire Line
	6750 3250 6750 4100
Wire Wire Line
	6150 4000 7100 4000
Wire Wire Line
	6900 3300 7800 3300
Wire Wire Line
	7800 3300 7800 3950
Wire Wire Line
	7800 3950 8500 3950
Wire Wire Line
	6950 3350 7750 3350
Wire Wire Line
	7750 3350 7750 4050
Wire Wire Line
	7750 4050 8500 4050
Wire Wire Line
	6500 5050 7900 5050
Wire Wire Line
	7900 5050 7900 4150
Wire Wire Line
	7900 4150 8500 4150
Wire Wire Line
	6550 5100 7950 5100
Wire Wire Line
	7950 5100 7950 4250
Wire Wire Line
	7950 4250 8500 4250
Wire Wire Line
	6700 5200 8050 5200
Wire Wire Line
	8050 5200 8050 4350
Wire Wire Line
	8050 4350 8500 4350
Wire Wire Line
	6750 5250 8100 5250
Wire Wire Line
	8100 5250 8100 4450
Wire Wire Line
	8100 4450 8500 4450
Wire Wire Line
	6500 3000 6500 3700
Connection ~ 6550 3600
Wire Wire Line
	6550 3600 6550 3050
Wire Wire Line
	6550 3600 7100 3600
Wire Wire Line
	6500 3700 7100 3700
Connection ~ 6500 3700
Wire Wire Line
	6050 4100 6750 4100
Wire Wire Line
	6700 3200 6700 4200
Connection ~ 6750 4100
Wire Wire Line
	6750 4100 7100 4100
Wire Wire Line
	7100 4200 6700 4200
Connection ~ 6700 4200
Wire Wire Line
	6900 4700 5750 4700
Wire Wire Line
	6900 3300 6900 4700
Wire Wire Line
	5850 4600 6950 4600
Connection ~ 6950 4600
Wire Wire Line
	6950 4600 6950 3350
Wire Wire Line
	6950 4600 7100 4600
Wire Wire Line
	7100 4700 6900 4700
Connection ~ 6900 4700
Wire Wire Line
	5600 5600 6500 5600
Connection ~ 6500 5600
Wire Wire Line
	6500 5050 6500 5600
Wire Wire Line
	5650 5500 6550 5500
Wire Wire Line
	5550 6100 6750 6100
Wire Wire Line
	6700 5200 6700 6200
Connection ~ 6550 5500
Wire Wire Line
	6550 5500 6550 5100
Wire Wire Line
	6550 5500 7150 5500
Wire Wire Line
	6500 5600 7150 5600
Connection ~ 6750 6100
Wire Wire Line
	6750 6100 6750 5250
Wire Wire Line
	6750 6100 7150 6100
Wire Wire Line
	6700 6200 7150 6200
Connection ~ 6700 6200
Wire Wire Line
	8500 4550 8400 4550
Wire Wire Line
	8400 4550 8400 4750
Wire Wire Line
	8400 4750 8500 4750
Wire Wire Line
	8400 4750 8400 4950
Wire Wire Line
	8400 4950 8500 4950
Connection ~ 8400 4750
Wire Wire Line
	8500 4650 8300 4650
Wire Wire Line
	8300 4650 8300 4850
Wire Wire Line
	8300 4850 8500 4850
Wire Wire Line
	8300 4850 8300 5000
Wire Wire Line
	8300 5050 8500 5050
Connection ~ 8300 4850
Wire Wire Line
	6250 4950 8400 4950
Connection ~ 6250 4950
Wire Wire Line
	6250 4950 6250 5700
Connection ~ 8400 4950
Wire Wire Line
	6150 5000 8300 5000
Connection ~ 6150 5000
Wire Wire Line
	6150 5000 6150 5400
Connection ~ 8300 5000
Wire Wire Line
	8300 5000 8300 5050
Wire Wire Line
	5450 3900 5800 3900
Wire Wire Line
	5800 3900 5800 3700
Wire Wire Line
	5450 3800 5700 3800
Wire Wire Line
	5700 3800 5700 3600
Wire Wire Line
	5700 3600 6550 3600
Wire Wire Line
	5450 3700 5550 3700
Connection ~ 5550 3700
Wire Wire Line
	5550 3700 5550 3500
$EndSCHEMATC
