#include <Arduino.h>
#include <SPI.h>

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

  c_1.init(OUTPUT_CONTROL::OUTPUT_MODE::FLASH, OUTPUT_CONTROL::ACTIVE_MODE::low, 4000, LED_1);
  c_2.init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, 1000, LED_2);
  c_3.init(OUTPUT_CONTROL::OUTPUT_MODE::FLASH, OUTPUT_CONTROL::ACTIVE_MODE::high, 4000, 13);

  Serial.println("Ausgänge sind nun konfigiert. Warte 4s");

  delay(4000);

  Serial.println("Es geht nun in die Schleife");
}

void setup() {
  Serial.begin(115200);
  // while (!Serial)
  //   ;
  // Serial.begin(115200);

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

void loop() {
  myDelayAndProcess(500);
  c_2.impulse();
  myDelayAndProcess(10000);
}
