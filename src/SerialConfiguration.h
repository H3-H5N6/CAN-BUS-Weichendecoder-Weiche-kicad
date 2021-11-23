#ifndef SERIAL_CONFIGURATION_H
#define SERIAL_CONFIGURATION_H

#define ZAHL_LENGTH 4

#include "CanConfiguration.h"

typedef void (*ChangeWeiche)(uint16_t);

class SerialConfiguration {
 public:
  SerialConfiguration();
  void init(CAN_CONFIGURATION &conf, ChangeWeiche cw);
  void printConfiguration();
  void reset_zahl();
  uint16_t calc_zahl();
  void process();

 private:
  CAN_CONFIGURATION can_configuration;
  boolean change_id = false;
  boolean change_weiche = false;
  uint8_t zahl[ZAHL_LENGTH];
  uint8_t zahl_pos = 0;
  void setAndWriteNewId();
  ChangeWeiche changeWeicheCallback = {};
};

#endif