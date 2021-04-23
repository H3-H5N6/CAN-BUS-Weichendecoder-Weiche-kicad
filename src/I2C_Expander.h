#ifndef I2C_EXPANDER_H
#define I2C_EXPANDER_H

#include "PCF8574.h"
#include "Signal_i2c.h"

class I2C_Expander {
 public:
  void signal_on(byte _pin);
  void signal_off(byte _pin);
  void init();
  void checkAll();

  void setSignal(Signal_i2c signal);

 private:
  byte amountI2c = 2;
  byte state [2] = { 0,0 };
};

#endif