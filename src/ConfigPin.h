#ifndef CONFIG_PIN
#define CONFIG_PIN

#include <Arduino.h>

class ConfigPin {
 public:
  ConfigPin(){};
  byte readCongigPin();

 private:
  int valueToKeyMap[4] = {1023, 700, 328, 285};
  byte mapValueToKey(int value);
};

#endif