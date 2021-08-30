#include <Arduino.h>

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
  OUTPUT_CONTROL::ACTIVE_MODE::low, 
  IMPULSE_LENGTH , 
  IMPULSE_LENGTH 
};

CANMessage frame;

uint16_t send_mode = 0;

OutputControl* control = (OutputControl*)malloc(sizeof(OutputControl) * 10);
Weiche* weiche = (Weiche*)malloc(sizeof(Weiche) * 5);

void initWeiche() {
  Serial.println(F("Init Weiche Beginn"));

  control[0] = OutputControl(&configuration, 701, LED_1);
  control[1] = OutputControl(&configuration, 702, LED_2);
  control[2] = OutputControl(&configuration, 703, LED_3);
  control[3] = OutputControl(&configuration, 704, LED_4);
  control[4] = OutputControl(&configuration, 705, LED_5);
  control[5] = OutputControl(&configuration, 706, LED_6);
  control[6] = OutputControl(&configuration, 707, LED_7);
  control[7] = OutputControl(&configuration, 708, LED_8);
  control[8] = OutputControl(&configuration, 709, LED_9);
  control[9] = OutputControl(&configuration, 710, LED_10);

  weiche[0] = Weiche(control[0], control[1]);
  weiche[1] = Weiche(control[2], control[3]);
  weiche[2] = Weiche(control[4], control[5]);
  weiche[3] = Weiche(control[6], control[7]);
  weiche[4] = Weiche(control[8], control[9]);
  Serial.println(F("Init Weiche End"));
}

void setup() {
  Serial.begin(115200);

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


void change(uint16_t address){
  for (byte i = 0; i < 5; i++){
    weiche[i].change(address);
  }
}

void loop() {
  Serial.print(F("."));
  if (can.receive(frame)) {
    debugFrame(&frame);

    Serial.print("16: ");  
    Serial.println(frame.data16[0]);


    if (frame.data16[0] == 999){
      Serial.println();
      Serial.print("Status: ");
      for (byte i = 0; i < 5; i++){
        Serial.print(weiche[i].statusAsAddress());
        Serial.print(" ");
      }
      Serial.println();
      send_mode = 1;
    } else {
      for (byte i = 0; i < 4; i++){
        uint16_t adr = frame.data16[i];
        Serial.print(adr);
        Serial.print(" ");
        if (adr != 0 ) {
          change(adr);
        }
      }
      Serial.println();
    }
  }


  if (send_mode == 1) {
    frame.id = 200;

    frame.ext = false;
    frame.rtr = false;
    frame.len = 8;

    frame.data16[0] = weiche[0].statusAsAddress();
    frame.data16[1] = weiche[1].statusAsAddress();
    frame.data16[2] = weiche[2].statusAsAddress();
    frame.data16[3] = weiche[3].statusAsAddress();

    bool ok = can.tryToSend(frame);
    if (ok) {
      Serial.print("Sent ok");
    } else {
      Serial.println("Send failure");
    }

    frame.data16[0] = weiche[4].statusAsAddress();
    frame.data16[1] = 0;
    frame.data16[2] = 0;
    frame.data16[3] = 0;

    ok = can.tryToSend(frame);
    if (ok) {
      Serial.print("Sent ok");
    } else {
      Serial.println("Send failure");
    }
    send_mode = 0;

  }

  processWeiche();

  delay(500);


}
