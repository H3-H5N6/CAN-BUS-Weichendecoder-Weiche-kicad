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
void I2C_Tools::scan_i2c(uint8_t adr[4]) {
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
          adr[amountFoundedDevices] = address;
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
}

void I2C_Tools::init_pcf8574() {
  for (byte i = 0; i < 4; i++) {
    for (byte j = 0; j < 8; j++) {
      pcf8574[i].pinMode(P0, OUTPUT, LOW);
      pcf8574[i].pinMode(P1, OUTPUT, LOW);
      pcf8574[i].pinMode(P2, OUTPUT, LOW);
      pcf8574[i].pinMode(P3, OUTPUT, HIGH);
      pcf8574[i].pinMode(P4, OUTPUT, HIGH);
      pcf8574[i].pinMode(P5, OUTPUT, HIGH);
      pcf8574[i].pinMode(P6, OUTPUT, HIGH);
      pcf8574[i].pinMode(P7, OUTPUT, HIGH);
    }

    // PCF 8574 starten
    Serial.print(F("Beginn ["));
    Serial.print(i);
    Serial.print(F("]: "));
    if (pcf8574[i].begin()) {
      Serial.println("OK");
    } else {
      Serial.println("KO");
    }
  }
  delay(4000);
  Serial.println("HP0");
  delay(1000);

  // Alle Signale auf HP0 stellen
  for (uint8_t index = 0; index < 3; index++) {
    setNewState(getHP0(), index);
  }
  writeState();

}

void I2C_Tools::setNewState(uint8_t value, uint8_t index) {
  state = (state & mask[index]) | (value << index * 5);
}

boolean I2C_Tools::writeState() {
  boolean result = true;
  for (uint8_t i = 0; i < 4; i++) {
    uint8_t value = state >> ((i * 8)) & 0xff;
    #ifdef DEBUG_I2C
    Serial.print(F("Schreibe "));
    Serial.print(i);
    Serial.print(": ");
    Serial.print(value);
    #endif
    if (pcf8574[i].digitalWriteAll(value)) {
      Serial.println(" OK");
    } else {
      Serial.println(" ERROR");
      result = false;
    }
  }
  return result;
}


uint8_t I2C_Tools::getHP0() {
  return 0b00001100;
}

uint8_t I2C_Tools::getHP1() {
  return 0b00010000;  // _gr_ _r1_ _r2_ _ge_ _we_
}
uint8_t I2C_Tools::getHP2() {
  return 0b00010010;
}

uint8_t I2C_Tools::getSH1() {
  return 0b00001001;
}