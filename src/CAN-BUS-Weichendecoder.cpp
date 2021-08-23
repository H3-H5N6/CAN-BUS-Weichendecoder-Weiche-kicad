#include <Arduino.h>

#include "OutputControl.h"
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

OutputControl* control = (OutputControl*)malloc(sizeof(OutputControl) * 10);

Weiche* weiche = (Weiche*)malloc(sizeof(Weiche) * 5);

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

  weiche[0] = Weiche(control[0], control[1]);
  weiche[1] = Weiche(control[2], control[3]);
  weiche[2] = Weiche(control[4], control[5]);
  weiche[3] = Weiche(control[6], control[7]);
  weiche[4] = Weiche(control[8], control[9]);


  delay(2000);

  Serial.println("Es geht nun in die Schleife");
}

void setup() {
  Serial.begin(115200);
  init_led();
}

void processControl() {
  for (byte k = 0; k < 5; k++) {
      weiche[k].process();
  }

  Serial.print("Weichen: ");
  for (byte k = 0; k < 5; k++) {
      Serial.print("[");
      Serial.print(weiche[k].status());
      Serial.print("]");
    }
    Serial.println();

}

unsigned long lastChanged = millis();
byte index = 0;

void loop() {
  if ((lastChanged + IMPULSE_LENGTH * 4 ) < millis()){
    Serial.print("impulse: ");
    Serial.println(index);
    lastChanged = millis();

    if (index == 0){
      Serial.println("Abzweig");
      WEICHE::POSITION p0 = weiche[0].abzweig();
      Serial.print("Position: ");
      Serial.println(p0);
      weiche[1].abzweig();
      weiche[2].abzweig();
      weiche[3].abzweig();
      weiche[4].abzweig();
      index = 1;
    } else {
      Serial.println("Gerade");
      weiche[0].gerade();
      weiche[1].gerade();
      weiche[2].gerade();
      weiche[3].gerade();
      weiche[4].gerade();
      index = 0;
    }

  }
  Serial.print(". ");
  processControl();
  delay(500);


}
