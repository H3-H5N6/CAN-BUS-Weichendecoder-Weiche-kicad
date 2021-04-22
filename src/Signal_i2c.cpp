#include "Signal_i2c.h"

void Signal_i2c::set(SIGNAL::State _state) {
  switch (state) {
    case SIGNAL::HP0:
    case SIGNAL::HP1:
    case SIGNAL::HP2:
    case SIGNAL::HP0_SH1:
      state = _state;
      break;
  }
}

SIGNAL::State Signal_i2c::get() {
  return state;
}

boolean Signal_i2c::isHP0() {
  return ((state & SIGNAL::HP0) != 0);
}

boolean Signal_i2c::isHP1() {
  return ((state & SIGNAL::HP1) != 0);
}

boolean Signal_i2c::isHP2() {
  return ((state & SIGNAL::HP2) != 0);
}

boolean Signal_i2c::isHP0_SH1() {
  return ((state & SIGNAL::HP0_SH1) != 0);
}
