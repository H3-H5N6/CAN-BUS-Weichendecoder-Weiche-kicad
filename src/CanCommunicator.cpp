#include "CanCommunicator.h"

#define CAN_DEBUG

#define VERSION 5
#define DEFAULT_MODUL_ID 1
#define FIRST_WEICHEN_ID 801
#define FIRST_SIGNAL_ID 901

static const byte MCP2515_CS = 10;  // CS input of MCP2515
static const byte MCP2515_INT = 3;  // INT output of MCP2515

static ACAN2515 can(MCP2515_CS, SPI, MCP2515_INT);

static const uint32_t QUARTZ_FREQUENCY = 16UL * 1000UL * 1000UL;  // 16 MHz

CanComm::CanComm(CAN_CONFIGURATION *_conf, Weiche *_weiche, Signal *_signal, ChangeWeiche _cw) : weiche(_weiche), signal(_signal) {
  changeWeicheCallback = _cw;
  conf = _conf;
}

void CanComm::initCanIds() {
  conf->config.modulId = DEFAULT_MODUL_ID;
  conf->config.firstIdWeiche = FIRST_WEICHEN_ID + (DEFAULT_MODUL_ID - 1) * 10;
  conf->config.firstIdSignal = FIRST_SIGNAL_ID + (DEFAULT_MODUL_ID - 1) * 10;
}

void CanComm::initVersion() {
  conf->config.version = VERSION;
}

void CanComm::writeCanConfigToEEPROM() {
  Serial.print(F("Schreibe initiale Konfig ..."));
  EEPROM.put(CAN_BUS_OFFSET, conf);
  Serial.print(F(". fertig"));
}

void CanComm::initCanConfiguraion(byte configPin) {
  EEPROM.get(CAN_BUS_OFFSET, conf->data);

  boolean writeConfigToEEPROM = false;

  // Modul ID und CAN-Bus-Adresse ggf. initialisieren
  if (configPin == 3 || conf->config.version == 0) {
    initCanIds();
    writeConfigToEEPROM = true;
  }

  if (conf->config.version != VERSION) {
    initVersion();
    writeConfigToEEPROM = true;
  }

  if (writeConfigToEEPROM) {
    writeCanConfigToEEPROM();
  }
}

void CanComm::printlnCanDebug(const __FlashStringHelper *key, const uint32_t value ) {
#ifdef CAN_DEBUG
  printCanDebug(key, value);
  Serial.println();
#endif
}

void CanComm::printlnCanDebug(const __FlashStringHelper *key) {
#ifdef CAN_DEBUG
  printCanDebug(key);
  Serial.println();
#endif
}

void CanComm::printCanDebug(const __FlashStringHelper *key) {
#ifdef CAN_DEBUG
  Serial.print(F("DEBUG CAN "));
  Serial.print(key);
#endif
}

void CanComm::printCanDebug(const __FlashStringHelper *key, const uint32_t value ) {
#ifdef CAN_DEBUG
  printCanDebug(key);
  Serial.print(F(": "));
  Serial.print(value);
#endif
}

void CanComm::printlnCanInfo(const __FlashStringHelper *key) {
  Serial.print(F("INFO CAN "));
  Serial.print(key);
}

void CanComm::printlnCanInfo(const __FlashStringHelper *key, const uint32_t value ) {
  Serial.print(F("INFO CAN "));
  Serial.print(key);
  Serial.print(F(": "));
  Serial.println(value);
}

void CanComm::init() {
  printlnCanInfo(F(" == init CAN Start == "));
  Serial.println();

  SPI.begin();
  ACAN2515Settings settings(QUARTZ_FREQUENCY, 125UL * 1000UL);
  settings.mRequestedMode = ACAN2515Settings::NormalMode;
  /** Buffer verkleinert, da wenig RAM verfügbar ist. Siehe auch
   * https://github.com/pierremolinaro/acan2515/issues/2 */
  settings.mReceiveBufferSize = 12;
  settings.mTransmitBuffer0Size = 12;
  const uint16_t errorCode = can.begin(settings, [] { can.isr(); });
  if (errorCode == 0) {
    printlnCanInfo(F("Receive Buffer Size"), settings.mReceiveBufferSize);
    printlnCanInfo(F("Transmit Buffer Size"), settings.mTransmitBuffer0Size);
    printlnCanInfo(F("Bit Rate prescaler"),settings.mBitRatePrescaler);
    printlnCanInfo(F("Propagation Segment"), settings.mPropagationSegment);
    printlnCanInfo(F("Phase segment 1"),settings.mPhaseSegment1);
    printlnCanInfo(F("Phase segment 2"), settings.mPhaseSegment2);
    printlnCanInfo(F("SJW: "), settings.mSJW);
    printlnCanInfo(F("Triple Sampling"), settings.mTripleSampling) ; // ? "yes" : "no"
    printlnCanInfo(F("Actual bit rate"), settings.actualBitRate()); // Serial.println(F(" bit/s"));
    printlnCanInfo(F("Exact bit rate ?"), settings.exactBitRate()); // ? "yes" : "no");
    printlnCanInfo(F("Sample point"), settings.samplePointFromBitStart()); // "%"));
  } else {
    printlnCanInfo(F("Configuration error 0x"));
    Serial.println(errorCode, HEX);
  }

  printlnCanInfo(F(" == init CAN Ende == "));
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

    printCanDebug(F("Frame ID"), frame.id);
    Serial.print(F(" Data: "));
    for (byte z = 0; z < 8; z++) {
      Serial.print(data[z]);
      Serial.print(F(" "));
    }

    for (byte n = 0; n < 2; n++) {
      for (byte k = 0; k < 4; k++) {
        frame.data16[k] = data[n * 4 + k];
      }

      bool ok = can.tryToSend(frame);
      if (ok) {
        Serial.print(F("ok "));
      } else {
        Serial.print(F("err "));
      }
    }
    Serial.println();
  }
}

void CanComm::processCanMessageGetStatus() {
  printlnCanDebug(F("Modul-ID"),conf->config.modulId);
  printlnCanDebug(F("Data 0"), frame.data16[0]);

  if (frame.data16[0] == conf->config.modulId) {
    printCanDebug(F("Status Weichen: "));
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
    printlnCanDebug(F(""));
    printlnCanDebug(F("Receive frame ID"),frame.id);

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
    printlnCanDebug(F("sendDetailWeichenStatus"));
    sendDetailWeichenStatus();
    send_mode = 0;
  }
}

void CanComm::printConfig() {
  Serial.print(F("Modul ID:  => "));
  Serial.println(conf->config.modulId);

  Serial.print(F("Version => "));
  Serial.println(VERSION);

  Serial.print(F("Erste Can ID Weiche  => "));
  Serial.println(conf->config.firstIdWeiche);

  Serial.print(F("Erste Can ID Signal => "));
  Serial.println(conf->config.firstIdSignal);
}