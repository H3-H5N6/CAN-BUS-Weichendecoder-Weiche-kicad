#include "SerialConfiguration.h"

#include <Arduino.h>
#include <EEPROM.h>



SerialConfiguration::SerialConfiguration() {
}

void SerialConfiguration::init(CAN_CONFIGURATION &_conf, ChangeWeiche _cw ) {
  can_configuration = _conf;
  changeWeicheCallback = _cw;
}

void SerialConfiguration::setAndWriteNewId() {
  can_configuration.config.id = calc_zahl();
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
        Serial.println(F("Hilfe"));
        Serial.println(F("======================================="));
        Serial.println(F("p           : Ausgabe der Konfiguartion"));
        Serial.println(F("i <MODUL_ID>: Neue Modul Id setzen"));
        Serial.println(F("q           : Abbruch der Eingabe"));
        Serial.println(F("h           : Diese Hilfe"));
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
  Serial.println(F("==== CAN-Konfiguration ===="));
  //              CAN ID: [3] => 
  Serial.print(F("SW-Version  => "));
  Serial.println(can_configuration.config.version);
  Serial.print(F("Modul Id    => "));
  Serial.println(can_configuration.config.id);
  for (int n = 0; n < 10; n++) {
    Serial.print("CAN ID: [");
    Serial.print(n);
    Serial.print("] => ");
    Serial.println(can_configuration.config.id_weichen[n]);
  }
  Serial.println(F("==========================="));
}
