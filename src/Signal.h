#ifndef SIGNAL_H
#define SIGNAL_H

#include <Arduino.h>
#include "I2C-Signal.h"

namespace SIGNAL {
enum POSITION: uint8_t {
  UNKNOWN, // 0
  HP0, // 1
  HP1, // 2
  HP2, // 3
  HP0SH1 // 4
};

enum STATE: uint8_t {
  SET,               // Postion wurde intern gesetzt
  POSITION_REACHED,  // Postion wurde auch extern gesetzt
  UNKNOWN_STATE
};
}  // namespace SIGNAL

class Signal {
 public:
  Signal(uint16_t address, uint8_t index , I2CSignal *i2c);
  void process();
  boolean change(uint16_t address);
  void hp0();
  void hp1();
  void hp2();
  void sh1();


  boolean isHp0();
  boolean isHp1();
  boolean isHp2();
  boolean isSh1();


 private:
  SIGNAL::STATE state;
  SIGNAL::POSITION position;
  uint16_t firstAddress;
  uint16_t lastAddress;
  uint8_t index;
  I2CSignal *i2csignal;
};

#endif