#include <Arduino.h>
#include <EEPROM.h>

#include "CanConfiguration.h"

#define VERSION 2
#define DEFAULT_MODUL_ID 3
#define DEFAULT_WEICHEN_ID 821

CAN_CONFIGURATION can_configuration;

#include "CanControl.h"
#include "Weiche.h"

#define IMPULSE_LENGTH 2000

uint8_t LED_1 = 4;
uint8_t LED_2 = 5;
uint8_t LED_3 = 6;
uint8_t LED_4 = 7;
uint8_t LED_5 = 8;
uint8_t LED_6 = 9;
uint8_t LED_7 = A0;
uint8_t LED_8 = A1;
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

void initCanConfiguraion() {
  EEPROM.get(0, can_configuration.data);

  if (can_configuration.config.version != VERSION) {
    can_configuration.config.version = VERSION;
    can_configuration.config.id = DEFAULT_MODUL_ID;
    for (int n = 0; n < 10; n++) {
      can_configuration.config.id_weichen[n] = DEFAULT_WEICHEN_ID + n;
    }
    EEPROM.put(0, can_configuration);
  }
  serialConfiguration.init(can_configuration);
}

void initWeiche() {
  Serial.println(F("Init Weiche Beginn"));

  control[0] = OutputControl(&configuration, can_configuration.config.id_weichen[0], LED_1);
  control[1] = OutputControl(&configuration, can_configuration.config.id_weichen[1], LED_2);
  control[2] = OutputControl(&configuration, can_configuration.config.id_weichen[2], LED_3);
  control[3] = OutputControl(&configuration, can_configuration.config.id_weichen[3], LED_4);
  control[4] = OutputControl(&configuration, can_configuration.config.id_weichen[4], LED_5);
  control[5] = OutputControl(&configuration, can_configuration.config.id_weichen[5], LED_6);
  control[6] = OutputControl(&configuration, can_configuration.config.id_weichen[6], LED_7);
  control[7] = OutputControl(&configuration, can_configuration.config.id_weichen[7], LED_8);
  control[8] = OutputControl(&configuration, can_configuration.config.id_weichen[8], LED_9);
  control[9] = OutputControl(&configuration, can_configuration.config.id_weichen[9], LED_10);

  weiche[0] = Weiche(control[0], control[1]);
  weiche[1] = Weiche(control[2], control[3]);
  weiche[2] = Weiche(control[4], control[5]);
  weiche[3] = Weiche(control[6], control[7]);
  weiche[4] = Weiche(control[8], control[9]);
  Serial.println(F("Init Weiche End"));
}

void setup() {
  Serial.begin(115200);

  initCanConfiguraion();
  serialConfiguration.printConfiguration();

  initWeiche();

  init_can();




}

void processWeiche() {
  for (byte k = 0; k < 5; k++) {
    weiche[k].process();
  }
}

unsigned long lastChanged = millis();
byte index = 0;

void change(uint16_t address) {
  for (byte i = 0; i < 5; i++) {
    boolean changed = weiche[i].change(address);
    if (changed){
      Serial.print(F("DEBUG: Address ["));
      Serial.print(address);
      Serial.println(F("] found"));
    }
  }
}

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

void loop() {
  serialConfiguration.process();

  processCanMessage(frame);

  processWeiche();


  int val = analogRead(A6);
  
  if ( abs(inputVal - val)  > 50 ) {
    Serial.print("InputVal: ");
    Serial.println(val);
    inputVal = val;    
  } 
  
  
    delay(1000);



  delay(5);
}
