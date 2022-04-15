#include <Arduino.h>
#include <EEPROM.h>
#include "Dcc.h"
#include "ConfigPin.h"

ConfigPin configPin;

#include "CanConfiguration.h"

#define VERSION 4
#define DEFAULT_MODUL_ID 1
#define START_WEICHEN_ID 801

CAN_CONFIGURATION can_configuration;

#include "CanControl.h"
#include "Weiche.h"

#include "I2C_Tools.h"



I2C_Tools i2c;


#define IMPULSE_LENGTH 2000

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

CANMessage frame;

uint16_t send_mode = 0;

OutputControl* control = (OutputControl*)malloc(sizeof(OutputControl) * 10);
Weiche* weiche = (Weiche*)malloc(sizeof(Weiche) * 5);

#include "SerialConfiguration.h"

SerialConfiguration serialConfiguration;

int inputVal = 0;

void change(uint16_t address) {
  for (byte i = 0; i < 5; i++) {
    boolean changed = weiche[i].change(address);
    if (changed) {
      Serial.print(F("DEBUG: Address ["));
      Serial.print(address);
      Serial.println(F("] found"));
    }
  }
}


void free_dump() {

      uint8_t *heapptr;
      uint8_t *stackptr;

      stackptr = (uint8_t *)malloc(4);   // use stackptr temporarily
      heapptr = stackptr;                // save value of heap pointer
      free(stackptr);                    // free up the memory again (sets stackptr to 0)
      stackptr =  (uint8_t *)(SP);       // save value of stack pointer


      // print("HP: ");
      Serial.println("Speicher");
      Serial.print(F("HP: "));
      Serial.println((int) heapptr);

      // print("SP: ");
      Serial.print(F("SP: "));
      Serial.println((int) stackptr);

      // print("Free: ");
      Serial.print(F("Free: "));
      Serial.println((int) stackptr - (int) heapptr);
      Serial.println();
}

void initDccConfiguraion(byte configPin, byte canModulId) {

  Serial.print (F("DCC-Address: ["));
  uint16_t dccAddr = Dcc.getCV(CV_ACCESSORY_DECODER_ADDRESS_LSB) + (8 * Dcc.getCV(CV_ACCESSORY_DECODER_ADDRESS_MSB));
  Serial.print(dccAddr);
  Serial.println(F("]"));

  Serial.print (F("Config Pin: ["));
  Serial.print(configPin);
  Serial.println(F("]"));


  if (configPin == 1 ) {
    uint16_t newDccAddr = ( (canModulId -1 ) * 5) + 1;

    Serial.print (F("Neue DCC-Addresse: ["));
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
    Serial.print(START_WEICHEN_ID + (10 * (DEFAULT_MODUL_ID-1 )));
    Serial.println(F("]"));

    can_configuration.config.id = DEFAULT_MODUL_ID;
    for (int n = 0; n < 10; n++) {
      can_configuration.config.id_weichen[n] = START_WEICHEN_ID + (10 * (DEFAULT_MODUL_ID-1 )) + n;
    }
  }

  if (can_configuration.config.version != VERSION) {
    Serial.print(F("Setze neue Version: ["));
    Serial.print(VERSION);
    Serial.println(F("]"));
    can_configuration.config.version = VERSION;
    writeConfigToEEPROM = true;
  }

  if (writeConfigToEEPROM){
    Serial.print(F("Schreibe initiale Konfig ..."));
    EEPROM.put(CAN_BUS_OFFSET, can_configuration);
    Serial.print(F(". fertig"));
  }

  serialConfiguration.init(can_configuration, *change);
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
  

  byte value = configPin.readCongigPin();
  Serial.print(F("Wert ConfigPin: ["));
  Serial.print(value);
  Serial.println(F("]"));

  initCanConfiguraion(value);

  serialConfiguration.printConfiguration();

  initWeiche();

  
  free_dump();
  init_can();
    free_dump();
  


  init_DCC();
  initDccConfiguraion(value, can_configuration.config.id);

  Serial.println(F("> init i2c ..."));
  i2c.init_i2c();
  Serial.println(F("= done"));

  Serial.println(F("> scan i2c ..."));
  i2c.scan_i2c();
  Serial.println(F("= done"));

  i2c.init_pcf8574();
}

void processWeiche() {
  for (byte k = 0; k < 5; k++) {
    weiche[k].process();
  }
}

unsigned long lastChanged = millis();
byte index = 0;



void sendDetailWeichenStatus() {
  frame.id = 300;

  frame.ext = false;
  frame.rtr = false;
  frame.len = 8;

  uint16_t data[8];

  for (byte i = 0; i < 5; i++) {
    weiche[i].statusForCan(data);
    Serial.print("Frame ID: ");
    Serial.print(frame.id);
    Serial.print(" Data: ");
    for (byte z = 0; z < 8; z++) {
      Serial.print(data[z]);
      Serial.print(" ");
    }
    Serial.println("");

    for (byte n = 0; n < 2; n++) {
      for (byte k = 0; k < 4; k++) {
        frame.data16[k] = data[n * 4 + k];
      }
      bool ok = can.tryToSend(frame);
      if (ok) {
        Serial.print("Sent ok");
      } else {
        Serial.println("Send failure");
      }
      // frame.id = frame.id + 1;
    }
  }
}

void processCanMessageGetStatus(CANMessage& frame) {
  if (frame.data16[0] == can_configuration.config.id) {
    Serial.println();
    Serial.print("Status: ");
    for (byte i = 0; i < 5; i++) {
      Serial.print(weiche[i].statusAsAddress());
      Serial.print(" ");
    }
    Serial.println();
    send_mode = 1;
  }
}

void processCanMessageChangeState(CANMessage& frame) {
  for (byte i = 0; i < 4; i++) {
    uint16_t adr = frame.data16[i];
    if (adr != 0) {
      change(adr);
    }
  }
  Serial.println();
}

void processCanMessage(CANMessage& frame) {
  if (can.receive(frame)) {
    debugFrame(frame);

    switch (frame.id) {
      case 100:
        processCanMessageChangeState(frame);
        break;
      case 200:
        processCanMessageGetStatus(frame);
        break;
    }
  }

  if (send_mode == 1) {
    Serial.println("sendDetailWeichenStatus");
    sendDetailWeichenStatus();
    send_mode = 0;
  }
}

#ifdef NOTIFY_DCC_MSG
void notifyDccMsg(DCC_MSG* Msg) {
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

  processCanMessage(frame);

  processWeiche();

  
  Dcc.process();

  dccWriteFactotyDefaults();

  for (byte i=0 ; i < 10; i++) {
    if (can_addr_buffer[i][1] != 0) {
      Serial.println("call Change");
      change(can_addr_buffer[i][1]);
      can_addr_buffer[i][1] = 0;
    }
  }

  delay(5);
}
