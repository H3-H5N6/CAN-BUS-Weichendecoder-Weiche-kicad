#ifndef I2C_SIGNAL
#define I2C_SIGNAL

#include <Arduino.h>
#include <I2C_Tools.h>
#include <PCF8574.h>

#include "Socket.h"

class I2CSignal {
 public:
  I2CSignal();
  // I2CSignal(PCF8574 pcf[MAX_I2C_DEVICES]);
  void setNewState(uint8_t value, uint8_t index);
  boolean writeState();
  uint8_t getHP0(SIGNAL::SOCKET socket);
  uint8_t getHP1(SIGNAL::SOCKET socket);
  uint8_t getHP2(SIGNAL::SOCKET socket);
  uint8_t getSH1(SIGNAL::SOCKET socket);
  void init_pcf8574();

 private:
  uint32_t i2cstate = 0x00000000;

  PCF8574 pcf8574[MAX_I2C_DEVICES] = {PCF8574(0x38), PCF8574(0x3a), PCF8574(0x39), PCF8574(0x3B)};

  // Bit-Maske für jedes Signal
  // 0b11111111111111111111111111100000 - 0xffffffe0,
  // 0b11111111111111111111110000011111 - 0xfffffc1f
  // 0b11111111111111111000001111111111 - 0xFFFF83FF
  // 0b11111111111000001111111111111111 - 0xFFE0FFFF
  // 0b11111100000111111111111111111111 - 0xFC1FFFFF
  // 0b10000011111111111111111111111111 - 0x83FFFFFF

  uint32_t mask[6] = {0xffffffe0, 0xfffffc1f, 0xFFFF83FF, 0xFFE0FFFF, 0xFC1FFFFF, 0x83FFFFFF};
};

#endif