#include <Arduino.h>

#include "OutputControl.h"

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

OutputControl* control = (OutputControl*)malloc(sizeof(OutputControl) * 10);

void init_led() {
  Serial.println("Beginn");

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
  Serial.println("Ausgänge sind nun konfigiert. Warte 2s");

  delay(2000);

  Serial.println("Es geht nun in die Schleife");
}

void setup() {
  Serial.begin(115200);
  init_led();
}

void processControl() {
  for (byte k = 0; k < 10; k++) {
      control[k].process();
  }
}

unsigned long lastChanged = millis();
byte index = 0;

void loop() {
  if ((lastChanged + IMPULSE_LENGTH * 4 ) < millis()){



    Serial.print("impulse: ");
    Serial.println(index);
    control[index].impulse();
    control[index+2].impulse();
    control[index+4].impulse();
    control[index+6].impulse();
    control[index+8].impulse();
    lastChanged = millis();

    if (index == 0){
      index = 1;
    } else {
      index = 0;
    }

  }
  Serial.print(". ");
  processControl();
  delay(500);


}
