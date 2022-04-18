#ifndef SOCKET_H
#define SOCKET_H

#include <Arduino.h>

namespace SIGNAL {
enum SOCKET : uint8_t {
  RJ12,
  PIN,
  WAGO
};
}

#endif