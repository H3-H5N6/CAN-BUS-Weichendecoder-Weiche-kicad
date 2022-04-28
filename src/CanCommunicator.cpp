#include "CanCommunicator.h"


static const byte MCP2515_CS = 10;  // CS input of MCP2515
static const byte MCP2515_INT = 3;  // INT output of MCP2515

static ACAN2515 can(MCP2515_CS, SPI, MCP2515_INT);

static const uint32_t QUARTZ_FREQUENCY = 16UL * 1000UL * 1000UL;  // 16 MHz

CanComm::CanComm(CAN_CONFIGURATION &_conf, Weiche *_weiche, Signal *_signal, ChangeWeiche _cw) : weiche(_weiche), signal(_signal) {
    changeWeicheCallback = _cw;
    can_configuration = _conf;
}


void CanComm::print(const __FlashStringHelper *ifsh) {
  Serial.print(F("DEBUG CAN "));
  Serial.print(ifsh);
  Serial.print(F(": "));
}

void CanComm::init() {
  print(F(" == init CAN Start == "));
  Serial.println();

  SPI.begin();
  ACAN2515Settings settings(QUARTZ_FREQUENCY, 125UL * 1000UL);
  settings.mRequestedMode = ACAN2515Settings::NormalMode;
  /** Buffer verkleinert, da wenig RAM verfügbar ist. Siehe auch 
   * https://github.com/pierremolinaro/acan2515/issues/2 */
  settings.mReceiveBufferSize = 12 ;
  settings.mTransmitBuffer0Size = 12 ;
  const uint16_t errorCode = can.begin(settings, [] { can.isr(); });
  if (errorCode == 0) {

    print(F("Receive Buffer Size"));
    Serial.println(settings.mReceiveBufferSize);

    print(F("Transmit Buffer Size"));
    Serial.println(settings.mTransmitBuffer0Size);

    print(F("Bit Rate prescaler"));
    Serial.println(settings.mBitRatePrescaler);
    
    print(F("Propagation Segment"));
    Serial.println(settings.mPropagationSegment);

    print(F("Phase segment 1"));
    Serial.println(settings.mPhaseSegment1);

    print(F("Phase segment 2"));
    Serial.println(settings.mPhaseSegment2);

    print(F("SJW: "));
    Serial.println(settings.mSJW);

    print(F("Triple Sampling"));
    Serial.println(settings.mTripleSampling ? "yes" : "no");
    
    print(F("Actual bit rate"));
    Serial.print(settings.actualBitRate());
    Serial.println(F(" bit/s"));

    print(F("Exact bit rate ?"));
    Serial.println(settings.exactBitRate() ? "yes" : "no");

    print(F("Sample point"));
    Serial.print(settings.samplePointFromBitStart());
    Serial.println(F("%"));
  } else {
    print(F("Configuration error 0x"));
    Serial.println(errorCode, HEX);
  }
  
  print(F(" == init CAN Ende == "));
  Serial.println();
}

void CanComm::sendDetailWeichenStatus() {
  frame.id = 300;

  frame.ext = false;
  frame.rtr = false;
  frame.len = 8;

  uint16_t data[8];

  for (byte i = 0; i < 5; i++) {
    weiche[i].statusForCan(data);
    Serial.print(F("Frame ID: "));
    Serial.print(frame.id);
    Serial.print(F(" Data: "));
    for (byte z = 0; z < 8; z++) {
      Serial.print(data[z]);
      Serial.print(F(" "));
    }
    Serial.println();

    for (byte n = 0; n < 2; n++) {
      for (byte k = 0; k < 4; k++) {
        frame.data16[k] = data[n * 4 + k];
      }
      bool ok = can.tryToSend(frame);
      if (ok) {
        Serial.print(F("Sent ok"));
      } else {
        Serial.println(F("Send failure"));
      }
      // frame.id = frame.id + 1;
    }
  }
}

void CanComm::processCanMessageGetStatus() {
  if (frame.data16[0] == can_configuration.config.id) {
    Serial.println();
    Serial.print("Status: ");
    for (byte i = 0; i < 5; i++) {
      Serial.print(weiche[i].statusAsAddress());
      Serial.print(" ");
    }
    Serial.println();
    send_mode = 1;
  }
}

void CanComm::processCanMessageChangeState() {
  for (byte i = 0; i < 4; i++) {
    uint16_t adr = frame.data16[i];
    if (adr != 0) {
      changeWeicheCallback(adr);
    }
  }
  Serial.println();
}

void CanComm::processCanMessage() {
  if (can.receive(frame)) {
    // debugFrame(frame);

    switch (frame.id) {
      case 100:
        processCanMessageChangeState();
        break;
      case 200:
        processCanMessageGetStatus();
        break;
    }
  }

  if (send_mode == 1) {
    Serial.println("sendDetailWeichenStatus");
    sendDetailWeichenStatus();
    send_mode = 0;
  }
}