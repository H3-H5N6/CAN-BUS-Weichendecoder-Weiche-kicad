#include <Arduino.h>
#include <EEPROM.h>

#include "Debug.h"

#include "ConfigPin.h"
#include "Dcc.h"

#include "I2C_Tools.h"
#include "Weiche.h"
#include "Signal.h"
#include "SerialConfiguration.h"
#include "CanConfiguration.h"
#include "CanCommunicator.h"

void change(uint16_t address);

#define VERSION 4
#define DEFAULT_MODUL_ID 1
#define START_WEICHEN_ID 801

#define IMPULSE_LENGTH 2000

ConfigPin configPin;
CAN_CONFIGURATION can_configuration;
I2C_Tools i2c;

uint8_t LED_1 = 4;
uint8_t LED_2 = 5;
uint8_t LED_3 = 6;
uint8_t LED_4 = 7;
uint8_t LED_5 = 8;
uint8_t LED_6 = 9;
uint8_t LED_7 = A1;
uint8_t LED_8 = A0;
uint8_t LED_9 = A2;
uint8_t LED_10 = A3;

OUTPUT_CONF configuration = {
    OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE,
    OUTPUT_CONTROL::ACTIVE_MODE::high,
    IMPULSE_LENGTH,
    IMPULSE_LENGTH};

OutputControl *control = (OutputControl *)malloc(sizeof(OutputControl) * 10);
Weiche *weiche = (Weiche *)malloc(sizeof(Weiche) * 5);
Signal *signal = (Signal *)malloc(sizeof(Signal) * 6);
SerialConfiguration serialConfiguration;
CanComm canComm = CanComm(can_configuration, weiche, signal, *change );

int inputVal = 0;

void change(uint16_t address) {
  for (byte i = 0; i < 5; i++) {
    boolean changed = weiche[i].change(address);
    if (changed) {
      Serial.print(F("DEBUG: Address Weiche["));
      Serial.print(address);
      Serial.println(F("] found"));
    }
  }
  for (byte i = 0; i < 6; i++) {
    boolean changed = signal[i].change(address);
    if (changed) {
      Serial.print(F("DEBUG: Address Signal ["));
      Serial.print(address);
      Serial.println(F("] found"));
    }
  }
}


void initDccConfiguraion(byte configPin, byte canModulId) {
  Serial.print(F("DCC-Address: ["));
  uint16_t dccAddr = Dcc.getCV(CV_ACCESSORY_DECODER_ADDRESS_LSB) + (8 * Dcc.getCV(CV_ACCESSORY_DECODER_ADDRESS_MSB));
  Serial.print(dccAddr);
  Serial.println(F("]"));

  Serial.print(F("Config Pin: ["));
  Serial.print(configPin);
  Serial.println(F("]"));

  if (configPin == 1) {
    uint16_t newDccAddr = ((canModulId - 1) * 5) + 1;

    Serial.print(F("Neue DCC-Addresse: ["));
    Serial.print(newDccAddr);
    Serial.println(F("]"));

    Dcc.setCV(CV_ACCESSORY_DECODER_ADDRESS_LSB, newDccAddr & 0xFF);
    Dcc.setCV(CV_ACCESSORY_DECODER_ADDRESS_MSB, newDccAddr >> 8);
  }
}

void initCanConfiguraion(byte configPin) {
  EEPROM.get(CAN_BUS_OFFSET, can_configuration.data);

  boolean writeConfigToEEPROM = false;

  // Modul ID und CAN-Bus-Adresse initialisieren
  if (configPin == 3 || can_configuration.config.version == 0) {
    Serial.print(F("Setze Mudul ID: ["));
    Serial.print(DEFAULT_MODUL_ID);
    Serial.println(F("]"));

    Serial.print(F("Setze CAN Adresse: ["));
    Serial.print(START_WEICHEN_ID + (10 * (DEFAULT_MODUL_ID - 1)));
    Serial.println(F("]"));

    can_configuration.config.id = DEFAULT_MODUL_ID;
    for (int n = 0; n < 10; n++) {
      can_configuration.config.id_weichen[n] = START_WEICHEN_ID + (10 * (DEFAULT_MODUL_ID - 1)) + n;
    }
  }

  if (can_configuration.config.version != VERSION) {
    Serial.print(F("Setze neue Version: ["));
    Serial.print(VERSION);
    Serial.println(F("]"));
    can_configuration.config.version = VERSION;
    writeConfigToEEPROM = true;
  }

  if (writeConfigToEEPROM) {
    Serial.print(F("Schreibe initiale Konfig ..."));
    EEPROM.put(CAN_BUS_OFFSET, can_configuration);
    Serial.print(F(". fertig"));
  }

  serialConfiguration.init(can_configuration, Dcc, *change);
}

void initSignal() {
  I2CSignal i2csignal;
  i2csignal.init_pcf8574();

  for (uint8_t i = 0; i < 5; i++) {
    signal[i] = Signal(900 + (i * 4), i, &i2csignal, SIGNAL::SOCKET::PIN);
  }
  for (uint8_t i = 5; i < 6; i++) {
    signal[i] = Signal(900 + (i * 4), i, &i2csignal, SIGNAL::SOCKET::RJ12);
  }
}

void initWeiche() {
  Serial.println(F("Init Weiche Beginn"));

  control[0] = OutputControl(&configuration, can_configuration.config.id_weichen[1], LED_1);
  control[1] = OutputControl(&configuration, can_configuration.config.id_weichen[0], LED_2);
  control[2] = OutputControl(&configuration, can_configuration.config.id_weichen[3], LED_3);
  control[3] = OutputControl(&configuration, can_configuration.config.id_weichen[2], LED_4);
  control[4] = OutputControl(&configuration, can_configuration.config.id_weichen[5], LED_5);
  control[5] = OutputControl(&configuration, can_configuration.config.id_weichen[4], LED_6);
  control[6] = OutputControl(&configuration, can_configuration.config.id_weichen[7], LED_7);
  control[7] = OutputControl(&configuration, can_configuration.config.id_weichen[6], LED_8);
  control[8] = OutputControl(&configuration, can_configuration.config.id_weichen[9], LED_9);
  control[9] = OutputControl(&configuration, can_configuration.config.id_weichen[8], LED_10);

  weiche[0] = Weiche(control[0], control[1]);
  weiche[1] = Weiche(control[2], control[3]);
  weiche[2] = Weiche(control[4], control[5]);
  weiche[3] = Weiche(control[6], control[7]);
  weiche[4] = Weiche(control[8], control[9]);
  Serial.println(F("Init Weiche End"));
}

void setup() {
  Serial.begin(115200);

  free_dump();

  // Serial.println(F("=== 1 ==="));
  // delay(1000);

  byte value = configPin.readCongigPin();
  Serial.print(F("Wert ConfigPin: ["));
  Serial.print(value);
  Serial.println(F("]"));

  Serial.println(F("> init i2c ..."));
  i2c.init_i2c();
  Serial.println(F("= done"));

  Serial.println(F("> scan i2c ..."));
  i2c.scan_i2c();
  Serial.println(F("= done"));

  // Serial.println(F("=== 2 ==="));
  // delay(1000);

  initCanConfiguraion(value);

  serialConfiguration.printConfiguration();

  Serial.println(F("=== 3 ==="));
  // delay(1000);

  initWeiche();

  // Serial.println(F("=== 4 ==="));
  // delay(1000);
  initSignal();


  free_dump();

  canComm.init();

  delay(1000);
  free_dump();

  init_DCC();
  initDccConfiguraion(value, can_configuration.config.id);
}

void processWeiche() {
  for (byte k = 0; k < 5; k++) {
    weiche[k].process();
  }
}

void processSignal() {
  for (byte k = 0; k < 6; k++) {
    signal[k].process();
  }
}

unsigned long lastChanged = millis();
byte index = 0;



#ifdef NOTIFY_DCC_MSG
void notifyDccMsg(DCC_MSG *Msg) {
  Serial.print("notifyDccMsg: ");
  for (uint8_t i = 0; i < Msg->Size; i++) {
    Serial.print(Msg->Data[i], HEX);
    Serial.write(' ');
  }
  Serial.println();
}
#endif

void loop() {
  serialConfiguration.process();

  canComm.processCanMessage();

  processWeiche();
  processSignal();

  Dcc.process();

  dccWriteFactotyDefaults();

  for (byte i = 0; i < 10; i++) {
    if (can_addr_buffer[i][1] != 0) {
      Serial.println("call Change");
      change(can_addr_buffer[i][1]);
      can_addr_buffer[i][1] = 0;
    }
  }

  delay(5);
}
