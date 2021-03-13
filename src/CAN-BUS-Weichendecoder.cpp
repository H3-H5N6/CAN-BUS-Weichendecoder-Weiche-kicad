#include <Arduino.h>
#include<SPI.h>

#include "OutputControl.h"

uint8_t LED_1 = 5;
uint8_t LED_2 = 6;


ACTOR led_1 = { OUTPUT_CONTROL::OUTPUT_MODE::FLASH, LOW, 2000, 0, HIGH, LED_1};
ACTOR led_2 = { OUTPUT_CONTROL::OUTPUT_MODE::FLASH, LOW, 3000, 0, HIGH, LED_2};


OutputControl c_1 = OutputControl(&led_1);
OutputControl c_2 = OutputControl(&led_2);

void init_led() {
  Serial.println("Beginn");
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  pinMode(LED_1, INPUT);
  pinMode(LED_2, INPUT_PULLUP);

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
 
  Serial.println("Ausgänge sind nun konfigiert. Warte 4s");
  delay(4000);

  Serial.println("Die 13 geht aus uns es geht nun in die Schleife");
  digitalWrite(13, LOW);
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, HIGH);

}



void setup() {

  Serial.begin(115200);
  // while (!Serial)
  //   ;
  // Serial.begin(115200);



  init_led();
}

void loop() {
  delay(500);
  c_1.pulse();
}
