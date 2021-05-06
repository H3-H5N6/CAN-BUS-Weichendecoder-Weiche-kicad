#ifndef I2C_EXPANDER_H
#define I2C_EXPANDER_H

#include "PCF8574.h"
#include "Signal_i2c.h"

// #define DEBUG_EXPANDER

class I2C_Expander {
 public:
  void on(byte _pin);
  void off(byte _pin);
  void init();
  void checkAll();

  void setSignal(Signal_i2c signal);

 private:
  byte amountI2c = 3;
  byte state [3] = { 0, 0 ,0};
};

#endif