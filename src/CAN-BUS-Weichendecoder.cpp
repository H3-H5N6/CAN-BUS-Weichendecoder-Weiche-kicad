#include <Arduino.h>

#include "CanControl.h"
#include "OutputControl.h"

uint8_t LED_1 = 5;
uint8_t LED_2 = 6;

ACTOR actor_1;
ACTOR actor_2;
ACTOR actor_3;

OutputControl c_1 = OutputControl(&actor_1);
OutputControl c_2 = OutputControl(&actor_2);
OutputControl c_3 = OutputControl(&actor_3);

void init_led() {
  Serial.println("Beginn");

  c_1.init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, 1000, LED_1);
  c_2.init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, 1000, LED_2);
  c_3.init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::high, 1000, 13);

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
        Serial.println("Impule 1");
        c_1.impulse();
        break;
      case 50:
        Serial.println("Impule 2");
        c_2.impulse();
        break;
      case 51:
        Serial.println("Impule 3");
        c_3.impulse();
        break;
      default:
        Serial.println("Skip");
    }
  }
  myDelayAndProcess(100);
}
