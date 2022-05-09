#include "Signal.h"

Signal::Signal() {
}

Signal::Signal(uint16_t _firstAddress, uint16_t _firstDccAddress, uint8_t _i2cIndex, I2CSignal *_i2csignal, SIGNAL::SOCKET _socket) : Debounce(), firstAddress(_firstAddress), lastAddress(_firstAddress + 3), firstDccAddress(_firstDccAddress), lastDccAddress(_firstDccAddress + 1), i2cIndex(_i2cIndex), i2csignal(_i2csignal), socket(_socket) {
  position = SIGNAL::POSITION::HP0;
  state = SIGNAL::STATE::SET;
}

boolean Signal::find(uint16_t _address) {
  if ((_address < firstAddress) || (_address > lastAddress)) {
    return false;
  }
  return true;
}

boolean Signal::findDccAddr(uint16_t _address) {
  if ((_address < firstDccAddress) || (_address > lastDccAddress)) {
    return false;
  }
  return true;
}

boolean Signal::changeDcc(uint16_t _address, uint8_t direction) {
  if (findDccAddr(_address)) {
    // Etwas Magie: DCC-Adresse und direction auf die CAN-Adresse mappen
    uint8_t offset = (_address - firstDccAddress) * 2 + direction;
    switch (offset) {
      case 2:
        offset = 3;
        break;
      case 3:
        offset = 2;
        break;
    }
    return change(firstAddress + offset);
  }
  return false;
}

uint8_t Signal::getDebounceMaske(uint16_t dccAddr, uint8_t direction) {
  Serial.println(F("DEBUG: Signal.getDebounceMaske"));
  uint8_t mask = 0;
  if (dccAddr == firstDccAddress) {
    mask = 0b001;
  }
  if (dccAddr == lastDccAddress) {
    mask = 0b0100;
  }
  if (direction > 0) {
    mask = mask << 1;
  }
  return mask;
}

boolean Signal::change(uint16_t _address) {
  if ((_address < firstAddress) || (_address > lastAddress)) {
    return false;
  }

  switch (_address - firstAddress + 1) {  //  900,901,902,903 - 900 => 1 2 3 4
    case SIGNAL::POSITION::HP0:           // 1
      if (isHp0()) {
        return true;
      }
      position = SIGNAL::POSITION::HP0;
      state = SIGNAL::STATE::SET;
      break;
    case SIGNAL::POSITION::HP1:
      if (isHp1()) {
        return true;
      }
      position = SIGNAL::POSITION::HP1;
      state = SIGNAL::STATE::SET;
      break;

    case SIGNAL::POSITION::HP2:
      if (isHp2()) {
        return true;
      }
      position = SIGNAL::POSITION::HP2;
      state = SIGNAL::STATE::SET;
      break;
    case SIGNAL::POSITION::HP0SH1:
      if (isSh1()) {
        return true;
      }
      position = SIGNAL::POSITION::HP0SH1;
      state = SIGNAL::STATE::SET;
      break;
  }

  return true;
}

boolean Signal::isHp0() {
  if (position == SIGNAL::POSITION::HP0 && state == SIGNAL::STATE::POSITION_REACHED) {
    return true;
  }
  return false;
}

boolean Signal::isHp1() {
  if (position == SIGNAL::POSITION::HP1 && state == SIGNAL::STATE::POSITION_REACHED) {
    return true;
  }
  return false;
}

boolean Signal::isHp2() {
  if (position == SIGNAL::POSITION::HP2 && state == SIGNAL::STATE::POSITION_REACHED) {
    return true;
  }
  return false;
}

boolean Signal::isSh1() {
  if (position == SIGNAL::POSITION::HP0SH1 && state == SIGNAL::STATE::POSITION_REACHED) {
    return true;
  }
  return false;
}

void Signal::process() {
  if (state == SIGNAL::STATE::SET) {
    uint8_t value;
    switch (position) {
      case SIGNAL::POSITION::UNKNOWN:
      case SIGNAL::POSITION::HP0:
        value = i2csignal->getHP0(socket);
        break;
      case SIGNAL::POSITION::HP1:
        value = i2csignal->getHP1(socket);
        break;
      case SIGNAL::POSITION::HP2:
        value = i2csignal->getHP2(socket);
        break;
      case SIGNAL::POSITION::HP0SH1:
        value = i2csignal->getSH1(socket);
        break;
    }
    Serial.print(F("DEBUG I2C : i"));
    Serial.print(i2cIndex);
    Serial.print(F(" v: 0x"));
    Serial.println(value, HEX);

    i2csignal->setNewState(value, i2cIndex);
    i2csignal->writeState();
    state = SIGNAL::STATE::POSITION_REACHED;
  }
}
