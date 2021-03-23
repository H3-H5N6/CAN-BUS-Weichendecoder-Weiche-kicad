#ifndef CAN_CONTROL_H
#define CAN_CONTROL_H


#define ID_STATUS 400
#define ID_SET 200

#define MSB_IS_MODUL 0xFF

#define COMMAND_CONFIG 0x03

#define AKTOR_WEICHE 0x01
#define AKTOR_HP 0x02
#define AKTOR_VERSION 0x80

#define INDEX_COMMAND 0x00
#define INDEX_MSB 0x01
#define INDEX_LSB 0x02
#define INDEX_AKTOR 0x03
#define INDEX_DATA0 0x04
#define INDEX_DATA1 0x05
#define INDEX_DATA2 0x06
#define INDEX_DATA3 0x07

#include <ACAN2515.h>
#include <SPI.h>

static const byte MCP2515_CS = 10;  // CS input of MCP2515
static const byte MCP2515_INT = 3;  // INT output of MCP2515

static ACAN2515 can(MCP2515_CS, SPI, MCP2515_INT);

static const uint32_t QUARTZ_FREQUENCY = 16UL * 1000UL * 1000UL;  // 16 MHz

void init_can() {
  SPI.begin();
  ACAN2515Settings settings(QUARTZ_FREQUENCY, 125UL * 1000UL);  // CAN bit rate 125 kb/s
  settings.mRequestedMode = ACAN2515Settings::NormalMode;     // Select loopback mode
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

#endif