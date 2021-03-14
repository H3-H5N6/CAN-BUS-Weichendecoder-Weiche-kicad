#include <Arduino.h>

#include "OutputControl.h"
#include "CanControl.h"

uint8_t LED_1 = 5;
uint8_t LED_2 = 6;

ACTOR actor_1;
ACTOR actor_2;
ACTOR actor_3;

OutputControl c_1 = OutputControl(&actor_1);
OutputControl c_2 = OutputControl(&actor_2);
OutputControl c_3 = OutputControl(&actor_3);

#include <ACAN2515.h>
#include <SPI.h>

static const byte MCP2515_CS = 10;  // CS input of MCP2515
static const byte MCP2515_INT = 3;  // INT output of MCP2515

static ACAN2515 can(MCP2515_CS, SPI, MCP2515_INT);

static const uint32_t QUARTZ_FREQUENCY = 16UL * 1000UL * 1000UL;  // 16 MHz


void init_can() {
  SPI.begin();
  ACAN2515Settings settings(QUARTZ_FREQUENCY, 125UL * 1000UL);  // CAN bit rate 125 kb/s
  settings.mRequestedMode = ACAN2515Settings::LoopBackMode;     // Select loopback mode
  const uint16_t errorCode = can.begin(settings, [] { can.isr(); });
  if (errorCode == 0) {
    Serial.print("Bit Rate prescaler: ");
    Serial.println(settings.mBitRatePrescaler);
    Serial.print("Propagation Segment: ");
    Serial.println(settings.mPropagationSegment);
    Serial.print("Phase segment 1: ");
    Serial.println(settings.mPhaseSegment1);
    Serial.print("Phase segment 2: ");
    Serial.println(settings.mPhaseSegment2);
    Serial.print("SJW: ");
    Serial.println(settings.mSJW);
    Serial.print("Triple Sampling: ");
    Serial.println(settings.mTripleSampling ? "yes" : "no");
    Serial.print("Actual bit rate: ");
    Serial.print(settings.actualBitRate());
    Serial.println(" bit/s");
    Serial.print("Exact bit rate ? ");
    Serial.println(settings.exactBitRate() ? "yes" : "no");
    Serial.print("Sample point: ");
    Serial.print(settings.samplePointFromBitStart());
    Serial.println("%");
  } else {
    Serial.print("Configuration error 0x");
    Serial.println(errorCode, HEX);
  }
}


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
  frame.id = id;
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

  if (can.available()) {
    can.receive(frame);
    gReceivedFrameCount++;
    Serial.print("Received: ");
    Serial.print(gReceivedFrameCount);
    Serial.print(" id: [");
    Serial.print(frame.id);
    Serial.println("]");
      
    if (frame.id == 100) {
      Serial.println("Impule");
      c_2.impulse();
    } else {
      Serial.println("Skip");
    }
  }

  myDelayAndProcess(10000);
}
