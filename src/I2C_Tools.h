#ifndef I2C_Tools_h
#define I2C_Tools_h

#include <Arduino.h>
#include <PCF8574.h>
#include <Wire.h>

#define MAX_I2C_DEVICES 4

#define DEBUG_I2C

class I2C_Tools {
 public:
  I2C_Tools() {}
  void init_i2c();
  void scan_i2c();
  

 private:
  // PCF8574 pcf8574[MAX_I2C_DEVICES] = {PCF8574(0x38), PCF8574(0x3a), PCF8574(0x39), PCF8574(0x3B)};
  uint8_t i2c_address[MAX_I2C_DEVICES];

  
};
#endif
