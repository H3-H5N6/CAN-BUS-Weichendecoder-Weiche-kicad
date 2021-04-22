#ifndef I2C_EXPANDER_H
#define I2C_EXPANDER_H

#include "PCF8574.h"

class I2C_Expander {
 public:
  void signal_on(byte _pin);
  void signal_off(byte _pin);
  void init();
  void checkAll();

 private:
  byte amountI2c = 2;
};

#endif