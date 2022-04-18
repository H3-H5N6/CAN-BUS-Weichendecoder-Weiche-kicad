#include "ConfigPin.h"

byte ConfigPin::mapValueToKey(int value) {
  Serial.print(F("Value ["));
  Serial.print(value);
  Serial.println(F("]"));
  for (byte i = 0; i < (sizeof valueToKeyMap / sizeof valueToKeyMap[0]); i++) {
    if (abs(value - valueToKeyMap[i]) < 10) {
      return i;
    }
  }
  return 0;
}

byte ConfigPin::readCongigPin() {
  return mapValueToKey(analogRead(A6));
}
