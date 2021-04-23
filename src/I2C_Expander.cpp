
#include "I2C_Expander.h"

#include "PCF8574.h"

byte address2[] = {0x38, 0x3c};
PCF8574 i2c2[] = {PCF8574(address2[0]), PCF8574(address2[1])};

void I2C_Expander::signal_on(byte _pin) {
  byte index = _pin / 8;
  byte pin = _pin % 8;

  i2c2[index].digitalWrite(pin, LOW);
  state[index] = state[index] | 1 << pin;

  Serial.print(index);
  Serial.print(":");
  Serial.println(state[index]);

}

void I2C_Expander::signal_off(byte _pin) {
  byte index = _pin / 8;
  byte pin = _pin % 8;

  i2c2[index].digitalWrite(pin, HIGH);
  state[index] = state[index] & ~(1 << pin);

  Serial.print(index);
  Serial.print(":");
  Serial.println(state[index]);
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

void I2C_Expander::checkAll() {
  for (byte i = 0; i < amountI2c * 8; i++) {
    signal_on(i);
    delay(100);
  }

  for (byte i = amountI2c * 8; i > 0; i--) {
    signal_off(i - 1);
    delay(100);
  }
}


void I2C_Expander::setSignal(Signal_i2c signal) {    
    byte value = signal.get();

    for (byte i = 0, pin = 0 ; i< 5; i++, pin++){
        Serial.print("Value: [");
        Serial.print(value);
        Serial.println("]");

        Serial.print("Pin: [");
        Serial.print(pin);
        Serial.print("] ");
        if (value & 0x01){
            Serial.print("on ->");
            signal_on(pin);
        } else {
            signal_off(pin);
            Serial.print("off ->");
        }
        value = value >> 1;
    }


}