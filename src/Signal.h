#ifndef SIGNAL_H
#define SIGNAL_H

#include <Arduino.h>

#include "Debounce.h"
#include "I2C-Signal.h"
#include "Socket.h"

namespace SIGNAL {
enum POSITION : uint8_t {
  UNKNOWN,  // 0
  HP0,      // 1
  HP1,      // 2
  HP2,      // 3
  HP0SH1    // 4
};

enum STATE : uint8_t {
  SET,               // Postion wurde intern gesetzt
  POSITION_REACHED,  // Postion wurde auch extern gesetzt
  UNKNOWN_STATE
};
}  // namespace SIGNAL

class Signal : public Debounce {
 public:
  Signal(uint16_t address, uint16_t dccAddress, uint8_t i2cIndex, I2CSignal *i2c, SIGNAL::SOCKET socket);
  void process();
  boolean find(uint16_t address);
  boolean findDccAddr(uint16_t address);
  boolean change(uint16_t address);
  boolean changeDcc(uint16_t _address, uint8_t direkction);

  boolean isHp0();
  boolean isHp1();
  boolean isHp2();
  boolean isSh1();

 private:
  SIGNAL::STATE state;
  SIGNAL::POSITION position;
  uint16_t firstAddress;
  uint16_t lastAddress;
  uint16_t firstDccAddress;
  uint16_t lastDccAddress;
  uint8_t i2cIndex;
  I2CSignal *i2csignal;
  SIGNAL::SOCKET socket;
  uint8_t getDebounceMaske(uint16_t dccAddr, uint8_t direction);
};

#endif