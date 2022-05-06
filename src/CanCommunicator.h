#ifndef CAN_COMMUNICATOR_H
#define CAN_COMMUNICATOR_H

#include <ACAN2515.h>
#include <Arduino.h>
#include <EEPROM.h>

#include "CanConfiguration.h"
#include "Signal.h"
#include "Weiche.h"

typedef void (*ChangeWeiche)(uint16_t);

class CanComm {
 public:
  CanComm(CAN_CONFIGURATION *_conf, Weiche *weiche, Signal *signal, ChangeWeiche _cw);
  void sendDetailWeichenStatus();
  void processCanMessageGetStatus();
  void processCanMessageChangeState();
  void processCanMessage();
  void init();
  void initCanConfiguraion(byte configPin);
  void printConfig();

 private:
  CAN_CONFIGURATION *conf;
  CANMessage frame;
  Weiche *weiche;
  Signal *signal;
  boolean send_mode = 0;
  ChangeWeiche changeWeicheCallback = {};

  void printlnCanDebug(const __FlashStringHelper *key, const uint32_t value);
  void printlnCanDebug(const __FlashStringHelper *key);
  void printCanDebug(const __FlashStringHelper *key);
  void printCanDebug(const __FlashStringHelper *key, const uint32_t value);
  void printlnCanInfo(const __FlashStringHelper *key, const uint32_t value);
  void printlnCanInfo(const __FlashStringHelper *key);
  void initCanIds();
  void initVersion();
  void writeCanConfigToEEPROM();
};

#endif