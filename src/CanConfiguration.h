#ifndef CAN_CONFIGURATION_H
#define CAN_CONFIGURATION_H

#include <Arduino.h>

#define CAN_BUS_OFFSET 256

typedef struct {
  uint16_t version;
  uint16_t modulId;
  uint16_t firstIdWeiche;
  uint16_t firstIdSignal;
} CONFIGURATION;

typedef union {
  CONFIGURATION config;
  uint16_t data[4];
} CAN_CONFIGURATION;

#endif