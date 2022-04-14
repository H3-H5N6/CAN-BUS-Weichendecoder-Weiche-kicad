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
  void init_pcf8574();
  uint8_t getHP0();
  uint8_t getHP1();
  uint8_t getHP2();
  uint8_t getSH1();

 private:
  PCF8574 pcf8574[MAX_I2C_DEVICES] = {PCF8574(0x38), PCF8574(0x3a), PCF8574(0x39), PCF8574(0x3B)};
  uint8_t i2c_address[MAX_I2C_DEVICES];

  // Bit-Maske für jedes Signal
  uint32_t mask[6] = {0xffffffe0, 0xfffffc1f, 0xFFFF83FF, 0xFFF07FFF, 0xFE0FFFFF, 0xC1FFFFFF};
  void setNewState(uint8_t value, uint8_t index);
  boolean writeState();

  uint32_t state = 0x00000000;
  
};
#endif
