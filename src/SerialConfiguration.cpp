#include "SerialConfiguration.h"

#include <Arduino.h>
#include <EEPROM.h>

#define HELP 1
#define CONF 2

SerialConfiguration::SerialConfiguration(ChangeWeiche _changeWeiche, ChangeSignal _changeSignal) {
  changeWeicheCallback = _changeWeiche;
  changeSignalCallback = _changeSignal;
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

void SerialConfiguration::init(CAN_CONFIGURATION &_conf, NmraDcc &_dcc) {
  can_configuration = _conf;
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
        last_signal = 0;
        reset_zahl();
        Serial.print(F("Output: "));
        return;
      case 's':
        change_signal = true;
        last_weiche = 0;
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
        printLineln(HELP, F("w           : Stelle Weiche"));
        printLineln(HELP, F("s           : Stelle Signal"));
        printLineln(HELP, F("i <MODUL_ID>: Neue Modul Id setzen"));
        printLineln(HELP, F("q           : Abbruch der Eingabe"));
        printLineln(HELP, F("h           : Diese Hilfe"));
        return;
      case '+':
        if (last_weiche > 0) {
          last_weiche = last_weiche + 2;
        }
        if (last_signal > 0) {
          last_signal = last_signal + 2;
        }
      case '-':
        if (last_weiche > 1) {
          last_weiche--;
        }
        if (last_signal > 1) {
          last_signal--;
        }
        if (last_weiche > 0) {
          Serial.print(F("Stelle Weiche: "));
          Serial.println(last_weiche);
          changeWeicheCallback(last_weiche);
        }
        if (last_signal > 0) {
          Serial.print(F("Stelle Signal: "));
          Serial.println(last_signal);
          changeSignalCallback(last_signal);
        }
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
        if (!change_id && !change_weiche && !change_signal) {
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

        if (change_signal) {
          Serial.print(F("Stelle Signal: "));
          Serial.println(calc_zahl());
          changeSignalCallback(calc_zahl());
          last_signal = calc_zahl();
          change_signal = false;
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
