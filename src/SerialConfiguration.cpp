#include "SerialConfiguration.h"

#include <Arduino.h>
#include <EEPROM.h>

#define HELP 1
#define CONF 2

SerialConfiguration::SerialConfiguration() {
}

void SerialConfiguration::printLineln(byte index, const __FlashStringHelper *ifsh) {
  printLine(index, ifsh);
  Serial.println();
}

void SerialConfiguration::printLine(byte index, const __FlashStringHelper *ifsh) {
  Serial.print(F("Config"));
  switch (index) {
    case HELP:
      Serial.print(F(".help"));
      break;
    case CONF:
      Serial.print(F(".conf"));
      break;
  }
  Serial.print(F(": "));
  Serial.print(ifsh);
}

void SerialConfiguration::printPrefix() {
  Serial.print(F("Config: "));
}

void SerialConfiguration::init(CAN_CONFIGURATION &_conf, NmraDcc &_dcc, ChangeWeiche _cw) {
  can_configuration = _conf;
  changeWeicheCallback = _cw;
  dcc = _dcc;
}

void SerialConfiguration::setAndWriteNewId() {
  can_configuration.config.modulId = calc_zahl();
  EEPROM.put(CAN_BUS_OFFSET, can_configuration);
}

void SerialConfiguration::reset_zahl() {
  zahl_pos = 0;
  for (uint8_t i = 0; i < ZAHL_LENGTH; i++) {
    zahl[i] = 0;
  }
}

uint16_t SerialConfiguration::calc_zahl() {
  uint16_t result = 0;
  uint16_t stelle = 1;

  for (uint8_t i = zahl_pos; i > 0; i--) {
    result = result + (zahl[i - 1] * stelle);
    stelle = stelle * 10;
  }
  return result;
}

void SerialConfiguration::process() {
  if (Serial.available()) {
    int input = Serial.read();
    switch (char(input)) {
      case 'p':
        change_id = false;
        reset_zahl();
        printConfiguration();
        return;
      case 'i':
        change_id = true;
        reset_zahl();
        Serial.print(F("Neue ID: "));
        return;
      case 'w':
        change_weiche = true;
        reset_zahl();
        Serial.print(F("Output: "));
        return;
      case 'q':
        change_id = false;
        reset_zahl();
        Serial.println(F(" Abbruch"));
        return;
      case 'h':
        //                   =======================================
        printLineln(HELP, F("=== Hilfe ============================="));
        printLineln(HELP, F("p           : Ausgabe der Konfiguartion"));
        printLineln(HELP, F("i <MODUL_ID>: Neue Modul Id setzen"));
        printLineln(HELP, F("q           : Abbruch der Eingabe"));
        printLineln(HELP, F("h           : Diese Hilfe"));
        return;
      case '+':
        if (last_weiche > 0) {
          last_weiche = last_weiche + 2;
        }
      case '-':
        if (last_weiche > 1) {
          last_weiche--;
        }
        Serial.print(F("Stelle Weiche: "));
        Serial.println(last_weiche);
        changeWeicheCallback(last_weiche);
        return;
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        if (!change_id && !change_weiche) {
          return;
        }
        Serial.print(char(input));
        if (zahl_pos > 3) {
          reset_zahl();
        }
        zahl[zahl_pos] = input - 48;
        zahl_pos++;
        return;
      case '\r':
        return;
      case '\n':
        Serial.print(char(input));
        if (change_id) {
          Serial.print(F("Setze neue Id: "));
          Serial.println(calc_zahl());
          setAndWriteNewId();
          change_id = false;
        }

        if (change_weiche) {
          Serial.print(F("Stelle Weiche: "));
          Serial.println(calc_zahl());
          changeWeicheCallback(calc_zahl());
          last_weiche = calc_zahl();
          change_weiche = false;
        }

        reset_zahl();
        return;
      default:
        change_id = false;
        reset_zahl();
    }
  }
}

void SerialConfiguration::printConfiguration() {
  //                   =======================================
  printLineln(CONF, F("=== CAN-Konfiguration ================="));

  printLine(CONF, F("SW-Version  => "));
  Serial.println(can_configuration.config.version);

  printLine(CONF, F("Modul Id    => "));
  Serial.println(can_configuration.config.modulId);

  printLine(CONF, F("DCC-Adresse => "));
  Serial.println(dcc.getAddr());

  printLine(CONF, F("Erste CAN ID Weiche => "));
  Serial.println(can_configuration.config.firstIdWeiche);

  printLine(CONF, F("Erste CAN ID Signal => "));
  Serial.println(can_configuration.config.firstIdSignal);
  
  printLineln(CONF, F("======================================="));
}
