#include "Debounce.h"

Debounce::Debounce() {
  debounceBits = 0;
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
