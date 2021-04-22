
#include "I2C_Expander.h"

#include "PCF8574.h"

byte address2[] = {0x38, 0x3c};
PCF8574 i2c2[] = {PCF8574(address2[0]), PCF8574(address2[1])};

void I2C_Expander::signal_on(byte _pin) {
  byte index = _pin / 8;
  byte pin = _pin % 8;

  i2c2[index].digitalWrite(pin, LOW);
}

void I2C_Expander::signal_off(byte _pin) {
  byte index = _pin / 8;
  byte pin = _pin % 8;

  i2c2[index].digitalWrite(pin, HIGH);
}

void I2C_Expander::init() {
  for (byte j = 0; j < amountI2c; j++) {
    for (byte i = 0; i < 8; i++) {
      i2c2[j].pinMode(i, OUTPUT, HIGH);
    }
  }

  for (byte j = 0; j < amountI2c; j++) {
    i2c2[j].begin();
  }
}