#include <Arduino.h>

#include <EEPROM.h>

#define VERSION 1
#define DEFAULT_MODUL_ID 2
#define DEFAULT_WEICHEN_ID 811

typedef struct {
	uint16_t version;
	uint16_t id;
	uint16_t id_weichen[10];
} CONFIGURATION;

typedef union {
	CONFIGURATION config;
	uint16_t data[12];
} CAN_CONFIGURATION;

CAN_CONFIGURATION can_configuration;

#include "CanControl.h"
#include "Weiche.h"

#define IMPULSE_LENGTH 1000

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


boolean change_id = false;
#define ZAHL_LENGTH 4

uint8_t  zahl [ZAHL_LENGTH];
uint8_t zahl_pos = 0;

void printConfiguration(){
  Serial.print(F("Version: ["));
  Serial.print(can_configuration.config.version);
  Serial.println("]");
  Serial.print("ID: [");
  Serial.print(can_configuration.config.id);
  Serial.println("]");
  for (int n = 0; n< 10; n++){
    Serial.print("CAN ID: [");
    Serial.print(n);
    Serial.print("] => ");
    Serial.println(can_configuration.config.id_weichen[n]);
  }
}


void initCanConfiguraion(){
  EEPROM.get(0, can_configuration.data);

  if (can_configuration.config.version != VERSION){
    can_configuration.config.version = VERSION;
    can_configuration.config.id = DEFAULT_MODUL_ID;
    for (int n = 0; n< 10; n++){
      can_configuration.config.id_weichen[n] = DEFAULT_WEICHEN_ID + n;
    }
    EEPROM.put(0,can_configuration);
  }  
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
  printConfiguration();

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
    weiche[i].change(address);
  }
}

/**
 * Sendet den Status der Weichen mit der id 200 und 201
 *
 */
void sendWeichenStatus() {
  frame.id = 200;

  frame.ext = false;
  frame.rtr = false;
  frame.len = 8;

  for (byte i = 0; i < 8; i++) {
    frame.data16[i % 4] = (i < 5) ? weiche[i].statusAsAddress() : 0;
    if (i % 4 == 3) {
      bool ok = can.tryToSend(frame);
      if (ok) {
        Serial.print("Sent ok");
      } else {
        Serial.println("Send failure");
      }
      frame.id = frame.id + 1;
    }
  }
}

void reset_zahl() {
  zahl_pos = 0;
  for (uint8_t i = 0; i < ZAHL_LENGTH ; i++){
    zahl[i] = 0;
  }
}

uint16_t calc_zahl(){
  uint16_t result = 0;
  uint16_t stelle = 1;

  for (uint8_t i = zahl_pos; i > 0 ; i--) {
    result = result + (zahl[i-1] * stelle);
    stelle = stelle * 10;

  }
  return result;

}

void loop() {

  if (Serial.available()){
    int input = Serial.read();
    

    switch (char(input)) {
      case 'p':
        change_id = false;
        reset_zahl();
        printConfiguration();
        break;
      case 'i':
        change_id = true;
        reset_zahl();
        Serial.print(F("Neue ID: "));
        break;
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
        Serial.print(char(input));
        if (zahl_pos > 3) {
          reset_zahl();
        }
        zahl[zahl_pos] = input-48;
        zahl_pos++;
        break;
      case '\r':
        break;
      case '\n':
      Serial.print(char(input));
        if (change_id) {
          Serial.print("Setze neue Id: ");
          Serial.println(calc_zahl());
          can_configuration.config.id = calc_zahl();
          EEPROM.put(0,can_configuration);
          change_id = false;
        }
        reset_zahl();
        break;
      default:
        change_id = false;
        reset_zahl();
    }
  }

  // Serial.print(F("."));
  if (can.receive(frame)) {
    debugFrame(&frame);

    Serial.print("16: ");
    Serial.println(frame.data16[0]);

    if (frame.data16[0] == can_configuration.config.id) {
      Serial.println();
      Serial.print("Status: ");
      for (byte i = 0; i < 5; i++) {
        Serial.print(weiche[i].statusAsAddress());
        Serial.print(" ");
      }
      Serial.println();
      send_mode = 1;
    } else {
      for (byte i = 0; i < 4; i++) {
        uint16_t adr = frame.data16[i];
        Serial.print(adr);
        Serial.print(" ");
        if (adr != 0) {
          change(adr);
        }
      }
      Serial.println();
    }
  }

  if (send_mode == 1) {
    sendWeichenStatus();
    send_mode = 0;
  }

  processWeiche();

  delay(5);
}
