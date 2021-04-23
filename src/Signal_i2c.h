#ifndef SIGNAL_I2C_H
#define SIGNAL_I2C_H

#include <Arduino.h>

namespace SIGNAL {

// gr
// r1 r2
//    we
// we
// ge

enum State {  // xx|xx|xx|we|ge|gr|r2|r1
  HP0 = B00000011,
  HP1 = B00000100,
  HP2 = B00001100,
  HP0_SH1 = B00010001,
  OFF = B00000000
};

}  // namespace SIGNAL

class Signal_i2c {
 public:
  Signal_i2c(byte id, byte firstPin);

  byte getId();

  void set(SIGNAL::State state);

  SIGNAL::State get();

  boolean isHP0();

  boolean isHP1();

  boolean isHP2();

  boolean isHP0_SH1();

 private:
  SIGNAL::State state;
  byte id;
  byte firstPin;
};

#endif