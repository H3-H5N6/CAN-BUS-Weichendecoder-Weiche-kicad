#include <Arduino.h>

#include "CanControl.h"
#include "OutputControl.h"

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


ACTOR actor_1;
ACTOR actor_2;
ACTOR actor_3;
ACTOR actor_4;
ACTOR actor_5;
ACTOR actor_6;
ACTOR actor_7;
ACTOR actor_8;
ACTOR actor_9;
ACTOR actor_10;

OutputControl c_1 = OutputControl(&actor_1);
OutputControl c_2 = OutputControl(&actor_2);
OutputControl c_3 = OutputControl(&actor_3);
OutputControl c_4 = OutputControl(&actor_4);
OutputControl c_5 = OutputControl(&actor_5);
OutputControl c_6 = OutputControl(&actor_6);
OutputControl c_7 = OutputControl(&actor_7);
OutputControl c_8 = OutputControl(&actor_8);
OutputControl c_9 = OutputControl(&actor_9);
OutputControl c_10 = OutputControl(&actor_10);


void init_led() {
  Serial.println("Beginn");

  c_1.init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, 1000, LED_1);
  c_2.init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, 1000, LED_2);
  c_3.init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, 1000, LED_3);
  c_4.init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, 1000, LED_4);
  c_5.init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, 1000, LED_5);
  c_6.init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, 1000, LED_6);
  c_7.init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, 1000, LED_7);
  c_8.init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, 1000, LED_8);
  c_9.init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, 1000, LED_9);
  c_10.init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, 1000, LED_10);

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
    delay(100);
    c_1.process();
    c_2.process();
    c_3.process();
    c_4.process();
    c_5.process();
    c_6.process();
    c_7.process();
    c_8.process();
    c_9.process();
    c_10.process();
  }
}

static uint32_t gReceivedFrameCount = 0;
static uint32_t gSentFrameCount = 0;

static uint32_t id = 100;

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
    gReceivedFrameCount++;
    Serial.print("Received: ");
    Serial.print(gReceivedFrameCount);
    Serial.print(" id: [");
    Serial.print(frame.id);
    Serial.println("]");

    switch (frame.data[0]) {
      case 49:
        Serial.println("Impule 1,3,5,7,9");
        c_1.impulse();
        c_3.impulse();
        c_5.impulse();
        c_7.impulse();
        c_9.impulse();
        break;
      case 50:
        Serial.println("Impule 2,4,6,8,10");
        c_2.impulse();
        c_4.impulse();
        c_6.impulse();
        c_8.impulse();
        c_10.impulse();

        break;
      case 51:
        Serial.println("Impule 3");
        c_3.on();
        Serial.println("on:");
        delay(1000);
        Serial.println("off:");
        c_3.off();
        break;
      default:
        Serial.println("Skip");
    }
  }
  myDelayAndProcess(100);
}
