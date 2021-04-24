#ifndef I2C_Tools_h
#define I2C_Tools_h

#include <Arduino.h>

#include <Wire.h>

/**
 * Scant den I2C-Bus und gibt die gefundenen Adressen als Hex-Zahl auf der Konsole aus.
 */
void scan_i2c() {
	uint8_t result;
	uint8_t address;
	uint8_t amountFoundedDevices;

	char addressAsString[6];

	Serial.println("Scanning i2c...");

	amountFoundedDevices = 0;
	for (address = 1; address < 127; address++) {
		sprintf(addressAsString, " 0x%02x", address);

		Wire.beginTransmission(address);
		result = Wire.endTransmission();

		switch (result) {
		case 4:
			Serial.print("Unknown error at address ");
			/* no break */
		case 0:
			amountFoundedDevices++;
			Serial.print(addressAsString);
			break;
		default:
			Serial.print(".");
		}
	}
	if (amountFoundedDevices == 0) {
		Serial.println("No I2C devices found\n");
	} else {
		Serial.println("done\n");
	}
}

#endif