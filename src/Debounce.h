#ifndef DEBOUNCE_H
#define DEBOUNCE_H

#include <Arduino.h>

class Debounce {
 public:
  boolean isDebounceSet(uint16_t dccAddr, uint8_t direction);
  void setDebounceBit(uint16_t dccAddr, uint8_t direction);
  void clearDebounceBit(uint16_t dccAddr, uint8_t direction);

 protected:
  Debounce();
  virtual uint8_t getDebounceMaske(uint16_t dccAddr, uint8_t direction) = 0;

 private:
  uint8_t debounceBits;
};

#endif