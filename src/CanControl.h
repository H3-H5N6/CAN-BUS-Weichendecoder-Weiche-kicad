#ifndef CAN_CONTROL_H
#define CAN_CONTROL_H

#include <ACAN2515.h>

static const byte MCP2515_CS = 10;  // CS input of MCP2515
static const byte MCP2515_INT = 3;  // INT output of MCP2515

static ACAN2515 can(MCP2515_CS, SPI, MCP2515_INT);

static const uint32_t QUARTZ_FREQUENCY = 16UL * 1000UL * 1000UL;  // 16 MHz

void init_can() {
  
  SPI.begin();
  ACAN2515Settings settings(QUARTZ_FREQUENCY, 125UL * 1000UL);
  settings.mRequestedMode = ACAN2515Settings::NormalMode;
  /** Buffer verkleinert, da wenig RAM verfügbar ist. Siehe auch 
   * https://github.com/pierremolinaro/acan2515/issues/2 */
  settings.mReceiveBufferSize = 4 ;
  settings.mTransmitBuffer0Size = 4 ;
  const uint16_t errorCode = can.begin(settings, [] { can.isr(); });
  if (errorCode == 0) {
    Serial.print(F("Bit Rate prescaler: "));
    Serial.println(settings.mBitRatePrescaler);
    Serial.print(F("Propagation Segment: "));
    Serial.println(settings.mPropagationSegment);
    Serial.print(F("Phase segment 1: "));
    Serial.println(settings.mPhaseSegment1);
    Serial.print(F("Phase segment 2: "));
    Serial.println(settings.mPhaseSegment2);
    Serial.print(F("SJW: "));
    Serial.println(settings.mSJW);
    Serial.print(F("Triple Sampling: "));
    Serial.println(settings.mTripleSampling ? "yes" : "no");
    Serial.print(F("Actual bit rate: "));
    Serial.print(settings.actualBitRate());
    Serial.println(F(" bit/s"));
    Serial.print(F("Exact bit rate ? "));
    Serial.println(settings.exactBitRate() ? "yes" : "no");
    Serial.print(F("Sample point: "));
    Serial.print(settings.samplePointFromBitStart());
    Serial.println(F("%"));
  } else {
    Serial.print(F("Configuration error 0x"));
    Serial.println(errorCode, HEX);
  }
}

void debugFrame(CANMessage& frame){
  Serial.println();
  Serial.print(F("DEBUG: Id ["));
  Serial.print(frame.id);
  Serial.print(F("] Data ["));
  for (byte i = 0; i < 4; i++) {
    Serial.print(F("["));
    Serial.print(frame.data16[i]);
    Serial.print(F("]"));
  }
  Serial.println(F("]"));
}

#endif