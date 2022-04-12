#ifndef I2C_Tools_h
#define I2C_Tools_h

#include <Arduino.h>
#include <Wire.h>

#define MAX_I2C_DEVICES 4

class I2C_Tools {
 public:
  I2C_Tools() {}
  void init_i2c();
  void scan_i2c(uint8_t adr[4]);
};
#endif
