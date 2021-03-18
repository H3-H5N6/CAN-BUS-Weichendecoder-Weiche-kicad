#include <Arduino.h>

#include "CanControl.h"
#include "OutputControl.h"
#include "Weiche.h"

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

ACTOR actor[10];

OutputControl* control = (OutputControl*)malloc(sizeof(OutputControl) * 10); 
Weiche* weiche = (Weiche*)malloc(sizeof(Weiche) * 5); 

void init_led() {
  Serial.println("Beginn");

  for (byte j = 0; j < 10; j++) {
    control[j] = OutputControl(&actor[j]);
  }

  control[0].init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, 1000, LED_1);
  control[1].init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, 1000, LED_2);
  control[2].init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, 1000, LED_3);
  control[3].init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, 1000, LED_4);
  control[4].init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, 1000, LED_5);
  control[5].init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, 1000, LED_6);
  control[6].init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, 1000, LED_7);
  control[7].init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, 1000, LED_8);
  control[8].init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, 1000, LED_9);
  control[9].init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, 1000, LED_10);

  weiche[0] = Weiche(control[0],control[1]);
  weiche[1] = Weiche(control[2],control[3]);
  weiche[2] = Weiche(control[4],control[5]);
  weiche[3] = Weiche(control[6],control[7]);


  Serial.println("Ausgänge sind nun konfigiert. Warte 4s");

  delay(4000);

  Serial.println("Es geht nun in die Schleife");
}

void setup() {
  Serial.begin(115200);
  // while (!Serial)
  //   ;
  // Serial.begin(115200);

  init_can();

  init_led();
}

void myDelayAndProcess(unsigned long duration) {
  unsigned long count = duration / 100;

  for (unsigned long i = 0; i < count; i++) {
    delay(500);
    for (byte k = 0; k < 10; k++) {
      control[k].process();
    }
    boolean isImpulePosible = control[0].isImpulePosible();
    Serial.print("Ready: [");
    Serial.print(isImpulePosible);
    Serial.println("]");
  }
}

void loop() {
  CANMessage frame;
  /*frame.id = id;
  id++;
  if (id > 103) {
    id = 100;
  }

  frame.ext = false;
  frame.rtr = false;
  frame.len = 8;

  frame.data[0] = 0;
  frame.data[1] = 0;
  frame.data[2] = 0;
  frame.data[3] = 0;
  frame.data[4] = 0;
  frame.data[5] = 0;
  frame.data[6] = 0;
  frame.data[7] = 0;

  const bool ok = can.tryToSend(frame);
  if (ok) {
    gSentFrameCount += 1;
    Serial.print("Sent: ");
    Serial.println(gSentFrameCount);
  } else {
    Serial.println("Send failure");
  }

  myDelayAndProcess(500);
  */
  if (can.available()) {
    can.receive(frame);
    Serial.print("Received: ");
    Serial.print(" id: [");
    Serial.print(frame.id);
    Serial.println("]");

    switch (frame.data[0]) {
      case 49:
        Serial.println("Weichen gerade");
        weiche[0].gerade();
        weiche[1].gerade();
        weiche[2].gerade();
        weiche[3].gerade();


        break;
      case 50:
        Serial.println("Weiche abzweig");
        
        weiche[0].abzweig();
        weiche[1].abzweig();
        weiche[2].abzweig();
        weiche[3].abzweig();
        
        break;
      case 51:
        Serial.println("Flash 10 off");
        control[9].offFlash(); 
        break;
      default:
        Serial.println("Skip");
    }
  }
  myDelayAndProcess(100);
}
