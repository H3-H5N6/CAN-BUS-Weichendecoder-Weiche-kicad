#include <Arduino.h>
#include <EEPROM.h>

#include "CanCommunicator.h"
#include "CanConfiguration.h"
#include "ConfigPin.h"
#include "Dcc.h"
#include "Debug.h"
#include "I2C_Tools.h"
#include "SerialConfiguration.h"
#include "Signal.h"
#include "Weiche.h"

void change(uint16_t address);
void changeWeiche(uint16_t address);
void changeSignal(uint16_t address);



#define IMPULSE_LENGTH 2000

ConfigPin configPin;
CAN_CONFIGURATION can_configuration;
I2C_Tools i2c;

#define LED_1 4
#define LED_2 5
#define LED_3 6
#define LED_4 7
#define LED_5 8
#define LED_6 9
#define LED_7 A1
#define LED_8 A0
#define LED_9 A2
#define LED_10 A3

OUTPUT_CONF configuration = {
    OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE,
    OUTPUT_CONTROL::ACTIVE_MODE::high,
    IMPULSE_LENGTH,
    IMPULSE_LENGTH};

OutputControl *control = (OutputControl *)malloc(sizeof(OutputControl) * 10);
Weiche *weiche = (Weiche *)malloc(sizeof(Weiche) * 5);
Signal *signal = (Signal *)malloc(sizeof(Signal) * 6);
SerialConfiguration serialConfiguration;
CanComm canComm = CanComm(&can_configuration, weiche, signal, *change);


void changeWeiche(uint16_t address) {
  for (byte i = 0; i < 5; i++) {
    if (weiche[i].find(address)) {
      Serial.print(F("DEBUG Address Weiche["));
      Serial.print(address);
      Serial.println(F("] gefunden"));

      weiche[i].change(address);
    }
  }
}

void changeSignal(uint16_t address){
  for (byte i = 0; i < 6; i++) {
    if (signal[i].find(address)) {
      Serial.print(F("DEBUG: Address Signal ["));
      Serial.print(address);
      Serial.println(F("] found"));

      signal[i].change(address);
    }
  }
}


void change(uint16_t address) {
  changeWeiche(address);
  changeSignal(address);
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

void initSignal() {
  I2CSignal i2csignal;
  i2csignal.init_pcf8574();

  for (uint8_t i = 0; i < 5; i++) {
    signal[i] = Signal(can_configuration.config.firstIdSignal + (i * 4), i, &i2csignal, SIGNAL::SOCKET::PIN);
  }
  for (uint8_t i = 5; i < 6; i++) {
    signal[i] = Signal(can_configuration.config.firstIdSignal + (i * 4), i, &i2csignal, SIGNAL::SOCKET::RJ12);
  }
}

void initWeiche() {
  Serial.println(F("Init Weiche Beginn"));

  control[0] = OutputControl(&configuration, LED_1);
  control[1] = OutputControl(&configuration, LED_2);
  control[2] = OutputControl(&configuration, LED_3);
  control[3] = OutputControl(&configuration, LED_4);
  control[4] = OutputControl(&configuration, LED_5);
  control[5] = OutputControl(&configuration, LED_6);
  control[6] = OutputControl(&configuration, LED_7);
  control[7] = OutputControl(&configuration, LED_8);
  control[8] = OutputControl(&configuration, LED_9);
  control[9] = OutputControl(&configuration, LED_10);

  // uint8_t id =  can_configuration.config.id ;
  for (uint8_t i = 0; i < 5; i++) {
    weiche[i] = Weiche(control[i * 2], control[(i * 2) + 1], can_configuration.config.firstIdWeiche + i * 2, 41 + i);
  }
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

  canComm.initCanConfiguraion(value);

  serialConfiguration.init(can_configuration, Dcc, *changeWeiche, *changeSignal);

  serialConfiguration.printConfiguration();

  initWeiche();
  initSignal();

  free_dump();

  canComm.init();

  free_dump();

  init_DCC();
  initDccConfiguraion(value, can_configuration.config.modulId);
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

void processDccToCan() {
  for (byte i = 0; i < 10; i++) {
    if (can_addr_buffer[i][1] != 0) {
      Serial.println("call Change");
      change(can_addr_buffer[i][1]);
      can_addr_buffer[i][1] = 0;
    }
  }
}

void loop() {
  serialConfiguration.process();

  canComm.processCanMessage();

  processWeiche();
  processSignal();

  Dcc.process();

  dccWriteFactotyDefaults();

  processDccToCan();

  delay(5);
}
