#include "Debounce.h"

Debounce::Debounce() {
}

uint8_t Debounce::getDebounceMaske(uint16_t dccAddr, uint8_t direction) {
  uint8_t mask = 0;
  // if (dccAddr == dccAddr) {
  mask = 0b001;
  //}
  if (direction > 0) {
    mask = mask << 1;
  }
  return mask;
}

boolean Debounce::isDebounceSet(uint16_t dccAddr, uint8_t direction) {
  // if (findDccAddr(dccAddr)) {
  if ((debounceBits & getDebounceMaske(dccAddr, direction)) > 0) {
    return true;
  }
  //}
  return false;
}

void Debounce::setDebounceBit(uint16_t dccAddr, uint8_t direction) {
  debounceBits = debounceBits | getDebounceMaske(dccAddr, direction);
}

void Debounce::clearDebounceBit(uint16_t dccAddr, uint8_t direction) {
  debounceBits = debounceBits & ~getDebounceMaske(dccAddr, direction);
}