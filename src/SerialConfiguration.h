#ifndef SERIAL_CONFIGURATION_H
#define SERIAL_CONFIGURATION_H

#define ZAHL_LENGTH 4

#include "CanConfiguration.h"
#include "NmraDcc.h"

typedef void (*ChangeWeiche)(uint16_t);
typedef void (*ChangeSignal)(uint16_t);

class SerialConfiguration {
 public:
  SerialConfiguration();
  void init(CAN_CONFIGURATION &conf, NmraDcc &dcc, ChangeWeiche changeWeiche, ChangeSignal changeSignal);
  void printConfiguration();
  void reset_zahl();
  uint16_t calc_zahl();
  void process();

 private:
  CAN_CONFIGURATION can_configuration;
  NmraDcc dcc;
  boolean change_id = false;
  boolean change_weiche = false;
  boolean change_signal = false;
  uint16_t last_weiche = 0;
  uint16_t last_signal = 0;
  uint8_t zahl[ZAHL_LENGTH];
  uint8_t zahl_pos = 0;
  void setAndWriteNewId();
  ChangeWeiche changeWeicheCallback = {};
  ChangeSignal changeSignalCallback = {};
  void printPrefix();
  void printLine(byte index, const __FlashStringHelper *ifsh);
  void printLineln(byte index, const __FlashStringHelper *ifsh);
};

#endif