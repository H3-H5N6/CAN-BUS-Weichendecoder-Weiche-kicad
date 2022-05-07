#ifndef SERIAL_CONFIGURATION_H
#define SERIAL_CONFIGURATION_H

#define ZAHL_LENGTH 4

#include "CanConfiguration.h"
#include "NmraDcc.h"

typedef void (*ChangeWeicheOrSignal)(uint16_t);

class SerialConfiguration {
 public:
  SerialConfiguration();
  void init(CAN_CONFIGURATION &conf, NmraDcc &dcc, ChangeWeicheOrSignal cWorS);
  void printConfiguration();
  void reset_zahl();
  uint16_t calc_zahl();
  void process();

 private:
  CAN_CONFIGURATION can_configuration;
  NmraDcc dcc;
  boolean change_id = false;
  boolean change_weiche = false;
  uint16_t last_weiche = -1;
  uint8_t zahl[ZAHL_LENGTH];
  uint8_t zahl_pos = 0;
  void setAndWriteNewId();
  ChangeWeicheOrSignal changeWeicheOrSignalCallback = {};
  void printPrefix();
  void printLine(byte index, const __FlashStringHelper *ifsh);
  void printLineln(byte index, const __FlashStringHelper *ifsh);
};

#endif