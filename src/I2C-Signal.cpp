#include <I2C-Signal.h>

I2CSignal::I2CSignal() {
}

uint8_t I2CSignal::getHP0(SIGNAL::SOCKET socket) {
  switch (socket) {
    case SIGNAL::SOCKET::RJ12:
      return 0b00000101;  // _ge_ _we_ _r2_ _gr_ _r1_
  }
  return 0b00001100;
}

uint8_t I2CSignal::getHP1(SIGNAL::SOCKET socket) {
  switch (socket) {
    case SIGNAL::SOCKET::RJ12:
      return 0b00000010;
  }
  return 0b00010000;  // _gr_ _r1_ _r2_ _ge_ _we_
}
uint8_t I2CSignal::getHP2(SIGNAL::SOCKET socket) {
  switch (socket) {
    case SIGNAL::SOCKET::RJ12:
      return 0b00010010;
  }
  return 0b00010010;
}

uint8_t I2CSignal::getSH1(SIGNAL::SOCKET socket) {
  switch (socket) {
    case SIGNAL::SOCKET::RJ12:
      return 0b00001001;
  }
  return 0b00001001;
}

void I2CSignal::setNewState(uint8_t value, uint8_t index) {
  i2cstate = (i2cstate & mask[index]) | (((uint32_t)value) << ((index * 5) + (index / 3)));
}

boolean I2CSignal::writeState() {
#ifdef DEBUG_I2C
  Serial.print(F("DEBUG I2C state: "));
  Serial.println(i2cstate, HEX);
#endif

  boolean result = true;
  for (uint8_t i = 0; i < 4; i++) {
    uint8_t value = i2cstate >> ((i * 8)) & 0xff;
#ifdef DEBUG_I2C
    Serial.print(F("DEBUG I2C Schreibe "));
    Serial.print(i);
    Serial.print(": ");
    Serial.print(value, HEX);
#endif
    if (pcf8574[i].digitalWriteAll(value)) {
      Serial.println(F(" OK"));
    } else {
      Serial.println(F(" ERROR"));
      result = false;
    }
  }
  return result;
}

void I2CSignal::init_pcf8574() {
  for (byte i = 0; i < 4; i++) {
    for (byte j = 0; j < 8; j++) {
      pcf8574[i].pinMode(j, OUTPUT, HIGH);
    }

    // PCF 8574 starten
    Serial.print(F("Beginn ["));
    Serial.print(i);
    Serial.print(F("]: "));
    if (pcf8574[i].begin()) {
      Serial.println(F("OK"));
    } else {
      Serial.println(F("KO"));
    }
  }
  delay(2000);
}