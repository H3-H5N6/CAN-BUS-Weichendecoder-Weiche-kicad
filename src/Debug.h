#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>

void print(const __FlashStringHelper *ifsh) {
  Serial.print(F("DEBUG MEM "));
  Serial.print(ifsh);
  Serial.print(F(": "));
}

void free_dump() {
  uint8_t *heapptr;
  uint8_t *stackptr;

  stackptr = (uint8_t *)malloc(4);  // use stackptr temporarily
  heapptr = stackptr;               // save value of heap pointer
  free(stackptr);                   // free up the memory again (sets stackptr to 0)
  stackptr = (uint8_t *)(SP);       // save value of stack pointer

  print(F("Speicher"));
  Serial.println();

  print(F("HP"));
  Serial.println((int)heapptr);

  print(F("SP"));
  Serial.println((int)stackptr);

  print(F("Free"));
  Serial.println((int)stackptr - (int)heapptr);
  Serial.println();
}

#endif