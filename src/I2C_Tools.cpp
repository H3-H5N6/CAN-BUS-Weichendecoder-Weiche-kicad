#include "I2C_Tools.h"

/**
 * Initialisert den i2c, muss vor der ersten Nutzung von i2c aufgeruft werden.
 *
 */
void I2C_Tools::init_i2c() {
  Wire.begin();
}

/**
 * Scant den I2C-Bus und gibt die gefundenen Adressen als Hex-Zahl auf der Konsole aus.
 */
void I2C_Tools::scan_i2c() {
  uint8_t result;
  uint8_t address;
  uint8_t amountFoundedDevices;

  char addressAsString[6];

  amountFoundedDevices = 0;
  for (address = 1; address < 127; address++) {
    sprintf(addressAsString, " 0x%02x", address);

    Wire.beginTransmission(address);
    result = Wire.endTransmission();

    switch (result) {
      case 4:
        Serial.print("E ");
        /* no break */
      case 0:
        if (amountFoundedDevices < MAX_I2C_DEVICES) {
          i2c_address[amountFoundedDevices] = address;
        }
        amountFoundedDevices++;
        Serial.print(addressAsString);
        break;
      default:
        Serial.print(".");
    }
  }
  if (amountFoundedDevices == 0) {
    Serial.println(F("No I2C devices found"));
  } else {
    Serial.println(F("done"));
  }

  Serial.println(F("> gefundene I2C-Adressen: "));

  for (uint8_t i = 0; i < MAX_I2C_DEVICES; i++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.println(i2c_address[i]);
  }
  Serial.println(F("= done"));
}
