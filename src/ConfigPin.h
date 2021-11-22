#ifndef CONFIG_PIN
#define CONFIG_PIN

#include <Arduino.h>

uint16_t valueToKeyMap [4] = {1023, 700, 328, 285 };

byte mapValueToKey (int value) {
  for (byte i=0; i <  ( sizeof valueToKeyMap / sizeof valueToKeyMap[0]) ; i++) {
    if (abs(value - valueToKeyMap[i]) < 10) {
      return i;
    }
  }
  return 0;
}

byte readCongigPin(){
    return mapValueToKey(analogRead(A6));
}


#endif