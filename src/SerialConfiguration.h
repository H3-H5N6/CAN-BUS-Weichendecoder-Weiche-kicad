#ifndef SERIAL_CONFIGURATION_H
#define SERIAL_CONFIGURATION_H

#define ZAHL_LENGTH 4

#include "CanConfiguration.h"

class SerialConfiguration {
 public:
  SerialConfiguration();
  void init(CAN_CONFIGURATION &conf);
  void printConfiguration();
  void reset_zahl();
  uint16_t calc_zahl();
  void process();

 private:
  CAN_CONFIGURATION can_configuration;
  boolean change_id = false;
  uint8_t zahl[ZAHL_LENGTH];
  uint8_t zahl_pos = 0;
  void setAndWriteNewId();
};

#endif