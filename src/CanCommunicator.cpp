#include "CanCommunicator.h"

CanComm::CanComm(CAN_CONFIGURATION &_conf, Weiche *_weiche, Signal *_signal, ChangeWeiche _cw) : weiche(_weiche), signal(_signal) {
    changeWeicheCallback = _cw;
    can_configuration = _conf;
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