#include <Arduino.h>

#include "CanControl.h"
#include "I2C_Expander.h"
#include "I2C_Tools.h"
#include "OutputControl.h"
#include "PCF8574.h"
#include "Signal_i2c.h"
#include "Weiche.h"

I2C_Expander i2c_expander;

Signal_i2c signal[] = {Signal_i2c(1,0), Signal_i2c(2,5), Signal_i2c(3,10)};

#define IMPULSE_LENGTH 4000

#define VERSION_MAJOR 1
#define VERSION_MINOR 3

byte modul_nr = 0x0C;

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

  control[0].init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, IMPULSE_LENGTH, LED_1);
  control[1].init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, IMPULSE_LENGTH, LED_2);
  control[2].init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, IMPULSE_LENGTH, LED_3);
  control[3].init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, IMPULSE_LENGTH, LED_4);
  control[4].init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, IMPULSE_LENGTH, LED_5);
  control[5].init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, IMPULSE_LENGTH, LED_6);
  control[6].init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, IMPULSE_LENGTH, LED_7);
  control[7].init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, IMPULSE_LENGTH, LED_8);
  control[8].init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, IMPULSE_LENGTH, LED_9);
  control[9].init(OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE, OUTPUT_CONTROL::ACTIVE_MODE::low, IMPULSE_LENGTH, LED_10);

  weiche[0] = Weiche(control[0], control[1]);
  weiche[1] = Weiche(control[2], control[3]);
  weiche[2] = Weiche(control[4], control[5]);
  weiche[3] = Weiche(control[6], control[7]);

  Serial.println("Ausgänge sind nun konfigiert. Warte 4s");

  delay(4000);

  Serial.println("Es geht nun in die Schleife");
}

void setup() {
  Serial.begin(115200);
  // while (!Serial)
  //   ;
  // Serial.begin(115200);
  Serial.println("Start");

  Wire.begin();
  scan_i2c();

  i2c_expander.init();

  //i2c_expander.checkAll();

  Serial.print("Before");
  Serial.println(signal[0].get());

  signal[0].set(SIGNAL::HP0);

  Serial.print("After");
  Serial.println(signal[0].get());  
  i2c_expander.setSignal(signal[0]);
  delay(2000);

  signal[0].set(SIGNAL::HP0_SH1);
  i2c_expander.setSignal(signal[0]);
  delay(2000);

  signal[0].set(SIGNAL::HP1);
  i2c_expander.setSignal(signal[0]);
  delay(2000);

  signal[0].set(SIGNAL::HP2);
  i2c_expander.setSignal(signal[0]);
  delay(2000);


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
    Serial.print("Weichen: ");
    for (byte k = 0; k < 4; k++) {
      Serial.print("[");
      Serial.print(weiche[k].status());
      Serial.print("]");
    }
    Serial.println();
  }
}

void sendVersion() {
  CANMessage frame;
  frame.id = ID_STATUS;

  frame.ext = false;
  frame.rtr = false;
  frame.len = 8;

  frame.data[INDEX_COMMAND] = COMMAND_CONFIG;
  frame.data[INDEX_MSB] = MSB_IS_MODUL;
  frame.data[INDEX_LSB] = modul_nr;
  frame.data[INDEX_AKTOR] = AKTOR_VERSION;
  frame.data[INDEX_DATA0] = VERSION_MAJOR;
  frame.data[INDEX_DATA1] = VERSION_MINOR;
  frame.data[INDEX_DATA2] = 0;
  frame.data[INDEX_DATA3] = 0;

  boolean result = can.tryToSend(frame);
  if (result) {
    Serial.println("Send OK");
  } else {
    Serial.println("Send Failed");
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

  boolean changeIsPosible = true;

  if (can.available()) {
    can.receive(frame);
    Serial.print("Received: ");
    Serial.print(" id: [");
    Serial.print(frame.id);
    Serial.println("]");

    switch (frame.data[0]) {
      case 49:
        Serial.println("Weichen gerade");

        for (byte k = 0; k < 4; k++) {
          if (weiche[0].changeIsPosible()) {
            continue;
          }
          changeIsPosible = false;
        }

        if (changeIsPosible) {
          weiche[0].gerade();
          weiche[1].gerade();
          weiche[2].gerade();
          weiche[3].gerade();
        } else {
          Serial.println(">>>>> Ignore");
        }

        break;
      case 50:
        Serial.println("Weiche abzweig");

        weiche[0].abzweig();
        weiche[1].abzweig();
        weiche[2].abzweig();
        weiche[3].abzweig();

        break;
      case 52:
        // Serial.println("Flash 10 off");
        // control[9].offFlash();
        Serial.println("Version senden");
        sendVersion();
        break;
      default:
        Serial.println("Skip");
    }

    if (!changeIsPosible) {
    }
  }
  myDelayAndProcess(100);
}
