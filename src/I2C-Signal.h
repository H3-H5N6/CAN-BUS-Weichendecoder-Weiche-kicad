#ifndef I2C_SIGNAL
#define I2C_SIGNAL

#include <Arduino.h>
#include <I2C_Tools.h>
#include <PCF8574.h>

class I2CSignal {
 public:
  //I2CSignal(PCF8574 pcf[MAX_I2C_DEVICES]);
  void setNewState(uint8_t value, uint8_t index);
  boolean writeState();
  uint8_t getHP0();
  uint8_t getHP1();
  uint8_t getHP2();
  uint8_t getSH1();
  void init_pcf8574();

 private:
  uint32_t i2cstate = 0x00000000;
  
  PCF8574 pcf8574[MAX_I2C_DEVICES] = {PCF8574(0x38), PCF8574(0x3a), PCF8574(0x39), PCF8574(0x3B)};
  uint8_t i2c_address[MAX_I2C_DEVICES];

  // Bit-Maske für jedes Signal
  uint32_t mask[6] = {0xffffffe0, 0xfffffc1f, 0xFFFF83FF, 0xFFF07FFF, 0xFE0FFFFF, 0xC1FFFFFF};
};

#endif