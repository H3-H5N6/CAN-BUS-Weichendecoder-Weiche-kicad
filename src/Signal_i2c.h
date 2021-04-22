#ifndef SIGNAL_I2C_H
#define SIGNAL_I2C_H

#include <Arduino.h>

namespace SIGNAL {

// gr
// r1 r2
//    we
// we
// ge

enum State {  // xx|xx|xx|we|ge|gr|r1|r2
  HP0 = B00000011,
  HP1 = B00000100,
  HP2 = B00001000,
  HP0_SH1 = B00010010
};

}  // namespace SIGNAL

class Signal_i2c {
 public:
  void set(SIGNAL::State state);

  SIGNAL::State get();

  boolean isHP0();

  boolean isHP1();

  boolean isHP2();

  boolean isHP0_SH1();

 private:
  SIGNAL::State state;
};

#endif