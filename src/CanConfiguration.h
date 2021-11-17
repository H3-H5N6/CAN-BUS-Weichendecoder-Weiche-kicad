#ifndef CAN_CONFIGURATION_H
#define CAN_CONFIGURATION_H

#include <Arduino.h>

#define CAN_BUS_OFFSET 256

typedef struct {
  uint16_t version;
  uint16_t id;
  uint16_t id_weichen[10];
} CONFIGURATION;

typedef union {
  CONFIGURATION config;
  uint16_t data[12];
} CAN_CONFIGURATION;

#endif